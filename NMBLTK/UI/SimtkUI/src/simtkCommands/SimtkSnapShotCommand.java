package simtkCommands;

import javax.swing.Action;
import javax.swing.JOptionPane;

import simtkCore.SimtkDB;
import simtkUtils.SimtkFileChooser;
import simtkView.SimtkViewDB;
import simtkui.SimtkApp;

public class SimtkSnapShotCommand extends SimtkEnvCommand implements SimtkFileOpenIF {
  boolean _modelNameSet = false;
  boolean _fileNameSet = false;
  String _fileName;

  public SimtkSnapShotCommand() {
    super();
    putValue(Action.NAME,  "Take Snapshot");
    putValue(Action.ACTION_COMMAND_KEY,getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Take snapshot of current window");
  }

  public boolean execute() {
    boolean success = false;
    // Make sure there's a model
    if (!_modelNameSet) {
      String currentModelName = SimtkViewDB.getCurrentModelName();
      if (currentModelName == null) {
        JOptionPane.showMessageDialog(SimtkApp.getTopComponent(),
                                      "There is no current model");
        return false;
      }
      setModelName(currentModelName);
    }

    if (_cmdParams.containsKey("FileName")) {
      setFileName( (String) _cmdParams.get("FileName"));
    }
    else {

      if (!getFile("*.tiff", "tiff", "Browse for directory to save file"))
        return false;
     }
    SimtkViewDB.write2Tiff((String) this._cmdParams.get("ModelName"), (String) this._cmdParams.get("FileName"));
    success = true;
    return success;
  }
  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkSnapShotCmd";
  }

  public void setModelName(String mdlName) {
    this._cmdParams.put("ModelName", mdlName);
    _modelNameSet = true;
  }

  public void setFileName(String fileName) {
    this._cmdParams.put("FileName", fileName);
    _fileNameSet = true;
  }
  /**
   * whenAvailable override to tell the system that this command is
   * conditionally available
   *
   * @return boolean
   */
  public boolean whenAvailable() {
    return (SimtkDB.getInstance().getNumberOfModels() > 0);
  }

  /**
   * isObserver is overloaded to tell the system that the command is
   * conditionally available based on system events
   *
   * @return boolean
   */
  public boolean isObserver()
  {
    return true;
  }
  /**
   * isTopLevel: Command is associated with Top level menu item or toolbar
   *
   * @return boolean
   */
  public boolean isTopLevel() {
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
    if (_cmdParams.containsKey("FileName")) {
      _fileName = (String) _cmdParams.get("FileName");
      return true;
    }

    // Show filechooser to browse for directory, file to open
    _fileName = SimtkFileChooser.getFile(dialogTitle, description, extension);
    if (_fileName == null)
      return false;
    _cmdParams.put("FileName", _fileName);

    return true;
  }
}
