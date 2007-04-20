/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Analysis extends IntegCallback {
  private long swigCPtr;

  public Analysis(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Analysis obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Analysis(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public Analysis(Model aModel) {
    this(opensimModelJNI.new_Analysis__SWIG_0(Model.getCPtr(aModel), aModel), true);
  }

  public Analysis() {
    this(opensimModelJNI.new_Analysis__SWIG_1(), true);
  }

  public Analysis(String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_Analysis__SWIG_2(aFileName, aUpdateFromXMLNode), true);
  }

  public Analysis(String aFileName) {
    this(opensimModelJNI.new_Analysis__SWIG_3(aFileName), true);
  }

  public Analysis(Analysis aObject) {
    this(opensimModelJNI.new_Analysis__SWIG_4(Analysis.getCPtr(aObject), aObject), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Analysis_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.Analysis_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void setInDegrees(boolean aTrueFalse) {
    opensimModelJNI.Analysis_setInDegrees(swigCPtr, this, aTrueFalse);
  }

  public boolean getInDegrees() {
    return opensimModelJNI.Analysis_getInDegrees(swigCPtr, this);
  }

  public void setColumnLabels(ArrayStr aLabels) {
    opensimModelJNI.Analysis_setColumnLabels(swigCPtr, this, ArrayStr.getCPtr(aLabels), aLabels);
  }

  public ArrayStr getColumnLabels() {
    return new ArrayStr(opensimModelJNI.Analysis_getColumnLabels(swigCPtr, this), false);
  }

  public ArrayStorage getStorageList() {
    return new ArrayStorage(opensimModelJNI.Analysis_getStorageList(swigCPtr, this), false);
  }

  public boolean proceed(int aStep) {
    return opensimModelJNI.Analysis_proceed__SWIG_0(swigCPtr, this, aStep);
  }

  public boolean proceed() {
    return opensimModelJNI.Analysis_proceed__SWIG_1(swigCPtr, this);
  }

  public int printResults(String aBaseName, String aDir, double aDT, String aExtension) {
    return opensimModelJNI.Analysis_printResults__SWIG_0(swigCPtr, this, aBaseName, aDir, aDT, aExtension);
  }

  public int printResults(String aBaseName, String aDir, double aDT) {
    return opensimModelJNI.Analysis_printResults__SWIG_1(swigCPtr, this, aBaseName, aDir, aDT);
  }

  public int printResults(String aBaseName, String aDir) {
    return opensimModelJNI.Analysis_printResults__SWIG_2(swigCPtr, this, aBaseName, aDir);
  }

  public int printResults(String aBaseName) {
    return opensimModelJNI.Analysis_printResults__SWIG_3(swigCPtr, this, aBaseName);
  }

}
