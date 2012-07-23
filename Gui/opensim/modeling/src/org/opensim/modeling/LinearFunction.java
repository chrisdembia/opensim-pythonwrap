/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class LinearFunction extends Function {
  private long swigCPtr;

  public LinearFunction(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.LinearFunction_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(LinearFunction obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_LinearFunction(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static LinearFunction safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.LinearFunction_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new LinearFunction(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.LinearFunction_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.LinearFunction_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.LinearFunction_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new LinearFunction(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.LinearFunction_getConcreteClassName(swigCPtr, this);
  }

  public LinearFunction() {
    this(opensimModelJNI.new_LinearFunction__SWIG_0(), true);
  }

  public LinearFunction(ArrayDouble coefficients) {
    this(opensimModelJNI.new_LinearFunction__SWIG_1(ArrayDouble.getCPtr(coefficients), coefficients), true);
  }

  public LinearFunction(double slope, double intercept) {
    this(opensimModelJNI.new_LinearFunction__SWIG_2(slope, intercept), true);
  }

  public LinearFunction(LinearFunction aSpline) {
    this(opensimModelJNI.new_LinearFunction__SWIG_3(LinearFunction.getCPtr(aSpline), aSpline), true);
  }

  public void setCoefficients(ArrayDouble coefficients) {
    opensimModelJNI.LinearFunction_setCoefficients(swigCPtr, this, ArrayDouble.getCPtr(coefficients), coefficients);
  }

  public void setSlope(double slope) {
    opensimModelJNI.LinearFunction_setSlope(swigCPtr, this, slope);
  }

  public void setIntercept(double intercept) {
    opensimModelJNI.LinearFunction_setIntercept(swigCPtr, this, intercept);
  }

  public ArrayDouble getCoefficients() {
    return new ArrayDouble(opensimModelJNI.LinearFunction_getCoefficients(swigCPtr, this), true);
  }

  public double getSlope() {
    return opensimModelJNI.LinearFunction_getSlope(swigCPtr, this);
  }

  public double getIntercept() {
    return opensimModelJNI.LinearFunction_getIntercept(swigCPtr, this);
  }

  public SWIGTYPE_p_SimTK__Function createSimTKFunction() {
    long cPtr = opensimModelJNI.LinearFunction_createSimTKFunction(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_SimTK__Function(cPtr, false);
  }

}
