/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimtkAnimationCallback extends IntegCallback {
  private long swigCPtr;

  public SimtkAnimationCallback(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimtkAnimationCallback obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      throw new UnsupportedOperationException("C++ destructor does not have public access");
    }
    swigCPtr = 0;
    super.delete();
  }

  public static SimtkAnimationCallback CreateAnimationCallback(AbstractModel aModel) {
    long cPtr = opensimModelJNI.SimtkAnimationCallback_CreateAnimationCallback(AbstractModel.getCPtr(aModel));
    return (cPtr == 0) ? null : new SimtkAnimationCallback(cPtr, false);
  }

  public double getCurrentTime() {
    return opensimModelJNI.SimtkAnimationCallback_getCurrentTime(swigCPtr);
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.SimtkAnimationCallback_step__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.SimtkAnimationCallback_step__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.SimtkAnimationCallback_begin__SWIG_0(swigCPtr, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.SimtkAnimationCallback_begin__SWIG_1(swigCPtr, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public Transform getBodyTransform(int bodyIndex) {
    long cPtr = opensimModelJNI.SimtkAnimationCallback_getBodyTransform(swigCPtr, bodyIndex);
    return (cPtr == 0) ? null : new Transform(cPtr, false);
  }

  public void extractOffsets(AbstractModel displayModel) {
    opensimModelJNI.SimtkAnimationCallback_extractOffsets(swigCPtr, AbstractModel.getCPtr(displayModel));
  }

}
