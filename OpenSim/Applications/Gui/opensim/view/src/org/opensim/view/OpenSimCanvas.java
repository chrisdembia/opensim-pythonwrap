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
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import javax.swing.JPopupMenu;
import org.openide.awt.StatusDisplayer;
import org.opensim.modeling.OpenSimObject;
import org.opensim.view.base.OpenSimBaseCanvas;
import org.opensim.view.editors.ObjectEditDialogMaker;
import org.opensim.view.pub.ViewDB;
import vtk.vtkAVIWriter;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAssemblyNode;
import vtk.vtkAssemblyPath;
import vtk.vtkCellPicker;
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
       int keyMods = e.getModifiers();
       if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
          OpenSimObject obj = findObjectAt(lastX, lastY);
          if ((keyMods & InputEvent.SHIFT_MASK) > 0) {
             if (obj == null) {
                // do nothing, a la Illustrator
             } else {
                ViewDB.getInstance().toggleAddSelectedObject(obj);
             }
          } else {
             if (obj == null) {
                ViewDB.getInstance().clearSelectedObjects();
             } else {
                ViewDB.getInstance().toggleSelectedObject(obj);
             }
          }
       } else {
          super.mousePressed(e);
       }
    }
 
    public void mouseReleased(MouseEvent e)
    {
       int keyMods = e.getModifiers();
       if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
          // do nothing; you're still in picking mode
       } else {
          super.mouseReleased(e);
       }
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
        if (asmPath==null)
            return null;
         
        OpenSimObject obj= ViewDB.getInstance().pickObject(asmPath);
        if (obj !=null) return obj;
         
        // Could be an object that's part of a glyph
        
        // Try point Picker void GetCellPoints(vtkIdType cellId, vtkIdList *ptIds);
        vtkCellPicker pPicker=new vtkCellPicker();
        vtkAssemblyNode asmNode=null;
        Lock();
        pPicker.Pick(x, rw.GetSize()[1] - y, 0, ren);
        asmNode= pPicker.GetPath().GetLastNode();
        UnLock();
        if (asmNode==null)
           return null;
        vtkActor candidateActor=(vtkActor) asmNode.GetViewProp();
        int cellId = pPicker.GetCellId();
        obj = ViewDB.getInstance().getSelectedGlyphObject(cellId, candidateActor);
        if (obj != null)
               StatusDisplayer.getDefault().setStatusText(obj.getType()+":"+obj.getName());
        // Get x,y,z, world for debugging
        /*
        vtkWorldPointPicker wpPicker=new vtkWorldPointPicker();
        Lock();
        wpPicker.Pick(x, rw.GetSize()[1] - y, 0, ren);
        UnLock();
        double[] wpos = wpPicker.GetPickPosition();
        //System.out.print("World Pos="+wpos[0]+", "+wpos[1]+", "+wpos[2]); */
        return obj;
    }
     /**
     * Callback invoked when the user doubleclicks an object in the graphics window
     */
    void handleDoubleClick(MouseEvent evt) {
       OpenSimObject obj = findObjectAt(lastX, lastY);
       if (obj != null){
          ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(obj, ViewDB.getInstance().getCurrenWindow());
          editorDialog.process();
          ViewDB.getInstance().statusDisplaySelectedObjects();
       }
    }

     //void selectObject(MouseEvent evt) {
        //OpenSimObject obj = findObjectAt(lastX, lastY);
        //ViewDB.getInstance().setSelectedObject(obj);
    //}

   public void keyPressed(KeyEvent e) {
      if (e.getKeyCode() == 17) {
         //System.out.println("picking on");
         ViewDB.getInstance().setPicking(true);
      }
      else
         super.keyPressed(e);
   }

   public void keyReleased(KeyEvent e) {
      if (e.getKeyCode() == 17) {
         //System.out.println("picking off");
         ViewDB.getInstance().setPicking(false);
      } else
         super.keyReleased(e);
   }

   public void mouseDragged(MouseEvent e) {
      int keyMods = e.getModifiers();
      if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         // do nothing; you're still in picking mode
      } else {
         super.mouseDragged(e);
      }
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