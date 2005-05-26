// rdMemory.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "rdToolsDLL.h"
//=============================================================================
#ifndef __rdMemory_h__
#define __rdMemory_h__




//=============================================================================
//=============================================================================
/**
 * A class for performing some basic memory operations.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdMemory {

//=============================================================================
// DATA
//=============================================================================
private:


//=============================================================================
// METHODS
//=============================================================================
public:
	// STRING ARRAYS
	static char** NewArrayOfStrings(int aNumStrings,int aStringLength);
	static void DeleteArrayOfStrings(int aNumPointers,char **aArray);

//=============================================================================
};	// END CLASS rdMemory
//=============================================================================
//=============================================================================

#endif // __rdMemory_h__
