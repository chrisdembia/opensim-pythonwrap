/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class MarkerSet extends SetMarkers {
  private long swigCPtr;

  public MarkerSet(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(MarkerSet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_MarkerSet(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public MarkerSet() {
    this(opensimModelJNI.new_MarkerSet__SWIG_0(), true);
  }

  public MarkerSet(String aMarkersFileName) throws java.io.IOException {
    this(opensimModelJNI.new_MarkerSet__SWIG_1(aMarkersFileName), true);
  }

  public MarkerSet(MarkerSet aMarkerSet) {
    this(opensimModelJNI.new_MarkerSet__SWIG_2(MarkerSet.getCPtr(aMarkerSet), aMarkerSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.MarkerSet_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setup(AbstractDynamicsEngine aAbstractDynamicsEngine) {
    opensimModelJNI.MarkerSet_setup(swigCPtr, this, AbstractDynamicsEngine.getCPtr(aAbstractDynamicsEngine), aAbstractDynamicsEngine);
  }

  public void getMarkerNames(ArrayStr aMarkerNamesArray) {
    opensimModelJNI.MarkerSet_getMarkerNames(swigCPtr, this, ArrayStr.getCPtr(aMarkerNamesArray), aMarkerNamesArray);
  }

  public void scale(ScaleSet aScaleSet) {
    opensimModelJNI.MarkerSet_scale(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void addNamePrefix(String prefix) {
    opensimModelJNI.MarkerSet_addNamePrefix(swigCPtr, this, prefix);
  }

}
