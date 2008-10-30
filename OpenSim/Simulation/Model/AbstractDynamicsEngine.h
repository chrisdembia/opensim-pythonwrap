#ifndef __AbstractDynamicsEngine_h__
#define __AbstractDynamicsEngine_h__

// AbstractDynamicsEngine.h
// Authors: Frank C. Anderson, Peter Loan, Ayman Habib
/*
 * Copyright (c)  2006, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// INCLUDES
#include <OpenSim/Simulation/osimSimulationDLL.h>
#include <iostream>
#include <string>
#include <OpenSim/Common/PropertyObj.h>
#include <OpenSim/Common/PropertyDblVec3.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/Object.h>
#include <OpenSim/Simulation/Model/JointSet.h>
#include <OpenSim/Simulation/Model/CoordinateSet.h>
#include <OpenSim/Simulation/Model/SpeedSet.h>
#include <OpenSim/Simulation/Model/ConstraintSet.h>

namespace OpenSim {

class ScaleSet;
class BodySet;
class ConstraintSet;
class Model;
class AbstractBody;
class AbstractJoint;
class AbstractCoordinate;
class AbstractSpeed;
class AbstractTransformAxis;
class AbstractMarker;
class MarkerSet;
class Transform;
class Storage;
class AbstractWrapObject;

#ifdef SWIG
	#ifdef OSIMSIMULATION_API
		#undef OSIMSIMULATION_API
		#define OSIMSIMULATION_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * An abstract class that specifies the interface for a kinematics or
 * dynamics engine. A kinematics engine is used to compute the positions,
 * velocities, and accelerations of bodies and points on bodies in an
 * aticulated linkage. A dynamics engine does everything a kinematics
 * engine does, plus can be used to apply forces to the bodies and
 * compute the resulting motion.
 *
 * At a minimum, a kinematics engine must contain a description of the
 * topology of the articulated linkage.  That is, how many bodies and how
 * those bodies are connected.
 *
 * @author Frank C. Anderson, Peter Loan, Ayman Habib
 * @version 1.0
 */
class OSIMSIMULATION_API AbstractDynamicsEngine : public Object
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Pointer to the model that owns this dynamics engine. */
	Model* _model;

	/** Array containg the acceleration due to gravity. */
	PropertyDblVec3 _gravityProp;
	SimTK::Vec3 &_gravity;

	/** Set containing the bodies in this model. */
	PropertyObj _bodySetProp;
	BodySet &_bodySet;

	/** Set containing the constraints in this model. */
	PropertyObj _constraintSetProp;
	ConstraintSet &_constraintSet;

	/** Set of markers for this model. */
	PropertyObj _markerSetProp;
	MarkerSet &_markerSet;

	/** Set containing the joints in this model. */
	// 2008_06_06: No longer a property because the joints are kept
	// local to the bodies in the Simbody Dynamics Engine.
	// For the SIMM and SDFast engines to continue to work, the properties
	// must be moved local to those classes.
	// The strategy now is to get OpenSim working with the Simbody engine
	// as quickly as possible.
	JointSet _jointSet;

	/** Set containing the generalized coordinates in this model. */
	// 2008_06_06: No longer a property because the coordinates are kept
	// local to the joints in the Simbody Dynamics Engine.
	// For the SIMM and SDFast engines to continue to work, the properties
	// must be moved local to those classes.
	// The strategy now is to get OpenSim working with the Simbody engine
	// as quickly as possible.
	CoordinateSet _coordinateSet;

	/** Set containing the generalized speeds in this model. */
	// 2008_06_06: No longer a property because the speeds are generated
	// from the coordinates, which are kept local to the joints.
	// For the SIMM and SDFast engines to continue to work, the properties
	// must be moved local to those classes.
	// The strategy now is to get OpenSim working with the Simbody engine
	// as quickly as possible.
	SpeedSet _speedSet;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION AND DESTRUCTION
	//--------------------------------------------------------------------------
public:
	AbstractDynamicsEngine();
	AbstractDynamicsEngine(const std::string &aFileName, bool aUpdateFromXMLNode = true);
	virtual ~AbstractDynamicsEngine();
	virtual Object* copy() const = 0;

	//_____________________________________________________________________________
	/**
	 * Perform set up functions after model has been read from file or copied.
	 *
	 * @param aModel model containing this dynamics engine.
	 */
	virtual void setup(Model* aModel);

protected:
	AbstractDynamicsEngine(const AbstractDynamicsEngine& aDE);
#ifndef SWIG
	AbstractDynamicsEngine& operator=(const AbstractDynamicsEngine &aDE);
#endif
	void setNull();

	/**
	 * Connect properties to local pointers.
	 */
	void setupProperties();

	/**
	 * Copy data members from one AbstractDynamicsEngine to another.
	 * @param aEngine AbstractDynamicsEngine to be copied.
	 */
	void copyData(const AbstractDynamicsEngine& aEngine);

public:

	//--------------------------------------------------------------------------
	// NUMBERS
	//--------------------------------------------------------------------------
	virtual int getNumBodies() const;
	virtual int getNumJoints() const;
	virtual int getNumConstraints() const;
	virtual int getNumCoordinates() const;
	virtual int getNumSpeeds() const;
	virtual int getNumMarkers() const;

	//--------------------------------------------------------------------------
	// MODEL
	//--------------------------------------------------------------------------
	const Model* getModel() const { return _model; }
	Model* getModel() { return _model; }
	void setModel(Model* aModel) { _model = aModel; }
	//--------------------------------------------------------------------------
	// GRAVITY
	//--------------------------------------------------------------------------
	virtual void getGravity(SimTK::Vec3& rGrav) const;
	virtual bool setGravity(const SimTK::Vec3& aGrav);

	//--------------------------------------------------------------------------
	// BODIES
	//--------------------------------------------------------------------------
	virtual BodySet* getBodySet() { return &_bodySet; }
#ifndef SWIG
	virtual const BodySet* getBodySet() const { return &_bodySet; }
#endif
	virtual AbstractBody& getGroundBody() const = 0;
	virtual AbstractBody* getLeafBody(AbstractJoint* aJoint) const { return NULL; }
	virtual AbstractWrapObject* getWrapObject(const std::string& aName) const;

	//--------------------------------------------------------------------------
	// JOINTS
	//--------------------------------------------------------------------------
	virtual JointSet* getJointSet() { return &_jointSet; }
#ifndef SWIG
	virtual const JointSet* getJointSet() const { return &_jointSet; }
#endif
	
	//--------------------------------------------------------------------------
	// COORDINATES
	//--------------------------------------------------------------------------
	virtual CoordinateSet* getCoordinateSet() { return &_coordinateSet; }
#ifndef SWIG
	virtual const CoordinateSet* getCoordinateSet() const { return &_coordinateSet; }
#endif
	virtual void updateCoordinateSet(CoordinateSet& aCoordinateSet) = 0;
	virtual void getUnlockedCoordinates(CoordinateSet& aUnlockedCoordinates) const = 0;
	virtual AbstractTransformAxis* findUnconstrainedDof(const AbstractCoordinate& aCoordinate, AbstractJoint*& rJoint) = 0;

	//--------------------------------------------------------------------------
	// CONSTRAINTS
	//--------------------------------------------------------------------------
	virtual ConstraintSet* getConstraintSet() { return &_constraintSet; }
#ifndef SWIG
	virtual const ConstraintSet* getConstraintSet() const { return &_constraintSet; }
#endif

	//--------------------------------------------------------------------------
	// SPEEDS
	//--------------------------------------------------------------------------
	virtual SpeedSet* getSpeedSet() { return &_speedSet; }
#ifndef SWIG
	virtual const SpeedSet* getSpeedSet() const { return &_speedSet; }
#endif

	//--------------------------------------------------------------------------
	// MARKERS
	//--------------------------------------------------------------------------
	virtual MarkerSet* getMarkerSet() { return &_markerSet; }
#ifndef SWIG
	virtual const MarkerSet* getMarkerSet() const { return &_markerSet; }
#endif
	virtual void writeMarkerFile(const std::string& aFileName) const;
	virtual int replaceMarkerSet(MarkerSet& aMarkerSet);
	virtual void updateMarkerSet(MarkerSet& aMarkerSet);
	virtual int deleteUnusedMarkers(const Array<std::string>& aMarkerNames);

	//--------------------------------------------------------------------------
	// CONFIGURATION
	//--------------------------------------------------------------------------
	/**
	 * Set the configuration (cooridnates and speeds) of the model.
	 * @param aY Array of coordinates followed by the speeds.
	 */
	virtual void setConfiguration(const double aY[]) = 0;
	virtual void getConfiguration(double rY[]) const = 0;

	/**
	 * Set the configuration (cooridnates and speeds) of the model.
	 * @param aQ Array of generalized coordinates.
	 * @param aU Array of generalized speeds.
	 */
	virtual void setConfiguration(const double aQ[],const double aU[]) = 0;
	virtual void getConfiguration(double rQ[],double rU[]) const = 0;
	virtual void getCoordinates(double rQ[]) const = 0;
	virtual void getSpeeds(double rU[]) const = 0;

	/**
	* PROJECT configuration to satisfy constaints and return the projected configuration
	*/
	virtual bool projectConfigurationToSatisfyConstraints(double uY[], const double cTol, double uYerr[]=0) =0;

	/**
	 * Get the last-computed values of the accelerations of the generalized
	 * coordinates.  For the values to be valid, the method
	 * computeDerivatives() must have been called.
	 *
	 * @param rDUDT Array to be filled with values of the accelerations of the
	 * generalized coordinates.  The length of rDUDT should be at least as large
	 * as the value returned by getNumSpeeds().
	 * @see computeDerivatives()
	 */
	virtual void getAccelerations(double rDUDT[]) const = 0;

	/**
	 * Extract the generalized coordinates and speeds from a combined array of
	 * the coordinates and speeds.  This is only a utility method.  The
	 * configuration of the model is not changed.
	 * @param aY Array of coordinates followed by the speeds.
	 * @param rQ Array of coordinates taken from aY. 
	 * @param rU Array of speeds taken from aY.
	 */
	virtual void extractConfiguration(const double aY[],double rQ[],double rU[]) const = 0;

	/**
	 * Extract the configuration (coordinates and speeds) of a model from the states.
	 * @param aYStore Storage object containing a complete set of model states.
	 * @param rQStore Storage object containing the coordinates held in aYStore.
	 * @param rUStore Storage object containing the speeds held in aYStore.
	 */
	virtual void extractConfiguration(const Storage &aYStore,Storage &rQStore,Storage &rUStore);
	virtual void applyDefaultConfiguration() = 0;

	//--------------------------------------------------------------------------
	// ASSEMBLING THE MODEL
	//--------------------------------------------------------------------------
	virtual int
		assemble(double aTime,double *rState,int *aLock,double aTol,
		int aMaxevals,int *rFcnt,int *rErr) = 0;

	//virtual	void init(Model* aModel) = 0;
 
	//--------------------------------------------------------------------------
	// SCALING
	//--------------------------------------------------------------------------
	virtual bool scale(const ScaleSet& aScaleSet, double aFinalMass = -1.0, bool aPreserveMassDist = false);

	//--------------------------------------------------------------------------
	// INERTIA
	//--------------------------------------------------------------------------
	virtual double getMass() const = 0;

	/**
	 * Return the total system inertial properties
	 * @param rM, total system mass
	 * @param rCOM, location of the system center of mass in ground
	 * @param rI, the effective total system intertia tensor 
	 */
	virtual void getSystemInertia(double *rM, SimTK::Vec3& rCOM, double rI[3][3]) const = 0;
	virtual void getSystemInertia(double *rM, double *rCOM, double *rI) const = 0;

	//--------------------------------------------------------------------------
	// KINEMATICS
	//--------------------------------------------------------------------------
	/**
	 * Get the inertial position of a point on a body.
	 * Note that the configuration of the model must be set before calling this
	 * method.
	 * @param aBody Pointer to body.
	 * @param aPoint Point on the body expressed in the body-local frame.
	 * @param rPos Position of the point in the inertial frame.
	 * @see setConfiguration()
	 */	
	virtual void getPosition(const AbstractBody &aBody, const SimTK::Vec3& aPoint, SimTK::Vec3& rPos) const = 0;

	/**
	 * Get the inertial velocity of a point on a body.
	 * Note that the configuration of the model must be set before calling this
	 * method.
	 * @param aBody Pointer to body.
	 * @param aPoint Point on the body expressed in the body-local frame.
	 * @param rVel Velocity of the point in the inertial frame.
	 * @see setConfiguration()
	 */
	virtual void getVelocity(const AbstractBody &aBody, const SimTK::Vec3& aPoint, SimTK::Vec3& rVel) const = 0;

	/**
	* Get the inertial acceleration of a point on a body.
	* Note that the configuration of the model must be set and accelerations of
	* the generalized coordinates must be computed before calling this method.
	* @param aBody Pointer to body.
	* @param aPoint Point on the body expressed in the body-local frame.
	* @param rAcc Acceleration of the point in the inertial frame.
	*
	* @see setConfiguration()
	* @see computeDerivatives()
	*/
	virtual void getAcceleration(const AbstractBody &aBody, const SimTK::Vec3& aPoint, SimTK::Vec3& rAcc) const = 0;

	/**
	 * Get the body orientation (rotation matrix) with respect to the ground.
	 * @param aBody Pointer to body.
	 * @param rDirCos Orientation (matrix) of the body with respect to the ground frame.
	 */
	virtual void getDirectionCosines(const AbstractBody &aBody, double rDirCos[3][3]) const = 0;
	virtual void getDirectionCosines(const AbstractBody &aBody, double *rDirCos) const = 0;

	/**
	 * Get the inertial angular velocity of a body in the ground reference frame.
	 * @param aBody Pointer to body.
	 * @param rAngVel Angular velocity of the body.
	 */
	virtual void getAngularVelocity(const AbstractBody &aBody, SimTK::Vec3& rAngVel) const = 0;
	virtual void getAngularVelocityBodyLocal(const AbstractBody &aBody, SimTK::Vec3& rAngVel) const = 0;

	/**
	 * Get the inertial angular acceleration of a body in the ground reference 
	 * frame. Note that the system acceleration must be realized by calling
	 * computeDerivatives() first.
	 *
	 * @param aBody Pointer to body.
	 * @param rAngAcc Angular acceleration of the body.
	 * @see computeDerivatives()
	 */
	virtual void getAngularAcceleration(const AbstractBody &aBody, SimTK::Vec3& rAngAcc) const = 0;
	virtual void getAngularAccelerationBodyLocal(const AbstractBody &aBody, SimTK::Vec3& rAngAcc) const = 0;
	virtual Transform getTransform(const AbstractBody &aBody) = 0;

	//--------------------------------------------------------------------------
	// LOAD APPLICATION
	//--------------------------------------------------------------------------
	// FORCES EXPRESSED IN INERTIAL FRAME
	virtual void applyForce(const AbstractBody &aBody, const SimTK::Vec3& aPoint, const SimTK::Vec3& aForce) = 0;
	virtual void applyForces(int aN, const AbstractBody *aBodies[], const double aPoints[][3], const double aForces[][3]) = 0;
	virtual void applyForces(int aN, const AbstractBody *aBodies[], const double *aPoints, const double *aForces) = 0;

	// FORCES EXPRESSED IN BODY-LOCAL FRAME
	virtual void applyForceBodyLocal(const AbstractBody &aBody, const SimTK::Vec3& aPoint, const SimTK::Vec3& aForce) = 0;
	virtual void applyForcesBodyLocal(int aN, const AbstractBody *aBodies[], const double aPoints[][3], const double aForces[][3]) = 0;
	virtual void applyForcesBodyLocal(int aN, const AbstractBody *aBodies[], const double *aPoints, const double *aForces) = 0;

	// TORQUES EXPRESSED IN INERTIAL FRAME
	virtual void applyTorque(const AbstractBody &aBody, const SimTK::Vec3& aTorque) = 0;
	virtual void applyTorques(int aN, const AbstractBody *aBodies[], const double aTorques[][3]) = 0;
	virtual void applyTorques(int aN, const AbstractBody *aBodies[], const double *aTorques) = 0;

	// TORQUES EXPRESSED IN BODY-LOCAL FRAME
	virtual void applyTorqueBodyLocal(const AbstractBody &aBody, const SimTK::Vec3& aTorque) = 0;
	virtual void applyTorquesBodyLocal(int aN, const AbstractBody *aBodies[], const double aTorques[][3]) = 0;
	virtual void applyTorquesBodyLocal(int aN, const AbstractBody *aBodies[], const double *aTorques) = 0;

	// GENERALIZED FORCES
	virtual void applyGeneralizedForce(const AbstractCoordinate &aU, double aF) = 0;
	virtual void applyGeneralizedForces(const double aF[]) = 0;
	virtual void applyGeneralizedForces(int aN, const AbstractCoordinate *aU[], const double aF[]) = 0;

	//--------------------------------------------------------------------------
	// LOAD ACCESS AND COMPUTATION
	//--------------------------------------------------------------------------
	virtual double getNetAppliedGeneralizedForce(const AbstractCoordinate &aU) const = 0;
	virtual void computeGeneralizedForces(double aDUDT[], double rF[]) const = 0;
	virtual void computeReactions(SimTK::Vector_<SimTK::Vec3>& rForces, SimTK::Vector_<SimTK::Vec3>& rTorques) const = 0;

	//--------------------------------------------------------------------------
	// CONSTRAINTS
	//--------------------------------------------------------------------------
	virtual void computeConstrainedCoordinates(double rQ[]) const = 0;
	virtual void formCompleteStorages(const OpenSim::Storage &aQIn,
		OpenSim::Storage *&rQComplete,OpenSim::Storage *&rUComplete) const;

	//--------------------------------------------------------------------------
	// EQUATIONS OF MOTION
	//--------------------------------------------------------------------------
	virtual void formMassMatrix(double *rI) = 0;
	virtual void formEulerTransform(const AbstractBody &aBody, double *rE) const = 0;
	virtual void formJacobianTranslation(const AbstractBody &aBody, const SimTK::Vec3& aPoint, double *rJ, const AbstractBody *aRefBody=NULL) const = 0;
	virtual void formJacobianOrientation(const AbstractBody &aBody, double *rJ0, const AbstractBody *aRefBody=NULL) const = 0;
	virtual void formJacobianEuler(const AbstractBody &aBody, double *rJE, const AbstractBody *aRefBody=NULL) const = 0;

	//--------------------------------------------------------------------------
	// DERIVATIVES/ACCELERATIONS
	//--------------------------------------------------------------------------
	/**
	 * Compute the derivatives of the generalized coordinates and speeds.
	 * The configuration must be set and all all forces applied for this
	 * method to return valid accelerations.
	 * @param dqdt Derivatives of generalized coordinates.
	 * @param dudt Derivatives of generalized speeds (accelerations).
	 */
	virtual void computeDerivatives(double *dqdt, double *dudt) = 0;

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	virtual void transform(const AbstractBody &aBodyFrom,const double aVec[3],const AbstractBody &aBodyTo,double rVec[3]) const = 0;
	virtual void transform(const AbstractBody &aBodyFrom,const SimTK::Vec3& aVec,const AbstractBody &aBodyTo,SimTK::Vec3& rVec) const = 0;
	virtual void transformPosition(const AbstractBody &aBodyFrom, const double aPos[3], const AbstractBody &aBodyTo, double rPos[3]) const = 0;
	virtual void transformPosition(const AbstractBody &aBodyFrom, const SimTK::Vec3& aPos, const AbstractBody &aBodyTo, SimTK::Vec3& rPos) const = 0;
	virtual void transformPosition(const AbstractBody &aBodyFrom, const double aPos[3], double rPos[3]) const = 0;
	virtual void transformPosition(const AbstractBody &aBodyFrom, const SimTK::Vec3& aPos, SimTK::Vec3& rPos) const = 0;

	virtual double calcDistance(const AbstractBody &aBody1, const double aPoint1[3], const AbstractBody &aBody2, const double aPoint2[3]) const = 0;
	virtual double calcDistance(const AbstractBody &aBody1, const SimTK::Vec3& aPoint1, const AbstractBody &aBody2, const SimTK::Vec3& aPoint2) const = 0;

	virtual void convertQuaternionsToAngles(double *aQ, double *rQAng) const = 0;
	virtual void convertQuaternionsToAngles(Storage *rQStore) const = 0;
	virtual void convertAnglesToQuaternions(double *aQAng, double *rQ) const = 0;
	virtual void convertAnglesToQuaternions(Storage *rQStore) const = 0;

	void convertRadiansToDegrees(Storage &rStorage) const;
	void convertDegreesToRadians(Storage &rStorage) const;
	void convertDegreesToRadians(double *aQDeg, double *rQRad) const;
	void convertRadiansToDegrees(double *aQRad, double *rQDeg) const;

	virtual void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, double rDirCos[3][3]) const = 0;
	virtual void convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, double *rDirCos) const = 0;

	/**
	 * Convert direction cosines to angles.
	 * @param aDirCos Vector of direction cosines.
	 * @param rE1 1st Euler angle.
	 * @param rE2 2nd Euler angle.
	 * @param rE3 3rd Euler angle.
	 */
	virtual void convertDirectionCosinesToAngles(double aDirCos[3][3], double *rE1, double *rE2, double *rE3) const = 0;
	virtual void convertDirectionCosinesToAngles(double *aDirCos, double *rE1, double *rE2, double *rE3) const = 0;

	virtual void convertDirectionCosinesToQuaternions(double aDirCos[3][3],	double *rQ1, double *rQ2, double *rQ3, double *rQ4) const = 0;
	virtual void convertDirectionCosinesToQuaternions(double *aDirCos, double *rQ1, double *rQ2, double *rQ3, double *rQ4) const = 0;

	virtual void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, double rDirCos[3][3]) const = 0;
	virtual void convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, double *rDirCos) const = 0;

private:
	void scaleRotationalDofColumns(Storage &rStorage, double factor) const;
//=============================================================================
};	// END of class AbstractDynamicsEngine
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __AbstractDynamicsEngine_h__


