// RootSolver.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include <iostream>
#include <string>
#include <float.h>
#include "rdMath.h"
#include "RootSolver.h"


using namespace std;


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
RootSolver::~RootSolver()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
RootSolver::
RootSolver(VectorFunctionUncoupledNxN *aFunc)
{
	setNull();
	_function = aFunc;
}

//-----------------------------------------------------------------------------
// CONSTRUCTION METHODS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set all member variables to NULL values.
 */
void RootSolver::
setNull()
{
	_function = NULL;
}


//=============================================================================
// SOLVE
//=============================================================================
//_____________________________________________________________________________
/**
 * Solve for the roots.
 *
 * 
 */
rdArray<double> RootSolver::
solve(const rdArray<double> &ax,const rdArray<double> &bx,
		const rdArray<double> &tol)
{
	int i;
	int N = _function->getNX();

	rdArray<double> a(0.0,N),b(0.0,N),c(0.0,N);
	rdArray<double> fa(0.0,N),fb(0.0,N),fc(0.0,N);
	rdArray<double> prev_step(0.0,N);
	rdArray<double> tol_act(0.0,N);
	rdArray<double> p(0.0,N);
	rdArray<double> q(0.0,N);
	rdArray<double> new_step(0.0,N);

	bool finished = false;
	rdArray<int>   converged(0,N);


	// INITIALIZATIONS
	a = ax;
	b = bx;
	_function->evaluate(a,fa);
	_function->evaluate(b,fb);
	c = a;
	fc = fa;


	// ITERATION LOOP
	int iter;
	for(iter=0;!finished;iter++) {

		// ABSCISSAE MANIPULATION LOOP
		for(i=0;i<N;i++) {

			// Continue?
			// If a function is already converged no need to do any manipulation.
			if(converged[i]) continue;
   
			// Make c on opposite side of b.
			// (was down at very bottom)
			 if( (fb[i]>0.0 && fc[i]>0.0) || (fb[i]<0.0 && fc[i]<0.0) ) {
				c[i] = a[i];
				fc[i] = fa[i];
			 }

			// Record previous step
			prev_step[i] = b[i] - a[i];

			// Swap data for b to be the best approximation.
			if( fabs(fc[i]) < fabs(fb[i]) ) {
				a[i] = b[i];  b[i] = c[i];  c[i] = a[i];
				fa[i]= fb[i]; fb[i]= fc[i]; fc[i]= fa[i];
			}
			tol_act[i] = 2.0*DBL_EPSILON*fabs(b[i]) + 0.5*tol[i];
			new_step[i] = 0.5 * (c[i]-b[i]);

			// Converged?
			// Original convergence test:
			if(fabs(new_step[i])<=tol_act[i] || fb[i]==(double)0.0 ) {
				converged[i] = iter;
				continue;
			}

			// Interpolate if prev_step was large enough and in true direction
			if( fabs(prev_step[i])>=tol_act[i] && fabs(fa[i])>fabs(fb[i]) ) {
				register double t1,cb,t2;
				cb = c[i]-b[i];

				// Only two distinct roots, must use linear interpolation.
				if(a[i]==c[i]) {
					t1 = fb[i]/fa[i];
					p[i] = cb*t1;
					q[i] = 1.0 - t1;

				// Quadratic interpolation
				} else {
					q[i] = fa[i]/fc[i];  t1 = fb[i]/fc[i];  t2 = fb[i]/fa[i];
					p[i] = t2 * ( cb*q[i]*(q[i]-t1) - (b[i]-a[i])*(t1-1.0) );
					q[i] = (q[i]-1.0) * (t1-1.0) * (t2-1.0);
				}

				// Change sign of q or p?
				if( p[i]>(double)0.0 ) {
					q[i] = -q[i];
				} else {
					p[i] = -p[i];
				}

				// If the interpolate is bad, use bissection.
				if( p[i]<(0.75*cb*q[i] - 0.5*fabs(tol_act[i]*q[i]))	&& p[i]<fabs(0.5*prev_step[i]*q[i]) )
					new_step[i] = p[i]/q[i];
			}

			// Adjust step to be not less than tolerance.
			if( fabs(new_step[i]) < tol_act[i] )
				if( new_step[i] > (double)0.0 )
					new_step[i] = tol_act[i];
				else
					new_step[i] = -tol_act[i];

			// Save previous approximation.
			a[i] = b[i];  fa[i] = fb[i];


			b[i] += new_step[i];
			 
		} // END ABSCISSAE LOOP
	 

		// NEW FUNCTION EVALUATION
		_function->evaluate(b,fb);


		// FINISHED?
		for(i=0;i<N;i++) {
			finished = true;
			if(!converged[i]) {
				finished = false;
				break;
			}
		}
	}

	// PRINT
	cout<<"\n\nRootSolver:  found solution in "<<iter<<" iterations.\n";
	cout<<"converged array:\n";
	cout<<converged<<endl<<endl;
	//cout<<"roots:\n";
	//cout<<b<<endl<<endl;
	//cout<<"errors:\n";
	//cout<<fb<<endl;
	
	return(b);
}
