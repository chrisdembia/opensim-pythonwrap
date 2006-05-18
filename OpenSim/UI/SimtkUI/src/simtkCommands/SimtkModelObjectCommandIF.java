package simtkCommands;

import opensimModel.*;

abstract interface SimtkModelObjectCommandIF
    extends SimtkModelCommandIF{

  /**
   * getObject
   *
   * @return OpenSimObject
   */
  public OpenSimObject getObject() ;

  /**
   * setObject
   *
   * @param Object OpenSimObject
   */
  public void setObject(OpenSimObject Object) ;
}
