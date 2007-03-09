/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Control extends OpenSimObject {
  private long swigCPtr;

  public Control(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Control obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Control(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public void setIsModelControl(boolean aTrueFalse) {
    opensimModelJNI.Control_setIsModelControl(swigCPtr, aTrueFalse);
  }

  public boolean getIsModelControl() {
    return opensimModelJNI.Control_getIsModelControl(swigCPtr);
  }

  public void setExtrapolate(boolean aTrueFalse) {
    opensimModelJNI.Control_setExtrapolate(swigCPtr, aTrueFalse);
  }

  public boolean getExtrapolate() {
    return opensimModelJNI.Control_getExtrapolate(swigCPtr);
  }

  public void setFilterOn(boolean aTrueFalse) {
    opensimModelJNI.Control_setFilterOn(swigCPtr, aTrueFalse);
  }

  public boolean getFilterOn() {
    return opensimModelJNI.Control_getFilterOn(swigCPtr);
  }

  public int getNumParameters() {
    return opensimModelJNI.Control_getNumParameters(swigCPtr);
  }

  public void setDefaultParameterMin(double aMin) {
    opensimModelJNI.Control_setDefaultParameterMin(swigCPtr, aMin);
  }

  public double getDefaultParameterMin() {
    return opensimModelJNI.Control_getDefaultParameterMin(swigCPtr);
  }

  public void setDefaultParameterMax(double aMin) {
    opensimModelJNI.Control_setDefaultParameterMax(swigCPtr, aMin);
  }

  public double getDefaultParameterMax() {
    return opensimModelJNI.Control_getDefaultParameterMax(swigCPtr);
  }

  public void setParameterMin(int aI, double aMin) {
    opensimModelJNI.Control_setParameterMin(swigCPtr, aI, aMin);
  }

  public double getParameterMin(int aI) {
    return opensimModelJNI.Control_getParameterMin(swigCPtr, aI);
  }

  public void setParameterMax(int aI, double aMax) {
    opensimModelJNI.Control_setParameterMax(swigCPtr, aI, aMax);
  }

  public double getParameterMax(int aI) {
    return opensimModelJNI.Control_getParameterMax(swigCPtr, aI);
  }

  public double getParameterTime(int aI) {
    return opensimModelJNI.Control_getParameterTime(swigCPtr, aI);
  }

  public void getParameterNeighborhood(int aI, SWIGTYPE_p_double rTLower, SWIGTYPE_p_double rTUpper) {
    opensimModelJNI.Control_getParameterNeighborhood(swigCPtr, aI, SWIGTYPE_p_double.getCPtr(rTLower), SWIGTYPE_p_double.getCPtr(rTUpper));
  }

  public int getParameterList(double aT, ArrayInt rList) {
    return opensimModelJNI.Control_getParameterList__SWIG_0(swigCPtr, aT, ArrayInt.getCPtr(rList));
  }

  public int getParameterList(double aTLower, double aTUpper, ArrayInt rList) {
    return opensimModelJNI.Control_getParameterList__SWIG_1(swigCPtr, aTLower, aTUpper, ArrayInt.getCPtr(rList));
  }

  public double getParameterValue(int aI) {
    return opensimModelJNI.Control_getParameterValue(swigCPtr, aI);
  }

  public void setParameterValue(int aI, double aP) {
    opensimModelJNI.Control_setParameterValue(swigCPtr, aI, aP);
  }

  public double getControlValue(double aT) {
    return opensimModelJNI.Control_getControlValue__SWIG_0(swigCPtr, aT);
  }

  public double getControlValue() {
    return opensimModelJNI.Control_getControlValue__SWIG_1(swigCPtr);
  }

  public void setControlValue(double aT, double aX) {
    opensimModelJNI.Control_setControlValue(swigCPtr, aT, aX);
  }

  public double getControlValueMin(double aT) {
    return opensimModelJNI.Control_getControlValueMin__SWIG_0(swigCPtr, aT);
  }

  public double getControlValueMin() {
    return opensimModelJNI.Control_getControlValueMin__SWIG_1(swigCPtr);
  }

  public void setControlValueMin(double aT, double aX) {
    opensimModelJNI.Control_setControlValueMin(swigCPtr, aT, aX);
  }

  public double getControlValueMax(double aT) {
    return opensimModelJNI.Control_getControlValueMax__SWIG_0(swigCPtr, aT);
  }

  public double getControlValueMax() {
    return opensimModelJNI.Control_getControlValueMax__SWIG_1(swigCPtr);
  }

  public void setControlValueMax(double aT, double aX) {
    opensimModelJNI.Control_setControlValueMax(swigCPtr, aT, aX);
  }

  public double getFirstTime() {
    return opensimModelJNI.Control_getFirstTime(swigCPtr);
  }

  public double getLastTime() {
    return opensimModelJNI.Control_getLastTime(swigCPtr);
  }

  public void simplify(PropertySet aProperties) {
    opensimModelJNI.Control_simplify(swigCPtr, PropertySet.getCPtr(aProperties));
  }

  public void filter(double aT) {
    opensimModelJNI.Control_filter(swigCPtr, aT);
  }

}
