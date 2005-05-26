// rdModelDLL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdModelDLL.h"
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
			printf("rdModel.DllMain: process attach.\n");
			break;
		case DLL_THREAD_ATTACH:
			printf("rdModel.DllMain: thread attach.\n");
			break;
		case DLL_THREAD_DETACH:
			printf("rdModel.DllMain: thread detach.\n");
			break;
		case DLL_PROCESS_DETACH:
			printf("rdModel.DllMain: process detach.\n");
			break;
    }

    return TRUE;
}

