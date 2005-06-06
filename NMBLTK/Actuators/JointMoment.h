// JointMoment.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __JointMoment_h__
#define __JointMoment_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdActuators.h"
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Actuators/rdGeneralizedForceAtv.h>


//=============================================================================
//=============================================================================
/**
 * This class is the same as rdGeneralizedForceAtv except that it adds a
 * new property (optinal_negative_force) that allows one to specify a
 * different flexion strength and extension strength.
 *
 * Controls: excitation
 * States: activation
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API JointMoment : public rdGeneralizedForceAtv
{
//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Optimal negative force.  This optimal force parameter is used when
	the activation level is positive.  It is the mechanism used for having
	a different flexion and extension strenthgs */
	rdPropertyDbl _propOptimalNegForce;

	// REFERENCES
	double &_optimalNegForce;

//=============================================================================
// METHODS
//=============================================================================
public:
	JointMoment(int aQID=-1,int aNX=1,int aNY=1,int aNYP=0);
	JointMoment(DOMElement *aElement,
		int aNX=1,int aNY=1,int aNYP=0);
	JointMoment(const JointMoment &aActuator);
	virtual ~JointMoment();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	void copyData(const JointMoment &aActuator);

public:

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
	JointMoment&
		operator=(const JointMoment &aActuator);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// OPTIMAL NEGATIVE FORCE
	void setOptimalNegativeForce(double aOptNegForce);
	double getOptimalNegativeForce() const;

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();

//=============================================================================
};	// END of class JointMoment
//=============================================================================
//=============================================================================


#endif // #ifndef __JointMoment_h__
