// SampleIntegrand.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __SampleIntegrand_h__
#define __SampleIntegrand_h__

// INCLUDES
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Integrator/Integrand.h>

#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * This class demonstrates a sample implementation of an Integrand.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class SampleIntegrand : public Integrand
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Storage for the states. */
	rdStorage *_stateStore;

	// WORK VARIABLES
	/** Initial time of the integration. */
	double _ti;
	/** Final time of the integration. */
	double _tf;
	/** Previous time. */
	double _tPrev;
	/** Size of previous time step. */
	double _dtPrev;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	SampleIntegrand();
	virtual ~SampleIntegrand();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET & SET
	//--------------------------------------------------------------------------
	// Size
	virtual int getSize() const;
	// STATE STORAGE
	void setStateStorage(rdStorage *aStorage);
	rdStorage* getStateStorage();

	//--------------------------------------------------------------------------
	// COMPUTATION
	//--------------------------------------------------------------------------
	virtual void compute(double t,double y[],double dydt[]);
	virtual void computeJacobian(double t,double y[],double *dydtdy);

	//--------------------------------------------------------------------------
	// HOOKS
	//--------------------------------------------------------------------------
	virtual void initialize(int step,double &dt,double ti,double tf,double y[]);
	virtual void processAfterStep(int step,double &dt,double t,double y[]);

//=============================================================================
};	// END class SampleIntegrand
//=============================================================================
//=============================================================================

#endif  // __SampleIntegrand_h__
