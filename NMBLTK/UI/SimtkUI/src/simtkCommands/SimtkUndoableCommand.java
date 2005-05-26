package simtkCommands;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 * SimtkUndoableCommand is the base class for all commands in the system that
 * are undoable. It defines methods that need to be implemented by a command to
 * support the undo Operation.
 *
 * @todo convert this class into an abstract interface in order not to branch the class
 * hierarchy early on
 */
abstract public interface SimtkUndoableCommand {
  /**
   * canUndo: Is implemented here so that undoable commands
   * can return true from this call. Since SimtkUndoableCommand is an interface
   * this method cannot have a body. So the function should be implemented by undoable commands.
   *
   * @return boolean
   */
  abstract public boolean canUndo();

  /**
   * undo: is the reverse-execute function that needs to be implemented by all
   * undoable commands. Once we start implementing undoable commands we may beef up this interface
   * so that the execution manager's task of undoing is more efficient.
   * For example we can mark some commands as lossy and in this case we must undo/redo using snapshots
   * Other commands may have an easy way to describe how to revert themselves. Ultimately the responsiblity
   * lies in the hands of the command writer to make undo possible and/or efficient.
   */
  abstract public boolean undo();

  /**
   * saveState is the method that saves the state that's going to be changed by
   * the command so that it can be recovered. It corresponds to the memento (in the memento pattern)
   *  The undo mechanism is resposnsible  for maintaining the state and passing it back to the command undo
   *
   * @return Object
   */
  abstract public void saveState();

}
