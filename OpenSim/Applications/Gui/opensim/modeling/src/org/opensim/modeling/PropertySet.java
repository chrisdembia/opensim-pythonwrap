/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class PropertySet {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public PropertySet(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(PropertySet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_PropertySet(swigCPtr);
    }
    swigCPtr = 0;
  }

  public void set_array(ArrayPtrsProperty value) {
    opensimModelJNI.PropertySet__array_set(swigCPtr, this, ArrayPtrsProperty.getCPtr(value), value);
  }

  public ArrayPtrsProperty get_array() {
    long cPtr = opensimModelJNI.PropertySet__array_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ArrayPtrsProperty(cPtr, false);
  }

  public PropertySet() {
    this(opensimModelJNI.new_PropertySet__SWIG_0(), true);
  }

  public PropertySet(PropertySet aSet) {
    this(opensimModelJNI.new_PropertySet__SWIG_1(PropertySet.getCPtr(aSet), aSet), true);
  }

  public boolean isEmpty() {
    return opensimModelJNI.PropertySet_isEmpty(swigCPtr, this);
  }

  public int getSize() {
    return opensimModelJNI.PropertySet_getSize(swigCPtr, this);
  }

  public Property get(int i) throws java.io.IOException {
    long cPtr = opensimModelJNI.PropertySet_get__SWIG_0(swigCPtr, this, i);
    return (cPtr == 0) ? null : new Property(cPtr, false);
  }

  public Property get(String aName) throws java.io.IOException {
    long cPtr = opensimModelJNI.PropertySet_get__SWIG_1(swigCPtr, this, aName);
    return (cPtr == 0) ? null : new Property(cPtr, false);
  }

  public void append(Property aProperty) {
    opensimModelJNI.PropertySet_append__SWIG_0(swigCPtr, this, Property.getCPtr(aProperty), aProperty);
  }

  public void append(Property aProperty, String aName) {
    opensimModelJNI.PropertySet_append__SWIG_1(swigCPtr, this, Property.getCPtr(aProperty), aProperty, aName);
  }

  public void remove(String aName) {
    opensimModelJNI.PropertySet_remove(swigCPtr, this, aName);
  }

  public void clear() {
    opensimModelJNI.PropertySet_clear(swigCPtr, this);
  }

  public PropertyGroup addGroup(String aGroupName) {
    long cPtr = opensimModelJNI.PropertySet_addGroup(swigCPtr, this, aGroupName);
    return (cPtr == 0) ? null : new PropertyGroup(cPtr, false);
  }

  public void addPropertyToGroup(String aGroupName, String aPropertyName) {
    opensimModelJNI.PropertySet_addPropertyToGroup__SWIG_0(swigCPtr, this, aGroupName, aPropertyName);
  }

  public void addPropertyToGroup(PropertyGroup aGroup, String aPropertyName) {
    opensimModelJNI.PropertySet_addPropertyToGroup__SWIG_1(swigCPtr, this, PropertyGroup.getCPtr(aGroup), aGroup, aPropertyName);
  }

  public void addPropertyToGroup(PropertyGroup aGroup, Property aProperty) {
    opensimModelJNI.PropertySet_addPropertyToGroup__SWIG_2(swigCPtr, this, PropertyGroup.getCPtr(aGroup), aGroup, Property.getCPtr(aProperty), aProperty);
  }

  public void addPropertyToGroup(String aGroupName, Property aProperty) {
    opensimModelJNI.PropertySet_addPropertyToGroup__SWIG_3(swigCPtr, this, aGroupName, Property.getCPtr(aProperty), aProperty);
  }

  public ArrayPtrsPropertyGroup getGroups() {
    return new ArrayPtrsPropertyGroup(opensimModelJNI.PropertySet_getGroups(swigCPtr, this), false);
  }

  public PropertyGroup getGroupContaining(Property aProperty) {
    long cPtr = opensimModelJNI.PropertySet_getGroupContaining(swigCPtr, this, Property.getCPtr(aProperty), aProperty);
    return (cPtr == 0) ? null : new PropertyGroup(cPtr, false);
  }

  public int getGroupIndexContaining(Property aProperty) {
    return opensimModelJNI.PropertySet_getGroupIndexContaining(swigCPtr, this, Property.getCPtr(aProperty), aProperty);
  }

}
