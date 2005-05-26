package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;

public class SimtkFileHelpCommand
    extends SimtkCommand {
  public SimtkFileHelpCommand() {
    super();
    putValue(Action.NAME, "Help");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Display main help dialog");
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkFileHelpCmd";
  }

  public boolean isBackgroundCmd()
 {
   return true;
 }

 public boolean execute() {
  return true;
 }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
  }
}
