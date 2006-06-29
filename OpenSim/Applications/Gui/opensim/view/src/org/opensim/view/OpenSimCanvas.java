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
import javax.swing.Action;
import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import java.io.File;
import java.util.Stack;
import javax.swing.JPopupMenu;
import org.opensim.modeling.OpenSimObject;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmBone;
import org.opensim.modeling.SimmJoint;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;
import org.opensim.view.base.OpenSimBaseCanvas;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkMatrix4x4;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProp3D;
import vtk.vtkPropPicker;
import vtk.vtkXMLPolyDataReader;

/**
 *
 * @author Ayman, based on Kenny Smith's Canvas3DVtk and earlier incarnations
 * A wrapper around vtkPanel that provides common behavior 
 */
public class OpenSimCanvas extends OpenSimBaseCanvas {
    
    SimmModel model;
    
    Hashtable<OpenSimObject, vtkAssembly> mapObject2Actors = new Hashtable<OpenSimObject, vtkAssembly>();
    Hashtable<vtkProp3D, OpenSimObject> mapActors2Objects = new Hashtable<vtkProp3D, OpenSimObject>();
    
    JPopupMenu visibilityMenu = new JPopupMenu();
    
    /** Creates a new instance of OpenSimCanvas */
    public OpenSimCanvas() {
    }
    
    /**
     * Function to load a SimmModel into a vtk Canvas. 
     */
    public boolean loadModel(final SimmModel model)
    {
        final ProgressHandle progressHandle = ProgressHandleFactory.createHandle("Building scene ");
        progressHandle.start();
        
        // DialogDisplayer.getDefault().notify(
        //        new NotifyDescriptor.Message("Click OK to continue."));
        
        // Build the scene graph in a worker thread.
        final SwingWorker worker = new SwingWorker() {
            
            public Object construct() { // runs in a worker thread
                
                boolean success = false;

                Stack<vtkAssembly> stack = new Stack<vtkAssembly>();

                File modelFile = new File(model.getInputFileName());
                String modelFilePath = modelFile.getParent() + modelFile.separator;

                // Traverse the bodies of the simmModel in depth-first order.
                SimmModelIterator i = new SimmModelIterator(model);

                while (i.getNextBody() != null) {

                    SimmBody body = i.getCurrentBody();

                    // Pop any stale entries off of our stack.
                    int depth = i.getNumAncestors();

                    while (stack.size() > depth)
                        stack.pop();

                    // Add a vtkAssembly to the vtk scene graph to represent
                    // the current body.
                    vtkAssembly bodyRep = new vtkAssembly();

                    // Fill the two maps between objects and actors to support picking, highlighting, etc..
                    mapObject2Actors.put(body, bodyRep);
                    
                    if (stack.size() > 0)
                        stack.peek().AddPart(bodyRep);
                    else
                        GetRenderer().AddViewProp(bodyRep); // used to be AddProp, but VTK 5 complains.

                    stack.push(bodyRep);

                    // Set the bodyRep's transform.
                    SimmJoint joint = i.getCurrentJoint();

                    if (joint != null) {
                        double[] jointXform = new double[16];
                        joint.getForwardTransform().getMatrix(jointXform);

                        vtkMatrix4x4 m = new vtkMatrix4x4();
                        for (int row = 0; row < 4; row++)
                            for (int col = 0; col < 4; col++){
                                m.SetElement(col, row, jointXform[row*4+col]);
                            }

                        bodyRep.SetUserMatrix(m);
                    }

                    // Add a vtkActor object to the vtk scene graph to represent
                    // each bone in the current body.
                    for (int k = 0; k < body.getNumBones(); ++k) {

                        SimmBone bone = body.getBone(k);

                        for (int l = 0; l < bone.getNumGeometryFiles(); ++l) {

                            // Get the native vtkPolyData object from the OpenSim
                            // model, and wrap a Java vtkPolyData object around it
                            // for use by VTK.
                            progressHandle.progress(bone.getGeometryFileName(l));
                            
                            vtkXMLPolyDataReader polyReader = new vtkXMLPolyDataReader();
                            String boneFile = modelFilePath + bone.getGeometryFileName(l);
                            polyReader.SetFileName(boneFile);

                            vtkPolyData poly = polyReader.GetOutput();
                            vtkPolyDataMapper mapper = new vtkPolyDataMapper();
                            mapper.SetInput(poly);

                            vtkActor actor = new vtkActor();
                            actor.SetMapper(mapper);
                            bodyRep.AddPart(actor);
                            mapActors2Objects.put(actor, body);

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
          OpenSimObject selectedObject = findObjectAt(lastX, lastY);
          if (selectedObject != null){
            JPopupMenu visPopup = new JPopupMenu();
            visPopup.add(new ModifyObjectVisibilityAction(selectedObject, this));
            visPopup.show(this, e.getX(), e.getY());
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
    
}
