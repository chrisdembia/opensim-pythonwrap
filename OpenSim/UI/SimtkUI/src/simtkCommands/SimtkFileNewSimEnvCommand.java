package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;

public class SimtkFileNewSimEnvCommand
    extends SimtkCommand {

  public SimtkFileNewSimEnvCommand() {
    super();
    putValue(Action.NAME, "New Environment");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Create new Simulation Environment");
    putValue(Action.LONG_DESCRIPTION, "Create new Simulation Environment, load entities interactively");

   }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
    super.setCommandParams(params);
   }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkFileNewSimEnvCmd";
  }

  public boolean execute() {
  boolean success = true;
  SimtkDB.getInstance().createNewSimEnv();
  return success;
}

}
