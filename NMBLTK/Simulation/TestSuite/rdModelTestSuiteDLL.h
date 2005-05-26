// rdModelTestSuiteDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdModelTestSuiteDLL_h__
#define __rdModelTestSuiteDLL_h__

// UNIX PLATFORM
#ifdef UNIX

#define RDMODELTESTSUITE_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDMODELTESTSUITE_EXPORTS
#define RDMODELTESTSUITE_API __declspec(dllexport)
#else
#define RDMODELTESTSUITE_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdModelTestSuiteDLL_h__
