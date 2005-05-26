package simtkCommands;

import javax.swing.Action;

import simtkUtils.SwingWorker;
import simtkui.SimtkApp;

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
 *
 * TestCommand is a dummy command used to illustrate adding a command to the
 * menus, and running the command in the background (as a separate thread) to add the numbers 1..100000
 * showing a termination message in message area upon completion.
 */
public class SimtkTestCommand extends SimtkCommand {
  public SimtkTestCommand() {
    super();
   putValue(Action.NAME, "Background Command");
   putValue(Action.ACTION_COMMAND_KEY,getCommandName());
   putValue(Action.SHORT_DESCRIPTION, "Run commands in background");
 }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "TestCmd";
  }

 public boolean execute() {
   SwingWorker workerThread = new SwingWorker() {
     /**
      * construct
      *
      * @return Object
      */
     public Object construct() {
       int dummy=0;
       for(int i=0; i < 100000; i++){
         dummy += i;
       }
       return null;
      }
      public void finished() {
        SimtkApp.displayInfoMessage("Done running TestCmd");
      }
   };
   workerThread.start();
   return true;
   }

}
