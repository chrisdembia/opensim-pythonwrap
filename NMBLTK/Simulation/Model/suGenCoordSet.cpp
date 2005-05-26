#include "suGenCoordSet.h"
#include "suGenCoord.h"
#include <RD/Tools/suRange.h>
#include <RD/Tools/rdSet.h>
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suGenCoordSet::~suGenCoordSet(void)
{}
//_____________________________________________________________________________
/**
 * Constructor from a file
 */
suGenCoordSet::suGenCoordSet(const std::string &aFileName):
rdSet<suGenCoord>(aFileName)
{
}
//_____________________________________________________________________________
/**
 * Default constructor
 */
suGenCoordSet::suGenCoordSet():
rdSet<suGenCoord>()
{
}
//_____________________________________________________________________________
/** 
 * Get all range mins in an rdArray 
 **/
void suGenCoordSet::
getAllMins(rdArray<double>& aAllMins) const
{
	for(int i=0; i < getSize(); i++){
		aAllMins.append(get(i)->getRange().getMin());
	}
}
//_____________________________________________________________________________
/** 
 * Get all range maxs in an rdArray 
 **/
void suGenCoordSet::
getAllMaxs(rdArray<double>& aAllMaxs) const
{
	for(int i=0; i < getSize(); i++){
		aAllMaxs.append(get(i)->getRange().getMax());
	}
}
//_____________________________________________________________________________
/** 
 * Get all GenCoord names in an rdArray 
 **/
void suGenCoordSet::
getAllNames(rdArray<std::string>& aAllNames) const
{
	for(int i=0; i < getSize(); i++){
		aAllNames.append(get(i)->getName());
	}

}
