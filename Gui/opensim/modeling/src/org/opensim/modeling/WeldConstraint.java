/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class WeldConstraint extends Constraint {
  private long swigCPtr;

  public WeldConstraint(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.WeldConstraint_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(WeldConstraint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_WeldConstraint(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static WeldConstraint safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.WeldConstraint_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new WeldConstraint(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.WeldConstraint_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.WeldConstraint_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.WeldConstraint_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new WeldConstraint(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.WeldConstraint_getConcreteClassName(swigCPtr, this);
  }

  public WeldConstraint() {
    this(opensimModelJNI.new_WeldConstraint__SWIG_0(), true);
  }

  public WeldConstraint(String name, Body body1, SWIGTYPE_p_SimTK__Vec3 locationInBody1, SWIGTYPE_p_SimTK__Vec3 orientationInBody1, Body body2, SWIGTYPE_p_SimTK__Vec3 locationInBody2, SWIGTYPE_p_SimTK__Vec3 orientationInBody2) {
    this(opensimModelJNI.new_WeldConstraint__SWIG_1(name, Body.getCPtr(body1), body1, SWIGTYPE_p_SimTK__Vec3.getCPtr(locationInBody1), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientationInBody1), Body.getCPtr(body2), body2, SWIGTYPE_p_SimTK__Vec3.getCPtr(locationInBody2), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientationInBody2)), true);
  }

  public WeldConstraint(String name, Body body1, SWIGTYPE_p_SimTK__Transform transformInBody1, Body body2, SWIGTYPE_p_SimTK__Transform transformInBody2) {
    this(opensimModelJNI.new_WeldConstraint__SWIG_2(name, Body.getCPtr(body1), body1, SWIGTYPE_p_SimTK__Transform.getCPtr(transformInBody1), Body.getCPtr(body2), body2, SWIGTYPE_p_SimTK__Transform.getCPtr(transformInBody2)), true);
  }

  public void setBody1ByName(String aBodyName) {
    opensimModelJNI.WeldConstraint_setBody1ByName(swigCPtr, this, aBodyName);
  }

  public void setBody1WeldLocation(SWIGTYPE_p_SimTK__Vec3 location, SWIGTYPE_p_SimTK__Vec3 orientation) {
    opensimModelJNI.WeldConstraint_setBody1WeldLocation__SWIG_0(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(location), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientation));
  }

  public void setBody1WeldLocation(SWIGTYPE_p_SimTK__Vec3 location) {
    opensimModelJNI.WeldConstraint_setBody1WeldLocation__SWIG_1(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(location));
  }

  public void setBody2ByName(String aBodyName) {
    opensimModelJNI.WeldConstraint_setBody2ByName(swigCPtr, this, aBodyName);
  }

  public void setBody2WeldLocation(SWIGTYPE_p_SimTK__Vec3 location, SWIGTYPE_p_SimTK__Vec3 orientation) {
    opensimModelJNI.WeldConstraint_setBody2WeldLocation__SWIG_0(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(location), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientation));
  }

  public void setBody2WeldLocation(SWIGTYPE_p_SimTK__Vec3 location) {
    opensimModelJNI.WeldConstraint_setBody2WeldLocation__SWIG_1(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(location));
  }

  public void setContactPointForInducedAccelerations(SWIGTYPE_p_SimTK__State s, SWIGTYPE_p_SimTK__Vec3 point) {
    opensimModelJNI.WeldConstraint_setContactPointForInducedAccelerations(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), SWIGTYPE_p_SimTK__Vec3.getCPtr(point));
  }

}