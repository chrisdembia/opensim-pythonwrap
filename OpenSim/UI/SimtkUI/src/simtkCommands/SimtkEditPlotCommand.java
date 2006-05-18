package simtkCommands;

import javax.swing.Action;
import simtkView.plot.*;
import opensimModel.*;

public class SimtkEditPlotCommand
    extends SimtkModelObjectCommand {
  public SimtkEditPlotCommand() {
    super();
    putValue(Action.NAME, "Graphical Edit");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Launch Graphical Editor");
    setEnabled(true);
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    boolean success = true;
    SimtkEditPlotDialog dlg = new SimtkEditPlotDialog((Control)this.getObject());
    dlg.pack();
    dlg.setVisible(true);
    return success;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkEditPlotCmd";
  }
}
