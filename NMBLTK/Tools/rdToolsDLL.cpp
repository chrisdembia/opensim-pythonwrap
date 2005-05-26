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
#include <NMBLTK/Security/rdSecurity.h>
#include <iostream>

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
	long securityStatus;

    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			cout<<"\n-------------------------------------------------------\n";
			cout<<"Library rdTools...\n";
			cout<<"This product includes software developed by the\n";
			cout<<"Apache Software Foundation (http://www.apache.org/).";
			securityStatus = rdSecurity::VerifyAuthorization();
			rdSecurity::PrintAuthorizationStatus(securityStatus);
			cout<<"-------------------------------------------------------\n\n\n";
			if(securityStatus<0) exit(0);
			break;

		case DLL_THREAD_ATTACH:
			cout<<"\n-------------------------------------------------------\n";
			cout<<"Library rdTools...\n";
			cout<<"This product includes software developed by the\n";
			cout<<"Apache Software Foundation (http://www.apache.org/).";
			securityStatus = rdSecurity::VerifyAuthorization();
			rdSecurity::PrintAuthorizationStatus(securityStatus);
			cout<<"-------------------------------------------------------\n\n\n";
			if(securityStatus<0) exit(0);
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			break;
    }

    return(TRUE);
}
