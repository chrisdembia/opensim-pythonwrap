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
    static vtkCamera frontCamera, topCamera, sideCamera;
    
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
        frontCamera = new vtkCamera(); //x
        frontCamera.Azimuth(90);
        frontCamera.Elevation(0);
        frontCamera.Roll(0);
        frontCamera.SetViewAngle(30);
        frontCamera.SetFocalPoint(0, 0, 0);
        frontCamera.SetViewUp(0, 1, 0);

        topCamera = new vtkCamera();    //z
        topCamera.Azimuth(0);
        topCamera.Elevation(0);
        topCamera.Roll(0);
        topCamera.SetViewAngle(30);
        topCamera.SetFocalPoint(0, 0, 0);
        topCamera.SetViewUp(0, 1, 0);
        
        sideCamera = new vtkCamera();   //y
        sideCamera.Azimuth(0);
        sideCamera.Elevation(90);
        sideCamera.Roll(180);
        sideCamera.SetViewAngle(30);
        sideCamera.SetFocalPoint(0, 0, 0);
        sideCamera.SetViewUp(0, 0, -1);

        availableCameras.add(frontCamera);
        availableCameraNames.add("Front");
        availableCameras.add(topCamera);
        availableCameraNames.add("Top");
        availableCameras.add(sideCamera);
        availableCameraNames.add("Side");
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

