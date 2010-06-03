/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetJoints extends OpenSimObject {
  private long swigCPtr;

  public SetJoints(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetJoints obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SetJoints(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SetJoints() {
    this(opensimModelJNI.new_SetJoints__SWIG_0(), true);
  }

  public SetJoints(String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_SetJoints__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public SetJoints(String aFileName) {
    this(opensimModelJNI.new_SetJoints__SWIG_2(aFileName), true);
  }

  public SetJoints(SetJoints aSet) {
    this(opensimModelJNI.new_SetJoints__SWIG_3(SetJoints.getCPtr(aSet), aSet), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SetJoints_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setup() {
    opensimModelJNI.SetJoints_setup(swigCPtr, this);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetJoints_setMemoryOwner(swigCPtr, this, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetJoints_getMemoryOwner(swigCPtr, this);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetJoints_computeNewCapacity(swigCPtr, this, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetJoints_ensureCapacity(swigCPtr, this, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetJoints_trim(swigCPtr, this);
  }

  public int getCapacity() {
    return opensimModelJNI.SetJoints_getCapacity(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetJoints_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetJoints_getCapacityIncrement(swigCPtr, this);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetJoints_setSize(swigCPtr, this, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetJoints_getSize(swigCPtr, this);
  }

  public int getIndex(Joint aObject, int aStartIndex) {
    return opensimModelJNI.SetJoints_getIndex__SWIG_0(swigCPtr, this, Joint.getCPtr(aObject), aObject, aStartIndex);
  }

  public int getIndex(Joint aObject) {
    return opensimModelJNI.SetJoints_getIndex__SWIG_1(swigCPtr, this, Joint.getCPtr(aObject), aObject);
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetJoints_getIndex__SWIG_2(swigCPtr, this, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetJoints_getIndex__SWIG_3(swigCPtr, this, aName);
  }

  public void getGroupNamesContaining(String aObjectName, ArrayStr rGroupNames) {
    opensimModelJNI.SetJoints_getGroupNamesContaining(swigCPtr, this, aObjectName, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public boolean append(Joint aObject) {
    return opensimModelJNI.SetJoints_append__SWIG_0(swigCPtr, this, Joint.getCPtr(aObject), aObject);
  }

  public boolean insert(int aIndex, Joint aObject) {
    return opensimModelJNI.SetJoints_insert(swigCPtr, this, aIndex, Joint.getCPtr(aObject), aObject);
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetJoints_remove__SWIG_0(swigCPtr, this, aIndex);
  }

  public boolean remove(Joint aObject) {
    return opensimModelJNI.SetJoints_remove__SWIG_1(swigCPtr, this, Joint.getCPtr(aObject), aObject);
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetJoints_clearAndDestroy(swigCPtr, this);
  }

  public boolean set(int aIndex, Joint aObject, boolean preserveGroups) {
    return opensimModelJNI.SetJoints_set__SWIG_0(swigCPtr, this, aIndex, Joint.getCPtr(aObject), aObject, preserveGroups);
  }

  public boolean set(int aIndex, Joint aObject) {
    return opensimModelJNI.SetJoints_set__SWIG_1(swigCPtr, this, aIndex, Joint.getCPtr(aObject), aObject);
  }

  public Joint get(int aIndex) {
    return new Joint(opensimModelJNI.SetJoints_get__SWIG_0(swigCPtr, this, aIndex), false);
  }

  public Joint get(String aName) {
    return new Joint(opensimModelJNI.SetJoints_get__SWIG_1(swigCPtr, this, aName), false);
  }

  public boolean contains(String aName) {
    return opensimModelJNI.SetJoints_contains(swigCPtr, this, aName);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetJoints_getNames(swigCPtr, this, ArrayStr.getCPtr(rNames), rNames);
  }

  public Joint getLast() {
    long cPtr = opensimModelJNI.SetJoints_getLast(swigCPtr, this);
    return (cPtr == 0) ? null : new Joint(cPtr, false);
  }

  public int searchBinary(Joint aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetJoints_searchBinary__SWIG_0(swigCPtr, this, Joint.getCPtr(aObject), aObject, aFindFirst, aLo, aHi);
  }

  public int searchBinary(Joint aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetJoints_searchBinary__SWIG_1(swigCPtr, this, Joint.getCPtr(aObject), aObject, aFindFirst, aLo);
  }

  public int searchBinary(Joint aObject, boolean aFindFirst) {
    return opensimModelJNI.SetJoints_searchBinary__SWIG_2(swigCPtr, this, Joint.getCPtr(aObject), aObject, aFindFirst);
  }

  public int searchBinary(Joint aObject) {
    return opensimModelJNI.SetJoints_searchBinary__SWIG_3(swigCPtr, this, Joint.getCPtr(aObject), aObject);
  }

  public int getNumGroups() {
    return opensimModelJNI.SetJoints_getNumGroups(swigCPtr, this);
  }

  public void addGroup(String aGroupName) {
    opensimModelJNI.SetJoints_addGroup(swigCPtr, this, aGroupName);
  }

  public void removeGroup(String aGroupName) {
    opensimModelJNI.SetJoints_removeGroup(swigCPtr, this, aGroupName);
  }

  public void renameGroup(String oldGroupName, String newGroupName) {
    opensimModelJNI.SetJoints_renameGroup(swigCPtr, this, oldGroupName, newGroupName);
  }

  public void addObjectToGroup(String aGroupName, String aObjectName) {
    opensimModelJNI.SetJoints_addObjectToGroup(swigCPtr, this, aGroupName, aObjectName);
  }

  public void getGroupNames(ArrayStr rGroupNames) {
    opensimModelJNI.SetJoints_getGroupNames(swigCPtr, this, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public ObjectGroup getGroup(String aGroupName) {
    long cPtr = opensimModelJNI.SetJoints_getGroup__SWIG_0(swigCPtr, this, aGroupName);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

  public ObjectGroup getGroup(int aIndex) {
    long cPtr = opensimModelJNI.SetJoints_getGroup__SWIG_1(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

}
