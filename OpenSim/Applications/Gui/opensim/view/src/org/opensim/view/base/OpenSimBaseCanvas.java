/*
 *
 * OpenSimBaseCanvas
 * Author(s): Ayman Habib
 * Copyright (c) 2005-2006, Stanford University, Ayman Habib
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

import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.util.StringTokenizer;
import java.util.prefs.Preferences;
import javax.swing.JMenu;
import javax.swing.JPopupMenu;
import org.openide.util.NbBundle;
import org.opensim.utils.TheApp;
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
        implements KeyListener {
    
    JPopupMenu settingsMenu = new JPopupMenu();
    JMenu camerasMenu = new JMenu();
    
    // Enable opoups to display on top of heavy weight component/canvas
    static {
     JPopupMenu.setDefaultLightWeightPopupEnabled(false);
    }
    /** Creates a new instance of OpenSimBaseCanvas */
    public OpenSimBaseCanvas() {
         String defaultBackgroundColor="0.15, 0.15, 0.15";
         defaultBackgroundColor = Preferences.userNodeForPackage(TheApp.class).get("BackgroundPref", defaultBackgroundColor);
         double[] background = parseColor(defaultBackgroundColor);
         GetRenderer().SetBackground(background);
         createSettingsMenu();
         addKeyListener(this);
         // AntiAliasing
         String desiredAAFrames = NbBundle.getMessage(OpenSimBaseCanvas.class,"CTL_AAFrames");
         if (desiredAAFrames != null){
             int numAAFrames = Integer.parseInt(desiredAAFrames);
             if (numAAFrames >=0 && numAAFrames <=10)
                 GetRenderWindow().SetAAFrames(numAAFrames);
         }

    }
    public void mousePressed(MouseEvent e)
   {
      
    if ((e.getModifiers()== (InputEvent.BUTTON3_MASK | InputEvent.SHIFT_MASK))){
        settingsMenu.show(this, e.getX(), e.getY());
    }
    // Show popup if right mouse otherwise pass along to super implementation
    super.mousePressed(e);
  }
  
  public void createSettingsMenu()
  {
      settingsMenu = new JPopupMenu();
      /** This should work and is more netBeans like style, but somehow fails to find Actions
       * possibly because of layer file issues
        try {
            
            Action act = (ModifyWindowSettingsAction) ModifyWindowSettingsAction.findObject(
                              Class.forName("org.opensim.view.base.ModifyWindowSettingsAction"));
            settingsMenu.add(act);
            settingsMenu.add((ToggleAxesAction) ToggleAxesAction.findObject(
                            Class.forName("org.opensim.view.base.ToggleAxesAction")));
       } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
       **/
      settingsMenu.add(new ModifyWindowSettingsAction());
      settingsMenu.add(new ToggleAxesAction());
      /*settingsMenu.add(*/new CamerasMenu(this);//);   // Already enough ways to do this better than crowding menus
  }

  public JPopupMenu getMenu()
    {
        return settingsMenu;
    }
    /**
     * Handle keys for default cameras, otherwise pass on to super
     * to get default vtkPanel behavior.
     */
      public void keyPressed(KeyEvent e)
      {
        char keyChar = e.getKeyChar();

        if ('x' == keyChar)
          {
         applyCameraX();
          }
        else if ('y' == keyChar)
          {
            applyCameraY();   
          }
        else if ('z' == keyChar)
          {
               applyCameraZ();
          }
        else if ('i' == keyChar)
        {
           GetRenderer().GetActiveCamera().Zoom(1.1);
           repaint();
        }
        else if ('o' == keyChar)
        {
           GetRenderer().GetActiveCamera().Zoom(0.9);
           repaint();
        }
        super.keyPressed(e);
      }

   public void applyCameraY() { 
      applyCamera(CamerasMenu.pickStandardCamera("Top"));
   }

   public void applyCameraZ() {
      applyCamera(CamerasMenu.pickStandardCamera("Side"));
   }

   public void applyCameraX() {
      applyCamera(CamerasMenu.pickStandardCamera("Front"));
   }
      
      /**
       * A method to apply a prespecified Camera (selectedCamera) to the current Canvas
       */
      public void applyCamera(vtkCamera selectedCamera)
      {
        vtkCamera currentCamera = GetRenderer().GetActiveCamera();
        currentCamera.SetPosition(selectedCamera.GetPosition());
        currentCamera.SetFocalPoint(selectedCamera.GetFocalPoint());
        currentCamera.SetViewAngle(selectedCamera.GetViewAngle());
        currentCamera.SetDistance(selectedCamera.GetDistance());
        currentCamera.SetClippingRange(selectedCamera.GetClippingRange());
        currentCamera.SetViewUp(selectedCamera.GetViewUp());
        currentCamera.SetParallelScale(selectedCamera.GetParallelScale());

        vtkLightCollection lights = GetRenderer().GetLights();
        lights.RemoveAllItems();
        GetRenderer().CreateLight();
        GetRenderer().ResetCamera();
        //GetRenderer().Render();
        repaint();
      }

    private double[] parseColor(String defaultBackgroundColor) {
        double[] color = new double[3];
        int i=0;
        StringTokenizer tokenizer = new StringTokenizer(defaultBackgroundColor, " \t\n\r\f,");
        while (tokenizer.hasMoreTokens() && i<3){
            String nextToken = tokenizer.nextToken();
            color[i] = Double.parseDouble(nextToken);
            i++;
        }
        return color;
    }
}
