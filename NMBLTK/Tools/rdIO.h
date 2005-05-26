// rdIO.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdIO_h__
#define __rdIO_h__


// INCLUDES
#include "rdTools.h"


// DEFINES
const int rdIO_STRLEN = 2048;
const int rdIO_STRING_INCREMENT = 2048;


//=============================================================================
//=============================================================================
/**
 * A class for performing input and output.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdIO {

//=============================================================================
// DATA
//=============================================================================
public:
	/** Default size of a statically or locally allocated character array. */
	static const int STRLEN;
	/** Increment by which the size of character strings are incremented. */
	static const int STRING_INCREMENT;

private:
	// NUMBER OUTPUT
	/** Specifies whether number output is in scientific or float format. */
	static bool _Scientific;
	/** Specifies number of digits of padding in number output. */ 
	static int _Pad;
	/** Specifies the precision of number output. */
	static int _Precision;
	/** The output format string. */
	static char _DoubleFormat[256];


//=============================================================================
// METHODS
//=============================================================================
public:
	// FILE NAMES
	static char* ConstructDateAndTimeStamp();
	// NUMBER OUTPUT FORMAT
	static void SetScientific(bool aTrueFalse);
	static bool GetScientific();
	static void SetDigitsPad(int aPad);
	static int GetDigitsPad();
	static void SetPrecision(int aPlaces);
	static int GetPrecision();
	static const char*
		GetDoubleOutputFormat();
private:
	static void ConstructDoubleOutputFormat();

public:
	// READ
	static char* ReadToTokenLine(FILE *aFP,const char *aToken);
	static char* ReadLine(FILE *aFP);
	static int ComputeLineLength(FILE *aFP);
	static int ComputeNumberOfSteps(double aTI,double aTF,double aDT);
	static char* ReadCharacters(FILE *aFP,int aNChar);
	static FILE* OpenFile(const char *aFileName,const char *aMode);

//=============================================================================
};	// END CLASS rdIO
//=============================================================================
//=============================================================================

#endif // __rdIO_h__
