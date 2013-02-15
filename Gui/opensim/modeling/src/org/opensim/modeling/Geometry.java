/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Geometry {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Geometry(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Geometry obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_Geometry(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Geometry() {
    this(opensimModelJNI.new_Geometry(), true);
  }

  public Geometry.GeometryType getShape() {
    return Geometry.GeometryType.swigToEnum(opensimModelJNI.Geometry_getShape(swigCPtr, this));
  }

  public boolean isAnalytic() {
    return opensimModelJNI.Geometry_isAnalytic(swigCPtr, this);
  }

  public void setFixed(boolean aFixed) {
    opensimModelJNI.Geometry_setFixed(swigCPtr, this, aFixed);
  }

  public boolean getFixed() {
    return opensimModelJNI.Geometry_getFixed(swigCPtr, this);
  }

  public final static class GeometryType {
    public final static Geometry.GeometryType None = new Geometry.GeometryType("None");
    public final static Geometry.GeometryType Sphere = new Geometry.GeometryType("Sphere");
    public final static Geometry.GeometryType Cylinder = new Geometry.GeometryType("Cylinder");
    public final static Geometry.GeometryType Cone = new Geometry.GeometryType("Cone");
    public final static Geometry.GeometryType Ellipsoid = new Geometry.GeometryType("Ellipsoid");
    public final static Geometry.GeometryType Torus = new Geometry.GeometryType("Torus");
    public final static Geometry.GeometryType Line = new Geometry.GeometryType("Line");
    public final static Geometry.GeometryType Arrow = new Geometry.GeometryType("Arrow");

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static GeometryType swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + GeometryType.class + " with value " + swigValue);
    }

    private GeometryType(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private GeometryType(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private GeometryType(String swigName, GeometryType swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static GeometryType[] swigValues = { None, Sphere, Cylinder, Cone, Ellipsoid, Torus, Line, Arrow };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}
