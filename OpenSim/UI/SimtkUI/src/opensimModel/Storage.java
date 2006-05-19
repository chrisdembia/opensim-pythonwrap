/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package opensimModel;

public class Storage extends OpenSimObject {
  private long swigCPtr;

  protected Storage(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Storage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Storage(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static double getLARGE_NEGATIVE() {
    return opensimModelJNI.Storage_LARGE_NEGATIVE_get();
  }

  public static double getLARGE_POSITIVE() {
    return opensimModelJNI.Storage_LARGE_POSITIVE_get();
  }

  public static void setDEFAULT_HEADER_TOKEN(String value) {
    opensimModelJNI.Storage_DEFAULT_HEADER_TOKEN_set(value);
  }

  public static String getDEFAULT_HEADER_TOKEN() {
    return opensimModelJNI.Storage_DEFAULT_HEADER_TOKEN_get();
  }

  public static void setDEFAULT_HEADER_SEPARATOR(String value) {
    opensimModelJNI.Storage_DEFAULT_HEADER_SEPARATOR_set(value);
  }

  public static String getDEFAULT_HEADER_SEPARATOR() {
    return opensimModelJNI.Storage_DEFAULT_HEADER_SEPARATOR_get();
  }

  public Storage(int aCapacity, String aName) {
    this(opensimModelJNI.new_Storage__SWIG_0(aCapacity, aName), true);
  }

  public Storage(int aCapacity) {
    this(opensimModelJNI.new_Storage__SWIG_1(aCapacity), true);
  }

  public Storage() {
    this(opensimModelJNI.new_Storage__SWIG_2(), true);
  }

  public Storage(String aFileName) {
    this(opensimModelJNI.new_Storage__SWIG_3(aFileName), true);
  }

  public Storage(Storage aStorage, boolean aCopyData) {
    this(opensimModelJNI.new_Storage__SWIG_4(Storage.getCPtr(aStorage), aCopyData), true);
  }

  public Storage(Storage aStorage) {
    this(opensimModelJNI.new_Storage__SWIG_5(Storage.getCPtr(aStorage)), true);
  }

  public Storage(Storage aStorage, int aStateIndex, int aN, String aDelimiter) {
    this(opensimModelJNI.new_Storage__SWIG_6(Storage.getCPtr(aStorage), aStateIndex, aN, aDelimiter), true);
  }

  public Storage(Storage aStorage, int aStateIndex, int aN) {
    this(opensimModelJNI.new_Storage__SWIG_7(Storage.getCPtr(aStorage), aStateIndex, aN), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Storage_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public int getSize() {
    return opensimModelJNI.Storage_getSize(swigCPtr);
  }

  public int getSmallestNumberOfStates() {
    return opensimModelJNI.Storage_getSmallestNumberOfStates(swigCPtr);
  }

  public StateVector getStateVector(int aTimeIndex) {
    long cPtr = opensimModelJNI.Storage_getStateVector(swigCPtr, aTimeIndex);
    return (cPtr == 0) ? null : new StateVector(cPtr, false);
  }

  public StateVector getLastStateVector() {
    long cPtr = opensimModelJNI.Storage_getLastStateVector(swigCPtr);
    return (cPtr == 0) ? null : new StateVector(cPtr, false);
  }

  public double getFirstTime() {
    return opensimModelJNI.Storage_getFirstTime(swigCPtr);
  }

  public double getLastTime() {
    return opensimModelJNI.Storage_getLastTime(swigCPtr);
  }

  public int getTime(int aTimeIndex, SWIGTYPE_p_double rTime, int aStateIndex) {
    return opensimModelJNI.Storage_getTime__SWIG_0(swigCPtr, aTimeIndex, SWIGTYPE_p_double.getCPtr(rTime), aStateIndex);
  }

  public int getTime(int aTimeIndex, SWIGTYPE_p_double rTime) {
    return opensimModelJNI.Storage_getTime__SWIG_1(swigCPtr, aTimeIndex, SWIGTYPE_p_double.getCPtr(rTime));
  }

  public int getTimeColumn(SWIGTYPE_p_double rTimes, int aStateIndex) {
    return opensimModelJNI.Storage_getTimeColumn__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(rTimes), aStateIndex);
  }

  public int getTimeColumn(SWIGTYPE_p_double rTimes) {
    return opensimModelJNI.Storage_getTimeColumn__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(rTimes));
  }

  public int getData(int aTimeIndex, int aStateIndex, SWIGTYPE_p_double rValue) {
    return opensimModelJNI.Storage_getData__SWIG_0(swigCPtr, aTimeIndex, aStateIndex, SWIGTYPE_p_double.getCPtr(rValue));
  }

  public int getData(int aTimeIndex, int aStateIndex, int aN, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getData__SWIG_1(swigCPtr, aTimeIndex, aStateIndex, aN, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getData(int aTimeIndex, int aN, SWIGTYPE_p_p_double rData) {
    return opensimModelJNI.Storage_getData__SWIG_2(swigCPtr, aTimeIndex, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getDataAtTime(double aTime, int aN, SWIGTYPE_p_p_double rData) {
    return opensimModelJNI.Storage_getDataAtTime__SWIG_0(swigCPtr, aTime, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getDataAtTime(double aTime, int aN, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getDataAtTime__SWIG_1(swigCPtr, aTime, aN, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getDataColumn(int aStateIndex, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getDataColumn__SWIG_0(swigCPtr, aStateIndex, SWIGTYPE_p_double.getCPtr(rData));
  }

  public void setDataColumn(int aStateIndex, ArrayDouble aData) {
    opensimModelJNI.Storage_setDataColumn(swigCPtr, aStateIndex, ArrayDouble.getCPtr(aData));
  }

  public int getDataColumn(SWIGTYPE_p_std__string columnName, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getDataColumn__SWIG_1(swigCPtr, SWIGTYPE_p_std__string.getCPtr(columnName), SWIGTYPE_p_double.getCPtr(rData));
  }

  public void setStepInterval(int aStepInterval) {
    opensimModelJNI.Storage_setStepInterval(swigCPtr, aStepInterval);
  }

  public int getStepInterval() {
    return opensimModelJNI.Storage_getStepInterval(swigCPtr);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.Storage_setCapacityIncrement(swigCPtr, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.Storage_getCapacityIncrement(swigCPtr);
  }

  public void setWriteSIMMHeader(boolean aTrueFalse) {
    opensimModelJNI.Storage_setWriteSIMMHeader(swigCPtr, aTrueFalse);
  }

  public boolean getWriteSIMMHeader() {
    return opensimModelJNI.Storage_getWriteSIMMHeader(swigCPtr);
  }

  public void setHeaderToken(String aToken) {
    opensimModelJNI.Storage_setHeaderToken(swigCPtr, aToken);
  }

  public String getHeaderToken() {
    return opensimModelJNI.Storage_getHeaderToken(swigCPtr);
  }

  public int getColumnIndex(String aColumnName) {
    return opensimModelJNI.Storage_getColumnIndex(swigCPtr, aColumnName);
  }

  public void setColumnLabels(String aLabels) {
    opensimModelJNI.Storage_setColumnLabels__SWIG_0(swigCPtr, aLabels);
  }

  public void setColumnLabels() {
    opensimModelJNI.Storage_setColumnLabels__SWIG_1(swigCPtr);
  }

  public String getColumnLabels() {
    return opensimModelJNI.Storage_getColumnLabels(swigCPtr);
  }

  public ArrayStr getColumnLabelsArray() {
    return new ArrayStr(opensimModelJNI.Storage_getColumnLabelsArray(swigCPtr), false);
  }

  public int reset(int aIndex) {
    return opensimModelJNI.Storage_reset__SWIG_0(swigCPtr, aIndex);
  }

  public int reset() {
    return opensimModelJNI.Storage_reset__SWIG_1(swigCPtr);
  }

  public int reset(double aTime) {
    return opensimModelJNI.Storage_reset__SWIG_2(swigCPtr, aTime);
  }

  public int append(StateVector aVec) {
    return opensimModelJNI.Storage_append__SWIG_0(swigCPtr, StateVector.getCPtr(aVec));
  }

  public int append(SWIGTYPE_p_OpenSim__ArrayTOpenSim__StateVector_t aArray) {
    return opensimModelJNI.Storage_append__SWIG_1(swigCPtr, SWIGTYPE_p_OpenSim__ArrayTOpenSim__StateVector_t.getCPtr(aArray));
  }

  public int append(double aT, int aN, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Storage_append__SWIG_2(swigCPtr, aT, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public int store(int aStep, double aT, int aN, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Storage_store(swigCPtr, aStep, aT, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void shiftTime(double aValue) {
    opensimModelJNI.Storage_shiftTime(swigCPtr, aValue);
  }

  public void scaleTime(double aValue) {
    opensimModelJNI.Storage_scaleTime(swigCPtr, aValue);
  }

  public void add(double aValue) {
    opensimModelJNI.Storage_add__SWIG_0(swigCPtr, aValue);
  }

  public void add(int aN, double[] aY) {
    opensimModelJNI.Storage_add__SWIG_1(swigCPtr, aN, aY);
  }

  public void add(int aN, double aValue) {
    opensimModelJNI.Storage_add__SWIG_2(swigCPtr, aN, aValue);
  }

  public void add(StateVector aStateVector) {
    opensimModelJNI.Storage_add__SWIG_3(swigCPtr, StateVector.getCPtr(aStateVector));
  }

  public void add(Storage aStorage) {
    opensimModelJNI.Storage_add__SWIG_4(swigCPtr, Storage.getCPtr(aStorage));
  }

  public void subtract(double aValue) {
    opensimModelJNI.Storage_subtract__SWIG_0(swigCPtr, aValue);
  }

  public void subtract(int aN, double[] aY) {
    opensimModelJNI.Storage_subtract__SWIG_1(swigCPtr, aN, aY);
  }

  public void subtract(StateVector aStateVector) {
    opensimModelJNI.Storage_subtract__SWIG_2(swigCPtr, StateVector.getCPtr(aStateVector));
  }

  public void subtract(Storage aStorage) {
    opensimModelJNI.Storage_subtract__SWIG_3(swigCPtr, Storage.getCPtr(aStorage));
  }

  public void multiply(double aValue) {
    opensimModelJNI.Storage_multiply__SWIG_0(swigCPtr, aValue);
  }

  public void multiplyColumn(int aIndex, double aValue) {
    opensimModelJNI.Storage_multiplyColumn(swigCPtr, aIndex, aValue);
  }

  public void multiply(int aN, double[] aY) {
    opensimModelJNI.Storage_multiply__SWIG_1(swigCPtr, aN, aY);
  }

  public void multiply(StateVector aStateVector) {
    opensimModelJNI.Storage_multiply__SWIG_2(swigCPtr, StateVector.getCPtr(aStateVector));
  }

  public void multiply(Storage aStorage) {
    opensimModelJNI.Storage_multiply__SWIG_3(swigCPtr, Storage.getCPtr(aStorage));
  }

  public void divide(double aValue) {
    opensimModelJNI.Storage_divide__SWIG_0(swigCPtr, aValue);
  }

  public void divide(int aN, double[] aY) {
    opensimModelJNI.Storage_divide__SWIG_1(swigCPtr, aN, aY);
  }

  public void divide(StateVector aStateVector) {
    opensimModelJNI.Storage_divide__SWIG_2(swigCPtr, StateVector.getCPtr(aStateVector));
  }

  public void divide(Storage aStorage) {
    opensimModelJNI.Storage_divide__SWIG_3(swigCPtr, Storage.getCPtr(aStorage));
  }

  public Storage integrate(int aI1, int aI2) {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_0(swigCPtr, aI1, aI2);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage integrate(int aI1) {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_1(swigCPtr, aI1);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage integrate() {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_2(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage integrate(double aT1, double aT2) {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_3(swigCPtr, aT1, aT2);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public int computeArea(int aN, SWIGTYPE_p_double aArea) {
    return opensimModelJNI.Storage_computeArea__SWIG_0(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aArea));
  }

  public int computeArea(double aTI, double aTF, int aN, SWIGTYPE_p_double aArea) {
    return opensimModelJNI.Storage_computeArea__SWIG_1(swigCPtr, aTI, aTF, aN, SWIGTYPE_p_double.getCPtr(aArea));
  }

  public int computeAverage(int aN, SWIGTYPE_p_double aAve) {
    return opensimModelJNI.Storage_computeAverage__SWIG_0(swigCPtr, aN, SWIGTYPE_p_double.getCPtr(aAve));
  }

  public int computeAverage(double aTI, double aTF, int aN, SWIGTYPE_p_double aAve) {
    return opensimModelJNI.Storage_computeAverage__SWIG_1(swigCPtr, aTI, aTF, aN, SWIGTYPE_p_double.getCPtr(aAve));
  }

  public void pad(int aPadSize) {
    opensimModelJNI.Storage_pad(swigCPtr, aPadSize);
  }

  public void lowpassFIR(int aOrder, double aCutoffFequency) {
    opensimModelJNI.Storage_lowpassFIR(swigCPtr, aOrder, aCutoffFequency);
  }

  public int findIndex(double aT) {
    return opensimModelJNI.Storage_findIndex__SWIG_0(swigCPtr, aT);
  }

  public int findIndex(int aI, double aT) {
    return opensimModelJNI.Storage_findIndex__SWIG_1(swigCPtr, aI, aT);
  }

  public void resample(double aDT, int aDegree) {
    opensimModelJNI.Storage_resample(swigCPtr, aDT, aDegree);
  }

  public void print() {
    opensimModelJNI.Storage_print__SWIG_0(swigCPtr);
  }

  public boolean print(String aFileName, String aMode) {
    return opensimModelJNI.Storage_print__SWIG_1(swigCPtr, aFileName, aMode);
  }

  public boolean print(String aFileName) {
    return opensimModelJNI.Storage_print__SWIG_2(swigCPtr, aFileName);
  }

  public int print(String aFileName, double aDT, String aMode) {
    return opensimModelJNI.Storage_print__SWIG_3(swigCPtr, aFileName, aDT, aMode);
  }

  public int print(String aFileName, double aDT) {
    return opensimModelJNI.Storage_print__SWIG_4(swigCPtr, aFileName, aDT);
  }

}
