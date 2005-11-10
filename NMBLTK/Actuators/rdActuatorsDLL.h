// rdActuators.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdActuatorsDLL_h__
#define __rdActuatorsDLL_h__

// UNIX PLATFORM
#ifndef WIN32

#define RDACTUATORS_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef RDACTUATORS_EXPORTS
#define RDACTUATORS_API __declspec(dllexport)
#else
#define RDACTUATORS_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __rdActuatorsDLL_h__
