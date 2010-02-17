/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ModelComponentSetForces extends SetForces {
  private long swigCPtr;

  public ModelComponentSetForces(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ModelComponentSetForces obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_ModelComponentSetForces(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public ModelComponentSetForces() {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_0(), true);
  }

  public ModelComponentSetForces(Model model) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_1(Model.getCPtr(model), model), true);
  }

  public ModelComponentSetForces(Model model, String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_2(Model.getCPtr(model), model, aFileName, aUpdateFromXMLNode), true);
  }

  public ModelComponentSetForces(Model model, String aFileName) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_3(Model.getCPtr(model), model, aFileName), true);
  }

  public ModelComponentSetForces(ModelComponentSetForces aSet) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_4(ModelComponentSetForces.getCPtr(aSet), aSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.ModelComponentSetForces_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public boolean append(Force aObject) {
    return opensimModelJNI.ModelComponentSetForces_append__SWIG_0(swigCPtr, this, Force.getCPtr(aObject), aObject);
  }

  public boolean insert(int aIndex, Force aObject) {
    return opensimModelJNI.ModelComponentSetForces_insert(swigCPtr, this, aIndex, Force.getCPtr(aObject), aObject);
  }

  public boolean set(int aIndex, Force aObject, boolean preserveGroups) {
    return opensimModelJNI.ModelComponentSetForces_set__SWIG_0(swigCPtr, this, aIndex, Force.getCPtr(aObject), aObject, preserveGroups);
  }

  public boolean set(int aIndex, Force aObject) {
    return opensimModelJNI.ModelComponentSetForces_set__SWIG_1(swigCPtr, this, aIndex, Force.getCPtr(aObject), aObject);
  }

}