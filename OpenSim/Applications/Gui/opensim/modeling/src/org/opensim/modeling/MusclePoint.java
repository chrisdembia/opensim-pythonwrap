/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class MusclePoint extends OpenSimObject {
  private long swigCPtr;

  public MusclePoint(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(MusclePoint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_MusclePoint(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public MusclePoint() {
    this(opensimModelJNI.new_MusclePoint__SWIG_0(), true);
  }

  public MusclePoint(MusclePoint aPoint) {
    this(opensimModelJNI.new_MusclePoint__SWIG_1(MusclePoint.getCPtr(aPoint), aPoint), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.MusclePoint_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(MusclePoint aPoint) {
    opensimModelJNI.MusclePoint_copyData(swigCPtr, this, MusclePoint.getCPtr(aPoint), aPoint);
  }

  public ArrayDouble getAttachment() {
    return new ArrayDouble(opensimModelJNI.MusclePoint_getAttachment(swigCPtr, this), false);
  }

  public void setAttachment(double[] aAttachment) {
    opensimModelJNI.MusclePoint_setAttachment__SWIG_0(swigCPtr, this, aAttachment);
  }

  public void setAttachment(int aCoordIndex, double aAttachment) {
    opensimModelJNI.MusclePoint_setAttachment__SWIG_1(swigCPtr, this, aCoordIndex, aAttachment);
  }

  public AbstractBody getBody() {
    long cPtr = opensimModelJNI.MusclePoint_getBody(swigCPtr, this);
    return (cPtr == 0) ? null : new AbstractBody(cPtr, false);
  }

  public void setBody(AbstractBody aBody) {
    opensimModelJNI.MusclePoint_setBody(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody);
  }

  public String getBodyName() {
    return opensimModelJNI.MusclePoint_getBodyName(swigCPtr, this);
  }

  public void scale(ArrayDouble aScaleFactors) {
    opensimModelJNI.MusclePoint_scale(swigCPtr, this, ArrayDouble.getCPtr(aScaleFactors), aScaleFactors);
  }

  public AbstractMuscle getMuscle() {
    long cPtr = opensimModelJNI.MusclePoint_getMuscle(swigCPtr, this);
    return (cPtr == 0) ? null : new AbstractMuscle(cPtr, false);
  }

  public boolean isActive() {
    return opensimModelJNI.MusclePoint_isActive(swigCPtr, this);
  }

  public AbstractWrapObject getWrapObject() {
    long cPtr = opensimModelJNI.MusclePoint_getWrapObject(swigCPtr, this);
    return (cPtr == 0) ? null : new AbstractWrapObject(cPtr, false);
  }

  public void setup(Model aModel, AbstractMuscle aMuscle) {
    opensimModelJNI.MusclePoint_setup(swigCPtr, this, Model.getCPtr(aModel), aModel, AbstractMuscle.getCPtr(aMuscle), aMuscle);
  }

  public void update() {
    opensimModelJNI.MusclePoint_update(swigCPtr, this);
  }

  public void getVelocity(double[] aVelocity) {
    opensimModelJNI.MusclePoint_getVelocity(swigCPtr, this, aVelocity);
  }

  public VisibleObject getDisplayer() {
    long cPtr = opensimModelJNI.MusclePoint_getDisplayer(swigCPtr, this);
    return (cPtr == 0) ? null : new VisibleObject(cPtr, false);
  }

  public void updateGeometry() {
    opensimModelJNI.MusclePoint_updateGeometry(swigCPtr, this);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.MusclePoint_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.MusclePoint_isA(swigCPtr, this, type);
  }

  public static MusclePoint safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.MusclePoint_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new MusclePoint(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.MusclePoint_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
