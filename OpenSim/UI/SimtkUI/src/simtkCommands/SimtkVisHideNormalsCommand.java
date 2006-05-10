package simtkCommands;

import javax.swing.Action;

public class SimtkVisHideNormalsCommand
    extends SimtkVisChangeCommand{
  public SimtkVisHideNormalsCommand() {
    super();
    putValue(Action.NAME,  "Hide Normals");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(HIDE_NORMALS);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisHideNormalsCmd";
  }
}
