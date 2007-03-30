/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class WrapEllipsoid extends AbstractWrapObject {
  private long swigCPtr;

  public WrapEllipsoid(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(WrapEllipsoid obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_WrapEllipsoid(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public WrapEllipsoid() {
    this(opensimModelJNI.new_WrapEllipsoid__SWIG_0(), true);
  }

  public WrapEllipsoid(WrapEllipsoid aWrapEllipsoid) {
    this(opensimModelJNI.new_WrapEllipsoid__SWIG_1(WrapEllipsoid.getCPtr(aWrapEllipsoid), aWrapEllipsoid), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.WrapEllipsoid_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(WrapEllipsoid aWrapEllipsoid) {
    opensimModelJNI.WrapEllipsoid_copyData(swigCPtr, this, WrapEllipsoid.getCPtr(aWrapEllipsoid), aWrapEllipsoid);
  }

  public String getWrapTypeName() {
    return opensimModelJNI.WrapEllipsoid_getWrapTypeName(swigCPtr, this);
  }

  public String getDimensionsString() {
    return opensimModelJNI.WrapEllipsoid_getDimensionsString(swigCPtr, this);
  }

  public void scale(ArrayDouble aScaleFactors) {
    opensimModelJNI.WrapEllipsoid_scale(swigCPtr, this, ArrayDouble.getCPtr(aScaleFactors), aScaleFactors);
  }

  public void setup(AbstractDynamicsEngine aEngine, AbstractBody aBody) {
    opensimModelJNI.WrapEllipsoid_setup(swigCPtr, this, AbstractDynamicsEngine.getCPtr(aEngine), aEngine, AbstractBody.getCPtr(aBody), aBody);
  }

  public int wrapLine(ArrayDouble aPoint1, ArrayDouble aPoint2, MuscleWrap aMuscleWrap, SWIGTYPE_p_OpenSim__WrapResult aWrapResult, SWIGTYPE_p_bool aFlag) {
    return opensimModelJNI.WrapEllipsoid_wrapLine(swigCPtr, this, ArrayDouble.getCPtr(aPoint1), aPoint1, ArrayDouble.getCPtr(aPoint2), aPoint2, MuscleWrap.getCPtr(aMuscleWrap), aMuscleWrap, SWIGTYPE_p_OpenSim__WrapResult.getCPtr(aWrapResult), SWIGTYPE_p_bool.getCPtr(aFlag));
  }

  public void peteTest() {
    opensimModelJNI.WrapEllipsoid_peteTest(swigCPtr, this);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.WrapEllipsoid_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.WrapEllipsoid_isA(swigCPtr, this, type);
  }

  public static WrapEllipsoid safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.WrapEllipsoid_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new WrapEllipsoid(cPtr, false);
  }

}
