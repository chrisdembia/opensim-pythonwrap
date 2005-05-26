package simtkCommands;

import javax.swing.Action;

public class SimtkVisHideAxesCommand
    extends SimtkVisChangeCommand{
  public SimtkVisHideAxesCommand() {
    super();
    putValue(Action.NAME,  "Hide Axes");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(HIDE_GEOM_CS);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisHideAxesCmd";
  }
}
