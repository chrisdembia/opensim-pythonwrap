// osimCFSQPDLL.h
#ifndef __osimCFSQPDLL_h__
#define __osimCFSQPDLL_h__


// UNIX PLATFORM
#ifndef WIN32

#define OSIMCFSQP_API 

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#ifdef OSIMCFSQP_EXPORTS
#define OSIMCFSQP_API __declspec(dllexport)
#else
#define OSIMCFSQP_API __declspec(dllimport)
#endif

#endif // PLATFORM

#endif // __osimCFSQPDLL_h__

