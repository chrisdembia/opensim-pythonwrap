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
public class SimtkObjectEditCommand
    extends SimtkCommand {

  boolean _modelNameIsSet = false;
  boolean _objectIsSet = false;
  public SimtkObjectEditCommand() {
     super();
     putValue(Action.NAME, "Edit object");
     putValue(Action.ACTION_COMMAND_KEY, getCommandName());
     putValue(Action.SHORT_DESCRIPTION, "Modify object properties");
     putValue(Action.LONG_DESCRIPTION, "Modify properties of model object");
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
    rdObject rdObj;
    Object object = _cmdParams.get("Object");
    if (object instanceof rdObject)
      rdObj = (rdObject) object;
    else if (object instanceof String) {
      rdModel mdl = SimtkDB.getInstance().getModelByName(mdlName);
      String objectName = object.toString();
      rdVisibleObject obj = mdl.getVisibleObjectByName(objectName);
      if (obj == null) // Object was not found
        return false;
      if (obj instanceof rdObject)
        rdObj = (rdObject) obj;
      else
        return false;
    }
    else
      return false;

    SimtkDB.getInstance().editObject(mdlName, rdObj);
    return true;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkObjectEditCmd";
  }

}
