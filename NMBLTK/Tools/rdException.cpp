// rdException.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include <iostream>
#include <string>
#include "rdTools.h"
#include "rdException.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aTrueFalse Scientific notation if true, and float if false.
 */
rdException::
rdException(const string &aMsg,const string &aFile,int aLine)
{
	setNull();

	setMessage(aMsg);
	_file = aFile;
	_line = aLine;
}

//-----------------------------------------------------------------------------
// NULL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the member variables to NULL values.
 */
void rdException::
setNull()
{
	setMessage("");
	_line = -1;
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// MESSAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the exception message.
 *
 * @param aMsg Message.
 */
void rdException::
setMessage(const string &aMsg)
{
	_msg = aMsg;
}
//_____________________________________________________________________________
/**
 * Get the exception message.
 *
 * @return Message.
 */
const char* rdException::
getMessage()
{
	return(_msg.c_str());
}


//=============================================================================
// IO
//=============================================================================
//-----------------------------------------------------------------------------
// PRINT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Print the exception to an output stream.
 *
 * @param aOut Output stream
 */
void rdException::
print(ostream &aOut)
{
	// HEADER
	aOut << "\nrdException:\n  ";

	// MESSAGE
	aOut << _msg << '\n';

	// FILE
	if(_file.size()>0) {
		aOut << "  file= " << _file << '\n';
	}

	// LINE
	if(_line>=0) {
		aOut << "  line= " << _line << '\n';
	}

	// RETURN
	aOut << '\n';
}

