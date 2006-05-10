package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;
import javax.swing.JOptionPane;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkView.SimtkViewDB;
import simtkui.SimtkApp;

public class SimtkFileCloseCommand extends SimtkCommand {
  String _fileName;
  /**
   * SimtkFileCloseCommand. Default constructor to be used to add Commands to
   * commandTable
   */
  public SimtkFileCloseCommand() {
    super();
    putValue(Action.NAME, "Close Model");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Close current model window");
  }

//  public void postExecute() {
//    SimtkDB.getInstance().removeModel(SimtkViewDB.getCurrentModelName());
//  }
  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
     super.setCommandParams(params);
    _fileName = (String) params.get("FileName");
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
    return "SimtkFileCloseCmd";
  }

  /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {

    String mdlToClose =  _cmdParams.containsKey("ModelName")? (String) _cmdParams.get("ModelName") : SimtkViewDB.getCurrentModelName();

    if(mdlToClose==null){
      JOptionPane.showMessageDialog(SimtkApp.getTopComponent(),
                                    "There is no current model to close",
                                    "Info.",
                                    JOptionPane.INFORMATION_MESSAGE);
      return false;
    }

    // Keep model name around for logging purposes
    _cmdParams.put("ModelName", mdlToClose);

    if (mdlToClose != null){
      if (SimtkDB.getInstance().needToSave(mdlToClose)){
        int userConfirm = JOptionPane.showConfirmDialog(SimtkApp.
            getTopComponent(),
            "Model " + mdlToClose +
            " has not been saved. Do you want to close and discard changes?",
                                "Confirmation",
                                JOptionPane.OK_CANCEL_OPTION);
        if (userConfirm == JOptionPane.OK_OPTION){
          SimtkSimEnv simEnv = SimtkDB.getInstance().getEnvForModel(mdlToClose);
          SimtkDB.getInstance().removeSimEnv(simEnv);
          return true;
        }
        else
          return false;
      }
      else { // Model has not changed. Just close it
        SimtkSimEnv simEnv = SimtkDB.getInstance().getEnvForModel(mdlToClose);
        SimtkDB.getInstance().removeSimEnv(simEnv);
        return true;
      }
    }
    return false;
  }

  /**
   * whenAvailable override to tell the system that this command is
   * conditionally available
   *
   * @return boolean
   */
  public boolean whenAvailable() {
    return (SimtkDB.getInstance().getNumberOfModels() > 0);
  }

  /**
   * isObserver is overloaded to tell the system that this command is
   * conditionally available based on system events. The function whenAvailable()
   * is re-evaluated when database event is generated.
   *
   * @return boolean
   */
  public boolean isObserver()
  {
    return true;
  }
}
