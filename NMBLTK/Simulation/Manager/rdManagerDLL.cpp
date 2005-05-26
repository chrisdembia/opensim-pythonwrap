// rdManagerDLL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdManagerDLL.h"
#include <stdio.h>

//=============================================================================
// DLL Main Entry Point
//=============================================================================
//_____________________________________________________________________________
/**
 *	This routine is called when this dll is attached and detached.
 */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved)
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			printf("rdManager.DllMain: process attach.\n");
			break;
		case DLL_THREAD_ATTACH:
			printf("rdManager.DllMain: thread attach.\n");
			break;
		case DLL_THREAD_DETACH:
			printf("rdManager.DllMain: thread detach.\n");
			break;
		case DLL_PROCESS_DETACH:
			printf("rdManager.DllMain: process detach.\n");
			break;
    }
    return TRUE;
}
