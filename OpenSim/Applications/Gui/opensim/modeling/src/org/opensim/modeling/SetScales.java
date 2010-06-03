/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetScales extends OpenSimObject {
  private long swigCPtr;

  public SetScales(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetScales obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SetScales(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SetScales() {
    this(opensimModelJNI.new_SetScales__SWIG_0(), true);
  }

  public SetScales(String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_SetScales__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public SetScales(String aFileName) {
    this(opensimModelJNI.new_SetScales__SWIG_2(aFileName), true);
  }

  public SetScales(SetScales aSet) {
    this(opensimModelJNI.new_SetScales__SWIG_3(SetScales.getCPtr(aSet), aSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SetScales_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setup() {
    opensimModelJNI.SetScales_setup(swigCPtr, this);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetScales_setMemoryOwner(swigCPtr, this, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetScales_getMemoryOwner(swigCPtr, this);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetScales_computeNewCapacity(swigCPtr, this, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetScales_ensureCapacity(swigCPtr, this, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetScales_trim(swigCPtr, this);
  }

  public int getCapacity() {
    return opensimModelJNI.SetScales_getCapacity(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetScales_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetScales_getCapacityIncrement(swigCPtr, this);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetScales_setSize(swigCPtr, this, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetScales_getSize(swigCPtr, this);
  }

  public int getIndex(Scale aObject, int aStartIndex) {
    return opensimModelJNI.SetScales_getIndex__SWIG_0(swigCPtr, this, Scale.getCPtr(aObject), aObject, aStartIndex);
  }

  public int getIndex(Scale aObject) {
    return opensimModelJNI.SetScales_getIndex__SWIG_1(swigCPtr, this, Scale.getCPtr(aObject), aObject);
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetScales_getIndex__SWIG_2(swigCPtr, this, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetScales_getIndex__SWIG_3(swigCPtr, this, aName);
  }

  public void getGroupNamesContaining(String aObjectName, ArrayStr rGroupNames) {
    opensimModelJNI.SetScales_getGroupNamesContaining(swigCPtr, this, aObjectName, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public boolean append(Scale aObject) {
    return opensimModelJNI.SetScales_append__SWIG_0(swigCPtr, this, Scale.getCPtr(aObject), aObject);
  }

  public boolean insert(int aIndex, Scale aObject) {
    return opensimModelJNI.SetScales_insert(swigCPtr, this, aIndex, Scale.getCPtr(aObject), aObject);
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetScales_remove__SWIG_0(swigCPtr, this, aIndex);
  }

  public boolean remove(Scale aObject) {
    return opensimModelJNI.SetScales_remove__SWIG_1(swigCPtr, this, Scale.getCPtr(aObject), aObject);
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetScales_clearAndDestroy(swigCPtr, this);
  }

  public boolean set(int aIndex, Scale aObject, boolean preserveGroups) {
    return opensimModelJNI.SetScales_set__SWIG_0(swigCPtr, this, aIndex, Scale.getCPtr(aObject), aObject, preserveGroups);
  }

  public boolean set(int aIndex, Scale aObject) {
    return opensimModelJNI.SetScales_set__SWIG_1(swigCPtr, this, aIndex, Scale.getCPtr(aObject), aObject);
  }

  public Scale get(int aIndex) {
    return new Scale(opensimModelJNI.SetScales_get__SWIG_0(swigCPtr, this, aIndex), false);
  }

  public Scale get(String aName) {
    return new Scale(opensimModelJNI.SetScales_get__SWIG_1(swigCPtr, this, aName), false);
  }

  public boolean contains(String aName) {
    return opensimModelJNI.SetScales_contains(swigCPtr, this, aName);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetScales_getNames(swigCPtr, this, ArrayStr.getCPtr(rNames), rNames);
  }

  public Scale getLast() {
    long cPtr = opensimModelJNI.SetScales_getLast(swigCPtr, this);
    return (cPtr == 0) ? null : new Scale(cPtr, false);
  }

  public int searchBinary(Scale aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetScales_searchBinary__SWIG_0(swigCPtr, this, Scale.getCPtr(aObject), aObject, aFindFirst, aLo, aHi);
  }

  public int searchBinary(Scale aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetScales_searchBinary__SWIG_1(swigCPtr, this, Scale.getCPtr(aObject), aObject, aFindFirst, aLo);
  }

  public int searchBinary(Scale aObject, boolean aFindFirst) {
    return opensimModelJNI.SetScales_searchBinary__SWIG_2(swigCPtr, this, Scale.getCPtr(aObject), aObject, aFindFirst);
  }

  public int searchBinary(Scale aObject) {
    return opensimModelJNI.SetScales_searchBinary__SWIG_3(swigCPtr, this, Scale.getCPtr(aObject), aObject);
  }

  public int getNumGroups() {
    return opensimModelJNI.SetScales_getNumGroups(swigCPtr, this);
  }

  public void addGroup(String aGroupName) {
    opensimModelJNI.SetScales_addGroup(swigCPtr, this, aGroupName);
  }

  public void removeGroup(String aGroupName) {
    opensimModelJNI.SetScales_removeGroup(swigCPtr, this, aGroupName);
  }

  public void renameGroup(String oldGroupName, String newGroupName) {
    opensimModelJNI.SetScales_renameGroup(swigCPtr, this, oldGroupName, newGroupName);
  }

  public void addObjectToGroup(String aGroupName, String aObjectName) {
    opensimModelJNI.SetScales_addObjectToGroup(swigCPtr, this, aGroupName, aObjectName);
  }

  public void getGroupNames(ArrayStr rGroupNames) {
    opensimModelJNI.SetScales_getGroupNames(swigCPtr, this, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public ObjectGroup getGroup(String aGroupName) {
    long cPtr = opensimModelJNI.SetScales_getGroup__SWIG_0(swigCPtr, this, aGroupName);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

  public ObjectGroup getGroup(int aIndex) {
    long cPtr = opensimModelJNI.SetScales_getGroup__SWIG_1(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

}
