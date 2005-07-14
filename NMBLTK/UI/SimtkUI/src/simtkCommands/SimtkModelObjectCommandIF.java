package simtkCommands;

import simtkModel.*;

abstract interface SimtkModelObjectCommandIF
    extends SimtkModelCommandIF{

  /**
   * getObject
   *
   * @return rdObject
   */
  public rdObject getObject() ;

  /**
   * setObject
   *
   * @param Object rdObject
   */
  public void setObject(rdObject Object) ;
}
