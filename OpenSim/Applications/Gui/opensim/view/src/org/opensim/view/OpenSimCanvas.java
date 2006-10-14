/*
 * OpenSimCanvas.java
 *
 * Created on June 14, 2006, 11:58 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import javax.swing.SwingUtilities;
import java.util.Hashtable;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import java.io.File;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JPopupMenu;
import org.openide.awt.StatusDisplayer;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.AnalyticGeometry.AnalyticGeometryType;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.Model;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmBodySet;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmMuscle;
import org.opensim.modeling.SimmMusclePoint;
import org.opensim.modeling.SimmMusclePointSet;
import org.opensim.modeling.SimtkAnimationCallback;
import org.opensim.modeling.Transform;
import org.opensim.modeling.VisibleObject;
import org.opensim.swingui.SwingWorker;
import org.opensim.view.base.OpenSimBaseCanvas;
import org.opensim.view.editors.ObjectEditDialogMaker;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkCylinderSource;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkProp3DCollection;
import vtk.vtkPropPicker;
import vtk.vtkProperty;
import vtk.vtkSphereSource;
import vtk.vtkXMLPolyDataReader;

/**
 *
 * @author Ayman Habib, based on Kenny Smith's Canvas3DVtk and earlier incarnations
 * A wrapper around vtkPanel that provides common behavior beyond OpenSimBaseCanvas
 */
public class OpenSimCanvas extends OpenSimBaseCanvas {
    
    private SimmModel model;
    
    Hashtable<OpenSimObject, vtkAssembly> mapObject2Actors = new Hashtable<OpenSimObject, vtkAssembly>();
    Hashtable<vtkProp3D, OpenSimObject> mapActors2Objects = new Hashtable<vtkProp3D, OpenSimObject>();
    // A kluge to keep handles to muscle segments that are not full objects
    Hashtable<String, vtkActor> mapObjectsSegments2Actors = new Hashtable<String, vtkActor>();
    
    JPopupMenu visibilityMenu = new JPopupMenu();
    
    private OpenSimObject selectedObject=null;
    private ModelWindowVTKTopComponent ownerTopComponent=null;
    
    /** Creates a new instance of OpenSimCanvas */
    public OpenSimCanvas() {
    }
    /**
     * Ideally I pass the ownerTopComponent in constructor but that messes up the GUI editor
     * in netbeans, so the call is broken into two that MUST be called in sequence.
     * @Fixme
     */
    public void setOwnerWindow(ModelWindowVTKTopComponent ownerTopComponent)
    {
         this.ownerTopComponent=ownerTopComponent;       
    }
    /**
     * Function to load a SimmModel into a vtk Canvas. 
     */
    public boolean loadModel(final SimmModel model, Boolean waitForCompletion)
    {
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Building scene ");
        progressHandle.start();
        this.model = model;
        
        // Build the scene graph in a worker thread.
        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                
                boolean success = false;
                double[] scales = new double[3];
                //Stack<vtkAssembly> stack = new Stack<vtkAssembly>();

                File modelFile = new File(model.getInputFileName());
                String modelFilePath = "";
                if (modelFile.getParent()!= null)
                    modelFilePath= modelFile.getParent()+ modelFile.separator; // Could this be null?

                //vtkAssembly fullModelAssembly = new vtkAssembly();
                // Traverse the bodies of the simmModel in depth-first order.
                //SimmModelIterator i = new SimmModelIterator(model);
                // Keep track of ground body to avoid recomputation
                SimmBody gnd = model.getSimmKinematicsEngine().getGroundBodyPtr();
                for(int i=0; i < model.getNB(); i++){

                    SimmBody body = model.getSimmKinematicsEngine().getBodies().get(i);
                    
                    // Add a vtkAssembly to the vtk scene graph to represent
                    // the current body.
                    vtkAssembly bodyRep = new vtkAssembly();
                    
                    // Fill the maps between objects and display to support picking, highlighting, etc..
                    // The reverse map takes an actor to an Object and is filled as actors are created.
                    mapObject2Actors.put(body, bodyRep);
                    
                    GetRenderer().AddViewProp(bodyRep); // used to be AddProp, but VTK 5 complains.

                    vtkMatrix4x4 m= getBodyTransform(model, body, gnd);
                    bodyRep.SetUserMatrix(m);

                    // Add a vtkActor object to the vtk scene graph to represent
                    VisibleObject bodyDisplayer = body.getDisplayer();
                    bodyDisplayer.getScaleFactors(scales);

                    //System.out.println("Scale factors"+scales[0]+scales[1]+scales[2]);
                    int ns = bodyDisplayer.getNumGeometryFiles();
                    // For each bone in the current body.
                    for (int k = 0; k < bodyDisplayer.getNumGeometryFiles(); ++k) {
                        // Get the native vtkPolyData object from the OpenSim
                        // model, and wrap a Java vtkPolyData object around it
                        // for use by VTK.
                        progressHandle.progress(bodyDisplayer.getGeometryFileName(k));

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
                                AnalyticGeometryType analyticType = ag.getShape();
                                if (analyticType == AnalyticGeometryType.Sphere){
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
                            }
                        }
                        GetRenderer().AddViewProp(attachmentRep); 
                        mapObject2Actors.put(Dependent.getOwner(), attachmentRep);
                    }
                } //body
                // Now the muscles which are different creatures since they don't have a frame of their own
                // We'll just connect the "musclepoints" in gnd frame to make up the muscle.
                // @FIXME handle non-muscle actuators
                int numMuscles = model.getNA();
                for(int m=0; m < numMuscles; m++){   
                    SimmMuscle nextMuscle = model.getMuscle(m);
                    // Create assembly for muscle
                    vtkAssembly muscleRep = new vtkAssembly();
                    
                    // Fill the object to display map
                    mapObject2Actors.put(nextMuscle, muscleRep);
                    
                    // Get attachments and connect them
                    SimmMusclePointSet attatchments = nextMuscle.getAttachmentSet();
                    int arraySize = attatchments.getSize();
                    if (arraySize > 0){
                        // Points must be traxformed to gnd frame as they generally live
                        // on diferent bodies
                        SimmMusclePoint firstPoint = attatchments.get(0);
                        SimmBody body = firstPoint.getBody();
                        double[] position1 = new double[3];
                        double[] position2 = new double[3];
                        for(int p=0; p <3; p++){
                            position1[p]=firstPoint.getAttachment().getitem(p);
                        }
                        model.getSimmKinematicsEngine().convertPoint(position1, body, gnd);
                        for (int att=1; att < arraySize; att++){
                             SimmMusclePoint curPoint = attatchments.get(att);
                             for(int p=0; p <3; p++){
                                position2[p]=curPoint.getAttachment().getitem(p);
                             }
                             SimmBody curBody = curPoint.getBody();
                             model.getSimmKinematicsEngine().convertPoint(position2, curBody, gnd);
                            double[] axis = new double[3];
                            double[] center = new double[3];
                            for(int d=0; d <3; d++){
                                axis[d]=position1[d]-position2[d];
                                center[d] = (position1[d]+position2[d])/2.0;
                            }
                            double length = normalizeAndGetLength(axis);
                            // Create a cylinder connecting position1, position2
                            // We should obtain this from the muscle so that shape,size and color are customizable
                            vtkCylinderSource cylinder = new vtkCylinderSource();
                            cylinder.SetRadius(.005);
                            cylinder.SetHeight(length);
                            cylinder.CappingOff();
                            vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                            mapper.SetInput(cylinder.GetOutput());
                            vtkActor dActor = new vtkActor();
                            dActor.GetProperty().SetColor(0.8, 0.1, 0.1);
                            dActor.SetUserMatrix(getCylinderTransform(axis, center));
                            dActor.SetMapper(mapper);
                            muscleRep.AddPart(dActor);
                            // Fill the display to object map
                            mapActors2Objects.put(dActor, nextMuscle);
                            String muscleSegname = nextMuscle.getName()+String.valueOf(att-1)+String.valueOf(att);
                            mapObjectsSegments2Actors.put(muscleSegname, dActor);
                            // Move position1 to the next point
                            for(int d=0; d <3; d++)
                                position1[d]=position2[d];
                        } // Attachments
                    } // ArraySize
                    GetRenderer().AddViewProp(muscleRep); 
                }
                return this;
            }
            public void finished() {
               GetRenderer().ResetCamera(); 
               Render();               
               progressHandle.finish();
            }
        };
        worker.start();
        return true;
    }
    /**
     * Method called in the animation loop to update positions with new xforms
     * Here, the xforms are obtained from the dynamcis engine and so 
     *
     */
    public void updateDisplayFromDynamicModel(SimtkAnimationCallback animationCallback, Boolean useSimmModel)
    {
        System.out.println("Got useSimmModel = " + useSimmModel);
        
          Model dModel = animationCallback.getModel();
         int nb = dModel.getNB();
         double[] xformMatrix = new double[16];
         animationCallback.getMutex();
         for(int bodyNum=0; bodyNum<nb; bodyNum++) {
            Transform bodyTransform = animationCallback.getBodyTransform(bodyNum); 
            SimmBodySet vModelBodies = model.getBodies();
            String bName = dModel.getBodyName(bodyNum);
            SimmBody vBody = vModelBodies.get(bName);
            
            vtkAssembly bodyRep = mapObject2Actors.get(vBody);
            // Make  matrix from xlation, rotations
            bodyTransform.getMatrix(xformMatrix);
            vtkMatrix4x4 m = new vtkMatrix4x4();
            m.DeepCopy(xformMatrix);
            m.Transpose();
            // Move translation to last column instead of last row
            if (bodyRep != null){   // Some bodies do not have a rep.
                bodyRep.SetUserMatrix(m);
            }
            
            // Bodies have things attached to them as handled by the
            // dependents mechanism. For each one of these a new assembly is created and attached 
            // to the same xform as the owner body.
            // this takes care of markers and musclepoints
            int ct = vBody.getDisplayer().countDependents();
            for(int j=0; j < ct;j++){
                VisibleObject Dependent = vBody.getDisplayer().getDependent(j);
                vtkAssembly attachmentRep = mapObject2Actors.get(Dependent.getOwner());
                attachmentRep.SetUserMatrix(m);
            } 
        } //body
        
        // Now the muscles
        int numMuscles = model.getNA();
        /*
        for(int m=0; m < numMuscles; m++){   
            SimmMuscle nextMuscle = model.getMuscle(m);
            // Get muscle rep
            vtkAssembly muscleRep = mapObject2Actors.get(nextMuscle);
            
            // Get attachments and connect them
            SimmMusclePointSet attatchments = nextMuscle.getAttachmentSet();
            int arraySize = attatchments.getSize();
            double[] position1InOwenerBody = new double[4];
            if (arraySize > 0){
                SimmMusclePoint firstPoint = attatchments.get(0);
                SimmBody pointBody = firstPoint.getBody();
                int pointBodyIndex = model.getBodyIndex(pointBody.getName());
                // get location of position1 in inertial frame
                double[] position1InOwnerBody = new double[4];
                double[] position1InWorld = new double[4];
                for(int i=0; i<3; i++)
                    position1InOwnerBody[i] = firstPoint.getAttachment().getitem(i);
                
                // xform the position into inertial frame
                Transform bodyTransform = animationCallback.getBodyTransform(pointBodyIndex); 
                bodyTransform.getMatrix(xformMatrix);
                vtkMatrix4x4 m1 = new vtkMatrix4x4();
                m1.DeepCopy(xformMatrix);
                // Move translation to last column instead of last row
                m1.Transpose();
                // m1 works because it gets applied to the body
                position1InOwnerBody[3]=1.0;
                m1.MultiplyPoint(position1InOwnerBody, position1InWorld);
                //debugLocation(position1InWorld);
                double[] position2InOwnerBody = new double[4];
                double[] position2InWorld = new double[4];

                for (int att=1; att < arraySize; att++){
                     String muscleSegname = nextMuscle.getName()+String.valueOf(att-1)+String.valueOf(att);
                     vtkActor segActor = mapObjectsSegments2Actors.get(muscleSegname);
                     SimmMusclePoint curPoint = attatchments.get(att);
                     SimmBody point2Body = curPoint.getBody();
                     int point2BodyIndex = model.getBodyIndex(point2Body.getName());
                     
                    double[] axis = new double[3];
                    double[] center = new double[3];
                    for(int i=0; i<3; i++)
                        position2InOwnerBody[i] = curPoint.getAttachment().getitem(i);
                    
                    Transform body2Transform = animationCallback.getBodyTransform(point2BodyIndex); 
                    body2Transform.getMatrix(xformMatrix);
                    vtkMatrix4x4 m2 = new vtkMatrix4x4();
                    m2.DeepCopy(xformMatrix);
                    // Move translation to last column instead of last row
                    m2.Transpose();
                   // m1 works because it gets applied to the body
                    position2InOwnerBody[3]=1.0;
                    m2.MultiplyPoint(position2InOwnerBody, position2InWorld);
                    //debugLocation(position2InWorld);

                    for(int d=0; d <3; d++){
                        axis[d]=position1InWorld[d]-position2InWorld[d];
                        center[d] = (position1InWorld[d]+position2InWorld[d])/2.0;
                    }
                    double length = normalizeAndGetLength(axis);
                    // Compute new xform and apply it to segActor
                    segActor.SetUserMatrix(getCylinderTransform(axis, center));
                    
                    // Move position1 to the next point
                    for(int d=0; d <3; d++){
                       position1InWorld[d]=position2InWorld[d];
                    }
                } // Attachments

            }
            
        }

         */
        
        animationCallback.releaseMutex();
        repaint();
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
    
     /**
      * Get the vtkTransform matrix between ground and a body frame,
      * There could be a more efficient way to do that than xform a frame
      * at body origin.
      */
     vtkMatrix4x4 getBodyTransform(SimmModel model, SimmBody body, SimmBody gnd)
     {
                    double[][] originFrame = new double[][]{{1.0, 0.0, 0.0}, 
                                                            {0.0, 1.0, 0.0}, 
                                                            {0.0, 0.0, 1.0},
                                                            {0.0, 0.0, 0.0}};

                    model.getSimmKinematicsEngine().convertVector(originFrame[0], body, gnd);
                    model.getSimmKinematicsEngine().convertVector(originFrame[1], body, gnd);
                    model.getSimmKinematicsEngine().convertVector(originFrame[2], body, gnd);
                    model.getSimmKinematicsEngine().convertPoint(originFrame[3], body, gnd);

                    vtkMatrix4x4 m = new vtkMatrix4x4();    // This should be moved out for performance
                    // Set the rotation part
                    for (int row = 0; row < 3; row++){
                        for (int col = 0; col < 3; col++){
                            m.SetElement(row, col, originFrame[row][col]);
                        }
                    }
                    // Set last row of the matrix to translation.
                    for (int col = 0; col < 3; col++)
                        m.SetElement(3, col, originFrame[3][col]);
                    
                    // Transpose the matrix per Pete!!
                    m.Transpose();
                    return m;
     }
     
    public void mousePressed(MouseEvent e)
   {
       if ( (e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.CTRL_MASK))) {
          setSelectedObject(findObjectAt(lastX, lastY));
          //if (getSelectedObject() != null){
            //JPopupMenu visPopup = new JPopupMenu();
            //visPopup.add(new ModifyObjectVisibilityAction(getSelectedObject(), ownerTopComponent));
            //visPopup.show(this, e.getX(), e.getY());
         //}
        }        // Show popup if right mouse otherwise pass along to super implementation
        super.mousePressed(e);
    }
    
    OpenSimObject findObjectAt(int x, int y)
    {
        vtkPropPicker picker = new vtkPropPicker();

        Lock();
        picker.Pick(x, rw.GetSize()[1] - y, 0, ren);
        UnLock();

        vtkAssemblyPath asmPath = picker.GetPath();
        if (asmPath != null) {
         vtkAssemblyNode pickedAsm = asmPath.GetLastNode();
         return mapActors2Objects.get(pickedAsm.GetViewProp());
        }
        return null;
    }
    public vtkAssembly getActorForObject(OpenSimObject obj)
    {
        return mapObject2Actors.get(obj);
    }
    
    public OpenSimObject getObjectForActor(vtkAssembly prop)
    {
        return mapActors2Objects.get(prop);
    }

    public void setObjectColor(OpenSimObject object, double[] colorComponents) {
        vtkAssembly asm = getActorForObject(object);
        vtkProp3DCollection parts = asm.GetParts();
        parts.InitTraversal();
        vtkProp3D prop = parts.GetNextProp3D();
        vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
	while (prop != null) {
            if (part != null)
                part.GetProperty().SetColor(colorComponents);
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
        }
    }
    public void setObjectOpacity(OpenSimObject object, double newOpacity) {
        vtkAssembly asm = getActorForObject(object);
        vtkProp3DCollection parts = asm.GetParts();
        parts.InitTraversal();
        vtkProp3D prop = parts.GetNextProp3D();
        vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
	while (prop != null) {
            if (part != null)
                part.GetProperty().SetOpacity(newOpacity);
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
        }
    }

    public void getObjectProperties(OpenSimObject object, vtkProperty saveProperty) {
        vtkAssembly asm = getActorForObject(object);
        vtkProp3DCollection parts = asm.GetParts();
        parts.InitTraversal();
        vtkProp3D prop = parts.GetNextProp3D();
        vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
	while (prop != null) {
            if (part != null){
                saveProperty.SetColor(part.GetProperty().GetColor());
                saveProperty.SetOpacity(part.GetProperty().GetOpacity());
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
        }
    }
    public void setObjectProperties(OpenSimObject object, vtkProperty saveProperty) {
        setObjectColor(object, saveProperty.GetColor());
        setObjectOpacity(object, saveProperty.GetOpacity());
    }

    void handleDoubleClick(MouseEvent evt) {
          setSelectedObject(findObjectAt(lastX, lastY));
          if (selectedObject != null){
                /*EditObjectTopComponent win = EditObjectTopComponent.findInstance();
                win.setContext(this);
                win.open();
                win.requestActive();*/
              ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(selectedObject, ownerTopComponent);
               editorDialog.process();
              //new VisibilityJDialog(new javax.swing.JFrame(), this, getSelectedObject()).setVisible(true);
          }
          setSelectedObject(null);
    }

    void selectObject(MouseEvent evt) {
          setSelectedObject(findObjectAt(lastX, lastY));
    }
    /**
     * Toggle graphical feed back that an object is selected
     */
    public void markSelected(OpenSimObject selectedObject, boolean onOff) {
        vtkAssembly asm = getActorForObject(selectedObject);
        vtkProp3DCollection parts = asm.GetParts();
        parts.InitTraversal();
        vtkProp3D prop = parts.GetNextProp3D();
        vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
        while (prop != null) {
            if (part != null){
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
        }
        
     }

    public OpenSimObject getSelectedObject() {
        return selectedObject;
    }

    public void setSelectedObject(OpenSimObject selectedObject) {
        this.selectedObject = selectedObject;
        if (selectedObject != null){
            markSelected(selectedObject, true);
            //Node selectedNode = ownerTopComponent.getNodeFor(selectedObject);
            //ownerTopComponent.setActivatedNodes(new Node[] {selectedNode});
            StatusDisplayer.getDefault().setStatusText(selectedObject.getType()+", "+selectedObject.getName());
        }
        else
            StatusDisplayer.getDefault().setStatusText("");
    }

    public SimmModel getModel() {
        return model;
    }
    
    private void debugLocation(double[] propLocation) {
        vtkActor startPointActor = new vtkActor();
        vtkSphereSource sphere = new vtkSphereSource();
        sphere.SetRadius(0.03);
        sphere.SetCenter(propLocation);
        vtkPolyDataMapper mapper = new vtkPolyDataMapper();
        mapper.SetInput(sphere.GetOutput());
        startPointActor.SetMapper(mapper);
        startPointActor.GetProperty().SetColor(0., 1., 0.);
        startPointActor.GetProperty().SetOpacity(0.2);
        GetRenderer().AddViewProp(startPointActor); 
    }

}
