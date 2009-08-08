/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Controller extends OpenSimObject {
  private long swigCPtr;

  public Controller(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Controller obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Controller(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public Model getModel() {
    long cPtr = opensimModelJNI.Controller_getModel(swigCPtr, this);
    return (cPtr == 0) ? null : new Model(cPtr, false);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.Controller_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void setControlSet(ControlSet aControlSet) {
    opensimModelJNI.Controller_setControlSet(swigCPtr, this, ControlSet.getCPtr(aControlSet), aControlSet);
  }

  public void setDesiredStatesStorage(Storage aYDesStore) {
    opensimModelJNI.Controller_setDesiredStatesStorage(swigCPtr, this, Storage.getCPtr(aYDesStore), aYDesStore);
  }

  public boolean getOn() {
    return opensimModelJNI.Controller_getOn(swigCPtr, this);
  }

  public void setOn(boolean aTrueFalse) {
    opensimModelJNI.Controller_setOn(swigCPtr, this, aTrueFalse);
  }

  public void computeControls(SWIGTYPE_p_double rDT, double aT, SWIGTYPE_p_double aY, ControlSet rX) {
    opensimModelJNI.Controller_computeControls(swigCPtr, this, SWIGTYPE_p_double.getCPtr(rDT), aT, SWIGTYPE_p_double.getCPtr(aY), ControlSet.getCPtr(rX), rX);
  }

}
