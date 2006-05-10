package simtkCommands;

import javax.swing.Action;

public class SimtkVisGouraudShadedCommand  extends SimtkVisChangeCommand{
  public SimtkVisGouraudShadedCommand() {
    super();
    putValue(Action.NAME,  "Gouraud Shade");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
    setProperty(GOURAUD_SHADED);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisGouraudShadedCmd";
  }
}
