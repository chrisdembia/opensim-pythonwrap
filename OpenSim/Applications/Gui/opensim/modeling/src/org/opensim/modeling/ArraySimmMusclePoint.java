/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ArraySimmMusclePoint {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ArraySimmMusclePoint(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ArraySimmMusclePoint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_ArraySimmMusclePoint(swigCPtr);
    }
    swigCPtr = 0;
  }

  public ArraySimmMusclePoint(SimmMusclePoint aDefaultValue, int aSize, int aCapacity) {
    this(opensimModelJNI.new_ArraySimmMusclePoint__SWIG_0(SimmMusclePoint.getCPtr(aDefaultValue), aSize, aCapacity), true);
  }

  public ArraySimmMusclePoint(SimmMusclePoint aDefaultValue, int aSize) {
    this(opensimModelJNI.new_ArraySimmMusclePoint__SWIG_1(SimmMusclePoint.getCPtr(aDefaultValue), aSize), true);
  }

  public ArraySimmMusclePoint(SimmMusclePoint aDefaultValue) {
    this(opensimModelJNI.new_ArraySimmMusclePoint__SWIG_2(SimmMusclePoint.getCPtr(aDefaultValue)), true);
  }

  public ArraySimmMusclePoint() {
    this(opensimModelJNI.new_ArraySimmMusclePoint__SWIG_3(), true);
  }

  public ArraySimmMusclePoint(ArraySimmMusclePoint aArray) {
    this(opensimModelJNI.new_ArraySimmMusclePoint__SWIG_4(ArraySimmMusclePoint.getCPtr(aArray)), true);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.ArraySimmMusclePoint_computeNewCapacity(swigCPtr, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.ArraySimmMusclePoint_ensureCapacity(swigCPtr, aCapacity);
  }

  public void trim() {
    opensimModelJNI.ArraySimmMusclePoint_trim(swigCPtr);
  }

  public int getCapacity() {
    return opensimModelJNI.ArraySimmMusclePoint_getCapacity(swigCPtr);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.ArraySimmMusclePoint_setCapacityIncrement(swigCPtr, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.ArraySimmMusclePoint_getCapacityIncrement(swigCPtr);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.ArraySimmMusclePoint_setSize(swigCPtr, aSize);
  }

  public int getSize() {
    return opensimModelJNI.ArraySimmMusclePoint_getSize(swigCPtr);
  }

  public int append(SimmMusclePoint aValue) {
    return opensimModelJNI.ArraySimmMusclePoint_append__SWIG_0(swigCPtr, SimmMusclePoint.getCPtr(aValue));
  }

  public int append(ArraySimmMusclePoint aArray) {
    return opensimModelJNI.ArraySimmMusclePoint_append__SWIG_1(swigCPtr, ArraySimmMusclePoint.getCPtr(aArray));
  }

  public int append(int aSize, SWIGTYPE_p_p_OpenSim__SimmMusclePoint aArray) {
    return opensimModelJNI.ArraySimmMusclePoint_append__SWIG_2(swigCPtr, aSize, SWIGTYPE_p_p_OpenSim__SimmMusclePoint.getCPtr(aArray));
  }

  public int insert(int aIndex, SimmMusclePoint aValue) {
    return opensimModelJNI.ArraySimmMusclePoint_insert(swigCPtr, aIndex, SimmMusclePoint.getCPtr(aValue));
  }

  public int remove(int aIndex) {
    return opensimModelJNI.ArraySimmMusclePoint_remove(swigCPtr, aIndex);
  }

  public void set(int aIndex, SimmMusclePoint aValue) {
    opensimModelJNI.ArraySimmMusclePoint_set(swigCPtr, aIndex, SimmMusclePoint.getCPtr(aValue));
  }

  public SWIGTYPE_p_p_OpenSim__SimmMusclePoint get() {
    long cPtr = opensimModelJNI.ArraySimmMusclePoint_get__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_p_OpenSim__SimmMusclePoint(cPtr, false);
  }

  public SimmMusclePoint get(int aIndex) {
    long cPtr = opensimModelJNI.ArraySimmMusclePoint_get__SWIG_1(swigCPtr, aIndex);
    return (cPtr == 0) ? null : new SimmMusclePoint(cPtr, false);
  }

  public SimmMusclePoint getitem(int index) {
    long cPtr = opensimModelJNI.ArraySimmMusclePoint_getitem(swigCPtr, index);
    return (cPtr == 0) ? null : new SimmMusclePoint(cPtr, false);
  }

  public void setitem(int index, SimmMusclePoint val) {
    opensimModelJNI.ArraySimmMusclePoint_setitem(swigCPtr, index, SimmMusclePoint.getCPtr(val));
  }

  public SimmMusclePoint getLast() {
    long cPtr = opensimModelJNI.ArraySimmMusclePoint_getLast(swigCPtr);
    return (cPtr == 0) ? null : new SimmMusclePoint(cPtr, false);
  }

  public int findIndex(SimmMusclePoint aValue) {
    return opensimModelJNI.ArraySimmMusclePoint_findIndex(swigCPtr, SimmMusclePoint.getCPtr(aValue));
  }

  public int rfindIndex(SimmMusclePoint aValue) {
    return opensimModelJNI.ArraySimmMusclePoint_rfindIndex(swigCPtr, SimmMusclePoint.getCPtr(aValue));
  }

  public int searchBinary(SimmMusclePoint aValue, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.ArraySimmMusclePoint_searchBinary__SWIG_0(swigCPtr, SimmMusclePoint.getCPtr(aValue), aFindFirst, aLo, aHi);
  }

  public int searchBinary(SimmMusclePoint aValue, boolean aFindFirst, int aLo) {
    return opensimModelJNI.ArraySimmMusclePoint_searchBinary__SWIG_1(swigCPtr, SimmMusclePoint.getCPtr(aValue), aFindFirst, aLo);
  }

  public int searchBinary(SimmMusclePoint aValue, boolean aFindFirst) {
    return opensimModelJNI.ArraySimmMusclePoint_searchBinary__SWIG_2(swigCPtr, SimmMusclePoint.getCPtr(aValue), aFindFirst);
  }

  public int searchBinary(SimmMusclePoint aValue) {
    return opensimModelJNI.ArraySimmMusclePoint_searchBinary__SWIG_3(swigCPtr, SimmMusclePoint.getCPtr(aValue));
  }

}
