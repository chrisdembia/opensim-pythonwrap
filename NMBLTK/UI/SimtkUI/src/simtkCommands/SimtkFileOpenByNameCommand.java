package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkCore.SimtkSimEnv;
import simtkModel.rdModel;
import simtkUtils.SimtkFileChooser;
import simtkui.SimDlgModelName;
import simtkui.SimtkApp;

public class SimtkFileOpenByNameCommand extends SimtkEnvCommand implements SimtkFileOpenIF {
  String _fullModelName, _fileName;

  public SimtkFileOpenByNameCommand() {
    super();
    putValue(Action.NAME, "Open Model");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Open model using typed in java class name");
    putValue(Action.LONG_DESCRIPTION, "Open model using full qualified class name");

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
    return "SimtkFileOpenByNameCmd";
  }

  public boolean execute() {
    boolean success = false;
    String _fileName = null;
    // Get full model name and try to instantiate it
    try {

      if (!_cmdParams.containsKey("FileName")) {
        SimDlgModelName mdlNameDlg = new SimDlgModelName();
        mdlNameDlg.pack();
        //Center the window
        mdlNameDlg.center();
        mdlNameDlg.setVisible(true);

        if (mdlNameDlg.userConfirmed())
          _fileName = mdlNameDlg.getModelName();
        else
          return false;
        // We don't need the dialog any more
        mdlNameDlg.dispose();
      }
      else
        _fileName = (String) _cmdParams.get("FileName");

      success = addModelByName(_fileName, (String)_cmdParams.get("EnvName"));
      if (success)
        SimtkApp.displayInfoMessage("Model " + _fileName +
                                " has been loaded successfully.");
      else
        SimtkApp.displayErrorMessage("Model " + _fileName +
                                " has not been loaded.");
    }

  catch (java.lang.ClassNotFoundException e) {
    SimtkApp.displayErrorMessage("Can't find class " + _fileName + " in classpath");
  }
  catch (java.lang.InstantiationException e) {
    SimtkApp.displayErrorMessage("Can't instantiate class " + _fileName +
                            ". Possible reasons are: class does not have a no-arg constructor");
  }
  catch (java.lang.IllegalAccessException e) {
    SimtkApp.displayErrorMessage("Don't have permission to instantiate class " +
                            _fileName);
  }

  // Keep model name around for logging purposes
  if (!_cmdParams.containsKey("FileName"))
    _cmdParams.put("FileName", _fileName);

  return success;
}

  /**
   * addModelByName adds a model to simtkDB by specifying the full qualified
   * name for it. The class must exist in the path and must have a no-arg
   * constructor.
   *
   * @param modelClassName String
   * @return boolean, unused at this point
   *
   */
  synchronized public boolean addModelByName(String modelClassName, String SimEnvName) throws
      ClassNotFoundException, IllegalAccessException, InstantiationException {
    boolean success = true;
    /*
     * Create an instance of the class.
     *
     * Note that created object's constructor-taking-no-arguments
     * will be called as part of the object's creation.
     */
    Class c = null;
    rdModel mdl = null;
    try {
      c = Class.forName(modelClassName);
      mdl = (rdModel) c.newInstance();
    }
    catch(ClassNotFoundException e){
      SimtkApp.displayErrorMessage("Model " + modelClassName+ " could not be located");
      return false;

    }
    catch(java.lang.NoClassDefFoundError er){
      SimtkApp.displayErrorMessage("Model " + modelClassName+ " could not be located");
      return false;
    }
    if (mdl==null){
      SimtkApp.displayErrorMessage("Model " + modelClassName+ " could not be loaded");
      return false;
    }
    if (SimtkDB.getInstance().addModel(mdl, SimEnvName)){
      SimtkSimEnv env = SimtkDB.getInstance().getEnvForModel(mdl.getName());
      if (!_cmdParams.containsKey("EnvName"))
        _cmdParams.put("EnvName", env.getName());
      return true;
    }
    // Model could not be added because it's already loaded
    SimtkApp.displayErrorMessage("Model " + mdl.getName()+ " is already loaded in memory");
    return false;
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
