/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmSubject extends OpenSimObject {
  private long swigCPtr;

  public SimmSubject(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimmSubject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmSubject(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SimmSubject() {
    this(opensimModelJNI.new_SimmSubject__SWIG_0(), true);
  }

  public SimmSubject(String aFileName) {
    this(opensimModelJNI.new_SimmSubject__SWIG_1(aFileName), true);
  }

  public SimmSubject(SimmSubject aSubject) {
    this(opensimModelJNI.new_SimmSubject__SWIG_2(SimmSubject.getCPtr(aSubject)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmSubject_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(SimmSubject aSubject) {
    opensimModelJNI.SimmSubject_copyData(swigCPtr, SimmSubject.getCPtr(aSubject));
  }

  public boolean processModel() {
    return opensimModelJNI.SimmSubject_processModel(swigCPtr);
  }

  public AbstractModel createModel() {
    long cPtr = opensimModelJNI.SimmSubject_createModel(swigCPtr);
    return (cPtr == 0) ? null : new AbstractModel(cPtr, false);
  }

  public SimmGenericModelMaker getGenericModelMaker() {
    return new SimmGenericModelMaker(opensimModelJNI.SimmSubject_getGenericModelMaker(swigCPtr), false);
  }

  public SimmModelScaler getModelScaler() {
    return new SimmModelScaler(opensimModelJNI.SimmSubject_getModelScaler(swigCPtr), false);
  }

  public SimmMarkerPlacer getMarkerPlacer() {
    return new SimmMarkerPlacer(opensimModelJNI.SimmSubject_getMarkerPlacer(swigCPtr), false);
  }

  public double getMass() {
    return opensimModelJNI.SimmSubject_getMass(swigCPtr);
  }

  public boolean isDefaultGenericModelMaker() {
    return opensimModelJNI.SimmSubject_isDefaultGenericModelMaker(swigCPtr);
  }

  public boolean isDefaultModelScaler() {
    return opensimModelJNI.SimmSubject_isDefaultModelScaler(swigCPtr);
  }

  public boolean isDefaultMarkerPlacer() {
    return opensimModelJNI.SimmSubject_isDefaultMarkerPlacer(swigCPtr);
  }

  public static void registerTypes() {
    opensimModelJNI.SimmSubject_registerTypes();
  }

  public double getSubjectMass() {
    return opensimModelJNI.SimmSubject_getSubjectMass(swigCPtr);
  }

  public double getSubjectAge() {
    return opensimModelJNI.SimmSubject_getSubjectAge(swigCPtr);
  }

  public double getSubjectHeight() {
    return opensimModelJNI.SimmSubject_getSubjectHeight(swigCPtr);
  }

  public String getPathToSubject() {
    return opensimModelJNI.SimmSubject_getPathToSubject(swigCPtr);
  }

  public void setPathToSubject(String aPath) {
    opensimModelJNI.SimmSubject_setPathToSubject(swigCPtr, aPath);
  }

  public void peteTest() {
    opensimModelJNI.SimmSubject_peteTest(swigCPtr);
  }

}
