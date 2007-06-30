/*
 * SingleModelVisuals.java
 *
 * Created on November 14, 2006, 5:46 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.io.File;
import java.util.Hashtable;
import java.util.Iterator;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.Model;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.AnalyticCylinder;
import org.opensim.modeling.AnalyticEllipsoid;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.AnalyticSphere;
import org.opensim.modeling.AnalyticTorus;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.MuscleViaPoint;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Transform;
import org.opensim.modeling.VisibleObject;
import org.opensim.utils.GeometryFileLocator;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkClipPolyData;
import vtk.vtkCylinderSource;
import vtk.vtkLinearTransform;
import vtk.vtkMatrix4x4;
import vtk.vtkParametricFunctionSource;
import vtk.vtkParametricTorus;
import vtk.vtkPlane;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkSphereSource;
import vtk.vtkStripper;
import vtk.vtkTransform;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkXMLPolyDataReader;
import vtk.vtkAppendPolyData;

/**
 *
 * @author Ayman. A class representing the visuals of one model.
 * This class does not actually display the model. Instead it builds the
 * data structures (vtkAssembly) needed to display the model and also
 * maintains the maps for finding an object based on selection and vice versa.
 *
 * Sources of slow down:
 * 1. Too many assemblies (1 per muscle).
 * 2. Too many actors (markers, muscle points) these should replaced with Glyph3D or TensorGlyphs
 * 3. Selection is slow because hashing vtkProp3D apparently doesn't destribute objects evenly use 
 *       some form of Id instead (e.g. vtkId).
 */
public class SingleModelVisuals {
    
    private vtkAssembly modelDisplayAssembly;   // assembly representing the model
    private vtkLinearTransform modelDisplayTransform; // extra transform to shift, rotate model
    private double opacity;
    private double[] bounds = new double[6];
    private boolean visible;

    private double[] defaultMuscleColor = new double[]{0.8, 0.1, 0.1};
    private double[] defaultMusclePointColor = new double[]{1.0, 0.0, 0.0};
    private double[] defaultMarkerColor = new double[]{1.0, 0.6, 0.8};
    private double[] defaultWrapObjectColor = new double[]{0.0, 1.0, 1.0};
    private double DEFAULT_MUSCLE_RADIUS = .005;

    // Maps between objects and vtkProp3D for going from Actor to Object and vice versa
    // Objects are mapped to vtkProp3D in general, but some are known to be assemblies
    // e.g. Muscles, Models
    private Hashtable<OpenSimObject, vtkProp3D> mapObject2VtkObjects = new Hashtable<OpenSimObject, vtkProp3D>();
    private Hashtable<vtkProp3D, OpenSimObject> mapVtkObjects2Objects = new Hashtable<vtkProp3D, OpenSimObject>(50);
   
    private Hashtable<OpenSimObject, LineSegmentMuscleDisplayer> mapActuator2Displayer = new Hashtable<OpenSimObject, LineSegmentMuscleDisplayer>();

    private Hashtable<OpenSimObject, Integer> mapMarkers2Glyphs = new Hashtable<OpenSimObject, Integer>(50);
    
    // Markers and muscle points are represented as Glyphs for performance
    private OpenSimvtkGlyphCloud  markersRep=new OpenSimvtkGlyphCloud();
    private OpenSimvtkGlyphCloud  musclePointsRep=new OpenSimvtkGlyphCloud(true,false);
    private OpenSimvtkOrientedGlyphCloud  muscleSegmentsRep = new OpenSimvtkOrientedGlyphCloud();

    private vtkProp3DCollection    userObjects = new vtkProp3DCollection();

    /**
     * Creates a new instance of SingleModelVisuals
     */
    public SingleModelVisuals(Model aModel) {
        initDefaultShapesAndColors();
        modelDisplayAssembly = createModelAssembly(aModel);
        setVisible(true);
    }
    /**
     * Find the vtkProp3D for the passed in object
     */
    public vtkProp3D getVtkRepForObject(OpenSimObject obj)
    {
        return mapObject2VtkObjects.get(obj);
    }
    /**
     * find the Object for passed in vtkProp3D
     */
    public OpenSimObject getObjectForVtkRep(vtkProp3D prop)
    {
        return mapVtkObjects2Objects.get(prop);
    }

    /**************************************************************
     * First Creation of Model Visuals
     **************************************************************/
    /**
     * Create one vtkAssembly representing the model and return it.
     */
    protected vtkAssembly createModelAssembly(Model model)
    {
        File modelFile = new File(model.getInputFileName());
        String modelFilePath = "";
        if (modelFile.getParent()!= null)
            modelFilePath= modelFile.getParent()+ modelFile.separator; // Could this be null?
                
        vtkAssembly modelAssembly = new vtkAssembly();

        // Keep track of ground body to avoid recomputation
        AbstractBody gnd = model.getDynamicsEngine().getGroundBody();
        BodySet bodies = model.getDynamicsEngine().getBodySet();
 
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++)
        {
            AbstractBody body = bodies.get(bodyNum);

            // Body actor
            vtkActor bodyRep = createAndAddBodyActor(modelAssembly, body, modelFilePath);

            if(bodyRep!=null) {
               // Fill the maps between objects and display to support picking, highlighting, etc..
               // The reverse map takes an actor to an Object and is filled as actors are created.
               mapObject2VtkObjects.put(body, bodyRep);
               mapVtkObjects2Objects.put(bodyRep, body);
            }

            // Bodies have things attached to them as handled by the
            // dependents mechanism. For each one of these a new vtkActor is created and attached 
            // to the same xform as the owner body.
            VisibleObject bodyDisplayer = body.getDisplayer();
            for(int j=0; j < bodyDisplayer.countDependents();j++){
                VisibleObject Dependent = bodyDisplayer.getDependent(j);
                
                OpenSimObject owner = Dependent.getOwner();
                if (AbstractMarker.safeDownCast(owner)!=null){
                    int index= getMarkersRep().addLocation(owner);
                    mapMarkers2Glyphs.put(owner, new Integer(index));
                    continue;
                } else if (MusclePoint.safeDownCast(owner)!=null||
                           MuscleViaPoint.safeDownCast(owner)!=null){
                   // Muscle points are handled in addActuatorsGeometry
                } else {
                   vtkActor attachmentRep = createAndAddWrapObjectActor(modelAssembly, Dependent);
                   if(attachmentRep!=null) {
                      mapObject2VtkObjects.put(Dependent.getOwner(), attachmentRep);
                      mapVtkObjects2Objects.put(attachmentRep, Dependent.getOwner());
                   }
                }
            }
        } //body

        // Add markers
        modelAssembly.AddPart(getMarkersRep().getVtkActor());

        // Now the muscles and other actuators
        addActuatorsGeometry(model, modelAssembly);

        // Add whole model assembly to object map
        mapObject2VtkObjects.put(model, modelAssembly);
        mapVtkObjects2Objects.put(modelAssembly, model);

        // Now call update to actually set all the positions/transforms of the actors and glyphs
        updateModelDisplay(model);

        return modelAssembly;
    }

   /**
    * Create actor for a single AbstractBody
    */
   private vtkActor createAndAddBodyActor(vtkAssembly modelAssembly, AbstractBody body, String modelFilePath)
   {
      vtkActor bodyRep = new vtkActor();

      VisibleObject bodyDisplayer = body.getDisplayer();

      vtkAppendPolyData bodyPolyData = new vtkAppendPolyData();
      // For each bone in the current body.
      for (int k = 0; k < bodyDisplayer.getNumGeometryFiles(); ++k) {
          vtkXMLPolyDataReader polyReader = new vtkXMLPolyDataReader();
          String boneFile = GeometryFileLocator.getInstance().getFullname(modelFilePath,bodyDisplayer.getGeometryFileName(k));
          if (boneFile==null)
             continue;
          polyReader.SetFileName(boneFile);

          vtkPolyData poly = polyReader.GetOutput();
          // Create polyData and append it to one common polyData object
          bodyPolyData.AddInput(poly);
          polyReader.GetOutput().ReleaseDataFlagOn();
      }

      // Mapper
      vtkPolyDataMapper bodyMapper = new vtkPolyDataMapper();
      bodyMapper.SetInput(bodyPolyData.GetOutput());
      bodyRep.SetMapper(bodyMapper);

      // Scale
      double[] scales = new double[3];
      bodyDisplayer.getScaleFactors(scales);
      bodyRep.SetScale(scales);

      // Add to assembly only if populated to avoid artificially big bounding box
      if (bodyDisplayer.getNumGeometryFiles()>0)
         modelAssembly.AddPart(bodyRep);

      return bodyRep;
   }

   /**
    * Create actor for wrap object(s)
    * TODO: Does this really handle multiple geometries under the visibleObject?
    */
   private vtkActor createAndAddWrapObjectActor(vtkAssembly modelAssembly, VisibleObject visibleObject)
   {
      vtkActor attachmentRep = new vtkActor();
      for(int gc=0; gc<visibleObject.countGeometry(); gc++){
         Geometry g = visibleObject.getGeometry(gc);
         AnalyticGeometry ag=null;
         ag = AnalyticGeometry.dynamic_cast(g);
         if (ag != null){  
            vtkPolyData analyticPolyData = AnalyticGeometryDisplayer.getPolyData(ag);

            // Move rep to proper location 
            vtkTransformPolyDataFilter mover = new vtkTransformPolyDataFilter();
            vtkTransform moverTransform = new vtkTransform();
            moverTransform.SetMatrix(convertTransformToVtkMatrix4x4(visibleObject.getTransform()));
            mover.SetInput(analyticPolyData);
            mover.SetTransform(moverTransform);
            
            // Mapper
            vtkPolyDataMapper mapper = new vtkPolyDataMapper();
            mapper.SetInput(mover.GetOutput());
            attachmentRep.SetMapper(mapper);

            // Color/shading
            attachmentRep.GetProperty().SetColor(defaultWrapObjectColor);
            attachmentRep.GetProperty().SetRepresentationToWireframe();
         } else {  // General geometry
            // throw an exception for not implemented though should be identical
            throw new UnsupportedOperationException(
                    "Single Model Visuals: Geometry visualization Not yet implemented");
         }
      }

      if(attachmentRep!=null) modelAssembly.AddPart(attachmentRep);

      return attachmentRep;
   }

    /**
     * updateModelDisplay with new transforms cached in animationCallback.
     * This method must be optimized since it's invoked during live animation
     * of simulations and/or analyses (ala IK).
     */
   public void updateModelDisplay(Model model) {
      // Cycle thru bodies and update their transforms from the kinematics engine
        double[] pos = new double[3];
        double[] gPos = new double[3];
        BodySet bodies = model.getDynamicsEngine().getBodySet();
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++){

            AbstractBody body = bodies.get(bodyNum);

            // Fill the maps between objects and display to support picking, highlighting, etc..
            // The reverse map takes an actor to an Object and is filled as actors are created.
            vtkProp3D bodyRep= mapObject2VtkObjects.get(body);
            vtkMatrix4x4 bodyVtkTransform= getBodyTransform(model, body);
            bodyRep.SetUserMatrix(bodyVtkTransform);

            // For dependents (markers, muscle points, update xforms as well)
            VisibleObject bodyDisplayer = body.getDisplayer();
            for(int j=0; j < bodyDisplayer.countDependents();j++){
                VisibleObject dependent = bodyDisplayer.getDependent(j);
                OpenSimObject owner = dependent.getOwner();

                if (AbstractMarker.safeDownCast(owner)!=null){
                    // Convert marker pos to global pos, and update the marker's glyph location
                    dependent.getTransform().getPosition(pos);
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index = (mapMarkers2Glyphs.get(owner)).intValue();
                    getMarkersRep().setLocation(index, gPos);
                } else if (MusclePoint.safeDownCast(owner)!=null||
                        MuscleViaPoint.safeDownCast(owner)!=null){
                   // Muscle points are handled in updateActuatorsGeometry
                } else {
                   // Must be a wrap object, so we set the wrap object's transform to the body transform (the wrap object
                   // has an additional xform that was set in createModelAssembly specifying the wrap object's xform in its parent body's space)
                   vtkProp3D deptAssembly = mapObject2VtkObjects.get(dependent.getOwner());
                   deptAssembly.SetUserMatrix(bodyVtkTransform);
                }
            }
        }
       
        getMarkersRep().setModified();
        updateActuatorsGeometry(model);
        updateUserObjects();
   }

   /**
    * Functions for dealing with actuator geometry
    */
    private void addActuatorsGeometry(Model mdl, vtkAssembly modelAssembly) {
        ActuatorSet acts = mdl.getActuatorSet();
        for(int actNumber=0; actNumber < acts.getSize(); actNumber++){
           addActuatorGeometry(acts.get(actNumber), false);
        }
        modelAssembly.AddPart(getMuscleSegmentsRep().getVtkActor());
        getMuscleSegmentsRep().setModified();
        modelAssembly.AddPart(getMusclePointsRep().getVtkActor());
        getMusclePointsRep().setModified();
    }

    public void addActuatorGeometry(AbstractActuator act, boolean callSetModified) {
       AbstractMuscle muscle = AbstractMuscle.safeDownCast(act);
       if(muscle == null) return;
       LineSegmentMuscleDisplayer disp = new LineSegmentMuscleDisplayer(muscle, getMusclePointsRep(), getMuscleSegmentsRep());
       mapActuator2Displayer.put(act, disp);
       disp.addGeometry();
       if (callSetModified) {
          getMuscleSegmentsRep().setModified();
          getMusclePointsRep().setModified();
       }
    }

   private void updateActuatorsGeometry(ActuatorSet acts) {
      Iterator<LineSegmentMuscleDisplayer> dispIter = mapActuator2Displayer.values().iterator();
      while(dispIter.hasNext()) dispIter.next().updateGeometry(true);
      getMuscleSegmentsRep().setModified();
      getMusclePointsRep().setModified();
   }

   public void updateActuatorGeometry(AbstractActuator act, boolean callUpdateDisplayer) {
      LineSegmentMuscleDisplayer disp = mapActuator2Displayer.get(act);
      if(disp != null) {
         disp.updateGeometry(callUpdateDisplayer);
         getMuscleSegmentsRep().setModified();
         getMusclePointsRep().setModified();
      }
   }

   public void updateActuatorsGeometry(Model mdl) {
      updateActuatorsGeometry(mdl.getActuatorSet());
   }

   public void removeActuatorGeometry(AbstractActuator act) {
      LineSegmentMuscleDisplayer disp = mapActuator2Displayer.get(act);
      if(disp != null) {
         disp.removeGeometry();
         mapActuator2Displayer.remove(act);
         getMuscleSegmentsRep().setModified();
         getMusclePointsRep().setModified();
      }
   }

     /**
      * Get the vtkTransform matrix between ground and a body frame,
      */
     vtkMatrix4x4 getBodyTransform(Model model, AbstractBody body)
     {
            Transform xform = model.getDynamicsEngine().getTransform(body);
            return convertTransformToVtkMatrix4x4(xform);
     }
    /**
     * return a reference to the vtkAssembly representing the model
     */
    public vtkAssembly getModelDisplayAssembly() {
        return modelDisplayAssembly;
    }
    
    public OpenSimObject pickObject(vtkAssemblyPath asmPath) {
        if (asmPath != null) {
         vtkAssemblyNode pickedAsm = asmPath.GetLastNode();
         return mapVtkObjects2Objects.get(pickedAsm.GetViewProp());
        }  
        return null;    // No selection
    }

    public vtkLinearTransform getModelDisplayTransform() {
        return modelDisplayTransform;
    }

    /**
     * Since there's no global model opacity, we'll take the opacity of the first object
     * we find and use it as value for the Opacity of he model. This has the advantage that
     * if Opacities are the same for all objects then the behavior is as expected.
     */
    public double getOpacity() {
        vtkProp3D prop = modelDisplayAssembly.GetParts().GetLastProp3D();  
        
        if (prop instanceof vtkAssembly){   //recur
            opacity = getAssemblyOpacity((vtkAssembly)prop);            
        }
        else if (prop instanceof vtkActor){ // Could be Actor or whatelse?
            opacity = ((vtkActor)prop).GetProperty().GetOpacity();
        }

        return opacity;
    }

    public void setOpacity(double opacity) {
        this.opacity = opacity;
    }

    /**
     * Compute bounding box for model as this can be useful for initial placement
     *  This is supposed to be a ballpark rather than an accurate estimate so that minor changes to
     * model do not cause overlap, but the bboox is not intended to be kept up-to-date
     * unused and turned out to be very slow for some reason*/
    private void computeModelBoundingbox() {
        modelDisplayAssembly.GetBounds(bounds);
    }
    /**
     * A flag indicating if the model assembly is shown or not for global visibility control
     */
    public boolean isVisible() {
        return visible;
    }

    public void setVisible(boolean onOff) {
        this.visible = onOff;
    }

    double[] getOffset() {
        return modelDisplayAssembly.GetPosition();
    }

    private double getAssemblyOpacity(vtkAssembly anAssembly) {
        vtkProp3DCollection parts = anAssembly.GetParts();
        parts.InitTraversal();
        int n =parts.GetNumberOfItems();
        for(int i=0; i<n; i++){
            vtkProp3D prop = parts.GetNextProp3D();
            if (prop instanceof vtkAssembly){   
                return getAssemblyOpacity((vtkAssembly)prop);
                // Should continue traversal here
            }
            else if (prop instanceof vtkActor){ 
                return ((vtkActor)prop).GetProperty().GetOpacity();
            }
        }
        return 0;
    }
   /**
    * Utility to convert Transform as defined by OpenSim to the form used by vtk
    */
   private vtkMatrix4x4 convertTransformToVtkMatrix4x4(Transform xform) {
      double[] xformAsVector= new double[16];
      xform.getMatrix(xformAsVector);
      vtkMatrix4x4 m = new vtkMatrix4x4();    // This should be moved out for performance
      // Transpose the rotation part of the matrix per Pete!!
      for (int row = 0; row < 3; row++){
          for (int col = row; col < 4; col++){
             double swap = xformAsVector[row*4+col];
             xformAsVector[row*4+col]=xformAsVector[col*4+row];
             xformAsVector[col*4+row]=swap;
          }
      }
      m.DeepCopy(xformAsVector);
      return m;
   }

   /**
    * Method used to update display of motion objects during animation 
    */
   private void updateUserObjects() {
      
   }
   
   public void addUserObject(vtkActor userObj){
      if (userObjects.IsItemPresent(userObj)==0){
        userObjects.AddItem(userObj);
        modelDisplayAssembly.AddPart(userObj);
      }
   }
   
   public void removeUserObject(vtkActor userObj){
      userObjects.RemoveItem(userObj);
      modelDisplayAssembly.RemovePart(userObj);
   }

   /**
    * Functions to deal with glyphs for markers and muscle points/segments
    */
    private void initDefaultShapesAndColors() {

       // Markers
       vtkSphereSource marker=new vtkSphereSource();
       marker.SetRadius(.01);
       marker.SetCenter(0., 0., 0.);
       getMarkersRep().setColor(defaultMarkerColor);
       vtkStripper strip1 = new vtkStripper();
       strip1.SetInput(marker.GetOutput());
       getMarkersRep().setShape(strip1.GetOutput());
       
       // Muscle points
       vtkSphereSource viaPoint=new vtkSphereSource();
       viaPoint.SetRadius(DEFAULT_MUSCLE_RADIUS);
       viaPoint.SetCenter(0., 0., 0.);
       getMusclePointsRep().setColor(defaultMusclePointColor);
       getMusclePointsRep().colorByScalar();
       vtkStripper strip2 = new vtkStripper();
       strip2.SetInput(viaPoint.GetOutput());
       getMusclePointsRep().setShape(strip2.GetOutput());
       getMusclePointsRep().scaleByVector();
      
       // Muscle segments 
       vtkCylinderSource muscleSegment=new vtkCylinderSource();
       muscleSegment.SetRadius(DEFAULT_MUSCLE_RADIUS);
       muscleSegment.SetHeight(1.0);
       muscleSegment.SetCenter(0.0, 0.0, 0.0);
       muscleSegment.CappingOff();
       getMuscleSegmentsRep().setColor(defaultMuscleColor);
       getMuscleSegmentsRep().setShape(muscleSegment.GetOutput());
    }

    public OpenSimvtkGlyphCloud getGlyphObjectForActor(vtkActor act) {
        if (getMarkersRep().getVtkActor()==act)
            return getMarkersRep();
        else if (getMusclePointsRep().getVtkActor()==act)
            return getMusclePointsRep();
        else
           return null;
    }

    public OpenSimvtkGlyphCloud getMarkersRep() {
        return markersRep;
    }

    public OpenSimvtkGlyphCloud getMusclePointsRep() {
        return musclePointsRep;
    }

    public OpenSimvtkOrientedGlyphCloud getMuscleSegmentsRep() {
        return muscleSegmentsRep;
    }
}
