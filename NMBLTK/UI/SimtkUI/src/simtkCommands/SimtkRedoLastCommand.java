package simtkCommands;

import javax.swing.Action;

public class SimtkRedoLastCommand
    extends SimtkCommand {
  public SimtkRedoLastCommand() {
    super();
    putValue(Action.NAME, "Redo");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Redo last undone command");
    setEnabled(true);
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkRedoLastCmd";
  }

  public boolean isBackgroundCmd()
 {
   return false;
 }

 public boolean execute() {
  return true;
 }

 public boolean whenAvailable() {
   return false;
 }
 /**
  * update for Observer interface
  *
  * @param o Observable
  * @param arg Object
  */
 public void update(java.util.Observable o, Object arg) {
   setEnabled(!((ExecutionManager) o).isRedoStackEmpty());
   return;
 }
}
