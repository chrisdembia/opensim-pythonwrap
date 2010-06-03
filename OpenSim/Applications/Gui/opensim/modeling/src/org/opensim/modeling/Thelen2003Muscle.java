/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Thelen2003Muscle extends Muscle {
  private long swigCPtr;

  public Thelen2003Muscle(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Thelen2003Muscle obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Thelen2003Muscle(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Thelen2003Muscle_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(Thelen2003Muscle aMuscle) {
    opensimModelJNI.Thelen2003Muscle_copyData(swigCPtr, this, Thelen2003Muscle.getCPtr(aMuscle), aMuscle);
  }

  public void copyPropertyValues(Actuator aActuator) {
    opensimModelJNI.Thelen2003Muscle_copyPropertyValues(swigCPtr, this, Actuator.getCPtr(aActuator), aActuator);
  }

  public double getMaxIsometricForce() {
    return opensimModelJNI.Thelen2003Muscle_getMaxIsometricForce(swigCPtr, this);
  }

  public double getOptimalFiberLength() {
    return opensimModelJNI.Thelen2003Muscle_getOptimalFiberLength(swigCPtr, this);
  }

  public double getTendonSlackLength() {
    return opensimModelJNI.Thelen2003Muscle_getTendonSlackLength(swigCPtr, this);
  }

  public double getPennationAngleAtOptimalFiberLength() {
    return opensimModelJNI.Thelen2003Muscle_getPennationAngleAtOptimalFiberLength(swigCPtr, this);
  }

  public double getActivationTimeConstant() {
    return opensimModelJNI.Thelen2003Muscle_getActivationTimeConstant(swigCPtr, this);
  }

  public double getDeactivationTimeConstant() {
    return opensimModelJNI.Thelen2003Muscle_getDeactivationTimeConstant(swigCPtr, this);
  }

  public double getVmax() {
    return opensimModelJNI.Thelen2003Muscle_getVmax(swigCPtr, this);
  }

  public double getVmax0() {
    return opensimModelJNI.Thelen2003Muscle_getVmax0(swigCPtr, this);
  }

  public double getFmaxTendonStrain() {
    return opensimModelJNI.Thelen2003Muscle_getFmaxTendonStrain(swigCPtr, this);
  }

  public double getFmaxMuscleStrain() {
    return opensimModelJNI.Thelen2003Muscle_getFmaxMuscleStrain(swigCPtr, this);
  }

  public double getKshapeActive() {
    return opensimModelJNI.Thelen2003Muscle_getKshapeActive(swigCPtr, this);
  }

  public double getKshapePassive() {
    return opensimModelJNI.Thelen2003Muscle_getKshapePassive(swigCPtr, this);
  }

  public double getDamping() {
    return opensimModelJNI.Thelen2003Muscle_getDamping(swigCPtr, this);
  }

  public double getAf() {
    return opensimModelJNI.Thelen2003Muscle_getAf(swigCPtr, this);
  }

  public double getFlen() {
    return opensimModelJNI.Thelen2003Muscle_getFlen(swigCPtr, this);
  }

  public boolean setActivationTimeConstant(double aActivationTimeConstant) {
    return opensimModelJNI.Thelen2003Muscle_setActivationTimeConstant(swigCPtr, this, aActivationTimeConstant);
  }

  public boolean setDeactivationTimeConstant(double aDeactivationTimeConstant) {
    return opensimModelJNI.Thelen2003Muscle_setDeactivationTimeConstant(swigCPtr, this, aDeactivationTimeConstant);
  }

  public boolean setMaxIsometricForce(double aMaxIsometricForce) {
    return opensimModelJNI.Thelen2003Muscle_setMaxIsometricForce(swigCPtr, this, aMaxIsometricForce);
  }

  public boolean setOptimalFiberLength(double aOptimalFiberLength) {
    return opensimModelJNI.Thelen2003Muscle_setOptimalFiberLength(swigCPtr, this, aOptimalFiberLength);
  }

  public boolean setTendonSlackLength(double aTendonSlackLength) {
    return opensimModelJNI.Thelen2003Muscle_setTendonSlackLength(swigCPtr, this, aTendonSlackLength);
  }

  public boolean setPennationAngle(double aPennationAngle) {
    return opensimModelJNI.Thelen2003Muscle_setPennationAngle(swigCPtr, this, aPennationAngle);
  }

  public boolean setVmax(double aVmax) {
    return opensimModelJNI.Thelen2003Muscle_setVmax(swigCPtr, this, aVmax);
  }

  public boolean setVmax0(double aVmax0) {
    return opensimModelJNI.Thelen2003Muscle_setVmax0(swigCPtr, this, aVmax0);
  }

  public boolean setFmaxTendonStrain(double aFmaxTendonStrain) {
    return opensimModelJNI.Thelen2003Muscle_setFmaxTendonStrain(swigCPtr, this, aFmaxTendonStrain);
  }

  public boolean setFmaxMuscleStrain(double aFmaxMuscleStrain) {
    return opensimModelJNI.Thelen2003Muscle_setFmaxMuscleStrain(swigCPtr, this, aFmaxMuscleStrain);
  }

  public boolean setKshapeActive(double aKShapeActive) {
    return opensimModelJNI.Thelen2003Muscle_setKshapeActive(swigCPtr, this, aKShapeActive);
  }

  public boolean setKshapePassive(double aKshapePassive) {
    return opensimModelJNI.Thelen2003Muscle_setKshapePassive(swigCPtr, this, aKshapePassive);
  }

  public boolean setDamping(double aDamping) {
    return opensimModelJNI.Thelen2003Muscle_setDamping(swigCPtr, this, aDamping);
  }

  public boolean setAf(double aAf) {
    return opensimModelJNI.Thelen2003Muscle_setAf(swigCPtr, this, aAf);
  }

  public boolean setFlen(double aFlen) {
    return opensimModelJNI.Thelen2003Muscle_setFlen(swigCPtr, this, aFlen);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.Thelen2003Muscle_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.Thelen2003Muscle_isA(swigCPtr, this, type);
  }

  public static Thelen2003Muscle safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.Thelen2003Muscle_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new Thelen2003Muscle(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.Thelen2003Muscle_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
