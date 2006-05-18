package simtkView;

import java.awt.event.ActionEvent;
import java.util.HashMap;

import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

import simtkCommands.CommandFactory;
import simtkCommands.CommandFactoryException;
import simtkCommands.ExecutionManager;
import simtkCommands.SimtkCommand;
import opensimModel.VisibleObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author not attributable
 * @version 1.0
 * Currently unused but intended to encapsulate all the visibility menus so that
 * the same code is excercised either from the Modeltree UI or from picking on
 * the gfx window.
 */
public class SimtkVisMenu extends JMenu {
  private final String _availableVisProperties[] = {
      "WireFrame",
      "Flat-Shaded",
      "Gouraud-Shaded",
      "BoundingBox",
      "None",
      "Color & Effects"
  };
  // These are grouped in pairs that are mutually exclusive
  private final String contextDependentProperties[] = {
      "ShowNormals",
      "HideNormals",
      "ShowAxes",
      "HideAxes"
  };
  private final String correspondingCommands[] = {
      "SimtkVisWireFrameCmd",
      "SimtkVisFlatShadedCmd",
      "SimtkVisGouraudShadedCmd",
      "SimtkVisBoundingBoxCmd",
      "SimtkVisNoneCmd",
      "SimtkObjectVisibilityCmd"
  };
  private final String correspondingOptionalCommands[] = {
      "SimtkVisShowNormalsCmd",
      "SimtkVisHideNormalsCmd",
      "SimtkVisShowAxesCmd",
      "SimtkVisHideAxesCmd"
  };
  private VisibleObject _selectedObject=null;
  private String _mdlName=null;

  public SimtkVisMenu(String menuName, String mdlName, VisibleObject selectedObject)
  {
    super(menuName);
    _mdlName = mdlName;
    _selectedObject = selectedObject;
    for (int i = 0; i < _availableVisProperties.length; i++) {
      JMenuItem nextMenuItem = new JMenuItem(new ChangeVisibility(_availableVisProperties[i]));
      add(nextMenuItem);
    }
    for(int j=0; j < contextDependentProperties.length; j++){
      if (optionValidForObject(contextDependentProperties[j], _selectedObject)){
        JMenuItem nextMenuItem = new JMenuItem(new ChangeVisibility(
            contextDependentProperties[j]));
        add(nextMenuItem);
      }
    }
  }

  /**
   * optionValidForObject: Some options may not be valid for object type (e.g.
   * CS of a musclePoint) some others are not valid becuase of context (e.g.
   * showNormals while normals are already shown)
   *
   * @param visOption String
   * @param vObject VisibleObject
   * @return boolean
   */
  boolean optionValidForObject(String visOption, VisibleObject vObject)
  {
    if (vObject == null)// No actual object was selected
      return false;

    if (vObject.getVisibleProperties().getShowNormals() && visOption == "ShowNormals")
      return false;
    if (!vObject.getVisibleProperties().getShowNormals() && visOption == "HideNormals")
      return false;
    if (vObject.getVisibleProperties().getShowAxes() && visOption == "ShowAxes")
      return false;
    if (!vObject.getVisibleProperties().getShowAxes() && visOption == "HideAxes")
      return false;
    return true;
  }
  /**
   * Inner class for Visibility control.
   */
  private class ChangeVisibility extends AbstractAction {

    ChangeVisibility(String StyleName) {
      super(StyleName);
    }

    /**
     * actionPerformed
     *
     * @param e ActionEvent
     */
    public void actionPerformed(ActionEvent e) {
      boolean commandFound = false;
      for(int i=0; i < _availableVisProperties.length; i++){
        if (e.getActionCommand()==_availableVisProperties[i]){
          commandFound = true;
          if (_selectedObject != null){
            // Build a command that will change property and fire event to update views
            SimtkCommand changeDisplayCommand = null;
            try {
              changeDisplayCommand = CommandFactory.getCommand(
                  correspondingCommands[i]);
              HashMap params = new HashMap(4);
              params.put("ModelName", _mdlName);
              params.put("Object", _selectedObject);
              params.put("ObjectName", _selectedObject.getName());
              changeDisplayCommand.setCommandParams(params);
              ExecutionManager.enQueueCommand(changeDisplayCommand);
            }
            catch (CommandFactoryException ex) {
            }
          }
          break;
        }
      }
      if (!commandFound){// Now try optional commands
        for(int i=0; i < contextDependentProperties.length; i++){
          if (e.getActionCommand()==contextDependentProperties[i]){
            commandFound = true;
            if (_selectedObject != null){
              // Build a command that will change property and fire event to update views
              SimtkCommand changeDisplayCommand = null;
              try {
                changeDisplayCommand = CommandFactory.getCommand(
                    correspondingOptionalCommands[i]);
                HashMap params = new HashMap(4);
                params.put("ModelName", _mdlName);
                params.put("Object", _selectedObject);

                changeDisplayCommand.setCommandParams(params);
                ExecutionManager.enQueueCommand(changeDisplayCommand);
              }
              catch (CommandFactoryException ex1) {
              }
            }
            break;
          }
        }
      }
    }
  }
}
