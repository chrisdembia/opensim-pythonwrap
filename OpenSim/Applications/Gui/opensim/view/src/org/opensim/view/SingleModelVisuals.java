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
import org.opensim.modeling.AbstractActuator;
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractModel;
import org.opensim.modeling.ActuatorSet;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.BodySet;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.LineGeometry;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.Transform;
import org.opensim.modeling.VisibleObject;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkCubeSource;
import vtk.vtkCylinderSource;
import vtk.vtkLinearTransform;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkSphereSource;
import vtk.vtkXMLPolyDataReader;

/**
 *
 * @author Ayman. A class representing the visuals of one model.
 * This class does not actually display the model. Instead it builds the
 * data structures (vtkAssembly) needed to display the model and also
 * maintains the maps for finding an object based on selection and vice versa.
 */
public class SingleModelVisuals {
    
    private vtkAssembly modelDisplayAssembly;   // assembly representing the model
    private vtkLinearTransform modelDisplayTransform; // extra transform to shift, rotate model
    private double opacity;
    private double[] bounds = new double[6];    // bounding box around the model assembly, in assembly's frame'
    private boolean visible;
    
    // Maps between objects and vtkAssemblies for going from Actor to Object and vice versa
    private Hashtable<OpenSimObject, vtkAssembly> mapObject2Actors = new Hashtable<OpenSimObject, vtkAssembly>();
    private Hashtable<vtkProp3D, OpenSimObject> mapActors2Objects = new Hashtable<vtkProp3D, OpenSimObject>();
    /**
     * Creates a new instance of SingleModelVisuals
     */
    public SingleModelVisuals(AbstractModel aModel) {
        modelDisplayAssembly = createModelAssembly(aModel);
        computeModelBoundingbox();
        setVisible(true);
    }
    /**
     * Find the vtkActor for the passed in object
     */
    public vtkAssembly getActorForObject(OpenSimObject obj)
    {
        return mapObject2Actors.get(obj);
    }
    /**
     * find the Object for passed in actor
     */
    public OpenSimObject getObjectForActor(vtkAssembly prop)
    {
        return mapActors2Objects.get(prop);
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
        // Traverse the bodies of the simmModel in depth-first order.
        //SimmModelIterator i = new SimmModelIterator(model);
        // Keep track of ground body to avoid recomputation
        AbstractBody gnd = model.getDynamicsEngine().getGroundBody();
        BodySet bodies = model.getDynamicsEngine().getBodySet();
        for(int bodyNum=0; bodyNum<bodies.getSize();  bodyNum++){

            AbstractBody body = bodies.get(bodyNum);

            // Add a vtkAssembly to the vtk scene graph to represent
            // the current body.
            vtkAssembly bodyRep = new vtkAssembly();

            // Fill the maps between objects and display to support picking, highlighting, etc..
            // The reverse map takes an actor to an Object and is filled as actors are created.
            mapObject2Actors.put(body, bodyRep);

             modelAssembly.AddPart(bodyRep);
            vtkMatrix4x4 m= getBodyTransform(model, body);
            bodyRep.SetUserMatrix(m);

            // Add a vtkActor object to the vtk scene graph to represent
            VisibleObject bodyDisplayer = body.getDisplayer();
            bodyDisplayer.getScaleFactors(scales);

            int ns = bodyDisplayer.getNumGeometryFiles();
            // For each bone in the current body.
            for (int k = 0; k < bodyDisplayer.getNumGeometryFiles(); ++k) {
                vtkXMLPolyDataReader polyReader = new vtkXMLPolyDataReader();
                String boneFile = modelFilePath + "bones\\"+bodyDisplayer.getGeometryFileName(k);
                polyReader.SetFileName(boneFile);

                vtkPolyData poly = polyReader.GetOutput();
                vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                mapper.SetInput(poly);

                vtkActor actor = new vtkActor();
                actor.SetMapper(mapper);
                actor.SetScale(scales);
                bodyRep.AddPart(actor);
                mapActors2Objects.put(actor, body);

            }

            // Bodies have things attached to them as handled by the
            // dependents mechanism. For each one of these a new assembly is created and attached 
            // to the same xform as the owner body.
            int ct = bodyDisplayer.countDependents();
            //System.out.println("Body "+body+" has "+ct+ " dependents");
            double[] color = new double[3];
            for(int j=0; j < ct;j++){
                VisibleObject Dependent = bodyDisplayer.getDependent(j);
                vtkAssembly attachmentRep = new vtkAssembly();
                attachmentRep.SetUserMatrix(m);
                int geomcount = Dependent.countGeometry();
                // Create actor for the dpendent
                for(int gc=0; gc<geomcount; gc++){
                    Geometry g = Dependent.getGeometry(gc);
                    vtkActor dActor = new vtkActor();
                    AnalyticGeometry ag=null;
                    ag = AnalyticGeometry.dynamic_cast(g);
                    if (ag != null){    
                        Geometry.GeometryType analyticType = ag.getShape();
                        if (analyticType == Geometry.GeometryType.Sphere){
                            vtkSphereSource sphere = new vtkSphereSource();
                            sphere.SetRadius(ag.getSphereRadius());
                            double[] pos = new double[3];
                            Dependent.getTransform().getPosition(pos);
                            sphere.SetCenter(pos);
                            vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                            mapper.SetInput(sphere.GetOutput());

                            Dependent.getVisibleProperties().getColor(color);
                            dActor.GetProperty().SetColor(color);

                            dActor.SetMapper(mapper);
                            attachmentRep.AddPart(dActor);
                            mapActors2Objects.put(dActor, Dependent.getOwner());
                        }
                    }
                    else {  // General geometry
                        // throw an exception for not implemented though should be identical
                        throw new UnsupportedOperationException(
                                "Single Model Visuals: Geometry visualization Not yet implemented");                    }
                }
                modelAssembly.AddPart(attachmentRep);
                mapObject2Actors.put(Dependent.getOwner(), attachmentRep);
            }
        } //body
        /**
         * Now the muscles and other actuators
         */
        addActuatorsGeometry(model, modelAssembly);
        mapObject2Actors.put(model, modelAssembly);
        mapActors2Objects.put(modelAssembly, model);
        // Postprocess model assembly
        /* Draw a box around the model, for debugging purposes
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
     * return a reference to the vtkAssembly representing the model
     */
    public vtkAssembly getModelDisplayAssembly() {
        return modelDisplayAssembly;
    }
    
    public OpenSimObject pickObject(vtkAssemblyPath asmPath) {
        if (asmPath != null) {
         vtkAssemblyNode pickedAsm = asmPath.GetLastNode();
         return mapActors2Objects.get(pickedAsm.GetViewProp());
        }  
        return null;    // No selection
    }
    /**
     * Apply an offset to model display
     */
    public void addOffset(double[] offset) {
        
        modelDisplayAssembly.SetPosition(offset);
    }

    public vtkLinearTransform getModelDisplayTransform() {
        return modelDisplayTransform;
    }

    public void setModelDisplayTransform(vtkLinearTransform modelDisplayTransform) {
        this.modelDisplayTransform = modelDisplayTransform;
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

    public double[] getBounds() {
        return bounds;
    }
    /**
     * Compute bounding box for model as this can be useful for initial placement
     *  This is supposed to be a ballpark rather than an accurate estimate so that minor changes to
     * model do not cause overlap, but the bboox is not intended to be kept up-to-date
     */
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
        // muscle poitns as well as segments connecting them
        double[] defaultMuscleColor = new double[]{0.8, 0.1, 0.1};
        ActuatorSet acts = mdl.getActuatorSet();
        for(int actNumber=0; actNumber < acts.getSize(); actNumber++){   
            AbstractActuator nextMuscle = acts.get(actNumber);
            // Create assembly for muscle
            vtkAssembly muscleRep = new vtkAssembly();

            // Fill the object to display map
            mapObject2Actors.put(nextMuscle, muscleRep);

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
                    double length = normalizeAndGetLength(axis);
                    // Create a cylinder connecting position1, position2
                    // We should obtain this from the muscle so that shape,size and defaultMuscleColor are customizable
                    vtkCylinderSource cylinder = new vtkCylinderSource();
                    cylinder.SetRadius(.005);
                    cylinder.SetHeight(length);
                    cylinder.CappingOff();
                    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                    mapper.SetInput(cylinder.GetOutput());
                    vtkActor dActor = new vtkActor();
                    dActor.GetProperty().SetColor(defaultMuscleColor);
                    dActor.SetUserMatrix(getCylinderTransform(axis, center));
                    dActor.SetMapper(mapper);
                    muscleRep.AddPart(dActor);
                    // Fill the display to object map
                    mapActors2Objects.put(dActor, nextMuscle);
                } // Attachments
            } // ArraySize
            modelAssembly.AddPart(muscleRep); 
            //System.out.println("Processing muscle "+nextMuscle.getName());
        }
    }
    /**
     * Get the transform that takes a unit cylinder aligned with Y axis to a cylnder connecting 2 points
     */
    private vtkMatrix4x4 getCylinderTransform(double[] axis, double[] origin)
    {
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
        for (int i=0; i < 3; i++)
            retTransform.SetElement(i, 0, newX[i]);
        
        for (int i=0; i < 3; i++)
            retTransform.SetElement(i, 3, origin[i]);
        
        return retTransform;
    }
    /**
     * Normalize a vector and return its length
     */
    private double normalizeAndGetLength(double[] vector3)
    {
        double length = Math.sqrt(Math.pow(vector3[0], 2)+
                                  Math.pow(vector3[1], 2)+
                                  Math.pow(vector3[2], 2));
        // normalize
        for(int d=0; d <3; d++)
            vector3[d]=vector3[d]/length;
        return length;
    }
}
