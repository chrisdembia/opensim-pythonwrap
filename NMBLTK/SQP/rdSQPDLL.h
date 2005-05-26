// rdSQPDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSQPDLL_h__
#define __rdSQPDLL_h__

// UNIX PLATFORM
#ifdef UNIX

#define RDSQP_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDSQP_EXPORTS
#define RDSQP_API __declspec(dllexport)
#else
#define RDSQP_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdSQPDLL_h__
