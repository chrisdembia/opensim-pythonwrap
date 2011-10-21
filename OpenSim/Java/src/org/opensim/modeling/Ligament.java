/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Ligament extends Force {
  private long swigCPtr;

  public Ligament(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.Ligament_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Ligament obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_Ligament(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Ligament() {
    this(opensimModelJNI.new_Ligament__SWIG_0(), true);
  }

  public Ligament(Ligament aLigament) {
    this(opensimModelJNI.new_Ligament__SWIG_1(Ligament.getCPtr(aLigament), aLigament), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Ligament_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(Ligament aLigament) {
    opensimModelJNI.Ligament_copyData(swigCPtr, this, Ligament.getCPtr(aLigament), aLigament);
  }

  public GeometryPath getGeometryPath() {
    return new GeometryPath(opensimModelJNI.Ligament_getGeometryPath(swigCPtr, this), false);
  }

  public boolean hasGeometryPath() {
    return opensimModelJNI.Ligament_hasGeometryPath(swigCPtr, this);
  }

  public double getLength(SWIGTYPE_p_SimTK__State s) {
    return opensimModelJNI.Ligament_getLength(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public double getRestingLength() {
    return opensimModelJNI.Ligament_getRestingLength(swigCPtr, this);
  }

  public boolean setRestingLength(double aRestingLength) {
    return opensimModelJNI.Ligament_setRestingLength(swigCPtr, this, aRestingLength);
  }

  public double getMaxIsometricForce() {
    return opensimModelJNI.Ligament_getMaxIsometricForce(swigCPtr, this);
  }

  public boolean setMaxIsometricForce(double aMaxIsometricForce) {
    return opensimModelJNI.Ligament_setMaxIsometricForce(swigCPtr, this, aMaxIsometricForce);
  }

  public Function getForceLengthCurve() {
    long cPtr = opensimModelJNI.Ligament_getForceLengthCurve(swigCPtr, this);
    return (cPtr == 0) ? null : new Function(cPtr, false);
  }

  public boolean setForceLengthCurve(Function aForceLengthCurve) {
    return opensimModelJNI.Ligament_setForceLengthCurve(swigCPtr, this, Function.getCPtr(aForceLengthCurve), aForceLengthCurve);
  }

  public double computeMomentArm(SWIGTYPE_p_SimTK__State s, Coordinate aCoord) {
    return opensimModelJNI.Ligament_computeMomentArm(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), Coordinate.getCPtr(aCoord), aCoord);
  }

  public void computeForce(SWIGTYPE_p_SimTK__State s, SWIGTYPE_p_SimTK__Vector_T_SimTK__SpatialVec_t bodyForces, SWIGTYPE_p_SimTK__Vector generalizedForces) {
    opensimModelJNI.Ligament_computeForce(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), SWIGTYPE_p_SimTK__Vector_T_SimTK__SpatialVec_t.getCPtr(bodyForces), SWIGTYPE_p_SimTK__Vector.getCPtr(generalizedForces));
  }

  public void preScale(SWIGTYPE_p_SimTK__State s, ScaleSet aScaleSet) {
    opensimModelJNI.Ligament_preScale(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void scale(SWIGTYPE_p_SimTK__State s, ScaleSet aScaleSet) {
    opensimModelJNI.Ligament_scale(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public void postScale(SWIGTYPE_p_SimTK__State s, ScaleSet aScaleSet) {
    opensimModelJNI.Ligament_postScale(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s), ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public VisibleObject getDisplayer() {
    long cPtr = opensimModelJNI.Ligament_getDisplayer(swigCPtr, this);
    return (cPtr == 0) ? null : new VisibleObject(cPtr, false);
  }

  public void updateDisplayer(SWIGTYPE_p_SimTK__State s) {
    opensimModelJNI.Ligament_updateDisplayer(swigCPtr, this, SWIGTYPE_p_SimTK__State.getCPtr(s));
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.Ligament_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.Ligament_isA(swigCPtr, this, type);
  }

  public static Ligament safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.Ligament_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new Ligament(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.Ligament_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
