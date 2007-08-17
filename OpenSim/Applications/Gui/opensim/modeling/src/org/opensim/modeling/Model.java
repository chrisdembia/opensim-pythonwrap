/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class Model extends OpenSimObject {
  private long swigCPtr;

  public Model(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Model obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_Model(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  private String originalModelPath = null;
  // Important that we only refer to originalModelPath if the model's getInputFileName() is not set
  public void setOriginalModelPathFromModel(Model model) {
    originalModelPath = null;
    if(model.getInputFileName()!=null && !model.getInputFileName().equals(""))
      originalModelPath = (new java.io.File(model.getInputFileName())).getParent();
	 else if(model.originalModelPath!=null && !model.originalModelPath.equals(""))
      originalModelPath = model.originalModelPath;
  }
  public String getFilePath() {
    if(getInputFileName()!=null && !getInputFileName().equals("") && (new java.io.File(getInputFileName())).getParent()!=null)
      return (new java.io.File(getInputFileName())).getParent() + java.io.File.separator;
    else if(originalModelPath!=null && !originalModelPath.equals(""))
      return originalModelPath + java.io.File.separator;
    else return "";
  }

  public Model() {
    this(opensimModelJNI.new_Model__SWIG_0(), true);
  }

  public Model(String aFileName) throws java.io.IOException {
    this(opensimModelJNI.new_Model__SWIG_1(aFileName), true);
  }

  public Model(Model aModel) {
    this(opensimModelJNI.new_Model__SWIG_2(Model.getCPtr(aModel), aModel), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.Model_copy(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(Model aModel) {
    opensimModelJNI.Model_copyData(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void setupProperties() {
    opensimModelJNI.Model_setupProperties(swigCPtr, this);
  }

  public Model clone() {
    long cPtr = opensimModelJNI.Model_clone(swigCPtr, this);
    return (cPtr == 0) ? null : new Model(cPtr, false);
  }

  public void setup() throws java.io.IOException {
    opensimModelJNI.Model_setup(swigCPtr, this);
  }

  public boolean builtOK() {
    return opensimModelJNI.Model_builtOK(swigCPtr, this);
  }

  public String getInputFileName() {
    return opensimModelJNI.Model_getInputFileName(swigCPtr, this);
  }

  public void setInputFileName(String fileName) {
    opensimModelJNI.Model_setInputFileName(swigCPtr, this, fileName);
  }

  public String getCredits() {
    return opensimModelJNI.Model_getCredits(swigCPtr, this);
  }

  public void setAuthors(String aCredits) {
    opensimModelJNI.Model_setAuthors(swigCPtr, this, aCredits);
  }

  public String getPublications() {
    return opensimModelJNI.Model_getPublications(swigCPtr, this);
  }

  public void setPublications(String aPublications) {
    opensimModelJNI.Model_setPublications(swigCPtr, this, aPublications);
  }

  public Units getLengthUnits() {
    return new Units(opensimModelJNI.Model_getLengthUnits(swigCPtr, this), false);
  }

  public Units getForceUnits() {
    return new Units(opensimModelJNI.Model_getForceUnits(swigCPtr, this), false);
  }

  public void getGravity(double[] rGrav) {
    opensimModelJNI.Model_getGravity(swigCPtr, this, rGrav);
  }

  public boolean setGravity(double[] aGrav) {
    return opensimModelJNI.Model_setGravity(swigCPtr, this, aGrav);
  }

  public int getNumControls() {
    return opensimModelJNI.Model_getNumControls(swigCPtr, this);
  }

  public int getNumStates() {
    return opensimModelJNI.Model_getNumStates(swigCPtr, this);
  }

  public int getNumPseudoStates() {
    return opensimModelJNI.Model_getNumPseudoStates(swigCPtr, this);
  }

  public int getNumBodies() {
    return opensimModelJNI.Model_getNumBodies(swigCPtr, this);
  }

  public int getNumJoints() {
    return opensimModelJNI.Model_getNumJoints(swigCPtr, this);
  }

  public int getNumCoordinates() {
    return opensimModelJNI.Model_getNumCoordinates(swigCPtr, this);
  }

  public int getNumSpeeds() {
    return opensimModelJNI.Model_getNumSpeeds(swigCPtr, this);
  }

  public int getNumActuators() {
    return opensimModelJNI.Model_getNumActuators(swigCPtr, this);
  }

  public int getNumContacts() {
    return opensimModelJNI.Model_getNumContacts(swigCPtr, this);
  }

  public int getNumAnalyses() {
    return opensimModelJNI.Model_getNumAnalyses(swigCPtr, this);
  }

  public int getNumConfigurations() {
    return opensimModelJNI.Model_getNumConfigurations(swigCPtr, this);
  }

  public boolean hasDynamicsEngine() {
    return opensimModelJNI.Model_hasDynamicsEngine(swigCPtr, this);
  }

  public AbstractDynamicsEngine getDynamicsEngine() {
    return new AbstractDynamicsEngine(opensimModelJNI.Model_getDynamicsEngine(swigCPtr, this), false);
  }

  public void setDynamicsEngine(AbstractDynamicsEngine aEngine) {
    opensimModelJNI.Model_setDynamicsEngine(swigCPtr, this, AbstractDynamicsEngine.getCPtr(aEngine), aEngine);
  }

  public void set(double aT, double[] aX, double[] aY) {
    opensimModelJNI.Model_set(swigCPtr, this, aT, aX, aY);
  }

  public void setTime(double aTime) {
    opensimModelJNI.Model_setTime(swigCPtr, this, aTime);
  }

  public double getTime() {
    return opensimModelJNI.Model_getTime(swigCPtr, this);
  }

  public void setTimeNormConstant(double aNormConst) {
    opensimModelJNI.Model_setTimeNormConstant(swigCPtr, this, aNormConst);
  }

  public double getTimeNormConstant() {
    return opensimModelJNI.Model_getTimeNormConstant(swigCPtr, this);
  }

  public void setControls(double[] aX) {
    opensimModelJNI.Model_setControls(swigCPtr, this, aX);
  }

  public void setControl(int aIndex, double aValue) {
    opensimModelJNI.Model_setControl__SWIG_0(swigCPtr, this, aIndex, aValue);
  }

  public void setControl(String aName, double aValue) {
    opensimModelJNI.Model_setControl__SWIG_1(swigCPtr, this, aName, aValue);
  }

  public void getControls(double[] rX) {
    opensimModelJNI.Model_getControls(swigCPtr, this, rX);
  }

  public double getControl(int aIndex) {
    return opensimModelJNI.Model_getControl__SWIG_0(swigCPtr, this, aIndex);
  }

  public double getControl(String aName) {
    return opensimModelJNI.Model_getControl__SWIG_1(swigCPtr, this, aName);
  }

  public String getControlName(int aIndex) {
    return opensimModelJNI.Model_getControlName(swigCPtr, this, aIndex);
  }

  public void getStateNames(ArrayStr rStateNames) {
    opensimModelJNI.Model_getStateNames(swigCPtr, this, ArrayStr.getCPtr(rStateNames), rStateNames);
  }

  public void setStates(ArrayDouble aY) {
    opensimModelJNI.Model_setStates__SWIG_0(swigCPtr, this, ArrayDouble.getCPtr(aY), aY);
  }

  public void setStates(double[] aY) {
    opensimModelJNI.Model_setStates__SWIG_1(swigCPtr, this, aY);
  }

  public void getStates(double[] rY) {
    opensimModelJNI.Model_getStates(swigCPtr, this, rY);
  }

  public void setInitialStates(double[] aYI) {
    opensimModelJNI.Model_setInitialStates(swigCPtr, this, aYI);
  }

  public void getInitialStates(double[] rYI) {
    opensimModelJNI.Model_getInitialStates(swigCPtr, this, rYI);
  }

  public int getPseudoStateNames(ArrayStr rStateNames) {
    return opensimModelJNI.Model_getPseudoStateNames(swigCPtr, this, ArrayStr.getCPtr(rStateNames), rStateNames);
  }

  public void setPseudoStates(double[] aYP) {
    opensimModelJNI.Model_setPseudoStates(swigCPtr, this, aYP);
  }

  public void getPseudoStates(double[] rYP) {
    opensimModelJNI.Model_getPseudoStates(swigCPtr, this, rYP);
  }

  public void setInitialPseudoStates(double[] aYPI) {
    opensimModelJNI.Model_setInitialPseudoStates(swigCPtr, this, aYPI);
  }

  public void getInitialPseudoStates(double[] rYPI) {
    opensimModelJNI.Model_getInitialPseudoStates(swigCPtr, this, rYPI);
  }

  public ActuatorSet getActuatorSet() {
    long cPtr = opensimModelJNI.Model_getActuatorSet(swigCPtr, this);
    return (cPtr == 0) ? null : new ActuatorSet(cPtr, false);
  }

  public ContactForceSet getContactSet() {
    long cPtr = opensimModelJNI.Model_getContactSet(swigCPtr, this);
    return (cPtr == 0) ? null : new ContactForceSet(cPtr, false);
  }

  public SWIGTYPE_p_OpenSim__IntegCallbackSet getIntegCallbackSet() {
    long cPtr = opensimModelJNI.Model_getIntegCallbackSet(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__IntegCallbackSet(cPtr, false);
  }

  public void addIntegCallback(IntegCallback aCallback) {
    opensimModelJNI.Model_addIntegCallback(swigCPtr, this, IntegCallback.getCPtr(aCallback), aCallback);
  }

  public void removeIntegCallback(IntegCallback aCallback) {
    opensimModelJNI.Model_removeIntegCallback(swigCPtr, this, IntegCallback.getCPtr(aCallback), aCallback);
  }

  public SWIGTYPE_p_OpenSim__DerivCallbackSet getDerivCallbackSet() {
    long cPtr = opensimModelJNI.Model_getDerivCallbackSet(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OpenSim__DerivCallbackSet(cPtr, false);
  }

  public void addDerivCallback(SWIGTYPE_p_OpenSim__DerivCallback aCallback) {
    opensimModelJNI.Model_addDerivCallback(swigCPtr, this, SWIGTYPE_p_OpenSim__DerivCallback.getCPtr(aCallback));
  }

  public AnalysisSet getAnalysisSet() {
    long cPtr = opensimModelJNI.Model_getAnalysisSet(swigCPtr, this);
    return (cPtr == 0) ? null : new AnalysisSet(cPtr, false);
  }

  public void addAnalysis(Analysis aAnalysis) {
    opensimModelJNI.Model_addAnalysis(swigCPtr, this, Analysis.getCPtr(aAnalysis), aAnalysis);
  }

  public void removeAnalysis(Analysis aAnalysis) {
    opensimModelJNI.Model_removeAnalysis(swigCPtr, this, Analysis.getCPtr(aAnalysis), aAnalysis);
  }

  public void computeDerivatives(double[] rDYDT) {
    opensimModelJNI.Model_computeDerivatives(swigCPtr, this, rDYDT);
  }

  public void computeAuxiliaryDerivatives(double[] rDYDT) {
    opensimModelJNI.Model_computeAuxiliaryDerivatives(swigCPtr, this, rDYDT);
  }

  public void computeEquilibriumForAuxiliaryStates(double[] rY) {
    opensimModelJNI.Model_computeEquilibriumForAuxiliaryStates(swigCPtr, this, rY);
  }

  public boolean scale(SWIGTYPE_p_ScaleSet aScaleSet, double aFinalMass, boolean aPreserveMassDist) {
    return opensimModelJNI.Model_scale__SWIG_0(swigCPtr, this, SWIGTYPE_p_ScaleSet.getCPtr(aScaleSet), aFinalMass, aPreserveMassDist);
  }

  public boolean scale(SWIGTYPE_p_ScaleSet aScaleSet, double aFinalMass) {
    return opensimModelJNI.Model_scale__SWIG_1(swigCPtr, this, SWIGTYPE_p_ScaleSet.getCPtr(aScaleSet), aFinalMass);
  }

  public boolean scale(SWIGTYPE_p_ScaleSet aScaleSet) {
    return opensimModelJNI.Model_scale__SWIG_2(swigCPtr, this, SWIGTYPE_p_ScaleSet.getCPtr(aScaleSet));
  }

  public void printBasicInfo(SWIGTYPE_p_std__ostream aOStream) {
    opensimModelJNI.Model_printBasicInfo(swigCPtr, this, SWIGTYPE_p_std__ostream.getCPtr(aOStream));
  }

  public void printDetailedInfo(SWIGTYPE_p_std__ostream aOStream) {
    opensimModelJNI.Model_printDetailedInfo(swigCPtr, this, SWIGTYPE_p_std__ostream.getCPtr(aOStream));
  }

  public void kinTest() {
    opensimModelJNI.Model_kinTest(swigCPtr, this);
  }

}
