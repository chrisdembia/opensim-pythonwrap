/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class IKSolverInterface {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public IKSolverInterface(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IKSolverInterface obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_IKSolverInterface(swigCPtr);
    }
    swigCPtr = 0;
  }

  public IKSolverInterface(SimmInverseKinematicsTarget aOptimizationTarget) {
    this(opensimModelJNI.new_IKSolverInterface(SimmInverseKinematicsTarget.getCPtr(aOptimizationTarget)), true);
  }

  public void solveFrames(SimmIKTrialParams aIKOptions, Storage inputData, Storage outputData) {
    opensimModelJNI.IKSolverInterface_solveFrames(swigCPtr, SimmIKTrialParams.getCPtr(aIKOptions), Storage.getCPtr(inputData), Storage.getCPtr(outputData));
  }

}
