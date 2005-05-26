package simtkCommands;

import javax.swing.Action;

import simtkView.plot.SimtkPtPlotDialog;
/**
 * <p>Title: UI for Simtk Prototype</p>
 * <p>Description: UI for Simtk Prototype</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: Stanford University</p>
 * @author not attributable
 * @version 1.0
 */

public class SimtkGrapherCommand extends SimtkCommand {
  public SimtkGrapherCommand() {
    putValue(Action.NAME, "Plot");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Plot quantities");
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    SimtkPtPlotDialog plotDlg = new SimtkPtPlotDialog();
    plotDlg.pack();
    plotDlg.setVisible(true);
    return true;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkGrapherCmd";
  }

}
