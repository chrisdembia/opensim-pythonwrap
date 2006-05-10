package simtkCommands;

import javax.swing.Action;

public class SimtkPlotCommand extends SimtkCommand {
  public SimtkPlotCommand() {
    super();
    putValue(Action.NAME, "Plot");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Launch plotter");
    setEnabled(true);
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    boolean success = true;
    //simtkGrapher.launcher.launch();
    return success;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkPlotCmd";
  }
}
