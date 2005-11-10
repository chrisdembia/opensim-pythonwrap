// rdToolsDLL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// INCLUDES
#include "rdToolsDLL.h"
#include <iostream>

#ifdef WIN32

using namespace std;


//=============================================================================
// DLL Main Entry Point
//=============================================================================
//_____________________________________________________________________________
/**
 *	This routine is called when the dll is loaded I believe.
 */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved)
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			cout<<"\n-------------------------------------------------------\n";
			cout<<"Library rdTools...\n";
			cout<<"This product includes software developed by the\n";
			cout<<"Apache Software Foundation (http://www.apache.org/).\n";
			cout<<"-------------------------------------------------------\n\n\n";
			break;

		case DLL_THREAD_ATTACH:
			cout<<"\n-------------------------------------------------------\n";
			cout<<"Library rdTools...\n";
			cout<<"This product includes software developed by the\n";
			cout<<"Apache Software Foundation (http://www.apache.org/).\n";
			cout<<"-------------------------------------------------------\n\n\n";
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			break;
    }

    return(TRUE);
}
#endif