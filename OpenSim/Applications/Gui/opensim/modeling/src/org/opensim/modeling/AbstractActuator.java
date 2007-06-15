/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class AbstractActuator extends OpenSimObject {
  private long swigCPtr;

  public AbstractActuator(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(AbstractActuator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_AbstractActuator(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static double getLARGE() {
    return opensimModelJNI.AbstractActuator_LARGE_get();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.AbstractActuator_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyPropertyValues(AbstractActuator aActuator) {
    opensimModelJNI.AbstractActuator_copyPropertyValues(swigCPtr, this, AbstractActuator.getCPtr(aActuator), aActuator);
  }

  public void setup(Model aModel) {
    opensimModelJNI.AbstractActuator_setup(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.AbstractActuator_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public Model getModel() {
    long cPtr = opensimModelJNI.AbstractActuator_getModel(swigCPtr, this);
    return (cPtr == 0) ? null : new Model(cPtr, false);
  }

  public int getNumControls() {
    return opensimModelJNI.AbstractActuator_getNumControls(swigCPtr, this);
  }

  public String getControlName(int aIndex) {
    return opensimModelJNI.AbstractActuator_getControlName(swigCPtr, this, aIndex);
  }

  public int getControlIndex(String aName) {
    return opensimModelJNI.AbstractActuator_getControlIndex(swigCPtr, this, aName);
  }

  public void setControl(int aIndex, double aValue) {
    opensimModelJNI.AbstractActuator_setControl(swigCPtr, this, aIndex, aValue);
  }

  public void setControls(double[] aX) {
    opensimModelJNI.AbstractActuator_setControls(swigCPtr, this, aX);
  }

  public double getControl(int aIndex) {
    return opensimModelJNI.AbstractActuator_getControl(swigCPtr, this, aIndex);
  }

  public void getControls(double[] rX) {
    opensimModelJNI.AbstractActuator_getControls(swigCPtr, this, rX);
  }

  public int getNumStates() {
    return opensimModelJNI.AbstractActuator_getNumStates(swigCPtr, this);
  }

  public String getStateName(int aIndex) {
    return opensimModelJNI.AbstractActuator_getStateName(swigCPtr, this, aIndex);
  }

  public int getStateIndex(String aName) {
    return opensimModelJNI.AbstractActuator_getStateIndex(swigCPtr, this, aName);
  }

  public void setState(int aIndex, double aValue) {
    opensimModelJNI.AbstractActuator_setState(swigCPtr, this, aIndex, aValue);
  }

  public void setStates(double[] aY) {
    opensimModelJNI.AbstractActuator_setStates(swigCPtr, this, aY);
  }

  public double getState(int aIndex) {
    return opensimModelJNI.AbstractActuator_getState(swigCPtr, this, aIndex);
  }

  public void getStates(double[] rY) {
    opensimModelJNI.AbstractActuator_getStates(swigCPtr, this, rY);
  }

  public int getNumPseudoStates() {
    return opensimModelJNI.AbstractActuator_getNumPseudoStates(swigCPtr, this);
  }

  public String getPseudoStateName(int aIndex) {
    return opensimModelJNI.AbstractActuator_getPseudoStateName(swigCPtr, this, aIndex);
  }

  public int getPseudoStateIndex(String aName) {
    return opensimModelJNI.AbstractActuator_getPseudoStateIndex(swigCPtr, this, aName);
  }

  public void setPseudoState(int aIndex, double aValue) {
    opensimModelJNI.AbstractActuator_setPseudoState(swigCPtr, this, aIndex, aValue);
  }

  public void setPseudoStates(double[] aY) {
    opensimModelJNI.AbstractActuator_setPseudoStates(swigCPtr, this, aY);
  }

  public double getPseudoState(int aIndex) {
    return opensimModelJNI.AbstractActuator_getPseudoState(swigCPtr, this, aIndex);
  }

  public void getPseudoStates(double[] rY) {
    opensimModelJNI.AbstractActuator_getPseudoStates(swigCPtr, this, rY);
  }

  public VisibleObject getDisplayer() {
    long cPtr = opensimModelJNI.AbstractActuator_getDisplayer(swigCPtr, this);
    return (cPtr == 0) ? null : new VisibleObject(cPtr, false);
  }

  public void updateDisplayer() {
    opensimModelJNI.AbstractActuator_updateDisplayer(swigCPtr, this);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.AbstractActuator_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.AbstractActuator_isA(swigCPtr, this, type);
  }

  public static AbstractActuator safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.AbstractActuator_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new AbstractActuator(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.AbstractActuator_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public boolean getAppliesForce() {
    return opensimModelJNI.AbstractActuator_getAppliesForce(swigCPtr, this);
  }

  public void setForce(double aForce) {
    opensimModelJNI.AbstractActuator_setForce(swigCPtr, this, aForce);
  }

  public double getForce() {
    return opensimModelJNI.AbstractActuator_getForce(swigCPtr, this);
  }

  public double getSpeed() {
    return opensimModelJNI.AbstractActuator_getSpeed(swigCPtr, this);
  }

  public double getPower() {
    return opensimModelJNI.AbstractActuator_getPower(swigCPtr, this);
  }

  public double getStress() {
    return opensimModelJNI.AbstractActuator_getStress(swigCPtr, this);
  }

  public void promoteControlsToStates(double[] aX, double aDT) {
    opensimModelJNI.AbstractActuator_promoteControlsToStates(swigCPtr, this, aX, aDT);
  }

  public void computeActuation() {
    opensimModelJNI.AbstractActuator_computeActuation(swigCPtr, this);
  }

  public void computeStateDerivatives(double[] rDYDT) {
    opensimModelJNI.AbstractActuator_computeStateDerivatives(swigCPtr, this, rDYDT);
  }

  public void computeEquilibrium() {
    opensimModelJNI.AbstractActuator_computeEquilibrium(swigCPtr, this);
  }

  public void updatePseudoStates() {
    opensimModelJNI.AbstractActuator_updatePseudoStates(swigCPtr, this);
  }

  public void apply() {
    opensimModelJNI.AbstractActuator_apply(swigCPtr, this);
  }

  public boolean check() {
    return opensimModelJNI.AbstractActuator_check(swigCPtr, this);
  }

  public void preScale(SWIGTYPE_p_ScaleSet aScaleSet) {
    opensimModelJNI.AbstractActuator_preScale(swigCPtr, this, SWIGTYPE_p_ScaleSet.getCPtr(aScaleSet));
  }

  public void scale(SWIGTYPE_p_ScaleSet aScaleSet) {
    opensimModelJNI.AbstractActuator_scale(swigCPtr, this, SWIGTYPE_p_ScaleSet.getCPtr(aScaleSet));
  }

  public void postScale(SWIGTYPE_p_ScaleSet aScaleSet) {
    opensimModelJNI.AbstractActuator_postScale(swigCPtr, this, SWIGTYPE_p_ScaleSet.getCPtr(aScaleSet));
  }

}
