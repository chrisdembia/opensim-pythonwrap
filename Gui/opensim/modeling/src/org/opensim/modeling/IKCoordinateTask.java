/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class IKCoordinateTask extends IKTask {
  private long swigCPtr;

  public IKCoordinateTask(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.IKCoordinateTask_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(IKCoordinateTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_IKCoordinateTask(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static IKCoordinateTask safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.IKCoordinateTask_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new IKCoordinateTask(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.IKCoordinateTask_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.IKCoordinateTask_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.IKCoordinateTask_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new IKCoordinateTask(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.IKCoordinateTask_getConcreteClassName(swigCPtr, this);
  }

  public IKCoordinateTask() {
    this(opensimModelJNI.new_IKCoordinateTask__SWIG_0(), true);
  }

  public IKCoordinateTask(IKCoordinateTask aIKCoordinateTask) {
    this(opensimModelJNI.new_IKCoordinateTask__SWIG_1(IKCoordinateTask.getCPtr(aIKCoordinateTask), aIKCoordinateTask), true);
  }

  public void setValueType(IKCoordinateTask.ValueType type) {
    opensimModelJNI.IKCoordinateTask_setValueType(swigCPtr, this, type.swigValue());
  }

  public IKCoordinateTask.ValueType getValueType() {
    return IKCoordinateTask.ValueType.swigToEnum(opensimModelJNI.IKCoordinateTask_getValueType(swigCPtr, this));
  }

  public double getValue() {
    return opensimModelJNI.IKCoordinateTask_getValue(swigCPtr, this);
  }

  public void setValue(double value) {
    opensimModelJNI.IKCoordinateTask_setValue(swigCPtr, this, value);
  }

  public static String ValueTypeToString(IKCoordinateTask.ValueType type) {
    return opensimModelJNI.IKCoordinateTask_ValueTypeToString(type.swigValue());
  }

  public static IKCoordinateTask.ValueType StringToValueType(String str) {
    return IKCoordinateTask.ValueType.swigToEnum(opensimModelJNI.IKCoordinateTask_StringToValueType(str));
  }

  public final static class ValueType {
    public final static IKCoordinateTask.ValueType DefaultValue = new IKCoordinateTask.ValueType("DefaultValue");
    public final static IKCoordinateTask.ValueType ManualValue = new IKCoordinateTask.ValueType("ManualValue");
    public final static IKCoordinateTask.ValueType FromFile = new IKCoordinateTask.ValueType("FromFile");

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static ValueType swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + ValueType.class + " with value " + swigValue);
    }

    private ValueType(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private ValueType(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private ValueType(String swigName, ValueType swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static ValueType[] swigValues = { DefaultValue, ManualValue, FromFile };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}
