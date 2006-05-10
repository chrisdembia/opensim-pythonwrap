package simtkCommands;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkui.SimtkSimulationSetupDlg;

public class SimtkSimulationSetupCommand
    extends SimtkCommand{
  /**
   * SimtkSimulationStartCommand. Default constructor used to add entries to command
   * table and set initial availability
   */
  public SimtkSimulationSetupCommand() {
    super();
    putValue(Action.NAME, "Setup");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Setup Simulation");
    setEnabled(true);
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
    return "SimtkSimulationSetupCmd";
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    boolean success = true;
    // Make sure there's a model
    String simenvName = (String) _cmdParams.get("EnvName");
    SimtkSimEnv currentEnv = SimtkDB.getInstance().getSimtkSimEnv(simenvName);
    // Show dialog to edit simulation environment properties
    SimtkSimulationSetupDlg simulationSetupDlg = new SimtkSimulationSetupDlg(
        currentEnv);
    simulationSetupDlg.pack();
    simulationSetupDlg.center();
    simulationSetupDlg.setVisible(true);

    // We don't need the dialog any more
    simulationSetupDlg.dispose();

    boolean retValue = true;
    return retValue;
  }
  /**
   * whenAvailable override to tell the system that this command is
   * conditionally available
   *
   * @return boolean
   */
  public boolean whenAvailable() {
    String simenvName = (String) _cmdParams.get("EnvName");
    if (simenvName==null)
      return true;
   return (SimtkDB.getInstance().getSimtkSimEnv(simenvName).getStatus()==SimtkSimEnv.READY);
  }

  /**
   * isObserver is overloaded to tell the system that the command is
   * conditionally available based on system events
   *
   * @return boolean
   */
  public boolean isObserver() {
    return true;
  }
}
