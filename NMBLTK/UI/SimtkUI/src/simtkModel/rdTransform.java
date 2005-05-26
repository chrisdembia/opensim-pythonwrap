/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package simtkModel;


public class rdTransform extends rdObject {
  private long swigCPtr;

  
  public  rdTransform(long cPtr, boolean cMemoryOwn) {
    super(ModelJNI.SWIGrdTransformTordObject(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      ModelJNI.delete_rdTransform(swigCPtr);
      swigCMemOwn = false;
      super.delete();
    }
    swigCPtr = 0;
  }

  public static long getCPtr(rdTransform obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public rdTransform() {
    this(ModelJNI.new_rdTransform__SWIG_0(), true);
  }

  public rdTransform(rdTransform aTransform) {
    this(ModelJNI.new_rdTransform__SWIG_1(rdTransform.getCPtr(aTransform)), true);
  }

  public rdTransform(double aAngle, SWIGTYPE_p_double aVector) {
    this(ModelJNI.new_rdTransform__SWIG_2(aAngle, SWIGTYPE_p_double.getCPtr(aVector)), true);
  }

  public rdObject copy() {
    long cPtr = ModelJNI.rdTransform_copy(swigCPtr);
    return (cPtr == 0) ? null : new rdObject(cPtr, false);
  }

  public void printMatrix() {
    ModelJNI.rdTransform_printMatrix(swigCPtr);
  }

  public void getPosition(SWIGTYPE_p_double pos) {
    ModelJNI.rdTransform_getPosition(swigCPtr, SWIGTYPE_p_double.getCPtr(pos));
  }

  public void setPosition(SWIGTYPE_p_double pos) {
    ModelJNI.rdTransform_setPosition(swigCPtr, SWIGTYPE_p_double.getCPtr(pos));
  }

  public void getOrientation(SWIGTYPE_p_double orientation) {
    ModelJNI.rdTransform_getOrientation(swigCPtr, SWIGTYPE_p_double.getCPtr(orientation));
  }

  public void setOrientation(SWIGTYPE_p_double orientation) {
    ModelJNI.rdTransform_setOrientation(swigCPtr, SWIGTYPE_p_double.getCPtr(orientation));
  }

  public void setIdentity() {
    ModelJNI.rdTransform_setIdentity(swigCPtr);
  }

  public void rotate(SWIGTYPE_p_double r, int preference, int order) {
    ModelJNI.rdTransform_rotate(swigCPtr, SWIGTYPE_p_double.getCPtr(r), preference, order);
  }

  public void rotateX(double r, int preference) {
    ModelJNI.rdTransform_rotateX(swigCPtr, r, preference);
  }

  public void rotateY(double r, int preference) {
    ModelJNI.rdTransform_rotateY(swigCPtr, r, preference);
  }

  public void rotateZ(double r, int preference) {
    ModelJNI.rdTransform_rotateZ(swigCPtr, r, preference);
  }

  public void rotateAxis(double r, int preference, SWIGTYPE_p_double axis) {
    ModelJNI.rdTransform_rotateAxis(swigCPtr, r, preference, SWIGTYPE_p_double.getCPtr(axis));
  }

  public void translateX(double t) {
    ModelJNI.rdTransform_translateX(swigCPtr, t);
  }

  public void translateY(double t) {
    ModelJNI.rdTransform_translateY(swigCPtr, t);
  }

  public void translateZ(double t) {
    ModelJNI.rdTransform_translateZ(swigCPtr, t);
  }

  public void translate(SWIGTYPE_p_double t) {
    ModelJNI.rdTransform_translate(swigCPtr, SWIGTYPE_p_double.getCPtr(t));
  }

  public void setupSerializedMembers() {
    ModelJNI.rdTransform_setupSerializedMembers(swigCPtr);
  }

  // enums and constants
  public final static int X = ModelJNI.get_rdTransform_X();
  public final static int Y = ModelJNI.get_rdTransform_Y();
  public final static int Z = ModelJNI.get_rdTransform_Z();
  public final static int NoAxis = ModelJNI.get_rdTransform_NoAxis();
  public final static int XYZ = ModelJNI.get_rdTransform_XYZ();
  public final static int XZY = ModelJNI.get_rdTransform_XZY();
  public final static int YXZ = ModelJNI.get_rdTransform_YXZ();
  public final static int YZX = ModelJNI.get_rdTransform_YZX();
  public final static int ZXY = ModelJNI.get_rdTransform_ZXY();
  public final static int ZYX = ModelJNI.get_rdTransform_ZYX();
  public final static int Radians = ModelJNI.get_rdTransform_Radians();
  public final static int Degrees = ModelJNI.get_rdTransform_Degrees();
}
