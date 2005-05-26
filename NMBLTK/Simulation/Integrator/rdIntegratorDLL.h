// rdIntegratorDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdIntegratorDLL_h__
#define __rdIntegratorDLL_h__


// UNIX PLATFORM
#ifdef UNIX

#define RDINTEGRATOR_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDINTEGRATOR_EXPORTS
#define RDINTEGRATOR_API __declspec(dllexport)
#else
#define RDINTEGRATOR_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdIntegratorDLL_h__
