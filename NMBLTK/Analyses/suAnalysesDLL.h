// suAnalyses.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suAnalysesDLL_h__
#define __suAnalysesDLL_h__

// UNIX PLATFORM
#ifndef WIN32

#define SUANALYSES_API

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef SUANALYSES_EXPORTS
#define SUANALYSES_API __declspec(dllexport)
#else
#define SUANALYSES_API __declspec(dllimport)
#endif

#endif // PLATFORM


#endif // __suAnalysesDLL_h__
