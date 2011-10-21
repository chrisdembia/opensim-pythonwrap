/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Delp1990Muscle extends ActivationFiberLengthMuscle {
  private long swigCPtr;

  public Delp1990Muscle(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.Delp1990Muscle_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Delp1990Muscle obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_Delp1990Muscle(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Delp1990Muscle_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(Delp1990Muscle aMuscle) {
    opensimModelJNI.Delp1990Muscle_copyData(swigCPtr, this, Delp1990Muscle.getCPtr(aMuscle), aMuscle);
  }

  public double getTimeScale() {
    return opensimModelJNI.Delp1990Muscle_getTimeScale(swigCPtr, this);
  }

  public double getMass() {
    return opensimModelJNI.Delp1990Muscle_getMass(swigCPtr, this);
  }

  public boolean setTimeScale(double aTimeScale) {
    return opensimModelJNI.Delp1990Muscle_setTimeScale(swigCPtr, this, aTimeScale);
  }

  public boolean setActivation1(double aActivation1) {
    return opensimModelJNI.Delp1990Muscle_setActivation1(swigCPtr, this, aActivation1);
  }

  public boolean setActivation2(double aActivation2) {
    return opensimModelJNI.Delp1990Muscle_setActivation2(swigCPtr, this, aActivation2);
  }

  public boolean setMass(double aMass) {
    return opensimModelJNI.Delp1990Muscle_setMass(swigCPtr, this, aMass);
  }

  public Function getActiveForceLengthCurve() {
    long cPtr = opensimModelJNI.Delp1990Muscle_getActiveForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setActiveForceLengthCurve(Function aActiveForceLengthCurve) {
    return opensimModelJNI.Delp1990Muscle_setActiveForceLengthCurve(swigCPtr, this, Function.getCPtr(aActiveForceLengthCurve), aActiveForceLengthCurve);
  }

  public Function getPassiveForceLengthCurve() {
    long cPtr = opensimModelJNI.Delp1990Muscle_getPassiveForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setPassiveForceLengthCurve(Function aPassiveForceLengthCurve) {
    return opensimModelJNI.Delp1990Muscle_setPassiveForceLengthCurve(swigCPtr, this, Function.getCPtr(aPassiveForceLengthCurve), aPassiveForceLengthCurve);
  }

  public Function getTendonForceLengthCurve() {
    long cPtr = opensimModelJNI.Delp1990Muscle_getTendonForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setTendonForceLengthCurve(Function aTendonForceLengthCurve) {
    return opensimModelJNI.Delp1990Muscle_setTendonForceLengthCurve(swigCPtr, this, Function.getCPtr(aTendonForceLengthCurve), aTendonForceLengthCurve);
  }

  public Function getForceVelocityCurve() {
    long cPtr = opensimModelJNI.Delp1990Muscle_getForceVelocityCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setForceVelocityCurve(Function aForceVelocityCurve) {
    return opensimModelJNI.Delp1990Muscle_setForceVelocityCurve(swigCPtr, this, Function.getCPtr(aForceVelocityCurve), aForceVelocityCurve);
  }

  public int getStateVariableYIndex(int index) {
    return opensimModelJNI.Delp1990Muscle_getStateVariableYIndex(swigCPtr, this, index);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.Delp1990Muscle_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.Delp1990Muscle_isA(swigCPtr, this, type);
  }

  public static Delp1990Muscle safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.Delp1990Muscle_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new Delp1990Muscle(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.Delp1990Muscle_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
