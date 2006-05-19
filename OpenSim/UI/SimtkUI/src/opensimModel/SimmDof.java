/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package opensimModel;

public class SimmDof extends OpenSimObject {
  private long swigCPtr;

  protected SimmDof(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGSimmDofUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SimmDof obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmDof(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmDof_copy__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public OpenSimObject copy(SWIGTYPE_p_DOMElement aElement) {
    long cPtr = opensimModelJNI.SimmDof_copy__SWIG_1(swigCPtr, SWIGTYPE_p_DOMElement.getCPtr(aElement));
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(SimmDof aDof) {
    opensimModelJNI.SimmDof_copyData(swigCPtr, SimmDof.getCPtr(aDof));
  }

  public void setup(SimmKinematicsEngine aEngine, SimmJoint aJoint) {
    opensimModelJNI.SimmDof_setup(swigCPtr, SimmKinematicsEngine.getCPtr(aEngine), SimmJoint.getCPtr(aJoint));
  }

  public void getAxis(double[] axis) {
    opensimModelJNI.SimmDof_getAxis(swigCPtr, axis);
  }

  public SWIGTYPE_p_double getAxisPtr() {
    long cPtr = opensimModelJNI.SimmDof_getAxisPtr(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_double(cPtr, false);
  }

  public double getValue() {
    return opensimModelJNI.SimmDof_getValue(swigCPtr);
  }

  public SimmDof.DofType getDofType() {
    return SimmDof.DofType.swigToEnum(opensimModelJNI.SimmDof_getDofType(swigCPtr));
  }

  public SimmCoordinate getCoordinate() {
    long cPtr = opensimModelJNI.SimmDof_getCoordinate(swigCPtr);
    return (cPtr == 0) ? null : new SimmCoordinate(cPtr, false);
  }

  public Function getFunction() {
    long cPtr = opensimModelJNI.SimmDof_getFunction(swigCPtr);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public void peteTest() {
    opensimModelJNI.SimmDof_peteTest(swigCPtr);
  }

  public final static class DofType {
    public final static DofType Translational = new DofType("Translational");
    public final static DofType Rotational = new DofType("Rotational");

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static DofType swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + DofType.class + " with value " + swigValue);
    }

    private DofType(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private DofType(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private DofType(String swigName, DofType swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static DofType[] swigValues = { Translational, Rotational };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}
