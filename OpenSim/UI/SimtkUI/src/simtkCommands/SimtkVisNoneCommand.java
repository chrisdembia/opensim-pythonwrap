package simtkCommands;

import javax.swing.Action;

public class SimtkVisNoneCommand  extends SimtkVisChangeCommand {
  public SimtkVisNoneCommand() {
    super();
    putValue(Action.NAME,  "None");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(NONE);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
   return "SimtkVisNoneCmd";
  }
}
