package simtkCommands;

import java.awt.Cursor;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkModel.rdControlSet;
import simtkUtils.SimtkFileChooser;
import simtkView.SimtkMdlInternalFrame;
import simtkui.SimtkApp;

public class SimtkLoadControlSetCommand
     extends SimtkEnvCommand implements SimtkFileOpenIF {
  String _fullModelName;
  String _fileName;

  public SimtkLoadControlSetCommand() {
    super();
    putValue(Action.NAME, "Load Controls");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Load control set");
    putValue(Action.LONG_DESCRIPTION, "Load control set into current environment");

   }

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
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkLoadControlSetCmd";
  }

  /**
   * execute queries the UI for file name and create a controlset based on it
   *
   * @return boolean true on success false on failure
   * @todo Handle failure to create controlSet for any reason
   */
  public boolean execute() {
    boolean success = false;

    String simenvName = (String) _cmdParams.get("EnvName");
    // Cache environment for later use
    SimtkSimEnv env = SimtkDB.getInstance().getSimtkSimEnv(simenvName);
    if (!_cmdParams.containsKey("FileName")) {
      // Show filechooser to browse for directory, type .tiff
      // For now we'll open a jar file
      File preferredDirectory = env.getPreferredDirectory();
      String preferredDirectoryName="";
      try {
        if (preferredDirectory!= null)
          preferredDirectoryName = preferredDirectory.getCanonicalPath();
      }
      catch (IOException ex) {
      }
      if (!getFile("*.ctr", "ctr", "Browse for control file"))
        return false;
     }
    else
      _fileName = (String) _cmdParams.get("FileName");

    env.setInfoString("Start reading control file");
    env.setDeterministicProgress(false);
    env.setStatus(SimtkSimEnv.LOADING);
    // Get frame for associated internalframe
    SimtkMdlInternalFrame mdlFrame = env.getAssociatedFrame();
    mdlFrame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

    rdControlSet newControlSet = new rdControlSet(_fileName);
    // What if the controlSet cant be constructed?
    success = SimtkDB.getInstance().addControlSet(newControlSet, simenvName);

    env.setInfoString("Done reading control file");
    env.setStatus(SimtkSimEnv.READY);
    env.setDeterministicProgress(true);
    env.setPreferredDirectory(new File(_fileName).getParentFile());
    mdlFrame.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));


    if (success)
      SimtkApp.displayInfoMessage("Control set " + _fileName +
                              " has been loaded successfully.");
    else
      SimtkApp.displayErrorMessage("Control set " + _fileName +
                              " has not been loaded.");

    return success;
  }

  public boolean isBackgroundCmd()
  {
    return true;
  }
  /**
   * whenAvailable override to tell the system that this command is
   * conditionally available
   *
   * @return boolean
   */
  public boolean whenAvailable() {
    String simenvName = (String) _cmdParams.get("EnvName");
    if (simenvName==null)
      return false;
   SimtkSimEnv env = SimtkDB.getInstance().getSimtkSimEnv(simenvName);
   return (true/*env.getStatus()==SimtkSimEnv.NOT_READY*/);
  }
  /**
   * isObserver is overloaded to tell the system that the command is
   * conditionally available based on system events
   *
   * @return boolean
   */
  public boolean isObserver() {
    return true;
  }

  /**
   * getFile
   *
   * @param extension String
   * @param description String
   * @param dialogTitle String
   * @return boolean
   */
  public boolean getFile(String extension, String description,
                         String dialogTitle) {
    boolean gotFile = false;

    if (_cmdParams.containsKey("FileName")) {
      _fileName = (String) _cmdParams.get("FileName");
      return true;
    }

    _fileName = SimtkFileChooser.getFile(dialogTitle, description, extension);
    if (_fileName == null)
      return false;
    _cmdParams.put("FileName", _fileName);

    return true;
  }
  ;
}
