/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmZajacHill extends AbstractSimmMuscle {
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

  public void delete() {
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
    this(opensimModelJNI.new_SimmZajacHill__SWIG_1(SimmZajacHill.getCPtr(aMuscle)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmZajacHill_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(SimmZajacHill aMuscle) {
    opensimModelJNI.SimmZajacHill_copyData(swigCPtr, SimmZajacHill.getCPtr(aMuscle));
  }

  public void computeStateDerivatives(double[] rDYDT) {
    opensimModelJNI.SimmZajacHill_computeStateDerivatives(swigCPtr, rDYDT);
  }

  public void computeActuation() {
    opensimModelJNI.SimmZajacHill_computeActuation(swigCPtr);
  }

  public static void registerTypes() {
    opensimModelJNI.SimmZajacHill_registerTypes();
  }

  public void postScale(ScaleSet aScaleSet) {
    opensimModelJNI.SimmZajacHill_postScale(swigCPtr, ScaleSet.getCPtr(aScaleSet));
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.SimmZajacHill_scale(swigCPtr, ScaleSet.getCPtr(aScaleSet));
  }

  public void setup(AbstractModel aModel) {
    opensimModelJNI.SimmZajacHill_setup(swigCPtr, AbstractModel.getCPtr(aModel));
  }

  public double getMaxIsometricForce() {
    return opensimModelJNI.SimmZajacHill_getMaxIsometricForce(swigCPtr);
  }

  public double getOptimalFiberLength() {
    return opensimModelJNI.SimmZajacHill_getOptimalFiberLength(swigCPtr);
  }

  public double getTendonSlackLength() {
    return opensimModelJNI.SimmZajacHill_getTendonSlackLength(swigCPtr);
  }

  public double getPennationAngle() {
    return opensimModelJNI.SimmZajacHill_getPennationAngle(swigCPtr);
  }

  public double getMaxContractionVelocity() {
    return opensimModelJNI.SimmZajacHill_getMaxContractionVelocity(swigCPtr);
  }

  public double getTimeScale() {
    return opensimModelJNI.SimmZajacHill_getTimeScale(swigCPtr);
  }

  public double getDamping() {
    return opensimModelJNI.SimmZajacHill_getDamping(swigCPtr);
  }

  public Function getActiveForceLengthCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getActiveForceLengthCurve(swigCPtr);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public Function getPassiveForceLengthCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getPassiveForceLengthCurve(swigCPtr);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public Function getTendonForceLengthCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getTendonForceLengthCurve(swigCPtr);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public Function getForceVelocityCurve() {
    long cPtr = opensimModelJNI.SimmZajacHill_getForceVelocityCurve(swigCPtr);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public double calcNonzeroPassiveForce(double aNormFiberLength, double aNormFiberVelocity) {
    return opensimModelJNI.SimmZajacHill_calcNonzeroPassiveForce(swigCPtr, aNormFiberLength, aNormFiberVelocity);
  }

  public double calcFiberVelocity(double aActivation, double aActiveForce, double aVelocityDependentForce) {
    return opensimModelJNI.SimmZajacHill_calcFiberVelocity(swigCPtr, aActivation, aActiveForce, aVelocityDependentForce);
  }

  public double calcTendonForce(double aNormTendonLength) {
    return opensimModelJNI.SimmZajacHill_calcTendonForce(swigCPtr, aNormTendonLength);
  }

  public double getStress() {
    return opensimModelJNI.SimmZajacHill_getStress(swigCPtr);
  }

  public double computeIsometricForce(double activation) {
    return opensimModelJNI.SimmZajacHill_computeIsometricForce(swigCPtr, activation);
  }

  public void peteTest() {
    opensimModelJNI.SimmZajacHill_peteTest(swigCPtr);
  }

}
