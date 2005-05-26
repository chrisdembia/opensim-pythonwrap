// INCLUDES
#include "suScaleSet.h"
//#include "rdModel.h"

using namespace std;
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suScaleSet::~suScaleSet(void)
{}

//_____________________________________________________________________________
/**
 * Constructor of a scaleSet from a file.
 */
suScaleSet::suScaleSet(const string& scalesFileName):
rdSet<suScale>(scalesFileName)
{
	setNull();
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Default constructor of a scaleSet.
 */
suScaleSet::suScaleSet():
rdSet<suScale>()
{
	setNull();
}

void suScaleSet::setNull()
{
	setType("suScaleSet");
	setName("ScaleSet");
}
