// rdRKF_fixed.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdIntegratorDLL.h"
#include <math.h>
#include <NMBLTK/Tools/rdMath.h>
#include "rdRKF_fixed.h"


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
rdRKF_fixed::rdRKF_fixed(rdModel *aModel)
{
	// MODEL
	_ny = 0;
	_model = aModel;
	if(_model != NULL) {
		_ny = _model->getNY();
	}

	// ARRAY POINTERS
	_yv = _dy = NULL;
	_k1 = _k2 = _k3 = _k4 = _k5 = NULL;
	
	// ALLOCATE MEMORY
	allocateMemory();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
rdRKF_fixed::~rdRKF_fixed()
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
int rdRKF_fixed::
allocateMemory()
{
	_yv = new double[_ny];
	_dy = new double[_ny];
	_k1 = new double[_ny];
	_k2 = new double[_ny];
	_k3 = new double[_ny];
	_k4 = new double[_ny];
	_k5 = new double[_ny];

	return(0);
}
//____________________________________________________________________________
/**
 * Free the memory needed to perform the integration.
 */
int rdRKF_fixed::
freeMemory()
{
	if(_yv!=NULL) { delete []_yv;  _yv = NULL; }
	if(_dy!=NULL) { delete []_dy;  _dy = NULL; }
	if(_k1!=NULL) { delete []_k1;  _k1 = NULL; }
	if(_k2!=NULL) { delete []_k2;  _k2 = NULL; }
	if(_k3!=NULL) { delete []_k3;  _k3 = NULL; }
	if(_k4!=NULL) { delete []_k4;  _k4 = NULL; }
	if(_k5!=NULL) { delete []_k5;  _k5 = NULL; }

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
rdModel* rdRKF_fixed::
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
int rdRKF_fixed::
getNY()
{
	return(_ny);
}


//=============================================================================
// INTEGRATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Step forward in time by dt.
 */
int rdRKF_fixed::
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
