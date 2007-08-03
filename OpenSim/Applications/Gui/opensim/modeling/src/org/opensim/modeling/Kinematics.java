/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Kinematics extends Analysis {
  private long swigCPtr;

  public Kinematics(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Kinematics obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Kinematics(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.Kinematics_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.Kinematics_isA(swigCPtr, this, type);
  }

  public static Kinematics safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.Kinematics_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new Kinematics(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.Kinematics_copy__SWIG_0(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public Kinematics(Model aModel) {
    this(opensimModelJNI.new_Kinematics__SWIG_0(Model.getCPtr(aModel), aModel), true);
  }

  public Kinematics() {
    this(opensimModelJNI.new_Kinematics__SWIG_1(), true);
  }

  public Kinematics(String aFileName) {
    this(opensimModelJNI.new_Kinematics__SWIG_2(aFileName), true);
  }

  public Kinematics(Kinematics aObject) {
    this(opensimModelJNI.new_Kinematics__SWIG_3(Kinematics.getCPtr(aObject), aObject), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Kinematics_copy__SWIG_1(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setStorageCapacityIncrements(int aIncrement) {
    opensimModelJNI.Kinematics_setStorageCapacityIncrements(swigCPtr, this, aIncrement);
  }

  public Storage getAccelerationStorage() {
    long cPtr = opensimModelJNI.Kinematics_getAccelerationStorage(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getVelocityStorage() {
    long cPtr = opensimModelJNI.Kinematics_getVelocityStorage(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getPositionStorage() {
    long cPtr = opensimModelJNI.Kinematics_getPositionStorage(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.Kinematics_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void setRecordAccelerations(boolean aRecordAccelerations) {
    opensimModelJNI.Kinematics_setRecordAccelerations(swigCPtr, this, aRecordAccelerations);
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.Kinematics_begin__SWIG_0(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP), SWIGTYPE_p_double.getCPtr(aDYDT), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT) {
    return opensimModelJNI.Kinematics_begin__SWIG_1(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP), SWIGTYPE_p_double.getCPtr(aDYDT));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP) {
    return opensimModelJNI.Kinematics_begin__SWIG_2(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Kinematics_begin__SWIG_3(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.Kinematics_step__SWIG_0(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), SWIGTYPE_p_double.getCPtr(aYPPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP), SWIGTYPE_p_double.getCPtr(aDYDT), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT) {
    return opensimModelJNI.Kinematics_step__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), SWIGTYPE_p_double.getCPtr(aYPPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP), SWIGTYPE_p_double.getCPtr(aDYDT));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP) {
    return opensimModelJNI.Kinematics_step__SWIG_2(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), SWIGTYPE_p_double.getCPtr(aYPPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, SWIGTYPE_p_double aYPPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Kinematics_step__SWIG_3(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), SWIGTYPE_p_double.getCPtr(aYPPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int end(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.Kinematics_end__SWIG_0(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP), SWIGTYPE_p_double.getCPtr(aDYDT), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int end(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP, SWIGTYPE_p_double aDYDT) {
    return opensimModelJNI.Kinematics_end__SWIG_1(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP), SWIGTYPE_p_double.getCPtr(aDYDT));
  }

  public int end(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_double aYP) {
    return opensimModelJNI.Kinematics_end__SWIG_2(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_double.getCPtr(aYP));
  }

  public int end(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Kinematics_end__SWIG_3(swigCPtr, this, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int printResults(String aBaseName, String aDir, double aDT, String aExtension) {
    return opensimModelJNI.Kinematics_printResults__SWIG_0(swigCPtr, this, aBaseName, aDir, aDT, aExtension);
  }

  public int printResults(String aBaseName, String aDir, double aDT) {
    return opensimModelJNI.Kinematics_printResults__SWIG_1(swigCPtr, this, aBaseName, aDir, aDT);
  }

  public int printResults(String aBaseName, String aDir) {
    return opensimModelJNI.Kinematics_printResults__SWIG_2(swigCPtr, this, aBaseName, aDir);
  }

  public int printResults(String aBaseName) {
    return opensimModelJNI.Kinematics_printResults__SWIG_3(swigCPtr, this, aBaseName);
  }

}
