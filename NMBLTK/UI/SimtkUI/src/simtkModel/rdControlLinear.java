/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package simtkModel;


public class rdControlLinear extends rdControl {
  private long swigCPtr;

  
  public  rdControlLinear(long cPtr, boolean cMemoryOwn) {
    super(ModelJNI.SWIGrdControlLinearTordControl(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected rdControlLinear() {
    this(0, false);
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      ModelJNI.delete_rdControlLinear(swigCPtr);
      swigCMemOwn = false;
      super.delete();
    }
    swigCPtr = 0;
  }

  public static long getCPtr(rdControlLinear obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static SWIGTYPE_p_rdControlLinearNode getDEFAULT_NODE() {
    return new SWIGTYPE_p_rdControlLinearNode(ModelJNI.get_rdControlLinear_DEFAULT_NODE(), true);
  }

  public rdControlLinear(SWIGTYPE_p_rdArrayPtrsTrdControlLinearNode_t aX, String aName) {
    this(ModelJNI.new_rdControlLinear__SWIG_0(SWIGTYPE_p_rdArrayPtrsTrdControlLinearNode_t.getCPtr(aX), aName), true);
  }

  public rdControlLinear(SWIGTYPE_p_DOMElement aElement) {
    this(ModelJNI.new_rdControlLinear__SWIG_1(SWIGTYPE_p_DOMElement.getCPtr(aElement)), true);
  }

  public rdControlLinear(rdControlLinear aControl) {
    this(ModelJNI.new_rdControlLinear__SWIG_2(rdControlLinear.getCPtr(aControl)), true);
  }

  public rdObject copy() {
    long cPtr = ModelJNI.rdControlLinear_copy__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new rdObject(cPtr, false);
  }

  public rdObject copy(SWIGTYPE_p_DOMElement aElement) {
    long cPtr = ModelJNI.rdControlLinear_copy__SWIG_1(swigCPtr, SWIGTYPE_p_DOMElement.getCPtr(aElement));
    return (cPtr == 0) ? null : new rdObject(cPtr, false);
  }

  public void setUseSteps(boolean aTrueFalse) {
    ModelJNI.rdControlLinear_setUseSteps(swigCPtr, aTrueFalse);
  }

  public boolean getUseSteps() {
    return ModelJNI.rdControlLinear_getUseSteps(swigCPtr);
  }

  public int getNumParameters() {
    return ModelJNI.rdControlLinear_getNumParameters(swigCPtr);
  }

  public void setParameterMin(int aI, double aMin) {
    ModelJNI.rdControlLinear_setParameterMin(swigCPtr, aI, aMin);
  }

  public double getParameterMin(int aI) {
    return ModelJNI.rdControlLinear_getParameterMin(swigCPtr, aI);
  }

  public void setParameterMax(int aI, double aMax) {
    ModelJNI.rdControlLinear_setParameterMax(swigCPtr, aI, aMax);
  }

  public double getParameterMax(int aI) {
    return ModelJNI.rdControlLinear_getParameterMax(swigCPtr, aI);
  }

  public double getParameterTime(int aI) {
    return ModelJNI.rdControlLinear_getParameterTime(swigCPtr, aI);
  }

  public void getParameterNeighborhood(int aI, SWIGTYPE_p_double rTLower, SWIGTYPE_p_double rTUpper) {
    ModelJNI.rdControlLinear_getParameterNeighborhood(swigCPtr, aI, SWIGTYPE_p_double.getCPtr(rTLower), SWIGTYPE_p_double.getCPtr(rTUpper));
  }

  public int getParameterList(double aT, rdArrayInt rList) {
    return ModelJNI.rdControlLinear_getParameterList__SWIG_0(swigCPtr, aT, rdArrayInt.getCPtr(rList));
  }

  public int getParameterList(double aT1, double aT2, rdArrayInt rList) {
    return ModelJNI.rdControlLinear_getParameterList__SWIG_1(swigCPtr, aT1, aT2, rdArrayInt.getCPtr(rList));
  }

  public void setParameterValue(int aI, double aP) {
    ModelJNI.rdControlLinear_setParameterValue(swigCPtr, aI, aP);
  }

  public double getParameterValue(int aI) {
    return ModelJNI.rdControlLinear_getParameterValue(swigCPtr, aI);
  }

  public void setControlValue(double aT, double aX) {
    ModelJNI.rdControlLinear_setControlValue(swigCPtr, aT, aX);
  }

  public double getControlValue(double aT) {
    return ModelJNI.rdControlLinear_getControlValue(swigCPtr, aT);
  }

  public SWIGTYPE_p_rdArrayPtrsTrdControlLinearNode_t getNodeArray() {
    return new SWIGTYPE_p_rdArrayPtrsTrdControlLinearNode_t(ModelJNI.rdControlLinear_getNodeArray(swigCPtr), false);
  }

  public double getFirstTime() {
    return ModelJNI.rdControlLinear_getFirstTime(swigCPtr);
  }

  public double getLastTime() {
    return ModelJNI.rdControlLinear_getLastTime(swigCPtr);
  }

  public void simplify(rdPropertySet aProperties) {
    ModelJNI.rdControlLinear_simplify(swigCPtr, rdPropertySet.getCPtr(aProperties));
  }

}
