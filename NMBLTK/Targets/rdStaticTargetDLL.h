// rdStaticTargetDLL.h
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
#ifndef __rdStaticTargetDLL_h__
#define __rdStaticTargetDLL_h__

// UNIX PLATFORM
#ifdef UNIX

#define RDSTATICTARGET_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDSTATICTARGET_EXPORTS
#define RDSTATICTARGET_API __declspec(dllexport)
#else
#define RDSTATICTARGET_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdStaticTargetDLL_h__
