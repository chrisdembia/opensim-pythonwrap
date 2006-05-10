package simtkCommands;

import java.util.LinkedList;
import java.util.Observable;
import java.util.Observer;

import simtkUtils.SwingWorker;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * @todo: Look into making ExecutionManager live on its own thread.
 *
 * @author Ayman Habib
 * @version 1.0 Execution Manager is the class responsible for
 *   dispatching/executing commands. It communicates with the command factory to
 *   customize its behavior, maintains a stack (implemented as a linkedlist) of
 *   undoable commands that gets flushed when a command that's not undoable is executed.
 *
 * The reason ExecutionManager extends Observable is only to allow for
 *     enabling/disabling of undo/redo buttons based
 *     on the status of the last executed command
 */
final public class ExecutionManager extends Observable implements Observer {
  static CommandFactory _commandFactory;
  static ExecutionManager _dInstance;
  static SimtkCommandQueue _commandQue = new SimtkCommandQueue();
  static private boolean _commandPlayBackOn = false;    // Commands are played back from an external command file
  static private boolean _undoAvailable = false;
  static private boolean _redoAvailable = false;

  static private String _commandLogFileName="CommandLogFile.log";
  /**
   * Both _historyList (undo) and _redoList are implemented a slinkedlists for efficiency
   * their use is primarily as a stack because that's the nature of the undo/redo functionality
   * operating on last command. Only exception is if/when we have a limited list of commands to keep
   * in our history then we can remove items from
   */
  static LinkedList _historyList = new LinkedList();
  static LinkedList _redoList = new LinkedList();

  public ExecutionManager() {
    _commandFactory = CommandFactory.getInstance();
    _commandFactory.turnCommandLogginOn(_commandLogFileName);
    _dInstance = this;
    _commandQue.addObserver(_dInstance);
  }

  /**
   * executeCommand: Lowest level and single place where command execution is
   * dispatched
   *
   * @param cmd SimtkCommand
   */
  public static void executeCommand(final SimtkCommand cmd)
  {
    // If command is undo then just do it here */
    if (cmd instanceof SimtkUndoLastCommand){
      undoLast();
      cmd.postExecute();// Log the operation
      _dInstance.fireUndoRedoAvailableEvent();
      return;
    }
     // Same if redo
    if (cmd instanceof SimtkRedoLastCommand){
      redoLast();
      cmd.postExecute();// Log the operation
      _dInstance.fireUndoRedoAvailableEvent();
      return;
    }
    // Commands assigned to the top level menus and buttons don't get new'ed every time they're used
    // similar to other commands created dynamically. To work around this problem
    // (which can cause subsequent invokations of the command to reuse params from previous call)
    // we create a clone of the command and cleanup params of original command to prep for next invokation
    /** @todo look into alternative mechanism to get this done */
    SimtkCommand dCommand = cmd;
    if (cmd.isTopLevel()){
      dCommand = cmd.CloneCommand();
      cmd.cleanUp();
    }
    // Generic command
    if (!dCommand.isBackgroundCmd() || _commandPlayBackOn) { // command executes on the same GUI thread
      dCommand.preExecute();
      if (dCommand.canUndo()) {
         // May also need to save a memento here for later retrieval
         if (dCommand instanceof SimtkUndoableCommand){
           ((SimtkUndoableCommand)dCommand).saveState();
           _historyList.addFirst(dCommand);
         }
     }
      else { // Flush undo stack and disable undo button
        _historyList.clear();
        _redoList.clear();
        _dInstance.fireUndoRedoAvailableEvent();
      }
      // execute
      if (dCommand.execute()) {
        dCommand.postExecute();
        _dInstance.fireUndoRedoAvailableEvent();
      }
      else { // Command actually failed, pop and throw away whatever state that was saved
        if (dCommand.canUndo()) {
          _historyList.removeFirst();
          _dInstance.fireUndoRedoAvailableEvent();
       }
      }
    }
    else {
      // Background command to be started on its own thread. Can't be undone
      SwingWorker workerThread = new SwingWorker() {
        /**
         * construct
         *
         * @return Object
         */
        public Object construct() {
          { // This block must be synchronized
            synchronized(this) {
              _historyList.clear();
              _redoList.clear();
            }
            _dInstance.fireUndoRedoAvailableEvent();
          }
          cmd.execute();
          cmd.postExecute();
          _dInstance.fireUndoRedoAvailableEvent();
          return null;
        }

        public void finished() {
        }

      };
      workerThread.start();
    }
  }

  synchronized public static void undoCommand()
  {
    if (!_historyList.isEmpty()){
      SimtkCommand cmd = (SimtkCommand) _historyList.removeFirst();
      ((SimtkUndoableCommand)cmd).undo();
    }
  }
  /**
   * enQueueCommand: adds specified command to the end of the commandQueue
   *
   * @param cmd SimtkCommand
   */
  public static void enQueueCommand(SimtkCommand cmd)
  {
    _commandQue.enQueue(cmd);
  }

  /**
   * getInstance returns the one single instance of the command manager
   *
   * @return ExecutionManager
   */
  public static ExecutionManager getInstance()
  {
    return _dInstance;
  }

  /**
   * update is the callback that gets executed when something is changed in the
   * command queue normally by adding commands to the commandQueue.
   *
   * @param o Observable is the commandQueue
   * @param arg Object is an abstraction of the change that triggered the
   *   callback
   */
  public void update(Observable o, Object arg) {
    SimtkCommand act = (SimtkCommand) _commandQue.deQueue();
    executeCommand(act);
  }

  /**
   * isUndoStackEmpty: Get the status of the undoStack.
   *
   * @return boolean
   */
  public boolean isUndoStackEmpty(){
    return _historyList.isEmpty();
  }

  /**
   * isRedoStackEmpty: gets the status of the redo list
   *
   * @return boolean
   */
  public boolean isRedoStackEmpty(){
    return _redoList.isEmpty();
  }

  /**
   * undoLast: undo the last command that was executed
   */
  private static void undoLast(){
    // Get undoable command at top of _historyList
    if (_historyList.isEmpty())
      return;
    SimtkCommand uCmd  = (SimtkCommand) _historyList.removeFirst();
    ((SimtkUndoableCommand)uCmd).undo();
    _redoList.addFirst(uCmd);
  }

  /**
   * redoLast: execute last command that was undone
   */
  private static void redoLast(){
    // Get undoable command at top of _historyList
    if (_redoList.isEmpty())
      return;
    SimtkCommand uCmd  = (SimtkCommand) _redoList.removeFirst();
    uCmd.execute();
   _historyList.addFirst(uCmd);
  }

  /**
   * fireUndoRedoAvailableEvent: Fires events to tell the undo/redo command
   * buttons if they should be enabled or not.
   *
   * @todo remove the Evnts altogether as the observers now query the state of
   * the executionManager directly
   */
  private void fireUndoRedoAvailableEvent(){
    if (_historyList.isEmpty()){
      if (_undoAvailable == true){
        _undoAvailable = false;
        ExecutionManagerCantUndoEvnt cantUndoEvnt = new
            ExecutionManagerCantUndoEvnt(Boolean.TRUE);
        _dInstance.setChanged();
        _dInstance.notifyObservers(cantUndoEvnt);
      }
    }
    else {
      if (_undoAvailable==false){
        _undoAvailable = true;
        ExecutionManagerCantUndoEvnt cantUndoEvnt = new
            ExecutionManagerCantUndoEvnt(Boolean.FALSE);
        _dInstance.setChanged();
        _dInstance.notifyObservers(cantUndoEvnt);
      }
   }
    if (_redoList.isEmpty()){
      if (_redoAvailable == true){
        _redoAvailable = false;
        ExecutionManagerCantRedoEvnt cantRedoEvnt = new
            ExecutionManagerCantRedoEvnt(Boolean.TRUE);
        _dInstance.setChanged();
        _dInstance.notifyObservers(cantRedoEvnt);
      }
    }
    else {
      if (_redoAvailable == false){
        _redoAvailable = true;
        ExecutionManagerCantRedoEvnt cantRedoEvnt = new
            ExecutionManagerCantRedoEvnt(Boolean.FALSE);
        _dInstance.setChanged();
        _dInstance.notifyObservers(cantRedoEvnt);
      }
    }
  }

  /**
   * playBackOn: Tells the ExecutionManager that it's playing back commands from
   * a file rather than live. Relevent only to background commands as they're
   * executed in foreground when playing back from a file since downstream
   * commands may have dependencies on them (for example running a simulation in
   * background then trying to show results works only after the simulation is done so we
   * do it in the Gui thread.).
   */
  public static void playBackOn()
  {
    _commandPlayBackOn = true;
  }

  public static void playBackOff()
 {
   _commandPlayBackOn = false;
 }

  /**
   * getLogfileName: get the name of the log file to be used
   *
   * @return String
   */
  public static final String getLogfileName() {
   return _commandLogFileName;
 }
}
