// suS26.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================

#include <NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
#include "suS26.h"
#include <NMBLTK/Simulation/Control/rdControlConstant.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/Control/rdControlLinearNode.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Simulation/Model/rdForce.h>
#include <NMBLTK/Simulation/Model/rdGeneralizedForce.h>
#include <NMBLTK/Simulation/Model/suMarkerSet.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/Tools/suRange.h>


//=============================================================================
// CONSTANTS
/*
-1 $ground  
// 0 calcn_rp             
// 1 calcn_lp             
// 2 pelvis              
// 3 femur_r  
// 4 tibia_r  
// 5 patella_r*
// 6 talus_r*  
// 7 calcn_r*  
// 8 toes_r*   
// 9 femur_l*  
//10 tibia_l*  
//11 patella_l*
//12 talus_l * 
//13 calcn_l*  
//14 toes_l*   
//15 torso*    
*/
//=============================================================================

static char* geomFileNames[] =
{ 
	"bones//foot.vtp",
	"bones//l_foot.vtp",
	"bones//sacrum.vtp",
	"bones//pelvis.vtp",
	"bones//l_pelvis.vtp",
	"bones//femur.vtp",
	"bones//tibia.vtp",
	"bones//fibula.vtp",
	"bones//pat.vtp",
	"bones//talus.vtp",
	"bones//foot.vtp",
	"bones//bofoot.vtp",
	"bones//l_femur.vtp",
	"bones//l_tibia.vtp",
	"bones//l_fibula.vtp",
	"bones//l_patella.vtp",
	"bones//l_talus.vtp",
	"bones//l_foot.vtp",
	"bones//l_bofoot.vtp",
	"bones//hat_spine.vtp",
	"bones//hat_jaw.vtp",
	"bones//hat_skull.vtp",
	"bones//hat_ribs.vtp"
};
static char* groundGeomFileName = "bones//Cube.vtp";

static int numGeomFiles[] =
{
	1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 4
};

#include "s26_geom.h"
//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suS26::~suS26()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
suS26::suS26(const std::string &aParametersFileName,rdContactForceSet *aContacts) :
	suPipeline40Workflow(aParametersFileName,aContacts)
{
	setNull();
	// Tie bodies to geometry
	constructGeometry();
	setName("suS26");
}


//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set member variables to their appropriate null values.
 */
void suS26::
setNull()
{
}
//_____________________________________________________________________________
/**
 * Read system description and fill in data to describe visible properties of model.
 */
void suS26::
constructGeometry()
{
	char *resourceDirectory= getenv("SIMTK_RESOURCE_DIR");
	char *curDirectory = ".";
	if (!resourceDirectory)
		resourceDirectory = curDirectory;
	int curIndex=0;
	char *fullFileName;
	// Body Geometry and preferences
	for(int i=0;i<getNB();i++) {
		// Actual body has been constructed by constructBodies()
		if (i==getGroundID())
			continue;
		int numFiles = numGeomFiles[i];
		rdBody *currentBody = getBody(i);	
		currentBody->setNumGeometryFiles(numFiles);
		// Set actual file names
		for(int subSegment=0; subSegment<numFiles; subSegment++, curIndex++){
			fullFileName = new char[strlen(resourceDirectory)+strlen(geomFileNames[curIndex])+3];
			strcpy(fullFileName, resourceDirectory);
			strcat(fullFileName, "//");
			strcat(fullFileName, geomFileNames[curIndex]);
			currentBody->setGeometryFileName(subSegment, fullFileName);
			delete[] fullFileName;
		}
		currentBody->setScaleFactors(scales[i]);
		currentBody->setCenterOfMass(coms[i]);
	}

	rdBody *groundBody = getBody(getNB());
	groundBody->setNumGeometryFiles(1);
	fullFileName = new char[strlen(resourceDirectory)+strlen(groundGeomFileName)+3];
	strcpy(fullFileName, resourceDirectory);
	strcat(fullFileName, "//");
	strcat(fullFileName, groundGeomFileName);
	groundBody->setGeometryFileName(0, fullFileName);
	delete[] fullFileName;
}
//=============================================================================
// Register Types: registers the types of objects that will be used by the 
// rdBlock Model so that it can be read and written to xml files (serialized)
//=============================================================================

void suS26::
RegisterTypes()
{
	/* This list should be broken so that
	 * 1. a Model doesn't have to be loaded before we load Actuators, Contacts, ...
	 * 2. rdBlock registers only classes it defines (rdBlock()) everything else
	 *	  would be registered in a base class and is done by calling inherited::RegisterTypes()
	 * 3. Plugins will define new types so they should use the mechanism in 2. for encapsulation.
	 */
	rdObject::RegisterType(rdControlLinearNode());
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlSet());
	rdObject::RegisterType(rdControlConstant());
}
