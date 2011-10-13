/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Schutte1993Muscle extends ActivationFiberLengthMuscle {
  private long swigCPtr;

  public Schutte1993Muscle(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.Schutte1993Muscle_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Schutte1993Muscle obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_Schutte1993Muscle(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Schutte1993Muscle_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(Schutte1993Muscle aMuscle) {
    opensimModelJNI.Schutte1993Muscle_copyData(swigCPtr, this, Schutte1993Muscle.getCPtr(aMuscle), aMuscle);
  }

  public double getTimeScale() {
    return opensimModelJNI.Schutte1993Muscle_getTimeScale(swigCPtr, this);
  }

  public double getDamping() {
    return opensimModelJNI.Schutte1993Muscle_getDamping__SWIG_0(swigCPtr, this);
  }

  public boolean setTimeScale(double aTimeScale) {
    return opensimModelJNI.Schutte1993Muscle_setTimeScale(swigCPtr, this, aTimeScale);
  }

  public boolean setActivation1(double aActivation1) {
    return opensimModelJNI.Schutte1993Muscle_setActivation1(swigCPtr, this, aActivation1);
  }

  public boolean setActivation2(double aActivation2) {
    return opensimModelJNI.Schutte1993Muscle_setActivation2(swigCPtr, this, aActivation2);
  }

  public boolean setDamping(double aDamping) {
    return opensimModelJNI.Schutte1993Muscle_setDamping(swigCPtr, this, aDamping);
  }

  public Function getActiveForceLengthCurve() {
    long cPtr = opensimModelJNI.Schutte1993Muscle_getActiveForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setActiveForceLengthCurve(Function aActiveForceLengthCurve) {
    return opensimModelJNI.Schutte1993Muscle_setActiveForceLengthCurve(swigCPtr, this, Function.getCPtr(aActiveForceLengthCurve), aActiveForceLengthCurve);
  }

  public Function getPassiveForceLengthCurve() {
    long cPtr = opensimModelJNI.Schutte1993Muscle_getPassiveForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setPassiveForceLengthCurve(Function aPassiveForceLengthCurve) {
    return opensimModelJNI.Schutte1993Muscle_setPassiveForceLengthCurve(swigCPtr, this, Function.getCPtr(aPassiveForceLengthCurve), aPassiveForceLengthCurve);
  }

  public Function getTendonForceLengthCurve() {
    long cPtr = opensimModelJNI.Schutte1993Muscle_getTendonForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setTendonForceLengthCurve(Function aTendonForceLengthCurve) {
    return opensimModelJNI.Schutte1993Muscle_setTendonForceLengthCurve(swigCPtr, this, Function.getCPtr(aTendonForceLengthCurve), aTendonForceLengthCurve);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.Schutte1993Muscle_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.Schutte1993Muscle_isA(swigCPtr, this, type);
  }

  public static Schutte1993Muscle safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.Schutte1993Muscle_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new Schutte1993Muscle(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.Schutte1993Muscle_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
