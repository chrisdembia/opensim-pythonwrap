/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class FreeJoint extends Joint {
  private long swigCPtr;

  public FreeJoint(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.FreeJoint_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(FreeJoint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_FreeJoint(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static FreeJoint safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.FreeJoint_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new FreeJoint(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.FreeJoint_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.FreeJoint_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.FreeJoint_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new FreeJoint(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.FreeJoint_getConcreteClassName(swigCPtr, this);
  }

  public FreeJoint() {
    this(opensimModelJNI.new_FreeJoint__SWIG_0(), true);
  }

  public FreeJoint(String name, Body parent, SWIGTYPE_p_SimTK__Vec3 locationInParent, SWIGTYPE_p_SimTK__Vec3 orientationInParent, Body body, SWIGTYPE_p_SimTK__Vec3 locationInBody, SWIGTYPE_p_SimTK__Vec3 orientationInBody, boolean reverse) {
    this(opensimModelJNI.new_FreeJoint__SWIG_1(name, Body.getCPtr(parent), parent, SWIGTYPE_p_SimTK__Vec3.getCPtr(locationInParent), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientationInParent), Body.getCPtr(body), body, SWIGTYPE_p_SimTK__Vec3.getCPtr(locationInBody), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientationInBody), reverse), true);
  }

  public FreeJoint(String name, Body parent, SWIGTYPE_p_SimTK__Vec3 locationInParent, SWIGTYPE_p_SimTK__Vec3 orientationInParent, Body body, SWIGTYPE_p_SimTK__Vec3 locationInBody, SWIGTYPE_p_SimTK__Vec3 orientationInBody) {
    this(opensimModelJNI.new_FreeJoint__SWIG_2(name, Body.getCPtr(parent), parent, SWIGTYPE_p_SimTK__Vec3.getCPtr(locationInParent), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientationInParent), Body.getCPtr(body), body, SWIGTYPE_p_SimTK__Vec3.getCPtr(locationInBody), SWIGTYPE_p_SimTK__Vec3.getCPtr(orientationInBody)), true);
  }

  public FreeJoint(FreeJoint aJoint) {
    this(opensimModelJNI.new_FreeJoint__SWIG_3(FreeJoint.getCPtr(aJoint), aJoint), true);
  }

  public void copyData(FreeJoint aJoint) {
    opensimModelJNI.FreeJoint_copyData(swigCPtr, this, FreeJoint.getCPtr(aJoint), aJoint);
  }

  public int numCoordinates() {
    return opensimModelJNI.FreeJoint_numCoordinates(swigCPtr, this);
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.FreeJoint_scale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void connectToModel(Model aModel) {
    opensimModelJNI.FreeJoint_connectToModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

}
