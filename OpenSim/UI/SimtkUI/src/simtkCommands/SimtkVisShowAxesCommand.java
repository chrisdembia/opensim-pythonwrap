package simtkCommands;

import javax.swing.Action;

public class SimtkVisShowAxesCommand extends SimtkVisChangeCommand{
  public SimtkVisShowAxesCommand() {
    super();
    putValue(Action.NAME,  "Show Axes");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(SHOW_GEOM_CS);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisShowAxesCmd";
  }
}
