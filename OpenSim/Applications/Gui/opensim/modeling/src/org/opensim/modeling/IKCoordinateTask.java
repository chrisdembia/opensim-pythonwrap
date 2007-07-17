/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class IKCoordinateTask extends IKTask {
  private long swigCPtr;

  public IKCoordinateTask(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(IKCoordinateTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_IKCoordinateTask(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.IKCoordinateTask_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.IKCoordinateTask_isA(swigCPtr, this, type);
  }

  public static IKCoordinateTask safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.IKCoordinateTask_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new IKCoordinateTask(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.IKCoordinateTask_copy__SWIG_0(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public IKCoordinateTask() {
    this(opensimModelJNI.new_IKCoordinateTask__SWIG_0(), true);
  }

  public IKCoordinateTask(IKCoordinateTask aIKCoordinateTask) {
    this(opensimModelJNI.new_IKCoordinateTask__SWIG_1(IKCoordinateTask.getCPtr(aIKCoordinateTask), aIKCoordinateTask), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.IKCoordinateTask_copy__SWIG_1(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public boolean getFromFile() {
    return opensimModelJNI.IKCoordinateTask_getFromFile(swigCPtr, this);
  }

  public void setFromFile(boolean fromFile) {
    opensimModelJNI.IKCoordinateTask_setFromFile(swigCPtr, this, fromFile);
  }

  public boolean getValueUseDefault() {
    return opensimModelJNI.IKCoordinateTask_getValueUseDefault(swigCPtr, this);
  }

  public void setValueUseDefault(boolean useDefault) {
    opensimModelJNI.IKCoordinateTask_setValueUseDefault(swigCPtr, this, useDefault);
  }

  public double getValue() {
    return opensimModelJNI.IKCoordinateTask_getValue(swigCPtr, this);
  }

  public void setValue(double value) {
    opensimModelJNI.IKCoordinateTask_setValue(swigCPtr, this, value);
  }

}