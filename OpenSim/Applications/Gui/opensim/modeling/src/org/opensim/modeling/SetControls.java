/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetControls extends OpenSimObject {
  private long swigCPtr;

  public SetControls(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetControls obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SetControls(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SetControls() {
    this(opensimModelJNI.new_SetControls__SWIG_0(), true);
  }

  public SetControls(String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_SetControls__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public SetControls(String aFileName) {
    this(opensimModelJNI.new_SetControls__SWIG_2(aFileName), true);
  }

  public SetControls(SetControls aSet) {
    this(opensimModelJNI.new_SetControls__SWIG_3(SetControls.getCPtr(aSet), aSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SetControls_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setup() {
    opensimModelJNI.SetControls_setup(swigCPtr, this);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetControls_setMemoryOwner(swigCPtr, this, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetControls_getMemoryOwner(swigCPtr, this);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetControls_computeNewCapacity(swigCPtr, this, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetControls_ensureCapacity(swigCPtr, this, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetControls_trim(swigCPtr, this);
  }

  public int getCapacity() {
    return opensimModelJNI.SetControls_getCapacity(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetControls_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetControls_getCapacityIncrement(swigCPtr, this);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetControls_setSize(swigCPtr, this, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetControls_getSize(swigCPtr, this);
  }

  public int getIndex(Control aObject, int aStartIndex) {
    return opensimModelJNI.SetControls_getIndex__SWIG_0(swigCPtr, this, Control.getCPtr(aObject), aObject, aStartIndex);
  }

  public int getIndex(Control aObject) {
    return opensimModelJNI.SetControls_getIndex__SWIG_1(swigCPtr, this, Control.getCPtr(aObject), aObject);
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetControls_getIndex__SWIG_2(swigCPtr, this, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetControls_getIndex__SWIG_3(swigCPtr, this, aName);
  }

  public boolean append(Control aObject) {
    return opensimModelJNI.SetControls_append__SWIG_0(swigCPtr, this, Control.getCPtr(aObject), aObject);
  }

  public boolean append(SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__Control_t aArray) {
    return opensimModelJNI.SetControls_append__SWIG_1(swigCPtr, this, SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__Control_t.getCPtr(aArray));
  }

  public boolean insert(int aIndex, Control aObject) {
    return opensimModelJNI.SetControls_insert(swigCPtr, this, aIndex, Control.getCPtr(aObject), aObject);
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetControls_remove__SWIG_0(swigCPtr, this, aIndex);
  }

  public boolean remove(Control aObject) {
    return opensimModelJNI.SetControls_remove__SWIG_1(swigCPtr, this, Control.getCPtr(aObject), aObject);
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetControls_clearAndDestroy(swigCPtr, this);
  }

  public boolean set(int aIndex, Control aObject) {
    return opensimModelJNI.SetControls_set(swigCPtr, this, aIndex, Control.getCPtr(aObject), aObject);
  }

  public Control get(int aIndex) {
    long cPtr = opensimModelJNI.SetControls_get__SWIG_0(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new Control(cPtr, false);
  }

  public Control get(String aName) {
    long cPtr = opensimModelJNI.SetControls_get__SWIG_1(swigCPtr, this, aName);
    return (cPtr == 0) ? null : new Control(cPtr, false);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetControls_getNames(swigCPtr, this, ArrayStr.getCPtr(rNames), rNames);
  }

  public Control getLast() {
    long cPtr = opensimModelJNI.SetControls_getLast(swigCPtr, this);
    return (cPtr == 0) ? null : new Control(cPtr, false);
  }

  public int searchBinary(Control aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetControls_searchBinary__SWIG_0(swigCPtr, this, Control.getCPtr(aObject), aObject, aFindFirst, aLo, aHi);
  }

  public int searchBinary(Control aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetControls_searchBinary__SWIG_1(swigCPtr, this, Control.getCPtr(aObject), aObject, aFindFirst, aLo);
  }

  public int searchBinary(Control aObject, boolean aFindFirst) {
    return opensimModelJNI.SetControls_searchBinary__SWIG_2(swigCPtr, this, Control.getCPtr(aObject), aObject, aFindFirst);
  }

  public int searchBinary(Control aObject) {
    return opensimModelJNI.SetControls_searchBinary__SWIG_3(swigCPtr, this, Control.getCPtr(aObject), aObject);
  }

  public void addGroup(SWIGTYPE_p_std__string aGroupName) {
    opensimModelJNI.SetControls_addGroup(swigCPtr, this, SWIGTYPE_p_std__string.getCPtr(aGroupName));
  }

  public void addObjectToGroup(SWIGTYPE_p_std__string aGroupName, SWIGTYPE_p_std__string aObjectName) {
    opensimModelJNI.SetControls_addObjectToGroup(swigCPtr, this, SWIGTYPE_p_std__string.getCPtr(aGroupName), SWIGTYPE_p_std__string.getCPtr(aObjectName));
  }

}
