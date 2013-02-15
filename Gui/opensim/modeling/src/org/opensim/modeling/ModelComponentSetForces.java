/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ModelComponentSetForces extends SetForces {
  private long swigCPtr;

  public ModelComponentSetForces(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.ModelComponentSetForces_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ModelComponentSetForces obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_ModelComponentSetForces(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static ModelComponentSetForces safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.ModelComponentSetForces_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new ModelComponentSetForces(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.ModelComponentSetForces_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.ModelComponentSetForces_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.ModelComponentSetForces_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new ModelComponentSetForces(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.ModelComponentSetForces_getConcreteClassName(swigCPtr, this);
  }

  public ModelComponentSetForces() {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_0(), true);
  }

  public ModelComponentSetForces(Model model) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_1(Model.getCPtr(model), model), true);
  }

  public ModelComponentSetForces(Model model, String fileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_2(Model.getCPtr(model), model, fileName, aUpdateFromXMLNode), true);
  }

  public ModelComponentSetForces(Model model, String fileName) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_3(Model.getCPtr(model), model, fileName), true);
  }

  public ModelComponentSetForces(ModelComponentSetForces source) {
    this(opensimModelJNI.new_ModelComponentSetForces__SWIG_4(ModelComponentSetForces.getCPtr(source), source), true);
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

  public void invokeConnectToModel(Model model) {
    opensimModelJNI.ModelComponentSetForces_invokeConnectToModel(swigCPtr, this, Model.getCPtr(model), model);
  }

  public void invokeAddToSystem(SWIGTYPE_p_SimTK__MultibodySystem system) {
    opensimModelJNI.ModelComponentSetForces_invokeAddToSystem(swigCPtr, this, SWIGTYPE_p_SimTK__MultibodySystem.getCPtr(system));
  }

  public void invokeInitStateFromProperties(State state) {
    opensimModelJNI.ModelComponentSetForces_invokeInitStateFromProperties(swigCPtr, this, State.getCPtr(state), state);
  }

  public void invokeSetPropertiesFromState(State state) {
    opensimModelJNI.ModelComponentSetForces_invokeSetPropertiesFromState(swigCPtr, this, State.getCPtr(state), state);
  }

  public void invokeGenerateDecorations(boolean fixed, ModelDisplayHints hints, State state, SWIGTYPE_p_SimTK__Array_T_SimTK__DecorativeGeometry_t appendToThis) {
    opensimModelJNI.ModelComponentSetForces_invokeGenerateDecorations(swigCPtr, this, fixed, ModelDisplayHints.getCPtr(hints), hints, State.getCPtr(state), state, SWIGTYPE_p_SimTK__Array_T_SimTK__DecorativeGeometry_t.getCPtr(appendToThis));
  }

}
