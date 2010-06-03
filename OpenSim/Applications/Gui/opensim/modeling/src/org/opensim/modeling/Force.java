/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Force extends ModelComponent {
  private long swigCPtr;

  public Force(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Force obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Force(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public void copyData(Force aForce) {
    opensimModelJNI.Force_copyData(swigCPtr, this, Force.getCPtr(aForce), aForce);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Force_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public int getNumStateVariables() {
    return opensimModelJNI.Force_getNumStateVariables(swigCPtr, this);
  }

  public String getStateVariableName(int index) {
    return opensimModelJNI.Force_getStateVariableName(swigCPtr, this, index);
  }

  public double getStateVariable(SWIGTYPE_p_SimTK__State state, int index) {
    return opensimModelJNI.Force_getStateVariable(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), index);
  }

  public void setStateVariable(SWIGTYPE_p_SimTK__State state, int index, double value) {
    opensimModelJNI.Force_setStateVariable(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state), index, value);
  }

  public ArrayStr getRecordLabels() {
    return new ArrayStr(opensimModelJNI.Force_getRecordLabels(swigCPtr, this), true);
  }

  public ArrayDouble getRecordValues(SWIGTYPE_p_SimTK__State state) {
    return new ArrayDouble(opensimModelJNI.Force_getRecordValues(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(state)), true);
  }

  public boolean isDisabled(SWIGTYPE_p_SimTK__State s) {
    return opensimModelJNI.Force_isDisabled(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public void setDisabled(SWIGTYPE_p_SimTK__State s, boolean disabled) {
    opensimModelJNI.Force_setDisabled(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), disabled);
  }

}
