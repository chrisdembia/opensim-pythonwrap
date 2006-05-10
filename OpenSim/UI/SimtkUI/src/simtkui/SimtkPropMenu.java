package simtkui;

import java.util.HashMap;

import javax.swing.JMenu;
import javax.swing.JMenuItem;

import simtkCommands.CommandFactory;
import simtkCommands.CommandFactoryException;
import simtkCommands.SimtkCommand;
import simtkModel.rdObject;

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
 * Intended to encapsulate all model tree originated menus so that
 * the same code is excercised either from the Modeltree UI or from picking on
 * the gfx window.
 */
public class SimtkPropMenu
    extends JMenu {
  private final String _defaultProperties[] = {
      "Review",
      "Edit",
      "Export"
  };
  private final String _defaultCommands[] = {
      "SimtkObjectReviewCmd",
      "SimtkObjectEditCmd",
      "SimtkObjectExportCmd"
  };
  private final String _contextDependentProperties[] = {
  };
  private final String _contextDependentCommands[] = {
  };
  private rdObject _selectedObject = null;
  private String _mdlName = null;

  public SimtkPropMenu(String menuName, String mdlName, rdObject selectedObject) {
    super(menuName);
    _mdlName = mdlName;
    _selectedObject = selectedObject;
    for (int i = 0; i < _defaultProperties.length; i++) {
      JMenuItem nextMenuItem = new JMenuItem(populateCommand(_defaultCommands[i]));
      add(nextMenuItem);
    }
    for (int j = 0; j < _contextDependentProperties.length; j++) {
    }
  }

  /**
   * populateCommand, fills in command parameters from current selected model
   * and object
   *
   * @param mdlName String
   * @param selectedObject rdObject
   * @param commandName String
   * @return Object
   */
  private SimtkCommand populateCommand(String commandName) {
    SimtkCommand command = null;
    if (_selectedObject != null) {
      // Build a command that will do the work
      try {
        command = CommandFactory.getCommand(commandName);
        HashMap params = new HashMap(4);
        params.put("ModelName", _mdlName);
        params.put("Object", _selectedObject);
        command.setCommandParams(params);
      }
      catch (CommandFactoryException ex) {
        SimtkApp.displayErrorMessage("Command " + commandName+ " could not be found.. Ignored");
      }
    }
    return command;
  }
}


