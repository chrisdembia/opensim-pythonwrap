package simtkCommands;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import opensimModel.ContactForceSet;
import simtkUtils.SimtkFileChooser;
import simtkui.SimtkApp;

public class SimtkLoadContactSetCommand
    extends SimtkEnvCommand implements SimtkFileOpenIF {
  String _fullModelName, _fileName;

  public SimtkLoadContactSetCommand() {
    super();
    putValue(Action.NAME, "Load Contacts");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Load Contact set");
    putValue(Action.LONG_DESCRIPTION, "Load contact set into current environment");

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
    return "SimtkLoadContactSetCmd";
  }

  /**
   * execute queries the UI for file name and create a controlset based on it
   *
   * @return boolean true on success false on failure
   * @todo Handle failure to create controlSet for any reason
   */
  public boolean execute() {
    boolean success = false;
    String _fileName = null;

    String simenvName = (String) _cmdParams.get("EnvName");
   // Cache environment for later use
   SimtkSimEnv env = SimtkDB.getInstance().getSimtkSimEnv(simenvName);
   if (!_cmdParams.containsKey("FileName")) {
     File preferredDirectory = env.getPreferredDirectory();
     String preferredDirectoryName="";
     try {
       if (preferredDirectory!= null)
         preferredDirectoryName = preferredDirectory.getCanonicalPath();
     }
     catch (IOException ex) {
     }
     if (!getFile("*.ctx", "ctx", "Browse for contact force set file"))
       return false;
    }
    else
      _fileName = (String) _cmdParams.get("FileName");

    ContactForceSet newContactSet = new ContactForceSet(_fileName);
    // What if the newContactSet cant be constructed?
    success = SimtkDB.getInstance().addContactForceSet(newContactSet, (String) _cmdParams.get("EnvName"));
    env.setPreferredDirectory(new File(_fileName).getParentFile());
    if (success)
      SimtkApp.displayInfoMessage("Contact force set " + _fileName +
                              " has been loaded successfully.");
    else
      SimtkApp.displayInfoMessage("Contact force set " + _fileName +
                              " has not been loaded.");

    return success;
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
   return (true/*SimtkDB.getInstance().getSimtkSimEnv(simenvName).getStatus()==SimtkSimEnv.NOT_READY*/);
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
}
