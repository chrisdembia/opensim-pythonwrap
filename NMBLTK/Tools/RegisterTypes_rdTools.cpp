// RegisterTypes_rdTools.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdObject.h>
#include "RegisterTypes_rdTools.h"
#include "rdFunctionSet.h"
#include "rdGCVSplineSet.h"
#include "suScaleSet.h"
#include "rdGCVSpline.h"
#include "rdTransform.h"
#include "rdVectorGCVSplineR1R3.h"
#include "suScale.h"

using namespace std;


//_____________________________________________________________________________
/**
 * The purpose of this routine is to register all class types exported by
 * the rdTools library.
 */
RDTOOLS_API void RegisterTypes_rdTools()
{
	cout<<"RegisterTypes_rdTools:  \n";

	rdObject::RegisterType( rdFunctionSet() );
	rdObject::RegisterType( rdGCVSplineSet() );
	rdObject::RegisterType( suScaleSet() );

	rdObject::RegisterType( rdGCVSpline() );
	rdObject::RegisterType( rdTransform() );
	rdObject::RegisterType( rdVectorGCVSplineR1R3() );
	//rdObject::RegisterType( RootSolver() );
	rdObject::RegisterType( suScale() );
}

