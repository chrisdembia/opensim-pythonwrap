/*
 * OpenSimCanvas.java
 *
 * Created on June 14, 2006, 11:58 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package org.opensim.view;

import java.awt.Cursor;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import javax.swing.JPopupMenu;
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
import vtk.vtkMatrix4x4;
import vtk.vtkPropPicker;
import vtk.vtkWindowToImageFilter;
import vtk.vtkWorldPointPicker;

/**
 *
 * @author Ayman Habib
 * A wrapper around vtkPanel that provides common behavior beyond OpenSimBaseCanvas.
 * 
 */
public class OpenSimCanvas extends OpenSimBaseCanvas {
        
    JPopupMenu visibilityMenu = new JPopupMenu();

    // The object that was clicked on to initiate dragging
    OpenSimObject dragObject = null;
    double[] dragPtOld = null; // XYZ coords in world frame of point under cursor during last drag event
    double dragStartZ = 0.0; // Z value in camera frame of point under cursor when dragging began
    int lastLeftButtonClickCount = 0;
    OpenSimObject lastLeftButtonClickObject = null;
    
    /** Creates a new instance of OpenSimCanvas */
    public OpenSimCanvas() {
    }
    /**
     * Event handler to handle mousePressed
     */
   public void mousePressed(MouseEvent e)
   {
      lastX = e.getX();
      lastY = e.getY();

      int keyMods = e.getModifiers();
      double[] worldPos = new double[3];
      OpenSimObject leftClickobj = null;
      if ((keyMods & InputEvent.BUTTON1_MASK) > 0) {
         leftClickobj = findObjectAt(e.getX(), e.getY(), worldPos);

         // Some code to handle double clicking on an object, but which does so in a way that the sequence
         // CTRL-Click and Click does not count as a double click.  This avoids
         // treating as double click the case where the user selects an object
         // (CTRL-Click) and quickly starts dragging (Click & Drag) 
         if (leftClickobj != null && !ViewDB.getInstance().isPicking()) {
            if (e.getClickCount() == lastLeftButtonClickCount+1 && leftClickobj == lastLeftButtonClickObject) {
               handleDoubleClick(leftClickobj);
               return; 
            } else {
               lastLeftButtonClickCount = e.getClickCount();
               lastLeftButtonClickObject = leftClickobj;
            } 
         } else {
            lastLeftButtonClickCount = -1;
            lastLeftButtonClickObject = null;
         }
      }

      if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         if ((keyMods & InputEvent.SHIFT_MASK) > 0) {
            if (leftClickobj == null) {
               // do nothing, a la Illustrator
            } else {
               ViewDB.getInstance().toggleAddSelectedObject(leftClickobj);
            }
         } else {
            if (leftClickobj == null) {
               ViewDB.getInstance().clearSelectedObjects();
            } else {
               ViewDB.getInstance().replaceSelectedObject(leftClickobj);
            }
         }
      } else if ((leftClickobj != null) && ViewDB.getInstance().isSelected(leftClickobj) == true) {
         //System.out.println("dragging on");
         dragObject = leftClickobj;
         double[] dragZ = new double[4];
         dragPtOld = new double[4];
         dragPtOld[0] = worldPos[0];
         dragPtOld[1] = worldPos[1];
         dragPtOld[2] = worldPos[2];
         dragPtOld[3] = 1.0;
         vtkMatrix4x4 vtm = cam.GetViewTransformMatrix();
         vtm.MultiplyPoint(dragPtOld, dragZ);
         dragStartZ = dragZ[2];
         //System.out.println("Old Drag init="+dragPtOld[0]+", "+dragPtOld[1]+", "+dragPtOld[2]);
         ViewDB.getInstance().setDragging(true, dragObject);
      } else {
         super.mousePressed(e);
      }
   }

    public void mouseReleased(MouseEvent e)
    {
       int keyMods = e.getModifiers();
       if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
          // do nothing; you're still in picking mode
       } else if (ViewDB.getInstance().isDragging() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
          //System.out.println("dragging off");
          dragObject = null;
          dragPtOld = null;
          dragStartZ = 0.0;
          ViewDB.getInstance().setDragging(false, dragObject);
       } else {
          super.mouseReleased(e);
       }
    }

     /**
     * Callback invoked when the user doubleclicks an object in the graphics window
     */
    void handleDoubleClick(OpenSimObject obj) {
       ObjectEditDialogMaker editorDialog =new ObjectEditDialogMaker(obj, ViewDB.getInstance().getCurrenWindow());
       editorDialog.process();
       ViewDB.getInstance().statusDisplaySelectedObjects();
    }

   public void keyPressed(KeyEvent e) {
      if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
         //System.out.println("picking on");
         ViewDB.getInstance().setPicking(true);
        setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
      }
      else
         super.keyPressed(e);
   }

   public void keyReleased(KeyEvent e) {
      if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
         //System.out.println("picking off");
         ViewDB.getInstance().setPicking(false);
         setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
       } else
         super.keyReleased(e);
   }

   public void mouseDragged(MouseEvent e) {
      int keyMods = e.getModifiers();
      if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         // do nothing; you're still in picking mode
         lastX = e.getX();
         lastY = e.getY();
      } else if (ViewDB.getInstance().isDragging() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
         if (e.getX() != lastX || e.getY() != lastY) {
            if (dragObject != null && dragPtOld != null) {
               double viewAngle = cam.GetViewAngle();
               double x = e.getX();
               double y = e.getY();
               double w = getWidth();
               double h = getHeight();
               double aspectRatio = w / h;
               double angle = Math.toRadians(cam.GetViewAngle() * 0.5);
               double y_half = -dragStartZ * Math.tan(angle);
               double x_half = y_half * aspectRatio;
               double x_percent = x / w;
               double y_percent = (h - y) / h;
               // dragPtNew starts out as the XYZ position in the camera frame
               // of the point under the cursor
               double dragPtNew[] = new double[4];
               dragPtNew[0] = -x_half + x_percent * 2.0 * x_half;
               dragPtNew[1] = -y_half + y_percent * 2.0 * y_half;
               dragPtNew[2] = dragStartZ;
               dragPtNew[3] = 1.0;
               vtkMatrix4x4 vtm = cam.GetViewTransformMatrix();
               vtkMatrix4x4 vtmInverse = new vtkMatrix4x4();
               vtmInverse.DeepCopy(vtm);
               vtmInverse.Invert();
               // Now transform dragPtNew so it is in the world frame
               vtmInverse.MultiplyPoint(dragPtNew, dragPtNew);
               // the amount to drag the objects is the distance between dragPtOld and dragPtNew
               double dragVector[] = new double[3];
               dragVector[0] = dragPtNew[0] - dragPtOld[0];
               dragVector[1] = dragPtNew[1] - dragPtOld[1];
               dragVector[2] = dragPtNew[2] - dragPtOld[2];
               // drag the selected objects
               ViewDB.getInstance().dragSelectedObjects(dragObject, dragVector);
               // store the new point as the old, for use next time
               dragPtOld[0] = dragPtNew[0];
               dragPtOld[1] = dragPtNew[1];
               dragPtOld[2] = dragPtNew[2];
            }
         }
         lastX = e.getX();
         lastY = e.getY();
      } else {
         super.mouseDragged(e);
      }
   }

    /**
     *  Utility method to locate an OpenSimObject located atscreen coordinate  x, y.
     *  Delegates the call to modelVisuals
     */
    OpenSimObject findObjectAt(int x, int y, double[] worldPosition)
    {
        vtkPropPicker picker = new vtkPropPicker();

        Lock();
        picker.Pick(x, rw.GetSize()[1] - y, 0, ren);
        UnLock();

        vtkAssemblyPath asmPath = picker.GetPath();
        if (asmPath==null)
            return null;
         
        OpenSimObject obj= ViewDB.getInstance().pickObject(asmPath);

        if (obj == null) {
           // Could be an object that's part of a glyph
           // Try point Picker void GetCellPoints(vtkIdType cellId, vtkIdList *ptIds);
           vtkCellPicker pPicker=new vtkCellPicker();
           // Important to set tolerance to something small, else it may pick glyphs not directly under cursor
           pPicker.SetTolerance(0.0001);
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
        }
        
        if (obj != null) {
           // Get x,y,z, world for debugging
           vtkWorldPointPicker wpPicker=new vtkWorldPointPicker();
           Lock();
           wpPicker.Pick(x, rw.GetSize()[1] - y, 0, ren);
           UnLock();
           double[] foo = wpPicker.GetPickPosition(); //TODO is there an easier way to assign the double[]?
           worldPosition[0] = foo[0];
           worldPosition[1] = foo[1];
           worldPosition[2] = foo[2];
           //System.out.println("World Pos="+worldPosition[0]+", "+worldPosition[1]+", "+worldPosition[2]);
        }

        return obj;
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
        //long before=System.nanoTime();
        super.Render();
        //long after=System.nanoTime();
        //System.out.println("Render only: "+1e-6*(after-before)+" ms");
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
