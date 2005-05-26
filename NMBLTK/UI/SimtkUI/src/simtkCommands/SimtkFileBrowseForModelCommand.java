package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;
import javax.swing.JFileChooser;

import simtkCore.SimtkDB;
import simtkModel.rdModel;
import simtkUtils.SimtkFileChooser;
import simtkui.SimtkApp;
import simtkui.guiUtilities.GenericFileFilter;

public class SimtkFileBrowseForModelCommand
    extends SimtkEnvCommand implements SimtkFileOpenIF {
  String _fullModelName, _fileName;

  public SimtkFileBrowseForModelCommand() {
    super();
    putValue(Action.NAME, "Browse for Model");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Browse for model class file");
    putValue(Action.LONG_DESCRIPTION, "Browse for model class file");

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
    return "SimtkFileBrowseForModelCmd";
  }

  public boolean execute() {
    boolean success = false;
     // Get full model name and try to instantiate it

    if (!_cmdParams.containsKey("FileName")) {
      // Show filechooser to browse for directory, type .class
      JFileChooser jFileChooser1 = new JFileChooser();
      jFileChooser1.setDialogTitle("Browse for directory of model class file");
      GenericFileFilter filter = new GenericFileFilter("class", "*.class");
      jFileChooser1.setFileFilter(filter);
      jFileChooser1.setVisible(true);
      if (jFileChooser1.showOpenDialog(SimtkApp.getTopComponent()) !=
          JFileChooser.APPROVE_OPTION)
        return success;
      String bareFileName = jFileChooser1.getSelectedFile().getName();
      String fileName = bareFileName.substring(0, bareFileName.length() - 6); // Remove .class part of file name
      String packageName = jFileChooser1.getSelectedFile().getParentFile().
          getName();
      _fileName = packageName + "." + fileName;
      // Keep model name around for logging purposes
      _cmdParams.put("FileName", _fileName);
    }
    else
      _fileName = (String) _cmdParams.get("FileName");

      rdModel mdl = null;
      // Pass selection to view to write the file
      try { //
        Class modelClass = this.getClass().getClassLoader().loadClass(_fileName);
        try {
          mdl = (rdModel) modelClass.newInstance();
        }
        catch (IllegalAccessException ex) {
        }
        catch (InstantiationException ex) {
        }
      }
      catch (ClassNotFoundException e) {
        SimtkApp.displayErrorMessage("Model " + _fileName +
                                     " could not be located");
        return false;

      }
      catch (java.lang.NoClassDefFoundError er) {
        SimtkApp.displayErrorMessage("Model " + _fileName +
                                     " could not be located");
        return false;
      }
      if (mdl == null) {
        SimtkApp.displayErrorMessage("Model " + _fileName +
                                     " could not be loaded");
        return false;
      }
    if (SimtkDB.getInstance().addModel(mdl, (String)_cmdParams.get("EnvName"))){
      SimtkApp.displayInfoMessage("Model " + _fileName +
                              " has been loaded successfully.");
      return true;
    }
// Model could not be added because it's already loaded
    SimtkApp.displayErrorMessage("Model " + mdl.getName() +
                            " is already loaded in memory");
    return false;

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
    if (SimtkDB.getInstance().addModel(mdl, SimEnvName))
      return true;
    // Model could not be added because it's already loaded
    SimtkApp.displayErrorMessage("Model " + mdl.getName()+ " is already loaded in memory");
    return false;
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
  ;

}
