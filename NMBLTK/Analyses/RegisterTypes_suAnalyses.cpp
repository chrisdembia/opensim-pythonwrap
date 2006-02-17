// RegisterTypes_suAnalyses.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdObject.h>
#include "RegisterTypes_suAnalyses.h"
#include "suKinematics.h"
#include "InvestigationPerturbation.h"
#include "InvestigationForward.h"

using namespace std;

//_____________________________________________________________________________
/**
 * The purpose of this routine is to register all class types exported by
 * the suAnalyses library.
 */
SUANALYSES_API void RegisterTypes_suAnalyses()
{
	cout<<"RegisterTypes_suAnalyses:  \n";

	rdObject::RegisterType( InvestigationPerturbation() );
	rdObject::RegisterType( InvestigationForward() );

	rdObject::RegisterType( suKinematics() );
}

