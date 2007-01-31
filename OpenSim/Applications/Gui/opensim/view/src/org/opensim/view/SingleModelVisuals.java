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
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.LineGeometry;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.modeling.Transform;
import org.opensim.modeling.VisibleObject;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkCylinderSource;
import vtk.vtkLinearTransform;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkSphereSource;
import vtk.vtkXMLPolyDataReader;
import vtk.vtkActorCollection;
import vtk.vtkAppendPolyData;
import vtk.vtkLODActor;

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
    private double[] defaultMarkerColor = new double[]{0.0, 0.0, 1.0};
    
    private double defaultMuscleRadius = .005;
    // Maps between objects and vtkProp3D for going from Actor to Object and vice versa
    // Objects are mapped to vtkProp3D in general, but some are known to be assemblies
    // e.g. Muscles, Models
    private Hashtable<OpenSimObject, vtkProp3D> mapObject2VtkObjects = new Hashtable<OpenSimObject, vtkProp3D>();
    private Hashtable<vtkProp3D, OpenSimObject> mapVtkObjects2Objects = new Hashtable<vtkProp3D, OpenSimObject>(50);
    
    private Hashtable<OpenSimObject, Vector<Integer>> mapObject2GlyphIds = new
            Hashtable<OpenSimObject, Vector<Integer>>();

    private Hashtable<OpenSimObject, Integer> mapMarkers2Glyphs = new Hashtable<OpenSimObject, Integer>(50);
    private Hashtable<OpenSimObject, Integer> mapMusclePoints2Glyphs = new Hashtable<OpenSimObject, Integer>(50);
    
    // Markers and muscle points are represented as Glyphs for performance
    OpenSimvtkGlyphCloud  markersRep=new OpenSimvtkGlyphCloud();
    OpenSimvtkGlyphCloud  musclePointsRep=new OpenSimvtkGlyphCloud();
    OpenSimvtkOrientedGlyphCloud  muscleSegmentsRep = new OpenSimvtkOrientedGlyphCloud();
    
    private vtkProp3DCollection    userObjects = new vtkProp3DCollection();
    /**
     * Creates a new instance of SingleModelVisuals
     */
    public SingleModelVisuals(AbstractModel aModel) {
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
    /**
     * Create one vtkAssembly representing the model and return it.
     */
    protected vtkAssembly createModelAssembly(AbstractModel model)
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
                String boneFile = modelFilePath + "bones\\"+bodyDisplayer.getGeometryFileName(k);
                polyReader.SetFileName(boneFile);

                vtkPolyData poly = polyReader.GetOutput();
                // Create polyData and append it to one common polyData object
                bodyPolyData.AddInput(poly);
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
                if (owner.getType().equals("SimmMarker")){
                    // Convert marker pos to global pos.
                    double[] pos = new double[3];
                    double[] gPos = new double[3];
                    Dependent.getTransform().getPosition(pos);
                    // xfrom to ground frame
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index= markersRep.addLocation(gPos);
                    mapMarkers2Glyphs.put(owner, new Integer(index));
                    continue;
                }
                else if (owner.getType().equals("SimmMusclePoint")||
                        owner.getType().equals("SimmMuscleViaPoint")){
                    double[] pos = new double[3];
                    double[] gPos = new double[3];
                    Dependent.getTransform().getPosition(pos);
                    // xfrom to ground frame
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index= musclePointsRep.addLocation(gPos);
                    mapMusclePoints2Glyphs.put(owner, new Integer(index));
                    continue;
                }
                /** unused but may be restored later 4 wrap objects
                vtkActor attachmentRep = new vtkLODActor();
                attachmentRep.SetUserMatrix(m);
                int geomcount = Dependent.countGeometry();
                // Create actor for the dpendent
                for(int gc=0; gc<geomcount; gc++){
                    Geometry g = Dependent.getGeometry(gc);
                    //vtkActor dActor = new vtkActor();
                    AnalyticGeometry ag=null;
                    ag = AnalyticGeometry.dynamic_cast(g);
                    if (ag != null){    
                        Geometry.GeometryType analyticType = ag.getShape();
                        if (analyticType == Geometry.GeometryType.Sphere){
                            vtkSphereSource sphere = new vtkSphereSource();
                            sphere.SetRadius(ag.getSphereRadius());
                            double[] pos = new double[3];
                            Dependent.getTransform().getPosition(pos);
                            //linePoints.InsertPoint(pointCount++,
                            //        pos[0], pos[1], pos[2]);
                            sphere.SetCenter(pos);
                            vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                            mapper.SetInput(sphere.GetOutput());

                            Dependent.getVisibleProperties().getColor(color);
                            attachmentRep.GetProperty().SetColor(color);

                            attachmentRep.SetMapper(mapper);
                            //attachmentRep.AddPart(dActor);
                            mapVtkObjects2Objects.put(attachmentRep, Dependent.getOwner());
                        }
                    }
                    else {  // General geometry
                        // throw an exception for not implemented though should be identical
                        throw new UnsupportedOperationException(
                                "Single Model Visuals: Geometry visualization Not yet implemented");                    }
                }
                //modelAssembly.AddPart(markersActor);
                modelAssembly.AddPart(attachmentRep);
                mapObject2VtkObjects.put(Dependent.getOwner(), attachmentRep);
                 */
            }
        } //body
        modelAssembly.AddPart(markersRep.getVtkActor());
        modelAssembly.AddPart(musclePointsRep.getVtkActor());
        markersRep.setModified();
        musclePointsRep.setModified();

        /**
         * Now the muscles and other actuators
         */
        addActuatorsGeometry(model, modelAssembly);
        mapObject2VtkObjects.put(model, modelAssembly);
        mapVtkObjects2Objects.put(modelAssembly, model);
        // Postprocess model assembly
        // Draw a box around the model, uncomment for debugging purposes
        /*
        vtkActor bboxActor = new vtkActor();
        vtkCubeSource bboxSource = new vtkCubeSource();
        bboxSource.SetBounds(modelAssembly.GetBounds());
        vtkPolyDataMapper bboxMapper = new vtkPolyDataMapper();
        bboxMapper.SetInput(bboxSource.GetOutput());
        bboxActor.SetMapper(bboxMapper);
        modelAssembly.AddPart(bboxActor);
        bboxActor.GetProperty().SetRepresentationToWireframe();
        */
        return modelAssembly;
    }
    
     /**
      * Get the vtkTransform matrix between ground and a body frame,
      * There could be a more efficient way to do that than xform a frame
      * at body origin.
      */
     vtkMatrix4x4 getBodyTransform(AbstractModel model, AbstractBody body)
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
    private void addActuatorsGeometry(AbstractModel  mdl, vtkAssembly modelAssembly) {
        // Now the muscles which are different creatures since they don't have a frame of their own
        // We'll display them by asking the "actuators for their geometry which may contain 
        // muscle points as well as segments connecting them
        ActuatorSet acts = mdl.getActuatorSet();
        for(int actNumber=0; actNumber < acts.getSize(); actNumber++){   
            AbstractActuator nextMuscle = acts.get(actNumber);
            Vector<Integer>   glyphIds = new Vector<Integer>(3);
            // Get attachments and connect them
            VisibleObject actuatorDisplayer = nextMuscle.getDisplayer();
            if (actuatorDisplayer == null){
                continue;
            }
            // A displayer is found, get geometry
            int geomSize = actuatorDisplayer.countGeometry();
            if (geomSize > 0){
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
                    vtkMatrix4x4 xform = getCylinderTransform(axis, center) ;
                    
                    int idx = muscleSegmentsRep.addLocation(center[0], center[1], center[2]);
                    muscleSegmentsRep.setTensorDataAtPoint(idx, 
                            xform.GetElement(0, 0), xform.GetElement(1, 0), xform.GetElement(2, 0),
                            length*xform.GetElement(0, 1), length*xform.GetElement(1, 1), length*xform.GetElement(2, 1),
                            xform.GetElement(0, 2), xform.GetElement(1, 2), xform.GetElement(2, 2)
                            );
                    glyphIds.add(new Integer(idx));
                } // Attachments
                mapObject2GlyphIds.put(nextMuscle, glyphIds);
            } // ArraySize
        }
        modelAssembly.AddPart(muscleSegmentsRep.getVtkActor());
        muscleSegmentsRep.setModified();
    }
    /**
     * Get the transform that takes a unit cylinder aligned with Y axis to a cylnder connecting 2 points
     */
    private vtkMatrix4x4 getCylinderTransform(double[] axis, double[] origin) {
       double length = normalizeAndGetLength(axis);
       vtkMatrix4x4 retTransform = new vtkMatrix4x4();
        // yaxis is the unit vector
        for (int i=0; i < 3; i++)
            retTransform.SetElement(i, 1, axis[i]);
        double[] newX = new double[3];
        double[] oldXCrossNewY = new double[3]; // NewZ
        oldXCrossNewY[0] = 0.0;
        oldXCrossNewY[1] = -axis[2];
        oldXCrossNewY[2] = axis[1];
        
        normalizeAndGetLength(oldXCrossNewY);
        for (int i=0; i < 3; i++)
            retTransform.SetElement(i, 2, oldXCrossNewY[i]);

        newX[0] = axis[1]*oldXCrossNewY[2]-axis[2]*oldXCrossNewY[1];
        newX[1] = axis[2]*oldXCrossNewY[0]-axis[0]*oldXCrossNewY[2];
        newX[2] = axis[0]*oldXCrossNewY[1]-axis[1]*oldXCrossNewY[0];
        normalizeAndGetLength(newX);
       for (int i=0; i < 3; i++){
            retTransform.SetElement(i, 0, newX[i]);
        // Scale by length
                retTransform.SetElement(i, 1, retTransform.GetElement(i, 1));
          retTransform.SetElement(i, 3, origin[i]);
         }
        return retTransform;
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
   public void updateModelDisplay(SimtkAnimationCallback animationCallback) {
      // Cycle thru bodies and update their transforms from the kinematics engine
        //animationCallback.mutex_begin(1);
        AbstractModel model = animationCallback.getModel();
        BodySet bodies = model.getDynamicsEngine().getBodySet();
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++){

            AbstractBody body = bodies.get(bodyNum);

            // Fill the maps between objects and display to support picking, highlighting, etc..
            // The reverse map takes an actor to an Object and is filled as actors are created.
            vtkProp3D bodyRep= mapObject2VtkObjects.get(body);
            Transform opensimTransform = animationCallback.getBodyTransform(bodyNum);
            vtkMatrix4x4 bodyVtkTransform = convertTransformToVtkMatrix4x4(opensimTransform);
            bodyRep.SetUserMatrix(bodyVtkTransform);
            // For dependents (markers, muscle points, update xforms as well)
            VisibleObject bodyDisplayer = body.getDisplayer();
            int ct = bodyDisplayer.countDependents();
            //System.out.println("Body "+body+" has "+ct+ " dependents");
            double[] color = new double[3];
            for(int j=0; j < ct;j++){
                VisibleObject dependent = bodyDisplayer.getDependent(j);
                vtkProp3D deptAssembly = mapObject2VtkObjects.get(dependent.getOwner());
                deptAssembly.SetUserMatrix(bodyVtkTransform);
            }
        }
        // Now the muscles
        updateActuatorsGeometry(model);
        //animationCallback.mutex_end(1);
   }
    /**
     * updateModelDisplay with new transforms cached in animationCallback.
     * This method must be optimized since it's invoked during live animation
     * of simulations and/or analyses (ala IK).
     */
   public void updateModelDisplay(AbstractModel model) {
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

                if (owner.getType().equals("SimmMarker")){
                    // Convert marker pos to global pos.
                    dependent.getTransform().getPosition(pos);
                    // xfrom to ground frame
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index = ((Integer)mapMarkers2Glyphs.get(owner)).intValue();
                    markersRep.setLocation(index, gPos[0], gPos[1], gPos[2]);
                    continue;
                }
                else if (owner.getType().equals("SimmMusclePoint")||
                        owner.getType().equals("SimmMuscleViaPoint")){
                    dependent.getTransform().getPosition(pos);
                    // xfrom to ground frame
                    model.getDynamicsEngine().transformPosition(body, pos, gPos);
                    int index = ((Integer)mapMusclePoints2Glyphs.get(owner)).intValue();
                    musclePointsRep.setLocation(index, gPos[0], gPos[1], gPos[2]);
                    continue;
                }
                vtkProp3D deptAssembly = mapObject2VtkObjects.get(dependent.getOwner());
                deptAssembly.SetUserMatrix(bodyVtkTransform);
            }
            
        }
        // Now the muscles
        updateActuatorsGeometry(model);
        //animationCallback.mutex_end(1);
        markersRep.setModified();
        musclePointsRep.setModified();
        updateUserObjects();
   }
   /**
    * Utility to convert Transform as defined by OpenSim to the form used by vtk
    */
   private vtkMatrix4x4 convertTransformToVtkMatrix4x4(Transform xform) {
      double[] xformAsVector= new double[16];
      xform.getMatrix(xformAsVector);
      vtkMatrix4x4 m = new vtkMatrix4x4();    // This should be moved out for performance
      // Set the rotation part
      for (int row = 0; row < 3; row++){
          for (int col = 0; col < 3; col++){
              m.SetElement(row, col, xformAsVector[row*4+col]);
          }
      }
      // Set last row of the matrix to translation.
      for (int col = 0; col < 3; col++)
          m.SetElement(3, col, xformAsVector[12+col]);

      // Transpose the matrix per Pete!!
      m.Transpose();
      return m;
   }
   /**
    * Update display of muscles and forces if any during playing back animation/motion, ..
    */
   private void updateActuatorsGeometry(AbstractModel mdl) {
      ActuatorSet acts = mdl.getActuatorSet();
      double[] axis = new double[]{0.0, 0.0, 0.0};
      double[] center = new double[]{0.0, 0.0, 0.0};
      for(int actNumber=0; actNumber < acts.getSize(); actNumber++){
         AbstractActuator nextMuscle = acts.get(actNumber);
         nextMuscle.updateGeometry();
         // Get attachments and connect them
         VisibleObject actuatorDisplayer = nextMuscle.getDisplayer();
         if (actuatorDisplayer == null){
            continue;
         }
         
         // A displayer is found, get geometry
         int geomSize = actuatorDisplayer.countGeometry();
         Vector<Integer> glyphIds = mapObject2GlyphIds.get(nextMuscle);
         
         int origGeomSize = glyphIds.size();
         if (geomSize>origGeomSize){   // Make extra segments and attach them 
            // Create new segments with ids and add them. 
            int idx = muscleSegmentsRep.addLocation(0.0, 0.0, 0.0);
            glyphIds.add(idx);
         }
         else if (origGeomSize>geomSize){ // remove unused segments
            int segmentsToRemove = origGeomSize-geomSize;
            for(int i=segmentsToRemove-1; i>=0; i--){
               muscleSegmentsRep.remove(glyphIds.get(i).intValue());
               glyphIds.remove(i);
            }
         }
         double[] position1 = new double[3];
         double[] position2 = new double[3];
         if (geomSize > 0){
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
              vtkMatrix4x4 xform = getCylinderTransform(axis, center) ;
              int idx = glyphIds.get(i).intValue();
              muscleSegmentsRep.setPoint(idx, center[0], center[1], center[2]);
              muscleSegmentsRep.setTensorDataAtPoint(idx, 
                      xform.GetElement(0, 0), xform.GetElement(1, 0), xform.GetElement(2, 0),
                      length*xform.GetElement(0, 1), length*xform.GetElement(1, 1), length*xform.GetElement(2, 1),
                      xform.GetElement(0, 2), xform.GetElement(1, 2), xform.GetElement(2, 2)
                      );
              muscleSegmentsRep.setModified();
            } // Attachments
         } // ArraySize        
      }
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
       markersRep.setColor(defaultMarkerColor);
       markersRep.setShape(marker.GetOutput());
       // MusclePoints
       vtkSphereSource viaPoint=new vtkSphereSource();
       viaPoint.SetRadius(defaultMuscleRadius);
       viaPoint.SetCenter(0., 0., 0.);
       musclePointsRep.setColor(defaultMuscleColor);
       musclePointsRep.setShape(viaPoint.GetOutput());
       
       vtkCylinderSource muscleSegment=new vtkCylinderSource();
       muscleSegment.SetRadius(defaultMuscleRadius);
       muscleSegment.SetHeight(1.0);
       muscleSegment.SetCenter(0.0, 0.0, 0.0);
       muscleSegment.CappingOff();
       
       muscleSegmentsRep.setColor(defaultMuscleColor);
       muscleSegmentsRep.setShape(muscleSegment.GetOutput());
       
       
     }
   
}
