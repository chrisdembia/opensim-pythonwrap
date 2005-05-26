// rdModelDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdModelDLL_h__
#define __rdModelDLL_h__

// UNIX PLATFORM
#ifdef UNIX

#define RDMODEL_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDMODEL_EXPORTS
#define RDMODEL_API __declspec(dllexport)
#else
#define RDMODEL_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdModelDLL_h__
