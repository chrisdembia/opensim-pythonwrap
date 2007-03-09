/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Integrand extends OpenSimObject {
  private long swigCPtr;

  public Integrand(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Integrand obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Integrand(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public int getSize() {
    return opensimModelJNI.Integrand_getSize(swigCPtr);
  }

  public void setInitialStates(double ti, double[] yi) {
    opensimModelJNI.Integrand_setInitialStates(swigCPtr, ti, yi);
  }

  public void getInitialStates(double[] yi) {
    opensimModelJNI.Integrand_getInitialStates(swigCPtr, yi);
  }

  public void compute(double t, double[] y, double[] dydt) {
    opensimModelJNI.Integrand_compute(swigCPtr, t, y, dydt);
  }

  public void computeJacobian(double t, double[] y, SWIGTYPE_p_double dydtdy) {
    opensimModelJNI.Integrand_computeJacobian(swigCPtr, t, y, SWIGTYPE_p_double.getCPtr(dydtdy));
  }

  public void initialize(int step, SWIGTYPE_p_double dt, double ti, double tf, double[] y) {
    opensimModelJNI.Integrand_initialize(swigCPtr, step, SWIGTYPE_p_double.getCPtr(dt), ti, tf, y);
  }

  public void processAfterStep(int step, SWIGTYPE_p_double dt, double t, double[] y) {
    opensimModelJNI.Integrand_processAfterStep(swigCPtr, step, SWIGTYPE_p_double.getCPtr(dt), t, y);
  }

  public void finalize(int step, double t, double[] y) {
    opensimModelJNI.Integrand_finalize(swigCPtr, step, t, y);
  }

}
