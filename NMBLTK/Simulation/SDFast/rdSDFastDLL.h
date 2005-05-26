// rdSDFastDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2001 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSDFastDLL_h__
#define __rdSDFastDLL_h__


// UNIX PLATFORM
#ifdef UNIX

#define RDSDFAST_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDSDFAST_EXPORTS
#define RDSDFAST_API __declspec(dllexport)
#else
#define RDSDFAST_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdSDFastDLL_h__

