// rdToolsDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdToolsDLL_h__
#define __rdToolsDLL_h__



// IMPORT AND EXPORT
// UNIX
#ifndef WIN32

	#define RDTOOLS_API


// WINDOWS
#else

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#ifdef RDTOOLS_EXPORTS
		#define RDTOOLS_API __declspec(dllexport)
	#else
		#define RDTOOLS_API __declspec(dllimport)
	#endif

#endif



#endif // __rdToolsDLL_h__
