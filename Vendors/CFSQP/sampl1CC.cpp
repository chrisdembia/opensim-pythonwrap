// sampleClay.cpp

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
	int iprint = 3;
	int miter = 500;
	int inform;
	double bigbnd = 1.0e10;
	double eps = 1.0e-8;
	double epsneq = 0.0;
	double udelta = 0.0;

	// NUMBERS
	int nx = 3;
	int np = 1;
	int nineqn = 1;
	int nineq = 1;
	int neqn = 0;
	int neq = 1;

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
	bl[0] = bl[1] = bl[2] = 0.0;
	bu[0] = bu[1] = bu[2] = bigbnd;

	// INITIALIZATIONS
	x[0] = 0.1;
	x[1] = 0.7;
	x[2] = 0.2;

	// CLIENT DATA
	void *cd = NULL;

	// OPTIMIZE
	cfsqp(nx,np,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh,
		mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,
		x,p,c,lambda,pFunc,cFunc,gpFunc,gcFunc,cd);

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
	pj[0] = pow((x[0]+3.e0*x[1]+x[2]),2.e0) + 4.e0*pow((x[0]-x[1]),2.e0);
}

//______________________________________________________________________________
/**
 * Evaluate the derivatives of the performance criterion.
 */
void
gpFunc(int nparam,int j,double *x,double *dpdx,
	void (*dummy)(int,int,double *,double *,void *),void *cd)
{
	double fa = 2.e0*(x[0]+3.e0*x[1]+x[2]);
	double fb = fb=8.e0*(x[0]-x[1]);

	dpdx[0] = fa + fb;
	dpdx[1] = fa*3.0 - fb;
	dpdx[2] = fa; 
}

//______________________________________________________________________________
/**
 * Evaluate the constraints.
 */
void
cFunc(int nparam,int j,double *x,double *cj,void *cd)
{
	switch (j) {
	case 1:
		*cj = pow(x[0],3.e0)-6.e0*x[1]-4.e0*x[2]+3.e0;
		break;
	case 2:
		*cj = 1.e0-x[0]-x[1]-x[2];
		break;
   }
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
	switch (j) {
	case 1:
		dcdx[0]=3.e0*x[0]*x[0];
		dcdx[1]=-6.e0;
		dcdx[2]=-4.e0;
		break;
	case 2:
		dcdx[0] = dcdx[1] = dcdx[2] = -1.e0;
		break;
	}
}
