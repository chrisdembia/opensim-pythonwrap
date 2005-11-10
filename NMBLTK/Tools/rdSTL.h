// rdSTL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSTL_h__
#define __rdSTL_h__


// INCLUDES
#include "rdToolsDLL.h"
#include <vector>


// STANDARD TEMPLATE LIBRARY (STL) GENERATION
// UNIX
#ifndef WIN32


// WINDOWS
// On Windows systems the following lines are necessary to export
// templates from DLL's and import them into other executables.
#else

	// TEMPLATE GENERATION
	template class RDTOOLS_API std::vector<int>;
	template class RDTOOLS_API std::vector<double>;

#endif


#endif // __rdSTL_h__
