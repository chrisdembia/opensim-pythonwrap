package simtkModel;

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class Model {
  public static SWIGTYPE_p_double new_doubleArray(int n) {
    long cPtr = ModelJNI.new_doubleArray(n);
    return (cPtr == 0) ? null : new SWIGTYPE_p_double(cPtr, false);
  }

  public static void free_doubleArray(SWIGTYPE_p_double x) {
    ModelJNI.free_doubleArray(SWIGTYPE_p_double.getCPtr(x));
  }

  public static void doubleArray_set(SWIGTYPE_p_double x, int i, double v) {
    ModelJNI.doubleArray_set(SWIGTYPE_p_double.getCPtr(x), i, v);
  }

  public static double doubleArray_get(SWIGTYPE_p_double x, int i) {
    return ModelJNI.doubleArray_get(SWIGTYPE_p_double.getCPtr(x), i);
  }

  public static SWIGTYPE_p_float new_floatArray(int n) {
    long cPtr = ModelJNI.new_floatArray(n);
    return (cPtr == 0) ? null : new SWIGTYPE_p_float(cPtr, false);
  }

  public static void free_floatArray(SWIGTYPE_p_float x) {
    ModelJNI.free_floatArray(SWIGTYPE_p_float.getCPtr(x));
  }

  public static void floatArray_set(SWIGTYPE_p_float x, int i, float v) {
    ModelJNI.floatArray_set(SWIGTYPE_p_float.getCPtr(x), i, v);
  }

  public static float floatArray_get(SWIGTYPE_p_float x, int i) {
    return ModelJNI.floatArray_get(SWIGTYPE_p_float.getCPtr(x), i);
  }

  public static SWIGTYPE_p_int new_intArray(int n) {
    long cPtr = ModelJNI.new_intArray(n);
    return (cPtr == 0) ? null : new SWIGTYPE_p_int(cPtr, false);
  }

  public static void free_intArray(SWIGTYPE_p_int x) {
    ModelJNI.free_intArray(SWIGTYPE_p_int.getCPtr(x));
  }

  public static void intArray_set(SWIGTYPE_p_int x, int i, int v) {
    ModelJNI.intArray_set(SWIGTYPE_p_int.getCPtr(x), i, v);
  }

  public static int intArray_get(SWIGTYPE_p_int x, int i) {
    return ModelJNI.intArray_get(SWIGTYPE_p_int.getCPtr(x), i);
  }

  public static int getRdArray_CAPMIN() {
    return ModelJNI.get_rdArray_CAPMIN();
  }

  public static String getRdObjectDEFAULT_NAME() {
    return ModelJNI.get_rdObjectDEFAULT_NAME();
  }

  public static int getRdStorage_DEFAULT_CAPACITY() {
    return ModelJNI.get_rdStorage_DEFAULT_CAPACITY();
  }

}
