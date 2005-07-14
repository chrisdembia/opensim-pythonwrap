/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.19
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package simtkModel;


public class rdAnalysisSet extends rdIntegCallbackSet {
  private long swigCPtr;

  
  public  rdAnalysisSet(long cPtr, boolean cMemoryOwn) {
    super(ModelJNI.SWIGrdAnalysisSetTordIntegCallbackSet(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected rdAnalysisSet() {
    this(0, false);
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      ModelJNI.delete_rdAnalysisSet(swigCPtr);
      swigCMemOwn = false;
      super.delete();
    }
    swigCPtr = 0;
  }

  public static long getCPtr(rdAnalysisSet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public rdAnalysisSet(rdModel aModel) {
    this(ModelJNI.new_rdAnalysisSet(rdModel.getCPtr(aModel)), true);
  }

  public rdAnalysis getAnalysis(int aIndex) {
    long cPtr = ModelJNI.rdAnalysisSet_getAnalysis(swigCPtr, aIndex);
    return (cPtr == 0) ? null : new rdAnalysis(cPtr, false);
  }

  public void printResults(String aBaseName, String aPath, double aDT, String aExtension) {
    ModelJNI.rdAnalysisSet_printResults(swigCPtr, aBaseName, aPath, aDT, aExtension);
  }

}
