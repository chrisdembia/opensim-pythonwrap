package simtkCommands;

import javax.swing.Action;

public class SimtkVisShowNormalsCommand extends SimtkVisChangeCommand{
  public SimtkVisShowNormalsCommand() {
    super();
    putValue(Action.NAME,  "Show Normals");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(SHOW_NORMALS);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisShowNormalsCmd";
  }
}
