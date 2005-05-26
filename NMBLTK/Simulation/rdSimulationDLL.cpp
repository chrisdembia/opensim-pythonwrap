// rdSimulationDLL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdSimulationDLL.h"
#include <stdio.h>



//=============================================================================
// DLL Main Entry Point
//=============================================================================
//_____________________________________________________________________________
/**
 *	This routine is called when the dll is loaded.
 */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			//printf("rdSimulation.DllMain: process attach.\n");
			break;
		case DLL_THREAD_ATTACH:
			//printf("rdSimulation.DllMain: thread attach.\n");
			break;
		case DLL_THREAD_DETACH:
			//printf("rdSimulation.DllMain: thread detach.\n");
			break;
		case DLL_PROCESS_DETACH:
			//printf("rdSimulation.DllMain: process detach.\n");
			break;
    }

    return TRUE;
}

