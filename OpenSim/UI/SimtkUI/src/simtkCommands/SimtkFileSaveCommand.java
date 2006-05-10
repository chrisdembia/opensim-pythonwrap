package simtkCommands;

import javax.swing.Action;
import javax.swing.JOptionPane;

import simtkCore.SimtkDB;
import simtkView.SimtkViewDB;
import simtkui.SimtkApp;

public class SimtkFileSaveCommand extends SimtkCommand {
  public SimtkFileSaveCommand() {
    super();
    putValue(Action.NAME, "Save");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Save current model");
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkSaveModelCmd";
  }

   /**
   * execute
   *
   * @return boolean
   */
  public boolean execute() {
    // Get current model name from View
    String mdlToSave = SimtkViewDB.getCurrentModelName();

    if (mdlToSave==null){// No current model to save
      JOptionPane.showMessageDialog(SimtkApp.getTopComponent(),
                                   "There is no current model to save.",
                                   "Info",
                                   JOptionPane.INFORMATION_MESSAGE);
     return true;

    }
  // If model doesn't need to be saved, warn user of no change and return;
   if (!SimtkDB.getInstance().needToSave(mdlToSave)){
     JOptionPane.showMessageDialog(SimtkApp.getTopComponent(),
                                   "Model " + mdlToSave +
                                   " has not been changed since last saved.",
                                   "Info",
                                   JOptionPane.INFORMATION_MESSAGE);
     return true;
   }
   // Here a model will really be saved.
   return SimtkDB.getInstance().saveModel(mdlToSave);
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
   * isObserver is overloaded to tell the system that the command is
   * conditionally available based on system events
   *
   * @return boolean
   */
  public boolean isObserver()
  {
    return true;
  }
}
