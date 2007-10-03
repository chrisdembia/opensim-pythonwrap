/*
 *
 * OpenSimBaseCanvas
 * Author(s): Ayman Habib & Jeff Reinbolt
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib & Jeff Reinbolt
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package org.opensim.view.base;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.prefs.Preferences;
import javax.swing.JPopupMenu;
import org.opensim.utils.Prefs;
import org.opensim.utils.TheApp;
import org.opensim.view.Camera;
import org.opensim.view.pub.ViewDB;
import vtk.vtkCamera;
import vtk.vtkLightCollection;
import vtk.vtkPanel;

/**
 *
 * @author Ayman Habib
 *
 * Base class for the Canvas to collect all the properties to be shared by OpenSim based
 * applications and to enforce behvior (e.g colors, camera, mouse interaction) that's not specific
 * to OpenSim's Top Gui Application.
 */
public class OpenSimBaseCanvas extends vtkPanel
        implements KeyListener, MouseListener {
   
   String defaultBackgroundColor="0.15, 0.15, 0.15";
   int    numAAFrames=0;
   JPopupMenu settingsMenu = new JPopupMenu();
   CamerasMenu camerasMenu;

   double currentTime = 0;
   Camera camera = null;
   
   // Enable opoups to display on top of heavy weight component/canvas
   static {
      JPopupMenu.setDefaultLightWeightPopupEnabled(false);
      javax.swing.ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);
   }
   /** Creates a new instance of OpenSimBaseCanvas */
   public OpenSimBaseCanvas() {
      defaultBackgroundColor = Preferences.userNodeForPackage(TheApp.class).get("BackgroundColor", defaultBackgroundColor);
      double[] background = Prefs.getInstance().parseColor(defaultBackgroundColor);
      GetRenderer().SetBackground(background);
      createSettingsMenu();
      camerasMenu = new CamerasMenu(this);
      addKeyListener(this);
      // AntiAliasing
      int desiredAAFrames = Preferences.userNodeForPackage(TheApp.class).getInt("AntiAliasingFrames", numAAFrames);
      if (desiredAAFrames >=0 && desiredAAFrames<=10){
         numAAFrames=desiredAAFrames;
      }
      GetRenderWindow().SetAAFrames(numAAFrames);
   }
   
   public void mousePressed(MouseEvent e) {
      super.mousePressed(e);
      // Disabled popup for now
      /*
      // Show popup if right mouse and Shift key, otherwise pass along to super implementation
      if ((e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.SHIFT_MASK))) {
         settingsMenu.show(this, e.getX(), e.getY());
      } else {
         super.mousePressed(e);
      }
      */
   }
   
   public void mouseDragged(MouseEvent e) {
      super.mouseDragged(e);
      // Disabled popup for now
      /*
      // do nothing (handled by settingsMenu) if right mouse and Shift, otherwise pass along to super implementation
      if ((e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.SHIFT_MASK))) {
      } else {
         super.mouseDragged(e);
      }
      */
   }
   
   public void createSettingsMenu() {
      settingsMenu = new JPopupMenu();
      /** This should work and is more netBeans like style, but somehow fails to find Actions
       * possibly because of layer file issues*/
      try {
         settingsMenu.add((ModifyWindowSettingsAction) (ModifyWindowSettingsAction.findObject(
                 Class.forName("org.opensim.view.base.ModifyWindowSettingsAction"), true)));
         settingsMenu.add((ToggleAxesAction) ToggleAxesAction.findObject(
                 Class.forName("org.opensim.view.base.ToggleAxesAction"), true));
      } catch (ClassNotFoundException ex) {
         ex.printStackTrace();
      }
   }
   
   public JPopupMenu getMenu() {
      return settingsMenu;
   }
   /**
    * Handle keys for default cameras, otherwise pass on to super
    * to get default vtkPanel behavior.
    */
   public void keyPressed(KeyEvent e) {
      char keyChar = e.getKeyChar();
      
      if ('x' == keyChar) {
         applyCameraMinusX();
      } else if ('y' == keyChar) {
         applyCameraMinusY();
      } else if ('z' == keyChar) {
         applyCameraMinusZ();
      } else if ('i' == keyChar) {
         GetRenderer().GetActiveCamera().Zoom(1.01);
         repaint();
      } else if ('o' == keyChar) {
         GetRenderer().GetActiveCamera().Zoom(0.99);
         repaint();
      }
      super.keyPressed(e);
   }
   
   public void applyCameraPlusY() {
      applyCamera(camerasMenu.pickStandardCamera("Bottom"));
   }
   
   public void applyCameraMinusY() {
      applyCamera(camerasMenu.pickStandardCamera("Top"));
   }
   
   public void applyCameraPlusZ() {
      applyCamera(camerasMenu.pickStandardCamera("Left"));
   }
   
   public void applyCameraMinusZ() {
      applyCamera(camerasMenu.pickStandardCamera("Right"));
   }
   
   public void applyCameraPlusX() {
      applyCamera(camerasMenu.pickStandardCamera("Back"));
   }
   
   public void applyCameraMinusX() {
      applyCamera(camerasMenu.pickStandardCamera("Front"));
   }

   // Overrides vtkPanel.resetCamera() to reset camera on selected objects (if any)
   public void resetCamera() {
      Lock();
      double[] bounds = ViewDB.getInstance().getSelectedObjectBounds();
      if(bounds!=null) GetRenderer().ResetCamera(bounds);
      else {
         bounds = ViewDB.getInstance().getSceneBoundsBodiesOnly();
         if(bounds!=null) GetRenderer().ResetCamera(bounds);
         else GetRenderer().ResetCamera();
      }
      UnLock();
   } 
      
   
   /**
    * A method to apply a prespecified Camera (selectedCamera) to the current Canvas
    */
   public void applyCamera(vtkCamera selectedCamera) {
      applyOrientation(selectedCamera);
      
      vtkLightCollection lights = GetRenderer().GetLights();
      lights.RemoveAllItems();
      GetRenderer().CreateLight();

      resetCamera();

      //GetRenderer().Render();
      repaint();
   }

    public void applyOrientation(final vtkCamera selectedCamera) {
        vtkCamera currentCamera = GetRenderer().GetActiveCamera();
        currentCamera.SetPosition(selectedCamera.GetPosition());
        currentCamera.SetFocalPoint(selectedCamera.GetFocalPoint());
        currentCamera.SetViewAngle(selectedCamera.GetViewAngle());
        currentCamera.SetDistance(selectedCamera.GetDistance());
        currentCamera.SetClippingRange(selectedCamera.GetClippingRange());
        currentCamera.SetViewUp(selectedCamera.GetViewUp());
        currentCamera.SetParallelScale(selectedCamera.GetParallelScale());
    }


   //========================================================================
   // Methods for new (animatable) Camera class
   //========================================================================

   public void setCamera(Camera camera) {
      System.out.println("OpenSimBaseCanvas.setCamera "+((camera!=null)?camera.getName():""));
      this.camera = camera;
      applyTime(currentTime);
   }
   public Camera getCamera() { return camera; }

   // TODO: really we should be querying the motion controller for the current time, but it's inaccessible from this package
   public double getCurrentTime() { return currentTime; }

   public void applyCameraConfiguration(Camera.Configuration config, boolean doRepaint) {
      config.applyToView(this);
      vtkLightCollection lights = GetRenderer().GetLights();
      lights.RemoveAllItems();
      GetRenderer().CreateLight();
      if(doRepaint) repaint();
   }
  
   public void applyTime(double time) {
      // Cache time since we don't have direct access to the motion controller
      currentTime = time;

      // if camera not null, apply modified camera
      // if not animated camera, don't need to do anything (assume that when user switched to that
      // nonanimated camera, the proper configuration was selected and that was good enough
      if(camera!=null && camera.getNumKeyFrames()>0) {
         applyCameraConfiguration(camera.getConfiguration(currentTime), false);
      }
   } 

   // mouseEntered and being a MouseListener is done for the specific purpose
   // of not calling super.mouseEnetered as it requests focus which throws modeless windows 
   // on top of the vtk window to the back. Alternatively we can change vtkPanel (but 
   // that's messy since it's a part of the standard VTK distribution).
    public void mouseEntered(MouseEvent e) {
        // super.mouseEntered(e);
    }
}
