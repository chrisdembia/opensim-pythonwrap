// rdTestUT.c


//==============================================================================
// INCLUDE
//==============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/TestSuite/rdModelTestSuite.h>
#include <RD/Models/UTWalking8/rdUTWalking8.h>


using namespace std;


//______________________________________________________________________________
/**
  * Code for testing rdUTWalking8.
 */
int main(int argc,char *argv)
{
	// CONSTRUCT A THE UTWALKING MODEL
	rdUTWalking8 *model = new rdUTWalking8();

	// TEST ALL
	rdModelTestSuite testSuite;
	testSuite.Test(model);

	// CLEANUP
	delete model;

	return(0);
}

