// rdModelTestSuite.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdModelTestSuite_h__
#define __rdModelTestSuite_h__


//============================================================================
// INCLUDE
//============================================================================
#include "rdModelTestSuiteDLL.h"
#include <NMBLTK/Simulation/Model/rdModel.h>


//=============================================================================
//=============================================================================
/**
 * A class for testing the basic functionality of an rdModel instance.
 *
 * @author Frank C. Anderson, James M. Ziegler
 * @version 1.0
 */
class RDMODELTESTSUITE_API rdModelTestSuite  
{
//=============================================================================
// DATA
//=============================================================================
private:
	/** File pointer to the output file. */
	FILE *_outFPT;


//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	rdModelTestSuite();


	//--------------------------------------------------------------------------
	// MODEL
	//--------------------------------------------------------------------------
	bool Test(rdModel *aModel);
	bool TestNumbers(rdModel *aModel);
	bool TestNames(rdModel *aModel);
	bool TestStates(rdModel *aModel);
	bool TestPseudoStates(rdModel *aModel);
	bool TestGravity(rdModel *aModel);
	bool TestBodies(rdModel *aModel);
	bool TestKinematics(rdModel *aModel);
	bool TestLoads(rdModel *aModel);
	bool TestDerivatives(rdModel *aModel);
	bool TestMassMatrix(rdModel *aModel);
	bool TestJacobian(rdModel *aModel);
	bool TestOrientationUtilities(rdModel *aModel);
	bool TestContact(rdModel *aModel);
	bool TestActuation(rdModel *aModel);

	// CONTACTS
	bool TestContacts(rdModel *aModel);

	// ACTUATORS
	bool TestActuators(rdModel *aModel);


//=============================================================================
};	// END of class rdModelTestSuite
//=============================================================================
//=============================================================================

#endif // __rdModelTestSuite_h__


