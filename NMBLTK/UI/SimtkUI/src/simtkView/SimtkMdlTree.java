package simtkView;

import java.awt.Component;
import java.awt.event.MouseEvent;
import java.util.Vector;

import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

import simtkCommands.SimtkCommand;
import simtkCommands.SimtkEnvCommand;
import simtkCommands.SimtkModelCommand;
import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkModel.rdManager;
import simtkModel.rdModel;
import simtkModel.rdObject;
import simtkModel.rdVisibleObject;
import simtkui.SimtkPropMenu;
import simtkui.SimtkSimulationEnvMenu;
import simtkui.SimtkSimulationMenu;
import simtkui.guiUtilities.SimtkJMenuFactory;

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
  private static rdObject selectedObject = null;
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
   * the variable selectedObject to proper rdObject. It's an effort to modularize how
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
    else if (selObj instanceof rdManager){
      _popup.add(new SimtkSimulationMenu("Simulation", getSimEnv(selPath).getName()));
      showPopup = true;
  }
   if (selObj instanceof rdObject){// We can only handle model objects below with getSelectedModel
      _popup.add(new SimtkPropMenu("Properties",
                                   getSimEnv(selPath).getModel().getName(),
                                   (rdObject) selObj));
      showPopup = true;
      if (selObj instanceof rdVisibleObject)
        _popup.add(new SimtkVisMenu("Visibility",
                                    getSimEnv(selPath).getModel().getName(),
                                    (rdVisibleObject) selObj));
        selectedObject = (rdObject) selObj;
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
    // Go down the path to find out instances of rdModel
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
   * getSelectedModel: Finds out the rdModel for the selected object by
   * traversing the tree path of the selected tree node and checking if it
   * corresponds to an rdModel object
   *
   * @param path TreePath
   * @return rdModel
   */
  rdModel getSelectedModel(TreePath path) {
    // Go down the path to find out instances of rdModel
    int pathLength = path.getPathCount();
    for( int i=0; i <= pathLength -1; i++){
      DefaultMutableTreeNode selNode = (DefaultMutableTreeNode) selPath.getPathComponent(i);
      Object selObj = selNode.getUserObject();
      if (selObj instanceof rdModel){
        return (rdModel) selObj;
      }
    }
    return null;
  }
}
