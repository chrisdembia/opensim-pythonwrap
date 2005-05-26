package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;
import javax.swing.JOptionPane;

import simtkCore.SimtkDB;
import simtkui.SimtkApp;

public class SimtkFileExitCommand extends SimtkCommand{
  /**
   * SimtkFileExitCommand. Default constructor used to add entries to command
   * table and set initial availability
   */
  public SimtkFileExitCommand() {
    super();
    putValue(Action.NAME, "Exit");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Exit Application");
    setEnabled(true);
   }

  public void postExecute() {
    // Flush log files
    CommandFactory.logCommand(this);
    CommandFactory.flushCommandLogFile();
    System.exit(0);
  }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
  }

  /**
   * canUndo
   *
   * @return boolean
   */
  public boolean canUndo() {
    return false;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkFileExitCmd";
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    if (SimtkDB.getInstance().confirmOnExit()){
      int userConfirm = JOptionPane.showConfirmDialog(SimtkApp.getTopComponent(),
                                    "Some model changes has not been saved. Do you want to exit?",
                                    "Confirmation",
                                    JOptionPane.OK_CANCEL_OPTION);
      return (userConfirm==JOptionPane.OK_OPTION);
    }
    return true;
  }
}
