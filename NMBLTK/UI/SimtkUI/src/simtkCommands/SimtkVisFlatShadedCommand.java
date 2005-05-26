package simtkCommands;

import javax.swing.Action;

public class SimtkVisFlatShadedCommand  extends SimtkVisChangeCommand {
  public SimtkVisFlatShadedCommand() {
    super();
    putValue(Action.NAME, "Flat Shade");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    setProperty(FLAT_SHADED);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisFlatShadedCmd";
  }
}
