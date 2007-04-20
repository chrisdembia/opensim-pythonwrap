/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmZajacHill extends AbstractMuscle {
  private long swigCPtr;

  public SimmZajacHill(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimmZajacHill obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmZajacHill(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SimmZajacHill() {
    this(opensimModelJNI.new_SimmZajacHill__SWIG_0(), true);
  }

  public SimmZajacHill(SimmZajacHill aMuscle) {
    this(opensimModelJNI.new_SimmZajacHill__SWIG_1(SimmZajacHill.getCPtr(aMuscle), aMuscle), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmZajacHill_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(SimmZajacHill aMuscle) {
    opensimModelJNI.SimmZajacHill_copyData(swigCPtr, this, SimmZajacHill.getCPtr(aMuscle), aMuscle);
  }

  public double getMaxIsometricForce() {
    return opensimModelJNI.SimmZajacHill_getMaxIsometricForce(swigCPtr, this);
  }

  public double getOptimalFiberLength() {
    return opensimModelJNI.SimmZajacHill_getOptimalFiberLength(swigCPtr, this);
  }

  public double getTendonSlackLength() {
    return opensimModelJNI.SimmZajacHill_getTendonSlackLength(swigCPtr, this);
  }

  public double getPennationAngleAtOptimalFiberLength() {
    return opensimModelJNI.SimmZajacHill_getPennationAngleAtOptimalFiberLength(swigCPtr, this);
  }

  public double getMaxContractionVelocity() {
    return opensimModelJNI.SimmZajacHill_getMaxContractionVelocity(swigCPtr, this);
  }

  public double getTimeScale() {
    return opensimModelJNI.SimmZajacHill_getTimeScale(swigCPtr, this);
  }

  public double getDamping() {
    return opensimModelJNI.SimmZajacHill_getDamping(swigCPtr, this);
  }

  public double getPennationAngle() {
    return opensimModelJNI.SimmZajacHill_getPennationAngle(swigCPtr, this);
  }

  public double getFiberLength() {
    return opensimModelJNI.SimmZajacHill_getFiberLength(swigCPtr, this);
  }

  public double getNormalizedFiberLength() {
    return opensimModelJNI.SimmZajacHill_getNormalizedFiberLength(swigCPtr, this);
  }

  public double getPassiveFiberForce() {
    return opensimModelJNI.SimmZajacHill_getPassiveFiberForce(swigCPtr, this);
  }

  public void computeStateDerivatives(double[] rDYDT) {
    opensimModelJNI.SimmZajacHill_computeStateDerivatives(swigCPtr, this, rDYDT);
  }

  public void computeActuation() {
    opensimModelJNI.SimmZajacHill_computeActuation(swigCPtr, this);
  }

  public void postScale(ScaleSet aScaleSet) {
    opensimModelJNI.SimmZajacHill_postScale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.SimmZajacHill_scale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void setup(Model aModel) {
    opensimModelJNI.SimmZajacHill_setup(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public Function getActiveForceLengthCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getActiveForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public Function getPassiveForceLengthCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getPassiveForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public Function getTendonForceLengthCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getTendonForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public Function getForceVelocityCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getForceVelocityCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public double calcNonzeroPassiveForce(double aNormFiberLength, double aNormFiberVelocity) {
    return opensimModelJNI.SimmZajacHill_calcNonzeroPassiveForce(swigCPtr, this, aNormFiberLength, aNormFiberVelocity);
  }

  public double calcFiberVelocity(double aActivation, double aActiveForce, double aVelocityDependentForce) {
    return opensimModelJNI.SimmZajacHill_calcFiberVelocity(swigCPtr, this, aActivation, aActiveForce, aVelocityDependentForce);
  }

  public double calcTendonForce(double aNormTendonLength) {
    return opensimModelJNI.SimmZajacHill_calcTendonForce(swigCPtr, this, aNormTendonLength);
  }

  public double getStress() {
    return opensimModelJNI.SimmZajacHill_getStress(swigCPtr, this);
  }

  public double computeIsometricForce(double activation) {
    return opensimModelJNI.SimmZajacHill_computeIsometricForce(swigCPtr, this, activation);
  }

  public void peteTest() {
    opensimModelJNI.SimmZajacHill_peteTest(swigCPtr, this);
  }

}
