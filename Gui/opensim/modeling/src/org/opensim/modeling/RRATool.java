/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class RRATool extends AbstractTool {
  private long swigCPtr;

  public RRATool(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.RRATool_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(RRATool obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_RRATool(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static RRATool safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.RRATool_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new RRATool(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.RRATool_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.RRATool_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.RRATool_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new RRATool(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.RRATool_getConcreteClassName(swigCPtr, this);
  }

  public RRATool() {
    this(opensimModelJNI.new_RRATool__SWIG_0(), true);
  }

  public RRATool(String aFileName, boolean aLoadModel) throws java.io.IOException {
    this(opensimModelJNI.new_RRATool__SWIG_1(aFileName, aLoadModel), true);
  }

  public RRATool(String aFileName) throws java.io.IOException {
    this(opensimModelJNI.new_RRATool__SWIG_2(aFileName), true);
  }

  public RRATool(RRATool aObject) {
    this(opensimModelJNI.new_RRATool__SWIG_3(RRATool.getCPtr(aObject), aObject), true);
  }

  public String getDesiredPointsFileName() {
    return opensimModelJNI.RRATool_getDesiredPointsFileName(swigCPtr, this);
  }

  public void setDesiredPointsFileName(String aFileName) {
    opensimModelJNI.RRATool_setDesiredPointsFileName(swigCPtr, this, aFileName);
  }

  public String getDesiredKinematicsFileName() {
    return opensimModelJNI.RRATool_getDesiredKinematicsFileName(swigCPtr, this);
  }

  public void setDesiredKinematicsFileName(String aFileName) {
    opensimModelJNI.RRATool_setDesiredKinematicsFileName(swigCPtr, this, aFileName);
  }

  public String getConstraintsFileName() {
    return opensimModelJNI.RRATool_getConstraintsFileName(swigCPtr, this);
  }

  public void setConstraintsFileName(String aFileName) {
    opensimModelJNI.RRATool_setConstraintsFileName(swigCPtr, this, aFileName);
  }

  public String getTaskSetFileName() {
    return opensimModelJNI.RRATool_getTaskSetFileName(swigCPtr, this);
  }

  public void setTaskSetFileName(String aFileName) {
    opensimModelJNI.RRATool_setTaskSetFileName(swigCPtr, this, aFileName);
  }

  public String getOutputModelFileName() {
    return opensimModelJNI.RRATool_getOutputModelFileName(swigCPtr, this);
  }

  public void setOutputModelFileName(String aFileName) {
    opensimModelJNI.RRATool_setOutputModelFileName(swigCPtr, this, aFileName);
  }

  public boolean getAdjustCOMToReduceResiduals() {
    return opensimModelJNI.RRATool_getAdjustCOMToReduceResiduals(swigCPtr, this);
  }

  public void setAdjustCOMToReduceResiduals(boolean aAdjust) {
    opensimModelJNI.RRATool_setAdjustCOMToReduceResiduals(swigCPtr, this, aAdjust);
  }

  public String getAdjustedCOMBody() {
    return opensimModelJNI.RRATool_getAdjustedCOMBody(swigCPtr, this);
  }

  public void setAdjustedCOMBody(String aBody) {
    opensimModelJNI.RRATool_setAdjustedCOMBody(swigCPtr, this, aBody);
  }

  public double getLowpassCutoffFrequency() {
    return opensimModelJNI.RRATool_getLowpassCutoffFrequency(swigCPtr, this);
  }

  public void setLowpassCutoffFrequency(double aLowpassCutoffFrequency) {
    opensimModelJNI.RRATool_setLowpassCutoffFrequency(swigCPtr, this, aLowpassCutoffFrequency);
  }

  public String getExternalLoadsFileName() {
    return opensimModelJNI.RRATool_getExternalLoadsFileName(swigCPtr, this);
  }

  public void setExternalLoadsFileName(String aFileName) {
    opensimModelJNI.RRATool_setExternalLoadsFileName(swigCPtr, this, aFileName);
  }

  public boolean run() throws java.io.IOException {
    return opensimModelJNI.RRATool_run(swigCPtr, this);
  }

  public Storage getForceStorage() {
    return new Storage(opensimModelJNI.RRATool_getForceStorage(swigCPtr, this), false);
  }

  public void setOriginalForceSet(ForceSet aForceSet) {
    opensimModelJNI.RRATool_setOriginalForceSet(swigCPtr, this, ForceSet.getCPtr(aForceSet), aForceSet);
  }

  public void updateFromXMLNode(SWIGTYPE_p_SimTK__Xml__Element aNode, int versionNumber) {
    opensimModelJNI.RRATool_updateFromXMLNode__SWIG_0(swigCPtr, this, SWIGTYPE_p_SimTK__Xml__Element.getCPtr(aNode), versionNumber);
  }

  public void updateFromXMLNode(SWIGTYPE_p_SimTK__Xml__Element aNode) {
    opensimModelJNI.RRATool_updateFromXMLNode__SWIG_1(swigCPtr, this, SWIGTYPE_p_SimTK__Xml__Element.getCPtr(aNode));
  }

}
