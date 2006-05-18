package simtkView;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import javax.swing.AbstractAction;
import javax.swing.JColorChooser;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;

import simtkCommands.CommandFactory;
import simtkCommands.CommandFactoryException;
import simtkCommands.ExecutionManager;
import opensimModel.VisibleObject;
import simtkui.SimtkDebugMenu;
import simtkui.SimtkPropMenu;
import vtk.vtkCanvas;
import vtk.vtkInteractorStyle;
import vtk.vtkInteractorStyleFlight;
import vtk.vtkInteractorStyleJoystickCamera;
import vtk.vtkInteractorStyleSwitch;
import vtk.vtkInteractorStyleTerrain;
import vtk.vtkInteractorStyleUnicam;
import vtk.vtkPropPicker;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * SimtkCanvas is our customization of vtkCanvas so that common behavior is
 * abstracted here. This class will possibly interact with other UI to get the
 * custiomization prefernces (e.g. AntiAliasing frames...)
 */
public class SimtkCanvas extends vtkCanvas {

  public static final int ANTIALIASING_DEFAULT = 1;

  private final JPopupMenu _viewMenu = new JPopupMenu();
  private final JMenu _mouseStyleMenu = new JMenu("Mouse Style");
//  private String _modelName = null;
  private SimtkMdlInternalFrame _iFrame=null;

  private final vtkInteractorStyle[] availableStyles = {
      new vtkInteractorStyleFlight(),
      new vtkInteractorStyleTerrain(),
      new vtkInteractorStyleSwitch(),
      new vtkInteractorStyleUnicam(),
      new vtkInteractorStyleJoystickCamera()
  };
  private final String availableStyleNames[] = {
      "Flight", "Terrain", "Trackball", "Unicam", "Joystick"
  };
  private static VisibleObject selectedObject = null;

  static {
    JPopupMenu.setDefaultLightWeightPopupEnabled(false);
  }

  public SimtkCanvas(SimtkMdlInternalFrame iFrame) {
    super();
    _iFrame = iFrame;
    // Removed the default antialiasing as it slows down rendering, users can still
    // force increasing Antialiasing level
    //rw.SetAAFrames(ANTIALIASING_DEFAULT);
    rw.DoubleBufferOff();
    rw.SetSwapBuffers(1);
    GetRenderer().SetBackground(.6, 0., .2);
    setInteractorStyle(new vtkInteractorStyleTerrain());
    create_mouseStyleMenu();
    JMenu winVisMenu = new JMenu("Window Display Options");
    JMenuItem antiAliasingMenuItem = new JMenuItem(new IncreaseAntiAliasingLevel());
    JMenuItem backgroundMenuItem = new JMenuItem(new SetBackgroundColor(this));
    JMenuItem printMenuItem = new JMenuItem("Take Snapshot");
    try {
      printMenuItem.setAction(CommandFactory.getCommand("SimtkSnapShotCmd"));
      printMenuItem.setText("Take Snapshot");
      _viewMenu.add(printMenuItem);
   }
    catch (CommandFactoryException ex) {
    }
    winVisMenu.add(antiAliasingMenuItem);
    winVisMenu.add(backgroundMenuItem);
    _viewMenu.add(winVisMenu);
    _viewMenu.add(_mouseStyleMenu);
    }

  /**
   * create_mouseStyleMenu: Adds cascade popup for interactor style
   */
  void create_mouseStyleMenu() {
    for (int i = 0; i < availableStyleNames.length; i++) {
      JMenuItem test1MenuItem = new JMenuItem(new ChangeInteractorStyle(
          availableStyleNames[i]));
      _mouseStyleMenu.add(test1MenuItem);
    }
  }

  /**
   * setAntiAliasingLevel: exposed method to set the number of Antialiasing
   * frames. Tradeoff quality vs. performance
   *
   * @param numAAFrames int
   */
  public void setAntiAliasingLevel(int numAAFrames)
  {
    rw.SetAAFrames(numAAFrames);
  }

  /**
   * getAntiAliasingLevel returns current number of Antialiasing frames
   *
   * @return int
   */
  public int getAntiAliasingLevel()
  {
    return rw.GetAAFrames();
  }

  /**
   * keyPressed overrides the default behavior in vtkCanvas and lower classes.
   * Intercepted events are handled here, else they go to std vtkCanvas. This
   * function changes default behavior of all SimtkCanvas's.
   *
   * @param e KeyEvent
   */
  public void keyPressed(KeyEvent e) {
    if (ren.VisibleActorCount() == 0) return;
 }

  /**
   * mousePressed: Handle mouse events in model window. Standard mouse keys are
   * all reserved for interaction. We use SHIFT to display _viewMenu and CTRL for
   * picking/showing visibility menu.
   *
   * @param e MouseEvent
   */
  public void mousePressed(MouseEvent e) {
    if ( (e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.SHIFT_MASK))) {
      _viewMenu.show(this, e.getX(), e.getY());
    }
    else if ( (e.getModifiers() == (InputEvent.BUTTON3_MASK | InputEvent.CTRL_MASK))) {
      selectedObject = findObjectAt(lastX, lastY);
      if (selectedObject != null){
        JPopupMenu visPopup = new JPopupMenu();
        SimtkPropMenu simtkPropMenu = new SimtkPropMenu("Properties",
            _iFrame.getModelName(), selectedObject);
        visPopup.add(simtkPropMenu);
        SimtkVisMenu simtkVisMenu = new SimtkVisMenu("Visibility",
            _iFrame.getModelName(), selectedObject);
        visPopup.add(simtkVisMenu);

        JPopupMenu debugPopup = new JPopupMenu();
        SimtkDebugMenu simtkdebugMenu = new SimtkDebugMenu("Debug",
           _iFrame.getModelName(), selectedObject);
       visPopup.add(simtkdebugMenu);
       visPopup.show(this, e.getX(), e.getY());
     }
    }
    else
      super.mousePressed(e);
  }

  /**
   * findObjectAt: Finds the VisibleObject given a selection
   * @todo: if performance becomes an issue, build a reverse lookup table to
   * locate object rather than use exhaustive search.
   *
   * @param x int
   * @param y int
   * @return OpenSimObject
   */
  private VisibleObject findObjectAt(int x, int y) {

    vtkPropPicker picker = new vtkPropPicker();

    Lock();
    picker.Pick(x, rw.GetSize()[1] - y, 0, ren);
    UnLock();

    if (picker.GetActor() != null) {
      // We'll get the first picked actor and use it for exhaustive search
      // This can be improved by using a different datastructure for reverse lookup
      return _iFrame.getVisibleObjectForActor(picker.GetActor());
    }
    return null;
  }

  /**
   * This is supposed to change background of the scene but it doesn't work.
   * @todo check if this's supposed to work (change background after window is
   * created)
   */
  private class SetBackgroundColor extends AbstractAction {
    Component _parent;

    SetBackgroundColor(Component parent)
    {
      super("Set Background Color");
      _parent = parent;
    }

    public void actionPerformed(ActionEvent e) {
      double[] dColorComponents;
      dColorComponents = SimtkCanvas.this.GetRenderer().GetBackground();
      Color oldColor = new Color((float) dColorComponents[0], (float) dColorComponents[1], (float) dColorComponents[2]);
      Color newColor = JColorChooser.showDialog(_parent, "Background Color",
                                               oldColor);
      if (newColor==null)// user cancelled
        return;
      float[] colorComponents = newColor.getRGBComponents(null);
      SimtkCanvas.this.GetRenderer().SetBackground(colorComponents[0], colorComponents[1], colorComponents[2]);
      SimtkCanvas.this.repaint();
    }
  }

  /**
   * Control Ambient light in scene. If we add more controls other than
   * Background and Ambient then we should abstract this out into a base class
   */
  private class SetAmbientColor extends AbstractAction {
    Component _parent;

    SetAmbientColor(Component parent)
    {
      super("Set Ambient Color");
      _parent = parent;
    }

    public void actionPerformed(ActionEvent e) {
      double[] dColorComponents;
      dColorComponents = SimtkCanvas.this.GetRenderer().GetAmbient();
      Color oldColor = new Color((float) dColorComponents[0], (float) dColorComponents[1], (float) dColorComponents[2]);
      Color newColor = JColorChooser.showDialog(_parent, "Ambient Color",
                                               oldColor);
      if (newColor==null) // user cancelled
        return;
      float[] colorComponents = newColor.getRGBComponents(null);
      SimtkCanvas.this.GetRenderer().SetAmbient(colorComponents[0], colorComponents[1], colorComponents[2]);
      SimtkCanvas.this.repaint();
    }
  }

  private class IncreaseAntiAliasingLevel extends AbstractAction {

    IncreaseAntiAliasingLevel()
    {
      super("Increase Antialiasing frames");
    }
    public void actionPerformed(ActionEvent e) {
      SimtkCanvas.this.setAntiAliasingLevel(SimtkCanvas.this.getAntiAliasingLevel()+1   );

    }
  }


  /**
   * Inner class to implement callbacks to change interaction/mouse style
   */
  private class ChangeInteractorStyle extends AbstractAction {

    ChangeInteractorStyle(String StyleName)
    {
      super(StyleName);
    }

    /**
     * actionPerformed: Callback for interactor style menu
     *
     * @param e ActionEvent
     */
    public void actionPerformed(ActionEvent e) {
      for(int i=0; i < availableStyleNames.length; i++){
        if (e.getActionCommand()==availableStyleNames[i]){
          SimtkCanvas.this.setInteractorStyle(availableStyles[i]);
          break;
        }
      }
    }
  }

  private class print2Tiff extends AbstractAction {
    Component _parent;

    print2Tiff(Component parent)
    {
      super("Take Snapshot");
      _parent=parent;
    }

    /**
     * actionPerformed: Callback for snapshot
     *
     * @param e ActionEvent
     */
    public void actionPerformed(ActionEvent e) {
      try {
        ExecutionManager.enQueueCommand(CommandFactory.getCommand(
            "SimtkSnapShotCmd"));
      }
      catch (CommandFactoryException ex) {
      }
    }
  }
}
