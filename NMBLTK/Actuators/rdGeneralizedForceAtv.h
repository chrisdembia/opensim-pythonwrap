// rdGeneralizedForceAtv.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdGeneralizedForceAtv_h__
#define __rdGeneralizedForceAtv_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdActuators.h"
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdGeneralizedForce.h>


//=============================================================================
//=============================================================================
/**
 * An actuator that exerts a generalized force and that incorporates
 * activation dynamics.  It has 1 control (excitation) and 1 state
 * (activation level).
 *
 * Controls: excitation
 * States: activation
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API rdGeneralizedForceAtv : public rdGeneralizedForce 
{
//=============================================================================
// DATA
//=============================================================================
private:
	static const std::string X_NAME;
	static const std::string Y_NAME;
protected:
	// PROPERTIES
	/** Rise time of activation. */
	rdPropertyDbl _propRiseTime;
	/** Fall time of activation. */
	rdPropertyDbl _propFallTime;

	// REFERENCES
	double &_riseTime;
	double &_fallTime;

	/** Activation level (state 0). */
	double _a;

//=============================================================================
// METHODS
//=============================================================================
public:
	rdGeneralizedForceAtv(int aQID=-1,int aNX=1,int aNY=1,int aNYP=0);
	rdGeneralizedForceAtv(DOMElement *aElement,
		int aNX=1,int aNY=1,int aNYP=0);
	rdGeneralizedForceAtv(const rdGeneralizedForceAtv &aActuator);
	virtual ~rdGeneralizedForceAtv();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	void copyData(const rdGeneralizedForceAtv &aActuator);

public:

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
	rdGeneralizedForceAtv&
		operator=(const rdGeneralizedForceAtv &aActuator);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STATES
	virtual int getNY() const;
	virtual const std::string& getStateName(int aIndex) const;
	virtual int getStateIndex(const std::string &aName) const;
	virtual void setStates(const double aX[]);
	virtual void setState(int aIndex,double aValue);
	virtual void setState(const std::string &aName,double aValue);
	virtual void getStates(double rX[]) const;
	virtual double getState(int aIndex) const;
	virtual double getState(const std::string &aName) const;
	// RISE TIME
	void setRiseTime(double aRiseTime);
	double getRiseTime() const;
	// FALL TIME
	void setFallTime(double aFallTime);
	double getFallTime() const;

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void promoteControlsToStates(const double aX[],double aDT);
	virtual void computeActuation();
	virtual void computeStateDerivatives(double rDYDT[]);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();

//=============================================================================
};	// END of class rdGeneralizedForceAtv
//=============================================================================
//=============================================================================


#endif // #ifndef __rdGeneralizedForceAtv_h__
