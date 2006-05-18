package simtkCommands;

import simtkCore.SimtkDB;
import opensimModel.Model;
import opensimModel.*;
/**
 * @todo getrid of obj and fix Model's getObjectByName
 */
abstract public class SimtkModelObjectCommand
    extends SimtkModelCommand implements SimtkModelObjectCommandIF{
  OpenSimObject   object;
  public SimtkModelObjectCommand() {
  }

  /**
   * getModel
   *
   * @return Model
   */
  public OpenSimObject getObject() {
    // Make sure there's a Object
    String objName = (String) _cmdParams.get("ObjectName");
    if (objName==null)
      return null;
    if (object != null)
      return object;
    OpenSimObject obj = getModel().getVisibleObjectByName(objName);
    return obj;
  }


  /**
   * setObject
   *
   * @param Object OpenSimObject
   */
  public void setObject(OpenSimObject Object)
  {
      if (getModel() != null)
        addCommandParam("ObjectName", Object.getName());
      object = Object;
  }
}
