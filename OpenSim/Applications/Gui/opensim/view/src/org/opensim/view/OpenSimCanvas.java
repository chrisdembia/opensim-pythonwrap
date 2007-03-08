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
import javax.swing.JPopupMenu;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.base.OpenSimBaseCanvas;
import org.opensim.view.editors.ObjectEditDialogMaker;
import org.opensim.view.pub.ViewDB;
import vtk.vtkAVIWriter;
import vtk.vtkAssembly;
import vtk.vtkAssemblyPath;
import vtk.vtkJPEGWriter;
import vtk.vtkMPEG2Writer;
import vtk.vtkPropPicker;
import vtk.vtkWindowToImageFilter;

/**
 *
 * @author Ayman Habib
 * A wrapper around vtkPanel that provides common behavior beyond OpenSimBaseCanvas.
 * 
 */
public class OpenSimCanvas extends OpenSimBaseCanvas {
        
    JPopupMenu visibilityMenu = new JPopupMenu();
    
    /** Creates a new instance of OpenSimCanvas */
    public OpenSimCanvas() {
    }
    /**
     * Event handler to handle mousePressed
     */
    public void mousePressed(MouseEvent e)
   {
       if ( (e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.CTRL_MASK))) {
          ViewDB.getInstance().setSelectedObject(findObjectAt(lastX, lastY));
        }        // Show popup if right mouse otherwise pass along to super implementation
        super.mousePressed(e);
    }
    /**
     *  Utility method to locate an OpenSimObject located atscreen coordinate  x, y.
     *  Delegates the call to modelVisuals
     */
    OpenSimObject findObjectAt(int x, int y)
    {
        vtkPropPicker picker = new vtkPropPicker();

        Lock();
        picker.Pick(x, rw.GetSize()[1] - y, 0, ren);
        UnLock();

        vtkAssemblyPath asmPath = picker.GetPath();
        return ViewDB.getInstance().pickObject(asmPath);
    }
     /**
     * Callback invoked when the user doubleclicks an object in the graphics window
     */
    void handleDoubleClick(MouseEvent evt) {
          ViewDB.getInstance().setSelectedObject(findObjectAt(lastX, lastY));
          OpenSimObject selectedObject = ViewDB.getInstance().getSelectedObject();
          if (selectedObject != null){
              ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(selectedObject, ViewDB.getInstance().getCurrenWindow());
               editorDialog.process();
          }
          ViewDB.getInstance().setSelectedObject(null);
    }

     void selectObject(MouseEvent evt) {
          ViewDB.getInstance().setSelectedObject(findObjectAt(lastX, lastY));
    }

    /*
    void addNewModelVisuals(SingleModelVisuals newModelVisual) {
        vtkAssembly assembly = newModelVisual.getModelDisplayAssembly();
        GetRenderer().AddViewProp(assembly);
        repaint();
    }
    /**
     * Temporarily hide a model from the current view
     */
    void setModelVisibility(SingleModelVisuals nextModelVis, boolean onOff) {
         vtkAssembly assembly = nextModelVis.getModelDisplayAssembly();
        if (onOff)
            assembly.VisibilityOn();
        else
            assembly.VisibilityOff();
        repaint();
    }

   public void lockDrawingSurface(boolean toLock) {
      if (toLock)
         Lock();
      else
         UnLock();
   }
   
   // support for writing AVI movies.
   vtkAVIWriter movieWriter=null;
   boolean movieWriterReady=false;
   vtkWindowToImageFilter imageFilter=null;
   /**
    * Create a movie with the specified filename
    */
   public void createMovie(String fileName) {
       movieWriter = new vtkAVIWriter();
       movieWriter.SetFileName(fileName);
              
       imageFilter = new vtkWindowToImageFilter();
       imageFilter.SetMagnification(1);
       imageFilter.SetInput(rw);
       imageFilter.ReadFrontBufferOff();
       imageFilter.Update();
       
       movieWriter.SetInputConnection(imageFilter.GetOutputPort());
       movieWriter.Start();
       movieWriterReady=true;
   }

    public void Render() {
        super.Render();
        if (movieWriter!=null && movieWriterReady){
            imageFilter.Modified();
            imageFilter.Update();
            movieWriter.Write();
        }
    }
    
    public void finishMovie() {
        movieWriter.End();
        movieWriter=null;
        movieWriterReady=false;
    }
    
}