/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class IKTool extends SimulationTool {
  private long swigCPtr;

  public IKTool(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(IKTool obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_IKTool(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public IKTool() {
    this(opensimModelJNI.new_IKTool__SWIG_0(), true);
  }

  public IKTool(String aFileName, AbstractModel guiModel) {
    this(opensimModelJNI.new_IKTool__SWIG_1(aFileName, AbstractModel.getCPtr(guiModel)), true);
  }

  public IKTool(String aFileName) {
    this(opensimModelJNI.new_IKTool__SWIG_2(aFileName), true);
  }

  public IKTool(IKTool aObject) {
    this(opensimModelJNI.new_IKTool__SWIG_3(IKTool.getCPtr(aObject)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.IKTool_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public static void registerTypes() {
    opensimModelJNI.IKTool_registerTypes();
  }

  public SimmIKTrialSet getIKTrialSet() {
    return new SimmIKTrialSet(opensimModelJNI.IKTool_getIKTrialSet(swigCPtr), false);
  }

  public void run() {
    opensimModelJNI.IKTool_run(swigCPtr);
  }

}
