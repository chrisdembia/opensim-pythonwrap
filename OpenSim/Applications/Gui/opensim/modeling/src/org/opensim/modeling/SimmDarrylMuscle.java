/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmDarrylMuscle extends AbstractMuscle {
  private long swigCPtr;

  public SimmDarrylMuscle(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimmDarrylMuscle obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmDarrylMuscle(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SimmDarrylMuscle() {
    this(opensimModelJNI.new_SimmDarrylMuscle__SWIG_0(), true);
  }

  public SimmDarrylMuscle(SimmDarrylMuscle aMuscle) {
    this(opensimModelJNI.new_SimmDarrylMuscle__SWIG_1(SimmDarrylMuscle.getCPtr(aMuscle), aMuscle), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmDarrylMuscle_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(SimmDarrylMuscle aMuscle) {
    opensimModelJNI.SimmDarrylMuscle_copyData(swigCPtr, this, SimmDarrylMuscle.getCPtr(aMuscle), aMuscle);
  }

  public double getMaxIsometricForce() {
    return opensimModelJNI.SimmDarrylMuscle_getMaxIsometricForce(swigCPtr, this);
  }

  public double getOptimalFiberLength() {
    return opensimModelJNI.SimmDarrylMuscle_getOptimalFiberLength(swigCPtr, this);
  }

  public double getTendonSlackLength() {
    return opensimModelJNI.SimmDarrylMuscle_getTendonSlackLength(swigCPtr, this);
  }

  public double getPennationAngleAtOptimalFiberLength() {
    return opensimModelJNI.SimmDarrylMuscle_getPennationAngleAtOptimalFiberLength(swigCPtr, this);
  }

  public double getActivationTimeConstant() {
    return opensimModelJNI.SimmDarrylMuscle_getActivationTimeConstant(swigCPtr, this);
  }

  public double getDeactivationTimeConstant() {
    return opensimModelJNI.SimmDarrylMuscle_getDeactivationTimeConstant(swigCPtr, this);
  }

  public double getVmax() {
    return opensimModelJNI.SimmDarrylMuscle_getVmax(swigCPtr, this);
  }

  public double getVmax0() {
    return opensimModelJNI.SimmDarrylMuscle_getVmax0(swigCPtr, this);
  }

  public double getFmaxTendonStrain() {
    return opensimModelJNI.SimmDarrylMuscle_getFmaxTendonStrain(swigCPtr, this);
  }

  public double getFmaxMuscleStrain() {
    return opensimModelJNI.SimmDarrylMuscle_getFmaxMuscleStrain(swigCPtr, this);
  }

  public double getKshapeActive() {
    return opensimModelJNI.SimmDarrylMuscle_getKshapeActive(swigCPtr, this);
  }

  public double getKshapePassive() {
    return opensimModelJNI.SimmDarrylMuscle_getKshapePassive(swigCPtr, this);
  }

  public double getDamping() {
    return opensimModelJNI.SimmDarrylMuscle_getDamping(swigCPtr, this);
  }

  public double getAf() {
    return opensimModelJNI.SimmDarrylMuscle_getAf(swigCPtr, this);
  }

  public double getFlen() {
    return opensimModelJNI.SimmDarrylMuscle_getFlen(swigCPtr, this);
  }

  public double getPennationAngle() {
    return opensimModelJNI.SimmDarrylMuscle_getPennationAngle(swigCPtr, this);
  }

  public double getFiberLength() {
    return opensimModelJNI.SimmDarrylMuscle_getFiberLength(swigCPtr, this);
  }

  public double getNormalizedFiberLength() {
    return opensimModelJNI.SimmDarrylMuscle_getNormalizedFiberLength(swigCPtr, this);
  }

  public double getPassiveFiberForce() {
    return opensimModelJNI.SimmDarrylMuscle_getPassiveFiberForce(swigCPtr, this);
  }

  public double getStress() {
    return opensimModelJNI.SimmDarrylMuscle_getStress(swigCPtr, this);
  }

  public void computeStateDerivatives(double[] rDYDT) {
    opensimModelJNI.SimmDarrylMuscle_computeStateDerivatives(swigCPtr, this, rDYDT);
  }

  public void computeActuation() {
    opensimModelJNI.SimmDarrylMuscle_computeActuation(swigCPtr, this);
  }

  public double calcTendonForce(double aNormTendonLength) {
    return opensimModelJNI.SimmDarrylMuscle_calcTendonForce(swigCPtr, this, aNormTendonLength);
  }

  public double calcPassiveForce(double aNormFiberLength) {
    return opensimModelJNI.SimmDarrylMuscle_calcPassiveForce(swigCPtr, this, aNormFiberLength);
  }

  public double calcActiveForce(double aNormFiberLength) {
    return opensimModelJNI.SimmDarrylMuscle_calcActiveForce(swigCPtr, this, aNormFiberLength);
  }

  public double calcFiberVelocity(double aActivation, double aActiveForce, double aVelocityDependentForce) {
    return opensimModelJNI.SimmDarrylMuscle_calcFiberVelocity(swigCPtr, this, aActivation, aActiveForce, aVelocityDependentForce);
  }

  public double computeIsometricForce(double activation) {
    return opensimModelJNI.SimmDarrylMuscle_computeIsometricForce(swigCPtr, this, activation);
  }

  public void postScale(ScaleSet aScaleSet) {
    opensimModelJNI.SimmDarrylMuscle_postScale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.SimmDarrylMuscle_scale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void setup(Model aModel) {
    opensimModelJNI.SimmDarrylMuscle_setup(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void peteTest() {
    opensimModelJNI.SimmDarrylMuscle_peteTest(swigCPtr, this);
  }

}
