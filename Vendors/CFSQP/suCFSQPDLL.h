// suCFSQPDLL.h
#ifndef __suCFSQPDLL_h__
#define __suCFSQPDLL_h__


// UNIX PLATFORM
#ifndef WIN32

#define SUCFSQP_API 

// WINDOWS PLATFORM
#else

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#ifdef SUCFSQP_EXPORTS
#define SUCFSQP_API __declspec(dllexport)
#else
#define SUCFSQP_API __declspec(dllimport)
#endif

#endif // PLATFORM

#endif // __suCFSQPDLL_h__

