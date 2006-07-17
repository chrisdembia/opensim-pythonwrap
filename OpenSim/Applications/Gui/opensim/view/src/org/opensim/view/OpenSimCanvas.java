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
import java.util.Hashtable;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import java.io.File;
import javax.swing.JPopupMenu;
import org.opensim.modeling.AnalyticGeometry;
import org.opensim.modeling.AnalyticGeometry.AnalyticGeometryType;
import org.opensim.modeling.Geometry;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;
import org.opensim.modeling.VisibleObject;
import org.opensim.view.base.OpenSimBaseCanvas;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
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
 * @author Ayman, based on Kenny Smith's Canvas3DVtk and earlier incarnations
 * A wrapper around vtkPanel that provides common behavior 
 */
public class OpenSimCanvas extends OpenSimBaseCanvas {
    
    private SimmModel model;
    
    Hashtable<OpenSimObject, vtkAssembly> mapObject2Actors = new Hashtable<OpenSimObject, vtkAssembly>();
    Hashtable<vtkProp3D, OpenSimObject> mapActors2Objects = new Hashtable<vtkProp3D, OpenSimObject>();
    
    JPopupMenu visibilityMenu = new JPopupMenu();
    
    private OpenSimObject selectedObject=null;
    
    /** Creates a new instance of OpenSimCanvas */
    public OpenSimCanvas() {
    }
    
    public SimmModel getModel()
    {
        return model;
    }
    /**
     * Function to load a SimmModel into a vtk Canvas. 
     */
    public boolean loadModel(final SimmModel model)
    {
        setModel(model);
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Building scene ");
        progressHandle.start();
        
        // DialogDisplayer.getDefault().notify(
        //        new NotifyDescriptor.Message("Click OK to continue."));
        
        // Build the scene graph in a worker thread.
        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                
                boolean success = false;

                //Stack<vtkAssembly> stack = new Stack<vtkAssembly>();

                File modelFile = new File(model.getInputFileName());
                String modelFilePath = modelFile.getParent() + modelFile.separator; // Could this be null?

                // Traverse the bodies of the simmModel in depth-first order.
                SimmModelIterator i = new SimmModelIterator(model);

                SimmBody gnd = model.getSimmKinematicsEngine().getGroundBodyPtr();
                while (i.getNextBody() != null) {

                    SimmBody body = i.getCurrentBody();
                    
                    // Add a vtkAssembly to the vtk scene graph to represent
                    // the current body.
                    vtkAssembly bodyRep = new vtkAssembly();

                    // Fill the two maps between objects and actors to support picking, highlighting, etc..
                    mapObject2Actors.put(body, bodyRep);
                    
                    GetRenderer().AddViewProp(bodyRep); // used to be AddProp, but VTK 5 complains.

                    // Convert origin frame in currentBody to ground.
                    
                    double[][] originFrame = new double[][]{{1.0, 0.0, 0.0}, 
                                                            {0.0, 1.0, 0.0}, 
                                                            {0.0, 0.0, 1.0},
                                                            {0.0, 0.0, 0.0}};

                    model.getSimmKinematicsEngine().convertVector(originFrame[0], body, gnd);
                    model.getSimmKinematicsEngine().convertVector(originFrame[1], body, gnd);
                    model.getSimmKinematicsEngine().convertVector(originFrame[2], body, gnd);
                    model.getSimmKinematicsEngine().convertPoint(originFrame[3], body, gnd);

                    vtkMatrix4x4 m = new vtkMatrix4x4();
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
                    bodyRep.SetUserMatrix(m);

                    // Add a vtkActor object to the vtk scene graph to represent
                    VisibleObject bodyDisplayer = body.getDisplayer();
                    // each bone in the current body.
                    for (int k = 0; k < bodyDisplayer.getNumGeometryFiles(); ++k) {

                        // Get the native vtkPolyData object from the OpenSim
                        // model, and wrap a Java vtkPolyData object around it
                        // for use by VTK.
                        progressHandle.progress(bodyDisplayer.getGeometryFileName(k));

                        vtkXMLPolyDataReader polyReader = new vtkXMLPolyDataReader();
                        String boneFile = modelFilePath + bodyDisplayer.getGeometryFileName(k);
                        polyReader.SetFileName(boneFile);

                        vtkPolyData poly = polyReader.GetOutput();
                        vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                        mapper.SetInput(poly);

                        vtkActor actor = new vtkActor();
                        actor.SetMapper(mapper);
                        bodyRep.AddPart(actor);
                        mapActors2Objects.put(actor, body);

                        }
                    int ct = bodyDisplayer.countDependents();
                    System.out.println("Body "+body+" has "+ct+ " dependents");
                    for(int j=0; j < ct;j++){
                        VisibleObject Dependent = bodyDisplayer.getDependent(j);
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
                                    sphere.SetRadius(0.01);
                                    double[] pos = new double[3];
                                    System.out.println("Sphere for object "+Dependent.getOwner().getName()+
                                            " at"+pos[0]+", "+pos[1]+", "+pos[2]);
                                    Dependent.getTransform().getPosition(pos);
                                    sphere.SetCenter(pos);
                                    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                                    mapper.SetInput(sphere.GetOutput());
                                    dActor.GetProperty().SetColor(new double[]{1.0, 0.0, 0.0});
                                    dActor.SetMapper(mapper);
                                    bodyRep.AddPart(dActor);
                                    mapActors2Objects.put(dActor, Dependent.getOwner());
                                    GetRenderer().AddViewProp(dActor); 
                                }
                            }
                        }
                    }
                }
                 
                return this;
            }
            public void finished() {
               progressHandle.finish();
               Render();               
            }
        };
        worker.start();
        return true;
    }
    
    public void mousePressed(MouseEvent e)
   {
       if ( (e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.CTRL_MASK))) {
          setSelectedObject(findObjectAt(lastX, lastY));
          if (getSelectedObject() != null){
            //JPopupMenu visPopup = new JPopupMenu();
            //visPopup.add(new ModifyObjectVisibilityAction(getSelectedObject(), this));
            //visPopup.show(this, e.getX(), e.getY());
         }
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
    void setObjectOpacity(OpenSimObject object, double newOpacity) {
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

    void getObjectProperties(OpenSimObject object, vtkProperty saveProperty) {
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
    void setObjectProperties(OpenSimObject object, vtkProperty saveProperty) {
        setObjectColor(object, saveProperty.GetColor());
        setObjectOpacity(object, saveProperty.GetOpacity());
    }

    void handleDoubleClick(MouseEvent evt) {
          setSelectedObject(findObjectAt(lastX, lastY));
          if (getSelectedObject() != null){
                EditObjectTopComponent win = EditObjectTopComponent.findInstance();
                win.setContext(this);
                win.open();
                win.requestActive();
              //new VisibilityJDialog(new javax.swing.JFrame(), this, getSelectedObject()).setVisible(true);
          }
          setSelectedObject(null);
    }

    void selectObject(MouseEvent evt) {
          setSelectedObject(findObjectAt(lastX, lastY));
          if (getSelectedObject() != null)
            markSelected(getSelectedObject(), true);
    }

    private void markSelected(OpenSimObject selectedObject, boolean on) {
        vtkAssembly asm = getActorForObject(selectedObject);
        vtkProp3DCollection parts = asm.GetParts();
        parts.InitTraversal();
        vtkProp3D prop = parts.GetNextProp3D();
        vtkActor part = (prop instanceof vtkActor)?(vtkActor)prop:null;
	while (prop != null) {
            if (part != null){
                if (on){
                    part.GetProperty().EdgeVisibilityOn();
                }
                else
                    part.GetProperty().EdgeVisibilityOff();
            }
            prop = parts.GetNextProp3D();
            part = (prop instanceof vtkActor)?(vtkActor)prop:null;
        }
    }
    
    public void setModel(SimmModel model) {
        this.model = model;
}

    public OpenSimObject getSelectedObject() {
        return selectedObject;
    }

    public void setSelectedObject(OpenSimObject selectedObject) {
        this.selectedObject = selectedObject;
    }
}
