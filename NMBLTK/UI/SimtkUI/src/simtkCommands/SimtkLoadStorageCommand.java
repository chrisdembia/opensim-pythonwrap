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
import simtkModel.*;

public class SimtkLoadStorageCommand
     extends SimtkEnvCommand implements SimtkFileOpenIF {
  String _fullModelName;
  String _fileName;

  public SimtkLoadStorageCommand() {
    super();
    putValue(Action.NAME, "Load Storage");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Load storage file");
    putValue(Action.LONG_DESCRIPTION, "Load storage file into current environment");

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
    return "SimtkLoadStorageCmd";
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
      if (!getFile("*.sto", "sto", "Browse for storage file"))
        return false;
     }
    else
      _fileName = (String) _cmdParams.get("FileName");

    env.setInfoString("Start reading storage file");
    env.setStatus(SimtkSimEnv.LOADING);
    env.setDeterministicProgress(false);
    // Get frame for associated internalframe
    SimtkMdlInternalFrame mdlFrame = env.getAssociatedFrame();
    mdlFrame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

    rdStorage newStorage = new rdStorage(_fileName);
    // What if the controlSet cant be constructed?
    success = SimtkDB.getInstance().addSorage(newStorage, simenvName);

    env.setStatus(SimtkSimEnv.READY);
    env.setDeterministicProgress(true);
    env.setInfoString("Done reading stoarge file");
    env.setPreferredDirectory(new File(_fileName).getParentFile());
    mdlFrame.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));


    if (success)
      SimtkApp.displayInfoMessage("Storage file " + _fileName +
                              " has been loaded successfully.");
    else
      SimtkApp.displayErrorMessage("Storage file " + _fileName +
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
