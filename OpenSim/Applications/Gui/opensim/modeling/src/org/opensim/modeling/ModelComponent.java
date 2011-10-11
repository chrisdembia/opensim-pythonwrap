/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ModelComponent extends OpenSimObject {
  private long swigCPtr;

  public ModelComponent(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
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

  public ModelComponent(SWIGTYPE_p_OpenSim__XMLDocument aDocument) {
    this(opensimModelJNI.new_ModelComponent__SWIG_3(SWIGTYPE_p_OpenSim__XMLDocument.getCPtr(aDocument)), true);
  }

  public ModelComponent(SWIGTYPE_p_DOMElement aNode) {
    this(opensimModelJNI.new_ModelComponent__SWIG_4(SWIGTYPE_p_DOMElement.getCPtr(aNode)), true);
  }

  public ModelComponent(ModelComponent copy) {
    this(opensimModelJNI.new_ModelComponent__SWIG_5(ModelComponent.getCPtr(copy), copy), true);
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

  public int getModelingOption(SWIGTYPE_p_SimTK__State state) {
    return opensimModelJNI.ModelComponent_getModelingOption(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state));
  }

  public void setModelingOption(SWIGTYPE_p_SimTK__State state, int flag) {
    opensimModelJNI.ModelComponent_setModelingOption(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), flag);
  }

  public int getNumStateVariables() {
    return opensimModelJNI.ModelComponent_getNumStateVariables(swigCPtr, this);
  }

  public String getStateVariableName(int index) {
    return opensimModelJNI.ModelComponent_getStateVariableName(swigCPtr, this, index);
  }

  public int getStateVariableYIndex(int index) {
    return opensimModelJNI.ModelComponent_getStateVariableYIndex(swigCPtr, this, index);
  }

  public double getStateVariable(SWIGTYPE_p_SimTK__State state, int index) {
    return opensimModelJNI.ModelComponent_getStateVariable__SWIG_0(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), index);
  }

  public double getStateVariable(SWIGTYPE_p_SimTK__State state, String name) {
    return opensimModelJNI.ModelComponent_getStateVariable__SWIG_1(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name);
  }

  public void setStateVariable(SWIGTYPE_p_SimTK__State state, int index, double value) {
    opensimModelJNI.ModelComponent_setStateVariable__SWIG_0(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), index, value);
  }

  public void setStateVariable(SWIGTYPE_p_SimTK__State state, String name, double value) {
    opensimModelJNI.ModelComponent_setStateVariable__SWIG_1(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), name, value);
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

  public void includeAsSubComponent(ModelComponent aComponent) {
    opensimModelJNI.ModelComponent_includeAsSubComponent(swigCPtr, this, ModelComponent.getCPtr(aComponent), aComponent);
  }

}
