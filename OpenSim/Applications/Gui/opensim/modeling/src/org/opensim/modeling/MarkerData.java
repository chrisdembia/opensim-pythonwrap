/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class MarkerData extends OpenSimObject {
  private long swigCPtr;

  public MarkerData(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.MarkerData_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(MarkerData obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_MarkerData(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public double[] getTimeRange() { return new double[]{getStartFrameTime(), getLastFrameTime()}; }

  public MarkerData() {
    this(opensimModelJNI.new_MarkerData__SWIG_0(), true);
  }

  public MarkerData(String aFileName) throws java.io.IOException {
    this(opensimModelJNI.new_MarkerData__SWIG_1(aFileName), true);
  }

  public void findFrameRange(double aStartTime, double aEndTime, SWIGTYPE_p_int rStartFrame, SWIGTYPE_p_int rEndFrame) {
    opensimModelJNI.MarkerData_findFrameRange(swigCPtr, this, aStartTime, aEndTime, SWIGTYPE_p_int.getCPtr(rStartFrame), SWIGTYPE_p_int.getCPtr(rEndFrame));
  }

  public void averageFrames(double aThreshold, double aStartTime, double aEndTime) {
    opensimModelJNI.MarkerData_averageFrames__SWIG_0(swigCPtr, this, aThreshold, aStartTime, aEndTime);
  }

  public void averageFrames(double aThreshold, double aStartTime) {
    opensimModelJNI.MarkerData_averageFrames__SWIG_1(swigCPtr, this, aThreshold, aStartTime);
  }

  public void averageFrames(double aThreshold) {
    opensimModelJNI.MarkerData_averageFrames__SWIG_2(swigCPtr, this, aThreshold);
  }

  public void averageFrames() {
    opensimModelJNI.MarkerData_averageFrames__SWIG_3(swigCPtr, this);
  }

  public String getFileName() {
    return opensimModelJNI.MarkerData_getFileName(swigCPtr, this);
  }

  public void makeRdStorage(Storage rStorage) {
    opensimModelJNI.MarkerData_makeRdStorage(swigCPtr, this, Storage.getCPtr(rStorage), rStorage);
  }

  public SWIGTYPE_p_MarkerFrame getFrame(int aIndex) {
    return new SWIGTYPE_p_MarkerFrame(opensimModelJNI.MarkerData_getFrame(swigCPtr, this, aIndex), false);
  }

  public int getMarkerIndex(String aName) {
    return opensimModelJNI.MarkerData_getMarkerIndex(swigCPtr, this, aName);
  }

  public Units getUnits() {
    return new Units(opensimModelJNI.MarkerData_getUnits(swigCPtr, this), false);
  }

  public void convertToUnits(Units aUnits) {
    opensimModelJNI.MarkerData_convertToUnits(swigCPtr, this, Units.getCPtr(aUnits), aUnits);
  }

  public ArrayStr getMarkerNames() {
    return new ArrayStr(opensimModelJNI.MarkerData_getMarkerNames(swigCPtr, this), false);
  }

  public int getNumMarkers() {
    return opensimModelJNI.MarkerData_getNumMarkers(swigCPtr, this);
  }

  public int getNumFrames() {
    return opensimModelJNI.MarkerData_getNumFrames(swigCPtr, this);
  }

  public double getStartFrameTime() {
    return opensimModelJNI.MarkerData_getStartFrameTime(swigCPtr, this);
  }

  public double getLastFrameTime() {
    return opensimModelJNI.MarkerData_getLastFrameTime(swigCPtr, this);
  }

  public double getDataRate() {
    return opensimModelJNI.MarkerData_getDataRate(swigCPtr, this);
  }

  public double getCameraRate() {
    return opensimModelJNI.MarkerData_getCameraRate(swigCPtr, this);
  }

}
