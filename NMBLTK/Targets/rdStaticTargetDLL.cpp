// rdStaticTargetDLL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// CONFIDENTIAL
//
// The material contain within this file is the sole property of
// Realistic Dynamics, Inc., and may not be read, copied, or distributed
// without the expressed writen consent of Realistic Dynamics, Inc.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "rdStaticTargetDLL.h"
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
			printf("rdStaticTarget.DllMain: process attach.\n");
			break;
		case DLL_THREAD_ATTACH:
			printf("rdStaticTarget.DllMain: thread attach.\n");
			break;
		case DLL_THREAD_DETACH:
			printf("rdStaticTarget.DllMain: thread detach.\n");
			break;
		case DLL_PROCESS_DETACH:
			printf("rdStaticTarget.DllMain: process detach.\n");
			break;
    }

    return TRUE;
}

