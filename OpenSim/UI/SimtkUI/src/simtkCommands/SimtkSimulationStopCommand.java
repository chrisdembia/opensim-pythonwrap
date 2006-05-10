package simtkCommands;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;

public class SimtkSimulationStopCommand
    extends SimtkCommand{
  /**
   * SimtkSimulationStopCommand. Default constructor used to add entries to command
   * table and set initial availability
   */
  public SimtkSimulationStopCommand() {
    super();
    putValue(Action.NAME, "Stop");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Abort Simulation");
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
    return "SimtkSimulationStopCmd";
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    String simenvName = (String) _cmdParams.get("EnvName");
    SimtkSimEnv currentEnv = SimtkDB.getInstance().getSimtkSimEnv(simenvName);
    if (currentEnv.getSimulationThread()!=null)
      currentEnv.getIntegrator().halt();
    currentEnv.setProgressRange(0.0, 0.0);
    currentEnv.setStatus(SimtkSimEnv.READY);
    return true;
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
      return false;
   return (SimtkDB.getInstance().getSimtkSimEnv(simenvName).getStatus()==SimtkSimEnv.STARTED);
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
