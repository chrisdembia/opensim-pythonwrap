/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ModelComponent extends OpenSimObject {
  private long swigCPtr;

  public ModelComponent(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.ModelComponent_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ModelComponent obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_ModelComponent(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ModelComponent() {
    this(opensimModelJNI.new_ModelComponent__SWIG_0(), true);
  }

  public ModelComponent(String aFileName, boolean aUpdateFromXMLNode) throws java.io.IOException {
    this(opensimModelJNI.new_ModelComponent__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public ModelComponent(String aFileName) throws java.io.IOException {
    this(opensimModelJNI.new_ModelComponent__SWIG_2(aFileName), true);
  }

  public ModelComponent(SWIGTYPE_p_SimTK__Xml__Element aNode) {
    this(opensimModelJNI.new_ModelComponent__SWIG_3(SWIGTYPE_p_SimTK__Xml__Element.getCPtr(aNode)), true);
  }

  public ModelComponent(ModelComponent copy) {
    this(opensimModelJNI.new_ModelComponent__SWIG_4(ModelComponent.getCPtr(copy), copy), true);
  }

  public Model getModel() {
    return new Model(opensimModelJNI.ModelComponent_getModel(swigCPtr, this), false);
  }

  public Model updModel() {
    return new Model(opensimModelJNI.ModelComponent_updModel(swigCPtr, this), false);
  }

  public void updateDisplayer(SWIGTYPE_p_SimTK__State s) {
    opensimModelJNI.ModelComponent_updateDisplayer(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public int getNumStateVariables() {
    return opensimModelJNI.ModelComponent_getNumStateVariables(swigCPtr, this);
  }

  public ArrayStr getStateVariableNames() {
    return new ArrayStr(opensimModelJNI.ModelComponent_getStateVariableNames(swigCPtr, this), true);
  }

  public SWIGTYPE_p_SimTK__SystemYIndex getStateVariableSystemIndex(String stateVariableName) {
    return new SWIGTYPE_p_SimTK__SystemYIndex(opensimModelJNI.ModelComponent_getStateVariableSystemIndex(swigCPtr, this, stateVariableName), true);
  }

  public int getModelingOption(SWIGTYPE_p_SimTK__State state, String name) {
    return opensimModelJNI.ModelComponent_getModelingOption(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name);
  }

  public void setModelingOption(SWIGTYPE_p_SimTK__State state, String name, int flag) {
    opensimModelJNI.ModelComponent_setModelingOption(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name, flag);
  }

  public double getStateVariable(SWIGTYPE_p_SimTK__State state, String name) {
    return opensimModelJNI.ModelComponent_getStateVariable(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name);
  }

  public void setStateVariable(SWIGTYPE_p_SimTK__State state, String name, double value) {
    opensimModelJNI.ModelComponent_setStateVariable(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name, value);
  }

  public double getDiscreteVariable(SWIGTYPE_p_SimTK__State state, String name) {
    return opensimModelJNI.ModelComponent_getDiscreteVariable(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name);
  }

  public void setDiscreteVariable(SWIGTYPE_p_SimTK__State state, String name, double value) {
    opensimModelJNI.ModelComponent_setDiscreteVariable(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name, value);
  }

  public void markCacheVariableValid(SWIGTYPE_p_SimTK__State state, String name) {
    opensimModelJNI.ModelComponent_markCacheVariableValid(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name);
  }

  public boolean isCacheVariableValid(SWIGTYPE_p_SimTK__State state, String name) {
    return opensimModelJNI.ModelComponent_isCacheVariableValid(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name);
  }

}
