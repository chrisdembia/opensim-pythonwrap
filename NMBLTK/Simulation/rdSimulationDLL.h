// rdSimulationDLL.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSimulationDLL_h__
#define __rdSimulationDLL_h__

// UNIX PLATFORM
#ifdef UNIX

#define RDSIMULATION_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDSIMULATION_EXPORTS
#define RDSIMULATION_API __declspec(dllexport)
#else
#define RDSIMULATION_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdSimulationDLL_h__
