package simtkCommands;

/**
 * <p>Title: Command Manager/Factory</p>
 *
 * <p>Description: Management of UI commands</p>
 *
 * Menu selections, tool bar actions and callbacks from context-menus will all go thru
 * this command manager to get executed. The command manger will keep a hash table that maps
 * a command name to a command object. The name of the command needs to be qualified such that different plugins
 * can add their own commands.
 *
 * The command manager will be able to log commands to an external file as well as execute
 * commands from an external command file. Commands read/written (including those from context menus)
 * need to be qualified by model-name
 * or proper attributes to make the command
 * 1. Unique.
 * 2. Pass parameters along with the command
 *
 * The command manager is implemented as a singleton so that it can be accessed from everywhere
 * in the application without having to "new" Commands. It implements a Factory style database where
 * Clients of this class pass in the name of the command (associated with the UI-Button) and get back
 * a reference to the base class of all commands (SimtkCommand). This way Clients are shielded from the
 * specific concrete class of the command.
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Institution: Stanford University</p>
 * @author Ayman Habib
 * @version 1.0
 */
import java.io.FileWriter;
import java.io.IOException;
import java.util.Hashtable;

import javax.swing.AbstractAction;

import simtkCore.SimtkDB;
import simtkui.SimtkApp;

public class CommandFactory {

  static private boolean _commandLoggingOn = true;     // Commands are logged to an external file
  static private String _commandLogFileName ="";    // Log file to write commands
  static private Hashtable _commandTable = new Hashtable();
  static private FileWriter _commandLogFile = null;
  static private CommandFactory _instance = null;
  static private boolean _instanceFlag = false;
  static boolean _singleStep = false;

  static boolean _echoCommands = true;
  /**
   * initialize:
   * Builtin in commands are added to the hash table here. We can possibly read
   * command text from an external ResourceBundle.
   *
   * @return boolean true if initialization succeeds, false otherwise
   */
  protected boolean initialize() {
    // File menu
    insertCommand(new SimtkFileNewSimEnvCommand());
    insertCommand(new SimtkFileBrowseForModelCommand());
    insertCommand(new SimtkFileOpenByNameCommand());
    insertCommand(new SimtkFileCloseCommand());
    insertCommand(new SimtkFileExitCommand());
    insertCommand(new SimtkSnapShotCommand());
    insertCommand(new SimtkFileSaveCommand());
    insertCommand(new SimtkFileHelpCommand());
    // Plugins
    /*
    insertCommand(new SimtkWorkFlowCommand());
    insertCommand(new SimtkPlotCommand());
    */
    // Visibility control
    insertCommand(new SimtkVisWireFrameCommand());
    insertCommand(new SimtkVisFlatShadedCommand());
    insertCommand(new SimtkVisGouraudShadedCommand());
    insertCommand(new SimtkVisBoundingBoxCommand());
    insertCommand(new SimtkVisNoneCommand());
    insertCommand(new SimtkVisShowNormalsCommand());
    insertCommand(new SimtkVisHideNormalsCommand());
    insertCommand(new SimtkVisShowAxesCommand());
    insertCommand(new SimtkVisHideAxesCommand());
    insertCommand(new SimtkObjectVisibilityCommand());
    // Properties
    insertCommand(new SimtkObjectReviewCommand());
    insertCommand(new SimtkObjectExportCommand());
    insertCommand(new SimtkObjectEditCommand());
    insertCommand(new SimtkGrapherCommand());
    // Test
    insertCommand(new SimtkTestCommand());
    // Scripting
    insertCommand(new SimtkLoadScriptCommand());

    // Simulation
    insertCommand(new SimtkSimulationStartCommand());
    insertCommand(new SimtkSimulationStopCommand());
    insertCommand(new SimtkSimulationSetupCommand());
    insertCommand(new SimtkSimulationErrChkCommand());
    // Loading entities
    insertCommand(new SimtkLoadControlSetCommand());
    insertCommand(new SimtkLoadContactSetCommand());
    insertCommand(new SimtkLoadActuatorSetCommand());
    // Undo/Redo
    insertCommand(new SimtkUndoLastCommand());
    insertCommand(new SimtkRedoLastCommand());
    return true;
  }

  public static CommandFactory getInstance()
  {
    if (!_instanceFlag) {
        _instanceFlag = true;
        _instance = new CommandFactory();
        _instance.initialize();
      }
    return _instance;
  }
  /**
   * CommandFactory default constructor made private
   */
  private CommandFactory() {
  }

  /**
   * insertCommand private method to add commands to the commandFactory
   *
   * @param cmd SimtkCommand
   * @return boolean true for successful addition
   * @todo handle exception for failed addition
   */
  private boolean insertCommand(SimtkCommand cmd)
  {
    return addCommand(cmd.getCommandName(), cmd.getClass());
  }
  /**
   * addCommand to the CommandFactory. A concrete Action object will be passed
   * in along with the String represnting commandName.
   *
   * @param command object
   * @return boolean true if command addition succeeded, else false
   */
  public boolean addCommand(String commandName, Class cmd)
  {
    boolean repreat = _commandTable.containsKey(commandName);
    try {
      if (!repreat)
        _commandTable.put(commandName, cmd);
   }
   catch(NullPointerException e){
     SimtkApp.displayErrorMessage("Null exception while inserting command "+commandName);
   }
   return true;
  }

  /**
   * removeCommand removes a command from the list maintained by CommandFactory
   *
   * @param commandName String
   */
  public void removeCommand(String commandName){
    try {
     _commandTable.remove(commandName);
   }
   catch(NullPointerException e){
     SimtkApp.displayErrorMessage("Null exception while removing command "+commandName);
   }

  }

  /**
   * logCommand is the command logging main function
   *
   * @param cmd SimtkCommand to log
   */
  static public void logCommand(SimtkCommand cmd)
  {
   if (_commandLoggingOn){
     if (_commandLogFile==null && _commandLogFileName!= null) {
       try {
         _commandLogFile = new FileWriter(_commandLogFileName);
       }
       catch(IOException e){
         SimtkApp.displayErrorMessage("Dont have permission to open command log file:"+_commandLogFileName);
         _commandLoggingOn = false;
       }
     }
   }
   if (_commandLoggingOn){   // Here we know that the the file could be opened for writing
     try{
       String commandLine = CommandFormatter.formatCommand(cmd);
      _commandLogFile.write(commandLine);
      _commandLogFile.flush();
      if (_echoCommands)
        SimtkApp.displayLogMessage(commandLine);
      }
     catch(IOException e){
         SimtkApp.displayErrorMessage("Dont have permission to open command log file:"+_commandLogFileName);
         flushCommandLogFile();
         _commandLoggingOn = false;
       }
   }
  }

 /**
   * turnCommandLogginOn/Off
   * @todo throw exception if file cannot be opened.
   */
  public void turnCommandLogginOn(String fileName)
  {
    _commandLoggingOn = true;
    _commandLogFileName = fileName;
  }
  public void turnCommandLogginOff()
  {
    _commandLoggingOn = false;
  }

  /**
   * flushCommandLogFile: flush and close logfile if open. Performs as no
   * operation if logging is not turned on.
   */
  static void flushCommandLogFile()
  {
    if (!_commandLoggingOn)
      return;

    try{
      if (_commandLogFile != null){
        _commandLogFile.flush();
        _commandLogFile.close();
      }
    }
    catch(IOException e){
      SimtkApp.displayErrorMessage("Failed to flush command log file:"+_commandLogFileName);
      _commandLoggingOn = false;
    }

  }

  /**
   * toggleCommandPlaybackSingleStep Toggles single step mode for script playback
   */
  static public void toggleCommandPlaybackSingleStep()
  {
    _singleStep = !_singleStep;
  }

  /**
   * getCommandPlaybackSingleStep retrieves single step mode
   *
   * @return boolean
   */
  static public boolean getCommandPlaybackSingleStep()
  {
    return _singleStep;
  }
  /**
   * getCommand. Factory method to retrieve a command based on name. The
   * returned type is a base class in order not to expose command class
   * hierarchy to Command users
   *
   * @param commandName String
   * @return SimtkCommand
   */
  static public SimtkCommand getCommand(String commandName) throws CommandFactoryException
  {
    Class commandClass = (Class) _commandTable.get(commandName);
    if (commandClass == null)
      throw( new CommandFactoryException("Failed to obtain command "+commandName+". Command maynot have registered with commandFactory"));

    Object obj = null;
    try {
      obj = commandClass.newInstance();
    }
    catch (IllegalAccessException ex) {
      SimtkApp.displayErrorMessage("Illegal access exception trying to instantiate command "+commandName);
    }
    catch (InstantiationException ex) {
      SimtkApp.displayErrorMessage("Failed to instantiate command "+commandName);
   }
    if (obj == null){
      SimtkApp.displayErrorMessage("Command not found: "+commandName);
     return null;
    }
    // Here something was found, it must be an Action but just incase
    if (! (obj instanceof AbstractAction))
      return null;

    SimtkCommand act = (SimtkCommand) obj;
    // Command might not be available because the context is not correct. Dim out initially
    act.setEnabled(act.whenAvailable());
    // Command may want to observe database changes to change it's availability
    if (act.isObserver())
      SimtkDB.getInstance().addObserver(act);
    return act;
  }

  /**
   * registerUSerCommands is responsible for registering the commands provided
   * by a plugin with the system.
   *
   * @param userCommands SimtkCommand[]
   */
  public static void registerUserCommands(SimtkCommand[] userCommands)
  {
    for(int i=0; i < userCommands.length; i++)
      getInstance().insertCommand(userCommands[i]);
  }

  public static void unregisterUserCommands(SimtkCommand[] userCommands)
  {
    for(int i=0; i < userCommands.length; i++)
      getInstance().removeCommand(userCommands[i].getCommandName());
  }

  /**
   * flushCommandLog
   */
  public static void flushCommandLog() {
    try {
      if (_commandLogFile != null)
        _commandLogFile.flush();
    }
    catch (IOException ex) {
    }
  }
}
