/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmModel extends Model {
  private long swigCPtr;

  protected SimmModel(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGSimmModelUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SimmModel obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmModel(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SimmModel() {
    this(opensimModelJNI.new_SimmModel__SWIG_0(), true);
  }

  public SimmModel(String aFileName) {
    this(opensimModelJNI.new_SimmModel__SWIG_1(aFileName), true);
  }

  public SimmModel(SWIGTYPE_p_DOMElement aElement) {
    this(opensimModelJNI.new_SimmModel__SWIG_2(SWIGTYPE_p_DOMElement.getCPtr(aElement)), true);
  }

  public SimmModel(SimmModel aModel) {
    this(opensimModelJNI.new_SimmModel__SWIG_3(SimmModel.getCPtr(aModel)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmModel_copy__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public OpenSimObject copy(SWIGTYPE_p_DOMElement aElement) {
    long cPtr = opensimModelJNI.SimmModel_copy__SWIG_1(swigCPtr, SWIGTYPE_p_DOMElement.getCPtr(aElement));
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void copyData(SimmModel aModel) {
    opensimModelJNI.SimmModel_copyData(swigCPtr, SimmModel.getCPtr(aModel));
  }

  public int getNumberOfMuscles() {
    return opensimModelJNI.SimmModel_getNumberOfMuscles(swigCPtr);
  }

  public OpenSimObject getMuscle(int index) {
    long cPtr = opensimModelJNI.SimmModel_getMuscle(swigCPtr, index);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public int getNumberOfMuscleGroups() {
    return opensimModelJNI.SimmModel_getNumberOfMuscleGroups(swigCPtr);
  }

  public SimmMuscleGroup enterGroup(String aName) {
    long cPtr = opensimModelJNI.SimmModel_enterGroup(swigCPtr, aName);
    return (cPtr == 0) ? null : new SimmMuscleGroup(cPtr, false);
  }

  public void setKinematicsEngine(AbstractDynamicsEngine aKE) {
    opensimModelJNI.SimmModel_setKinematicsEngine(swigCPtr, AbstractDynamicsEngine.getCPtr(aKE));
  }

  public AbstractDynamicsEngine getKinematicsEngine() {
    return new AbstractDynamicsEngine(opensimModelJNI.SimmModel_getKinematicsEngine(swigCPtr), false);
  }

  public SimmKinematicsEngine getSimmKinematicsEngine() {
    return new SimmKinematicsEngine(opensimModelJNI.SimmModel_getSimmKinematicsEngine(swigCPtr), false);
  }

  public void moveMarkersToCloud(Storage aMarkerStorage) {
    opensimModelJNI.SimmModel_moveMarkersToCloud(swigCPtr, Storage.getCPtr(aMarkerStorage));
  }

  public int deleteUnusedMarkers(ArrayStr aMarkerNames) {
    return opensimModelJNI.SimmModel_deleteUnusedMarkers(swigCPtr, ArrayStr.getCPtr(aMarkerNames));
  }

  public int replaceMarkerSet(SWIGTYPE_p_SimmMarkerSet aMarkerSet) {
    return opensimModelJNI.SimmModel_replaceMarkerSet(swigCPtr, SWIGTYPE_p_SimmMarkerSet.getCPtr(aMarkerSet));
  }

  public void updateMarkers(SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmMarker_t aMarkerArray) {
    opensimModelJNI.SimmModel_updateMarkers(swigCPtr, SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmMarker_t.getCPtr(aMarkerArray));
  }

  public void updateCoordinates(SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmCoordinate_t aCoordinateArray) {
    opensimModelJNI.SimmModel_updateCoordinates(swigCPtr, SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmCoordinate_t.getCPtr(aCoordinateArray));
  }

  public double takeMeasurement(SWIGTYPE_p_SimmMeasurement aMeasurement) {
    return opensimModelJNI.SimmModel_takeMeasurement(swigCPtr, SWIGTYPE_p_SimmMeasurement.getCPtr(aMeasurement));
  }

  public SimmUnits getLengthUnits() {
    return new SimmUnits(opensimModelJNI.SimmModel_getLengthUnits(swigCPtr), false);
  }

  public SimmUnits getForceUnits() {
    return new SimmUnits(opensimModelJNI.SimmModel_getForceUnits(swigCPtr), false);
  }

  public SWIGTYPE_p_double getGravity() {
    long cPtr = opensimModelJNI.SimmModel_getGravity__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_double(cPtr, false);
  }

  public String getGravityLabel() {
    return opensimModelJNI.SimmModel_getGravityLabel(swigCPtr);
  }

  public boolean bodyNeededForDynamics(SimmBody aBody) {
    return opensimModelJNI.SimmModel_bodyNeededForDynamics(swigCPtr, SimmBody.getCPtr(aBody));
  }

  public SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmBody_t getBodies() {
    return new SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmBody_t(opensimModelJNI.SimmModel_getBodies(swigCPtr), false);
  }

  public SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmCoordinate_t getCoordinates() {
    return new SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmCoordinate_t(opensimModelJNI.SimmModel_getCoordinates__SWIG_0(swigCPtr), false);
  }

  public void setPin(int aBody, int aPinNumber, double[] aPin) {
    opensimModelJNI.SimmModel_setPin(swigCPtr, aBody, aPinNumber, aPin);
  }

  public void getPin(int aBody, int aPinNumber, double[] rPin) {
    opensimModelJNI.SimmModel_getPin(swigCPtr, aBody, aPinNumber, rPin);
  }

  public void getJointInfo(int aJoint, int[] rInfo, int[] rSlider) {
    opensimModelJNI.SimmModel_getJointInfo(swigCPtr, aJoint, rInfo, rSlider);
  }

  public String getInputFileName() {
    return opensimModelJNI.SimmModel_getInputFileName(swigCPtr);
  }

  public void writeSIMMJointFile(SWIGTYPE_p_std__string aFileName) {
    opensimModelJNI.SimmModel_writeSIMMJointFile(swigCPtr, SWIGTYPE_p_std__string.getCPtr(aFileName));
  }

  public void writeSIMMMuscleFile(SWIGTYPE_p_std__string aFileName) {
    opensimModelJNI.SimmModel_writeSIMMMuscleFile(swigCPtr, SWIGTYPE_p_std__string.getCPtr(aFileName));
  }

  public void writeMarkerFile(SWIGTYPE_p_std__string aFileName) {
    opensimModelJNI.SimmModel_writeMarkerFile(swigCPtr, SWIGTYPE_p_std__string.getCPtr(aFileName));
  }

  public static void registerTypes() {
    opensimModelJNI.SimmModel_registerTypes();
  }

  public void setup() {
    opensimModelJNI.SimmModel_setup(swigCPtr);
  }

  public boolean builtOK() {
    return opensimModelJNI.SimmModel_builtOK(swigCPtr);
  }

  public void peteTest() {
    opensimModelJNI.SimmModel_peteTest(swigCPtr);
  }

  public int getNJ() {
    return opensimModelJNI.SimmModel_getNJ(swigCPtr);
  }

  public int getNQ() {
    return opensimModelJNI.SimmModel_getNQ(swigCPtr);
  }

  public int getNU() {
    return opensimModelJNI.SimmModel_getNU(swigCPtr);
  }

  public int getNX() {
    return opensimModelJNI.SimmModel_getNX(swigCPtr);
  }

  public int getNA() {
    return opensimModelJNI.SimmModel_getNA(swigCPtr);
  }

  public int getNP() {
    return opensimModelJNI.SimmModel_getNP(swigCPtr);
  }

  public int getNY() {
    return opensimModelJNI.SimmModel_getNY(swigCPtr);
  }

  public int getNYP() {
    return opensimModelJNI.SimmModel_getNYP(swigCPtr);
  }

  public String getBodyName(int aIndex) {
    return opensimModelJNI.SimmModel_getBodyName(swigCPtr, aIndex);
  }

  public String getCoordinateName(int aIndex) {
    return opensimModelJNI.SimmModel_getCoordinateName(swigCPtr, aIndex);
  }

  public String getSpeedName(int aIndex) {
    return opensimModelJNI.SimmModel_getSpeedName(swigCPtr, aIndex);
  }

  public String getActuatorName(int aIndex) {
    return opensimModelJNI.SimmModel_getActuatorName(swigCPtr, aIndex);
  }

  public String getControlName(int aIndex) {
    return opensimModelJNI.SimmModel_getControlName(swigCPtr, aIndex);
  }

  public String getStateName(int aIndex) {
    return opensimModelJNI.SimmModel_getStateName(swigCPtr, aIndex);
  }

  public String getPseudoStateName(int aIndex) {
    return opensimModelJNI.SimmModel_getPseudoStateName(swigCPtr, aIndex);
  }

  public int getBodyIndex(String aName) {
    return opensimModelJNI.SimmModel_getBodyIndex(swigCPtr, aName);
  }

  public int getCoordinateIndex(String aName) {
    return opensimModelJNI.SimmModel_getCoordinateIndex(swigCPtr, aName);
  }

  public int getSpeedIndex(String aName) {
    return opensimModelJNI.SimmModel_getSpeedIndex(swigCPtr, aName);
  }

  public int getActuatorIndex(String aName) {
    return opensimModelJNI.SimmModel_getActuatorIndex(swigCPtr, aName);
  }

  public int getControlIndex(String aName) {
    return opensimModelJNI.SimmModel_getControlIndex(swigCPtr, aName);
  }

  public int getStateIndex(String aName) {
    return opensimModelJNI.SimmModel_getStateIndex(swigCPtr, aName);
  }

  public int getPseudoStateIndex(String aName) {
    return opensimModelJNI.SimmModel_getPseudoStateIndex(swigCPtr, aName);
  }

  public void set(double aT, double[] aX, double[] aY) {
    opensimModelJNI.SimmModel_set(swigCPtr, aT, aX, aY);
  }

  public void setControls(double[] aX) {
    opensimModelJNI.SimmModel_setControls(swigCPtr, aX);
  }

  public void setControl(int aIndex, double aValue) {
    opensimModelJNI.SimmModel_setControl__SWIG_0(swigCPtr, aIndex, aValue);
  }

  public void setControl(String aName, double aValue) {
    opensimModelJNI.SimmModel_setControl__SWIG_1(swigCPtr, aName, aValue);
  }

  public void getControls(double[] rX) {
    opensimModelJNI.SimmModel_getControls(swigCPtr, rX);
  }

  public double getControl(int aIndex) {
    return opensimModelJNI.SimmModel_getControl__SWIG_0(swigCPtr, aIndex);
  }

  public double getControl(String aName) {
    return opensimModelJNI.SimmModel_getControl__SWIG_1(swigCPtr, aName);
  }

  public void setInitialStates(double[] aYI) {
    opensimModelJNI.SimmModel_setInitialStates(swigCPtr, aYI);
  }

  public void getInitialStates(double[] rYI) {
    opensimModelJNI.SimmModel_getInitialStates(swigCPtr, rYI);
  }

  public double getInitialState(int aIndex) {
    return opensimModelJNI.SimmModel_getInitialState__SWIG_0(swigCPtr, aIndex);
  }

  public double getInitialState(String aName) {
    return opensimModelJNI.SimmModel_getInitialState__SWIG_1(swigCPtr, aName);
  }

  public void setStates(double[] aY) {
    opensimModelJNI.SimmModel_setStates(swigCPtr, aY);
  }

  public void getStates(double[] rY) {
    opensimModelJNI.SimmModel_getStates(swigCPtr, rY);
  }

  public double getState(int aIndex) {
    return opensimModelJNI.SimmModel_getState__SWIG_0(swigCPtr, aIndex);
  }

  public double getState(String aName) {
    return opensimModelJNI.SimmModel_getState__SWIG_1(swigCPtr, aName);
  }

  public void applyDefaultPose() {
    opensimModelJNI.SimmModel_applyDefaultPose(swigCPtr);
  }

  public void setInitialPseudoStates(double[] aYPI) {
    opensimModelJNI.SimmModel_setInitialPseudoStates(swigCPtr, aYPI);
  }

  public void getInitialPseudoStates(double[] rYPI) {
    opensimModelJNI.SimmModel_getInitialPseudoStates(swigCPtr, rYPI);
  }

  public double getInitialPseudoState(int aIndex) {
    return opensimModelJNI.SimmModel_getInitialPseudoState__SWIG_0(swigCPtr, aIndex);
  }

  public double getInitialPseudoState(String aName) {
    return opensimModelJNI.SimmModel_getInitialPseudoState__SWIG_1(swigCPtr, aName);
  }

  public void setPseudoStates(double[] aYP) {
    opensimModelJNI.SimmModel_setPseudoStates(swigCPtr, aYP);
  }

  public void getPseudoStates(double[] rYP) {
    opensimModelJNI.SimmModel_getPseudoStates(swigCPtr, rYP);
  }

  public double getPseudoState(int aIndex) {
    return opensimModelJNI.SimmModel_getPseudoState(swigCPtr, aIndex);
  }

  public void setConfiguration(double[] aY) {
    opensimModelJNI.SimmModel_setConfiguration__SWIG_0(swigCPtr, aY);
  }

  public void setConfiguration(double[] aQ, double[] aU) {
    opensimModelJNI.SimmModel_setConfiguration__SWIG_1(swigCPtr, aQ, aU);
  }

  public void getCoordinates(double[] rQ) {
    opensimModelJNI.SimmModel_getCoordinates__SWIG_1(swigCPtr, rQ);
  }

  public double getCoordinate(int aIndex) {
    return opensimModelJNI.SimmModel_getCoordinate__SWIG_0(swigCPtr, aIndex);
  }

  public double getCoordinate(String aName) {
    return opensimModelJNI.SimmModel_getCoordinate__SWIG_1(swigCPtr, aName);
  }

  public void getSpeeds(double[] rU) {
    opensimModelJNI.SimmModel_getSpeeds(swigCPtr, rU);
  }

  public double getSpeed(int aIndex) {
    return opensimModelJNI.SimmModel_getSpeed__SWIG_0(swigCPtr, aIndex);
  }

  public double getSpeed(String aName) {
    return opensimModelJNI.SimmModel_getSpeed__SWIG_1(swigCPtr, aName);
  }

  public void getAccelerations(double[] rDUDT) {
    opensimModelJNI.SimmModel_getAccelerations(swigCPtr, rDUDT);
  }

  public double getAcceleration(int aIndex) {
    return opensimModelJNI.SimmModel_getAcceleration__SWIG_0(swigCPtr, aIndex);
  }

  public double getAcceleration(String aSpeedName) {
    return opensimModelJNI.SimmModel_getAcceleration__SWIG_1(swigCPtr, aSpeedName);
  }

  public void extractConfiguration(double[] aY, double[] rQ, double[] rU) {
    opensimModelJNI.SimmModel_extractConfiguration(swigCPtr, aY, rQ, rU);
  }

  public int assemble(double aTime, SWIGTYPE_p_double rState, SWIGTYPE_p_int aLock, double aTol, int aMaxevals, SWIGTYPE_p_int rFcnt, SWIGTYPE_p_int rErr) {
    return opensimModelJNI.SimmModel_assemble(swigCPtr, aTime, SWIGTYPE_p_double.getCPtr(rState), SWIGTYPE_p_int.getCPtr(aLock), aTol, aMaxevals, SWIGTYPE_p_int.getCPtr(rFcnt), SWIGTYPE_p_int.getCPtr(rErr));
  }

  public boolean scale(ScaleSet aScaleSet) {
    return opensimModelJNI.SimmModel_scale__SWIG_0(swigCPtr, ScaleSet.getCPtr(aScaleSet));
  }

  public boolean scale(ScaleSet aScaleSet, boolean aPreserveMassDist, double aFinalMass) {
    return opensimModelJNI.SimmModel_scale__SWIG_1(swigCPtr, ScaleSet.getCPtr(aScaleSet), aPreserveMassDist, aFinalMass);
  }

  public void getGravity(double[] rGrav) {
    opensimModelJNI.SimmModel_getGravity__SWIG_1(swigCPtr, rGrav);
  }

  public void setGravity(double[] aGrav) {
    opensimModelJNI.SimmModel_setGravity(swigCPtr, aGrav);
  }

  public int getGroundID() {
    return opensimModelJNI.SimmModel_getGroundID(swigCPtr);
  }

  public void setBodyToJointBodyLocal(int aBody, double[] aBTJ) {
    opensimModelJNI.SimmModel_setBodyToJointBodyLocal(swigCPtr, aBody, aBTJ);
  }

  public void getBodyToJointBodyLocal(int aBody, double[] rBTJ) {
    opensimModelJNI.SimmModel_getBodyToJointBodyLocal(swigCPtr, aBody, rBTJ);
  }

  public void setInboardToJointBodyLocal(int aBody, double[] aBTJ) {
    opensimModelJNI.SimmModel_setInboardToJointBodyLocal(swigCPtr, aBody, aBTJ);
  }

  public void getInboardToJointBodyLocal(int aBody, double[] rBTJ) {
    opensimModelJNI.SimmModel_getInboardToJointBodyLocal(swigCPtr, aBody, rBTJ);
  }

  public double getMass() {
    return opensimModelJNI.SimmModel_getMass__SWIG_0(swigCPtr);
  }

  public double getMass(int aBody) {
    return opensimModelJNI.SimmModel_getMass__SWIG_1(swigCPtr, aBody);
  }

  public int getInertiaBodyLocal(int aBody, SWIGTYPE_p_a_3__double rI) {
    return opensimModelJNI.SimmModel_getInertiaBodyLocal__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_a_3__double.getCPtr(rI));
  }

  public int getInertiaBodyLocal(int aBody, SWIGTYPE_p_double rI) {
    return opensimModelJNI.SimmModel_getInertiaBodyLocal__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rI));
  }

  public void getSystemInertia(SWIGTYPE_p_double rM, double[] rCOM, SWIGTYPE_p_a_3__double rI) {
    opensimModelJNI.SimmModel_getSystemInertia__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(rM), rCOM, SWIGTYPE_p_a_3__double.getCPtr(rI));
  }

  public void getSystemInertia(SWIGTYPE_p_double rM, SWIGTYPE_p_double rCOM, SWIGTYPE_p_double rI) {
    opensimModelJNI.SimmModel_getSystemInertia__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(rM), SWIGTYPE_p_double.getCPtr(rCOM), SWIGTYPE_p_double.getCPtr(rI));
  }

  public void getPosition(int aBody, double[] aPoint, double[] rPos) {
    opensimModelJNI.SimmModel_getPosition(swigCPtr, aBody, aPoint, rPos);
  }

  public void getVelocity(int aBody, double[] aPoint, double[] rVel) {
    opensimModelJNI.SimmModel_getVelocity(swigCPtr, aBody, aPoint, rVel);
  }

  public void getAcceleration(int aBody, double[] aPoint, double[] rAcc) {
    opensimModelJNI.SimmModel_getAcceleration__SWIG_2(swigCPtr, aBody, aPoint, rAcc);
  }

  public void getDirectionCosines(int aBody, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimmModel_getDirectionCosines__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void getDirectionCosines(int aBody, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimmModel_getDirectionCosines__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void getAngularVelocity(int aBody, double[] rAngVel) {
    opensimModelJNI.SimmModel_getAngularVelocity(swigCPtr, aBody, rAngVel);
  }

  public void getAngularVelocityBodyLocal(int aBody, double[] rAngVel) {
    opensimModelJNI.SimmModel_getAngularVelocityBodyLocal(swigCPtr, aBody, rAngVel);
  }

  public void getAngularAcceleration(int aBody, double[] rAngAcc) {
    opensimModelJNI.SimmModel_getAngularAcceleration(swigCPtr, aBody, rAngAcc);
  }

  public void getAngularAccelerationBodyLocal(int aBody, double[] rAngAcc) {
    opensimModelJNI.SimmModel_getAngularAccelerationBodyLocal(swigCPtr, aBody, rAngAcc);
  }

  public void applyForce(int aBody, double[] aPoint, double[] aForce) {
    opensimModelJNI.SimmModel_applyForce(swigCPtr, aBody, aPoint, aForce);
  }

  public void applyForces(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aPoints, SWIGTYPE_p_a_3__double aForces) {
    opensimModelJNI.SimmModel_applyForces__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aPoints), SWIGTYPE_p_a_3__double.getCPtr(aForces));
  }

  public void applyForces(int aN, int[] aBodies, SWIGTYPE_p_double aPoints, SWIGTYPE_p_double aForces) {
    opensimModelJNI.SimmModel_applyForces__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aPoints), SWIGTYPE_p_double.getCPtr(aForces));
  }

  public void applyForceBodyLocal(int aBody, double[] aPoint, double[] aForce) {
    opensimModelJNI.SimmModel_applyForceBodyLocal(swigCPtr, aBody, aPoint, aForce);
  }

  public void applyForcesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aPoints, SWIGTYPE_p_a_3__double aForces) {
    opensimModelJNI.SimmModel_applyForcesBodyLocal__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aPoints), SWIGTYPE_p_a_3__double.getCPtr(aForces));
  }

  public void applyForcesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_double aPoints, SWIGTYPE_p_double aForces) {
    opensimModelJNI.SimmModel_applyForcesBodyLocal__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aPoints), SWIGTYPE_p_double.getCPtr(aForces));
  }

  public void applyTorque(int aBody, double[] aTorque) {
    opensimModelJNI.SimmModel_applyTorque(swigCPtr, aBody, aTorque);
  }

  public void applyTorques(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aTorques) {
    opensimModelJNI.SimmModel_applyTorques__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aTorques));
  }

  public void applyTorques(int aN, int[] aBodies, SWIGTYPE_p_double aTorques) {
    opensimModelJNI.SimmModel_applyTorques__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aTorques));
  }

  public void applyTorqueBodyLocal(int aBody, double[] aTorque) {
    opensimModelJNI.SimmModel_applyTorqueBodyLocal(swigCPtr, aBody, aTorque);
  }

  public void applyTorquesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aTorques) {
    opensimModelJNI.SimmModel_applyTorquesBodyLocal__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aTorques));
  }

  public void applyTorquesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_double aTorques) {
    opensimModelJNI.SimmModel_applyTorquesBodyLocal__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aTorques));
  }

  public void applyGeneralizedForce(int aU, double aF) {
    opensimModelJNI.SimmModel_applyGeneralizedForce(swigCPtr, aU, aF);
  }

  public void applyGeneralizedForces(double[] aF) {
    opensimModelJNI.SimmModel_applyGeneralizedForces__SWIG_0(swigCPtr, aF);
  }

  public void applyGeneralizedForces(int aN, int[] aU, double[] aF) {
    opensimModelJNI.SimmModel_applyGeneralizedForces__SWIG_1(swigCPtr, aN, aU, aF);
  }

  public double getNetAppliedGeneralizedForce(int aU) {
    return opensimModelJNI.SimmModel_getNetAppliedGeneralizedForce(swigCPtr, aU);
  }

  public void computeGeneralizedForces(double[] aDUDT, double[] rF) {
    opensimModelJNI.SimmModel_computeGeneralizedForces(swigCPtr, aDUDT, rF);
  }

  public void computeReactions(SWIGTYPE_p_a_3__double rForces, SWIGTYPE_p_a_3__double rTorques) {
    opensimModelJNI.SimmModel_computeReactions(swigCPtr, SWIGTYPE_p_a_3__double.getCPtr(rForces), SWIGTYPE_p_a_3__double.getCPtr(rTorques));
  }

  public void prescribeMotion(int aJoint, int aAxis, int aPrescribed) {
    opensimModelJNI.SimmModel_prescribeMotion(swigCPtr, aJoint, aAxis, aPrescribed);
  }

  public void formMassMatrix(SWIGTYPE_p_double rI) {
    opensimModelJNI.SimmModel_formMassMatrix(swigCPtr, SWIGTYPE_p_double.getCPtr(rI));
  }

  public void formEulerTransform(int aBody, SWIGTYPE_p_double rE) {
    opensimModelJNI.SimmModel_formEulerTransform(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rE));
  }

  public void formJacobianTranslation(int aBody, double[] aPoint, SWIGTYPE_p_double rJ, int aRefBody) {
    opensimModelJNI.SimmModel_formJacobianTranslation__SWIG_0(swigCPtr, aBody, aPoint, SWIGTYPE_p_double.getCPtr(rJ), aRefBody);
  }

  public void formJacobianTranslation(int aBody, double[] aPoint, SWIGTYPE_p_double rJ) {
    opensimModelJNI.SimmModel_formJacobianTranslation__SWIG_1(swigCPtr, aBody, aPoint, SWIGTYPE_p_double.getCPtr(rJ));
  }

  public void formJacobianOrientation(int aBody, SWIGTYPE_p_double rJ0, int aRefBody) {
    opensimModelJNI.SimmModel_formJacobianOrientation__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJ0), aRefBody);
  }

  public void formJacobianOrientation(int aBody, SWIGTYPE_p_double rJ0) {
    opensimModelJNI.SimmModel_formJacobianOrientation__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJ0));
  }

  public void formJacobianEuler(int aBody, SWIGTYPE_p_double rJE, int aRefBody) {
    opensimModelJNI.SimmModel_formJacobianEuler__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJE), aRefBody);
  }

  public void formJacobianEuler(int aBody, SWIGTYPE_p_double rJE) {
    opensimModelJNI.SimmModel_formJacobianEuler__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJE));
  }

  public int computeAccelerations(SWIGTYPE_p_double dqdt, SWIGTYPE_p_double dudt) {
    return opensimModelJNI.SimmModel_computeAccelerations(swigCPtr, SWIGTYPE_p_double.getCPtr(dqdt), SWIGTYPE_p_double.getCPtr(dudt));
  }

  public void computeAuxiliaryDerivatives(SWIGTYPE_p_double dydt) {
    opensimModelJNI.SimmModel_computeAuxiliaryDerivatives(swigCPtr, SWIGTYPE_p_double.getCPtr(dydt));
  }

  public void transform(int aBody1, double[] aVec1, int aBody2, double[] rVec2) {
    opensimModelJNI.SimmModel_transform(swigCPtr, aBody1, aVec1, aBody2, rVec2);
  }

  public void transformPosition(int aBody, double[] aPos, double[] rPos) {
    opensimModelJNI.SimmModel_transformPosition(swigCPtr, aBody, aPos, rPos);
  }

  public void convertQuaternionsToAngles(SWIGTYPE_p_double aQ, SWIGTYPE_p_double rQAng) {
    opensimModelJNI.SimmModel_convertQuaternionsToAngles__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQ), SWIGTYPE_p_double.getCPtr(rQAng));
  }

  public void convertQuaternionsToAngles(Storage rQStore) {
    opensimModelJNI.SimmModel_convertQuaternionsToAngles__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertAnglesToQuaternions(SWIGTYPE_p_double aQAng, SWIGTYPE_p_double rQ) {
    opensimModelJNI.SimmModel_convertAnglesToQuaternions__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQAng), SWIGTYPE_p_double.getCPtr(rQ));
  }

  public void convertAnglesToQuaternions(Storage rQStore) {
    opensimModelJNI.SimmModel_convertAnglesToQuaternions__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertRadiansToDegrees(SWIGTYPE_p_double aQRad, SWIGTYPE_p_double rQDeg) {
    opensimModelJNI.SimmModel_convertRadiansToDegrees__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQRad), SWIGTYPE_p_double.getCPtr(rQDeg));
  }

  public void convertRadiansToDegrees(Storage rQStore) {
    opensimModelJNI.SimmModel_convertRadiansToDegrees__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertDegreesToRadians(SWIGTYPE_p_double aQDeg, SWIGTYPE_p_double rQRad) {
    opensimModelJNI.SimmModel_convertDegreesToRadians__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQDeg), SWIGTYPE_p_double.getCPtr(rQRad));
  }

  public void convertDegreesToRadians(Storage rQStore) {
    opensimModelJNI.SimmModel_convertDegreesToRadians__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimmModel_convertAnglesToDirectionCosines__SWIG_0(swigCPtr, aE1, aE2, aE3, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimmModel_convertAnglesToDirectionCosines__SWIG_1(swigCPtr, aE1, aE2, aE3, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void convertDirectionCosinesToAngles(SWIGTYPE_p_a_3__double aDirCos, SWIGTYPE_p_double rE1, SWIGTYPE_p_double rE2, SWIGTYPE_p_double rE3) {
    opensimModelJNI.SimmModel_convertDirectionCosinesToAngles__SWIG_0(swigCPtr, SWIGTYPE_p_a_3__double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rE1), SWIGTYPE_p_double.getCPtr(rE2), SWIGTYPE_p_double.getCPtr(rE3));
  }

  public void convertDirectionCosinesToAngles(SWIGTYPE_p_double aDirCos, SWIGTYPE_p_double rE1, SWIGTYPE_p_double rE2, SWIGTYPE_p_double rE3) {
    opensimModelJNI.SimmModel_convertDirectionCosinesToAngles__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rE1), SWIGTYPE_p_double.getCPtr(rE2), SWIGTYPE_p_double.getCPtr(rE3));
  }

  public void convertDirectionCosinesToQuaternions(SWIGTYPE_p_a_3__double aDirCos, SWIGTYPE_p_double rQ1, SWIGTYPE_p_double rQ2, SWIGTYPE_p_double rQ3, SWIGTYPE_p_double rQ4) {
    opensimModelJNI.SimmModel_convertDirectionCosinesToQuaternions__SWIG_0(swigCPtr, SWIGTYPE_p_a_3__double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rQ1), SWIGTYPE_p_double.getCPtr(rQ2), SWIGTYPE_p_double.getCPtr(rQ3), SWIGTYPE_p_double.getCPtr(rQ4));
  }

  public void convertDirectionCosinesToQuaternions(SWIGTYPE_p_double aDirCos, SWIGTYPE_p_double rQ1, SWIGTYPE_p_double rQ2, SWIGTYPE_p_double rQ3, SWIGTYPE_p_double rQ4) {
    opensimModelJNI.SimmModel_convertDirectionCosinesToQuaternions__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rQ1), SWIGTYPE_p_double.getCPtr(rQ2), SWIGTYPE_p_double.getCPtr(rQ3), SWIGTYPE_p_double.getCPtr(rQ4));
  }

  public void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimmModel_convertQuaternionsToDirectionCosines__SWIG_0(swigCPtr, aQ1, aQ2, aQ3, aQ4, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimmModel_convertQuaternionsToDirectionCosines__SWIG_1(swigCPtr, aQ1, aQ2, aQ3, aQ4, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void computeActuation() {
    opensimModelJNI.SimmModel_computeActuation(swigCPtr);
  }

  public void applyActuatorForce(int aID) {
    opensimModelJNI.SimmModel_applyActuatorForce(swigCPtr, aID);
  }

  public void applyActuatorForces() {
    opensimModelJNI.SimmModel_applyActuatorForces(swigCPtr);
  }

  public void setActuatorForce(int aID, double aForce) {
    opensimModelJNI.SimmModel_setActuatorForce(swigCPtr, aID, aForce);
  }

  public double getActuatorForce(int aID) {
    return opensimModelJNI.SimmModel_getActuatorForce(swigCPtr, aID);
  }

  public double getActuatorStress(int aID) {
    return opensimModelJNI.SimmModel_getActuatorStress(swigCPtr, aID);
  }

  public double getActuatorSpeed(int aID) {
    return opensimModelJNI.SimmModel_getActuatorSpeed(swigCPtr, aID);
  }

  public double getActuatorPower(int aID) {
    return opensimModelJNI.SimmModel_getActuatorPower(swigCPtr, aID);
  }

  public void computeContact() {
    opensimModelJNI.SimmModel_computeContact(swigCPtr);
  }

  public void applyContactForce(int aID) {
    opensimModelJNI.SimmModel_applyContactForce(swigCPtr, aID);
  }

  public void applyContactForces() {
    opensimModelJNI.SimmModel_applyContactForces(swigCPtr);
  }

  public int getContactBodyA(int aID) {
    return opensimModelJNI.SimmModel_getContactBodyA(swigCPtr, aID);
  }

  public int getContactBodyB(int aID) {
    return opensimModelJNI.SimmModel_getContactBodyB(swigCPtr, aID);
  }

  public void setContactPointA(int aID, double[] aPoint) {
    opensimModelJNI.SimmModel_setContactPointA(swigCPtr, aID, aPoint);
  }

  public void getContactPointA(int aID, double[] rPoint) {
    opensimModelJNI.SimmModel_getContactPointA(swigCPtr, aID, rPoint);
  }

  public void setContactPointB(int aID, double[] aPoint) {
    opensimModelJNI.SimmModel_setContactPointB(swigCPtr, aID, aPoint);
  }

  public void getContactPointB(int aID, double[] rPoint) {
    opensimModelJNI.SimmModel_getContactPointB(swigCPtr, aID, rPoint);
  }

  public void getContactForce(int aID, double[] rF) {
    opensimModelJNI.SimmModel_getContactForce__SWIG_0(swigCPtr, aID, rF);
  }

  public void getContactNormalForce(int aID, double[] rFP, double[] rFV, double[] rF) {
    opensimModelJNI.SimmModel_getContactNormalForce(swigCPtr, aID, rFP, rFV, rF);
  }

  public void getContactTangentForce(int aID, double[] rFP, double[] rFV, double[] rF) {
    opensimModelJNI.SimmModel_getContactTangentForce(swigCPtr, aID, rFP, rFV, rF);
  }

  public void getContactStiffness(int aID, double[] aDX, double[] rDF) {
    opensimModelJNI.SimmModel_getContactStiffness(swigCPtr, aID, aDX, rDF);
  }

  public void getContactViscosity(int aID, double[] aDV, double[] rDF) {
    opensimModelJNI.SimmModel_getContactViscosity(swigCPtr, aID, aDV, rDF);
  }

  public void getContactFrictionCorrection(int aID, double[] aDFFric) {
    opensimModelJNI.SimmModel_getContactFrictionCorrection(swigCPtr, aID, aDFFric);
  }

  public double getContactForce(int aID) {
    return opensimModelJNI.SimmModel_getContactForce__SWIG_1(swigCPtr, aID);
  }

  public double getContactSpeed(int aID) {
    return opensimModelJNI.SimmModel_getContactSpeed(swigCPtr, aID);
  }

  public double getContactPower(int aID) {
    return opensimModelJNI.SimmModel_getContactPower(swigCPtr, aID);
  }

}
