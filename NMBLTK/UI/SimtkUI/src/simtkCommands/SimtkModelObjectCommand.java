package simtkCommands;

import simtkCore.SimtkDB;
import simtkModel.rdModel;
import simtkModel.*;

abstract public class SimtkModelObjectCommand
    extends SimtkModelCommand implements SimtkModelObjectCommandIF{
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
  }
}
