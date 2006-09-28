/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.realisticDynamics;
import org.opensim.modeling.*;

public class rdCMC extends Controller {
  private long swigCPtr;

  protected rdCMC(long cPtr, boolean cMemoryOwn) {
    super(cmcJNI.SWIGrdCMCUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(rdCMC obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      cmcJNI.delete_rdCMC(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public rdCMC(Model aModel, rdCMC_TaskSet aSet) {
    this(cmcJNI.new_rdCMC(Model.getCPtr(aModel), rdCMC_TaskSet.getCPtr(aSet)), true);
  }

  public void setNull() {
    cmcJNI.rdCMC_setNull(swigCPtr);
  }

  public void setControlConstraints(ControlSet aCcontrolSet) {
    cmcJNI.rdCMC_setControlConstraints(swigCPtr, ControlSet.getCPtr(aCcontrolSet));
  }

  public ControlSet getControlConstraints() {
    long cPtr = cmcJNI.rdCMC_getControlConstraints(swigCPtr);
    return (cPtr == 0) ? null : new ControlSet(cPtr, false);
  }

  public ControlSet getControlSet() {
    long cPtr = cmcJNI.rdCMC_getControlSet(swigCPtr);
    return (cPtr == 0) ? null : new ControlSet(cPtr, false);
  }

  public rdCMC_TaskSet getTaskSet() {
    long cPtr = cmcJNI.rdCMC_getTaskSet(swigCPtr);
    return (cPtr == 0) ? null : new rdCMC_TaskSet(cPtr, false);
  }

  public ArrayInt getParameterList() {
    long cPtr = cmcJNI.rdCMC_getParameterList(swigCPtr);
    return (cPtr == 0) ? null : new ArrayInt(cPtr, false);
  }

  public SWIGTYPE_p_OpenSim__rdFSQP getOptimizer() {
    long cPtr = cmcJNI.rdCMC_getOptimizer(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__rdFSQP(cPtr, false);
  }

  public SWIGTYPE_p_OpenSim__rdOptimizationTarget setOptimizationTarget(SWIGTYPE_p_OpenSim__rdOptimizationTarget aTarget) {
    long cPtr = cmcJNI.rdCMC_setOptimizationTarget(swigCPtr, SWIGTYPE_p_OpenSim__rdOptimizationTarget.getCPtr(aTarget));
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__rdOptimizationTarget(cPtr, false);
  }

  public SWIGTYPE_p_OpenSim__rdOptimizationTarget getOptimizationTarget() {
    long cPtr = cmcJNI.rdCMC_getOptimizationTarget(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__rdOptimizationTarget(cPtr, false);
  }

  public void setDT(double aDT) {
    cmcJNI.rdCMC_setDT(swigCPtr, aDT);
  }

  public double getDT() {
    return cmcJNI.rdCMC_getDT(swigCPtr);
  }

  public void setTargetTime(double aTime) {
    cmcJNI.rdCMC_setTargetTime(swigCPtr, aTime);
  }

  public double getTargetTime() {
    return cmcJNI.rdCMC_getTargetTime(swigCPtr);
  }

  public void setTargetDT(double aDT) {
    cmcJNI.rdCMC_setTargetDT(swigCPtr, aDT);
  }

  public double getTargetDT() {
    return cmcJNI.rdCMC_getTargetDT(swigCPtr);
  }

  public void setCheckTargetTime(boolean aTrueFalse) {
    cmcJNI.rdCMC_setCheckTargetTime(swigCPtr, aTrueFalse);
  }

  public boolean getCheckTargetTime() {
    return cmcJNI.rdCMC_getCheckTargetTime(swigCPtr);
  }

  public void setActuatorForcePredictor(SWIGTYPE_p_OpenSim__VectorFunctionForActuators aPredictor) {
    cmcJNI.rdCMC_setActuatorForcePredictor(swigCPtr, SWIGTYPE_p_OpenSim__VectorFunctionForActuators.getCPtr(aPredictor));
  }

  public SWIGTYPE_p_OpenSim__VectorFunctionForActuators getActuatorForcePredictor() {
    long cPtr = cmcJNI.rdCMC_getActuatorForcePredictor(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__VectorFunctionForActuators(cPtr, false);
  }

  public Storage getPositionErrorStorage() {
    long cPtr = cmcJNI.rdCMC_getPositionErrorStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getVelocityErrorStorage() {
    long cPtr = cmcJNI.rdCMC_getVelocityErrorStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public Storage getStressTermWeightStorage() {
    long cPtr = cmcJNI.rdCMC_getStressTermWeightStorage(swigCPtr);
    return (cPtr == 0) ? null : new Storage(cPtr, false);
  }

  public void setUseReflexes(boolean aTrueFalse) {
    cmcJNI.rdCMC_setUseReflexes(swigCPtr, aTrueFalse);
  }

  public boolean getUseReflexes() {
    return cmcJNI.rdCMC_getUseReflexes(swigCPtr);
  }

  public void constrainControlsBasedOnReflexes(double time, ArrayDouble xmin, ArrayDouble xmax) {
    cmcJNI.rdCMC_constrainControlsBasedOnReflexes(swigCPtr, time, ArrayDouble.getCPtr(xmin), ArrayDouble.getCPtr(xmax));
  }

  public void restoreConfiguration(int nqnu, SWIGTYPE_p_double yi, SWIGTYPE_p_double y) {
    cmcJNI.rdCMC_restoreConfiguration(swigCPtr, nqnu, SWIGTYPE_p_double.getCPtr(yi), SWIGTYPE_p_double.getCPtr(y));
  }

  public void obtainActuatorEquilibrium(double tiReal, double dtReal, ArrayDouble x, ArrayDouble y, boolean hold) {
    cmcJNI.rdCMC_obtainActuatorEquilibrium(swigCPtr, tiReal, dtReal, ArrayDouble.getCPtr(x), ArrayDouble.getCPtr(y), hold);
  }

  public void computeInitialStates(SWIGTYPE_p_double rTI, SWIGTYPE_p_double rYI) {
    cmcJNI.rdCMC_computeInitialStates(swigCPtr, SWIGTYPE_p_double.getCPtr(rTI), SWIGTYPE_p_double.getCPtr(rYI));
  }

  public void computeControls(SWIGTYPE_p_double rDT, double aT, SWIGTYPE_p_double aY, ControlSet rX) {
    cmcJNI.rdCMC_computeControls(swigCPtr, SWIGTYPE_p_double.getCPtr(rDT), aT, SWIGTYPE_p_double.getCPtr(aY), ControlSet.getCPtr(rX));
  }

  public static void FilterControls(ControlSet aControlSet, double aDT, double aT, ArrayDouble rControls) {
    cmcJNI.rdCMC_FilterControls(ControlSet.getCPtr(aControlSet), aDT, aT, ArrayDouble.getCPtr(rControls));
  }

}
