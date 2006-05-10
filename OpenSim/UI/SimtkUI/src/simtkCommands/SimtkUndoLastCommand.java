package simtkCommands;

import javax.swing.Action;

public class SimtkUndoLastCommand
    extends SimtkCommand {
  public SimtkUndoLastCommand() {
    super();
    putValue(Action.NAME, "Undo");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Undo last command");
    setEnabled(true);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkUndoLastCmd";
  }

  public boolean isBackgroundCmd()
 {
   return false;
 }

 public boolean execute() {
   return true;
 }

 public boolean whenAvailable() {
   return (false);
 }
 /**
  * update for Observer interface
  *
  * @param o Observable
  * @param arg Object
  */
 public void update(java.util.Observable o, Object arg) {
   setEnabled(!((ExecutionManager) o).isUndoStackEmpty());
   return;
 }
}
