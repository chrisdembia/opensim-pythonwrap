package simtkCommands;

import javax.swing.Action;

public class SimtkVisBoundingBoxCommand  extends SimtkVisChangeCommand {
  public SimtkVisBoundingBoxCommand() {
    super();
    putValue(Action.NAME,  "Bounding Box");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
     setProperty(BOUNDING_BOX);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkVisBoundingBoxCmd";
  }
}
