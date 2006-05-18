package simtkCommands;

import java.util.HashMap;

import javax.swing.Action;

import simtkCore.SimtkDB;
import opensimModel.Model;
import opensimModel.OpenSimObject;
import opensimModel.VisibleObject;

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
public class SimtkObjectReviewCommand
    extends SimtkCommand {

  boolean _modelNameIsSet = false;
  boolean _objectIsSet = false;
  public SimtkObjectReviewCommand()
   {
     super();
     putValue(Action.NAME, "Review object");
     putValue(Action.ACTION_COMMAND_KEY, getCommandName());
     putValue(Action.SHORT_DESCRIPTION, "Review object properties");
     putValue(Action.LONG_DESCRIPTION, "Review object properties from model ");
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

  public void setObject(OpenSimObject rObj)
  {
    this._cmdParams.put("Object", rObj);
   _objectIsSet = true;

  }

  public boolean execute() {
    boolean success = true;
    // Make sure there's a model
    String mdlName = (String) _cmdParams.get("ModelName");
    OpenSimObject rdObj;
    Object object = _cmdParams.get("Object");
    if (object instanceof OpenSimObject)
      rdObj = (OpenSimObject) object;
    else if (object instanceof String) {
      Model mdl = SimtkDB.getInstance().getModelByName(mdlName);
      String objectName = object.toString();
      VisibleObject obj = mdl.getVisibleObjectByName(objectName);
      if (obj == null) // Object was not found
        return false;
      if (obj instanceof OpenSimObject)
        rdObj = (OpenSimObject) obj;
      else
        return false;
    }
    else
      return false;
    SimtkDB.getInstance().reviewObject(mdlName, rdObj);
    return true;
  }

  /**
   * getCommandName
   *
   * @return String
   */
  public String getCommandName() {
    return "SimtkObjectReviewCmd";
  }

}
