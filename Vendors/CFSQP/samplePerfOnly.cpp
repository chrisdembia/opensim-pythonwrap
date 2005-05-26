// samplePerfOnly.cpp

//==============================================================================
// INCLUDES
//==============================================================================
#include "cfsqpusr.h"


//==============================================================================
// INTERNAL FUNCTIONS
//==============================================================================
void pFunc(int nparam,int j,double *x,double *pj,void *cd);
void cFunc(int nparam,int j,double *x,double *cj,void *cd);
void gpFunc(int nparam,int j,double *x,double *dpdx,
		void (*dummy)(int,int,double *,double *,void *),void *cd);
void gcFunc(int nparam,int j,double *x,double *dcdx,
		void (*dummy)(int,int,double *,double *,void *),void *cd);


//==============================================================================
// ENTRY POINT
//==============================================================================
//______________________________________________________________________________
/**
 * A sample C++ routine for testing CFSQP.
 *
 * 2000_01_12
 * This test program executes correctly.  However, because this is compiled
 * with C++, one must add an the following lines to the cfsqpusr.h file
 *
 * #ifdef __cplusplus
 * extern "C" {
 * #endif
 *
 * ... original .h stuff ...
 * 
 * #ifdef __cplusplus
 * extern "C" {
 * #endif
 *
 *
 * The optimization problem is a single non-linear performance criterion
 * with bounds on the control variables.
 */
int main()
{
	// PARAMETERS
	int mode = 100;
	int iprint = 2;
	int miter = 500;
	int inform;
	double bigbnd = 1.0e10;
	double eps = 1.0e-8;
	double epsneq = 0.0;
	double udelta = 0.0;

	// NUMBERS
	int nx = 3;
	int np = 1;
	int nineqn = 0;
	int nineq = 0;
	int neqn = 0;
	int neq = 0;

	// SEQUENTIAL
	int ncsrl = 0;
	int ncsrn = 0;
	int nfsr = 0;
	int mesh[] = { 0 };

	// ALLOCATIONS
	double *bl = new double[nx];
	double *bu = new double[nx];
	double *x = new double[nx];
	double *p = new double[np];
	double *c = new double[nineq+neq];
	double *lambda = new double[nineq+neq+np+nx];

	// LOWER BOUND ON CONTROLS
	bl[0] = bl[1] = bl[2] =  -0.1;
	bu[0] = bu[1] = bu[2] =  bigbnd;

	// INITIALIZATIONS
	x[0] = 22.1;
	x[1] = 1.7;
	x[2] = 10.6;

	// CLIENT DATA
	void *cd = NULL;

	// OPTIMIZE
	cfsqp(nx,np,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh,
		mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,
		x,p,c,lambda,pFunc,NULL,gpFunc,NULL,cd);

	// CLEANUP
	delete bl;
	delete bu;
	delete x;
	delete p;
	delete c;
	delete lambda;
}




//==============================================================================
// USER DEFINED FUNCTIONS
//==============================================================================
//______________________________________________________________________________
/**
 * Evaluate the performance criterion.
 */
void
pFunc(int nparam,int j,double *x,double *pj,void *cd)
{
	pj[0] = 1.3*x[0]*x[0]*x[0]*x[0] + 4.8*x[1]*x[1] + 12.6*x[2]*x[2];
}

//______________________________________________________________________________
/**
 * Evaluate the derivatives of the performance criterion.
 */
void
gpFunc(int nparam,int j,double *x,double *dpdx,
	void (*dummy)(int,int,double *,double *,void *),void *cd)
{
	dpdx[0] = 4.0*1.3*x[0]*x[0]*x[0];
	dpdx[1] = 2.0*4.8*x[1];
	dpdx[2] = 2.0*12.6*x[2]; 
}

//______________________________________________________________________________
/**
 * Evaluate the constraints.
 */
void
cFunc(int nparam,int j,double *x,double *cj,void *cd)
{
}
//______________________________________________________________________________
/**
 * Evaluate the gradient of the constraints.
 */
void
gcFunc(int nparam,int j,double *x,double *dcdx,
	void (*dummy)(int,int,double *,double *,void *),
	void *cd)
{
}
