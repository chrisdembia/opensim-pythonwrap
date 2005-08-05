package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;
import javax.swing.JFileChooser;

import simtkCore.SimtkDB;
import simtkModel.rdModel;
import simtkUtils.SimtkFileChooser;
import simtkui.SimtkApp;
import simtkui.guiUtilities.GenericFileFilter;
import javax.swing.filechooser.*;
import java.io.File;

public class SimtkSetWorkingDirCommand
    extends SimtkEnvCommand implements SimtkFileOpenIF {
  String _fileName;

  public SimtkSetWorkingDirCommand() {
    super();
    putValue(Action.NAME, "Browse for Working Directory");
    putValue(Action.ACTION_COMMAND_KEY, getCommandName());
    putValue(Action.SHORT_DESCRIPTION, "Browse for Working Directory");
    putValue(Action.LONG_DESCRIPTION, "Browse for Working Directory");

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
    return "SimtkChangeWorkingDirCmd";
  }

  public boolean execute() {
    boolean success = false;
     // Get full model name and try to instantiate it

    if (!_cmdParams.containsKey("FileName")) {
      // Show filechooser to browse for directory, type .class
      JFileChooser jFileChooser1 = new JFileChooser();
      jFileChooser1.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
      jFileChooser1.setDialogTitle("Browse for directory to make into working directory");
      FileFilter filter = new FileFilter(){
        /**
         * accept
         *
         * @param f File
         * @return boolean
         */
        public boolean accept(File f) {
          return f.isDirectory();
        }

        /**
         * getDescription
         *
         * @return String
         */
        public String getDescription() {
          return "";
        }
      };
      jFileChooser1.setFileFilter(filter);
      jFileChooser1.setVisible(true);
      if (jFileChooser1.showOpenDialog(SimtkApp.getTopComponent()) !=
          JFileChooser.APPROVE_OPTION)
        return success;
      _fileName = jFileChooser1.getSelectedFile().getAbsolutePath();
      // Keep model name around for logging purposes
      _cmdParams.put("FileName", _fileName);
    }
    else
      _fileName = (String) _cmdParams.get("FileName");

    System.setProperty("user.dir", _fileName);
    SimtkApp.displayInfoMessage("Directory " + _fileName +
                              " has been made working directory.");
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
  ;

}
