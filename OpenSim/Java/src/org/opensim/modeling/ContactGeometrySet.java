/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ContactGeometrySet extends ModelComponentSetContactGeometry {
  private long swigCPtr;

  public ContactGeometrySet(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.ContactGeometrySet_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ContactGeometrySet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_ContactGeometrySet(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ContactGeometrySet() {
    this(opensimModelJNI.new_ContactGeometrySet__SWIG_0(), true);
  }

  public ContactGeometrySet(Model model) {
    this(opensimModelJNI.new_ContactGeometrySet__SWIG_1(Model.getCPtr(model), model), true);
  }

  public ContactGeometrySet(Model model, String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_ContactGeometrySet__SWIG_2(Model.getCPtr(model), model, aFileName, aUpdateFromXMLNode), true);
  }

  public ContactGeometrySet(ContactGeometrySet aContactGeometrySet) {
    this(opensimModelJNI.new_ContactGeometrySet__SWIG_3(ContactGeometrySet.getCPtr(aContactGeometrySet), aContactGeometrySet), true);
  }

  public void setup(Model aModel) {
    opensimModelJNI.ContactGeometrySet_setup(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.ContactGeometrySet_scale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

}
