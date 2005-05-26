package simtkCommands;

import java.util.HashMap;

import simtkUtils.SimtkFileChooser;

abstract public class SimtkFileOpenCommand extends SimtkCommand {
  protected String _fileName;
  boolean _fileNameSet;

  public SimtkFileOpenCommand() {
    _fileNameSet = false;
  }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
    // Expect exactly one parameter which is file name
    super.setCommandParams(params);
    _fileName = (String) params.get("FileName");
    _fileNameSet = true;
  }

  //abstract public void actionPerformed(ActionEvent e) ;

  /**
   * canUndo
   * Mark it final so that derived classes can not override it
   * @return boolean
   */
  final public boolean canUndo() {
    return false;
  }

  abstract public String getCommandName() ;

  public abstract boolean execute();

  protected boolean getFile(String extension, String description, String dialogTitle) {
    boolean gotFile = false;
    if ( _cmdParams.containsKey("FileName")   ){
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
