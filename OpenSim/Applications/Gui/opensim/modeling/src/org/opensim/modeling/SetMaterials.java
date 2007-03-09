/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SetMaterials extends OpenSimObject {
  private long swigCPtr;

  public SetMaterials(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SetMaterials obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SetMaterials(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SetMaterials() {
    this(opensimModelJNI.new_SetMaterials__SWIG_0(), true);
  }

  public SetMaterials(String aFileName) {
    this(opensimModelJNI.new_SetMaterials__SWIG_1(aFileName), true);
  }

  public SetMaterials(SetMaterials aSet) {
    this(opensimModelJNI.new_SetMaterials__SWIG_2(SetMaterials.getCPtr(aSet)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SetMaterials_copy(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void setMemoryOwner(boolean aTrueFalse) {
    opensimModelJNI.SetMaterials_setMemoryOwner(swigCPtr, aTrueFalse);
  }

  public boolean getMemoryOwner() {
    return opensimModelJNI.SetMaterials_getMemoryOwner(swigCPtr);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return opensimModelJNI.SetMaterials_computeNewCapacity(swigCPtr, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return opensimModelJNI.SetMaterials_ensureCapacity(swigCPtr, aCapacity);
  }

  public void trim() {
    opensimModelJNI.SetMaterials_trim(swigCPtr);
  }

  public int getCapacity() {
    return opensimModelJNI.SetMaterials_getCapacity(swigCPtr);
  }

  public void setCapacityIncrement(int aIncrement) {
    opensimModelJNI.SetMaterials_setCapacityIncrement(swigCPtr, aIncrement);
  }

  public int getCapacityIncrement() {
    return opensimModelJNI.SetMaterials_getCapacityIncrement(swigCPtr);
  }

  public boolean setSize(int aSize) {
    return opensimModelJNI.SetMaterials_setSize(swigCPtr, aSize);
  }

  public int getSize() {
    return opensimModelJNI.SetMaterials_getSize(swigCPtr);
  }

  public int getIndex(Material aObject, int aStartIndex) {
    return opensimModelJNI.SetMaterials_getIndex__SWIG_0(swigCPtr, Material.getCPtr(aObject), aStartIndex);
  }

  public int getIndex(Material aObject) {
    return opensimModelJNI.SetMaterials_getIndex__SWIG_1(swigCPtr, Material.getCPtr(aObject));
  }

  public int getIndex(String aName, int aStartIndex) {
    return opensimModelJNI.SetMaterials_getIndex__SWIG_2(swigCPtr, aName, aStartIndex);
  }

  public int getIndex(String aName) {
    return opensimModelJNI.SetMaterials_getIndex__SWIG_3(swigCPtr, aName);
  }

  public boolean append(Material aObject) {
    return opensimModelJNI.SetMaterials_append__SWIG_0(swigCPtr, Material.getCPtr(aObject));
  }

  public boolean append(SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__Material_t aArray) {
    return opensimModelJNI.SetMaterials_append__SWIG_1(swigCPtr, SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__Material_t.getCPtr(aArray));
  }

  public boolean insert(int aIndex, Material aObject) {
    return opensimModelJNI.SetMaterials_insert(swigCPtr, aIndex, Material.getCPtr(aObject));
  }

  public boolean remove(int aIndex) {
    return opensimModelJNI.SetMaterials_remove__SWIG_0(swigCPtr, aIndex);
  }

  public boolean remove(Material aObject) {
    return opensimModelJNI.SetMaterials_remove__SWIG_1(swigCPtr, Material.getCPtr(aObject));
  }

  public void clearAndDestroy() {
    opensimModelJNI.SetMaterials_clearAndDestroy(swigCPtr);
  }

  public boolean set(int aIndex, Material aObject) {
    return opensimModelJNI.SetMaterials_set(swigCPtr, aIndex, Material.getCPtr(aObject));
  }

  public Material get(int aIndex) {
    long cPtr = opensimModelJNI.SetMaterials_get__SWIG_0(swigCPtr, aIndex);
    return (cPtr == 0) ? null : new Material(cPtr, false);
  }

  public Material get(String aName) {
    long cPtr = opensimModelJNI.SetMaterials_get__SWIG_1(swigCPtr, aName);
    return (cPtr == 0) ? null : new Material(cPtr, false);
  }

  public void getNames(ArrayStr rNames) {
    opensimModelJNI.SetMaterials_getNames(swigCPtr, ArrayStr.getCPtr(rNames));
  }

  public Material getLast() {
    long cPtr = opensimModelJNI.SetMaterials_getLast(swigCPtr);
    return (cPtr == 0) ? null : new Material(cPtr, false);
  }

  public int searchBinary(Material aObject, boolean aFindFirst, int aLo, int aHi) {
    return opensimModelJNI.SetMaterials_searchBinary__SWIG_0(swigCPtr, Material.getCPtr(aObject), aFindFirst, aLo, aHi);
  }

  public int searchBinary(Material aObject, boolean aFindFirst, int aLo) {
    return opensimModelJNI.SetMaterials_searchBinary__SWIG_1(swigCPtr, Material.getCPtr(aObject), aFindFirst, aLo);
  }

  public int searchBinary(Material aObject, boolean aFindFirst) {
    return opensimModelJNI.SetMaterials_searchBinary__SWIG_2(swigCPtr, Material.getCPtr(aObject), aFindFirst);
  }

  public int searchBinary(Material aObject) {
    return opensimModelJNI.SetMaterials_searchBinary__SWIG_3(swigCPtr, Material.getCPtr(aObject));
  }

}
