/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class BodyScaleSet extends SetBodyScales {
  private long swigCPtr;

  public BodyScaleSet(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.BodyScaleSet_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(BodyScaleSet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_BodyScaleSet(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public BodyScaleSet() {
    this(opensimModelJNI.new_BodyScaleSet__SWIG_0(), true);
  }

  public BodyScaleSet(BodyScaleSet aBodyScaleSet) {
    this(opensimModelJNI.new_BodyScaleSet__SWIG_1(BodyScaleSet.getCPtr(aBodyScaleSet), aBodyScaleSet), true);
  }

}
