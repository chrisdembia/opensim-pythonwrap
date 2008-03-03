/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ContactForceSet extends ActuatorSet {
  private long swigCPtr;

  public ContactForceSet(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ContactForceSet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_ContactForceSet(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public ContactForceSet() {
    this(opensimModelJNI.new_ContactForceSet__SWIG_0(), true);
  }

  public ContactForceSet(String aFileName) {
    this(opensimModelJNI.new_ContactForceSet__SWIG_1(aFileName), true);
  }

  public ContactForceSet(ContactForceSet aContactForceSet) {
    this(opensimModelJNI.new_ContactForceSet__SWIG_2(ContactForceSet.getCPtr(aContactForceSet), aContactForceSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.ContactForceSet_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(ContactForceSet aContactForceSet) {
    opensimModelJNI.ContactForceSet_copyData(swigCPtr, this, ContactForceSet.getCPtr(aContactForceSet), aContactForceSet);
  }

  public boolean append(SWIGTYPE_p_OpenSim__ContactForce aContact) {
    return opensimModelJNI.ContactForceSet_append__SWIG_0(swigCPtr, this, SWIGTYPE_p_OpenSim__ContactForce.getCPtr(aContact));
  }

  public boolean append(ContactForceSet aContactForceSet, boolean aAllowDuplicateNames) {
    return opensimModelJNI.ContactForceSet_append__SWIG_1(swigCPtr, this, ContactForceSet.getCPtr(aContactForceSet), aContactForceSet, aAllowDuplicateNames);
  }

  public boolean append(ContactForceSet aContactForceSet) {
    return opensimModelJNI.ContactForceSet_append__SWIG_2(swigCPtr, this, ContactForceSet.getCPtr(aContactForceSet), aContactForceSet);
  }

  public boolean set(int aIndex, SWIGTYPE_p_OpenSim__ContactForce aContact) {
    return opensimModelJNI.ContactForceSet_set(swigCPtr, this, aIndex, SWIGTYPE_p_OpenSim__ContactForce.getCPtr(aContact));
  }

  public AbstractBody getContactBodyA(int aID) {
    long cPtr = opensimModelJNI.ContactForceSet_getContactBodyA(swigCPtr, this, aID);
    return (cPtr == 0) ? null : new AbstractBody(cPtr, false);
  }

  public AbstractBody getContactBodyB(int aID) {
    long cPtr = opensimModelJNI.ContactForceSet_getContactBodyB(swigCPtr, this, aID);
    return (cPtr == 0) ? null : new AbstractBody(cPtr, false);
  }

  public void setContactPointA(int aID, SWIGTYPE_p_SimTK__Vec3 aPoint) {
    opensimModelJNI.ContactForceSet_setContactPointA(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint));
  }

  public void getContactPointA(int aID, SWIGTYPE_p_SimTK__Vec3 rPoint) {
    opensimModelJNI.ContactForceSet_getContactPointA(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(rPoint));
  }

  public void setContactPointB(int aID, SWIGTYPE_p_SimTK__Vec3 aPoint) {
    opensimModelJNI.ContactForceSet_setContactPointB(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint));
  }

  public void getContactPointB(int aID, SWIGTYPE_p_SimTK__Vec3 rPoint) {
    opensimModelJNI.ContactForceSet_getContactPointB(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(rPoint));
  }

  public void getContactForce(int aID, SWIGTYPE_p_SimTK__Vec3 rF) {
    opensimModelJNI.ContactForceSet_getContactForce__SWIG_0(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(rF));
  }

  public void getContactNormalForce(int aID, SWIGTYPE_p_SimTK__Vec3 rFP, SWIGTYPE_p_SimTK__Vec3 rFV, SWIGTYPE_p_SimTK__Vec3 rF) {
    opensimModelJNI.ContactForceSet_getContactNormalForce(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(rFP), SWIGTYPE_p_SimTK__Vec3.getCPtr(rFV), SWIGTYPE_p_SimTK__Vec3.getCPtr(rF));
  }

  public void getContactTangentForce(int aID, SWIGTYPE_p_SimTK__Vec3 rFP, SWIGTYPE_p_SimTK__Vec3 rFV, SWIGTYPE_p_SimTK__Vec3 rF) {
    opensimModelJNI.ContactForceSet_getContactTangentForce(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(rFP), SWIGTYPE_p_SimTK__Vec3.getCPtr(rFV), SWIGTYPE_p_SimTK__Vec3.getCPtr(rF));
  }

  public void getContactStiffness(int aID, SWIGTYPE_p_SimTK__Vec3 aDX, SWIGTYPE_p_SimTK__Vec3 rDF) {
    opensimModelJNI.ContactForceSet_getContactStiffness(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(aDX), SWIGTYPE_p_SimTK__Vec3.getCPtr(rDF));
  }

  public void getContactViscosity(int aID, SWIGTYPE_p_SimTK__Vec3 aDV, SWIGTYPE_p_SimTK__Vec3 rDF) {
    opensimModelJNI.ContactForceSet_getContactViscosity(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(aDV), SWIGTYPE_p_SimTK__Vec3.getCPtr(rDF));
  }

  public void getContactFrictionCorrection(int aID, SWIGTYPE_p_SimTK__Vec3 aDFFric) {
    opensimModelJNI.ContactForceSet_getContactFrictionCorrection(swigCPtr, this, aID, SWIGTYPE_p_SimTK__Vec3.getCPtr(aDFFric));
  }

  public double getContactForce(int aID) {
    return opensimModelJNI.ContactForceSet_getContactForce__SWIG_1(swigCPtr, this, aID);
  }

  public double getContactSpeed(int aID) {
    return opensimModelJNI.ContactForceSet_getContactSpeed(swigCPtr, this, aID);
  }

  public double getContactPower(int aID) {
    return opensimModelJNI.ContactForceSet_getContactPower(swigCPtr, this, aID);
  }

  public void computeContact() {
    opensimModelJNI.ContactForceSet_computeContact(swigCPtr, this);
  }

  public void updatePseudoStates() {
    opensimModelJNI.ContactForceSet_updatePseudoStates(swigCPtr, this);
  }

  public void apply() {
    opensimModelJNI.ContactForceSet_apply(swigCPtr, this);
  }

  public boolean check() {
    return opensimModelJNI.ContactForceSet_check(swigCPtr, this);
  }

}
