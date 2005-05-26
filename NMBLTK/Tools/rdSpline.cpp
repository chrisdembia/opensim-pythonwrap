// rdSpline.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdSpline.h"
#include "rdMath.h"


// DEFINES
#define MAXSIZE 2048


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdSpline::~rdSpline()
{
	if(_coefs!=NULL) { delete[] _coefs;  _coefs=NULL; }
	if(_knots!=NULL) { delete[] _knots;  _knots=NULL; }
	if(_tx!=NULL) { delete[] _tx;  _tx=NULL; }
	if(_b!=NULL) { delete[] _b;  _b=NULL; }
}
//_____________________________________________________________________________
/**
 * Construct a b-spline representation of a smooth function.
 *
 *	@param aFileName Name of a valid spline file.
 */
rdSpline::
rdSpline(const char *aFileName)
{
	// BASIC INITIALIZATION
	null();

	// CHECK FILE NAME
	if(aFileName==NULL) {
		printf("rdSpline.initialize: ERROR- file name is NULL.\n");
		_status = -1;
		return;
	}
	if(strlen(aFileName)<=0) {
		printf("rdSpline.initialize: ERROR- file name has no length.\n");
		_status = -1;
		return;
	}

	// OPEN FILE
	FILE *fp = fopen(aFileName,"r");
	if(fp==NULL) {
		printf("rdSpline.initialize: ERROR- failed to open file %s.\n",
		 aFileName);
		_status = -1;
		return;
	}

	// CONTRUCT BASED ON FILE
	_status = initialize(fp);

	// CLOSE FILE
	fclose(fp);

	// CHECK STATUS
	if(_status<0) {
		printf("rdSpline.rdSpline: WARNING- spline failed to initialize.\n");
		return;
	}

	// ALLOCATE WORKING ARRAYS
	_tx = new double[2*(_order-1)];
	_b = new double[2*_nknots];

	_status = 0;
}
//_____________________________________________________________________________
/**
 * Construct a b-spline representation of a smooth function.
 *
 *	@param a pointer to an openned spline file.
 */
rdSpline::
rdSpline(FILE *aFP)
{
	// BASIC INITIALIZATION
	null();

	// CHECK FILE POINTER
	if(aFP==NULL) {
		printf("rdSpline.rdSpline(FILE*): ERROR- invalid file pointer.\n");
		_status = -1;
		return;
	}

	// INITIALIZE
	_status = initialize(aFP);

	// CHECK STATUS
	if(_status<0) {
		printf("rdSpline.rdSpline: WARNING- spline failed to initialize.\n");
		return;
	}

	// ALLOCATE WORKING ARRAYS
	_tx = new double[2*(_order-1)];
	_b = new double[2*_nknots];

	_status = 0;
}
//_____________________________________________________________________________
/**
 * Initialize spline based on the contents of a file.
 *
 *	@param aFileName Name of a valid spline file.
 */
int rdSpline::
initialize(FILE *aFP)
{
	if(aFP==NULL) return(-1);
	char dum[MAXSIZE];
	int i,status;

	// NAME
	status = fscanf(aFP,"%s",_name);
	if(checkFileStatus(status)!=0) return(-1);

	// ORDER
	status = fscanf(aFP,"%s",dum);
	if(checkFileStatus(status)!=0) return(-1);
	fscanf(aFP,"%d",&_order);
	if(checkFileStatus(status)!=0) return(-1);
	if(_order<=0) {
		printf("rdSpline.initialize: ERROR- invalid order (%d).\n",
		 _order);
		return(-1);
	}

	// INTERVAL
	fscanf(aFP,"%s",dum);
	if(checkFileStatus(status)!=0) return(-1);
	fscanf(aFP,"%lf",&_ti);
	if(checkFileStatus(status)!=0) return(-1);
	fscanf(aFP,"%lf",&_tf);
	if(checkFileStatus(status)!=0) return(-1);
	if(_ti>_tf) {
		printf("rdSpline.initialize: ERROR- invalid interval (%lf to %lf).\n",
		 _ti,_tf);
		return(-1);
	}

	// NUMBER OF KNOTS
	fscanf(aFP,"%s",dum);
	if(checkFileStatus(status)!=0) return(-1);
	fscanf(aFP,"%d",&_nknots);
	if(checkFileStatus(status)!=0) return(-1);
	if(_nknots<=0) {
		printf("rdSpline.initialize: ERROR- invalid number of knots (%d).\n",
		 _nknots);
		return(-1);
	}

	// ALLOCATE KNOTS ARRAY
	_knots = new double[_nknots];
	if(_knots==NULL) {
		printf("rdSpline.initialize: ERROR- not enough memory for %d knots.\n",
		 _nknots);
		return(-1);
	}

	// KNOT VALUES
	for(i=0;i<_nknots;i++) {
		fscanf(aFP,"%lf",&_knots[i]);
		if(checkFileStatus(status)!=0) return(-1);
	}

	// NUMBER OF COEFFICIENTS
	fscanf(aFP,"%s",dum);
	if(checkFileStatus(status)!=0) return(-1);
	fscanf(aFP,"%d",&_ncoefs);
	if(checkFileStatus(status)!=0) return(-1);
	if(_ncoefs<=0) {
		printf("rdSpline.initialize: ERROR- invalid number of");
		printf(" coefficents (%d).\n",_ncoefs);
		return(-1);
	}

	// ALLOCATE COEFFICIENTS ARRAY
	_coefs = new double[_ncoefs];
	if(_coefs==NULL) {
		printf("rdSpline.initialize: ERROR- not enough memory for %d",_ncoefs);
		printf(" coefficents.\n");
		return(-1);
	}

	// COEFFICENT VALUES
	for(i=0;i<_ncoefs;i++) {
		status = fscanf(aFP,"%lf",&_coefs[i]);
		if(checkFileStatus(status)!=0) return(-1);
	}

	return(0);
}
//_____________________________________________________________________________
/**
 * NULL or zero data.
 */
void rdSpline::
null()
{
	_status = -1;
	_ti = 0.0;
	_tf = 0.0;
	_order = 0;
	_nknots = 0;
	_ncoefs = 0;
	_knots = NULL;
	_coefs = NULL;
	_tx = NULL;
	_b = NULL;
}
//_____________________________________________________________________________
/**
 * Check the status of a file read.
 *
 *	@param aFileName Name of a valid spline file.
 */
int rdSpline::
checkFileStatus(int aStatus)
{
	if(aStatus==EOF) {
		printf("rdSpline.checkFileStatus: ERROR during file read.\n");
		return(-1);
	}
	return(0);
}


//=============================================================================
// EVALUATION
//=============================================================================
//______________________________________________________________________________
/**
 * Get the knot index for the interval in which x falls.
 * If x does not fall within a valid interval, -1 is returned.
 */
int rdSpline::
getKnotIndex(double x)
{
	int index=-1;
	int i;
	for(i=0;i<_nknots-1;i++) {
		if((_knots[i]<=x)&&(x<_knots[i+1])) {
			index = i;
			break;
		}
	}
	return(index);
}
//______________________________________________________________________________
/**
 * Evaluate a spline at x.
 * 
 * This function is based on Matlab's spval.m.
 *
 * 2000_08_10
 * This routine assumes that the end knots have the proper multiplicity.
 *
 */
double rdSpline::
evaluate(double x)
{
	// INITIALIZATIONS
	int i,j;
	int k = _order;
	double *t = _knots;
	double *a = _coefs;

	// GET THE KNOT INEX
	int index = getKnotIndex(x);
	if(index<0) {
		printf("rdSpline.evaluate: WARNING- x (%lf) is not",x);
		printf(" on the spline interval (%lf to %lf).\n",_ti,_tf);
		return(0.0);
	}

	// INITIALIZE THE PERTINENT KNOT VALUES
	for(i=0;i<2*(k-1);i++) {
		_tx[i] = t[index-k+2+i] - x;
	}

	// INITIALIZE THE SEED VALUES OF b
	double num,den;
	for(j=0,i=index-k+1;i<=index;i++,j++) {
		_b[j] = a[i];
	}

	// LOOP
	for(int r=0;r<k-1;r++) {
		for(i=0;i<k-r-1;i++) {
			num = _tx[i+k-1]*_b[i] - _tx[i+r]*_b[i+1];
			den = _tx[i+k-1] - _tx[i+r];
			_b[i] = num/den;
		}
	}
	return(_b[0]);
}


//=============================================================================
// PRINTING
//=============================================================================
//______________________________________________________________________________
/**
 * Print a spline.
 */
void rdSpline::
print()
{
	int i;

	// NAME
	printf("name= %s\n",_name);

	// ORDER
	printf("order= %d\n",_order);

	// INTERVAL
	printf("interval=  %lf %lf\n",_ti,_tf);

	// KNOTS
	printf("nknots= %d\n",_nknots);
	for(i=0;i<_nknots;i++) {
		printf("%lf ",_knots[i]);
	}
	printf("\n");

	// COEFFICIENTS
	printf("ncoefs= %d\n",_ncoefs);
	for(i=0;i<_ncoefs;i++) {
		printf("%lf ",_coefs[i]);
	}
	printf("\n");
}
