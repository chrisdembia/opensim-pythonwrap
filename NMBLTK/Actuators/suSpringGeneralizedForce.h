// suSpringGeneralizedForce.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suSpringGeneralizedForce_h__
#define __suSpringGeneralizedForce_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdGeneralizedForce.h>
#include "rdActuatorsDLL.h"


//=============================================================================
//=============================================================================
/**
 * An actuator that exerts a generalized force based on spring-like
 * characteristics (stiffness and viscosity).  It has one control:
 * stiffness. 
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API suSpringGeneralizedForce : public rdGeneralizedForce 
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** Name of the control. */
	static const std::string X_NAME;
protected:
	// PROPERTIES
	/** Rest length. */
	rdPropertyDbl _propRestLength;
	/** Viscosity. */
	rdPropertyDbl _propViscosity;

	// REFERENCES
	double &_restLength;
	double &_viscosity;

	/** Stiffness (control 0). */
	double _stiffness;


//=============================================================================
// METHODS
//=============================================================================
public:
	suSpringGeneralizedForce(int aQID=-1,int aNX=1,int aNY=0,int aNYP=0);
	suSpringGeneralizedForce(DOMElement *aElement,
		int aNX=1,int aNY=0,int aNYP=0);
	suSpringGeneralizedForce(const suSpringGeneralizedForce &aActuator);
	virtual ~suSpringGeneralizedForce();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();

public:

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
	suSpringGeneralizedForce&
		operator=(const suSpringGeneralizedForce &aActuator);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// CONTROLS
	virtual int getNX() const;
	virtual const std::string getControlName(int aIndex) const;
	virtual int getControlIndex(const std::string &aName) const;
	virtual void setControls(const double aX[]);
	virtual void setControl(int aIndex,double aValue);
	virtual void setControl(const std::string &aName,double aValue);
	virtual void getControls(double rX[]) const;
	virtual double getControl(int aIndex) const;
	virtual double getControl(const std::string &aName) const;
	// REST LENGTH
	void setRestLength(double aRestLength);
	double getRestLength() const;
	// VISCOSITY
	void setViscosity(double aViscosity);
	double getViscosity() const;
	// STIFFNESS
	void setStiffness(double aStiffness);
	double getStiffness() const;

	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeActuation();

//=============================================================================
};	// END of class suSpringGeneralizedForce
//=============================================================================
//=============================================================================


#endif // #ifndef __suSpringGeneralizedForce_h__
