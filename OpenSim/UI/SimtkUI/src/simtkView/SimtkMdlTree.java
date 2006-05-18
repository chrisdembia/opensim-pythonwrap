package simtkView;

import java.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;

import simtkCommands.*;
import simtkCore.*;
import opensimModel.*;
import simtkui.*;
import simtkui.guiUtilities.*;

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
 * This class represents the "Model-tree" that shows on the left side of the
 * main dialog. Tree-display specific behavior is maintained here. Although this
 * is primarily a view object the class has some other UI components since Swing
 * entangles the view and (UI).
 */
public class SimtkMdlTree extends JTree {
  private SimtkDB _simtkDB = null;// Keep reference to database.
  private JPopupMenu _popup = new JPopupMenu("Available options");
  private static OpenSimObject selectedObject = null;
  private static TreePath selPath=null;
  static {
    // Enable popups to show on top of heavy-weight components to work around a Swing bug.
    JPopupMenu.setDefaultLightWeightPopupEnabled(false);
  }

  /**
   * initialize: Sets up the tree with the TreeModel from the database and the
   * SelectionModel
   */
  public void initialize() {
    _simtkDB = SimtkDB.getInstance();
    setModel(_simtkDB.getTreeModel());
    getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
    setRootVisible(false);
  }

  /**
   * registerCustomCommands
   */
  static public void registerCustomCommands(String[] classNames, SimtkCommand[] commands) {
    for(int i=0; i < classNames.length; i++)
      SimtkJMenuFactory.registerActionWithClass(
          classNames[i], commands[i]);
  }

  /**
   * SimtkMdlTree dfault constructor
   */
  public SimtkMdlTree() {
    super();
    this.setCellRenderer(new SimtkMdlTreeRenderer());
  }

  /**
   * handleMousePressed: Single entry point for handling mouse events on the
   * model-tree
   *
   * @param e MouseEvent
   */
  public void handleMousePressed(MouseEvent e) {
    selPath = getPathForLocation(e.getX(), e.getY());
    if (selPath==null)
      return;
    int pathLength = selPath.getPathCount();
    _popup.removeAll();

    DefaultMutableTreeNode selNode = (DefaultMutableTreeNode) selPath.getPathComponent(pathLength - 1);
    Object selObj = selNode.getUserObject();

    boolean showPopup = populateObjectPopup(selObj);

    if (showPopup)
      _popup.show( (Component) e.getSource(), e.getX(), e.getY());
  }

  /**
   * populateObjectPopup is the method that fills the popup to be displayed when
   * right mouse clicking a node in the model tree. It has the side effect of setting
   * the variable selectedObject to proper OpenSimObject. It's an effort to modularize how
   * popups are populated so that it can exposed to end-users.
   *
   * @param selObj Object is the selected object
   * @return boolean true if popup needs to be shown false otherwise
   */
  private boolean populateObjectPopup(Object selObj)
  {
    boolean showPopup = false;
    /** Don't show menu unless we have an object associated with the tree node */
    if (selObj instanceof SimtkSimEnv){
      _popup.add(new SimtkSimulationEnvMenu("Simulation Environment", getSimEnv(selPath).getName()));
      showPopup = true;
     }
    else if (selObj instanceof Manager){
      _popup.add(new SimtkSimulationMenu("Simulation", getSimEnv(selPath).getName()));
      showPopup = true;
  }
   if (selObj instanceof OpenSimObject){// We can only handle model objects below with getSelectedModel
      _popup.add(new SimtkPropMenu("Properties",
                                   getSimEnv(selPath).getModel().getName(),
                                   (OpenSimObject) selObj));
      showPopup = true;
      if (selObj instanceof VisibleObject)
        _popup.add(new SimtkVisMenu("Visibility",
                                    getSimEnv(selPath).getModel().getName(),
                                    (VisibleObject) selObj));
        selectedObject = (OpenSimObject) selObj;
    }
    // Add custom menu actions
    if (showPopup){
      Vector customActions = SimtkJMenuFactory.getRegisteredActions(selObj.getClass().getName());
      if (customActions != null){
        for (int i = 0; i < customActions.size(); i++){
          SimtkCommand cmd = (SimtkCommand) customActions.elementAt(i);
          if (cmd instanceof SimtkEnvCommand)
            ((SimtkEnvCommand) cmd).setEnv(getSimEnv(selPath));
          if (cmd instanceof SimtkModelCommand)
            ((SimtkModelCommand) cmd).setModel(getSimEnv(selPath).getModel());
          if (cmd instanceof SimtkModelObjectCommand)
            ((SimtkModelObjectCommand) cmd).setObject((OpenSimObject)selObj);
          _popup.add(new JMenuItem(cmd));
        }
      }
    }
    return showPopup;
  }

  /**
   * getSimEnv
   *
   * @param selPath TreePath
   * @return Object
   */
  private SimtkSimEnv getSimEnv(TreePath selPath) {
    // Go down the path to find out instances of Model
    int pathLength = selPath.getPathCount();
    for( int i=0; i <= pathLength -1; i++){
      DefaultMutableTreeNode selNode = (DefaultMutableTreeNode) selPath.getPathComponent(i);
      Object selObj = selNode.getUserObject();
      if (selObj instanceof SimtkSimEnv){
        return (SimtkSimEnv) selObj;
      }
    }
    return null;
  }

  /**
   * getSelectedModel: Finds out the Model for the selected object by
   * traversing the tree path of the selected tree node and checking if it
   * corresponds to an Model object
   *
   * @param path TreePath
   * @return Model
   */
  Model getSelectedModel(TreePath path) {
    // Go down the path to find out instances of Model
    int pathLength = path.getPathCount();
    for( int i=0; i <= pathLength -1; i++){
      DefaultMutableTreeNode selNode = (DefaultMutableTreeNode) selPath.getPathComponent(i);
      Object selObj = selNode.getUserObject();
      if (selObj instanceof Model){
        return (Model) selObj;
      }
    }
    return null;
  }

  /**
   * addCustomCommands registers special purpose commands associated with individual classes
   */
  public void addCustomCommands() {
    SimtkCommand[] customCommands = new SimtkCommand[1];
    String[]         customCommandClasses = new String[1];
    customCommands[0] = new SimtkEditPlotCommand();
    customCommandClasses[0] = "opensimModel.Control";
    registerCustomCommands(customCommandClasses, customCommands);
  }
}
