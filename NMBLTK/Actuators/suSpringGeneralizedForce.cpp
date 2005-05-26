// suSpringGeneralizedForce.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHORS:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include "suSpringGeneralizedForce.h"


using namespace std;


//=============================================================================
// STATICS
//=============================================================================
const string suSpringGeneralizedForce::X_NAME = "stiffness";

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suSpringGeneralizedForce::~suSpringGeneralizedForce()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
suSpringGeneralizedForce::
suSpringGeneralizedForce(int aQID,int aNX,int aNY,int aNYP) :
	rdGeneralizedForce(aQID,aNX,aNY,aNYP),
	_restLength(_propRestLength.getValueDbl()),
	_viscosity(_propViscosity.getValueDbl())
{
	// NULL
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct the actuator from an XML Element.
 *
 * @param aElement XML element.
 * @param aNX Number of controls.
 * @param aNY Number of states.
 * @param aNYP Number of pseudo-states.
 */
suSpringGeneralizedForce::
suSpringGeneralizedForce(DOMElement *aElement,int aNX,int aNY,int aNYP):
	rdGeneralizedForce(aElement,aNX,aNY,aNYP),
	_restLength(_propRestLength.getValueDbl()),
	_viscosity(_propViscosity.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aActuator Actuator to be copied.
 */
suSpringGeneralizedForce::
suSpringGeneralizedForce(const suSpringGeneralizedForce &aActuator) :
	rdGeneralizedForce(aActuator),
	_restLength(_propRestLength.getValueDbl()),
	_viscosity(_propViscosity.getValueDbl())
{
	setNull();

	// MEMBER VARIABLES
	setRestLength(aActuator.getRestLength());
	setViscosity(aActuator.getViscosity());
}

//_____________________________________________________________________________
/**
 * Copy this actuator and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this actuator.
 */
rdObject* suSpringGeneralizedForce::
copy() const
{
	rdActuator *act = new suSpringGeneralizedForce(*this);
	return(act);
}
//_____________________________________________________________________________
/**
 * Copy this actuator and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * rdG::rdForce(DOMElement*,int,int) in order to establish the
 * relationship of the rdForce object with the XML node.  Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this rdForce object.  Finally, the data members of the copy are
 * updated using rdForce::updateObject().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this actuator.
 */
rdObject* suSpringGeneralizedForce::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	suSpringGeneralizedForce *act = new
		suSpringGeneralizedForce(aElement,getNX(),getNY(),getNYP());

	// ASSIGNMENT OPERATOR
	*act = *this;

	// UPDATE BASED ON NODE
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
void suSpringGeneralizedForce::
setNull()
{
	setType("suSpringGeneralizedForce");
	setupProperties();

	// APPLIES FORCE
	_appliesForce = true;

	// CONTROL VALUES
	_restLength = 0.0;
	_viscosity = 0.0;
	_stiffness = 0.0;
}

//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void suSpringGeneralizedForce::
setupProperties()
{
	_propRestLength.setName("rest_length");
	_propRestLength.setValue(0.0);
	_propertySet.append( &_propRestLength );

	_propViscosity.setName("viscosity");
	_propViscosity.setValue(0.0);
	_propertySet.append( &_propViscosity );
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
 * @return  Reference to the altered object.
 */
suSpringGeneralizedForce& suSpringGeneralizedForce::
operator=(const suSpringGeneralizedForce &aActuator)
{
	// BASE CLASS
	rdGeneralizedForce::operator =(aActuator);

	// MEMBER VARIABLES
	setRestLength(aActuator.getRestLength());
	setViscosity(aActuator.getViscosity());

	return(*this);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// CONTROLS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of controls.
 *
 * @return Number of controls (1 for an rdGeneralizedForce actuator).
 */
int suSpringGeneralizedForce::
getNX() const
{
	return(1);
}
//_____________________________________________________________________________
/**
 * Get the name of a control.\n
 * Valid indices: 0
 *
 * @param aIndex Index of the control whose name is desired.
 * @throws rdException If aIndex is not valid.
 */
const string suSpringGeneralizedForce::
getControlName(int aIndex) const
{
	if(aIndex!=0) {
		string msg = "suSpringGeneralizedForce.setControl: ERR- index out of bounds.\n";
		msg += "Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has only 1 control (only an index of 0 is valid).";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	string name = getName();
	name += ".";
	name += X_NAME;
	return(name);
}
//_____________________________________________________________________________
/**
 * Get the index of a control of a specified name.\n
 * Valid names: x
 *
 * @param aName Name of the control whose index is desired.
 * @return Index of the specified control.
 * @throws rdException If aName is not valid.
 */
int suSpringGeneralizedForce::
getControlIndex(const string &aName) const
{
	if(aName!=getControlName(0)) {
		string msg = "suSpringGeneralizedForce.getControlIndex: ERR- Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has no control by the name";
		msg += aName;
		msg += ".\nThe only valid control name is ";
		msg += getControlName(0);
		msg += ".";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	return(0);
}
//_____________________________________________________________________________
/**
 * Set the current values of the controls.  This actuator has one control:
 * the force mangnitude of the actuator.
 *
 * @param aX Array of control values.  aX should be at least a size of 1.
 */
void suSpringGeneralizedForce::
setControls(const double aX[])
{
	setStiffness(aX[0]);
}
//_____________________________________________________________________________
/**
 * Set the value of a control at a specified index.\n
 * Valid indices:  0
 *
 * @param aIndex Index of the control to be set.
 * @param aValue Value to which to set the control.
 * @throws rdException If aIndex is not valid.
 */
void suSpringGeneralizedForce::
setControl(int aIndex,double aValue)
{
	if(aIndex!=0) {
		string msg = "suSpringGeneralizedForce.setControl: ERR- index out of bounds.\n";
		msg += "Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has only 1 control (only an index of 0 is valid).";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	setStiffness(aValue);
}
//_____________________________________________________________________________
/**
 * Set the value of a control of a specified name.\n
 * Valid names: x
 *
 * @param aName Name of the control to be set.
 * @param aValue Value to which to set the control.
 * @throws rdException If aName is not valid.
 */
void suSpringGeneralizedForce::
setControl(const string &aName,double aValue)
{
	int index = getControlIndex(aName);
	setControl(index,aValue);
}
//_____________________________________________________________________________
/**
 * Get the current values of the controls.
 *
 * @param rX Array of control values.  The size of rX should be at least 1.
 */
void suSpringGeneralizedForce::
getControls(double rX[]) const
{
	rX[0] = getStiffness();
}
//_____________________________________________________________________________
/**
 * Get the value of a control at a specified index.\n
 *	Valid Indices: 0
 *
 * @param aIndex Index of the desired control.
 * @return Value of the desired control.
 * @throws rdException If aIndex is not valid.
 */
double suSpringGeneralizedForce::
getControl(int aIndex) const
{
	if(aIndex!=0) {
		string msg = "suSpringGeneralizedForce.setControl: ERR- index out of bounds.\n";
		msg += "Actuator ";
		msg += getName();
		msg += " of type ";
		msg += getType();
		msg += " has only 1 control (only an index of 0 is valid).";
		throw( rdException(msg,__FILE__,__LINE__) );
	}
	return(getStiffness());
}
//_____________________________________________________________________________
/**
 * Get the value of a control of a specified name.\n
 * Valid names: x
 *
 * @param aName Name of the desired control.
 * @return Value of the desired control.
 * @throws rdException If aName is not valid.
 */
double suSpringGeneralizedForce::
getControl(const string &aName) const
{
	int index = getControlIndex(aName);
	return(getControl(index));
}

//-----------------------------------------------------------------------------
// REST LENGTH
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the rest length of the actuator.
 *
 * @param aRestLength Rest length of the actuator.
 */
void suSpringGeneralizedForce::
setRestLength(double aRestLength)
{
	_restLength = aRestLength;
}
//_____________________________________________________________________________
/**
 * Get the rest length of the actuator.
 *
 * @return Rest length of the actuator.
 */
double suSpringGeneralizedForce::
getRestLength() const
{
	return(_restLength);
}

//-----------------------------------------------------------------------------
// VISCOSITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the viscosity of the actuator.  Normally the viscosity should be a
 * positive number.  Negative viscosities will put energy into the system
 * rather than apply a damping force.
 *
 * @param aViscosity Viscosity of the actuator.
 */
void suSpringGeneralizedForce::
setViscosity(double aViscosity)
{
	_viscosity = aViscosity;
}
//_____________________________________________________________________________
/**
 * Get the viscosity of the actuator.
 *
 * @return Stiffness of the actuator.
 */
double suSpringGeneralizedForce::
getViscosity() const
{
	return(_viscosity);
}

//-----------------------------------------------------------------------------
// STIFFNESS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the stiffness of the actuator.  Normally the stiffness is a positive
 * quantity.  Negative stiffnessess will result in an unstable system- the
 * force will push away from the rest length instead of pulling toward it.
 *
 * @param aStiffness Stiffness of the actuator.
 */
void suSpringGeneralizedForce::
setStiffness(double aStiffness)
{
	_stiffness = aStiffness;
}
//_____________________________________________________________________________
/**
 * Get the stiffness of the actuator.
 *
 * @return Stiffness of the actuator.
 */
double suSpringGeneralizedForce::
getStiffness() const
{
	return(_stiffness);
}


//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Compute all quantities necessary for applying the actuator force to the
 * model.
 */
void suSpringGeneralizedForce::
computeActuation()
{
	if(_model==NULL) return;

	// FORCE
	double q = _model->getCoordinate(_qID);
	_speed = _model->getSpeed(_qID);
	double force = -_stiffness*(q - _restLength) - _viscosity*_speed;
	setForce(force);
}
