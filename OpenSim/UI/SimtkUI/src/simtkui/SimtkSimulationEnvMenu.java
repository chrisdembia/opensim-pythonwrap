package simtkui;

import java.util.HashMap;

import javax.swing.JMenuItem;

import simtkCommands.CommandFactory;
import simtkCommands.CommandFactoryException;
import simtkCommands.SimtkCommand;
import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkui.guiUtilities.SimtkJMenu;

/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */

public class SimtkSimulationEnvMenu extends SimtkJMenu {
  private final String _defaultCommands[] = {
      "SimtkFileOpenByNameCmd",
      "SimtkLoadControlSetCmd",
      "SimtkLoadContactSetCmd",
      "SimtkLoadActuatorSetCmd",
      "SimtkLoadStorageCmd"
  };
  private String _simEnvName = null;
  public SimtkSimulationEnvMenu(String menuName, String simEnvName) {
    super(menuName);
    _simEnvName = simEnvName;
    SimtkSimEnv currentEnv = SimtkDB.getInstance().getSimtkSimEnv(_simEnvName);
    for (int i = 0; i < _defaultCommands.length; i++) {
      SimtkCommand nextCommand = populateCommand(_defaultCommands[i]);
      JMenuItem nextMenuItem = new JMenuItem(nextCommand);
      // Control set needs a model loaded
      if (i==1 && currentEnv.getModel()==null)
        nextCommand.setEnabled(false);
      add(nextMenuItem);
    }
  }
  /**
   * populateCommand, fills in command parameters from current selected model
   * and object
   *
   * @param mdlName String
   * @param selectedObject OpenSimObject
   * @param commandName String
   * @return Object
   */
  private SimtkCommand populateCommand(String commandName) {
    SimtkCommand command = null;
      // Build a command that will do the work
      try {
        command = CommandFactory.getCommand(commandName);
        HashMap params = new HashMap(4);
        params.put("EnvName", _simEnvName);
        command.setCommandParams(params);
        // Call update to enable command since env. is set
        command.update(null, null);
      }
      catch (CommandFactoryException ex) {
        SimtkApp.displayErrorMessage("Command " + commandName+ " could not be found.. Ignored");
      }

    return command;
  }

}
