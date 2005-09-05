/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package simtksuS26Pkg;

import simtkModel.*;

public class rdActuatedModel_SDFast extends rdSDFast {
  private long swigCPtr;

  protected rdActuatedModel_SDFast(long cPtr, boolean cMemoryOwn) {
    super(suS26ModuleJNI.SWIGrdActuatedModel_SDFastTordSDFast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected rdActuatedModel_SDFast() {
    this(0, false);
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      suS26ModuleJNI.delete_rdActuatedModel_SDFast(swigCPtr);
      swigCMemOwn = false;
      super.delete();
    }
    swigCPtr = 0;
  }

  protected static long getCPtr(rdActuatedModel_SDFast obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public rdActuatedModel_SDFast(rdActuatorSet aActuators, rdContactForceSet aContacts) {
    this(suS26ModuleJNI.new_rdActuatedModel_SDFast__SWIG_0(rdActuatorSet.getCPtr(aActuators), rdContactForceSet.getCPtr(aContacts)), true);
  }

  public rdActuatedModel_SDFast(String aFileName, rdActuatorSet aActuators, rdContactForceSet aContacts) {
    this(suS26ModuleJNI.new_rdActuatedModel_SDFast__SWIG_1(aFileName, rdActuatorSet.getCPtr(aActuators), rdContactForceSet.getCPtr(aContacts)), true);
  }

  public int getNX() {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getNX(swigCPtr);
  }

  public int getNA() {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getNA(swigCPtr);
  }

  public int getNP() {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getNP(swigCPtr);
  }

  public int getNY() {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getNY(swigCPtr);
  }

  public int getNYP() {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getNYP(swigCPtr);
  }

  public String getActuatorName(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorName(swigCPtr, aIndex);
  }

  public String getControlName(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getControlName(swigCPtr, aIndex);
  }

  public String getStateName(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getStateName(swigCPtr, aIndex);
  }

  public String getPseudoStateName(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getPseudoStateName(swigCPtr, aIndex);
  }

  public int getActuatorIndex(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorIndex(swigCPtr, aName);
  }

  public int getControlIndex(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getControlIndex(swigCPtr, aName);
  }

  public int getStateIndex(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getStateIndex(swigCPtr, aName);
  }

  public int getPseudoStateIndex(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getPseudoStateIndex(swigCPtr, aName);
  }

  public rdActuatorSet getActuatorSet() {
    long cPtr = suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorSet(swigCPtr);
    return (cPtr == 0) ? null : new rdActuatorSet(cPtr, false);
  }

  public rdContactForceSet getContactForceSet() {
    long cPtr = suS26ModuleJNI.rdActuatedModel_SDFast_getContactForceSet(swigCPtr);
    return (cPtr == 0) ? null : new rdContactForceSet(cPtr, false);
  }

  public void setControl(int aIndex, double aValue) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setControl__SWIG_0(swigCPtr, aIndex, aValue);
  }

  public void setControl(String aName, double aValue) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setControl__SWIG_1(swigCPtr, aName, aValue);
  }

  public void setControls(SWIGTYPE_p_double aX) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setControls(swigCPtr, SWIGTYPE_p_double.getCPtr(aX));
  }

  public double getControl(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getControl__SWIG_0(swigCPtr, aName);
  }

  public double getControl(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getControl__SWIG_1(swigCPtr, aIndex);
  }

  public void getControls(SWIGTYPE_p_double aX) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getControls(swigCPtr, SWIGTYPE_p_double.getCPtr(aX));
  }

  public void setStates(SWIGTYPE_p_double aY) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setStates(swigCPtr, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void getStates(SWIGTYPE_p_double rY) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getStates(swigCPtr, SWIGTYPE_p_double.getCPtr(rY));
  }

  public double getState(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getState__SWIG_0(swigCPtr, aIndex);
  }

  public double getState(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getState__SWIG_1(swigCPtr, aName);
  }

  public void setPseudoStates(SWIGTYPE_p_double aYP) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setPseudoStates(swigCPtr, SWIGTYPE_p_double.getCPtr(aYP));
  }

  public void getPseudoStates(SWIGTYPE_p_double rYP) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getPseudoStates(swigCPtr, SWIGTYPE_p_double.getCPtr(rYP));
  }

  public double getPseudoState(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getPseudoState__SWIG_0(swigCPtr, aIndex);
  }

  public double getPseudoState(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getPseudoState__SWIG_1(swigCPtr, aName);
  }

  public void setInitialPseudoStates(SWIGTYPE_p_double aYPI) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setInitialPseudoStates(swigCPtr, SWIGTYPE_p_double.getCPtr(aYPI));
  }

  public double getInitialPseudoState(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getInitialPseudoState__SWIG_0(swigCPtr, aIndex);
  }

  public double getInitialPseudoState(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getInitialPseudoState__SWIG_1(swigCPtr, aName);
  }

  public void getInitialPseudoStates(SWIGTYPE_p_double rYPI) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getInitialPseudoStates(swigCPtr, SWIGTYPE_p_double.getCPtr(rYPI));
  }

  public void setInitialStates(SWIGTYPE_p_double aYI) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setInitialStates(swigCPtr, SWIGTYPE_p_double.getCPtr(aYI));
  }

  public double getInitialState(int aIndex) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getInitialState__SWIG_0(swigCPtr, aIndex);
  }

  public double getInitialState(String aName) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getInitialState__SWIG_1(swigCPtr, aName);
  }

  public void getInitialStates(SWIGTYPE_p_double rYI) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getInitialStates(swigCPtr, SWIGTYPE_p_double.getCPtr(rYI));
  }

  public void computeActuation() {
    suS26ModuleJNI.rdActuatedModel_SDFast_computeActuation(swigCPtr);
  }

  public void computeActuatorStateDerivatives(SWIGTYPE_p_double rDY) {
    suS26ModuleJNI.rdActuatedModel_SDFast_computeActuatorStateDerivatives(swigCPtr, SWIGTYPE_p_double.getCPtr(rDY));
  }

  public void applyActuatorForce(int aID) {
    suS26ModuleJNI.rdActuatedModel_SDFast_applyActuatorForce(swigCPtr, aID);
  }

  public void applyActuatorForces() {
    suS26ModuleJNI.rdActuatedModel_SDFast_applyActuatorForces(swigCPtr);
  }

  public void setActuatorForce(int aID, double aForce) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setActuatorForce(swigCPtr, aID, aForce);
  }

  public double getActuatorForce(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorForce(swigCPtr, aID);
  }

  public double getActuatorStress(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorStress(swigCPtr, aID);
  }

  public double getActuatorSpeed(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorSpeed(swigCPtr, aID);
  }

  public double getActuatorPower(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getActuatorPower(swigCPtr, aID);
  }

  public void computeContact() {
    suS26ModuleJNI.rdActuatedModel_SDFast_computeContact(swigCPtr);
  }

  public void applyContactForce(int aID) {
    suS26ModuleJNI.rdActuatedModel_SDFast_applyContactForce(swigCPtr, aID);
  }

  public void applyContactForces() {
    suS26ModuleJNI.rdActuatedModel_SDFast_applyContactForces(swigCPtr);
  }

  public int getContactBodyA(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getContactBodyA(swigCPtr, aID);
  }

  public int getContactBodyB(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getContactBodyB(swigCPtr, aID);
  }

  public void setContactPointA(int aID, SWIGTYPE_p_double aPoint) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setContactPointA(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(aPoint));
  }

  public void getContactPointA(int aID, SWIGTYPE_p_double rPoint) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactPointA(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(rPoint));
  }

  public void setContactPointB(int aID, SWIGTYPE_p_double aPoint) {
    suS26ModuleJNI.rdActuatedModel_SDFast_setContactPointB(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(aPoint));
  }

  public void getContactPointB(int aID, SWIGTYPE_p_double rPoint) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactPointB(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(rPoint));
  }

  public void getContactForce(int aID, SWIGTYPE_p_double rF) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactForce__SWIG_0(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(rF));
  }

  public void getContactNormalForce(int aID, SWIGTYPE_p_double rFP, SWIGTYPE_p_double rFV, SWIGTYPE_p_double rF) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactNormalForce(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(rFP), SWIGTYPE_p_double.getCPtr(rFV), SWIGTYPE_p_double.getCPtr(rF));
  }

  public void getContactTangentForce(int aID, SWIGTYPE_p_double rFP, SWIGTYPE_p_double rFV, SWIGTYPE_p_double rF) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactTangentForce(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(rFP), SWIGTYPE_p_double.getCPtr(rFV), SWIGTYPE_p_double.getCPtr(rF));
  }

  public void getContactStiffness(int aID, SWIGTYPE_p_double aDX, SWIGTYPE_p_double rDF) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactStiffness(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(aDX), SWIGTYPE_p_double.getCPtr(rDF));
  }

  public void getContactViscosity(int aID, SWIGTYPE_p_double aDV, SWIGTYPE_p_double rDF) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactViscosity(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(aDV), SWIGTYPE_p_double.getCPtr(rDF));
  }

  public void getContactFrictionCorrection(int aID, SWIGTYPE_p_double rDFFric) {
    suS26ModuleJNI.rdActuatedModel_SDFast_getContactFrictionCorrection(swigCPtr, aID, SWIGTYPE_p_double.getCPtr(rDFFric));
  }

  public double getContactForce(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getContactForce__SWIG_1(swigCPtr, aID);
  }

  public double getContactSpeed(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getContactSpeed(swigCPtr, aID);
  }

  public double getContactPower(int aID) {
    return suS26ModuleJNI.rdActuatedModel_SDFast_getContactPower(swigCPtr, aID);
  }

  public void promoteControlsToStates(SWIGTYPE_p_double aX, double aDT) {
    suS26ModuleJNI.rdActuatedModel_SDFast_promoteControlsToStates(swigCPtr, SWIGTYPE_p_double.getCPtr(aX), aDT);
  }

  public void computeAuxiliaryDerivatives(SWIGTYPE_p_double dydt) {
    suS26ModuleJNI.rdActuatedModel_SDFast_computeAuxiliaryDerivatives(swigCPtr, SWIGTYPE_p_double.getCPtr(dydt));
  }

}
