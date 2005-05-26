package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;
import simtkModel.rdModel;
import simtkModel.rdObject;
import simtkModel.rdVisibleObject;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Generic object viewer
 */
public class SimtkObjectSelectCommand
    extends SimtkCommand {

  boolean _modelNameIsSet = false;
  boolean _objectIsSet = false;
  public SimtkObjectSelectCommand()
   {
     super();
     putValue(Action.NAME, "Select Object");
     putValue(Action.ACTION_COMMAND_KEY, getCommandName());
     putValue(Action.SHORT_DESCRIPTION, "Select an Object");
     putValue(Action.LONG_DESCRIPTION, "Select an Object");
    }

  /**
   * setCommandParams
   *
   * @param params HashMap
   */
  public void setCommandParams(HashMap params) {
    super.setCommandParams(params);
    if (_cmdParams.containsKey("ModelName"))
      _modelNameIsSet = true;
    if (_cmdParams.containsKey("ObjectName"))
      _objectIsSet = true;
  }


  public void setModelName(String mdlName)
  {
    this._cmdParams.put("ModelName", mdlName);
   _modelNameIsSet = true;
  }

  public void setObject(rdObject rObj)
  {
    this._cmdParams.put("Object", rObj);
   _objectIsSet = true;

  }

  public boolean execute() {
    boolean success = true;
    // Make sure there's a model
    String mdlName = (String) _cmdParams.get("ModelName");
    rdVisibleObject rdVisObj;
    Object object = _cmdParams.get("Object");
    if (object instanceof rdVisibleObject)
      rdVisObj = (rdVisibleObject) object;
    else if (object instanceof String) {
      rdModel mdl = SimtkDB.getInstance().getModelByName(mdlName);
      String objectName = object.toString();
      rdVisObj = mdl.getVisibleObjectByName(objectName);
      if (rdVisObj == null) // Object was not found
        return false;
    }
    else
      return false;

    return true;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkSelectCmd";
  }

}
