/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class BodySet extends ModelComponentSetBodies {
  private long swigCPtr;

  public BodySet(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.BodySet_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(BodySet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_BodySet(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public BodySet() {
    this(opensimModelJNI.new_BodySet__SWIG_0(), true);
  }

  public BodySet(Model model) {
    this(opensimModelJNI.new_BodySet__SWIG_1(Model.getCPtr(model), model), true);
  }

  public BodySet(BodySet aAbsBodySet) {
    this(opensimModelJNI.new_BodySet__SWIG_2(BodySet.getCPtr(aAbsBodySet), aAbsBodySet), true);
  }

  public void setup(Model aModel) {
    opensimModelJNI.BodySet_setup(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public BodySet(Model model, String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_BodySet__SWIG_3(Model.getCPtr(model), model, aFileName, aUpdateFromXMLNode), true);
  }

  public BodySet(Model model, String aFileName) {
    this(opensimModelJNI.new_BodySet__SWIG_4(Model.getCPtr(model), model, aFileName), true);
  }

  public void scale(ScaleSet aScaleSet, boolean aScaleMass) {
    opensimModelJNI.BodySet_scale__SWIG_0(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet, aScaleMass);
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.BodySet_scale__SWIG_1(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

}
