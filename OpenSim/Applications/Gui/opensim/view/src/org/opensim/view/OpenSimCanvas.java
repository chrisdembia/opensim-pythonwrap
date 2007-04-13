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
import org.opensim.modeling.AbstractBody;
import org.opensim.modeling.AbstractDynamicsEngine;
import org.opensim.modeling.ArrayDouble;
import org.opensim.modeling.MusclePoint;
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
    double dragPtOld[] = null;
    
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
      OpenSimObject obj = findObjectAt(e.getX(), e.getY());
      if (ViewDB.getInstance().isPicking() == true && (keyMods & InputEvent.BUTTON1_MASK) > 0) {
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
               ViewDB.getInstance().replaceSelectedObject(obj);
            }
         }
      } else if ((keyMods & InputEvent.BUTTON1_MASK) > 0 && ViewDB.getInstance().isSelected(obj) == true) {
         //System.out.println("dragging on");
         dragObject = obj;
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
          ViewDB.getInstance().setDragging(false, dragObject);
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
        //if (obj != null)
               //StatusDisplayer.getDefault().setStatusText(obj.getType()+":"+obj.getName());
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
       OpenSimObject obj = findObjectAt(evt.getX(), evt.getY());
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
            if (dragObject != null) {
               double viewAngle = cam.GetViewAngle();
               float x = e.getX();
               float y = e.getY();
               double w = getWidth();
               double h = getHeight();
               double aspectRatio = w / h;
               double dragOrigin[] = {0.0, 0.0, 0.0, 1.0};
               getOrigin(dragObject, dragOrigin);
               vtkMatrix4x4 vtm = cam.GetViewTransformMatrix();
               vtm.MultiplyPoint(dragOrigin, dragOrigin);
               double angle = Math.toRadians(cam.GetViewAngle() * 0.5);
               double z_value = dragOrigin[2];
               double y_half = -z_value * Math.tan(angle);
               double x_half = y_half * aspectRatio;
               double x_percent = x / w;
               double y_percent = (h - y) / h;
               double dragPtNew[] = new double[4];
               dragPtNew[0] = -x_half + x_percent * 2.0 * x_half;
               dragPtNew[1] = -y_half + y_percent * 2.0 * y_half;
               dragPtNew[2] = z_value;
               dragPtNew[3] = 1.0;
               vtkMatrix4x4 vtmInverse = new vtkMatrix4x4();
               vtmInverse.DeepCopy(vtm);
               vtmInverse.Invert();
               vtmInverse.MultiplyPoint(dragPtNew, dragPtNew);
               // the first time through, compute the old drag point, since it has not yet been stored
               // (this will usually be equal to the new point)
               if (dragPtOld == null) {
                  dragPtOld = new double[4];
                  double x_percentOld = lastX / w;
                  double y_percentOld = (h - lastY) / h;
                  dragPtOld[0] = -x_half + x_percentOld * 2.0 * x_half;
                  dragPtOld[1] = -y_half + y_percentOld * 2.0 * y_half;
                  dragPtOld[2] = z_value;
                  dragPtOld[3] = 1.0;
                  vtmInverse.MultiplyPoint(dragPtOld, dragPtOld);
               }
               // the amount to drag the objects is the distance between the two points
               double dragVector[] = new double[3];
               dragVector[0] = dragPtNew[0] - dragPtOld[0];
               dragVector[1] = dragPtNew[1] - dragPtOld[1];
               dragVector[2] = dragPtNew[2] - dragPtOld[2];
               // drag the selected objects
               ViewDB.getInstance().dragSelectedObjects(dragObject, dragVector);
               // store the new pt as the old, for use next time
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
    * Get the origin of the passed-in oject in the global reference frame.
    * TODO: this code currently assumes the object is a MusclePoint, but
    * should be made more general, perhaps using VTK functions so that
    * the type of OpenSimObject is not needed.
    */
   private void getOrigin(OpenSimObject obj, double origin[]) {
      MusclePoint mp = MusclePoint.safeDownCast(obj);
      AbstractDynamicsEngine engine = mp.getMuscle().getModel().getDynamicsEngine();
      AbstractBody body = mp.getBody();
      AbstractBody ground = engine.getGroundBody();
      ArrayDouble mpt = mp.getAttachment();
      double mpt1[] = {mpt.getitem(0), mpt.getitem(1), mpt.getitem(2)};
      double mpt2[] = {mpt.getitem(0), mpt.getitem(1), mpt.getitem(2)};
      engine.transformPosition(body, mpt1, ground, mpt2);
      origin[0] = mpt2[0];
      origin[1] = mpt2[1];
      origin[2] = mpt2[2];
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