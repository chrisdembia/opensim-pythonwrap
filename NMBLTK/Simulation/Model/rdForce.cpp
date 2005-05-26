// rdForce.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include "rdForce.h"


using namespace std;


//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 *
 * @todo There appears to be a memory leak when the control names are
 * allocated (_xNames) in rdForce.
 */
rdForce::~rdForce()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdForce::rdForce(int aBodyA,int aBodyB,int aNX,int aNY,int aNYP) :
	rdActuator(aNX,aNY,aNYP),
	_bA(_propBodyA.getValueInt()),
	_pA(_propPointA.getValueDblArray()),
	_uA(_propUnitVectorA.getValueDblArray()),
	_bB(_propBodyB.getValueInt()),
	_pB(_propPointB.getValueDblArray())
{
	// NULL
	setNull();

	// MEMBER DATA
	_bA = aBodyA;
	_bB = aBodyB;
}
//_____________________________________________________________________________
/**
 * Construct an actuator from file.
 *
 * @param aFileName Name of the file.
 */
rdForce::rdForce(DOMElement *aElement,int aNX,int aNY,int aNYP) :
	rdActuator(aNX,aNY,aNYP,aElement),
	_bA(_propBodyA.getValueInt()),
	_pA(_propPointA.getValueDblArray()),
	_uA(_propUnitVectorA.getValueDblArray()),
	_bB(_propBodyB.getValueInt()),
	_pB(_propPointB.getValueDblArray())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aForce Force to be copied.
 */
rdForce::rdForce(const rdForce &aForce) :
	rdActuator(aForce),
	_bA(_propBodyA.getValueInt()),
	_pA(_propPointA.getValueDblArray()),
	_uA(_propUnitVectorA.getValueDblArray()),
	_bB(_propBodyB.getValueInt()),
	_pB(_propPointB.getValueDblArray())
{
	setNull();
	*this = aForce;
}
//_____________________________________________________________________________
/**
 * Copy this actuator.  The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdForce::
copy() const
{
	rdForce *act = new rdForce(*this);
	return(act);
}
//_____________________________________________________________________________
/**
 * Copy this actuator and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * rdForce::rdForce(DOMElement*,int,int) in order to establish the
 * relationship of the rdForce object with the XML node.  Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this rdForce object.  Finally, the data members of the copy are
 * updated using rdForce::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* rdForce::
copy(DOMElement *aElement) const
{
	rdForce *act = new rdForce(aElement,getNX(),getNY());
	*act = *this;
	act->updateFromXMLNode();

	return(act);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdForce::
setNull()
{
	setupProperties();

	// TYPE
	setType("rdForce");

	// APPLIES FORCE
	setAppliesForce(true);

	// BODY A
	_bA = -1;
	_pA[0] = _pA[1] = _pA[2] = 0.0;
	_uA[0] = _uA[1] = _uA[2] = 0.0;  _uA[0] = 1.0;

	// BODY B
	_bB = -1;
	_pB[0] = _pB[1] = _pB[2] = 0.0;
	_uB[0] = _uB[1] = _uB[2] = 0.0;  _uB[0] = 1.0;

	//POINT FUNCTIONS
	_pAFunction = NULL;
	_pBFunction = NULL;

	//SCALE FACTOR
	_scaleFunction = NULL;
	_scaleFactor = 1.0;
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdForce::
setupProperties()
{
	double origin[3] = { 0.0, 0.0, 0.0 };
	double x_axis[3] = { 1.0, 0.0, 0.0 };

	_propBodyA.setName("body_A");
	_propBodyA.setValue(-1);
	_propertySet.append( &_propBodyA );

	_propPointA.setName("point_A");
	_propPointA.setValue(3,origin);
	_propertySet.append( &_propPointA );

	_propUnitVectorA.setName("direction_A");
	_propUnitVectorA.setValue(3,x_axis);
	_propertySet.append( &_propUnitVectorA );

	_propBodyB.setName("body_B");
	_propBodyB.setValue(-1);
	_propertySet.append( &_propBodyB );

	_propPointB.setName("point_B");
	_propPointB.setValue(3,origin);
	_propertySet.append( &_propPointB );
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
rdForce& rdForce::
operator=(const rdForce &aForce)
{
	// BASE CLASS
	rdActuator::operator=(aForce);

	// BODY A
	setBodyA(aForce.getBodyA());

	// POINT A
	aForce.getPointA(&_pA[0]);

	// DIRCTION A
	aForce.getForceDirectionA(&_uA[0]);

	// BODY B
	setBodyB(aForce.getBodyB());

	// POINT B
	aForce.getPointB(&_pB[0]);

	// DIRECTION B
	aForce.getForceDirectionB(_uB);

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// BODY A
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the id of the first body to which the force is applied.
 *
 * @param aID Body ID.
 */
void rdForce::
setBodyA(int aID)
{
	_bA = aID;
}
//_____________________________________________________________________________
/**
 * Get the id of the first body to which the force is applied.
 *
 * @param aID Body ID.
 */
int rdForce::
getBodyA() const
{
	return(_bA);
}

//-----------------------------------------------------------------------------
// POINT A
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of the point on BodyA at which the force is applied.
 *
 * @param aPoint Point x, y, and z values.
 */
void rdForce::
setPointA(const double aPoint[3])
{
	_pA[0] = aPoint[0];
	_pA[1] = aPoint[1];
	_pA[2] = aPoint[2];
}
//_____________________________________________________________________________
/**
 * Get the value of the point on BodyA at which the force is applied.
 *
 * @param rPoint Point x, y, and z values.
 */
void rdForce::
getPointA(double rPoint[3]) const
{
	rPoint[0] = _pA[0];
	rPoint[1] = _pA[1];
	rPoint[2] = _pA[2];
}
//_____________________________________________________________________________
/**
 * Set the vector function to read in values for Point A.
 *
 * @param aVectorFunction Vector function containing  x, y, and z values of
 * Point A (expressed in the body local frame) as a function fo time.
 */
void rdForce::
setPointAFunction(rdVectorFunction* aVectorFunction)
{
	_pAFunction = aVectorFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function to read in values for Point A.
 *
 * @param rVectorFunction Vector function containing  x, y, and z values of
 * Point A (expressed in the body local frame) as a function fo time.
 */
const rdVectorFunction* rdForce::
getPointAFunction() const
{
	return(_pAFunction);
}
//-----------------------------------------------------------------------------
// FORCE DIRECTION A
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the direction in which a positive actuator force is applied to BodyA.
 *
 * Newton's second law states that the force between
 * two bodies is equal and opposite in direction, so when the direction
 * of force on one body is known, the direction on the other body
 * can be calculated.  Therefore, the direction of force on BodyB is always
 * computed.
 *
 * @param aDirection Direction.  The direction is normalized.  If the
 * magnitude of aDirection is less than rdMath::ZERO, the force direction
 * is set to the zero vector, the effect of which is to prevent any force
 * from being applied.
 */
void rdForce::
setForceDirectionA(const double aDirection[3])
{
	double mag = rdMtx::Normalize(3,aDirection,&_uA[0]);
	if(mag==rdMath::ZERO) {
		printf("rdForce.setForceDirection: WARN- direction has a magnitude ");
		printf("of less than %lf.\n",rdMath::ZERO);
		printf("\tSetting the direction to (0,0,0).\n");
		_uA[0] = _uA[1] = _uA[2] = 0.0;
	}
}
//_____________________________________________________________________________
/**
 * Set the direction in which a positive actuator force is applied to BodyA.
 *
 * @param rPoint Point x, y, and z values.
 */
void rdForce::
getForceDirectionA(double rDirection[3]) const
{
	rDirection[0] = _uA[0];
	rDirection[1] = _uA[1];
	rDirection[2] = _uA[2];
}

//-----------------------------------------------------------------------------
// BODY B
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the id of the second body to which the force is applied.
 *
 * @param aID Body ID.
 */
void rdForce::
setBodyB(int aID)
{
	_bB = aID;
}
//_____________________________________________________________________________
/**
 * Get the id of the second body to which the force is applied.
 *
 * @param aID Body ID.
 */
int rdForce::
getBodyB() const
{
	return(_bB);
}

//-----------------------------------------------------------------------------
// POINT B
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the value of the point on BodyB at which the force is applied.
 *
 * @param aPoint Point x, y, and z values.
 */
void rdForce::
setPointB(const double aPoint[3])
{
	_pB[0] = aPoint[0];
	_pB[1] = aPoint[1];
	_pB[2] = aPoint[2];
}
//_____________________________________________________________________________
/**
 * Get the value of the point on BodyB at which the force is applied.
 *
 * @param rPoint Point x, y, and z values.
 */
void rdForce::
getPointB(double rPoint[3]) const
{
	rPoint[0] = _pB[0];
	rPoint[1] = _pB[1];
	rPoint[2] = _pB[2];
}
//_____________________________________________________________________________
/**
 * Set the vector function to read in values for Point B.
 *
 * @param aVectorFunction Vector function containing  x, y, and z values of
 * Point B (expressed in the body local frame) as a function fo time.
 */
void rdForce::
setPointBFunction(rdVectorFunction* aVectorFunction)
{
	_pBFunction = aVectorFunction;
}
//_____________________________________________________________________________
/**
 * Get the vector function to read in values for Point B.
 *
 * @param rVectorFunction Vector function containing  x, y, and z values of
 * Point B (expressed in the body local frame) as a function fo time.
 */
const rdVectorFunction* rdForce::
getPointBFunction() const
{
	return(_pBFunction);
}

//-----------------------------------------------------------------------------
// FORCE DIRECTION B
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the direction in which a positive actuator force is applied to BodyB.
 *
 * Note that the direction of force application on BodyB cannot be set; it is
 * always computed based on the force direction set for BodyA.
 *
 * @param rPoint Point x, y, and z values.
 */
void rdForce::
getForceDirectionB(double rDirection[3]) const
{
	rDirection[0] = _uB[0];
	rDirection[1] = _uB[1];
	rDirection[2] = _uB[2];
}

//-----------------------------------------------------------------------------
// SCALE FACTOR FUNCTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the function containing the scale factor as a function of time.
 *
 * @param aScaleFunction.
 */
void rdForce::
setScaleFunction(rdFunction* aScaleFunction)
{
	_scaleFunction = aScaleFunction;
}
//_____________________________________________________________________________
/**
 * Get the function containing the scale factor as a function of time.
 *
 * @return aScaleFunction.
 */
rdFunction* rdForce::
getScaleFunction() const
{
	return(_scaleFunction);
}

//-----------------------------------------------------------------------------
// SCALE FACTOR
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the scale factor that pre-multiplies the applied force.
 *
 * @param aScaleFactor
 */
void rdForce::
setScaleFactor(double aScaleFactor)
{
	_scaleFactor = aScaleFactor;
}
//_____________________________________________________________________________
/**
 * Get the scale factor that pre-multiplies the applied force.
 *
 * @return aScaleFactor.
 */
double rdForce::
getScaleFactor()
{
	return(_scaleFactor);
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute all quantities necessary for applying the actuator force to the
 * model.
 */
void rdForce::
computeActuation()
{
	// DIRECTION
	computeForceDirectionForBodyB();

	// SPEED
	computeSpeed();

	// FORCE
	double force = getControl(0) * getOptimalForce();
	setForce(force);
}
//_____________________________________________________________________________
/**
 * Compute the force direction for BodyB based on the force direction set
 * for BodyA.
 */
void rdForce::
computeForceDirectionForBodyB()
{
	_model->transform(_bA,&_uA[0],_bB,_uB);
	rdMtx::Multiply(1,3,_uB,-1.0,_uB);
}
//_____________________________________________________________________________
/**
 * Compute the speed of the actuator.
 */
void rdForce::
computeSpeed()
{
	double vA[3],vB[3],v[3];
	_model->getVelocity(_bA,&_pA[0],vA);
	_model->getVelocity(_bA,&_pB[0],vB);
	rdMtx::Subtract(1,3,vB,vA,v);
	_model->transform(_model->getGroundID(),v,_bA,v);
	_speed = -rdMtx::DotProduct(3,&_uA[0],v);
}
//_____________________________________________________________________________
/**
 * Update the position of PointA.  That is, if it has been specified by a read
 * in function, set the current position to be that in the function.
 */
void rdForce::
updatePointA()
{
	double time = _model->getTime()*_model->getTimeNormConstant();
	if(_pAFunction !=NULL)
		_pA = _pAFunction->evaluate(time);
}
//_____________________________________________________________________________
/**
 * Update the position of PointB.  That is, if it has been specified by a read
 * in function, set the current position to be that in the function.
 */
void rdForce::
updatePointB()
{
	double time = _model->getTime()*_model->getTimeNormConstant();
	if(_pBFunction !=NULL)
	_pB = _pBFunction->evaluate(time);
}

//=============================================================================
// APPLICATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Apply the actuator force to BodyA and BodyB.
 */
void rdForce::
apply()
{
	// SET SCALE FACTOR
	double scaleFactor;
	if(_scaleFunction!=NULL) {
		scaleFactor = _scaleFunction->evaluate(0,_model->getTime()*_model->getTimeNormConstant());
		setScaleFactor(scaleFactor);
	}
	
	// FORCE ON BODY A
	if(_bA!=_model->getGroundID()) {
		double fA[3];
		rdMtx::Multiply(1,3,&_uA[0],_force,fA);
		rdMtx::Multiply(1,3,fA,_scaleFactor,fA);
		_model->applyForceBodyLocal(_bA,&_pA[0],fA);
	}

	// FORCE ON BODY B
	if(_bB!=_model->getGroundID()) {
		double fB[3];
		rdMtx::Multiply(1,3,_uB,_force,fB);
		rdMtx::Multiply(1,3,fB,_scaleFactor,fB);
		_model->applyForceBodyLocal(_bB,&_pB[0],fB);
	}
}


//=============================================================================
// CHECK
//=============================================================================
//_____________________________________________________________________________
/**
 * Check that this force actuator has a valid set of states.
 */
bool rdForce::
check() const
{
	rdActuator::check();

	// BODY A
	if(_model!=NULL) {
		if((getBodyA()<_model->getGroundID())||(getBodyA()>=_model->getNB())) {
			printf("rdForce.check: ERROR- %s has invalid body for BodyA (%d).\n",
				getName().c_str(),getBodyA());
			return(false);
		}
	}

	// BODY B
	if(_model!=NULL) {
		if((getBodyB()<_model->getGroundID())||(getBodyB()>=_model->getNB())) {
			printf("rdForce.check: ERROR- %s has invalid body for BodyB (%d).\n",
				getName().c_str(),getBodyB());
			return(false);
		}
	}

	// SAME BODY
	if(getBodyA()==getBodyB()) {
		printf("rdForce.check: WARN- %s has the same body for BodyA and BodyB\n",
			getName().c_str());
	}

	return(true);
}


//=============================================================================
// UTILITY
//=============================================================================
//-----------------------------------------------------------------------------
// LINE OF ACTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the vector directed from the point of force application on 
 * BodyA to the point of force application on BodyB expressed in the
 * local frame of BodyA.
 *
 * @param rLineOfAction Line of action expressed in the local frame of BodyA.
 * @todo Check that the line of action is expressed in the proper frame.
 */
void rdForce::
computeLineOfAction(double rLineOfAction[3]) const
{
	if(rLineOfAction==NULL) return;
	if(_model==NULL) {
		printf("rdForce.computeLineOfAction: ERROR- no model.\n");
		return;
	}

	// GET INERTIAL POSITONS
	double pB[3],pA[3];
	_model->getPosition(_bB,&_pB[0],pB);
	_model->getPosition(_bA,&_pA[0],pA);

	// SUBTRACT
	rdMtx::Subtract(1,3,pB,pA,rLineOfAction);

	// TRANSFORM
	int ground = _model->getGroundID();
	_model->transform(ground,rLineOfAction,_bA,rLineOfAction);
}

