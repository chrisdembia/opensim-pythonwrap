/*
 * OpenSimCanvas.java
 *
 * Created on June 14, 2006, 11:58 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import org.netbeans.api.progress.ProgressHandle;
import org.netbeans.api.progress.ProgressHandleFactory;
import java.io.File;
import java.util.Stack;
import org.opensim.modeling.SimmBody;
import org.opensim.modeling.SimmBone;
import org.opensim.modeling.SimmJoint;
import org.opensim.modeling.SimmModel;
import org.opensim.modeling.SimmModelIterator;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkCamera;
import vtk.vtkMatrix4x4;
import vtk.vtkPanel;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkXMLPolyDataReader;

/**
 *
 * @author Ayman, based on Kenny Smith's Canvas3DVtk and earlier incarnations
 * A wrapper around vtkPanel that provides common behavior 
 */
public class OpenSimCanvas extends vtkPanel {
    
    SimmModel model;
    
    /** Creates a new instance of OpenSimCanvas */
    public OpenSimCanvas() {
         GetRenderer().SetBackground(0.2, 0.2, 1.0); 
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

                    // Print the body name (debug only).
                    // for (int j = 0; j < depth; ++j) System.out.print("  ");
                    // System.out.println(body.getName() + " (bones: " + body.getNumBones() + ")");

                    // Add a vtkAssembly to the vtk scene graph to represent
                    // the current body.
                    vtkAssembly assembly = new vtkAssembly();

                    if (stack.size() > 0)
                        stack.peek().AddPart(assembly);
                    else
                        GetRenderer().AddViewProp(assembly); // used to be AddProp, but VTK 5 complains.

                    stack.push(assembly);

                    // Set the assembly's transform.
                    SimmJoint joint = i.getCurrentJoint();

                    if (joint != null) {
                        double[] jointXform = new double[16];
                        joint.getForwardTransform().getMatrix(jointXform);

                        vtkMatrix4x4 m = new vtkMatrix4x4();
                        for (int row = 0; row < 4; row++)
                            for (int col = 0; col < 4; col++){
                                m.SetElement(col, row, jointXform[row*4+col]);
                            }

                        assembly.SetUserMatrix(m);
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
                            assembly.AddPart(actor);
                        }
                    }
                }
                 
                return this;
            }
            public void finished() {
                resetCamera();
                Render();
                progressHandle.finish();
            }
        };
        worker.start();
        return true;
    }
}
