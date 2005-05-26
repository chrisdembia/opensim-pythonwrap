package simtkCommands;

import javax.swing.Action;

public class SimtkVisWireFrameCommand extends SimtkVisChangeCommand{
  public SimtkVisWireFrameCommand() {
    super();
    putValue(Action.NAME,  "Wireframe");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(WIREFRAME);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisWireFrameCmd";
  }
}
