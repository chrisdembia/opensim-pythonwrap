/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Function extends OpenSimObject {
  private long swigCPtr;

  public Function(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Function obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Function(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Function_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setMinX(double aMinX) {
    opensimModelJNI.Function_setMinX(swigCPtr, this, aMinX);
  }

  public double getMinX() {
    return opensimModelJNI.Function_getMinX(swigCPtr, this);
  }

  public void setMaxX(double aMaxX) {
    opensimModelJNI.Function_setMaxX(swigCPtr, this, aMaxX);
  }

  public double getMaxX() {
    return opensimModelJNI.Function_getMaxX(swigCPtr, this);
  }

  public void setMinY(double aMinY) {
    opensimModelJNI.Function_setMinY(swigCPtr, this, aMinY);
  }

  public double getMinY() {
    return opensimModelJNI.Function_getMinY(swigCPtr, this);
  }

  public void setMaxY(double aMaxY) {
    opensimModelJNI.Function_setMaxY(swigCPtr, this, aMaxY);
  }

  public double getMaxY() {
    return opensimModelJNI.Function_getMaxY(swigCPtr, this);
  }

  public void setMinZ(double aMinZ) {
    opensimModelJNI.Function_setMinZ(swigCPtr, this, aMinZ);
  }

  public double getMinZ() {
    return opensimModelJNI.Function_getMinZ(swigCPtr, this);
  }

  public void setMaxZ(double aMaxZ) {
    opensimModelJNI.Function_setMaxZ(swigCPtr, this, aMaxZ);
  }

  public double getMaxZ() {
    return opensimModelJNI.Function_getMaxZ(swigCPtr, this);
  }

  public void isLinear(double aTol, double aMinX, double aMaxX, SWIGTYPE_p_double rMX, double aMinY, double aMaxY, SWIGTYPE_p_double rMY, double aMinZ, double aMaxZ, SWIGTYPE_p_double rMZ) {
    opensimModelJNI.Function_isLinear(swigCPtr, this, aTol, aMinX, aMaxX, SWIGTYPE_p_double.getCPtr(rMX), aMinY, aMaxY, SWIGTYPE_p_double.getCPtr(rMY), aMinZ, aMaxZ, SWIGTYPE_p_double.getCPtr(rMZ));
  }

  public void updateBoundingBox() {
    opensimModelJNI.Function_updateBoundingBox(swigCPtr, this);
  }

  public int getNumberOfPoints() {
    return opensimModelJNI.Function_getNumberOfPoints(swigCPtr, this);
  }

  public double evaluate(int aDerivOrder, double aX, double aY, double aZ) {
    return opensimModelJNI.Function_evaluate__SWIG_0(swigCPtr, this, aDerivOrder, aX, aY, aZ);
  }

  public double evaluate(int aDerivOrder, double aX, double aY) {
    return opensimModelJNI.Function_evaluate__SWIG_1(swigCPtr, this, aDerivOrder, aX, aY);
  }

  public double evaluate(int aDerivOrder, double aX) {
    return opensimModelJNI.Function_evaluate__SWIG_2(swigCPtr, this, aDerivOrder, aX);
  }

  public double evaluate(int aDerivOrder) {
    return opensimModelJNI.Function_evaluate__SWIG_3(swigCPtr, this, aDerivOrder);
  }

  public double evaluateTotalFirstDerivative(double aX, double aDxdt) {
    return opensimModelJNI.Function_evaluateTotalFirstDerivative(swigCPtr, this, aX, aDxdt);
  }

  public double evaluateTotalSecondDerivative(double aX, double aDxdt, double aD2xdt2) {
    return opensimModelJNI.Function_evaluateTotalSecondDerivative(swigCPtr, this, aX, aDxdt, aD2xdt2);
  }

  public void scaleY(double aScaleFactor) {
    opensimModelJNI.Function_scaleY(swigCPtr, this, aScaleFactor);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.Function_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.Function_isA(swigCPtr, this, type);
  }

  public static Function safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.Function_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.Function_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
