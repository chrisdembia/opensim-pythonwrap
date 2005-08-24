// rdModelIntegrandForActuators.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdModelIntegrandForActuators_h__
#define __rdModelIntegrandForActuators_h__

// INCLUDES
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdFunctionSet.h>
#include <NMBLTK/Simulation/Integrator/Integrand.h>
#include "rdModel.h"
#include "rdModelIntegrand.h"
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
class RDSIMULATION_API rdModelIntegrandForActuators : public rdModelIntegrand
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Prescribed trajectories of the generalized coordinates. */
	rdFunctionSet *_qSet;
	/** Prescribed trajectories of the generalized speeds. */
	rdFunctionSet *_uSet;
	/** Correction to the generalized coordinates. */
	rdArray<double> _qCorrections;
	/** Correction to the generalized speeds. */
	rdArray<double> _uCorrections;
	/** Flag indicating whether or not to hold the coordinates and speeds
	constant. */
	bool _holdCoordinatesConstant;
	/** Time at which to hold the coordinates constant. */
	double _holdTime;

	// WORK VARIABLES
	/** Work array for holding the generalized coordinates. */
	rdArray<double> _qWork;
	/** Work array for holding the generalized speeds. */
	rdArray<double> _uWork;
	/** Array for holding the model states (as opposed to the integrated
	states). */
	rdArray<double> _yModel;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdModelIntegrandForActuators(rdModel *aModel);
	virtual ~rdModelIntegrandForActuators();
private:
	void setNull();
public:

	//--------------------------------------------------------------------------
	// GET & SET
	//--------------------------------------------------------------------------
	// Size
	virtual int getSize() const;
	// Coordinate Trajectories
	virtual void setCoordinateTrajectories(rdFunctionSet *aSet);
	virtual rdFunctionSet* getCoordinateTrajectories();
	// Speed Trajectories
	virtual void setSpeedTrajectories(rdFunctionSet *aSet);
	virtual rdFunctionSet* getSpeedTrajectories();
	// Coordinate Corrections
	virtual void setCoordinateCorrections(const double aCorrections[]);
	virtual void getCoordinateCorrections(double rCorrections[]) const;
	// Speed Corrections
	virtual void setSpeedCorrections(const double aCorrections[]);
	virtual void getSpeedCorrections(double rCorrections[]) const;

	//--------------------------------------------------------------------------
	// CONVERT STATES
	//--------------------------------------------------------------------------
	void holdCoordinatesConstant(double t);
	void releaseCoordinates();
	void virtual
		convertStatesIntegrandToModel(double t,const double y[],double yModel[]);
	void virtual
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
};	// END class rdModelIntegrandForActuators
//=============================================================================
//=============================================================================

#endif  // __rdModelIntegrandForActuators_h__
