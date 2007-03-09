/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class GeneralizedForces extends Analysis {
  private long swigCPtr;

  public GeneralizedForces(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GeneralizedForces obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_GeneralizedForces(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public GeneralizedForces(AbstractModel aModel) {
    this(opensimModelJNI.new_GeneralizedForces__SWIG_0(AbstractModel.getCPtr(aModel)), true);
  }

  public GeneralizedForces() {
    this(opensimModelJNI.new_GeneralizedForces__SWIG_1(), true);
  }

  public GeneralizedForces(String aFileName) {
    this(opensimModelJNI.new_GeneralizedForces__SWIG_2(aFileName), true);
  }

  public GeneralizedForces(GeneralizedForces aObject) {
    this(opensimModelJNI.new_GeneralizedForces__SWIG_3(GeneralizedForces.getCPtr(aObject)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.GeneralizedForces_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setStorageCapacityIncrements(int aIncrement) {
    opensimModelJNI.GeneralizedForces_setStorageCapacityIncrements(swigCPtr, aIncrement);
  }

  public Storage getGravGenForcesStorage() {
    long cPtr = opensimModelJNI.GeneralizedForces_getGravGenForcesStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getVelGenForcesStorage() {
    long cPtr = opensimModelJNI.GeneralizedForces_getVelGenForcesStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getActuatorGenForcesStorage() {
    long cPtr = opensimModelJNI.GeneralizedForces_getActuatorGenForcesStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getContactGenForcesStorage() {
    long cPtr = opensimModelJNI.GeneralizedForces_getContactGenForcesStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public void setModel(AbstractModel aModel) {
    opensimModelJNI.GeneralizedForces_setModel(swigCPtr, AbstractModel.getCPtr(aModel));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.GeneralizedForces_begin__SWIG_0(swigCPtr, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int begin(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.GeneralizedForces_begin__SWIG_1(swigCPtr, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.GeneralizedForces_step__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int step(SWIGTYPE_p_double aXPrev, SWIGTYPE_p_double aYPrev, int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.GeneralizedForces_step__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(aXPrev), SWIGTYPE_p_double.getCPtr(aYPrev), aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int end(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY, SWIGTYPE_p_void aClientData) {
    return opensimModelJNI.GeneralizedForces_end__SWIG_0(swigCPtr, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY), SWIGTYPE_p_void.getCPtr(aClientData));
  }

  public int end(int aStep, double aDT, double aT, SWIGTYPE_p_double aX, SWIGTYPE_p_double aY) {
    return opensimModelJNI.GeneralizedForces_end__SWIG_1(swigCPtr, aStep, aDT, aT, SWIGTYPE_p_double.getCPtr(aX), SWIGTYPE_p_double.getCPtr(aY));
  }

  public int printResults(String aBaseName, String aDir, double aDT, String aExtension) {
    return opensimModelJNI.GeneralizedForces_printResults__SWIG_0(swigCPtr, aBaseName, aDir, aDT, aExtension);
  }

  public int printResults(String aBaseName, String aDir, double aDT) {
    return opensimModelJNI.GeneralizedForces_printResults__SWIG_1(swigCPtr, aBaseName, aDir, aDT);
  }

  public int printResults(String aBaseName, String aDir) {
    return opensimModelJNI.GeneralizedForces_printResults__SWIG_2(swigCPtr, aBaseName, aDir);
  }

  public int printResults(String aBaseName) {
    return opensimModelJNI.GeneralizedForces_printResults__SWIG_3(swigCPtr, aBaseName);
  }

}
