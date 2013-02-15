/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimbodyEngine extends OpenSimObject {
  private long swigCPtr;

  public SimbodyEngine(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SimbodyEngine_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimbodyEngine obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        opensimModelJNI.delete_SimbodyEngine(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static SimbodyEngine safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.SimbodyEngine_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new SimbodyEngine(cPtr, false);
  }

  public void assign(OpenSimObject aObject) {
    opensimModelJNI.SimbodyEngine_assign(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

  public static String getClassName() {
    return opensimModelJNI.SimbodyEngine_getClassName();
  }

  public OpenSimObject clone() {
    long cPtr = opensimModelJNI.SimbodyEngine_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new SimbodyEngine(cPtr, false);
  }

  public String getConcreteClassName() {
    return opensimModelJNI.SimbodyEngine_getConcreteClassName(swigCPtr, this);
  }

  public void set_model(Model value) {
    opensimModelJNI.SimbodyEngine__model_set(swigCPtr, this, Model.getCPtr(value), value);
  }

  public Model get_model() {
    long cPtr = opensimModelJNI.SimbodyEngine__model_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Model(cPtr, false);
  }

  public SimbodyEngine() {
    this(opensimModelJNI.new_SimbodyEngine__SWIG_0(), true);
  }

  public SimbodyEngine(String aFileName) {
    this(opensimModelJNI.new_SimbodyEngine__SWIG_1(aFileName), true);
  }

  public SimbodyEngine(SimbodyEngine aEngine) {
    this(opensimModelJNI.new_SimbodyEngine__SWIG_2(SimbodyEngine.getCPtr(aEngine), aEngine), true);
  }

  public Model getModel() {
    return new Model(opensimModelJNI.SimbodyEngine_getModel(swigCPtr, this), false);
  }

  public void setModel(Model aModel) {
    opensimModelJNI.SimbodyEngine_setModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void connectSimbodyEngineToModel(Model aModel) {
    opensimModelJNI.SimbodyEngine_connectSimbodyEngineToModel(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public Body getGroundBody() {
    return new Body(opensimModelJNI.SimbodyEngine_getGroundBody(swigCPtr, this), false);
  }

  public WrapObject getWrapObject(String aName) {
    long cPtr = opensimModelJNI.SimbodyEngine_getWrapObject(swigCPtr, this, aName);
    return (cPtr == 0) ? null : new WrapObject(cPtr, false);
  }

  public double getMass() {
    return opensimModelJNI.SimbodyEngine_getMass(swigCPtr, this);
  }

  public void computeDerivatives(State s, SWIGTYPE_p_double dqdt, SWIGTYPE_p_double dudt) {
    opensimModelJNI.SimbodyEngine_computeDerivatives(swigCPtr, this, State.getCPtr(s), s, SWIGTYPE_p_double.getCPtr(dqdt), SWIGTYPE_p_double.getCPtr(dudt));
  }

  public void transform(State s, Body aBodyFrom, double[] aVec, Body aBodyTo, double[] rVec) {
    opensimModelJNI.SimbodyEngine_transform__SWIG_0(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBodyFrom), aBodyFrom, aVec, Body.getCPtr(aBodyTo), aBodyTo, rVec);
  }

  public void transform(State s, Body aBodyFrom, Vec3 aVec, Body aBodyTo, Vec3 rVec) {
    opensimModelJNI.SimbodyEngine_transform__SWIG_1(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBodyFrom), aBodyFrom, Vec3.getCPtr(aVec), aVec, Body.getCPtr(aBodyTo), aBodyTo, Vec3.getCPtr(rVec), rVec);
  }

  public void transformPosition(State s, Body aBodyFrom, double[] aPos, Body aBodyTo, double[] rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_0(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBodyFrom), aBodyFrom, aPos, Body.getCPtr(aBodyTo), aBodyTo, rPos);
  }

  public void transformPosition(State s, Body aBodyFrom, Vec3 aPos, Body aBodyTo, Vec3 rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_1(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBodyFrom), aBodyFrom, Vec3.getCPtr(aPos), aPos, Body.getCPtr(aBodyTo), aBodyTo, Vec3.getCPtr(rPos), rPos);
  }

  public void transformPosition(State s, Body aBodyFrom, double[] aPos, double[] rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_2(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBodyFrom), aBodyFrom, aPos, rPos);
  }

  public void transformPosition(State s, Body aBodyFrom, Vec3 aPos, Vec3 rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_3(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBodyFrom), aBodyFrom, Vec3.getCPtr(aPos), aPos, Vec3.getCPtr(rPos), rPos);
  }

  public double calcDistance(State s, Body aBody1, double[] aPoint1, Body aBody2, double[] aPoint2) {
    return opensimModelJNI.SimbodyEngine_calcDistance__SWIG_0(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBody1), aBody1, aPoint1, Body.getCPtr(aBody2), aBody2, aPoint2);
  }

  public double calcDistance(State s, Body aBody1, Vec3 aPoint1, Body aBody2, Vec3 aPoint2) {
    return opensimModelJNI.SimbodyEngine_calcDistance__SWIG_1(swigCPtr, this, State.getCPtr(s), s, Body.getCPtr(aBody1), aBody1, Vec3.getCPtr(aPoint1), aPoint1, Body.getCPtr(aBody2), aBody2, Vec3.getCPtr(aPoint2), aPoint2);
  }

  public void convertRadiansToDegrees(Storage rStorage) {
    opensimModelJNI.SimbodyEngine_convertRadiansToDegrees__SWIG_0(swigCPtr, this, Storage.getCPtr(rStorage), rStorage);
  }

  public void convertDegreesToRadians(Storage rStorage) {
    opensimModelJNI.SimbodyEngine_convertDegreesToRadians__SWIG_0(swigCPtr, this, Storage.getCPtr(rStorage), rStorage);
  }

  public void convertDegreesToRadians(SWIGTYPE_p_double aQDeg, SWIGTYPE_p_double rQRad) {
    opensimModelJNI.SimbodyEngine_convertDegreesToRadians__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aQDeg), SWIGTYPE_p_double.getCPtr(rQRad));
  }

  public void convertRadiansToDegrees(SWIGTYPE_p_double aQRad, SWIGTYPE_p_double rQDeg) {
    opensimModelJNI.SimbodyEngine_convertRadiansToDegrees__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aQRad), SWIGTYPE_p_double.getCPtr(rQDeg));
  }

  public void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimbodyEngine_convertAnglesToDirectionCosines__SWIG_0(swigCPtr, this, aE1, aE2, aE3, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimbodyEngine_convertAnglesToDirectionCosines__SWIG_1(swigCPtr, this, aE1, aE2, aE3, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void convertDirectionCosinesToAngles(SWIGTYPE_p_a_3__double aDirCos, SWIGTYPE_p_double rE1, SWIGTYPE_p_double rE2, SWIGTYPE_p_double rE3) {
    opensimModelJNI.SimbodyEngine_convertDirectionCosinesToAngles__SWIG_0(swigCPtr, this, SWIGTYPE_p_a_3__double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rE1), SWIGTYPE_p_double.getCPtr(rE2), SWIGTYPE_p_double.getCPtr(rE3));
  }

  public void convertDirectionCosinesToAngles(SWIGTYPE_p_double aDirCos, SWIGTYPE_p_double rE1, SWIGTYPE_p_double rE2, SWIGTYPE_p_double rE3) {
    opensimModelJNI.SimbodyEngine_convertDirectionCosinesToAngles__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rE1), SWIGTYPE_p_double.getCPtr(rE2), SWIGTYPE_p_double.getCPtr(rE3));
  }

  public void convertDirectionCosinesToQuaternions(SWIGTYPE_p_a_3__double aDirCos, SWIGTYPE_p_double rQ1, SWIGTYPE_p_double rQ2, SWIGTYPE_p_double rQ3, SWIGTYPE_p_double rQ4) {
    opensimModelJNI.SimbodyEngine_convertDirectionCosinesToQuaternions__SWIG_0(swigCPtr, this, SWIGTYPE_p_a_3__double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rQ1), SWIGTYPE_p_double.getCPtr(rQ2), SWIGTYPE_p_double.getCPtr(rQ3), SWIGTYPE_p_double.getCPtr(rQ4));
  }

  public void convertDirectionCosinesToQuaternions(SWIGTYPE_p_double aDirCos, SWIGTYPE_p_double rQ1, SWIGTYPE_p_double rQ2, SWIGTYPE_p_double rQ3, SWIGTYPE_p_double rQ4) {
    opensimModelJNI.SimbodyEngine_convertDirectionCosinesToQuaternions__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rQ1), SWIGTYPE_p_double.getCPtr(rQ2), SWIGTYPE_p_double.getCPtr(rQ3), SWIGTYPE_p_double.getCPtr(rQ4));
  }

  public void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimbodyEngine_convertQuaternionsToDirectionCosines__SWIG_0(swigCPtr, this, aQ1, aQ2, aQ3, aQ4, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimbodyEngine_convertQuaternionsToDirectionCosines__SWIG_1(swigCPtr, this, aQ1, aQ2, aQ3, aQ4, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

}
