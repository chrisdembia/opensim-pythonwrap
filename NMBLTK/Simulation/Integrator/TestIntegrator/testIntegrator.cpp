// testIntegrator.cpp
// Author:  Frank C. Anderson


// INCLUDES
#include <iostream>
#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Integrator/rdIntegRKF.h>
#include <NMBLTK/Simulation/Integrator/Integrand.h>
#include <NMBLTK/Simulation/integrator/TestIntegrator/SampleIntegrand.h>

using namespace std;


//_____________________________________________________________________________
/**
 * Test the integrator classes.
 */
int main(int argc, char* argv[])
{
	// CONSTRUCT INTEGRATOR
	SampleIntegrand integrand;
	rdIntegRKF rkf(&integrand);
	rkf.setTolerance(1.0e-8);
	rkf.setMaximumNumberOfSteps(10000);

	// STORAGE
	rdStorage *yStore = new rdStorage();
	yStore->setName("SampleIntegrand");
	integrand.setStateStorage(yStore);

	// CONSTRUCT STATES
	rdArray<double> y(0.0);
	y.setSize(integrand.getSize());

	// INTEGRATE
	rkf.integrate(0.0,1.0,&y[0],1.0e-8);

	// PRINT RESULTS
	cout<<"\n\nResults:\n";
	cout<< y <<endl;
	yStore->print("sampleIntegrand.sto");

	// CLEANUP
	delete yStore;

	return(0);
}


