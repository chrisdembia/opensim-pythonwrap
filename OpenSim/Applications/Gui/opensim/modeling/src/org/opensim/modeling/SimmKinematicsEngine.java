/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimmKinematicsEngine extends AbstractDynamicsEngine {
  private long swigCPtr;

  public SimmKinematicsEngine(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimmKinematicsEngine obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimmKinematicsEngine(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public void set_sdfastInfo(SWIGTYPE_p_SimmSdfastInfo value) {
    opensimModelJNI.SimmKinematicsEngine__sdfastInfo_set(swigCPtr, SWIGTYPE_p_SimmSdfastInfo.getCPtr(value));
  }

  public SWIGTYPE_p_SimmSdfastInfo get_sdfastInfo() {
    return new SWIGTYPE_p_SimmSdfastInfo(opensimModelJNI.SimmKinematicsEngine__sdfastInfo_get(swigCPtr), true);
  }

  public SimmKinematicsEngine() {
    this(opensimModelJNI.new_SimmKinematicsEngine__SWIG_0(), true);
  }

  public SimmKinematicsEngine(String aFileName) {
    this(opensimModelJNI.new_SimmKinematicsEngine__SWIG_1(aFileName), true);
  }

  public SimmKinematicsEngine(SWIGTYPE_p_DOMElement aElement) {
    this(opensimModelJNI.new_SimmKinematicsEngine__SWIG_2(SWIGTYPE_p_DOMElement.getCPtr(aElement)), true);
  }

  public static void registerTypes() {
    opensimModelJNI.SimmKinematicsEngine_registerTypes();
  }

  public SimmKinematicsEngine(SimmKinematicsEngine aEngine) {
    this(opensimModelJNI.new_SimmKinematicsEngine__SWIG_3(SimmKinematicsEngine.getCPtr(aEngine)), true);
  }

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_copy__SWIG_0(swigCPtr);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public OpenSimObject copy(SWIGTYPE_p_DOMElement aElement) {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_copy__SWIG_1(swigCPtr, SWIGTYPE_p_DOMElement.getCPtr(aElement));
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void saveDynamics(String aFolderName, String aMuscleFileName, String aBonePath, String aKineticsFile, String aOutputMotionFile) {
    opensimModelJNI.SimmKinematicsEngine_saveDynamics__SWIG_0(swigCPtr, aFolderName, aMuscleFileName, aBonePath, aKineticsFile, aOutputMotionFile);
  }

  public void saveDynamics(String aFolderName, String aMuscleFileName, String aBonePath, String aKineticsFile) {
    opensimModelJNI.SimmKinematicsEngine_saveDynamics__SWIG_1(swigCPtr, aFolderName, aMuscleFileName, aBonePath, aKineticsFile);
  }

  public void saveDynamics(String aFolderName, String aMuscleFileName, String aBonePath) {
    opensimModelJNI.SimmKinematicsEngine_saveDynamics__SWIG_2(swigCPtr, aFolderName, aMuscleFileName, aBonePath);
  }

  public void saveDynamics(String aFolderName, String aMuscleFileName) {
    opensimModelJNI.SimmKinematicsEngine_saveDynamics__SWIG_3(swigCPtr, aFolderName, aMuscleFileName);
  }

  public void saveDynamics(String aFolderName) {
    opensimModelJNI.SimmKinematicsEngine_saveDynamics__SWIG_4(swigCPtr, aFolderName);
  }

  public void saveDynamics() {
    opensimModelJNI.SimmKinematicsEngine_saveDynamics__SWIG_5(swigCPtr);
  }

  public SimmBody getLeafBody(SimmJoint aJoint) {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_getLeafBody(swigCPtr, SimmJoint.getCPtr(aJoint));
    return (cPtr == 0) ? null : new SimmBody(cPtr, false);
  }

  public SimmDof markUnconstrainedDof(SimmCoordinate aCoordinate) {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_markUnconstrainedDof(swigCPtr, SimmCoordinate.getCPtr(aCoordinate));
    return (cPtr == 0) ? null : new SimmDof(cPtr, false);
  }

  public void setup(SimmModel aModel) {
    opensimModelJNI.SimmKinematicsEngine_setup(swigCPtr, SimmModel.getCPtr(aModel));
  }

  public void makePaths() {
    opensimModelJNI.SimmKinematicsEngine_makePaths(swigCPtr);
  }

  public SimmBody getGroundBodyPtr() {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_getGroundBodyPtr(swigCPtr);
    return (cPtr == 0) ? null : new SimmBody(cPtr, false);
  }

  public void convertPoint(double[] aPoint, SimmBody aFrom, SimmBody aTo) {
    opensimModelJNI.SimmKinematicsEngine_convertPoint__SWIG_0(swigCPtr, aPoint, SimmBody.getCPtr(aFrom), SimmBody.getCPtr(aTo));
  }

  public void convertVector(double[] aVector, SimmBody aFrom, SimmBody aTo) {
    opensimModelJNI.SimmKinematicsEngine_convertVector(swigCPtr, aVector, SimmBody.getCPtr(aFrom), SimmBody.getCPtr(aTo));
  }

  public void convertPoint(ArrayDouble aPoint, SimmBody aFrom, SimmBody aTo) {
    opensimModelJNI.SimmKinematicsEngine_convertPoint__SWIG_1(swigCPtr, ArrayDouble.getCPtr(aPoint), SimmBody.getCPtr(aFrom), SimmBody.getCPtr(aTo));
  }

  public double calcDistance(ArrayDouble aPoint1, SimmBody aBody1, ArrayDouble aPoint2, SimmBody aBody2) {
    return opensimModelJNI.SimmKinematicsEngine_calcDistance__SWIG_0(swigCPtr, ArrayDouble.getCPtr(aPoint1), SimmBody.getCPtr(aBody1), ArrayDouble.getCPtr(aPoint2), SimmBody.getCPtr(aBody2));
  }

  public double calcDistance(double[] aPoint1, SimmBody aBody1, double[] aPoint2, SimmBody aBody2) {
    return opensimModelJNI.SimmKinematicsEngine_calcDistance__SWIG_1(swigCPtr, aPoint1, SimmBody.getCPtr(aBody1), aPoint2, SimmBody.getCPtr(aBody2));
  }

  public int getNumMarkers() {
    return opensimModelJNI.SimmKinematicsEngine_getNumMarkers(swigCPtr);
  }

  public void moveMarkersToCloud(Storage aMarkerStorage) {
    opensimModelJNI.SimmKinematicsEngine_moveMarkersToCloud(swigCPtr, Storage.getCPtr(aMarkerStorage));
  }

  public int deleteUnusedMarkers(ArrayStr aMarkerNames) {
    return opensimModelJNI.SimmKinematicsEngine_deleteUnusedMarkers(swigCPtr, ArrayStr.getCPtr(aMarkerNames));
  }

  public int replaceMarkerSet(SimmMarkerSet aMarkerSet) {
    return opensimModelJNI.SimmKinematicsEngine_replaceMarkerSet(swigCPtr, SimmMarkerSet.getCPtr(aMarkerSet));
  }

  public void updateMarkers(SimmMarkerSet aMarkerArray) {
    opensimModelJNI.SimmKinematicsEngine_updateMarkers(swigCPtr, SimmMarkerSet.getCPtr(aMarkerArray));
  }

  public void updateCoordinates(SimmCoordinateSet aCoordinateArray) {
    opensimModelJNI.SimmKinematicsEngine_updateCoordinates(swigCPtr, SimmCoordinateSet.getCPtr(aCoordinateArray));
  }

  public double takeMeasurement(SimmMeasurement aMeasurement) {
    return opensimModelJNI.SimmKinematicsEngine_takeMeasurement(swigCPtr, SimmMeasurement.getCPtr(aMeasurement));
  }

  public void writeSIMMJointFile(String aFileName) {
    opensimModelJNI.SimmKinematicsEngine_writeSIMMJointFile(swigCPtr, aFileName);
  }

  public void writeMarkerFile(String aFileName) {
    opensimModelJNI.SimmKinematicsEngine_writeMarkerFile(swigCPtr, aFileName);
  }

  public void peteTest() {
    opensimModelJNI.SimmKinematicsEngine_peteTest(swigCPtr);
  }

  public void getUnlockedCoordinates(SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmCoordinate_t aUnlockedCoordinates) {
    opensimModelJNI.SimmKinematicsEngine_getUnlockedCoordinates(swigCPtr, SWIGTYPE_p_OpenSim__ArrayPtrsTOpenSim__SimmCoordinate_t.getCPtr(aUnlockedCoordinates));
  }

  public SimmBody getBody(String aName) {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_getBody(swigCPtr, aName);
    return (cPtr == 0) ? null : new SimmBody(cPtr, false);
  }

  public Coordinate getCoordinate(String aName) {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_getCoordinate(swigCPtr, aName);
    return (cPtr == 0) ? null : new Coordinate(cPtr, false);
  }

  public SimmJoint getJoint(int index) {
    long cPtr = opensimModelJNI.SimmKinematicsEngine_getJoint(swigCPtr, index);
    return (cPtr == 0) ? null : new SimmJoint(cPtr, false);
  }

  public SimmBodySet getBodies() {
    return new SimmBodySet(opensimModelJNI.SimmKinematicsEngine_getBodies(swigCPtr), false);
  }

  public SimmCoordinateSet getCoordinates() {
    return new SimmCoordinateSet(opensimModelJNI.SimmKinematicsEngine_getCoordinates(swigCPtr), false);
  }

  public int getNumBodies() {
    return opensimModelJNI.SimmKinematicsEngine_getNumBodies(swigCPtr);
  }

  public int getNumJoints() {
    return opensimModelJNI.SimmKinematicsEngine_getNumJoints(swigCPtr);
  }

  public int getNumCoordinates() {
    return opensimModelJNI.SimmKinematicsEngine_getNumCoordinates(swigCPtr);
  }

  public int getNumSpeeds() {
    return opensimModelJNI.SimmKinematicsEngine_getNumSpeeds(swigCPtr);
  }

  public int getNumControls() {
    return opensimModelJNI.SimmKinematicsEngine_getNumControls(swigCPtr);
  }

  public int getNumContacts() {
    return opensimModelJNI.SimmKinematicsEngine_getNumContacts(swigCPtr);
  }

  public int getNumStates() {
    return opensimModelJNI.SimmKinematicsEngine_getNumStates(swigCPtr);
  }

  public int getNumPseudoStates() {
    return opensimModelJNI.SimmKinematicsEngine_getNumPseudoStates(swigCPtr);
  }

  public void setBodyName(int aIndex, String aName) {
    opensimModelJNI.SimmKinematicsEngine_setBodyName(swigCPtr, aIndex, aName);
  }

  public String getBodyName(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getBodyName(swigCPtr, aIndex);
  }

  public String getCoordinateName(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getCoordinateName(swigCPtr, aIndex);
  }

  public String getSpeedName(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getSpeedName(swigCPtr, aIndex);
  }

  public String getControlName(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getControlName(swigCPtr, aIndex);
  }

  public String getStateName(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getStateName(swigCPtr, aIndex);
  }

  public String getPseudoStateName(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getPseudoStateName(swigCPtr, aIndex);
  }

  public int getBodyIndex(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getBodyIndex(swigCPtr, aName);
  }

  public int getCoordinateIndex(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getCoordinateIndex(swigCPtr, aName);
  }

  public int getSpeedIndex(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getSpeedIndex(swigCPtr, aName);
  }

  public int getControlIndex(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getControlIndex(swigCPtr, aName);
  }

  public int getStateIndex(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getStateIndex(swigCPtr, aName);
  }

  public int getPseudoStateIndex(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getPseudoStateIndex(swigCPtr, aName);
  }

  public void set(double aT, double[] aX, double[] aY) {
    opensimModelJNI.SimmKinematicsEngine_set(swigCPtr, aT, aX, aY);
  }

  public void setInitialStates(double[] aYI) {
    opensimModelJNI.SimmKinematicsEngine_setInitialStates(swigCPtr, aYI);
  }

  public void getInitialStates(double[] rYI) {
    opensimModelJNI.SimmKinematicsEngine_getInitialStates(swigCPtr, rYI);
  }

  public double getInitialState(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getInitialState__SWIG_0(swigCPtr, aIndex);
  }

  public double getInitialState(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getInitialState__SWIG_1(swigCPtr, aName);
  }

  public void setStates(double[] aY) {
    opensimModelJNI.SimmKinematicsEngine_setStates(swigCPtr, aY);
  }

  public void getStates(double[] rY) {
    opensimModelJNI.SimmKinematicsEngine_getStates(swigCPtr, rY);
  }

  public double getState(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getState__SWIG_0(swigCPtr, aIndex);
  }

  public double getState(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getState__SWIG_1(swigCPtr, aName);
  }

  public void applyDefaultPose() {
    opensimModelJNI.SimmKinematicsEngine_applyDefaultPose(swigCPtr);
  }

  public void setInitialPseudoStates(double[] aYPI) {
    opensimModelJNI.SimmKinematicsEngine_setInitialPseudoStates(swigCPtr, aYPI);
  }

  public void getInitialPseudoStates(double[] rYPI) {
    opensimModelJNI.SimmKinematicsEngine_getInitialPseudoStates(swigCPtr, rYPI);
  }

  public double getInitialPseudoState(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getInitialPseudoState__SWIG_0(swigCPtr, aIndex);
  }

  public double getInitialPseudoState(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getInitialPseudoState__SWIG_1(swigCPtr, aName);
  }

  public void setPseudoStates(double[] aYP) {
    opensimModelJNI.SimmKinematicsEngine_setPseudoStates(swigCPtr, aYP);
  }

  public void getPseudoStates(double[] rYP) {
    opensimModelJNI.SimmKinematicsEngine_getPseudoStates(swigCPtr, rYP);
  }

  public double getPseudoState(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getPseudoState(swigCPtr, aIndex);
  }

  public void setConfiguration(double[] aY) {
    opensimModelJNI.SimmKinematicsEngine_setConfiguration__SWIG_0(swigCPtr, aY);
  }

  public void setConfiguration(double[] aQ, double[] aU) {
    opensimModelJNI.SimmKinematicsEngine_setConfiguration__SWIG_1(swigCPtr, aQ, aU);
  }

  public void getCoordinateValues(double[] rQ) {
    opensimModelJNI.SimmKinematicsEngine_getCoordinateValues(swigCPtr, rQ);
  }

  public double getCoordinateValue(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getCoordinateValue__SWIG_0(swigCPtr, aIndex);
  }

  public double getCoordinateValue(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getCoordinateValue__SWIG_1(swigCPtr, aName);
  }

  public void getSpeeds(double[] rU) {
    opensimModelJNI.SimmKinematicsEngine_getSpeeds(swigCPtr, rU);
  }

  public double getSpeed(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getSpeed__SWIG_0(swigCPtr, aIndex);
  }

  public double getSpeed(String aName) {
    return opensimModelJNI.SimmKinematicsEngine_getSpeed__SWIG_1(swigCPtr, aName);
  }

  public void getAccelerations(double[] rDUDT) {
    opensimModelJNI.SimmKinematicsEngine_getAccelerations(swigCPtr, rDUDT);
  }

  public double getAcceleration(int aIndex) {
    return opensimModelJNI.SimmKinematicsEngine_getAcceleration__SWIG_0(swigCPtr, aIndex);
  }

  public double getAcceleration(String aSpeedName) {
    return opensimModelJNI.SimmKinematicsEngine_getAcceleration__SWIG_1(swigCPtr, aSpeedName);
  }

  public void extractConfiguration(double[] aY, double[] rQ, double[] rU) {
    opensimModelJNI.SimmKinematicsEngine_extractConfiguration(swigCPtr, aY, rQ, rU);
  }

  public int assemble(double aTime, SWIGTYPE_p_double rState, SWIGTYPE_p_int aLock, double aTol, int aMaxevals, SWIGTYPE_p_int rFcnt, SWIGTYPE_p_int rErr) {
    return opensimModelJNI.SimmKinematicsEngine_assemble(swigCPtr, aTime, SWIGTYPE_p_double.getCPtr(rState), SWIGTYPE_p_int.getCPtr(aLock), aTol, aMaxevals, SWIGTYPE_p_int.getCPtr(rFcnt), SWIGTYPE_p_int.getCPtr(rErr));
  }

  public boolean scale(ScaleSet aScaleSet) {
    return opensimModelJNI.SimmKinematicsEngine_scale__SWIG_0(swigCPtr, ScaleSet.getCPtr(aScaleSet));
  }

  public boolean scale(ScaleSet aScaleSet, boolean aPreserveMassDist, double aFinalMass) {
    return opensimModelJNI.SimmKinematicsEngine_scale__SWIG_1(swigCPtr, ScaleSet.getCPtr(aScaleSet), aPreserveMassDist, aFinalMass);
  }

  public void getGravity(double[] rGrav) {
    opensimModelJNI.SimmKinematicsEngine_getGravity(swigCPtr, rGrav);
  }

  public void setGravity(double[] aGrav) {
    opensimModelJNI.SimmKinematicsEngine_setGravity(swigCPtr, aGrav);
  }

  public int getGroundBodyIndex() {
    return opensimModelJNI.SimmKinematicsEngine_getGroundBodyIndex(swigCPtr);
  }

  public void setBodyToJointBodyLocal(int aBody, double[] aBTJ) {
    opensimModelJNI.SimmKinematicsEngine_setBodyToJointBodyLocal(swigCPtr, aBody, aBTJ);
  }

  public void getBodyToJointBodyLocal(int aBody, double[] rBTJ) {
    opensimModelJNI.SimmKinematicsEngine_getBodyToJointBodyLocal(swigCPtr, aBody, rBTJ);
  }

  public void setInboardToJointBodyLocal(int aBody, double[] aBTJ) {
    opensimModelJNI.SimmKinematicsEngine_setInboardToJointBodyLocal(swigCPtr, aBody, aBTJ);
  }

  public void getInboardToJointBodyLocal(int aBody, double[] rBTJ) {
    opensimModelJNI.SimmKinematicsEngine_getInboardToJointBodyLocal(swigCPtr, aBody, rBTJ);
  }

  public double getMass() {
    return opensimModelJNI.SimmKinematicsEngine_getMass__SWIG_0(swigCPtr);
  }

  public double getMass(int aBody) {
    return opensimModelJNI.SimmKinematicsEngine_getMass__SWIG_1(swigCPtr, aBody);
  }

  public int getInertiaBodyLocal(int aBody, SWIGTYPE_p_a_3__double rI) {
    return opensimModelJNI.SimmKinematicsEngine_getInertiaBodyLocal__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_a_3__double.getCPtr(rI));
  }

  public int getInertiaBodyLocal(int aBody, SWIGTYPE_p_double rI) {
    return opensimModelJNI.SimmKinematicsEngine_getInertiaBodyLocal__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rI));
  }

  public void getSystemInertia(SWIGTYPE_p_double rM, double[] rCOM, SWIGTYPE_p_a_3__double rI) {
    opensimModelJNI.SimmKinematicsEngine_getSystemInertia__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(rM), rCOM, SWIGTYPE_p_a_3__double.getCPtr(rI));
  }

  public void getSystemInertia(SWIGTYPE_p_double rM, SWIGTYPE_p_double rCOM, SWIGTYPE_p_double rI) {
    opensimModelJNI.SimmKinematicsEngine_getSystemInertia__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(rM), SWIGTYPE_p_double.getCPtr(rCOM), SWIGTYPE_p_double.getCPtr(rI));
  }

  public void getPosition(int aBody, double[] aPoint, double[] rPos) {
    opensimModelJNI.SimmKinematicsEngine_getPosition(swigCPtr, aBody, aPoint, rPos);
  }

  public void getVelocity(int aBody, double[] aPoint, double[] rVel) {
    opensimModelJNI.SimmKinematicsEngine_getVelocity(swigCPtr, aBody, aPoint, rVel);
  }

  public void getAcceleration(int aBody, double[] aPoint, double[] rAcc) {
    opensimModelJNI.SimmKinematicsEngine_getAcceleration__SWIG_2(swigCPtr, aBody, aPoint, rAcc);
  }

  public void getDirectionCosines(int aBody, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimmKinematicsEngine_getDirectionCosines__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void getDirectionCosines(int aBody, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimmKinematicsEngine_getDirectionCosines__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void getAngularVelocity(int aBody, double[] rAngVel) {
    opensimModelJNI.SimmKinematicsEngine_getAngularVelocity(swigCPtr, aBody, rAngVel);
  }

  public void getAngularVelocityBodyLocal(int aBody, double[] rAngVel) {
    opensimModelJNI.SimmKinematicsEngine_getAngularVelocityBodyLocal(swigCPtr, aBody, rAngVel);
  }

  public void getAngularAcceleration(int aBody, double[] rAngAcc) {
    opensimModelJNI.SimmKinematicsEngine_getAngularAcceleration(swigCPtr, aBody, rAngAcc);
  }

  public void getAngularAccelerationBodyLocal(int aBody, double[] rAngAcc) {
    opensimModelJNI.SimmKinematicsEngine_getAngularAccelerationBodyLocal(swigCPtr, aBody, rAngAcc);
  }

  public void applyForce(int aBody, double[] aPoint, double[] aForce) {
    opensimModelJNI.SimmKinematicsEngine_applyForce(swigCPtr, aBody, aPoint, aForce);
  }

  public void applyForces(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aPoints, SWIGTYPE_p_a_3__double aForces) {
    opensimModelJNI.SimmKinematicsEngine_applyForces__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aPoints), SWIGTYPE_p_a_3__double.getCPtr(aForces));
  }

  public void applyForces(int aN, int[] aBodies, SWIGTYPE_p_double aPoints, SWIGTYPE_p_double aForces) {
    opensimModelJNI.SimmKinematicsEngine_applyForces__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aPoints), SWIGTYPE_p_double.getCPtr(aForces));
  }

  public void applyForceBodyLocal(int aBody, double[] aPoint, double[] aForce) {
    opensimModelJNI.SimmKinematicsEngine_applyForceBodyLocal(swigCPtr, aBody, aPoint, aForce);
  }

  public void applyForcesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aPoints, SWIGTYPE_p_a_3__double aForces) {
    opensimModelJNI.SimmKinematicsEngine_applyForcesBodyLocal__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aPoints), SWIGTYPE_p_a_3__double.getCPtr(aForces));
  }

  public void applyForcesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_double aPoints, SWIGTYPE_p_double aForces) {
    opensimModelJNI.SimmKinematicsEngine_applyForcesBodyLocal__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aPoints), SWIGTYPE_p_double.getCPtr(aForces));
  }

  public void applyTorque(int aBody, double[] aTorque) {
    opensimModelJNI.SimmKinematicsEngine_applyTorque(swigCPtr, aBody, aTorque);
  }

  public void applyTorques(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aTorques) {
    opensimModelJNI.SimmKinematicsEngine_applyTorques__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aTorques));
  }

  public void applyTorques(int aN, int[] aBodies, SWIGTYPE_p_double aTorques) {
    opensimModelJNI.SimmKinematicsEngine_applyTorques__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aTorques));
  }

  public void applyTorqueBodyLocal(int aBody, double[] aTorque) {
    opensimModelJNI.SimmKinematicsEngine_applyTorqueBodyLocal(swigCPtr, aBody, aTorque);
  }

  public void applyTorquesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_a_3__double aTorques) {
    opensimModelJNI.SimmKinematicsEngine_applyTorquesBodyLocal__SWIG_0(swigCPtr, aN, aBodies, SWIGTYPE_p_a_3__double.getCPtr(aTorques));
  }

  public void applyTorquesBodyLocal(int aN, int[] aBodies, SWIGTYPE_p_double aTorques) {
    opensimModelJNI.SimmKinematicsEngine_applyTorquesBodyLocal__SWIG_1(swigCPtr, aN, aBodies, SWIGTYPE_p_double.getCPtr(aTorques));
  }

  public void applyGeneralizedForce(int aU, double aF) {
    opensimModelJNI.SimmKinematicsEngine_applyGeneralizedForce(swigCPtr, aU, aF);
  }

  public void applyGeneralizedForces(double[] aF) {
    opensimModelJNI.SimmKinematicsEngine_applyGeneralizedForces__SWIG_0(swigCPtr, aF);
  }

  public void applyGeneralizedForces(int aN, int[] aU, double[] aF) {
    opensimModelJNI.SimmKinematicsEngine_applyGeneralizedForces__SWIG_1(swigCPtr, aN, aU, aF);
  }

  public double getNetAppliedGeneralizedForce(int aU) {
    return opensimModelJNI.SimmKinematicsEngine_getNetAppliedGeneralizedForce(swigCPtr, aU);
  }

  public void computeGeneralizedForces(double[] aDUDT, double[] rF) {
    opensimModelJNI.SimmKinematicsEngine_computeGeneralizedForces(swigCPtr, aDUDT, rF);
  }

  public void computeReactions(SWIGTYPE_p_a_3__double rForces, SWIGTYPE_p_a_3__double rTorques) {
    opensimModelJNI.SimmKinematicsEngine_computeReactions(swigCPtr, SWIGTYPE_p_a_3__double.getCPtr(rForces), SWIGTYPE_p_a_3__double.getCPtr(rTorques));
  }

  public void formMassMatrix(SWIGTYPE_p_double rI) {
    opensimModelJNI.SimmKinematicsEngine_formMassMatrix(swigCPtr, SWIGTYPE_p_double.getCPtr(rI));
  }

  public void formEulerTransform(int aBody, SWIGTYPE_p_double rE) {
    opensimModelJNI.SimmKinematicsEngine_formEulerTransform(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rE));
  }

  public void formJacobianTranslation(int aBody, double[] aPoint, SWIGTYPE_p_double rJ, int aRefBody) {
    opensimModelJNI.SimmKinematicsEngine_formJacobianTranslation__SWIG_0(swigCPtr, aBody, aPoint, SWIGTYPE_p_double.getCPtr(rJ), aRefBody);
  }

  public void formJacobianTranslation(int aBody, double[] aPoint, SWIGTYPE_p_double rJ) {
    opensimModelJNI.SimmKinematicsEngine_formJacobianTranslation__SWIG_1(swigCPtr, aBody, aPoint, SWIGTYPE_p_double.getCPtr(rJ));
  }

  public void formJacobianOrientation(int aBody, SWIGTYPE_p_double rJ0, int aRefBody) {
    opensimModelJNI.SimmKinematicsEngine_formJacobianOrientation__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJ0), aRefBody);
  }

  public void formJacobianOrientation(int aBody, SWIGTYPE_p_double rJ0) {
    opensimModelJNI.SimmKinematicsEngine_formJacobianOrientation__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJ0));
  }

  public void formJacobianEuler(int aBody, SWIGTYPE_p_double rJE, int aRefBody) {
    opensimModelJNI.SimmKinematicsEngine_formJacobianEuler__SWIG_0(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJE), aRefBody);
  }

  public void formJacobianEuler(int aBody, SWIGTYPE_p_double rJE) {
    opensimModelJNI.SimmKinematicsEngine_formJacobianEuler__SWIG_1(swigCPtr, aBody, SWIGTYPE_p_double.getCPtr(rJE));
  }

  public int computeAccelerations(SWIGTYPE_p_double dqdt, SWIGTYPE_p_double dudt) {
    return opensimModelJNI.SimmKinematicsEngine_computeAccelerations(swigCPtr, SWIGTYPE_p_double.getCPtr(dqdt), SWIGTYPE_p_double.getCPtr(dudt));
  }

  public void computeAuxiliaryDerivatives(SWIGTYPE_p_double dydt) {
    opensimModelJNI.SimmKinematicsEngine_computeAuxiliaryDerivatives(swigCPtr, SWIGTYPE_p_double.getCPtr(dydt));
  }

  public void transform(int aBody1, double[] aVec1, int aBody2, double[] rVec2) {
    opensimModelJNI.SimmKinematicsEngine_transform(swigCPtr, aBody1, aVec1, aBody2, rVec2);
  }

  public void transformPosition(int aBody, double[] aPos, double[] rPos) {
    opensimModelJNI.SimmKinematicsEngine_transformPosition(swigCPtr, aBody, aPos, rPos);
  }

  public void convertQuaternionsToAngles(SWIGTYPE_p_double aQ, SWIGTYPE_p_double rQAng) {
    opensimModelJNI.SimmKinematicsEngine_convertQuaternionsToAngles__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQ), SWIGTYPE_p_double.getCPtr(rQAng));
  }

  public void convertQuaternionsToAngles(Storage rQStore) {
    opensimModelJNI.SimmKinematicsEngine_convertQuaternionsToAngles__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertAnglesToQuaternions(SWIGTYPE_p_double aQAng, SWIGTYPE_p_double rQ) {
    opensimModelJNI.SimmKinematicsEngine_convertAnglesToQuaternions__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQAng), SWIGTYPE_p_double.getCPtr(rQ));
  }

  public void convertAnglesToQuaternions(Storage rQStore) {
    opensimModelJNI.SimmKinematicsEngine_convertAnglesToQuaternions__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertRadiansToDegrees(SWIGTYPE_p_double aQRad, SWIGTYPE_p_double rQDeg) {
    opensimModelJNI.SimmKinematicsEngine_convertRadiansToDegrees__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQRad), SWIGTYPE_p_double.getCPtr(rQDeg));
  }

  public void convertRadiansToDegrees(Storage rQStore) {
    opensimModelJNI.SimmKinematicsEngine_convertRadiansToDegrees__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertDegreesToRadians(SWIGTYPE_p_double aQDeg, SWIGTYPE_p_double rQRad) {
    opensimModelJNI.SimmKinematicsEngine_convertDegreesToRadians__SWIG_0(swigCPtr, SWIGTYPE_p_double.getCPtr(aQDeg), SWIGTYPE_p_double.getCPtr(rQRad));
  }

  public void convertDegreesToRadians(Storage rQStore) {
    opensimModelJNI.SimmKinematicsEngine_convertDegreesToRadians__SWIG_1(swigCPtr, Storage.getCPtr(rQStore));
  }

  public void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimmKinematicsEngine_convertAnglesToDirectionCosines__SWIG_0(swigCPtr, aE1, aE2, aE3, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimmKinematicsEngine_convertAnglesToDirectionCosines__SWIG_1(swigCPtr, aE1, aE2, aE3, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void convertDirectionCosinesToAngles(SWIGTYPE_p_a_3__double aDirCos, SWIGTYPE_p_double rE1, SWIGTYPE_p_double rE2, SWIGTYPE_p_double rE3) {
    opensimModelJNI.SimmKinematicsEngine_convertDirectionCosinesToAngles__SWIG_0(swigCPtr, SWIGTYPE_p_a_3__double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rE1), SWIGTYPE_p_double.getCPtr(rE2), SWIGTYPE_p_double.getCPtr(rE3));
  }

  public void convertDirectionCosinesToAngles(SWIGTYPE_p_double aDirCos, SWIGTYPE_p_double rE1, SWIGTYPE_p_double rE2, SWIGTYPE_p_double rE3) {
    opensimModelJNI.SimmKinematicsEngine_convertDirectionCosinesToAngles__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rE1), SWIGTYPE_p_double.getCPtr(rE2), SWIGTYPE_p_double.getCPtr(rE3));
  }

  public void convertDirectionCosinesToQuaternions(SWIGTYPE_p_a_3__double aDirCos, SWIGTYPE_p_double rQ1, SWIGTYPE_p_double rQ2, SWIGTYPE_p_double rQ3, SWIGTYPE_p_double rQ4) {
    opensimModelJNI.SimmKinematicsEngine_convertDirectionCosinesToQuaternions__SWIG_0(swigCPtr, SWIGTYPE_p_a_3__double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rQ1), SWIGTYPE_p_double.getCPtr(rQ2), SWIGTYPE_p_double.getCPtr(rQ3), SWIGTYPE_p_double.getCPtr(rQ4));
  }

  public void convertDirectionCosinesToQuaternions(SWIGTYPE_p_double aDirCos, SWIGTYPE_p_double rQ1, SWIGTYPE_p_double rQ2, SWIGTYPE_p_double rQ3, SWIGTYPE_p_double rQ4) {
    opensimModelJNI.SimmKinematicsEngine_convertDirectionCosinesToQuaternions__SWIG_1(swigCPtr, SWIGTYPE_p_double.getCPtr(aDirCos), SWIGTYPE_p_double.getCPtr(rQ1), SWIGTYPE_p_double.getCPtr(rQ2), SWIGTYPE_p_double.getCPtr(rQ3), SWIGTYPE_p_double.getCPtr(rQ4));
  }

  public void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimmKinematicsEngine_convertQuaternionsToDirectionCosines__SWIG_0(swigCPtr, aQ1, aQ2, aQ3, aQ4, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimmKinematicsEngine_convertQuaternionsToDirectionCosines__SWIG_1(swigCPtr, aQ1, aQ2, aQ3, aQ4, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void computeContact() {
    opensimModelJNI.SimmKinematicsEngine_computeContact(swigCPtr);
  }

  public void applyContactForce(int aID) {
    opensimModelJNI.SimmKinematicsEngine_applyContactForce(swigCPtr, aID);
  }

  public void applyContactForces() {
    opensimModelJNI.SimmKinematicsEngine_applyContactForces(swigCPtr);
  }

  public int getContactBodyA(int aID) {
    return opensimModelJNI.SimmKinematicsEngine_getContactBodyA(swigCPtr, aID);
  }

  public int getContactBodyB(int aID) {
    return opensimModelJNI.SimmKinematicsEngine_getContactBodyB(swigCPtr, aID);
  }

  public void setContactPointA(int aID, double[] aPoint) {
    opensimModelJNI.SimmKinematicsEngine_setContactPointA(swigCPtr, aID, aPoint);
  }

  public void getContactPointA(int aID, double[] rPoint) {
    opensimModelJNI.SimmKinematicsEngine_getContactPointA(swigCPtr, aID, rPoint);
  }

  public void setContactPointB(int aID, double[] aPoint) {
    opensimModelJNI.SimmKinematicsEngine_setContactPointB(swigCPtr, aID, aPoint);
  }

  public void getContactPointB(int aID, double[] rPoint) {
    opensimModelJNI.SimmKinematicsEngine_getContactPointB(swigCPtr, aID, rPoint);
  }

  public void getContactForce(int aID, double[] rF) {
    opensimModelJNI.SimmKinematicsEngine_getContactForce__SWIG_0(swigCPtr, aID, rF);
  }

  public void getContactNormalForce(int aID, double[] rFP, double[] rFV, double[] rF) {
    opensimModelJNI.SimmKinematicsEngine_getContactNormalForce(swigCPtr, aID, rFP, rFV, rF);
  }

  public void getContactTangentForce(int aID, double[] rFP, double[] rFV, double[] rF) {
    opensimModelJNI.SimmKinematicsEngine_getContactTangentForce(swigCPtr, aID, rFP, rFV, rF);
  }

  public void getContactStiffness(int aID, double[] aDX, double[] rDF) {
    opensimModelJNI.SimmKinematicsEngine_getContactStiffness(swigCPtr, aID, aDX, rDF);
  }

  public void getContactViscosity(int aID, double[] aDV, double[] rDF) {
    opensimModelJNI.SimmKinematicsEngine_getContactViscosity(swigCPtr, aID, aDV, rDF);
  }

  public void getContactFrictionCorrection(int aID, double[] aDFFric) {
    opensimModelJNI.SimmKinematicsEngine_getContactFrictionCorrection(swigCPtr, aID, aDFFric);
  }

  public double getContactForce(int aID) {
    return opensimModelJNI.SimmKinematicsEngine_getContactForce__SWIG_1(swigCPtr, aID);
  }

  public double getContactSpeed(int aID) {
    return opensimModelJNI.SimmKinematicsEngine_getContactSpeed(swigCPtr, aID);
  }

  public double getContactPower(int aID) {
    return opensimModelJNI.SimmKinematicsEngine_getContactPower(swigCPtr, aID);
  }

}
