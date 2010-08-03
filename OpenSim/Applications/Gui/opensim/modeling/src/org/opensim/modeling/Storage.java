/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Storage extends StorageInterface {
  private long swigCPtr;

  public Storage(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Storage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Storage(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
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

  public static int getMAX_RESAMPLE_SIZE() {
    return opensimModelJNI.Storage_MAX_RESAMPLE_SIZE_get();
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

  public Storage(String aFileName) throws java.io.IOException {
    this(opensimModelJNI.new_Storage__SWIG_3(aFileName), true);
  }

  public Storage(Storage aStorage, boolean aCopyData) {
    this(opensimModelJNI.new_Storage__SWIG_4(Storage.getCPtr(aStorage), aStorage, aCopyData), true);
  }

  public Storage(Storage aStorage) {
    this(opensimModelJNI.new_Storage__SWIG_5(Storage.getCPtr(aStorage), aStorage), true);
  }

  public Storage(Storage aStorage, int aStateIndex, int aN, String aDelimiter) {
    this(opensimModelJNI.new_Storage__SWIG_6(Storage.getCPtr(aStorage), aStorage, aStateIndex, aN, aDelimiter), true);
  }

  public Storage(Storage aStorage, int aStateIndex, int aN) {
    this(opensimModelJNI.new_Storage__SWIG_7(Storage.getCPtr(aStorage), aStorage, aStateIndex, aN), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Storage_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public String getName() {
    return opensimModelJNI.Storage_getName(swigCPtr, this);
  }

  public String getDescription() {
    return opensimModelJNI.Storage_getDescription(swigCPtr, this);
  }

  public void setName(String aName) {
    opensimModelJNI.Storage_setName(swigCPtr, this, aName);
  }

  public void setDescription(String aDescription) {
    opensimModelJNI.Storage_setDescription(swigCPtr, this, aDescription);
  }

  public int getSize() {
    return opensimModelJNI.Storage_getSize(swigCPtr, this);
  }

  public int getSmallestNumberOfStates() {
    return opensimModelJNI.Storage_getSmallestNumberOfStates(swigCPtr, this);
  }

  public StateVector getStateVector(int aTimeIndex) {
    long cPtr = opensimModelJNI.Storage_getStateVector(swigCPtr, this, aTimeIndex);
    return (cPtr == 0) ? null : new StateVector(cPtr, false);
  }

  public StateVector getLastStateVector() {
    long cPtr = opensimModelJNI.Storage_getLastStateVector(swigCPtr, this);
    return (cPtr == 0) ? null : new StateVector(cPtr, false);
  }

  public double getFirstTime() {
    return opensimModelJNI.Storage_getFirstTime(swigCPtr, this);
  }

  public double getLastTime() {
    return opensimModelJNI.Storage_getLastTime(swigCPtr, this);
  }

  public double getMinTimeStep() {
    return opensimModelJNI.Storage_getMinTimeStep(swigCPtr, this);
  }

  public boolean getTime(int aTimeIndex, SWIGTYPE_p_double rTime, int aStateIndex) {
    return opensimModelJNI.Storage_getTime__SWIG_0(swigCPtr, this, aTimeIndex, SWIGTYPE_p_double.getCPtr(rTime), aStateIndex);
  }

  public boolean getTime(int aTimeIndex, SWIGTYPE_p_double rTime) {
    return opensimModelJNI.Storage_getTime__SWIG_1(swigCPtr, this, aTimeIndex, SWIGTYPE_p_double.getCPtr(rTime));
  }

  public int getTimeColumn(SWIGTYPE_p_double rTimes, int aStateIndex) {
    return opensimModelJNI.Storage_getTimeColumn__SWIG_0(swigCPtr, this, SWIGTYPE_p_double.getCPtr(rTimes), aStateIndex);
  }

  public int getTimeColumn(SWIGTYPE_p_double rTimes) {
    return opensimModelJNI.Storage_getTimeColumn__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(rTimes));
  }

  public int getTimeColumn(ArrayDouble rTimes, int aStateIndex) {
    return opensimModelJNI.Storage_getTimeColumn__SWIG_2(swigCPtr, this, ArrayDouble.getCPtr(rTimes), rTimes, aStateIndex);
  }

  public int getTimeColumn(ArrayDouble rTimes) {
    return opensimModelJNI.Storage_getTimeColumn__SWIG_3(swigCPtr, this, ArrayDouble.getCPtr(rTimes), rTimes);
  }

  public void getTimeColumnWithStartTime(ArrayDouble rTimes, double startTime) {
    opensimModelJNI.Storage_getTimeColumnWithStartTime__SWIG_0(swigCPtr, this, ArrayDouble.getCPtr(rTimes), rTimes, startTime);
  }

  public void getTimeColumnWithStartTime(ArrayDouble rTimes) {
    opensimModelJNI.Storage_getTimeColumnWithStartTime__SWIG_1(swigCPtr, this, ArrayDouble.getCPtr(rTimes), rTimes);
  }

  public void addKeyValuePair(String aKey, String aValue) {
    opensimModelJNI.Storage_addKeyValuePair(swigCPtr, this, aKey, aValue);
  }

  public void getValueForKey(String aKey, SWIGTYPE_p_std__string rValue) {
    opensimModelJNI.Storage_getValueForKey(swigCPtr, this, aKey, SWIGTYPE_p_std__string.getCPtr(rValue));
  }

  public boolean hasKey(String aKey) {
    return opensimModelJNI.Storage_hasKey(swigCPtr, this, aKey);
  }

  public int getData(int aTimeIndex, int aStateIndex, SWIGTYPE_p_double rValue) {
    return opensimModelJNI.Storage_getData__SWIG_0(swigCPtr, this, aTimeIndex, aStateIndex, SWIGTYPE_p_double.getCPtr(rValue));
  }

  public int getData(int aTimeIndex, int aStateIndex, int aN, SWIGTYPE_p_p_double rData) {
    return opensimModelJNI.Storage_getData__SWIG_1(swigCPtr, this, aTimeIndex, aStateIndex, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getData(int aTimeIndex, int aStateIndex, int aN, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getData__SWIG_2(swigCPtr, this, aTimeIndex, aStateIndex, aN, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getData(int aTimeIndex, int aN, SWIGTYPE_p_p_double rData) {
    return opensimModelJNI.Storage_getData__SWIG_3(swigCPtr, this, aTimeIndex, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getDataAtTime(double aTime, int aN, SWIGTYPE_p_p_double rData) {
    return opensimModelJNI.Storage_getDataAtTime__SWIG_0(swigCPtr, this, aTime, aN, SWIGTYPE_p_p_double.getCPtr(rData));
  }

  public int getDataAtTime(double aTime, int aN, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getDataAtTime__SWIG_1(swigCPtr, this, aTime, aN, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getDataAtTime(double aTime, int aN, ArrayDouble rData) {
    return opensimModelJNI.Storage_getDataAtTime__SWIG_2(swigCPtr, this, aTime, aN, ArrayDouble.getCPtr(rData), rData);
  }

  public int getDataColumn(int aStateIndex, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getDataColumn__SWIG_0(swigCPtr, this, aStateIndex, SWIGTYPE_p_double.getCPtr(rData));
  }

  public int getDataColumn(int aStateIndex, ArrayDouble rData) {
    return opensimModelJNI.Storage_getDataColumn__SWIG_1(swigCPtr, this, aStateIndex, ArrayDouble.getCPtr(rData), rData);
  }

  public void setDataColumn(int aStateIndex, ArrayDouble aData) {
    opensimModelJNI.Storage_setDataColumn(swigCPtr, this, aStateIndex, ArrayDouble.getCPtr(aData), aData);
  }

  public int getDataColumn(String columnName, SWIGTYPE_p_double rData) {
    return opensimModelJNI.Storage_getDataColumn__SWIG_2(swigCPtr, this, columnName, SWIGTYPE_p_double.getCPtr(rData));
  }

  public void getDataColumn(String columnName, ArrayDouble data, double startTime) {
    opensimModelJNI.Storage_getDataColumn__SWIG_3(swigCPtr, this, columnName, ArrayDouble.getCPtr(data), data, startTime);
  }

  public void getDataColumn(String columnName, ArrayDouble data) {
    opensimModelJNI.Storage_getDataColumn__SWIG_4(swigCPtr, this, columnName, ArrayDouble.getCPtr(data), data);
  }

  public void setStepInterval(int aStepInterval) {
    opensimModelJNI.Storage_setStepInterval(swigCPtr, this, aStepInterval);
  }

  public int getStepInterval() {
    return opensimModelJNI.Storage_getStepInterval(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.Storage_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.Storage_getCapacityIncrement(swigCPtr, this);
  }

  public void setWriteSIMMHeader(boolean aTrueFalse) {
    opensimModelJNI.Storage_setWriteSIMMHeader(swigCPtr, this, aTrueFalse);
  }

  public boolean getWriteSIMMHeader() {
    return opensimModelJNI.Storage_getWriteSIMMHeader(swigCPtr, this);
  }

  public void setHeaderToken(String aToken) {
    opensimModelJNI.Storage_setHeaderToken(swigCPtr, this, aToken);
  }

  public String getHeaderToken() {
    return opensimModelJNI.Storage_getHeaderToken(swigCPtr, this);
  }

  public int getStateIndex(String aColumnName, int startIndex) {
    return opensimModelJNI.Storage_getStateIndex__SWIG_0(swigCPtr, this, aColumnName, startIndex);
  }

  public int getStateIndex(String aColumnName) {
    return opensimModelJNI.Storage_getStateIndex__SWIG_1(swigCPtr, this, aColumnName);
  }

  public void setColumnLabels(ArrayStr aColumnLabels) {
    opensimModelJNI.Storage_setColumnLabels(swigCPtr, this, ArrayStr.getCPtr(aColumnLabels), aColumnLabels);
  }

  public ArrayStr getColumnLabels() {
    return new ArrayStr(opensimModelJNI.Storage_getColumnLabels(swigCPtr, this), false);
  }

  public int reset(int aIndex) {
    return opensimModelJNI.Storage_reset__SWIG_0(swigCPtr, this, aIndex);
  }

  public int reset() {
    return opensimModelJNI.Storage_reset__SWIG_1(swigCPtr, this);
  }

  public int reset(double aTime) {
    return opensimModelJNI.Storage_reset__SWIG_2(swigCPtr, this, aTime);
  }

  public void purge() {
    opensimModelJNI.Storage_purge(swigCPtr, this);
  }

  public void crop(double newStartTime, double newFinalTime) {
    opensimModelJNI.Storage_crop(swigCPtr, this, newStartTime, newFinalTime);
  }

  public int append(StateVector aVec, boolean aCheckForDuplicateTime) {
    return opensimModelJNI.Storage_append__SWIG_0(swigCPtr, this, StateVector.getCPtr(aVec), aVec, aCheckForDuplicateTime);
  }

  public int append(StateVector aVec) {
    return opensimModelJNI.Storage_append__SWIG_1(swigCPtr, this, StateVector.getCPtr(aVec), aVec);
  }

  public int append(SWIGTYPE_p_OpenSim__ArrayTOpenSim__StateVector_t aArray) {
    return opensimModelJNI.Storage_append__SWIG_2(swigCPtr, this, SWIGTYPE_p_OpenSim__ArrayTOpenSim__StateVector_t.getCPtr(aArray));
  }

  public int append(double aT, int aN, SWIGTYPE_p_double aY, boolean aCheckForDuplicateTime) {
    return opensimModelJNI.Storage_append__SWIG_3(swigCPtr, this, aT, aN, SWIGTYPE_p_double.getCPtr(aY), aCheckForDuplicateTime);
  }

  public int append(double aT, int aN, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Storage_append__SWIG_4(swigCPtr, this, aT, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public int append(double aT, SWIGTYPE_p_SimTK__Vector aY, boolean aCheckForDuplicateTime) {
    return opensimModelJNI.Storage_append__SWIG_5(swigCPtr, this, aT, SWIGTYPE_p_SimTK__Vector.getCPtr(aY), aCheckForDuplicateTime);
  }

  public int append(double aT, SWIGTYPE_p_SimTK__Vector aY) {
    return opensimModelJNI.Storage_append__SWIG_6(swigCPtr, this, aT, SWIGTYPE_p_SimTK__Vector.getCPtr(aY));
  }

  public int append(double aT, SWIGTYPE_p_SimTK__Vec3 aY, boolean aCheckForDuplicateTime) {
    return opensimModelJNI.Storage_append__SWIG_7(swigCPtr, this, aT, SWIGTYPE_p_SimTK__Vec3.getCPtr(aY), aCheckForDuplicateTime);
  }

  public int append(double aT, SWIGTYPE_p_SimTK__Vec3 aY) {
    return opensimModelJNI.Storage_append__SWIG_8(swigCPtr, this, aT, SWIGTYPE_p_SimTK__Vec3.getCPtr(aY));
  }

  public int store(int aStep, double aT, int aN, SWIGTYPE_p_double aY) {
    return opensimModelJNI.Storage_store(swigCPtr, this, aStep, aT, aN, SWIGTYPE_p_double.getCPtr(aY));
  }

  public void shiftTime(double aValue) {
    opensimModelJNI.Storage_shiftTime(swigCPtr, this, aValue);
  }

  public void scaleTime(double aValue) {
    opensimModelJNI.Storage_scaleTime(swigCPtr, this, aValue);
  }

  public void add(double aValue) {
    opensimModelJNI.Storage_add__SWIG_0(swigCPtr, this, aValue);
  }

  public void add(int aN, double[] aY) {
    opensimModelJNI.Storage_add__SWIG_1(swigCPtr, this, aN, aY);
  }

  public void add(int aN, double aValue) {
    opensimModelJNI.Storage_add__SWIG_2(swigCPtr, this, aN, aValue);
  }

  public void add(StateVector aStateVector) {
    opensimModelJNI.Storage_add__SWIG_3(swigCPtr, this, StateVector.getCPtr(aStateVector), aStateVector);
  }

  public void add(Storage aStorage) {
    opensimModelJNI.Storage_add__SWIG_4(swigCPtr, this, Storage.getCPtr(aStorage), aStorage);
  }

  public void subtract(double aValue) {
    opensimModelJNI.Storage_subtract__SWIG_0(swigCPtr, this, aValue);
  }

  public void subtract(int aN, double[] aY) {
    opensimModelJNI.Storage_subtract__SWIG_1(swigCPtr, this, aN, aY);
  }

  public void subtract(StateVector aStateVector) {
    opensimModelJNI.Storage_subtract__SWIG_2(swigCPtr, this, StateVector.getCPtr(aStateVector), aStateVector);
  }

  public void subtract(Storage aStorage) {
    opensimModelJNI.Storage_subtract__SWIG_3(swigCPtr, this, Storage.getCPtr(aStorage), aStorage);
  }

  public void multiply(double aValue) {
    opensimModelJNI.Storage_multiply__SWIG_0(swigCPtr, this, aValue);
  }

  public void multiplyColumn(int aIndex, double aValue) {
    opensimModelJNI.Storage_multiplyColumn(swigCPtr, this, aIndex, aValue);
  }

  public void multiply(int aN, double[] aY) {
    opensimModelJNI.Storage_multiply__SWIG_1(swigCPtr, this, aN, aY);
  }

  public void multiply(StateVector aStateVector) {
    opensimModelJNI.Storage_multiply__SWIG_2(swigCPtr, this, StateVector.getCPtr(aStateVector), aStateVector);
  }

  public void multiply(Storage aStorage) {
    opensimModelJNI.Storage_multiply__SWIG_3(swigCPtr, this, Storage.getCPtr(aStorage), aStorage);
  }

  public void divide(double aValue) {
    opensimModelJNI.Storage_divide__SWIG_0(swigCPtr, this, aValue);
  }

  public void divide(int aN, double[] aY) {
    opensimModelJNI.Storage_divide__SWIG_1(swigCPtr, this, aN, aY);
  }

  public void divide(StateVector aStateVector) {
    opensimModelJNI.Storage_divide__SWIG_2(swigCPtr, this, StateVector.getCPtr(aStateVector), aStateVector);
  }

  public void divide(Storage aStorage) {
    opensimModelJNI.Storage_divide__SWIG_3(swigCPtr, this, Storage.getCPtr(aStorage), aStorage);
  }

  public Storage integrate(int aI1, int aI2) {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_0(swigCPtr, this, aI1, aI2);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage integrate(int aI1) {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_1(swigCPtr, this, aI1);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage integrate() {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_2(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage integrate(double aT1, double aT2) {
    long cPtr = opensimModelJNI.Storage_integrate__SWIG_3(swigCPtr, this, aT1, aT2);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public int computeArea(int aN, SWIGTYPE_p_double aArea) {
    return opensimModelJNI.Storage_computeArea__SWIG_0(swigCPtr, this, aN, SWIGTYPE_p_double.getCPtr(aArea));
  }

  public int computeArea(double aTI, double aTF, int aN, SWIGTYPE_p_double aArea) {
    return opensimModelJNI.Storage_computeArea__SWIG_1(swigCPtr, this, aTI, aTF, aN, SWIGTYPE_p_double.getCPtr(aArea));
  }

  public int computeAverage(int aN, SWIGTYPE_p_double aAve) {
    return opensimModelJNI.Storage_computeAverage__SWIG_0(swigCPtr, this, aN, SWIGTYPE_p_double.getCPtr(aAve));
  }

  public int computeAverage(double aTI, double aTF, int aN, SWIGTYPE_p_double aAve) {
    return opensimModelJNI.Storage_computeAverage__SWIG_1(swigCPtr, this, aTI, aTF, aN, SWIGTYPE_p_double.getCPtr(aAve));
  }

  public void pad(int aPadSize) {
    opensimModelJNI.Storage_pad(swigCPtr, this, aPadSize);
  }

  public void smoothSpline(int aOrder, double aCutoffFrequency) {
    opensimModelJNI.Storage_smoothSpline(swigCPtr, this, aOrder, aCutoffFrequency);
  }

  public void lowpassIIR(double aCutoffFequency) {
    opensimModelJNI.Storage_lowpassIIR(swigCPtr, this, aCutoffFequency);
  }

  public void lowpassFIR(int aOrder, double aCutoffFequency) {
    opensimModelJNI.Storage_lowpassFIR(swigCPtr, this, aOrder, aCutoffFequency);
  }

  public void addToRdStorage(Storage rStorage, double aStartTime, double aEndTime) {
    opensimModelJNI.Storage_addToRdStorage(swigCPtr, this, Storage.getCPtr(rStorage), rStorage, aStartTime, aEndTime);
  }

  public int findIndex(double aT) {
    return opensimModelJNI.Storage_findIndex__SWIG_0(swigCPtr, this, aT);
  }

  public int findIndex(int aI, double aT) {
    return opensimModelJNI.Storage_findIndex__SWIG_1(swigCPtr, this, aI, aT);
  }

  public void findFrameRange(double aStartTime, double aEndTime, SWIGTYPE_p_int oStartFrame, SWIGTYPE_p_int oEndFrame) {
    opensimModelJNI.Storage_findFrameRange(swigCPtr, this, aStartTime, aEndTime, SWIGTYPE_p_int.getCPtr(oStartFrame), SWIGTYPE_p_int.getCPtr(oEndFrame));
  }

  public double resample(double aDT, int aDegree) {
    return opensimModelJNI.Storage_resample(swigCPtr, this, aDT, aDegree);
  }

  public double resampleLinear(double aDT) {
    return opensimModelJNI.Storage_resampleLinear(swigCPtr, this, aDT);
  }

  public double compareColumn(Storage aOtherStorage, SWIGTYPE_p_std__string aColumnName, double startTime, double endTime) {
    return opensimModelJNI.Storage_compareColumn__SWIG_0(swigCPtr, this, Storage.getCPtr(aOtherStorage), aOtherStorage, SWIGTYPE_p_std__string.getCPtr(aColumnName), startTime, endTime);
  }

  public double compareColumn(Storage aOtherStorage, SWIGTYPE_p_std__string aColumnName, double startTime) {
    return opensimModelJNI.Storage_compareColumn__SWIG_1(swigCPtr, this, Storage.getCPtr(aOtherStorage), aOtherStorage, SWIGTYPE_p_std__string.getCPtr(aColumnName), startTime);
  }

  public boolean makeStorageLabelsUnique() {
    return opensimModelJNI.Storage_makeStorageLabelsUnique(swigCPtr, this);
  }

  public void print() {
    opensimModelJNI.Storage_print__SWIG_0(swigCPtr, this);
  }

  public boolean print(String aFileName, String aMode, String aComment) {
    return opensimModelJNI.Storage_print__SWIG_1(swigCPtr, this, aFileName, aMode, aComment);
  }

  public boolean print(String aFileName, String aMode) {
    return opensimModelJNI.Storage_print__SWIG_2(swigCPtr, this, aFileName, aMode);
  }

  public boolean print(String aFileName) {
    return opensimModelJNI.Storage_print__SWIG_3(swigCPtr, this, aFileName);
  }

  public int print(String aFileName, double aDT, String aMode) {
    return opensimModelJNI.Storage_print__SWIG_4(swigCPtr, this, aFileName, aDT, aMode);
  }

  public int print(String aFileName, double aDT) {
    return opensimModelJNI.Storage_print__SWIG_5(swigCPtr, this, aFileName, aDT);
  }

  public void setOutputFileName(String aFileName) {
    opensimModelJNI.Storage_setOutputFileName(swigCPtr, this, aFileName);
  }

  public static void printResult(Storage aStorage, String aName, String aDir, double aDT, String aExtension) {
    opensimModelJNI.Storage_printResult(Storage.getCPtr(aStorage), aStorage, aName, aDir, aDT, aExtension);
  }

  public void interpolateAt(ArrayDouble targetTimes) {
    opensimModelJNI.Storage_interpolateAt(swigCPtr, this, ArrayDouble.getCPtr(targetTimes), targetTimes);
  }

}
