/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ProbeReporter extends Analysis {
  private long swigCPtr;

  public ProbeReporter(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.ProbeReporter_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ProbeReporter obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_ProbeReporter(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static ProbeReporter safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.ProbeReporter_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new ProbeReporter(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.ProbeReporter_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.ProbeReporter_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.ProbeReporter_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new ProbeReporter(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.ProbeReporter_getConcreteClassName(swigCPtr, this);
  }

  public ProbeReporter(Model aModel) {
    this(opensimModelJNI.new_ProbeReporter__SWIG_0(Model.getCPtr(aModel), aModel), true);
  }

  public ProbeReporter() {
    this(opensimModelJNI.new_ProbeReporter__SWIG_1(), true);
  }

  public ProbeReporter(String aFileName) {
    this(opensimModelJNI.new_ProbeReporter__SWIG_2(aFileName), true);
  }

  public ProbeReporter(ProbeReporter aObject) {
    this(opensimModelJNI.new_ProbeReporter__SWIG_3(ProbeReporter.getCPtr(aObject), aObject), true);
  }

  public Storage getProbeStorage() {
    return new Storage(opensimModelJNI.ProbeReporter_getProbeStorage(swigCPtr, this), false);
  }

  public Storage updProbeStorage() {
    return new Storage(opensimModelJNI.ProbeReporter_updProbeStorage(swigCPtr, this), false);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.ProbeReporter_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public int begin(SWIGTYPE_p_SimTK__State s) {
    return opensimModelJNI.ProbeReporter_begin(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public int step(SWIGTYPE_p_SimTK__State s, int setNumber) {
    return opensimModelJNI.ProbeReporter_step(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), setNumber);
  }

  public int end(SWIGTYPE_p_SimTK__State s) {
    return opensimModelJNI.ProbeReporter_end(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public int printResults(String aBaseName, String aDir, double aDT, String aExtension) {
    return opensimModelJNI.ProbeReporter_printResults__SWIG_0(swigCPtr, this, aBaseName, aDir, aDT, aExtension);
  }

  public int printResults(String aBaseName, String aDir, double aDT) {
    return opensimModelJNI.ProbeReporter_printResults__SWIG_1(swigCPtr, this, aBaseName, aDir, aDT);
  }

  public int printResults(String aBaseName, String aDir) {
    return opensimModelJNI.ProbeReporter_printResults__SWIG_2(swigCPtr, this, aBaseName, aDir);
  }

  public int printResults(String aBaseName) {
    return opensimModelJNI.ProbeReporter_printResults__SWIG_3(swigCPtr, this, aBaseName);
  }

}
