/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class IKTask extends OpenSimObject {
  private long swigCPtr;

  public IKTask(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(IKTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_IKTask(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.IKTask_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public boolean getApply() {
    return opensimModelJNI.IKTask_getApply(swigCPtr, this);
  }

  public void setApply(boolean aApply) {
    opensimModelJNI.IKTask_setApply(swigCPtr, this, aApply);
  }

  public double getWeight() {
    return opensimModelJNI.IKTask_getWeight(swigCPtr, this);
  }

  public void setWeight(double weight) {
    opensimModelJNI.IKTask_setWeight(swigCPtr, this, weight);
  }

}
