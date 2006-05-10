package simtkCommands;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

import javax.swing.Action;
import javax.swing.JOptionPane;

import simtkUtils.SimtkFileChooser;
import simtkui.SimtkApp;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Command to load script file, parse it and execute it. Special about this
 * command is that it should not be logged otherwise playback can get nested!
 */
public class SimtkLoadScriptCommand extends SimtkCommand{
  public SimtkLoadScriptCommand() {
    super();
    putValue(Action.NAME, "Load Script");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Run commands from a script file");
  }

  /**
   * execute is the entry point for playback/scripting functionality. The
   * command internally invokes the UI to get the script file name and iterate
   * thru the commands in the file to execute them.
   *
   * @return boolean
   */
  public boolean execute() {
    boolean success = false;
    String _fileName = SimtkFileChooser.getFile("Browse for directory for script file ",
                                         "log", "*.log");
    if (_fileName==null)
      return success;

    // We'll have to handle the read commands in a different thread
    try {
     BufferedReader in = new BufferedReader(new FileReader(_fileName));
     String str;
     ExecutionManager.playBackOn();
     while ((str = in.readLine()) != null) {
         if (str.length()==0)
           continue;
         process(str);
         if(CommandFactory.getCommandPlaybackSingleStep()){
           JOptionPane.showMessageDialog(SimtkApp.getTopComponent(),
                              "Press ok to continue",
                              "Single Step Mode",
                              JOptionPane.INFORMATION_MESSAGE);

         }
     }
     ExecutionManager.playBackOff();
     in.close();
   } catch (IOException e) {
   } finally {
     ExecutionManager.playBackOff();
   }

    return true;
  }
/**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkLoadScriptCmd";
  }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
  }
  /**
   * Override method so that command is not logged.
   */
  public void postExecute() { // Common postExecute activities
  };

  /**
   * process is the main function used by this command as it parses the
   * commandline and passes the parsed command to the execution manager by
   * placing it in an execution queue
   *
   * @param commandLine String
   * @todo If/when we expose a command line for end users to types in commands,
   *   then user entered strings will be passed to this function to parse them,
   *   create proper command and execute them
   */
  void process(String commandLine) {
    // We don't execute commands directly. We just put them in queue and the system knows what to do
    SimtkCommand nextCommand = null;
    try {
      nextCommand = CommandFormatter.parseCommand(commandLine);
      ExecutionManager.enQueueCommand(nextCommand);
    }
    catch (CommandFactoryException ex) {
      SimtkApp.displayErrorMessage("Command " + " could not be found.. Ignored");
    }
  }
}
