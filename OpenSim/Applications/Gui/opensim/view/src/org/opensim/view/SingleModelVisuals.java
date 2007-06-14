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
import java.util.Vector;
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractMarker;
import org.opensim.modeling.AbstractMuscle;
import org.opensim.modeling.ArrayMusclePoint;
import org.opensim.modeling.Model;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.AnalyticCylinder;
import org.opensim.modeling.AnalyticEllipsoid;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.AnalyticSphere;
import org.opensim.modeling.AnalyticTorus;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.LineGeometry;
import org.opensim.modeling.MusclePoint;
import org.opensim.modeling.MuscleViaPoint;
import org.opensim.modeling.MuscleWrapPoint;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Transform;
import org.opensim.modeling.VisibleObject;
import org.opensim.modeling.VisibleProperties;
import org.opensim.modeling.VisibleProperties.DisplayPreference;
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
    
    private int RESOLUTION_PHI=32;
    private int RESOLUTION_THETA=32;
    private int CYL_RESOLUTION=32;
    
    private double DEFAULT_MUSCLE_RADIUS = .005;
    // Maps between objects and vtkProp3D for going from Actor to Object and vice versa
    // Objects are mapped to vtkProp3D in general, but some are known to be assemblies
    // e.g. Muscles, Models
    private Hashtable<OpenSimObject, vtkProp3D> mapObject2VtkObjects = new Hashtable<OpenSimObject, vtkProp3D>();
    private Hashtable<vtkProp3D, OpenSimObject> mapVtkObjects2Objects = new Hashtable<vtkProp3D, OpenSimObject>(50);
    
    private Hashtable<OpenSimObject, Vector<Integer>> mapActuator2SegmentGlyphIds = new
            Hashtable<OpenSimObject, Vector<Integer>>();
    private Hashtable<OpenSimObject, Vector<Integer>> mapActuator2PointGlyphIds = new
            Hashtable<OpenSimObject, Vector<Integer>>();

    private Hashtable<OpenSimObject, Integer> mapMarkers2Glyphs = new Hashtable<OpenSimObject, Integer>(50);
    
    // Markers and muscle points are represented as Glyphs for performance
    private OpenSimvtkGlyphCloud  markersRep=new OpenSimvtkGlyphCloud();
    private OpenSimvtkGlyphCloud  musclePointsRep=new OpenSimvtkGlyphCloud(true);
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
                
        double[] scales = new double[3];
        vtkAssembly modelAssembly = new vtkAssembly();
        // Keep track of ground body to avoid recomputation
        AbstractBody gnd = model.getDynamicsEngine().getGroundBody();
        BodySet bodies = model.getDynamicsEngine().getBodySet();
 
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++){

            AbstractBody body = bodies.get(bodyNum);

            // Add a vtkActor to the vtk scene graph to represent
            // the current body.
            vtkActor bodyRep = new vtkActor();

            // Fill the maps between objects and display to support picking, highlighting, etc..
            // The reverse map takes an actor to an Object and is filled as actors are created.
            mapObject2VtkObjects.put(body, bodyRep);

            // Add a vtkActor object to the vtk scene graph to represent
            VisibleObject bodyDisplayer = body.getDisplayer();
            bodyDisplayer.getScaleFactors(scales);

            int ns = bodyDisplayer.getNumGeometryFiles();
            long timepre = System.currentTimeMillis();
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
            // Add to assembly only if populated to avoid artificially big bounding box
            if (bodyDisplayer.getNumGeometryFiles()>0){
               modelAssembly.AddPart(bodyRep);
            }
            vtkMatrix4x4 m= getBodyTransform(model, body);
            bodyRep.SetUserMatrix(m);
            
             vtkPolyDataMapper bodyMapper = new vtkPolyDataMapper();
             bodyMapper.SetInput(bodyPolyData.GetOutput());

             bodyRep.SetMapper(bodyMapper);
             bodyRep.SetScale(scales);
             mapVtkObjects2Objects.put(bodyRep, body);

            // Bodies have things attached to them as handled by the
            // dependents mechanism. For each one of these a new vtkActor is created and attached 
            // to the same xform as the owner body.
             
            int ct = bodyDisplayer.countDependents();
            
            double[] color = new double[3];
            for(int j=0; j < ct;j++){
                VisibleObject Dependent = bodyDisplayer.getDependent(j);
                
                OpenSimObject owner = Dependent.getOwner();
                // There should be a better way to do this type checking
                // than String comparison but dynamic casting across JNI doesn't work!
                String test = owner.getType();
                if (AbstractMarker.safeDownCast(owner)!=null){
                    // Convert marker pos to global pos.
                    double[] pos = new double[3];
                    double[] gPos = new double[3];
                    Dependent.getTransform().getPosition(pos);
                    // xfrom to ground frame
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index= getMarkersRep().addLocation(gPos, owner);
                    mapMarkers2Glyphs.put(owner, new Integer(index));
                    continue;
                }
                vtkActor attachmentRep = new vtkActor();
                attachmentRep.SetUserMatrix(m);
                int geomcount = Dependent.countGeometry();
                // Create actor for the dpendent
                for(int gc=0; gc<geomcount; gc++){
                    Geometry g = Dependent.getGeometry(gc);
                    //vtkActor dActor = new vtkActor();
                    AnalyticGeometry ag=null;
                    ag = AnalyticGeometry.dynamic_cast(g);
                    if (ag != null){  
                        //System.out.println("Processing "+Dependent.getOwner().getName());
                         vtkPolyData analyticPolyData = getPolyDataForAnalyticGeometry(ag);
                         
                         // Move rep to proper location 
                         vtkTransformPolyDataFilter mover = new vtkTransformPolyDataFilter();
                         vtkTransform moverTransform = new vtkTransform();
                         moverTransform.SetMatrix(convertTransformToVtkMatrix4x4(Dependent.getTransform()));
                         mover.SetInput(analyticPolyData);
                         mover.SetTransform(moverTransform);
                         vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                         mapper.SetInput(mover.GetOutput());
                         
                         //Dependent.getVisibleProperties().getColor(color);
                         attachmentRep.GetProperty().SetColor(defaultWrapObjectColor);

                         attachmentRep.SetMapper(mapper);
                         attachmentRep.GetProperty().SetRepresentationToWireframe();
                         //attachmentRep.AddPart(dActor);
                         mapVtkObjects2Objects.put(attachmentRep, Dependent.getOwner());
                    }
                    else {  // General geometry
                        // throw an exception for not implemented though should be identical
                        throw new UnsupportedOperationException(
                                "Single Model Visuals: Geometry visualization Not yet implemented");                    }
                }
                //modelAssembly.AddPart(markersActor);
                modelAssembly.AddPart(attachmentRep);
                mapObject2VtkObjects.put(Dependent.getOwner(), attachmentRep);
                 
            }
        } //body
        modelAssembly.AddPart(getMarkersRep().getVtkActor());
        getMarkersRep().setModified();
        /**
         * Now the muscles and other actuators
         */
        addActuatorsGeometry(model, modelAssembly);
        mapObject2VtkObjects.put(model, modelAssembly);
        mapVtkObjects2Objects.put(modelAssembly, model);
        return modelAssembly;
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
     * Visualize all actuators and add created vtk creatures to the model Assembly
     * Potentially can be used to add muscles separately from a file to an existing model.
     */
    private void addActuatorsGeometry(Model  mdl, vtkAssembly modelAssembly) {
        // Now the muscles which are different creatures since they don't have a frame of their own
        // We'll display them by asking the "actuators for their geometry which may contain 
        // muscle points as well as segments connecting them
        ActuatorSet acts = mdl.getActuatorSet();
        for(int actNumber=0; actNumber < acts.getSize(); actNumber++){   
            AbstractActuator nextMuscle = acts.get(actNumber);
            Vector<Integer>   segmentGlyphIds = new Vector<Integer>(3);
            Vector<Integer>   pointGlyphIds = new Vector<Integer>(3);
            // Get attachments and connect them
            VisibleObject actuatorDisplayer = nextMuscle.getDisplayer();
            if (actuatorDisplayer == null){
                continue;
            }
            // A displayer is found, get geometry
            int geomSize = actuatorDisplayer.countGeometry();
            //System.out.println("Number of points for Actutor"+nextMuscle.getName()+"="+geomSize);
            if (geomSize > 0){
                AbstractMuscle muscle = AbstractMuscle.safeDownCast(nextMuscle);
                String muscleName = muscle.getName();
                ArrayMusclePoint path=muscle.getCurrentPath();
                // Points are already in inertial frame
                for(int i=0; i<geomSize; i++) {
                    Geometry geomEntry = actuatorDisplayer.getGeometry(i);
                    double[] position1 = new double[3];
                    double[] position2 = new double[3];
                    LineGeometry geomLine = LineGeometry.dynamic_cast(geomEntry);
                    geomLine.getPoints(position1, position2);
                    double[] axis = new double[3];
                    double[] center = new double[3];
                    for(int d=0; d <3; d++){
                        axis[d]=position1[d]-position2[d];
                        center[d] = (position1[d]+position2[d])/2.0;
                    }
                    double[] unitAxis = new double[]{axis[0], axis[1], axis[2]};
                    double length = normalizeAndGetLength(axis);
                    double[] xform = getCylinderTransform(axis, center) ;
                    
                    int idx = getMuscleSegmentsRep().addLocation(center[0], center[1], center[2]);
                    getMuscleSegmentsRep().setTensorDataAtLocation(idx, 
                            xform[0], xform[4], xform[8],
                            length*xform[1], length*xform[5], length*xform[9],
                            xform[2], xform[6], xform[10]
                            );
                    segmentGlyphIds.add(new Integer(idx));

                    // Add muscle point at position1 of segment, and if this is the last segment also at position2
                    MusclePoint pt1 = path.get(i);
                    if (MuscleWrapPoint.safeDownCast(pt1)!= null)
                        pt1.setPickable(false);
                    
                    int pointIdx = getMusclePointsRep().addLocation(position1, path.get(i));
                    getMusclePointsRep().setVectorDataAtLocation(pointIdx,1,1,1);
                    pointGlyphIds.add(new Integer(pointIdx));
                    if(i==geomSize-1) {
                        MusclePoint pt2 = path.get(i+1);
                        if (MuscleWrapPoint.safeDownCast(pt2)!= null)
                           pt2.setPickable(false);
                        pointIdx = getMusclePointsRep().addLocation(position2, path.get(i+1));
                        getMusclePointsRep().setVectorDataAtLocation(pointIdx,1,1,1);
                        pointGlyphIds.add(new Integer(pointIdx));
                    }
                } // Attachments
                mapActuator2SegmentGlyphIds.put(nextMuscle, segmentGlyphIds);
                mapActuator2PointGlyphIds.put(nextMuscle, pointGlyphIds);
            } // ArraySize
        }
        modelAssembly.AddPart(getMuscleSegmentsRep().getVtkActor());
        getMuscleSegmentsRep().setModified();
        // EG
        modelAssembly.AddPart(getMusclePointsRep().getVtkActor());
        getMusclePointsRep().setModified();
    }
    /**
     * Get the transform that takes a unit cylinder aligned with Y axis to a cylnder connecting 2 points
     */
    vtkMatrix4x4 retTransform = new vtkMatrix4x4();
    double[]     retTransformVector = new double[16];
    double[] newX = new double[3];
    double[] oldXCrossNewY = new double[3]; // NewZ
    double[] getCylinderTransform(double[] normalizedAxis, double[] origin) {
        //Assume normalizedAxis is already normalized
        //double length = normalizeAndGetLength(axis);
        
        // yaxis is the unit vector
        for (int i=0; i < 3; i++){
            retTransformVector[i*4+ 1]= normalizedAxis[i];
        }
        oldXCrossNewY[0] = 0.0;
        oldXCrossNewY[1] = -normalizedAxis[2];
        oldXCrossNewY[2] = normalizedAxis[1];
        
        normalizeAndGetLength(oldXCrossNewY);
        for (int i=0; i < 3; i++){
            retTransformVector[i*4+ 2]= oldXCrossNewY[i];
        }
        newX[0] = normalizedAxis[1]*oldXCrossNewY[2]-normalizedAxis[2]*oldXCrossNewY[1];
        newX[1] = normalizedAxis[2]*oldXCrossNewY[0]-normalizedAxis[0]*oldXCrossNewY[2];
        newX[2] = normalizedAxis[0]*oldXCrossNewY[1]-normalizedAxis[1]*oldXCrossNewY[0];
        normalizeAndGetLength(newX);
       for (int i=0; i < 3; i++){
          retTransformVector[i*4]= newX[i];
          retTransformVector[i*4+ 3]= origin[i];
         }
        for(int i=12; i<15;i++)
            retTransformVector[i]=0.0;
        retTransformVector[15]=1.0;
        //retTransform.DeepCopy(retTransformVector);
        return retTransformVector;
    }
    /**
     * Normalize a vector and return its length
     */
    private double normalizeAndGetLength(double[] vector3)
    {
        double length = Math.sqrt(vector3[0]*vector3[0]+
                                  vector3[1]*vector3[1]+
                                  vector3[2]*vector3[2]);
        // normalize
        for(int d=0; d <3; d++)
            vector3[d]=vector3[d]/length;
        return length;
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
            //Transform opensimTransform = animationCallback.getBodyTransform(bodyNum);
            //vtkMatrix4x4 bodyVtkTransform = convertTransformToVtkMatrix4x4(opensimTransform);
            bodyRep.SetUserMatrix(bodyVtkTransform);
            // For dependents (markers, muscle points, update xforms as well)
            VisibleObject bodyDisplayer = body.getDisplayer();
            int ct = bodyDisplayer.countDependents();
            
            //System.out.println("Body "+body+" has "+ct+ " dependents");
            for(int j=0; j < ct;j++){
                VisibleObject dependent = bodyDisplayer.getDependent(j);
                OpenSimObject owner = dependent.getOwner();

                if (AbstractMarker.safeDownCast(owner)!=null){
                    // Convert marker pos to global pos.
                    dependent.getTransform().getPosition(pos);
                    // xfrom to ground frame
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index = ((Integer)mapMarkers2Glyphs.get(owner)).intValue();
                    getMarkersRep().setLocation(index, gPos);
                    continue;
                }
                else if (MusclePoint.safeDownCast(owner)!=null||
                        MuscleViaPoint.safeDownCast(owner)!=null){
                    continue;
                }
                vtkProp3D deptAssembly = mapObject2VtkObjects.get(dependent.getOwner());
                deptAssembly.SetUserMatrix(bodyVtkTransform);
            }
            
        }
        // Now the muscles
        updateActuatorsGeometry(model);
        //animationCallback.mutex_end(1);
        getMarkersRep().setModified();
        updateUserObjects();
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

   private void updateActuatorGlyphIds(Vector<Integer> segmentGlyphIds, Vector<Integer> pointGlyphIds, int newNumSegments) {
      int origNumSegments = segmentGlyphIds.size();
      //System.out.println("ORIG="+origNumSegments+" NEW="+newNumSegments+"");
      if (newNumSegments>origNumSegments){   // Make extra segments (and points) and attach them 
         // We always want to maintain one more point than number of segments
         if(origNumSegments==0) {
            int pointIdx = getMusclePointsRep().addLocation(0.0, 0.0, 0.0); // always one more muscle point than number of segments
            pointGlyphIds.add(new Integer(pointIdx));
         }
         // Add required number of segments, and one point for each segment
         for(int i=origNumSegments; i<newNumSegments; i++) {
            int idx = getMuscleSegmentsRep().addLocation(0.0, 0.0, 0.0);
            segmentGlyphIds.add(new Integer(idx));
            int pointIdx = getMusclePointsRep().addLocation(0.0, 0.0, 0.0);
            getMusclePointsRep().setVectorDataAtLocation(pointIdx,1,1,1);
            pointGlyphIds.add(new Integer(pointIdx));
         }
         // Sanity check: number of points should be number of segments + 1
         assert(pointGlyphIds.size()==segmentGlyphIds.size()+1);
      }
      else if (origNumSegments>newNumSegments){ // remove unused segments
         for(int i=newNumSegments; i<origNumSegments; i++) {
            getMuscleSegmentsRep().remove(segmentGlyphIds.get(i).intValue());
            getMusclePointsRep().remove(pointGlyphIds.get(i+1).intValue()); // always one more muscle point than number of segments
         }
         segmentGlyphIds.setSize(newNumSegments);
         if(newNumSegments == 0) {
            getMusclePointsRep().remove(pointGlyphIds.get(0).intValue());
            pointGlyphIds.setSize(0);
         } else {
            pointGlyphIds.setSize(newNumSegments+1);
         }
      }
   }

   /**
    * Update display of muscles and forces if any during playing back animation/motion, ..
    */
   private void updateActuatorsGeometry(ActuatorSet acts, boolean callUpdateGeometry) {
      for(int actNumber=0; actNumber < acts.getSize(); actNumber++){
         updateActuatorGeometry(acts.get(actNumber), callUpdateGeometry);
      }
      //getMuscleSegmentsRep().setModified();
      //getMusclePointsRep().setModified();
   }

   public void updateActuatorGeometry(AbstractActuator act, boolean callUpdateGeometry) {
      //System.out.println("Update geometry for actuator"+act.getName());
      double[] axis = new double[]{0.0, 0.0, 0.0};
      double[] center = new double[]{0.0, 0.0, 0.0};
      if(callUpdateGeometry) act.updateGeometry();
      // Get attachments and connect them
      VisibleObject actuatorDisplayer = act.getDisplayer();
      if (actuatorDisplayer == null){
         return;
      }

      boolean visible = false;
      DisplayPreference dp = actuatorDisplayer.getVisibleProperties().getDisplayPreference();
      if (dp != DisplayPreference.None)
         visible = true;

      // A displayer is found, get geometry
      int geomSize = actuatorDisplayer.countGeometry();
      if (visible == false)
         geomSize = 0;

      Vector<Integer> segmentGlyphIds = mapActuator2SegmentGlyphIds.get(act);
      Vector<Integer> pointGlyphIds = mapActuator2PointGlyphIds.get(act);

      updateActuatorGlyphIds(segmentGlyphIds, pointGlyphIds, geomSize);         

      if (geomSize > 0) {
         double[] position1 = new double[3];
         double[] position2 = new double[3];
         // Points are already in inertial frame
         for(int i=0; i<geomSize; i++) {
            Geometry geomEntry = actuatorDisplayer.getGeometry(i);
            LineGeometry geomLine = LineGeometry.dynamic_cast(geomEntry);
            geomLine.getPoints(position1, position2);
               
            for(int d=0; d <3; d++){
               axis[d]=position1[d]-position2[d];
               center[d] = (position1[d]+position2[d])/2.0;
            }
            // Create a cylinder connecting position1, position2
            double[] unitAxis = new double[]{axis[0], axis[1], axis[2]};
            double length = normalizeAndGetLength(axis);
            double[] xform = getCylinderTransform(axis, center) ;
            int idx = segmentGlyphIds.get(i).intValue();
            getMuscleSegmentsRep().setLocation(idx, center);
            getMuscleSegmentsRep().setTensorDataAtLocation(idx, 
                             xform[0], xform[4], xform[8],
                             length*xform[1], length*xform[5], length*xform[9],
                             xform[2], xform[6], xform[10]
                    );

            // Draw muscle point at position1 of segment, and if this is the last segment also at position2
            int pointIdx = pointGlyphIds.get(i).intValue();
            getMusclePointsRep().setLocation(pointIdx, position1);
            if(i==geomSize-1) {
                pointIdx = pointGlyphIds.get(i+1).intValue();
                getMusclePointsRep().setLocation(pointIdx, position2);
            }
         }
      }

      getMuscleSegmentsRep().setModified();
      getMusclePointsRep().setModified();
   }

   public void updateActuatorsGeometry(Model mdl) {
      updateActuatorsGeometry(mdl.getActuatorSet(), true);
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

    private void initDefaultShapesAndColors() {
        // Markers
       
       vtkSphereSource marker=new vtkSphereSource();
       marker.SetRadius(.01);
       marker.SetCenter(0., 0., 0.);
       getMarkersRep().setColor(defaultMarkerColor);
       vtkStripper strip1 = new vtkStripper();
       strip1.SetInput(marker.GetOutput());
       getMarkersRep().setShape(strip1.GetOutput());
       
       // MusclePoints
       vtkSphereSource viaPoint=new vtkSphereSource();
       viaPoint.SetRadius(DEFAULT_MUSCLE_RADIUS);
       viaPoint.SetCenter(0., 0., 0.);
       getMusclePointsRep().setColor(defaultMusclePointColor);
       getMusclePointsRep().colorByScalar();
       vtkStripper strip2 = new vtkStripper();
       strip2.SetInput(viaPoint.GetOutput());
       getMusclePointsRep().setShape(strip2.GetOutput());
       getMusclePointsRep().scaleByVector();
       
       vtkCylinderSource muscleSegment=new vtkCylinderSource();
       muscleSegment.SetRadius(DEFAULT_MUSCLE_RADIUS);
       muscleSegment.SetHeight(1.0);
       muscleSegment.SetCenter(0.0, 0.0, 0.0);
       muscleSegment.CappingOff();
       
       getMuscleSegmentsRep().setColor(defaultMuscleColor);
       getMuscleSegmentsRep().setShape(muscleSegment.GetOutput());
     }

    /**
     * Convert AnalyticGeometry object passed in to the corresponding vtk polyhedral representation.
     * Transform is passed in as well since the way it applies to PolyData depends on source
     */
    private vtkPolyData getPolyDataForAnalyticGeometry(AnalyticGeometry ag) {
       Geometry.GeometryType analyticType = ag.getShape();
       boolean quadrants[] = new boolean[6];
       ag.getQuadrants(quadrants);
       double[] pos = new double[3];
       if (analyticType == Geometry.GeometryType.Sphere){
          vtkSphereSource sphere = new vtkSphereSource();
          AnalyticSphere typed = AnalyticSphere.dynamic_cast(ag);
          sphere.LatLongTessellationOn(); 
          sphere.SetPhiResolution(RESOLUTION_PHI);
          sphere.SetThetaResolution(RESOLUTION_THETA);
          sphere.SetRadius(typed.getRadius());
          if (ag.isPiece())
            setQuadrants(quadrants, sphere);
          return sphere.GetOutput();
       }
       else if (analyticType == Geometry.GeometryType.Ellipsoid){
          vtkSphereSource sphere = new vtkSphereSource();
          sphere.LatLongTessellationOn(); 
          sphere.SetPhiResolution(RESOLUTION_PHI);
          sphere.SetThetaResolution(RESOLUTION_THETA);
          sphere.SetRadius(1.0);
          if (ag.isPiece())
            setQuadrants(quadrants, sphere);
          
          AnalyticEllipsoid typed = AnalyticEllipsoid.dynamic_cast(ag);
          // Make a stretching transform to take the sphere into an ellipsoid
          vtkTransformPolyDataFilter stretch = new vtkTransformPolyDataFilter();
          vtkTransform stretchSphereToEllipsoid = new vtkTransform();
          double[] params = new double[]{1.0, 1.0, 1.0};
          typed.getEllipsoidParams(params);
          stretchSphereToEllipsoid.Scale(params[0], params[1], params[2]);
          stretch.SetTransform(stretchSphereToEllipsoid);
          stretch.SetInputConnection(sphere.GetOutputPort());
          return stretch.GetOutput();
       }
       else if (analyticType == Geometry.GeometryType.Cylinder){
          vtkCylinderSource cylinder = new vtkCylinderSource();
          cylinder.SetResolution(CYL_RESOLUTION);
          AnalyticCylinder typed = AnalyticCylinder.dynamic_cast(ag);
          double[] params = new double[]{1.0, 1.0};
          typed.getCylinderParams(params);
          //System.out.println("Processing cyl (r, l)"+params[0]+","+params[1]);
          cylinder.SetRadius(params[0]);
          cylinder.SetHeight(params[1]);
          // Transform vtk cylinder (Y-axis aligned at origin) to match SIMM's along Z-axis at center
          vtkTransformPolyDataFilter xformOriginDirsFilter = new vtkTransformPolyDataFilter();
          vtkTransform xformOriginDirs = new vtkTransform();
          xformOriginDirs.RotateX(90);
          xformOriginDirsFilter.SetTransform(xformOriginDirs);
          xformOriginDirsFilter.SetInputConnection(cylinder.GetOutputPort());
          vtkPolyData full = xformOriginDirsFilter.GetOutput();
          if (ag.isPiece())
            return clipPolyData(quadrants, full);
          else
             return full;
       }
       else if (analyticType == Geometry.GeometryType.Torus){
          vtkParametricTorus torus=new vtkParametricTorus();
          vtkParametricFunctionSource torusSource = new vtkParametricFunctionSource();
          torusSource.SetParametricFunction(torus);
          vtkPolyDataMapper torusMapper=new vtkPolyDataMapper();
          torusMapper.SetInputConnection(torusSource.GetOutputPort());

          AnalyticTorus typed = AnalyticTorus.dynamic_cast(ag);
          double[] params = new double[]{1.0, 1.0};
          typed.getTorusParams(params);
          //System.out.println("Processing torus (r1, r2)"+params[0]+","+params[1]);
          torus.SetRingRadius(params[0]);
          torus.SetCrossSectionRadius(params[1]);
          vtkPolyData full = torusSource.GetOutput();
          if (ag.isPiece())
            return clipPolyData(quadrants, full);
          else
             return full;
       }
       return null;
    }
    /**
     * Based on the array of quadrants, clip the wrap-object sphere/ellipsoid 
     */
   private void setQuadrants(final boolean quadrants[], final vtkSphereSource sphere) {
      if (!quadrants[0]){ 
         sphere.SetStartTheta(270.0);
         sphere.SetEndTheta(90.0);
      }
      else if (!quadrants[1]){
         sphere.SetStartTheta(90.0);
         sphere.SetEndTheta(270.0);
      }
      else if (!quadrants[2]){
        sphere.SetEndTheta(180.0);
      }
      else if (!quadrants[3]){  
         sphere.SetStartTheta(180.0);
      }
      else if (!quadrants[4])   
        sphere.SetEndPhi(90.0);
      else if (!quadrants[5])
         sphere.SetStartPhi(90.0);
   }

   /** 
    * Clip poly data of Cylinder, torus to proper half per passed in quadrants array
    * only x, y are considered here as they are supported by the kinematics engine
    */
   private vtkPolyData clipPolyData(boolean[] quadrants, vtkPolyData full) {
      vtkPlane cutPlane = new vtkPlane();
      if (!quadrants[0])
         cutPlane.SetNormal(1.0, 0.0, 0.0);
      else if (!quadrants[1])
         cutPlane.SetNormal(-1.0, 0.0, 0.0);
      else if (!quadrants[2]) 
         cutPlane.SetNormal(0.0, 1.0, 0.0);
      else if (!quadrants[3])
         cutPlane.SetNormal(0.0, -1.0, 0.0);
      else  // do nothing
         return full;
      vtkClipPolyData clipper = new vtkClipPolyData();
      clipper.SetClipFunction(cutPlane);
      clipper.SetInput(full);
      
      return clipper.GetOutput();
   }

    public OpenSimvtkGlyphCloud getGlyphObjectForActor(vtkActor act) {
        if (getMarkersRep().getVtkActor()==act)
            return getMarkersRep();
        if (getMusclePointsRep().getVtkActor()==act)
            return getMusclePointsRep();
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
