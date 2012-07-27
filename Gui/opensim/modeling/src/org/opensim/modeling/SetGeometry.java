/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetGeometry extends OpenSimObject {
  private long swigCPtr;

  public SetGeometry(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SetGeometry_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetGeometry obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_SetGeometry(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static SetGeometry safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.SetGeometry_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new SetGeometry(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.SetGeometry_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.SetGeometry_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.SetGeometry_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new SetGeometry(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.SetGeometry_getConcreteClassName(swigCPtr, this);
  }

  public SetGeometry() {
    this(opensimModelJNI.new_SetGeometry__SWIG_0(), true);
  }

  public SetGeometry(String aFileName, boolean aUpdateFromXMLNode) {
    this(opensimModelJNI.new_SetGeometry__SWIG_1(aFileName, aUpdateFromXMLNode), true);
  }

  public SetGeometry(String aFileName) {
    this(opensimModelJNI.new_SetGeometry__SWIG_2(aFileName), true);
  }

  public SetGeometry(SetGeometry aSet) {
    this(opensimModelJNI.new_SetGeometry__SWIG_3(SetGeometry.getCPtr(aSet), aSet), true);
  }

  public void setupGroups() {
    opensimModelJNI.SetGeometry_setupGroups(swigCPtr, this);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetGeometry_setMemoryOwner(swigCPtr, this, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetGeometry_getMemoryOwner(swigCPtr, this);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetGeometry_computeNewCapacity(swigCPtr, this, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetGeometry_ensureCapacity(swigCPtr, this, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetGeometry_trim(swigCPtr, this);
  }

  public int getCapacity() {
    return opensimModelJNI.SetGeometry_getCapacity(swigCPtr, this);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetGeometry_setCapacityIncrement(swigCPtr, this, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetGeometry_getCapacityIncrement(swigCPtr, this);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetGeometry_setSize(swigCPtr, this, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetGeometry_getSize(swigCPtr, this);
  }

  public int getIndex(DisplayGeometry aObject, int aStartIndex) {
    return opensimModelJNI.SetGeometry_getIndex__SWIG_0(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject, aStartIndex);
  }

  public int getIndex(DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_getIndex__SWIG_1(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetGeometry_getIndex__SWIG_2(swigCPtr, this, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetGeometry_getIndex__SWIG_3(swigCPtr, this, aName);
  }

  public void getGroupNamesContaining(String aObjectName, ArrayStr rGroupNames) {
    opensimModelJNI.SetGeometry_getGroupNamesContaining(swigCPtr, this, aObjectName, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public boolean append(DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_append(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public boolean cloneAndAppend(DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_cloneAndAppend(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public boolean insert(int aIndex, DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_insert(swigCPtr, this, aIndex, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetGeometry_remove__SWIG_0(swigCPtr, this, aIndex);
  }

  public boolean remove(DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_remove__SWIG_1(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetGeometry_clearAndDestroy(swigCPtr, this);
  }

  public boolean set(int aIndex, DisplayGeometry aObject, boolean preserveGroups) {
    return opensimModelJNI.SetGeometry_set__SWIG_0(swigCPtr, this, aIndex, DisplayGeometry.getCPtr(aObject), aObject, preserveGroups);
  }

  public boolean set(int aIndex, DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_set__SWIG_1(swigCPtr, this, aIndex, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public DisplayGeometry get(int aIndex) {
    return new DisplayGeometry(opensimModelJNI.SetGeometry_get__SWIG_0(swigCPtr, this, aIndex), false);
  }

  public DisplayGeometry get(String aName) {
    return new DisplayGeometry(opensimModelJNI.SetGeometry_get__SWIG_1(swigCPtr, this, aName), false);
  }

  public boolean contains(String aName) {
    return opensimModelJNI.SetGeometry_contains(swigCPtr, this, aName);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetGeometry_getNames(swigCPtr, this, ArrayStr.getCPtr(rNames), rNames);
  }

  public DisplayGeometry getLast() {
    long cPtr = opensimModelJNI.SetGeometry_getLast(swigCPtr, this);
    return (cPtr == 0) ? null : new DisplayGeometry(cPtr, false);
  }

  public int searchBinary(DisplayGeometry aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetGeometry_searchBinary__SWIG_0(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject, aFindFirst, aLo, aHi);
  }

  public int searchBinary(DisplayGeometry aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetGeometry_searchBinary__SWIG_1(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject, aFindFirst, aLo);
  }

  public int searchBinary(DisplayGeometry aObject, boolean aFindFirst) {
    return opensimModelJNI.SetGeometry_searchBinary__SWIG_2(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject, aFindFirst);
  }

  public int searchBinary(DisplayGeometry aObject) {
    return opensimModelJNI.SetGeometry_searchBinary__SWIG_3(swigCPtr, this, DisplayGeometry.getCPtr(aObject), aObject);
  }

  public int getNumGroups() {
    return opensimModelJNI.SetGeometry_getNumGroups(swigCPtr, this);
  }

  public void addGroup(String aGroupName) {
    opensimModelJNI.SetGeometry_addGroup(swigCPtr, this, aGroupName);
  }

  public void removeGroup(String aGroupName) {
    opensimModelJNI.SetGeometry_removeGroup(swigCPtr, this, aGroupName);
  }

  public void renameGroup(String oldGroupName, String newGroupName) {
    opensimModelJNI.SetGeometry_renameGroup(swigCPtr, this, oldGroupName, newGroupName);
  }

  public void addObjectToGroup(String aGroupName, String aObjectName) {
    opensimModelJNI.SetGeometry_addObjectToGroup(swigCPtr, this, aGroupName, aObjectName);
  }

  public void getGroupNames(ArrayStr rGroupNames) {
    opensimModelJNI.SetGeometry_getGroupNames(swigCPtr, this, ArrayStr.getCPtr(rGroupNames), rGroupNames);
  }

  public ObjectGroup getGroup(String aGroupName) {
    long cPtr = opensimModelJNI.SetGeometry_getGroup__SWIG_0(swigCPtr, this, aGroupName);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

  public ObjectGroup getGroup(int aIndex) {
    long cPtr = opensimModelJNI.SetGeometry_getGroup__SWIG_1(swigCPtr, this, aIndex);
    return (cPtr == 0) ? null : new ObjectGroup(cPtr, false);
  }

}
