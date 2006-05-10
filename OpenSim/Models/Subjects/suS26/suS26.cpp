// suS26.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Author:  Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================

#include <OpenSim/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
#include "suS26.h"
#include <OpenSim/Simulation/Control/ControlConstant.h>
#include <OpenSim/Simulation/Control/ControlLinear.h>
#include <OpenSim/Simulation/Control/ControlLinearNode.h>
#include <OpenSim/Simulation/Control/ControlSet.h>
#include <OpenSim/Simulation/Model/Force.h>
#include <OpenSim/Simulation/Model/GeneralizedForce.h>
#include <OpenSim/Simulation/Model/MarkerSet.h>
#include <OpenSim/Tools/ScaleSet.h>
#include <OpenSim/Tools/Range.h>


//=============================================================================
// CONSTANTS


using namespace OpenSim;
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



static double	coms[16][3] = {
						{0.086666026551,     0.025999807965,		0.000000},// 0 calcn_rp 
						{0.086666026551,     0.025999807965,		0.000000},// 1 calcn_lp             
						{-0.061272880771,    0.000000,				0.000000},// 2 pelvis
						{0.000000,			-0.155964671962,		0.000000},// 3 femur_r
						{0.000000,			-0.152325035757,		0.000000},// 4 tibia_r
						{0.000000,			0.000000,				0.000000},// 5 patella_r
						{0.000000,			0.000000,				0.000000},// 6 talus_r
						{0.086666026551,     0.025999807965,		0.000000},// 7 calcn_r
						{0.029986445187,     0.005199961593,		-0.015166554646},// 8 toes_r
						{0.000000,			-0.155964671962,		0.000000},// 9 femur_l
						{0.000000,			-0.152325035757,		0.000000},//10 tibia_l
						{0.000000,			0.000000,				0.000000},//11 patella_l
						{0.000000,			0.000000,				0.000000},//12 talus_l
						{0.086666026551,	0.025999807965,			0.000000},//13 calcn_l
						{0.029986445187,	0.005199961593,			0.015166554646},//14 toes_l
						{-0.025999807965,	0.277331284963,			0.000000} //15 torso
}; 

static char* geomFileNames[] =
{ 
	"S26//bones//foot.vtp",
	"S26//bones//l_foot.vtp",
	"S26//bones//sacrum.vtp",
	"S26//bones//pelvis.vtp",
	"S26//bones//l_pelvis.vtp",
	"S26//bones//femur.vtp",
	"S26//bones//tibia.vtp",
	"S26//bones//fibula.vtp",
	"S26//bones//pat.vtp",
	"S26//bones//talus.vtp",
	"S26//bones//foot.vtp",
	"S26//bones//bofoot.vtp",
	"S26//bones//l_femur.vtp",
	"S26//bones//l_tibia.vtp",
	"S26//bones//l_fibula.vtp",
	"S26//bones//l_patella.vtp",
	"S26//bones//l_talus.vtp",
	"S26//bones//l_foot.vtp",
	"S26//bones//l_bofoot.vtp",
	"S26//bones//hat_spine.vtp",
	"S26//bones//hat_jaw.vtp",
	"S26//bones//hat_skull.vtp",
	"S26//bones//hat_ribs.vtp"
};
static char* groundGeomFileName = "S26//bones//Cube.vtp";

static int numGeomFiles[] =
{
	1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 4
};

static double	scales[16][3] = {
{0.866660265508    , 0.866660265508    , 0.866660265508},// 0 calcn_rp 
{0.866660265508    , 0.866660265508    , 0.866660265508},// 1 calcn_lp  
{0.866660265508    , 0.866660265508    , 0.866660265508},// 2 pelvis
{0.917439246834    , 0.917439246834    , 0.917439246834},// 3 femur_r
{0.815881284182    , 0.815881284182    , 0.815881284182},// 4 tibia_r
{0.866660265508    , 0.866660265508    , 0.866660265508},// 5 patella_r
{0.815881284182    , 0.815881284182    , 0.815881284182},// 6 talus_r
{0.866660265508    , 0.866660265508    , 0.866660265508},// 7 calcn_r
{0.866660265508    , 0.866660265508    , 0.866660265508},// 8 toes_r
{0.917439246834    , 0.917439246834    , 0.917439246834},// 9 femur_l
{0.815881284182    , 0.815881284182    , 0.815881284182},//10 tibia_l
{0.866660265508    , 0.866660265508    , 0.866660265508},//11 patella_l
{0.815881284182    , 0.815881284182    , 0.815881284182},//12 talus_l
{0.866660265508    , 0.866660265508    , 0.866660265508},//13 calcn_l
{0.866660265508    , 0.866660265508    , 0.866660265508},//14 toes_l
{0.866660265508    , 0.866660265508    , 0.866660265508} //15 torso
};

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
suS26::suS26(const std::string &aParametersFileName,ContactForceSet *aContacts) :
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
		Body *currentBody = getBody(i);	
		currentBody->setNumGeometryFiles(numFiles);
		// Set actual file names
		for(int subSegment=0; subSegment<numFiles; subSegment++, curIndex++){
			fullFileName = new char[strlen(resourceDirectory)+strlen(geomFileNames[curIndex])+1];
			strcpy(fullFileName, resourceDirectory);
			strcat(fullFileName, geomFileNames[curIndex]);
			currentBody->setGeometryFileName(subSegment, fullFileName);
			delete[] fullFileName;
		}
		currentBody->setScaleFactors(scales[i]);
		currentBody->setCenterOfMass(coms[i]);
	}
	Body *groundBody = getBody(getNB());
	groundBody->setNumGeometryFiles(1);
	fullFileName = new char[strlen(resourceDirectory)+strlen(groundGeomFileName)+1];
	strcpy(fullFileName, resourceDirectory);
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
	Object::RegisterType(ControlLinearNode());
	Object::RegisterType(ControlLinear());
	Object::RegisterType(ControlSet());
	ActuatedModel_SDFast::RegisterTypes();
	Object::RegisterType(ControlConstant());
	Object::RegisterType(Force());
	Object::RegisterType(GeneralizedForce());
	Object::RegisterType(Marker());
	Object::RegisterType(MarkerSet());

	Object::RegisterType(Scale());
	Object::RegisterType(ScaleSet());

}
