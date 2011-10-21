/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetBodyScales extends OpenSimObject {
  private long swigCPtr;

  public SetBodyScales(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SetBodyScales_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetBodyScales obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_SetBodyScales(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public SetBodyScales() {
    this(opensimModelJNI.new_SetBodyScales__SWIG_0(), true);
  }

  public SetBodyScales(String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_SetBodyScales__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public SetBodyScales(String aFileName) {
    this(opensimModelJNI.new_SetBodyScales__SWIG_2(aFileName), true);
  }

  public SetBodyScales(SetBodyScales aSet) {
    this(opensimModelJNI.new_SetBodyScales__SWIG_3(SetBodyScales.getCPtr(aSet), aSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SetBodyScales_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setup() {
    opensimModelJNI.SetBodyScales_setup(swigCPtr, this);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetBodyScales_setMemoryOwner(swigCPtr, this, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetBodyScales_getMemoryOwner(swigCPtr, this);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetBodyScales_computeNewCapacity(swigCPtr, this, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetBodyScales_ensureCapacity(swigCPtr, this, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetBodyScales_trim(swigCPtr, this);
  }

  public int getCapacity() {
    return opensimModelJNI.SetBodyScales_getCapacity(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetBodyScales_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetBodyScales_getCapacityIncrement(swigCPtr, this);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetBodyScales_setSize(swigCPtr, this, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetBodyScales_getSize(swigCPtr, this);
  }

  public int getIndex(BodyScale aObject, int aStartIndex) {
    return opensimModelJNI.SetBodyScales_getIndex__SWIG_0(swigCPtr, this, BodyScale.getCPtr(aObject), aObject, aStartIndex);
  }

  public int getIndex(BodyScale aObject) {
    return opensimModelJNI.SetBodyScales_getIndex__SWIG_1(swigCPtr, this, BodyScale.getCPtr(aObject), aObject);
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetBodyScales_getIndex__SWIG_2(swigCPtr, this, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetBodyScales_getIndex__SWIG_3(swigCPtr, this, aName);
  }

  public void getGroupNamesContaining(String aObjectName, ArrayStr rGroupNames) {
    opensimModelJNI.SetBodyScales_getGroupNamesContaining(swigCPtr, this, aObjectName, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public boolean append(BodyScale aObject) {
    return opensimModelJNI.SetBodyScales_append(swigCPtr, this, BodyScale.getCPtr(aObject), aObject);
  }

  public boolean insert(int aIndex, BodyScale aObject) {
    return opensimModelJNI.SetBodyScales_insert(swigCPtr, this, aIndex, BodyScale.getCPtr(aObject), aObject);
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetBodyScales_remove__SWIG_0(swigCPtr, this, aIndex);
  }

  public boolean remove(BodyScale aObject) {
    return opensimModelJNI.SetBodyScales_remove__SWIG_1(swigCPtr, this, BodyScale.getCPtr(aObject), aObject);
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetBodyScales_clearAndDestroy(swigCPtr, this);
  }

  public boolean set(int aIndex, BodyScale aObject, boolean preserveGroups) {
    return opensimModelJNI.SetBodyScales_set__SWIG_0(swigCPtr, this, aIndex, BodyScale.getCPtr(aObject), aObject, preserveGroups);
  }

  public boolean set(int aIndex, BodyScale aObject) {
    return opensimModelJNI.SetBodyScales_set__SWIG_1(swigCPtr, this, aIndex, BodyScale.getCPtr(aObject), aObject);
  }

  public BodyScale get(int aIndex) {
    return new BodyScale(opensimModelJNI.SetBodyScales_get__SWIG_0(swigCPtr, this, aIndex), false);
  }

  public BodyScale get(String aName) {
    return new BodyScale(opensimModelJNI.SetBodyScales_get__SWIG_1(swigCPtr, this, aName), false);
  }

  public boolean contains(String aName) {
    return opensimModelJNI.SetBodyScales_contains(swigCPtr, this, aName);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetBodyScales_getNames(swigCPtr, this, ArrayStr.getCPtr(rNames), rNames);
  }

  public BodyScale getLast() {
    long cPtr = opensimModelJNI.SetBodyScales_getLast(swigCPtr, this);
    return (cPtr == 0) ? null : new BodyScale(cPtr, false);
  }

  public int searchBinary(BodyScale aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetBodyScales_searchBinary__SWIG_0(swigCPtr, this, BodyScale.getCPtr(aObject), aObject, aFindFirst, aLo, aHi);
  }

  public int searchBinary(BodyScale aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetBodyScales_searchBinary__SWIG_1(swigCPtr, this, BodyScale.getCPtr(aObject), aObject, aFindFirst, aLo);
  }

  public int searchBinary(BodyScale aObject, boolean aFindFirst) {
    return opensimModelJNI.SetBodyScales_searchBinary__SWIG_2(swigCPtr, this, BodyScale.getCPtr(aObject), aObject, aFindFirst);
  }

  public int searchBinary(BodyScale aObject) {
    return opensimModelJNI.SetBodyScales_searchBinary__SWIG_3(swigCPtr, this, BodyScale.getCPtr(aObject), aObject);
  }

  public int getNumGroups() {
    return opensimModelJNI.SetBodyScales_getNumGroups(swigCPtr, this);
  }

  public void addGroup(String aGroupName) {
    opensimModelJNI.SetBodyScales_addGroup(swigCPtr, this, aGroupName);
  }

  public void removeGroup(String aGroupName) {
    opensimModelJNI.SetBodyScales_removeGroup(swigCPtr, this, aGroupName);
  }

  public void renameGroup(String oldGroupName, String newGroupName) {
    opensimModelJNI.SetBodyScales_renameGroup(swigCPtr, this, oldGroupName, newGroupName);
  }

  public void addObjectToGroup(String aGroupName, String aObjectName) {
    opensimModelJNI.SetBodyScales_addObjectToGroup(swigCPtr, this, aGroupName, aObjectName);
  }

  public void getGroupNames(ArrayStr rGroupNames) {
    opensimModelJNI.SetBodyScales_getGroupNames(swigCPtr, this, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public ObjectGroup getGroup(String aGroupName) {
    long cPtr = opensimModelJNI.SetBodyScales_getGroup__SWIG_0(swigCPtr, this, aGroupName);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

  public ObjectGroup getGroup(int aIndex) {
    long cPtr = opensimModelJNI.SetBodyScales_getGroup__SWIG_1(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

}
