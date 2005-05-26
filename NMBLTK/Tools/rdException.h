// rdException.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdException_h__
#define __rdException_h__


// INCLUDES
#include "rdTools.h"
#include <string>

//using namespace std;


//=============================================================================
//=============================================================================
/**
 * A class for basic exception functionality.
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
#ifdef SWIG
	#ifdef RDTOOLS_API
		#undef RDTOOLS_API
		#define RDTOOLS_API
	#endif
#endif

class RDTOOLS_API rdException {

//=============================================================================
// DATA
//=============================================================================
protected:
	/** A user set message for the exception. */
	std::string _msg;
	/** File in which the error occurred. */
	std::string _file;
	/** Line number at which the error occurred. */
	int _line;

//=============================================================================
// METHODS
//=============================================================================
public:
	// CONSTRUCTORS
	rdException(const std::string &aMsg=NULL,const std::string &aFile="",int aLine=-1);
private:
	void setNull();

public:
	// SET AND GET
	void setMessage(const std::string &aMsg);
	const char* getMessage();

	// PRINT
	void print(std::ostream &aOut);

//=============================================================================
};	// END CLASS rdException
//=============================================================================
//=============================================================================

#endif // __rdException_h__
