// rdRKF.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdIntegrator.h"
#include <math.h>
#include <NMBLTK/Tools/rdMath.h>
#include "rdRKF.h"


//============================================================================
// EXPORTED CONSTANTS
//============================================================================
/*
extern RDSIMULATION_API const int rdRKF_NORMAL = 20;
extern RDSIMULATION_API const int rdRKF_FINE = 30;
extern RDSIMULATION_API const int rdRKF_POOR = -40;
extern RDSIMULATION_API const int rdRKF_NAN = -50;
extern RDSIMULATION_API const int rdRKF_ERROR = -60;
extern RDSIMULATION_API const int rdRKF_TOO_MANY_STEPS = -70;
*/
//============================================================================
// INTERNAL TOLERANCE CONSTANTS
//============================================================================
const double TOLMAX = 1.0;
const double TOLMIN = 1.0e-12;
const double TOLFINERATIO = 1.0e-2;

//============================================================================
// INTERMAL RKF CONSTANTS
//============================================================================
const double C21	=  2.500000e-1;
const double C22	=  2.500000e-1;

const double C31	=  3.750000e-1;
const double C32	=  9.375000e-2;
const double C33	=  2.812500e-1;

const double C41	=  9.230769e-1;
const double C42	=  8.793810e-1;
const double C43	= -3.277196;
const double C44	=  3.320892;

const double C51	=  1.000000;
const double C52	=  2.032407;
const double C53	= -8.000000;
const double C54	=  7.173489;
const double C55	= -2.058967e-1;

const double C61	=  5.000000e-1;
const double C62	= -2.962963e-1;
const double C63	=  2.000000;
const double C64	= -1.381676;
const double C65	=  4.529727e-1;
const double C66	= -2.750000e-1;

const double CE1	=  2.777778e-3;
const double CE2	= -2.994152e-2;
const double CE3	= -2.919989e-2;
const double CE4	=  2.000000e-2;
const double CE5	=  3.636364e-2;

const double CY1	=  1.157407e-1;
const double CY2	=  5.489279e-1;
const double CY3	=  5.353314e-1;
const double CY4	= -2.000000e-1;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdRKF::rdRKF(rdModel *aModel,double aTol,double aTolFine)
{
	// MODEL
	_ny = 0;
	_model = aModel;
	if(_model != NULL) {
		_nx = _model->getNX();
		_ny = _model->getNY();
	}

	// ARRAY POINTERS
	_x = NULL;
	_yv = _ye = _dy = NULL;
	_k1 = _k2 = _k3 = _k4 = _k5 = _k6 = NULL;

	// TOLERANCES
	_tol = aTol;
	if(aTolFine>=0.0) {
		_tolFine = aTolFine;
	} else {
		_tolFine = 1.0e-2 * _tol;
	}
	
	// ALLOCATE MEMORY
	allocateMemory();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
rdRKF::~rdRKF()
{
	freeMemory();
}


//-----------------------------------------------------------------------------
// MEMORY
//-----------------------------------------------------------------------------
//____________________________________________________________________________
/**
 * Allocate the memory needed to perform the integration.
 */
int rdRKF::
allocateMemory()
{
	if(_nx>0) _x = new double[_nx];
	_yv = new double[_ny];
	_ye = new double[_ny];
	_dy = new double[_ny];
	_k1 = new double[_ny];
	_k2 = new double[_ny];
	_k3 = new double[_ny];
	_k4 = new double[_ny];
	_k5 = new double[_ny];
	_k6 = new double[_ny];

	return(0);
}
//____________________________________________________________________________
/**
 * Free the memory needed to perform the integration.
 */
int rdRKF::
freeMemory()
{
	if(_x!=NULL) { delete []_x;  _x = NULL; }
	if(_yv!=NULL) { delete []_yv;  _yv = NULL; }
	if(_ye!=NULL) { delete []_ye;  _ye = NULL; }
	if(_dy!=NULL) { delete []_dy;  _dy = NULL; }
	if(_k1!=NULL) { delete []_k1;  _k1 = NULL; }
	if(_k2!=NULL) { delete []_k2;  _k2 = NULL; }
	if(_k3!=NULL) { delete []_k3;  _k3 = NULL; }
	if(_k4!=NULL) { delete []_k4;  _k4 = NULL; }
	if(_k5!=NULL) { delete []_k5;  _k5 = NULL; }
	if(_k6!=NULL) { delete []_k6;  _k6 = NULL; }

	return(0);
}

//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the model.
 */
rdModel* rdRKF::
getModel()
{
	return(_model);
}

//-----------------------------------------------------------------------------
// STATES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of states being integrated.
 */
int rdRKF::
getNY()
{
	return(_ny);
}

//-----------------------------------------------------------------------------
// TOLERANCE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the tolerances of the integrator.
 *
 * The tolerance, aTol, specifies the allowd error of an integration.
 * If the error exceeds the tolerance, the integration step size should
 * be halved.
 *
 * The fine tollerance, aTolFine, specifies the accuracy tolerance of an
 * integration. If the accuracy is better than aTolFine, the integration step
 * size should be doubled.
 */
void rdRKF::
setTolerance(double aTol,double aTolFine)
{
	// TOLERANCE
	if(aTol<TOLMIN) {
		aTol = TOLMIN;
	} else if(aTol>TOLMAX) {
		aTol = TOLMAX;
	}
	_tol = aTol;
	
	// FINE TOLERANCE
	setFineTolerance(aTolFine);
}
//_____________________________________________________________________________
/**
 * Set the fine tolerance of the integrator.
 *
 * The fine tollerance, aTolFine, specifies the accuracy tolerance of an
 * integration. If the accuracy is better than aTolFine, the integration step
 * size should be doubled.
 */
void rdRKF::
setFineTolerance(double aTolFine)
{	
	if((aTolFine<=0.0)||(aTolFine>=_tol)) {
		aTolFine = TOLFINERATIO * _tol;
	}
	_tolFine = aTolFine;
}

//_____________________________________________________________________________
/**
 * Get the tolerance of the integrator.
 *
 * The tolerance specifies the allowd error of an integration.
 * If the error exceeds the tolerance, the integration step size is halved.
 */
double rdRKF::
getTolerance()
{
	return(_tol);
}
//_____________________________________________________________________________
/**
 * Get the fine tolerance of the integrator.
 *
 * The fine tollerance specifies the accuracy tolerance of an integration.
 * If the accuracy is better than aTolFine, the integration step size is
 * doubled.
 */
double rdRKF::
getFineTolerance()
{
	return(_tolFine);
}


//=============================================================================
// INTEGRATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Step forward in time by dt.
 *
 * @param dt Requested integration time step.
 * @param t Current time.
 * @param controlSet Controls.
 * @param y States.
 * @return rdRKF_NORMAL on a successful step, rdRKF_NAN if not-a-number is
 * encountered in any of the states, rdRKF_POOR if the integration error
 * is worse than the specified tolerance, or rdRKF_FINE if the integration
 * error is better than the specified fine tolerance.
 */
int rdRKF::
step(double dt,double t,rdControlSet &controlSet,double *y)
{
	int i,offender;
	double t2,yemax;

	// CHECK FOR PROPER INITIALIZATION
	if(_ny<1) {
		printf("rkf:  ERROR- the number of states is less than 1.\n");
		return(rdRKF_ERROR);
	}

	// ORDER 1
	controlSet.getControlValues(t,_x);
	_model->deriv(t,_x,y,_dy);
	for(i=0;i<_ny;i++) {
		_k1[i] = dt*_dy[i];
		_yv[i] = y[i] + _k1[i]*C22;
	}
	t2 = t + dt*C21;

	// ORDER 2
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k2[i] = dt*_dy[i];
		_yv[i] = y[i] + C32*_k1[i] + C33*_k2[i];
	}
	t2 = t + dt*C31;

	// ORDER 3
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k3[i] =  dt*_dy[i];
		_yv[i] = y[i] + C42*_k1[i] + C43*_k2[i] + C44*_k3[i];
	}
	t2 = t + dt*C41;

	// ORDER 4
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k4[i] = dt*_dy[i];
		_yv[i] = y[i] + C52*_k1[i] + C53*_k2[i] + C54*_k3[i] + C55*_k4[i];
	}
	t2 = t + dt;

	// ORDER 5
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k5[i] = dt*_dy[i];
		_yv[i] = y[i] + C62*_k1[i] + C63*_k2[i] + C64*_k3[i] + C65*_k4[i] + C66*_k5[i];
	}
	t2 = t + dt*C61;

	// ORDER 6
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k6[i] = dt*_dy[i];
	}


	// GET MAX ERROR
	offender = -1;
	for(yemax=0.0,i=0;i<_ny;i++) {

		_ye[i] = CE1*_k1[i] + CE2*_k3[i] + CE3*_k4[i] + CE4*_k5[i] + CE5*_k6[i];

		// GOOD NUMBER
		if((_ye[i]<0.0) || (_ye[i]>=0.0)) {  
			_ye[i] = fabs(_ye[i]);
			if(_ye[i]>yemax) {
				offender = i;
				yemax = _ye[i];
			}

		// NAN
		} else {
			printf("rdRKF.step: NAN in state %d\n",i);
			return(rdRKF_NAN);
		}
	}

	// CHECK ERROR
	if(yemax > _tol) {
		//printf("rkf: error exceeded tolerance. offender = %d\n",offender);
		return(rdRKF_POOR);
	}

	// UPDATE STATES
	for(i=0;i<_ny;i++) {
		y[i] = y[i] + CY1*_k1[i] + CY2*_k3[i] + CY3*_k4[i] + CY4*_k5[i];
	}

	// FINE ACCURACY
	if(yemax < _tolFine) {
		return(rdRKF_FINE);
	}

	return(rdRKF_NORMAL);
}

//_____________________________________________________________________________
/**
 * Step forward in time by dt.
 *
 * @param dt Requested integration time step.
 * @param t Current time.
 * @param x Controls.
 * @param y States.
 * @return rdRKF_NORMAL on a successful step, rdRKF_NAN if not-a-number is
 * encountered in any of the states, rdRKF_POOR if the integration error
 * is worse than the specified tolerance, or rdRKF_FINE if the integration
 * error is better than the specified fine tolerance.
 */
int rdRKF::
step(double dt,double t,double *x,double *y)
{
	int i,offender;
	double t2,yemax;

	// CHECK FOR PROPER INITIALIZATION
	if(_ny<1) {
		printf("rkf:  ERROR- the number of states is less than 1.\n");
		return(rdRKF_ERROR);
	}

	// ORDER 1
	_model->deriv(t,x,y,_dy);
	for(i=0;i<_ny;i++) {
		_k1[i] = dt*_dy[i];
		_yv[i] = y[i] + _k1[i]*C22;
	}
	t2 = t + dt*C21;

	// ORDER 2
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k2[i] = dt*_dy[i];
		_yv[i] = y[i] + C32*_k1[i] + C33*_k2[i];
	}
	t2 = t + dt*C31;

	// ORDER 3
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k3[i] =  dt*_dy[i];
		_yv[i] = y[i] + C42*_k1[i] + C43*_k2[i] + C44*_k3[i];
	}
	t2 = t + dt*C41;

	// ORDER 4
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k4[i] = dt*_dy[i];
		_yv[i] = y[i] + C52*_k1[i] + C53*_k2[i] + C54*_k3[i] + C55*_k4[i];
	}
	t2 = t + dt;

	// ORDER 5
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k5[i] = dt*_dy[i];
		_yv[i] = y[i] + C62*_k1[i] + C63*_k2[i] + C64*_k3[i] + C65*_k4[i] + C66*_k5[i];
	}
	t2 = t + dt*C61;

	// ORDER 6
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k6[i] = dt*_dy[i];
	}


	// GET MAX ERROR
	offender = -1;
	for(yemax=0.0,i=0;i<_ny;i++) {

		_ye[i] = CE1*_k1[i] + CE2*_k3[i] + CE3*_k4[i] + CE4*_k5[i] + CE5*_k6[i];

		// GOOD NUMBER
		if((_ye[i]<0.0) || (_ye[i]>=0.0)) {  
			_ye[i] = fabs(_ye[i]);
			if(_ye[i]>yemax) {
				offender = i;
				yemax = _ye[i];
			}

		// NAN
		} else {
			printf("rdRKF.step: NAN in state %d\n",i);
			return(rdRKF_NAN);
		}
	}

	// CHECK ERROR
	if(yemax > _tol) {
		//printf("rkf: error exceeded tolerance. offender = %d\n",offender);
		return(rdRKF_POOR);
	}

	// UPDATE STATES
	for(i=0;i<_ny;i++) {
		y[i] = y[i] + CY1*_k1[i] + CY2*_k3[i] + CY3*_k4[i] + CY4*_k5[i];
	}

	// FINE ACCURACY
	if(yemax < _tolFine) {
		return(rdRKF_FINE);
	}

	return(rdRKF_NORMAL);
}

//_____________________________________________________________________________
/**
 * Step forward in time by dt.  This method does not estimate the integration
 * error and does not return any kind of integration status other than
 * rdRKF_NORMAL or rdRKF_NAN.
 *
 * @param dt Requested integration step.
 * @param t Current time.
 * @param controlSet Controls.
 * @param y States.
 * @return rdRKF_NORMAL on a successful step, or rdRKF_NAN if not-a-number is
 * encountered in any of the states.
 */
int rdRKF::
stepFixed(double dt,double t,rdControlSet &controlSet,double *y)
{
	int i;
	double t2;

	// ORDER 1
	controlSet.getControlValues(t,_x);
	_model->deriv(t,_x,y,_dy);
	for(i=0;i<_ny;i++) {
		_k1[i] = dt*_dy[i];
		_yv[i] = y[i] + _k1[i]*C22;
	}
	t2 = t + dt*C21;

	// ORDER 2
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k2[i] = dt*_dy[i];
		_yv[i] = y[i] + C32*_k1[i] + C33*_k2[i];
	}
	t2 = t + dt*C31;

	// ORDER 3
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k3[i] =  dt*_dy[i];
		_yv[i] = y[i] + C42*_k1[i] + C43*_k2[i] + C44*_k3[i];
	}
	t2 = t + dt*C41;

	// ORDER 4
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k4[i] = dt*_dy[i];
		_yv[i] = y[i] + C52*_k1[i] + C53*_k2[i] + C54*_k3[i] + C55*_k4[i];
	}
	t2 = t + dt;

	// ORDER 5
	controlSet.getControlValues(t2,_x);
	_model->deriv(t2,_x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k5[i] = dt*_dy[i];
		_yv[i] = y[i] + C62*_k1[i] + C63*_k2[i] + C64*_k3[i] + C65*_k4[i] + C66*_k5[i];
	}

	// UPDATE STATES
	for(i=0;i<_ny;i++) {
		y[i] = y[i] + CY1*_k1[i] + CY2*_k3[i] + CY3*_k4[i] + CY4*_k5[i];

		// CHECK FOR NAN
		if(!((y[i]<0.0)||(y[i]>=0.0))) {
			printf("rdRKF_fixed.step: NAN in state %d\n",i);
			return(rdRKF_NAN);
		}
	}

	return(rdRKF_NORMAL);
}

//_____________________________________________________________________________
/**
 * Step forward in time by dt.  This method does not estimate the integration
 * error and does not return any kind of integration status other than
 * rdRKF_NORMAL or rdRKF_NAN.
 *
 * @param dt Requested integration step.
 * @param t Current time.
 * @param x Controls.
 * @param y States.
 * @return rdRKF_NORMAL on a successful step, or rdRKF_NAN if not-a-number is
 * encountered in any of the states.
 */
int rdRKF::
stepFixed(double dt,double t,double *x,double *y)
{
	int i;
	double t2;

	// ORDER 1
	_model->deriv(t,x,y,_dy);
	for(i=0;i<_ny;i++) {
		_k1[i] = dt*_dy[i];
		_yv[i] = y[i] + _k1[i]*C22;
	}
	t2 = t + dt*C21;

	// ORDER 2
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k2[i] = dt*_dy[i];
		_yv[i] = y[i] + C32*_k1[i] + C33*_k2[i];
	}
	t2 = t + dt*C31;

	// ORDER 3
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k3[i] =  dt*_dy[i];
		_yv[i] = y[i] + C42*_k1[i] + C43*_k2[i] + C44*_k3[i];
	}
	t2 = t + dt*C41;

	// ORDER 4
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k4[i] = dt*_dy[i];
		_yv[i] = y[i] + C52*_k1[i] + C53*_k2[i] + C54*_k3[i] + C55*_k4[i];
	}
	t2 = t + dt;

	// ORDER 5
	_model->deriv(t2,x,_yv,_dy);
	for(i=0;i<_ny;i++) {
		_k5[i] = dt*_dy[i];
		_yv[i] = y[i] + C62*_k1[i] + C63*_k2[i] + C64*_k3[i] + C65*_k4[i] + C66*_k5[i];
	}

	// UPDATE STATES
	for(i=0;i<_ny;i++) {
		y[i] = y[i] + CY1*_k1[i] + CY2*_k3[i] + CY3*_k4[i] + CY4*_k5[i];

		// CHECK FOR NAN
		if(!((y[i]<0.0)||(y[i]>=0.0))) {
			printf("rdRKF_fixed.step: NAN in state %d\n",i);
			return(rdRKF_NAN);
		}
	}

	return(rdRKF_NORMAL);
}
