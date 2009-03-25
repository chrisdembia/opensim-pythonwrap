/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opensim.modeling;

public class SimbodyEngine extends AbstractDynamicsEngine {
  private long swigCPtr;

  public SimbodyEngine(long cPtr, boolean cMemoryOwn) {
    super(opensimModelJNI.SWIGStorageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SimbodyEngine obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      opensimModelJNI.delete_SimbodyEngine(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
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

  public OpenSimObject copy() {
    long cPtr = opensimModelJNI.SimbodyEngine_copy__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new OpenSimObject(cPtr, false);
  }

  public void migrateFromPreviousVersion(OpenSimObject aPreviousVersion) {
    opensimModelJNI.SimbodyEngine_migrateFromPreviousVersion(swigCPtr, this, OpenSimObject.getCPtr(aPreviousVersion), aPreviousVersion);
  }

  public static void registerTypes() {
    opensimModelJNI.SimbodyEngine_registerTypes();
  }

  public void setup(Model aModel) {
    opensimModelJNI.SimbodyEngine_setup(swigCPtr, this, Model.getCPtr(aModel), aModel);
  }

  public void setInvalid() {
    opensimModelJNI.SimbodyEngine_setInvalid(swigCPtr, this);
  }

  public boolean isInvalid() {
    return opensimModelJNI.SimbodyEngine_isInvalid(swigCPtr, this);
  }

  public boolean setGravity(SWIGTYPE_p_SimTK__Vec3 aGrav) {
    return opensimModelJNI.SimbodyEngine_setGravity(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(aGrav));
  }

  public void getGravity(SWIGTYPE_p_SimTK__Vec3 rGrav) {
    opensimModelJNI.SimbodyEngine_getGravity(swigCPtr, this, SWIGTYPE_p_SimTK__Vec3.getCPtr(rGrav));
  }

  public void addBody(Body aBody) {
    opensimModelJNI.SimbodyEngine_addBody(swigCPtr, this, Body.getCPtr(aBody), aBody);
  }

  public void addJoint(SWIGTYPE_p_OpenSim__Joint aJoint) {
    opensimModelJNI.SimbodyEngine_addJoint(swigCPtr, this, SWIGTYPE_p_OpenSim__Joint.getCPtr(aJoint));
  }

  public void addCoordinate(SWIGTYPE_p_OpenSim__Coordinate aCoord) {
    opensimModelJNI.SimbodyEngine_addCoordinate(swigCPtr, this, SWIGTYPE_p_OpenSim__Coordinate.getCPtr(aCoord));
  }

  public void addSpeed(SWIGTYPE_p_Speed aSpeed) {
    opensimModelJNI.SimbodyEngine_addSpeed(swigCPtr, this, SWIGTYPE_p_Speed.getCPtr(aSpeed));
  }

  public void updateCoordinateSet(CoordinateSet aCoordinateSet) {
    opensimModelJNI.SimbodyEngine_updateCoordinateSet(swigCPtr, this, CoordinateSet.getCPtr(aCoordinateSet), aCoordinateSet);
  }

  public void getUnlockedCoordinates(CoordinateSet rUnlockedCoordinates) {
    opensimModelJNI.SimbodyEngine_getUnlockedCoordinates(swigCPtr, this, CoordinateSet.getCPtr(rUnlockedCoordinates), rUnlockedCoordinates);
  }

  public AbstractTransformAxis findUnconstrainedDof(AbstractCoordinate aCoordinate, AbstractJoint rJoint) {
    long cPtr = opensimModelJNI.SimbodyEngine_findUnconstrainedDof(swigCPtr, this, AbstractCoordinate.getCPtr(aCoordinate), aCoordinate, AbstractJoint.getCPtr(rJoint));
    return (cPtr == 0) ? null : new AbstractTransformAxis(cPtr, false);
  }

  public JointSet getJointSet() {
    long cPtr = opensimModelJNI.SimbodyEngine_getJointSet(swigCPtr, this);
    return (cPtr == 0) ? null : new JointSet(cPtr, false);
  }

  public void setTime(double aTime) {
    opensimModelJNI.SimbodyEngine_setTime(swigCPtr, this, aTime);
  }

  public void setConfiguration(double[] aY) {
    opensimModelJNI.SimbodyEngine_setConfiguration__SWIG_0(swigCPtr, this, aY);
  }

  public void getConfiguration(double[] rY) {
    opensimModelJNI.SimbodyEngine_getConfiguration__SWIG_0(swigCPtr, this, rY);
  }

  public void setConfiguration(double[] aQ, double[] aU) {
    opensimModelJNI.SimbodyEngine_setConfiguration__SWIG_1(swigCPtr, this, aQ, aU);
  }

  public void getConfiguration(double[] rQ, double[] rU) {
    opensimModelJNI.SimbodyEngine_getConfiguration__SWIG_1(swigCPtr, this, rQ, rU);
  }

  public void getCoordinates(double[] rQ) {
    opensimModelJNI.SimbodyEngine_getCoordinates(swigCPtr, this, rQ);
  }

  public void getSpeeds(double[] rU) {
    opensimModelJNI.SimbodyEngine_getSpeeds(swigCPtr, this, rU);
  }

  public void getAccelerations(double[] rDUDT) {
    opensimModelJNI.SimbodyEngine_getAccelerations(swigCPtr, this, rDUDT);
  }

  public void extractConfiguration(double[] aY, double[] rQ, double[] rU) {
    opensimModelJNI.SimbodyEngine_extractConfiguration(swigCPtr, this, aY, rQ, rU);
  }

  public void applyDefaultConfiguration() {
    opensimModelJNI.SimbodyEngine_applyDefaultConfiguration(swigCPtr, this);
  }

  public boolean projectConfigurationToSatisfyConstraints(double[] uY, double cTol, double[] uYerr) {
    return opensimModelJNI.SimbodyEngine_projectConfigurationToSatisfyConstraints__SWIG_0(swigCPtr, this, uY, cTol, uYerr);
  }

  public boolean projectConfigurationToSatisfyConstraints(double[] uY, double cTol) {
    return opensimModelJNI.SimbodyEngine_projectConfigurationToSatisfyConstraints__SWIG_1(swigCPtr, this, uY, cTol);
  }

  public int assemble(double aTime, SWIGTYPE_p_double rState, SWIGTYPE_p_int aLock, double aTol, int aMaxevals, SWIGTYPE_p_int rFcnt, SWIGTYPE_p_int rErr) {
    return opensimModelJNI.SimbodyEngine_assemble(swigCPtr, this, aTime, SWIGTYPE_p_double.getCPtr(rState), SWIGTYPE_p_int.getCPtr(aLock), aTol, aMaxevals, SWIGTYPE_p_int.getCPtr(rFcnt), SWIGTYPE_p_int.getCPtr(rErr));
  }

  public boolean scale(ScaleSet aScaleSet, double aFinalMass, boolean aPreserveMassDist) {
    return opensimModelJNI.SimbodyEngine_scale__SWIG_0(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet, aFinalMass, aPreserveMassDist);
  }

  public boolean scale(ScaleSet aScaleSet, double aFinalMass) {
    return opensimModelJNI.SimbodyEngine_scale__SWIG_1(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet, aFinalMass);
  }

  public boolean scale(ScaleSet aScaleSet) {
    return opensimModelJNI.SimbodyEngine_scale__SWIG_2(swigCPtr, this, ScaleSet.getCPtr(aScaleSet), aScaleSet);
  }

  public AbstractBody getGroundBody() {
    return new AbstractBody(opensimModelJNI.SimbodyEngine_getGroundBody(swigCPtr, this), false);
  }

  public AbstractBody getLeafBody(AbstractJoint aJoint) {
    long cPtr = opensimModelJNI.SimbodyEngine_getLeafBody(swigCPtr, this, AbstractJoint.getCPtr(aJoint), aJoint);
    return (cPtr == 0) ? null : new AbstractBody(cPtr, false);
  }

  public boolean adjustJointVectorsForNewMassCenter(Body aBody) {
    return opensimModelJNI.SimbodyEngine_adjustJointVectorsForNewMassCenter(swigCPtr, this, Body.getCPtr(aBody), aBody);
  }

  public double getMass() {
    return opensimModelJNI.SimbodyEngine_getMass(swigCPtr, this);
  }

  public void getSystemInertia(SWIGTYPE_p_double rM, SWIGTYPE_p_SimTK__Vec3 rCOM, SWIGTYPE_p_a_3__double rI) {
    opensimModelJNI.SimbodyEngine_getSystemInertia__SWIG_0(swigCPtr, this, SWIGTYPE_p_double.getCPtr(rM), SWIGTYPE_p_SimTK__Vec3.getCPtr(rCOM), SWIGTYPE_p_a_3__double.getCPtr(rI));
  }

  public void getSystemInertia(SWIGTYPE_p_double rM, SWIGTYPE_p_double rCOM, SWIGTYPE_p_double rI) {
    opensimModelJNI.SimbodyEngine_getSystemInertia__SWIG_1(swigCPtr, this, SWIGTYPE_p_double.getCPtr(rM), SWIGTYPE_p_double.getCPtr(rCOM), SWIGTYPE_p_double.getCPtr(rI));
  }

  public void updateBodyInertia(AbstractBody aBody) {
    opensimModelJNI.SimbodyEngine_updateBodyInertia(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody);
  }

  public void getPosition(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_SimTK__Vec3 rPos) {
    opensimModelJNI.SimbodyEngine_getPosition(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_SimTK__Vec3.getCPtr(rPos));
  }

  public void getVelocity(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_SimTK__Vec3 rVel) {
    opensimModelJNI.SimbodyEngine_getVelocity(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_SimTK__Vec3.getCPtr(rVel));
  }

  public void getAcceleration(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_SimTK__Vec3 rAcc) {
    opensimModelJNI.SimbodyEngine_getAcceleration(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_SimTK__Vec3.getCPtr(rAcc));
  }

  public void getDirectionCosines(AbstractBody aBody, SWIGTYPE_p_a_3__double rDirCos) {
    opensimModelJNI.SimbodyEngine_getDirectionCosines__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_a_3__double.getCPtr(rDirCos));
  }

  public void getDirectionCosines(AbstractBody aBody, SWIGTYPE_p_double rDirCos) {
    opensimModelJNI.SimbodyEngine_getDirectionCosines__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_double.getCPtr(rDirCos));
  }

  public void getAngularVelocity(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 rAngVel) {
    opensimModelJNI.SimbodyEngine_getAngularVelocity(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(rAngVel));
  }

  public void getAngularVelocityBodyLocal(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 rAngVel) {
    opensimModelJNI.SimbodyEngine_getAngularVelocityBodyLocal(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(rAngVel));
  }

  public void getAngularAcceleration(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 rAngAcc) {
    opensimModelJNI.SimbodyEngine_getAngularAcceleration(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(rAngAcc));
  }

  public void getAngularAccelerationBodyLocal(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 rAngAcc) {
    opensimModelJNI.SimbodyEngine_getAngularAccelerationBodyLocal(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(rAngAcc));
  }

  public Transform getTransform(AbstractBody aBody) {
    return new Transform(opensimModelJNI.SimbodyEngine_getTransform(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody), true);
  }

  public void applyForce(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_SimTK__Vec3 aForce) {
    opensimModelJNI.SimbodyEngine_applyForce(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_SimTK__Vec3.getCPtr(aForce));
  }

  public void applyForces(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_a_3__double aPoints, SWIGTYPE_p_a_3__double aForces) {
    opensimModelJNI.SimbodyEngine_applyForces__SWIG_0(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_a_3__double.getCPtr(aPoints), SWIGTYPE_p_a_3__double.getCPtr(aForces));
  }

  public void applyForces(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_double aPoints, SWIGTYPE_p_double aForces) {
    opensimModelJNI.SimbodyEngine_applyForces__SWIG_1(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_double.getCPtr(aPoints), SWIGTYPE_p_double.getCPtr(aForces));
  }

  public void applyForceBodyLocal(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_SimTK__Vec3 aForce) {
    opensimModelJNI.SimbodyEngine_applyForceBodyLocal(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_SimTK__Vec3.getCPtr(aForce));
  }

  public void applyForcesBodyLocal(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_a_3__double aPoints, SWIGTYPE_p_a_3__double aForces) {
    opensimModelJNI.SimbodyEngine_applyForcesBodyLocal__SWIG_0(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_a_3__double.getCPtr(aPoints), SWIGTYPE_p_a_3__double.getCPtr(aForces));
  }

  public void applyForcesBodyLocal(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_double aPoints, SWIGTYPE_p_double aForces) {
    opensimModelJNI.SimbodyEngine_applyForcesBodyLocal__SWIG_1(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_double.getCPtr(aPoints), SWIGTYPE_p_double.getCPtr(aForces));
  }

  public void applyTorque(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aTorque) {
    opensimModelJNI.SimbodyEngine_applyTorque(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aTorque));
  }

  public void applyTorques(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_a_3__double aTorques) {
    opensimModelJNI.SimbodyEngine_applyTorques__SWIG_0(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_a_3__double.getCPtr(aTorques));
  }

  public void applyTorques(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_double aTorques) {
    opensimModelJNI.SimbodyEngine_applyTorques__SWIG_1(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_double.getCPtr(aTorques));
  }

  public void applyTorqueBodyLocal(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aTorque) {
    opensimModelJNI.SimbodyEngine_applyTorqueBodyLocal(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aTorque));
  }

  public void applyTorquesBodyLocal(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_a_3__double aTorques) {
    opensimModelJNI.SimbodyEngine_applyTorquesBodyLocal__SWIG_0(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_a_3__double.getCPtr(aTorques));
  }

  public void applyTorquesBodyLocal(int aN, SWIGTYPE_p_p_OpenSim__AbstractBody aBodies, SWIGTYPE_p_double aTorques) {
    opensimModelJNI.SimbodyEngine_applyTorquesBodyLocal__SWIG_1(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractBody.getCPtr(aBodies), SWIGTYPE_p_double.getCPtr(aTorques));
  }

  public void applyGeneralizedForce(AbstractCoordinate aU, double aF) {
    opensimModelJNI.SimbodyEngine_applyGeneralizedForce(swigCPtr, this, AbstractCoordinate.getCPtr(aU), aU, aF);
  }

  public void applyGeneralizedForces(double[] aF) {
    opensimModelJNI.SimbodyEngine_applyGeneralizedForces__SWIG_0(swigCPtr, this, aF);
  }

  public void applyGeneralizedForces(int aN, SWIGTYPE_p_p_OpenSim__AbstractCoordinate aU, double[] aF) {
    opensimModelJNI.SimbodyEngine_applyGeneralizedForces__SWIG_1(swigCPtr, this, aN, SWIGTYPE_p_p_OpenSim__AbstractCoordinate.getCPtr(aU), aF);
  }

  public double getNetAppliedGeneralizedForce(AbstractCoordinate aU) {
    return opensimModelJNI.SimbodyEngine_getNetAppliedGeneralizedForce(swigCPtr, this, AbstractCoordinate.getCPtr(aU), aU);
  }

  public void computeGeneralizedForces(double[] aDUDT, double[] rF) {
    opensimModelJNI.SimbodyEngine_computeGeneralizedForces(swigCPtr, this, aDUDT, rF);
  }

  public void computeReactions(SWIGTYPE_p_SimTK__Vector_TSimTK__Vec3_t rForces, SWIGTYPE_p_SimTK__Vector_TSimTK__Vec3_t rTorques) {
    opensimModelJNI.SimbodyEngine_computeReactions(swigCPtr, this, SWIGTYPE_p_SimTK__Vector_TSimTK__Vec3_t.getCPtr(rForces), SWIGTYPE_p_SimTK__Vector_TSimTK__Vec3_t.getCPtr(rTorques));
  }

  public void computeConstrainedCoordinates(double[] rQ) {
    opensimModelJNI.SimbodyEngine_computeConstrainedCoordinates(swigCPtr, this, rQ);
  }

  public void formMassMatrix(SWIGTYPE_p_double rI) {
    opensimModelJNI.SimbodyEngine_formMassMatrix(swigCPtr, this, SWIGTYPE_p_double.getCPtr(rI));
  }

  public void formEulerTransform(AbstractBody aBody, SWIGTYPE_p_double rE) {
    opensimModelJNI.SimbodyEngine_formEulerTransform(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_double.getCPtr(rE));
  }

  public void formJacobianTranslation(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_double rJ, AbstractBody aRefBody) {
    opensimModelJNI.SimbodyEngine_formJacobianTranslation__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_double.getCPtr(rJ), AbstractBody.getCPtr(aRefBody), aRefBody);
  }

  public void formJacobianTranslation(AbstractBody aBody, SWIGTYPE_p_SimTK__Vec3 aPoint, SWIGTYPE_p_double rJ) {
    opensimModelJNI.SimbodyEngine_formJacobianTranslation__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint), SWIGTYPE_p_double.getCPtr(rJ));
  }

  public void formJacobianOrientation(AbstractBody aBody, SWIGTYPE_p_double rJ0, AbstractBody aRefBody) {
    opensimModelJNI.SimbodyEngine_formJacobianOrientation__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_double.getCPtr(rJ0), AbstractBody.getCPtr(aRefBody), aRefBody);
  }

  public void formJacobianOrientation(AbstractBody aBody, SWIGTYPE_p_double rJ0) {
    opensimModelJNI.SimbodyEngine_formJacobianOrientation__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_double.getCPtr(rJ0));
  }

  public void formJacobianEuler(AbstractBody aBody, SWIGTYPE_p_double rJE, AbstractBody aRefBody) {
    opensimModelJNI.SimbodyEngine_formJacobianEuler__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_double.getCPtr(rJE), AbstractBody.getCPtr(aRefBody), aRefBody);
  }

  public void formJacobianEuler(AbstractBody aBody, SWIGTYPE_p_double rJE) {
    opensimModelJNI.SimbodyEngine_formJacobianEuler__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBody), aBody, SWIGTYPE_p_double.getCPtr(rJE));
  }

  public void computeDerivatives(SWIGTYPE_p_double dqdt, SWIGTYPE_p_double dudt) {
    opensimModelJNI.SimbodyEngine_computeDerivatives(swigCPtr, this, SWIGTYPE_p_double.getCPtr(dqdt), SWIGTYPE_p_double.getCPtr(dudt));
  }

  public void dumpState() {
    opensimModelJNI.SimbodyEngine_dumpState(swigCPtr, this);
  }

  public void transform(AbstractBody aBodyFrom, double[] aVec, AbstractBody aBodyTo, double[] rVec) {
    opensimModelJNI.SimbodyEngine_transform__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBodyFrom), aBodyFrom, aVec, AbstractBody.getCPtr(aBodyTo), aBodyTo, rVec);
  }

  public void transform(AbstractBody aBodyFrom, SWIGTYPE_p_SimTK__Vec3 aVec, AbstractBody aBodyTo, SWIGTYPE_p_SimTK__Vec3 rVec) {
    opensimModelJNI.SimbodyEngine_transform__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBodyFrom), aBodyFrom, SWIGTYPE_p_SimTK__Vec3.getCPtr(aVec), AbstractBody.getCPtr(aBodyTo), aBodyTo, SWIGTYPE_p_SimTK__Vec3.getCPtr(rVec));
  }

  public void transformPosition(AbstractBody aBodyFrom, double[] aPos, AbstractBody aBodyTo, double[] rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBodyFrom), aBodyFrom, aPos, AbstractBody.getCPtr(aBodyTo), aBodyTo, rPos);
  }

  public void transformPosition(AbstractBody aBodyFrom, SWIGTYPE_p_SimTK__Vec3 aPos, AbstractBody aBodyTo, SWIGTYPE_p_SimTK__Vec3 rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBodyFrom), aBodyFrom, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPos), AbstractBody.getCPtr(aBodyTo), aBodyTo, SWIGTYPE_p_SimTK__Vec3.getCPtr(rPos));
  }

  public void transformPosition(AbstractBody aBodyFrom, double[] aPos, double[] rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_2(swigCPtr, this, AbstractBody.getCPtr(aBodyFrom), aBodyFrom, aPos, rPos);
  }

  public void transformPosition(AbstractBody aBodyFrom, SWIGTYPE_p_SimTK__Vec3 aPos, SWIGTYPE_p_SimTK__Vec3 rPos) {
    opensimModelJNI.SimbodyEngine_transformPosition__SWIG_3(swigCPtr, this, AbstractBody.getCPtr(aBodyFrom), aBodyFrom, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPos), SWIGTYPE_p_SimTK__Vec3.getCPtr(rPos));
  }

  public double calcDistance(AbstractBody aBody1, double[] aPoint1, AbstractBody aBody2, double[] aPoint2) {
    return opensimModelJNI.SimbodyEngine_calcDistance__SWIG_0(swigCPtr, this, AbstractBody.getCPtr(aBody1), aBody1, aPoint1, AbstractBody.getCPtr(aBody2), aBody2, aPoint2);
  }

  public double calcDistance(AbstractBody aBody1, SWIGTYPE_p_SimTK__Vec3 aPoint1, AbstractBody aBody2, SWIGTYPE_p_SimTK__Vec3 aPoint2) {
    return opensimModelJNI.SimbodyEngine_calcDistance__SWIG_1(swigCPtr, this, AbstractBody.getCPtr(aBody1), aBody1, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint1), AbstractBody.getCPtr(aBody2), aBody2, SWIGTYPE_p_SimTK__Vec3.getCPtr(aPoint2));
  }

  public void convertQuaternionsToAngles(SWIGTYPE_p_double aQ, SWIGTYPE_p_double rQAng) {
    opensimModelJNI.SimbodyEngine_convertQuaternionsToAngles__SWIG_0(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aQ), SWIGTYPE_p_double.getCPtr(rQAng));
  }

  public void convertQuaternionsToAngles(Storage rQStore) {
    opensimModelJNI.SimbodyEngine_convertQuaternionsToAngles__SWIG_1(swigCPtr, this, Storage.getCPtr(rQStore), rQStore);
  }

  public void convertAnglesToQuaternions(SWIGTYPE_p_double aQAng, SWIGTYPE_p_double rQ) {
    opensimModelJNI.SimbodyEngine_convertAnglesToQuaternions__SWIG_0(swigCPtr, this, SWIGTYPE_p_double.getCPtr(aQAng), SWIGTYPE_p_double.getCPtr(rQ));
  }

  public void convertAnglesToQuaternions(Storage rQStore) {
    opensimModelJNI.SimbodyEngine_convertAnglesToQuaternions__SWIG_1(swigCPtr, this, Storage.getCPtr(rQStore), rQStore);
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

  public void resizeBodyAndMobilityForceVectors() {
    opensimModelJNI.SimbodyEngine_resizeBodyAndMobilityForceVectors(swigCPtr, this);
  }

  public void resetBodyAndMobilityForceVectors() {
    opensimModelJNI.SimbodyEngine_resetBodyAndMobilityForceVectors(swigCPtr, this);
  }

  public SWIGTYPE_p_SimTK__Vector_TSimTK__SpatialVec_t getBodyForces() {
    return new SWIGTYPE_p_SimTK__Vector_TSimTK__SpatialVec_t(opensimModelJNI.SimbodyEngine_getBodyForces(swigCPtr, this), false);
  }

  public SWIGTYPE_p_SimTK__Vector getMobilityForces() {
    return new SWIGTYPE_p_SimTK__Vector(opensimModelJNI.SimbodyEngine_getMobilityForces(swigCPtr, this), false);
  }

  public static boolean isKindOf(String type) {
    return opensimModelJNI.SimbodyEngine_isKindOf(type);
  }

  public boolean isA(String type) {
    return opensimModelJNI.SimbodyEngine_isA(swigCPtr, this, type);
  }

  public static SimbodyEngine safeDownCast(OpenSimObject obj) {
    long cPtr = opensimModelJNI.SimbodyEngine_safeDownCast(OpenSimObject.getCPtr(obj), obj);
    return (cPtr == 0) ? null : new SimbodyEngine(cPtr, false);
  }

  public void copy(OpenSimObject aObject) {
    opensimModelJNI.SimbodyEngine_copy__SWIG_1(swigCPtr, this, OpenSimObject.getCPtr(aObject), aObject);
  }

}
