// testUT.c


//==============================================================================
// INCLUDE
//==============================================================================
#include <stdlib.h>
#include <rdSimModel.h>
#include "rdSimModelUTWalking.h"



//______________________________________________________________________________


using namespace OpenSim;
/**
 * Code for testing rdSimModelUTWalking.
 */
int main(int argc,char *argv)
{

	// CONSTRUCT A THE UTWALKING MODEL
	rdSimModelUTWalking *model = new rdSimModelUTWalking();

	// CONTROLS
	int nx = model->getNX();
	double *x = new double[nx];
	for(i=0;i<nx;i++) x[i] = 1.0;
	
	// INITIAL STATES
	int ny = model->getNY();
	double y = new double[ny];
	double *yi = model->getInitialStates();
	for(i=0;i<ny;i++) {
		y[i] = yi[i];
		printf("y[%d] = %lf\n",y[i]);
	}

	return(0);
}

