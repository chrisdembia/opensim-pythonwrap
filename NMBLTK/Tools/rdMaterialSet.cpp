// rdMaterialSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdPropertyObjArray.h"
#include "rdMaterialSet.h"
#include "rdMaterial.h"


using namespace std;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * No-arg constructor used for registration.
 *
 */
rdMaterialSet::rdMaterialSet():
rdSet<rdMaterial>()
{
	setNull();

	// TYPE
	setType("rdMaterialSet");
	setName("");
}

//_____________________________________________________________________________
/**
 * Constructor from an xml file passed in by Name.
 *
 */
rdMaterialSet::rdMaterialSet(const string &aFileName):
rdSet<rdMaterial>(aFileName)
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor
 *
 */
rdMaterialSet::rdMaterialSet(const rdMaterialSet &aMaterialSet):
rdSet<rdMaterial>(aMaterialSet)
{
	setNull();

	// ASSIGN
	*this = aMaterialSet;
}
//_____________________________________________________________________________
/**
 * Destructor
 *
 */
rdMaterialSet::~rdMaterialSet()
{
}
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdMaterialSet::
setNull()
{
}
//_____________________________________________________________________________
/**
 * Serialization support.
 */
void rdMaterialSet::
setupProperties()
{
}
//_____________________________________________________________________________
/**
 * Add a material
 *
 */
bool rdMaterialSet::
addMaterial(rdMaterial& aMaterial)
{
	if(materialExists(aMaterial.getName()))
		return(false);

	append(&aMaterial);
	return(true);
}

//_____________________________________________________________________________
/**
 * Modify/Update a material
 *
 */
bool rdMaterialSet::
updateMaterial(rdMaterial& materialToUpdate)
{
	if (!materialExists(materialToUpdate.getName()))
		return false;

	removeMaterial(materialToUpdate);
	addMaterial(materialToUpdate);

	return true;
}
//_____________________________________________________________________________
/**
 * Remove a material
 *
 */
bool rdMaterialSet::
removeMaterial(rdMaterial& materialToRemove)
{
	if (!materialExists(materialToRemove.getName()))
		return false;

	bool found = false;
	for (int i=0; i < getSize() && !found; i++){
		rdMaterial &currentMaterial = *(get(i));
		if (currentMaterial==materialToRemove){
			found= true;
			remove(i);
			break;
		}
	}
	return found;
}
//_____________________________________________________________________________
/**
 * Check if a metrial exists
 *
 */
bool rdMaterialSet::
materialExists(const string &materialName) const
{
	bool exists = false;
	for (int i=0; i < getSize(); i++){
		rdMaterial &currentMaterial = *(get(i));
		if (currentMaterial.getName() == materialName){
			exists= true;
			break;
		}
	}
	return exists;
}
//_____________________________________________________________________________
/**
 * Gets the number of materials maintained by the material manager
 *
 */
int rdMaterialSet::
getNumberOfMaterials() const
{
	return getSize();
}

//_____________________________________________________________________________
/**
 * Retrieve a material based on index 
 * if material is not found then a default material as defined by rdMaterial::getDefaultMaterial
 * is returned. This allows the caller to reliably assume that it has a const ref to a material 
 */
const rdMaterial &rdMaterialSet::
getMaterialByIndex(int idx) const
{
	return (*get(idx));
}

//_____________________________________________________________________________
/**
 * Retrieve a material based on name 
 * if material is not found then a default material as defined by rdMaterial::getDefaultMaterial
 * is returned. This allows the caller to reliably assume that it has a const ref to a material
 *
 */
const rdMaterial &rdMaterialSet::
getMaterialByName(const char *materialName) const
{
	for (int i=0; i < getSize(); i++){
		rdMaterial &currentMaterial = *(get(i));
		if (currentMaterial.getName() == materialName){
			return currentMaterial;
		}
	}
	// If material was not found return default
	return(rdMaterial::GetDefaultMaterial());
}
