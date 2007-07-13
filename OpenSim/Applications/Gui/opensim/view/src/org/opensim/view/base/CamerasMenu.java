/*
 *
 * CamerasMenu
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

import java.awt.event.ActionEvent;
import java.util.ArrayList;
import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import vtk.vtkCamera;
import vtk.vtkLightCollection;

/**
 *
 * @author Ayman & Jeff Reinbolt
 *
 * A class to create a list of cameras with standard views.
 */
public class CamerasMenu extends JMenu {
    
    OpenSimBaseCanvas dCanvas;
    static vtkCamera minusXCamera, minusZCamera, minusYCamera;
    static vtkCamera plusXCamera, plusZCamera, plusYCamera;
    
    static ArrayList<vtkCamera> availableCameras = new ArrayList<vtkCamera>();
    static ArrayList<String> availableCameraNames = new ArrayList<String>();
    static ArrayList<JMenuItem> availableCameraItems = new ArrayList<JMenuItem>();
    static boolean initialzed = false;

   /** Creates a new instance of CamerasMenu */
    public CamerasMenu(OpenSimBaseCanvas aCanvas) {
        super("Cameras");
        dCanvas = aCanvas;
        if (!initialzed){
            createDefaultCameras();
            createCameraActions();
            for( int i=0; i < availableCameras.size(); i++ )
                add(availableCameraItems.get(i));
            initialzed = true;
        }
    }
    
    private void createDefaultCameras()
    {
        plusXCamera = new vtkCamera(); // +x
        plusXCamera.Azimuth(-90);
        plusXCamera.Elevation(0);
        plusXCamera.Roll(0);
        plusXCamera.SetViewAngle(30);
        plusXCamera.SetFocalPoint(0, 0, 0);
        plusXCamera.SetViewUp(0, 1, 0);
        
        minusXCamera = new vtkCamera(); // -x
        minusXCamera.Azimuth(90);
        minusXCamera.Elevation(0);
        minusXCamera.Roll(0);
        minusXCamera.SetViewAngle(30);
        minusXCamera.SetFocalPoint(0, 0, 0);
        minusXCamera.SetViewUp(0, 1, 0);

        plusZCamera = new vtkCamera(); // +z
        plusZCamera.Azimuth(180);
        plusZCamera.Elevation(0);
        plusZCamera.Roll(0);
        plusZCamera.SetViewAngle(30);
        plusZCamera.SetFocalPoint(0, 0, 0);
        plusZCamera.SetViewUp(0, 1, 0);
        
        minusZCamera = new vtkCamera(); // -z
        minusZCamera.Azimuth(0);
        minusZCamera.Elevation(0);
        minusZCamera.Roll(0);
        minusZCamera.SetViewAngle(30);
        minusZCamera.SetFocalPoint(0, 0, 0);
        minusZCamera.SetViewUp(0, 1, 0);
        
        plusYCamera = new vtkCamera(); // +y
        plusYCamera.SetViewUp(1, 0, 0);
        plusYCamera.Azimuth(90);
        plusYCamera.Elevation(0);
        plusYCamera.Roll(0);
        plusYCamera.SetViewAngle(30);
        plusYCamera.SetFocalPoint(0, 0, 0);
         
        minusYCamera = new vtkCamera(); // -y
        minusYCamera.SetViewUp(-1, 0, 0);
        minusYCamera.Azimuth(90);
        minusYCamera.Elevation(0);
        minusYCamera.Roll(0);
        minusYCamera.SetViewAngle(30);
        minusYCamera.SetFocalPoint(0, 0, 0);

        availableCameras.add(plusXCamera);
        availableCameraNames.add("Back");
        availableCameras.add(minusXCamera);
        availableCameraNames.add("Front");
        availableCameras.add(plusZCamera);
        availableCameraNames.add("Left");
        availableCameras.add(minusZCamera);
        availableCameraNames.add("Right");
        availableCameras.add(plusYCamera);
        availableCameraNames.add("Bottom");
        availableCameras.add(minusYCamera);
        availableCameraNames.add("Top");
    }

    private void createCameraActions()
    {
        for(int i=0; i < availableCameras.size(); i++){
            setPickCameraAction cameraAction = new setPickCameraAction();
            JMenuItem cameraItem = new JMenuItem(cameraAction);
            cameraItem.setActionCommand(availableCameraNames.get(i));
            cameraItem.setText(availableCameraNames.get(i));
            availableCameraItems.add(cameraItem);
        }
        // Add a new Camera definition option
        
        
    }
    /**
     * Pick one of the standard Front, Top, Side Cameras using fullname.
     * Eventually the user will be able to add some and assocate a keyboard binding with it
     * if not already in use.
     */
    static public vtkCamera pickStandardCamera(String camName)
    {
        int index = availableCameraNames.indexOf((String)camName);
        if (index != -1){
            return availableCameras.get(index);
        }
        return null;
    }

    /**
     * Handle button push of Camera Actions
     **/
   private class setPickCameraAction extends AbstractAction {

    /**
     * actionPerformed
     *
     * @param e ActionEvent
     */
    public void actionPerformed(ActionEvent e) {
      String cameraName = e.getActionCommand();
      int cameraIndex = availableCameraNames.indexOf((Object) cameraName);
        vtkCamera selectedCamera = availableCameras.get(cameraIndex);
        CamerasMenu.this.dCanvas.applyCamera(selectedCamera);
      }
    }
  }

