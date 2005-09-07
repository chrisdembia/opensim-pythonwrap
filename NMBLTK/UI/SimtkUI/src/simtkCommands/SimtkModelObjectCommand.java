package simtkCommands;

import simtkModel.*;
/**
 * @todo getrid of obj and fix Model's getObjectByName
 */
abstract public class SimtkModelObjectCommand
    extends SimtkModelCommand implements SimtkModelObjectCommandIF{
  rdObject   object;
  public SimtkModelObjectCommand() {
  }

  /**
   * getModel
   *
   * @return rdModel
   */
  public rdObject getObject() {
    // Make sure there's a Object
    String objName = (String) _cmdParams.get("ObjectName");
    if (objName==null)
      return null;
    if (object != null)
      return object;
    rdObject obj = getModel().getVisibleObjectByName(objName);
    return obj;
  }


  /**
   * setObject
   *
   * @param Object rdObject
   */
  public void setObject(rdObject Object)
  {
      if (getModel() != null)
        addCommandParam("ObjectName", Object.getName());
      object = Object;
  }
}
