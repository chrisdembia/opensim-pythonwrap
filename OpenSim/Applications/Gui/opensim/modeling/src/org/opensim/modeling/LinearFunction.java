/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class LinearFunction extends Function {
  private long swigCPtr;

  public LinearFunction(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(LinearFunction obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_LinearFunction(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public LinearFunction() {
    this(opensimModelJNI.new_LinearFunction__SWIG_0(), true);
  }

  public LinearFunction(int aN, SWIGTYPE_p_double aTimes, SWIGTYPE_p_double aValues, String aName) {
    this(opensimModelJNI.new_LinearFunction__SWIG_1(aN, SWIGTYPE_p_double.getCPtr(aTimes), SWIGTYPE_p_double.getCPtr(aValues), aName), true);
  }

  public LinearFunction(int aN, SWIGTYPE_p_double aTimes, SWIGTYPE_p_double aValues) {
    this(opensimModelJNI.new_LinearFunction__SWIG_2(aN, SWIGTYPE_p_double.getCPtr(aTimes), SWIGTYPE_p_double.getCPtr(aValues)), true);
  }

  public LinearFunction(LinearFunction aFunction) {
    this(opensimModelJNI.new_LinearFunction__SWIG_3(LinearFunction.getCPtr(aFunction), aFunction), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.LinearFunction_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void init(int aN, SWIGTYPE_p_double aXValues, SWIGTYPE_p_double aYValues) {
    opensimModelJNI.LinearFunction_init(swigCPtr, this, aN, SWIGTYPE_p_double.getCPtr(aXValues), SWIGTYPE_p_double.getCPtr(aYValues));
  }

  public int getSize() {
    return opensimModelJNI.LinearFunction_getSize(swigCPtr, this);
  }

  public double getMinX() {
    return opensimModelJNI.LinearFunction_getMinX(swigCPtr, this);
  }

  public double getMaxX() {
    return opensimModelJNI.LinearFunction_getMaxX(swigCPtr, this);
  }

  public ArrayDouble getX() {
    return new ArrayDouble(opensimModelJNI.LinearFunction_getX__SWIG_0(swigCPtr, this), false);
  }

  public ArrayDouble getY() {
    return new ArrayDouble(opensimModelJNI.LinearFunction_getY__SWIG_0(swigCPtr, this), false);
  }

  public SWIGTYPE_p_double getXValues() {
    long cPtr = opensimModelJNI.LinearFunction_getXValues(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_double(cPtr, false);
  }

  public SWIGTYPE_p_double getYValues() {
    long cPtr = opensimModelJNI.LinearFunction_getYValues(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_double(cPtr, false);
  }

  public int getNumberOfPoints() {
    return opensimModelJNI.LinearFunction_getNumberOfPoints(swigCPtr, this);
  }

  public double getX(int aIndex) {
    return opensimModelJNI.LinearFunction_getX__SWIG_1(swigCPtr, this, aIndex);
  }

  public double getY(int aIndex) {
    return opensimModelJNI.LinearFunction_getY__SWIG_1(swigCPtr, this, aIndex);
  }

  public double getZ(int aIndex) {
    return opensimModelJNI.LinearFunction_getZ(swigCPtr, this, aIndex);
  }

  public void setX(int aIndex, double aValue) {
    opensimModelJNI.LinearFunction_setX(swigCPtr, this, aIndex, aValue);
  }

  public void setY(int aIndex, double aValue) {
    opensimModelJNI.LinearFunction_setY(swigCPtr, this, aIndex, aValue);
  }

  public void scaleY(double aScaleFactor) {
    opensimModelJNI.LinearFunction_scaleY(swigCPtr, this, aScaleFactor);
  }

  public boolean deletePoint(int aIndex) {
    return opensimModelJNI.LinearFunction_deletePoint(swigCPtr, this, aIndex);
  }

  public void addPoint(double aX, double aY) {
    opensimModelJNI.LinearFunction_addPoint(swigCPtr, this, aX, aY);
  }

  public ArrayXYPoint renderAsLineSegments(double aStart, double aEnd) {
    long cPtr = opensimModelJNI.LinearFunction_renderAsLineSegments__SWIG_0(swigCPtr, this, aStart, aEnd);
    return (cPtr == 0) ? null : new ArrayXYPoint(cPtr, false);
  }

  public ArrayXYPoint renderAsLineSegments(int aIndex) {
    long cPtr = opensimModelJNI.LinearFunction_renderAsLineSegments__SWIG_1(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new ArrayXYPoint(cPtr, false);
  }

  public void updateBoundingBox() {
    opensimModelJNI.LinearFunction_updateBoundingBox(swigCPtr, this);
  }

  public double evaluate(int aDerivOrder, double aX, double aY, double aZ) {
    return opensimModelJNI.LinearFunction_evaluate__SWIG_0(swigCPtr, this, aDerivOrder, aX, aY, aZ);
  }

  public double evaluate(int aDerivOrder, double aX, double aY) {
    return opensimModelJNI.LinearFunction_evaluate__SWIG_1(swigCPtr, this, aDerivOrder, aX, aY);
  }

  public double evaluate(int aDerivOrder, double aX) {
    return opensimModelJNI.LinearFunction_evaluate__SWIG_2(swigCPtr, this, aDerivOrder, aX);
  }

  public double evaluate(int aDerivOrder) {
    return opensimModelJNI.LinearFunction_evaluate__SWIG_3(swigCPtr, this, aDerivOrder);
  }

  public double evaluateTotalFirstDerivative(double aX, double aDxdt) {
    return opensimModelJNI.LinearFunction_evaluateTotalFirstDerivative(swigCPtr, this, aX, aDxdt);
  }

  public double evaluateTotalSecondDerivative(double aX, double aDxdt, double aD2xdt2) {
    return opensimModelJNI.LinearFunction_evaluateTotalSecondDerivative(swigCPtr, this, aX, aDxdt, aD2xdt2);
  }

  public void updateFromXMLNode() {
    opensimModelJNI.LinearFunction_updateFromXMLNode(swigCPtr, this);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.LinearFunction_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.LinearFunction_isA(swigCPtr, this, type);
  }

  public static LinearFunction safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.LinearFunction_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new LinearFunction(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.LinearFunction_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
