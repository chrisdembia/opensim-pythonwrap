// rdModelIntegrand.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdModelIntegrand_h__
#define __rdModelIntegrand_h__

// INCLUDES
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Integrator/Integrand.h>
#include "rdModel.h"
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Simulation/Control/rdController.h>

#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

//=============================================================================
//=============================================================================
/**
 * This class makes rdModel into a valid Integrand.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDSIMULATION_API rdModelIntegrand : public Integrand
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Model. */
	rdModel *_model;
	/** Control set. */
	rdControlSet _controlSet;
	/** Controller. */
	rdController *_controller;
	/** Storage for the controls. */
	rdStorage *_controlStore;
	/** Storage for the states. */
	rdStorage *_stateStore;
	/** Storage for the pseudostates. */
	rdStorage *_pseudoStore;

	// WORK VARIABLES
	/** Initial time of the integration. */
	double _ti;
	/** Final time of the integration. */
	double _tf;
	/** Previous time. */
	double _tPrev;
	/** Size of previous time step. */
	double _dtPrev;
	/** Array of control values at the current time. */
	rdArray<double> _x;
	/** Array of control values at the previous integration time step. */
	rdArray<double> _xPrev;
	/** Array of state values at the previous integration time step. */
	rdArray<double> _yPrev;
	/** Array of pseudo states. */
	rdArray<double> _yp;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdModelIntegrand(rdModel *aModel);
	virtual ~rdModelIntegrand();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET & SET
	//--------------------------------------------------------------------------
	// Size
	virtual int getSize() const;
	// Model
	rdModel* getModel();
	// Control Set
	void setControlSet(const rdControlSet &aControlSet);
	rdControlSet* getControlSet();
	// CONTROL STORAGE
	void setControlStorage(rdStorage *aStorage);
	rdStorage* getControlStorage();
	// STATE STORAGE
	void setStateStorage(rdStorage *aStorage);
	rdStorage* getStateStorage();
	// PSEUDO-STATE STORAGE
	void setPseudoStateStorage(rdStorage *aStorage);
	rdStorage* getPseudoStateStorage();
	// CONTROLLER
	void setController(rdController *aController);
	rdController* getController();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	virtual rdControlSet* constructControlSet() const;
	virtual void
		convertStatesIntegrandToModel(double t,const double y[],double yModel[]);
	virtual void
		convertStatesModelToIntegrand(const double yModel[],double y[]) const;

	//--------------------------------------------------------------------------
	// INITIAL STATES
	//--------------------------------------------------------------------------
	virtual void setInitialStates(double ti,const double yi[]);
	virtual void getInitialStates(double yi[]) const;
	
	//--------------------------------------------------------------------------
	// COMPUTATION
	//--------------------------------------------------------------------------
	virtual void compute(double t,double y[],double dydt[]);

	//--------------------------------------------------------------------------
	// HOOKS
	//--------------------------------------------------------------------------
	virtual void initialize(int step,double &dt,double ti,double tf,double y[]);
	virtual void processAfterStep(int step,double &dt,double t,double y[]);
	virtual void finalize(int step,double t,double y[]);

//=============================================================================
};	// END class rdModelIntegrand
//=============================================================================
//=============================================================================

#endif  // __rdModelIntegrand_h__
