/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Actuation extends Analysis {
  private long swigCPtr;

  public Actuation(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.Actuation_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Actuation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_Actuation(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Actuation(Model aModel) {
    this(opensimModelJNI.new_Actuation__SWIG_0(Model.getCPtr(aModel), aModel), true);
  }

  public Actuation() {
    this(opensimModelJNI.new_Actuation__SWIG_1(), true);
  }

  public Actuation(String aFileName) {
    this(opensimModelJNI.new_Actuation__SWIG_2(aFileName), true);
  }

  public Actuation(Actuation aObject) {
    this(opensimModelJNI.new_Actuation__SWIG_3(Actuation.getCPtr(aObject), aObject), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Actuation_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setStorageCapacityIncrements(int aIncrement) {
    opensimModelJNI.Actuation_setStorageCapacityIncrements(swigCPtr, this, aIncrement);
  }

  public Storage getForceStorage() {
    long cPtr = opensimModelJNI.Actuation_getForceStorage(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getSpeedStorage() {
    long cPtr = opensimModelJNI.Actuation_getSpeedStorage(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getPowerStorage() {
    long cPtr = opensimModelJNI.Actuation_getPowerStorage(swigCPtr, this);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.Actuation_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public int printResults(String aBaseName, String aDir, double aDT, String aExtension) {
    return opensimModelJNI.Actuation_printResults__SWIG_0(swigCPtr, this, aBaseName, aDir, aDT, aExtension);
  }

  public int printResults(String aBaseName, String aDir, double aDT) {
    return opensimModelJNI.Actuation_printResults__SWIG_1(swigCPtr, this, aBaseName, aDir, aDT);
  }

  public int printResults(String aBaseName, String aDir) {
    return opensimModelJNI.Actuation_printResults__SWIG_2(swigCPtr, this, aBaseName, aDir);
  }

  public int printResults(String aBaseName) {
    return opensimModelJNI.Actuation_printResults__SWIG_3(swigCPtr, this, aBaseName);
  }

}
