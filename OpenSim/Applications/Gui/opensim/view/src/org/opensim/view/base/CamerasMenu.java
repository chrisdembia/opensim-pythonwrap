/*
 *
 * CamerasMenu
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

import java.awt.event.ActionEvent;
import java.util.ArrayList;
import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import vtk.vtkCamera;
import vtk.vtkLightCollection;

/**
 *
 * @author Ayman
 *
 * A class to create a list of cameras with standard views (front, top, side).
 */
public class CamerasMenu extends JMenu {
    
    OpenSimBaseCanvas dCanvas;
    static vtkCamera upXCamera, upZCamera, upYCamera;
    
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
        upXCamera = new vtkCamera(); //x
        upXCamera.Azimuth(90);
        upXCamera.Elevation(0);
        upXCamera.Roll(0);
        upXCamera.SetViewAngle(30);
        upXCamera.SetFocalPoint(0, 0, 0);
        upXCamera.SetViewUp(0, 1, 0);

        upZCamera = new vtkCamera();    //z
        upZCamera.Azimuth(0);
        upZCamera.Elevation(0);
        upZCamera.Roll(0);
        upZCamera.SetViewAngle(30);
        upZCamera.SetFocalPoint(0, 0, 0);
        upZCamera.SetViewUp(0, 1, 0);
        
        upYCamera = new vtkCamera();   //y
        upYCamera.Azimuth(0);
        upYCamera.Elevation(90);
        upYCamera.Roll(180);
        upYCamera.SetViewAngle(30);
        upYCamera.SetFocalPoint(0, 0, 0);
        upYCamera.SetViewUp(0, 0, -1);

        availableCameras.add(upXCamera);
        availableCameraNames.add("Front");
        availableCameras.add(upZCamera);
        availableCameraNames.add("Side");
        availableCameras.add(upYCamera);
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

