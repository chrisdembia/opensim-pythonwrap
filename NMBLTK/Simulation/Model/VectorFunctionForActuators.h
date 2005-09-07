// VectorFunctionForActuators.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __VectorFunctionForActuators_h__
#define __VectorFunctionForActuators_h__

#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/VectorFunctionUncoupledNxN.h>
#include <NMBLTK/Simulation/Integrator/rdIntegRKF.h>
#include "rdModelIntegrand.h"

//extern template class RDTOOLS_API rdArray<double>;

//=============================================================================
//=============================================================================
/**
 * An abstract class for representing a vector function.
 *
 * A vector function is a relation between some number of independent variables 
 * and some number of dependent values such that for any particular set of
 * independent variables the correct number of dependent variables is returned.
 * Values of the function and its derivatives
 * are obtained by calling the evaluate() method.  The curve may or may not
 * be finite or diferentiable; the evaluate method returns values between
 * rdMath::MINUS_INFINITY and rdMath::PLUS_INFINITY, or it returns rdMath::NAN
 * (not a number) if the curve is not defined.
 * Currently, functions of up to 3 variables (x,y,z) are supported.
 *
 * @author Frank C. Anderson
 */
class RDSIMULATION_API VectorFunctionForActuators :
	public VectorFunctionUncoupledNxN
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Initial time for the integration. */
	double _ti;
	/** Final time for the integration. */
	double _tf;
	/** Target actuator forces. */
	rdArray<double> _f;
	/** Integrand. */
	rdModelIntegrand *_integrand;
	/** Integrator. */
	rdIntegRKF *_integrator;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	VectorFunctionForActuators(rdModelIntegrand *aIntegrand);
	VectorFunctionForActuators(DOMElement *aElement);
	VectorFunctionForActuators(const VectorFunctionForActuators &aFunction);
	virtual ~VectorFunctionForActuators();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setEqual(const VectorFunctionForActuators &aVectorFunction);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
	VectorFunctionForActuators&
		operator=(const VectorFunctionForActuators &aFunction);

	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	void setInitialTime(double aTI);
	double getInitialTime() const;
	void setFinalTime(double aTF);
	double getFinalTime() const;
	void setTargetForces(const double *aF);
	void getTargetForces(double *rF) const;
	rdModelIntegrand* getIntegrand();

	
	//--------------------------------------------------------------------------
	// EVALUATE
	//--------------------------------------------------------------------------
	virtual void evaluate(const double *aX,double *aY);

//=============================================================================
};	// END class VectorFunctionForActuators
//=============================================================================
//=============================================================================

#endif  // __VectorFunctionForActuators_h__
