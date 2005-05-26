/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package simtksuN187Pkg;

import simtkModel.*;

public class rdStorage extends rdObject {
  private long swigCPtr;

  protected rdStorage(long cPtr, boolean cMemoryOwn) {
    super(suN187ModuleJNI.SWIGrdStorageTordObject(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected rdStorage() {
    this(0, false);
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      suN187ModuleJNI.delete_rdStorage(swigCPtr);
      swigCMemOwn = false;
      super.delete();
    }
    swigCPtr = 0;
  }

  protected static long getCPtr(rdStorage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static double getLARGE_NEGATIVE() {
    return suN187ModuleJNI.get_rdStorage_LARGE_NEGATIVE();
  }

  public static double getLARGE_POSITIVE() {
    return suN187ModuleJNI.get_rdStorage_LARGE_POSITIVE();
  }

  public static void setDEFAULT_HEADER_TOKEN(String value) {
    suN187ModuleJNI.set_rdStorage_DEFAULT_HEADER_TOKEN(value);
  }

  public static String getDEFAULT_HEADER_TOKEN() {
    return suN187ModuleJNI.get_rdStorage_DEFAULT_HEADER_TOKEN();
  }

  public static void setDEFAULT_HEADER_SEPARATOR(String value) {
    suN187ModuleJNI.set_rdStorage_DEFAULT_HEADER_SEPARATOR(value);
  }

  public static String getDEFAULT_HEADER_SEPARATOR() {
    return suN187ModuleJNI.get_rdStorage_DEFAULT_HEADER_SEPARATOR();
  }

  public rdStorage(int aCapacity, String aName) {
    this(suN187ModuleJNI.new_rdStorage__SWIG_0(aCapacity, aName), true);
  }

  public rdStorage(String aFileName) {
    this(suN187ModuleJNI.new_rdStorage__SWIG_1(aFileName), true);
  }

  public rdStorage(rdStorage aStorage, boolean aCopyData) {
    this(suN187ModuleJNI.new_rdStorage__SWIG_2(rdStorage.getCPtr(aStorage), aCopyData), true);
  }

  public rdStorage(rdStorage aStorage, int aStateIndex, int aN, String aDelimiter) {
    this(suN187ModuleJNI.new_rdStorage__SWIG_3(rdStorage.getCPtr(aStorage), aStateIndex, aN, aDelimiter), true);
  }

  public rdObject copy() {
    long cPtr = suN187ModuleJNI.rdStorage_copy(swigCPtr);
    return (cPtr == 0) ? null : new rdObject(cPtr, false);
  }

  public int getSize() {
    return suN187ModuleJNI.rdStorage_getSize(swigCPtr);
  }

  public int getSmallestNumberOfStates() {
    return suN187ModuleJNI.rdStorage_getSmallestNumberOfStates(swigCPtr);
  }

  public rdStateVector getStateVector(int aTimeIndex) {
    long cPtr = suN187ModuleJNI.rdStorage_getStateVector(swigCPtr, aTimeIndex);
    return (cPtr == 0) ? null : new rdStateVector(cPtr, false);
  }

  public rdStateVector getLastStateVector() {
    long cPtr = suN187ModuleJNI.rdStorage_getLastStateVector(swigCPtr);
    return (cPtr == 0) ? null : new rdStateVector(cPtr, false);
  }

  public double getFirstTime() {
    return suN187ModuleJNI.rdStorage_getFirstTime(swigCPtr);
  }

  public double getLastTime() {
    return suN187ModuleJNI.rdStorage_getLastTime(swigCPtr);
  }

  public int getTime(int aTimeIndex, SWIGTYPE_p_double rTime, int aStateIndex) {
    return suN187ModuleJNI.rdStorage_getTime(swigCPtr, aTimeIndex, SWIGTYPE_p_double.getCPtr(rTime), aStateIndex);
  }

  public int getTimeColumn(SWIGTYPE_p_p_double rTimes, int aStateIndex) {
    return suN187ModuleJNI.rdStorage_getTimeColumn(swigCPtr, SWIGTYPE_p_p_double.getCPtr(rTimes), aStateIndex);
  }

  public int getData(int aTimeIndex, int aStateIndex, SWIGTYPE_p_double rValue) {
    return suN187ModuleJNI.rdStorage_getData__SWIG_0(swigCPtr, aTimeIndex, aStateIndex, SWIGTYPE_p_double.getCPtr(rValue));
  }

  public int getData(int aTimeIndex, int aStateIndex, int aN, SWIGTYPE_p_double rData) {
    return suN187ModuleJNI.rdStorage_getData__SWIG_1(swigCPtr, aTimeIndex, aStateIndex, aN, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getData(int aTimeIndex, int aN, SWIGTYPE_p_p_double rData) {
    return suN187ModuleJNI.rdStorage_getData__SWIG_2(swigCPtr, aTimeIndex, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }


  public int getDataAtTime(double aTime, int aN, SWIGTYPE_p_p_double rData) {
    return suN187ModuleJNI.rdStorage_getDataAtTime__SWIG_0(swigCPtr, aTime, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getDataAtTime(double aTime, int aN, SWIGTYPE_p_double rData) {
    return suN187ModuleJNI.rdStorage_getDataAtTime__SWIG_1(swigCPtr, aTime, aN, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getDataColumn(int aStateIndex, SWIGTYPE_p_p_double rData) {
    return suN187ModuleJNI.rdStorage_getDataColumn__SWIG_0(swigCPtr, aStateIndex, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getDataColumn(SWIGTYPE_p_std__string columnName, SWIGTYPE_p_p_double rData) {
    return suN187ModuleJNI.rdStorage_getDataColumn__SWIG_1(swigCPtr, SWIGTYPE_p_std__string.getCPtr(columnName), SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public void setStepInterval(int aStepInterval) {
    suN187ModuleJNI.rdStorage_setStepInterval(swigCPtr, aStepInterval);
  }

  public int getStepInterval() {
    return suN187ModuleJNI.rdStorage_getStepInterval(swigCPtr);
  }

  public void setCapacityIncrement(int aIncrement) {
    suN187ModuleJNI.rdStorage_setCapacityIncrement(swigCPtr, aIncrement);
  }

  public int getCapacityIncrement() {
    return suN187ModuleJNI.rdStorage_getCapacityIncrement(swigCPtr);
  }

  public void setWriteSIMMHeader(boolean aTrueFalse) {
    suN187ModuleJNI.rdStorage_setWriteSIMMHeader(swigCPtr, aTrueFalse);
  }

  public boolean getWriteSIMMHeader() {
    return suN187ModuleJNI.rdStorage_getWriteSIMMHeader(swigCPtr);
  }

  public void setHeaderToken(String aToken) {
    suN187ModuleJNI.rdStorage_setHeaderToken(swigCPtr, aToken);
  }

  public String getHeaderToken() {
    return suN187ModuleJNI.rdStorage_getHeaderToken(swigCPtr);
  }

  public int getColumnIndex(SWIGTYPE_p_std__string aColumnName) {
    return suN187ModuleJNI.rdStorage_getColumnIndex(swigCPtr, SWIGTYPE_p_std__string.getCPtr(aColumnName));
  }

  public void setColumnLabels(String aLabels) {
    suN187ModuleJNI.rdStorage_setColumnLabels(swigCPtr, aLabels);
  }

  public String getColumnLabels() {
    return suN187ModuleJNI.rdStorage_getColumnLabels(swigCPtr);
  }

  public rdArrayStr getColumnLabelsArray() {
    return new rdArrayStr(suN187ModuleJNI.rdStorage_getColumnLabelsArray(swigCPtr), false);
  }

  public int reset(int aIndex) {
    return suN187ModuleJNI.rdStorage_reset__SWIG_0(swigCPtr, aIndex);
  }

  public int reset(double aTime) {
    return suN187ModuleJNI.rdStorage_reset__SWIG_1(swigCPtr, aTime);
  }

  public int append(rdStateVector aVec) {
    return suN187ModuleJNI.rdStorage_append__SWIG_0(swigCPtr, rdStateVector.getCPtr(aVec));
  }

  public int append(SWIGTYPE_p_rdArrayTrdStateVector_t aArray) {
    return suN187ModuleJNI.rdStorage_append__SWIG_1(swigCPtr, SWIGTYPE_p_rdArrayTrdStateVector_t.getCPtr(aArray));
  }

  public int append(double aT, int aN, SWIGTYPE_p_double aY) {
    return suN187ModuleJNI.rdStorage_append__SWIG_2(swigCPtr, aT, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public int store(int aStep, double aT, int aN, SWIGTYPE_p_double aY) {
    return suN187ModuleJNI.rdStorage_store(swigCPtr, aStep, aT, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void shiftTime(double aValue) {
    suN187ModuleJNI.rdStorage_shiftTime(swigCPtr, aValue);
  }

  public void scaleTime(double aValue) {
    suN187ModuleJNI.rdStorage_scaleTime(swigCPtr, aValue);
  }

  public void add(double aValue) {
    suN187ModuleJNI.rdStorage_add__SWIG_0(swigCPtr, aValue);
  }

  public void add(int aN, SWIGTYPE_p_double aY) {
    suN187ModuleJNI.rdStorage_add__SWIG_1(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void add(int aN, double aValue) {
    suN187ModuleJNI.rdStorage_add__SWIG_2(swigCPtr, aN, aValue);
  }

  public void add(rdStateVector aStateVector) {
    suN187ModuleJNI.rdStorage_add__SWIG_3(swigCPtr, rdStateVector.getCPtr(aStateVector));
  }

  public void add(rdStorage aStorage) {
    suN187ModuleJNI.rdStorage_add__SWIG_4(swigCPtr, rdStorage.getCPtr(aStorage));
  }

  public void subtract(double aValue) {
    suN187ModuleJNI.rdStorage_subtract__SWIG_0(swigCPtr, aValue);
  }

  public void subtract(int aN, SWIGTYPE_p_double aY) {
    suN187ModuleJNI.rdStorage_subtract__SWIG_1(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void subtract(rdStateVector aStateVector) {
    suN187ModuleJNI.rdStorage_subtract__SWIG_2(swigCPtr, rdStateVector.getCPtr(aStateVector));
  }

  public void subtract(rdStorage aStorage) {
    suN187ModuleJNI.rdStorage_subtract__SWIG_3(swigCPtr, rdStorage.getCPtr(aStorage));
  }

  public void multiply(double aValue) {
    suN187ModuleJNI.rdStorage_multiply__SWIG_0(swigCPtr, aValue);
  }

  public void multiplyColumn(int aIndex, double aValue) {
    suN187ModuleJNI.rdStorage_multiplyColumn(swigCPtr, aIndex, aValue);
  }

  public void multiply(int aN, SWIGTYPE_p_double aY) {
    suN187ModuleJNI.rdStorage_multiply__SWIG_1(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void multiply(rdStateVector aStateVector) {
    suN187ModuleJNI.rdStorage_multiply__SWIG_2(swigCPtr, rdStateVector.getCPtr(aStateVector));
  }

  public void multiply(rdStorage aStorage) {
    suN187ModuleJNI.rdStorage_multiply__SWIG_3(swigCPtr, rdStorage.getCPtr(aStorage));
  }

  public void divide(double aValue) {
    suN187ModuleJNI.rdStorage_divide__SWIG_0(swigCPtr, aValue);
  }

  public void divide(int aN, SWIGTYPE_p_double aY) {
    suN187ModuleJNI.rdStorage_divide__SWIG_1(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void divide(rdStateVector aStateVector) {
    suN187ModuleJNI.rdStorage_divide__SWIG_2(swigCPtr, rdStateVector.getCPtr(aStateVector));
  }

  public void divide(rdStorage aStorage) {
    suN187ModuleJNI.rdStorage_divide__SWIG_3(swigCPtr, rdStorage.getCPtr(aStorage));
  }

  public rdStorage integrate(int aI1, int aI2) {
    long cPtr = suN187ModuleJNI.rdStorage_integrate__SWIG_0(swigCPtr, aI1, aI2);
    return (cPtr == 0) ? null : new rdStorage(cPtr, false);
  }

  public rdStorage integrate(double aT1, double aT2) {
    long cPtr = suN187ModuleJNI.rdStorage_integrate__SWIG_1(swigCPtr, aT1, aT2);
    return (cPtr == 0) ? null : new rdStorage(cPtr, false);
  }

  public int computeArea(int aN, SWIGTYPE_p_double aArea) {
    return suN187ModuleJNI.rdStorage_computeArea__SWIG_0(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aArea));
  }

  public int computeArea(double aTI, double aTF, int aN, SWIGTYPE_p_double aArea) {
    return suN187ModuleJNI.rdStorage_computeArea__SWIG_1(swigCPtr, aTI, aTF, aN, SWIGTYPE_p_double.getCPtr(aArea));
  }

  public int computeAverage(int aN, SWIGTYPE_p_double aAve) {
    return suN187ModuleJNI.rdStorage_computeAverage__SWIG_0(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aAve));
  }

  public int computeAverage(double aTI, double aTF, int aN, SWIGTYPE_p_double aAve) {
    return suN187ModuleJNI.rdStorage_computeAverage__SWIG_1(swigCPtr, aTI, aTF, aN, SWIGTYPE_p_double.getCPtr(aAve));
  }

  public int findIndex(double aT) {
    return suN187ModuleJNI.rdStorage_findIndex__SWIG_0(swigCPtr, aT);
  }

  public int findIndex(int aI, double aT) {
    return suN187ModuleJNI.rdStorage_findIndex__SWIG_1(swigCPtr, aI, aT);
  }

  public void reSample(double aRate, int aDegree) {
    suN187ModuleJNI.rdStorage_reSample(swigCPtr, aRate, aDegree);
  }

  public void print() {
    suN187ModuleJNI.rdStorage_print__SWIG_0(swigCPtr);
  }

  public int print(String aFileName, String aMode) {
    return suN187ModuleJNI.rdStorage_print__SWIG_1(swigCPtr, aFileName, aMode);
  }

  public int print(String aFileName, double aDT, String aMode) {
    return suN187ModuleJNI.rdStorage_print__SWIG_2(swigCPtr, aFileName, aDT, aMode);
  }

}
