package simtkCommands;

/**
 * <p>Title: Command</p>
 *
 * <p>Description: Common interface for all commands to be executed by the
 * simtkUI</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */
import java.awt.event.ActionEvent;
import java.util.HashMap;
import java.util.Observable;
import java.util.Observer;

import javax.swing.AbstractAction;
import javax.swing.AbstractButton;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 *
 * @author Ayman Habib
 * @version 1.0
 *
 *   Base class for all commands to be executed within the Simtk UI framework.
 *   It encapsulates actions to be performed by user interface in compliace
 *   with the command pattern (UI does not execute actions directly but creates
 *   an object of this type that executes the action later).
 *
 */
public abstract class SimtkCommand extends AbstractAction implements Observer{

  protected HashMap _cmdParams = new HashMap(4); // Handy place for commands to store params

  /**
   * setCommandParams sets the values of all the parameters needed for the
   * command to execute. To be used for playing back from a file or when
   * executing commands not directly from UI-button (e.g. short-cuts from right
   * mouse clicks or from tree)
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params)
  {
    _cmdParams.putAll(params);
  }

  /**
   * addCommandParam adds a key, value pair to parameters needed for the
   * command to execute.
   *
   * @param parmName Parameter name
   * @param parmValue Parameter Value
   */
  public void addCommandParam(String parmName, Object parmValue)
  {
    if (!_cmdParams.containsKey(parmName))
      _cmdParams.put(parmName, parmValue);
  }


  /**
   * canUndo function states if a command is undoable or not.
   *
   * @return boolean default is false
   */
  public boolean canUndo()
  {
    return false;
  }

  /**
   * getCommandName a function to get the name of the command. Made abstract to
   * force users to give names to commands.
   *
   * @return String
   */
  public abstract String getCommandName();

  /**
   * isBackgroundCmd is provided to allow commands to indicate if they NEED to block
   * the UI or not. Some commands may be costly to execute and these should override
   * the default behavior provided which is to return false.
   *
   * @return boolean
   */
  public boolean isBackgroundCmd()
  {
    return false;
  }
  /**
   * preExecute: Actions to be done before actual actual execution.
   * Commands overriding this method must call super.preExecute() to
   * get the default behavior
   */
  public void preExecute() { // Common preExecute activities
   };

  /**
   * postExecute: Actions to be done post command execution. This can
   * potentially disable other commands (e.g. can't undo after an undoable
   * command is executed)
   */
  public void postExecute() { // Common postExecute activities
    CommandFactory.logCommand(this);
  };

  /**
   * execute: Normally a command takes parameters to execute but incase it
   * doesn't or these parameters are already set using setCommandParams then execute
   * is invoked. Note that this function should never be executed directly.
   */
  public abstract boolean execute() ;

  /**
   * actionPerformed is provided here and made final so that it cannot be
   * overriden in derived classes and so that command execution can only go
   * through the execute mechanism.
   *
   * @param e ActionEvent
   */
  final public void actionPerformed(ActionEvent e) {
    AbstractButton item = (AbstractButton) e.getSource();
    // Get actual command from item and dispatch it
    ExecutionManager.executeCommand((SimtkCommand)item.getAction());
  }

  /**
   * whenAvailable is a function to be implemented by commands that need to be
   * conditionally enabled. default is always available
   *
   * @return boolean
   */
  public boolean whenAvailable() {
    return true;
  }
  /**
   * update for Observer interface to be overriden by commands that need to behave as observers
   * some examples: undo/redo observe executionManager to make themselves available
   * model-save/model-snapShot/model-close observe database to enable themselves when there's a loaded model
   *
   * @param o Observable
   * @param arg Object
   */
  public void update(Observable o, Object arg) {
    setEnabled(whenAvailable());
    return;
  }

  /**
   * isObserver: indicates that the command will observe the database and get notified with database events
   *
   * @return boolean
   */
  public boolean isObserver() {
    return false;
  }

  /**
    * isTopLevel: Command is associated with Top level menu item or toolbar
    *
    * @return boolean
    */
  public boolean isTopLevel() {
    return false;
  }

  /**
   * CloneCommand: clones a SimtkCommand and returns a copy. Note that this's a base class method so any data members
   * at concrete command level will not be cloned here. Commands should exclusively use _cmdParams to maintain their
   * state and they should recover the data from there. That's why commands can work from scripts which have access
   * to nothing but the command params
   *
   * @return SimtkCommand
   */
  public SimtkCommand CloneCommand() {
    try {
      SimtkCommand clone = CommandFactory.getCommand(getCommandName());
       clone._cmdParams.putAll(this._cmdParams);
      return clone;
    }
    catch (CommandFactoryException ex) {
    }
    return null;
  }

  /**
   * cleanUp
   */
  public void cleanUp() {
    _cmdParams.clear();
  }
}
