/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class ArrayPtrsObj {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ArrayPtrsObj(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ArrayPtrsObj obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_ArrayPtrsObj(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ArrayPtrsObj(int aCapacity) {
    this(opensimModelJNI.new_ArrayPtrsObj__SWIG_0(aCapacity), true);
  }

  public ArrayPtrsObj() {
    this(opensimModelJNI.new_ArrayPtrsObj__SWIG_1(), true);
  }

  public ArrayPtrsObj(ArrayPtrsObj aArray) {
    this(opensimModelJNI.new_ArrayPtrsObj__SWIG_2(ArrayPtrsObj.getCPtr(aArray), aArray), true);
  }

  public void clearAndDestroy() {
    opensimModelJNI.ArrayPtrsObj_clearAndDestroy(swigCPtr, this);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.ArrayPtrsObj_setMemoryOwner(swigCPtr, this, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.ArrayPtrsObj_getMemoryOwner(swigCPtr, this);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.ArrayPtrsObj_computeNewCapacity(swigCPtr, this, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.ArrayPtrsObj_ensureCapacity(swigCPtr, this, aCapacity);
  }

  public void trim() {
    opensimModelJNI.ArrayPtrsObj_trim(swigCPtr, this);
  }

  public int getCapacity() {
    return opensimModelJNI.ArrayPtrsObj_getCapacity(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.ArrayPtrsObj_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.ArrayPtrsObj_getCapacityIncrement(swigCPtr, this);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.ArrayPtrsObj_setSize(swigCPtr, this, aSize);
  }

  public int getSize() {
    return opensimModelJNI.ArrayPtrsObj_getSize(swigCPtr, this);
  }

  public int getIndex(OpenSimObject aObject, int aStartIndex) {
    return opensimModelJNI.ArrayPtrsObj_getIndex__SWIG_0(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject, aStartIndex);
  }

  public int getIndex(OpenSimObject aObject) {
    return opensimModelJNI.ArrayPtrsObj_getIndex__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.ArrayPtrsObj_getIndex__SWIG_2(swigCPtr, this, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.ArrayPtrsObj_getIndex__SWIG_3(swigCPtr, this, aName);
  }

  public boolean append(OpenSimObject aObject) {
    return opensimModelJNI.ArrayPtrsObj_append__SWIG_0(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public boolean append(ArrayPtrsObj aArray) {
    return opensimModelJNI.ArrayPtrsObj_append__SWIG_1(swigCPtr, this, ArrayPtrsObj.getCPtr(aArray), aArray);
  }

  public boolean insert(int aIndex, OpenSimObject aObject) {
    return opensimModelJNI.ArrayPtrsObj_insert(swigCPtr, this, aIndex, OpenSimObject.getCPtr(aObject), aObject);
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.ArrayPtrsObj_remove__SWIG_0(swigCPtr, this, aIndex);
  }

  public boolean remove(OpenSimObject aObject) {
    return opensimModelJNI.ArrayPtrsObj_remove__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public boolean set(int aIndex, OpenSimObject aObject) {
    return opensimModelJNI.ArrayPtrsObj_set(swigCPtr, this, aIndex, OpenSimObject.getCPtr(aObject), aObject);
  }

  public OpenSimObject get(int aIndex) {
    long cPtr = opensimModelJNI.ArrayPtrsObj_get__SWIG_0(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public OpenSimObject get(String aName) {
    long cPtr = opensimModelJNI.ArrayPtrsObj_get__SWIG_1(swigCPtr, this, aName);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public OpenSimObject getLast() {
    long cPtr = opensimModelJNI.ArrayPtrsObj_getLast(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public int searchBinary(OpenSimObject aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.ArrayPtrsObj_searchBinary__SWIG_0(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject, aFindFirst, aLo, aHi);
  }

  public int searchBinary(OpenSimObject aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.ArrayPtrsObj_searchBinary__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject, aFindFirst, aLo);
  }

  public int searchBinary(OpenSimObject aObject, boolean aFindFirst) {
    return opensimModelJNI.ArrayPtrsObj_searchBinary__SWIG_2(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject, aFindFirst);
  }

  public int searchBinary(OpenSimObject aObject) {
    return opensimModelJNI.ArrayPtrsObj_searchBinary__SWIG_3(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}