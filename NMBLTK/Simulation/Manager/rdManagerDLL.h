// rdManager.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdManagerDLL_h__
#define __rdManagerDLL_h__

// UNIX
#ifndef WIN32

#define RDMANAGER_API

// WINDOWS
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDMANAGER_EXPORTS
#define RDMANAGER_API __declspec(dllexport)
#else
#define RDMANAGER_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdManagerDLL_h__
