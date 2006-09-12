/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmMotionData {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected SimmMotionData(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SimmMotionData obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmMotionData(swigCPtr);
    }
    swigCPtr = 0;
  }

  public SimmMotionData() {
    this(opensimModelJNI.new_SimmMotionData__SWIG_0(), true);
  }

  public SimmMotionData(String aFileName) {
    this(opensimModelJNI.new_SimmMotionData__SWIG_1(aFileName), true);
  }

  public SimmMotionData(Storage aData) {
    this(opensimModelJNI.new_SimmMotionData__SWIG_2(Storage.getCPtr(aData)), true);
  }

  public int getNumColumns() {
    return opensimModelJNI.SimmMotionData_getNumColumns(swigCPtr);
  }

  public int getColumnIndex(String aName) {
    return opensimModelJNI.SimmMotionData_getColumnIndex(swigCPtr, aName);
  }

  public void setColumnLabel(int aIndex, String aLabel) {
    opensimModelJNI.SimmMotionData_setColumnLabel(swigCPtr, aIndex, aLabel);
  }

  public double getValue(String aName, int aFrameIndex) {
    return opensimModelJNI.SimmMotionData_getValue(swigCPtr, aName, aFrameIndex);
  }

  public double getRangeMin() {
    return opensimModelJNI.SimmMotionData_getRangeMin(swigCPtr);
  }

  public double getRangeMax() {
    return opensimModelJNI.SimmMotionData_getRangeMax(swigCPtr);
  }

  public void addToRdStorage(Storage aStorage, double startTime, double endTime) {
    opensimModelJNI.SimmMotionData_addToRdStorage(swigCPtr, Storage.getCPtr(aStorage), startTime, endTime);
  }

  public void writeSIMMMotionFile(String aFileName, String aComment) {
    opensimModelJNI.SimmMotionData_writeSIMMMotionFile(swigCPtr, aFileName, aComment);
  }

  public void peteTest() {
    opensimModelJNI.SimmMotionData_peteTest(swigCPtr);
  }

}
