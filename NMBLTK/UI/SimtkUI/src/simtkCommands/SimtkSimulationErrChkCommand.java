package simtkCommands;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkModel.rdManager;
import simtkui.SimtkApp;

public class SimtkSimulationErrChkCommand
    extends SimtkCommand{
  /**
   * SimtkSimulationStartCommand. Default constructor used to add entries to command
   * table and set initial availability
   */
  public SimtkSimulationErrChkCommand() {
    super();
    putValue(Action.NAME, "Error Check");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Error Check");
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
    return "SimtkSimulationErrChkCmd";
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
    rdManager mgr = currentEnv.getSimulationManager();
    // We have to have a model
    if (mgr.getModel()==null){
      SimtkApp.displayInfoMessage("No model in current Simulation Environment");
      success = false;
    }
    else if (mgr.getControlSet()==null){
      SimtkApp.displayInfoMessage("No Control Set in current Simulation Environment");
      success = false;
    }
    else if (mgr.getIntegrator()==null){
      SimtkApp.displayInfoMessage("No integrator in current Simulation Environment");
      success = false;
    }
    else
      SimtkApp.displayInfoMessage("Simulation Environment is ready to start simulation");
    return success;
  }
}
