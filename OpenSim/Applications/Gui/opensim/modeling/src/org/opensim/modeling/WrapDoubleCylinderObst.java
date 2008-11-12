/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class WrapDoubleCylinderObst extends AbstractWrapObject {
  private long swigCPtr;

  public WrapDoubleCylinderObst(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(WrapDoubleCylinderObst obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_WrapDoubleCylinderObst(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public WrapDoubleCylinderObst() {
    this(opensimModelJNI.new_WrapDoubleCylinderObst__SWIG_0(), true);
  }

  public WrapDoubleCylinderObst(WrapDoubleCylinderObst aWrapDoubleCylinderObst) {
    this(opensimModelJNI.new_WrapDoubleCylinderObst__SWIG_1(WrapDoubleCylinderObst.getCPtr(aWrapDoubleCylinderObst), aWrapDoubleCylinderObst), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.WrapDoubleCylinderObst_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(WrapDoubleCylinderObst aWrapDoubleCylinderObst) {
    opensimModelJNI.WrapDoubleCylinderObst_copyData(swigCPtr, this, WrapDoubleCylinderObst.getCPtr(aWrapDoubleCylinderObst), aWrapDoubleCylinderObst);
  }

  public double getRadius() {
    return opensimModelJNI.WrapDoubleCylinderObst_getRadius(swigCPtr, this);
  }

  public void setRadius(double aRadius) {
    opensimModelJNI.WrapDoubleCylinderObst_setRadius(swigCPtr, this, aRadius);
  }

  public double getLength() {
    return opensimModelJNI.WrapDoubleCylinderObst_getLength(swigCPtr, this);
  }

  public void setLength(double aLength) {
    opensimModelJNI.WrapDoubleCylinderObst_setLength(swigCPtr, this, aLength);
  }

  public int getWrapDirection() {
    return opensimModelJNI.WrapDoubleCylinderObst_getWrapDirection(swigCPtr, this);
  }

  public String getWrapTypeName() {
    return opensimModelJNI.WrapDoubleCylinderObst_getWrapTypeName(swigCPtr, this);
  }

  public String getDimensionsString() {
    return opensimModelJNI.WrapDoubleCylinderObst_getDimensionsString(swigCPtr, this);
  }

  public void scale(SWIGTYPE_p_SimTK__Vec3 aScaleFactors) {
    opensimModelJNI.WrapDoubleCylinderObst_scale(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(aScaleFactors));
  }

  public void setup(AbstractDynamicsEngine aEngine, AbstractBody aBody) {
    opensimModelJNI.WrapDoubleCylinderObst_setup(swigCPtr, this, AbstractDynamicsEngine.getCPtr(aEngine), aEngine, AbstractBody.getCPtr(aBody), aBody);
  }

  public int wrapLine(SWIGTYPE_p_SimTK__Vec3 aPoint1, SWIGTYPE_p_SimTK__Vec3 aPoint2, MuscleWrap aMuscleWrap, SWIGTYPE_p_OpenSim__WrapResult aWrapResult, SWIGTYPE_p_bool aFlag) {
    return opensimModelJNI.WrapDoubleCylinderObst_wrapLine(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint1), SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint2), MuscleWrap.getCPtr(aMuscleWrap), aMuscleWrap, SWIGTYPE_p_OpenSim__WrapResult.getCPtr(aWrapResult), SWIGTYPE_p_bool.getCPtr(aFlag));
  }

}