// rdSDFastDLL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2001 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdSDFastDLL.h"
#include <stdio.h>


//=============================================================================
// DLL Main Entry Point
//=============================================================================
//_____________________________________________________________________________
/**
 *	This routine is called when the dll is loaded I believe.
 */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			printf("rdSDFast.DllMain: process attach.\n");
			break;
		case DLL_THREAD_ATTACH:
			printf("rdSDFast.DllMain: thread attach.\n");
			break;
		case DLL_THREAD_DETACH:
			printf("rdSDFast.DllMain: thread detach.\n");
			break;
		case DLL_PROCESS_DETACH:
			printf("rdSDFast.DllMain: process detach.\n");
			break;
    }

    return TRUE;
}

