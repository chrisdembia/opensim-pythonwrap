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
import java.awt.event.MouseEvent;
import javax.swing.JMenu;
import javax.swing.JPopupMenu;
import vtk.AxesActor;
import vtk.vtkActor;
import vtk.vtkAssembly;
import vtk.vtkAxes;
import vtk.vtkMapper;
import vtk.vtkPanel;

/**
 *
 * @author Ayman
 */
public class OpenSimBaseCanvas extends vtkPanel {
    
    JPopupMenu settingsMenu = new JPopupMenu();
    JMenu camerasMenu = new JMenu();
    
    vtkAssembly     axesActor;
    boolean axesDisplayed;
    
    // Enable opoups to display on top of heavy weight component/canvas
    static {
     JPopupMenu.setDefaultLightWeightPopupEnabled(false);
    }
    /** Creates a new instance of OpenSimBaseCanvas */
    public OpenSimBaseCanvas() {
         GetRenderer().SetBackground(0.2, 0.2, 1.0); 
         createSettingsMenu();
         axesActor = null;
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
      settingsMenu.add(new ModifyWindowSettingsAction(this));
      settingsMenu.add(new CamerasMenu(this));
      settingsMenu.add(new ToggleAxesAction(this));
  }

    boolean getAxesDisplayed() {
        return (axesDisplayed);
    }

    void displayAxes(boolean toDisplay) {
        if (toDisplay){
            axesActor = new AxesActor();
            //vtkMapper axesMapper = new vtkMapper();
            //axesActor.SetMapper(axesMapper);
            GetRenderer().AddViewProp(axesActor);
            setAxesDisplayed(true);
            Render();
        }
        else {
            this.GetRenderer().RemoveActor(axesActor);
            setAxesDisplayed(false);
            Render();
        }
    }

    void setAxesDisplayed(boolean b) {
        axesDisplayed = b;
    }
  
}
