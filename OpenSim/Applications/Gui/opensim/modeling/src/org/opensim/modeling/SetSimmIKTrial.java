/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetSimmIKTrial extends OpenSimObject {
  private long swigCPtr;

  public SetSimmIKTrial(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetSimmIKTrial obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SetSimmIKTrial(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SetSimmIKTrial() {
    this(opensimModelJNI.new_SetSimmIKTrial__SWIG_0(), true);
  }

  public SetSimmIKTrial(String aFileName) {
    this(opensimModelJNI.new_SetSimmIKTrial__SWIG_1(aFileName), true);
  }

  public SetSimmIKTrial(SetSimmIKTrial aSet) {
    this(opensimModelJNI.new_SetSimmIKTrial__SWIG_2(SetSimmIKTrial.getCPtr(aSet)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SetSimmIKTrial_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetSimmIKTrial_setMemoryOwner(swigCPtr, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetSimmIKTrial_getMemoryOwner(swigCPtr);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetSimmIKTrial_computeNewCapacity(swigCPtr, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetSimmIKTrial_ensureCapacity(swigCPtr, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetSimmIKTrial_trim(swigCPtr);
  }

  public int getCapacity() {
    return opensimModelJNI.SetSimmIKTrial_getCapacity(swigCPtr);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetSimmIKTrial_setCapacityIncrement(swigCPtr, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetSimmIKTrial_getCapacityIncrement(swigCPtr);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetSimmIKTrial_setSize(swigCPtr, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetSimmIKTrial_getSize(swigCPtr);
  }

  public int getIndex(SimmIKTrial aObject, int aStartIndex) {
    return opensimModelJNI.SetSimmIKTrial_getIndex__SWIG_0(swigCPtr, SimmIKTrial.getCPtr(aObject), aStartIndex);
  }

  public int getIndex(SimmIKTrial aObject) {
    return opensimModelJNI.SetSimmIKTrial_getIndex__SWIG_1(swigCPtr, SimmIKTrial.getCPtr(aObject));
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetSimmIKTrial_getIndex__SWIG_2(swigCPtr, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetSimmIKTrial_getIndex__SWIG_3(swigCPtr, aName);
  }

  public boolean append(SimmIKTrial aObject) {
    return opensimModelJNI.SetSimmIKTrial_append__SWIG_0(swigCPtr, SimmIKTrial.getCPtr(aObject));
  }

  public boolean append(SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmIKTrial_t aArray) {
    return opensimModelJNI.SetSimmIKTrial_append__SWIG_1(swigCPtr, SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmIKTrial_t.getCPtr(aArray));
  }

  public boolean insert(int aIndex, SimmIKTrial aObject) {
    return opensimModelJNI.SetSimmIKTrial_insert(swigCPtr, aIndex, SimmIKTrial.getCPtr(aObject));
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetSimmIKTrial_remove__SWIG_0(swigCPtr, aIndex);
  }

  public boolean remove(SimmIKTrial aObject) {
    return opensimModelJNI.SetSimmIKTrial_remove__SWIG_1(swigCPtr, SimmIKTrial.getCPtr(aObject));
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetSimmIKTrial_clearAndDestroy(swigCPtr);
  }

  public boolean set(int aIndex, SimmIKTrial aObject) {
    return opensimModelJNI.SetSimmIKTrial_set(swigCPtr, aIndex, SimmIKTrial.getCPtr(aObject));
  }

  public SimmIKTrial get(int aIndex) {
    long cPtr = opensimModelJNI.SetSimmIKTrial_get__SWIG_0(swigCPtr, aIndex);
    return (cPtr == 0) ? null : new SimmIKTrial(cPtr, false);
  }

  public SimmIKTrial get(String aName) {
    long cPtr = opensimModelJNI.SetSimmIKTrial_get__SWIG_1(swigCPtr, aName);
    return (cPtr == 0) ? null : new SimmIKTrial(cPtr, false);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetSimmIKTrial_getNames(swigCPtr, ArrayStr.getCPtr(rNames));
  }

  public SimmIKTrial getLast() {
    long cPtr = opensimModelJNI.SetSimmIKTrial_getLast(swigCPtr);
    return (cPtr == 0) ? null : new SimmIKTrial(cPtr, false);
  }

  public int searchBinary(SimmIKTrial aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetSimmIKTrial_searchBinary__SWIG_0(swigCPtr, SimmIKTrial.getCPtr(aObject), aFindFirst, aLo, aHi);
  }

  public int searchBinary(SimmIKTrial aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetSimmIKTrial_searchBinary__SWIG_1(swigCPtr, SimmIKTrial.getCPtr(aObject), aFindFirst, aLo);
  }

  public int searchBinary(SimmIKTrial aObject, boolean aFindFirst) {
    return opensimModelJNI.SetSimmIKTrial_searchBinary__SWIG_2(swigCPtr, SimmIKTrial.getCPtr(aObject), aFindFirst);
  }

  public int searchBinary(SimmIKTrial aObject) {
    return opensimModelJNI.SetSimmIKTrial_searchBinary__SWIG_3(swigCPtr, SimmIKTrial.getCPtr(aObject));
  }

}
