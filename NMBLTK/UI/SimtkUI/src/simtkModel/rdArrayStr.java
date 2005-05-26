/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package simtkModel;


public class rdArrayStr {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  
  public  rdArrayStr(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected rdArrayStr() {
    this(0, false);
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      ModelJNI.delete_rdArrayStr(swigCPtr);
      swigCMemOwn = false;
    }
    swigCPtr = 0;
  }

  public static long getCPtr(rdArrayStr obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public rdArrayStr(String aDefaultValue, int aSize, int aCapacity) {
    this(ModelJNI.new_rdArrayStr__SWIG_0(aDefaultValue, aSize, aCapacity), true);
  }

  public rdArrayStr(rdArrayStr aArray) {
    this(ModelJNI.new_rdArrayStr__SWIG_1(rdArrayStr.getCPtr(aArray)), true);
  }

  public boolean computeNewCapacity(int aMinCapacity, SWIGTYPE_p_int rNewCapacity) {
    return ModelJNI.rdArrayStr_computeNewCapacity(swigCPtr, aMinCapacity, SWIGTYPE_p_int.getCPtr(rNewCapacity));
  }

  public boolean ensureCapacity(int aCapacity) {
    return ModelJNI.rdArrayStr_ensureCapacity(swigCPtr, aCapacity);
  }

  public void trim() {
    ModelJNI.rdArrayStr_trim(swigCPtr);
  }

  public int getCapacity() {
    return ModelJNI.rdArrayStr_getCapacity(swigCPtr);
  }

  public void setCapacityIncrement(int aIncrement) {
    ModelJNI.rdArrayStr_setCapacityIncrement(swigCPtr, aIncrement);
  }

  public int getCapacityIncrement() {
    return ModelJNI.rdArrayStr_getCapacityIncrement(swigCPtr);
  }

  public boolean setSize(int aSize) {
    return ModelJNI.rdArrayStr_setSize(swigCPtr, aSize);
  }

  public int getSize() {
    return ModelJNI.rdArrayStr_getSize(swigCPtr);
  }

  public int append(String aValue) {
    return ModelJNI.rdArrayStr_append__SWIG_0(swigCPtr, aValue);
  }

  public int append(rdArrayStr aArray) {
    return ModelJNI.rdArrayStr_append__SWIG_1(swigCPtr, rdArrayStr.getCPtr(aArray));
  }

  public int append(int aSize, SWIGTYPE_p_std__string aArray) {
    return ModelJNI.rdArrayStr_append__SWIG_2(swigCPtr, aSize, SWIGTYPE_p_std__string.getCPtr(aArray));
  }

  public int insert(int aIndex, String aValue) {
    return ModelJNI.rdArrayStr_insert(swigCPtr, aIndex, aValue);
  }

  public int remove(int aIndex) {
    return ModelJNI.rdArrayStr_remove(swigCPtr, aIndex);
  }

  public void set(int aIndex, String aValue) {
    ModelJNI.rdArrayStr_set(swigCPtr, aIndex, aValue);
  }

  public SWIGTYPE_p_std__string get() {
    long cPtr = ModelJNI.rdArrayStr_get__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_std__string(cPtr, false);
  }

  public SWIGTYPE_p_std__string get(int aIndex) {
    return new SWIGTYPE_p_std__string(ModelJNI.rdArrayStr_get__SWIG_1(swigCPtr, aIndex), false);
  }

  public String getitem(int index) {
    return ModelJNI.rdArrayStr_getitem(swigCPtr, index);
  }

  public void setitem(int index, String val) {
    ModelJNI.rdArrayStr_setitem(swigCPtr, index, val);
  }

  public SWIGTYPE_p_std__string getLast() {
    return new SWIGTYPE_p_std__string(ModelJNI.rdArrayStr_getLast(swigCPtr), false);
  }

  public int searchBinary(String aValue, boolean aFindFirst, int aLo, int aHi) {
    return ModelJNI.rdArrayStr_searchBinary(swigCPtr, aValue, aFindFirst, aLo, aHi);
  }

}
