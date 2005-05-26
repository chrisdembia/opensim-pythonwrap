// rdMaterialManager.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdPropertyObjArray.h"
#include "rdMaterialManager.h"
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
rdMaterialManager::rdMaterialManager()
{
	setNull();

	// TYPE
	setType("rdMaterialManager");
	setName("");
}

//_____________________________________________________________________________
/**
 * Constructor from an xml file passed in by Name.
 *
 */
rdMaterialManager::rdMaterialManager(const string &aFileName):
rdObject(aFileName)
{
	// NULL STATES
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Constructor from an xml element
 *
 */
rdMaterialManager::rdMaterialManager(DOMElement *aElement):
rdObject(aElement)
{
	setNull();

	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor
 *
 */
rdMaterialManager::rdMaterialManager(const rdMaterialManager &aMaterialManager):
rdObject(aMaterialManager)
{
	setNull();

	// ASSIGN
	*this = aMaterialManager;
}
//_____________________________________________________________________________
/**
 * Another incarnation of copy that's virtual.
 *
 * @param aElement XMLnode to construct rdMaterialManager from.
 */

rdObject *rdMaterialManager::
copy() const
{
	return(new rdMaterialManager(*this));
}
//_____________________________________________________________________________
/**
 * Create object from DOMElement.
 *
 * @param aElement XMLnode to construct rdMaterialManager from.
 */

rdObject* rdMaterialManager::
copy(DOMElement *aElement) const
{
	rdMaterialManager *m = new rdMaterialManager(aElement);
	*m = *this;
	m->updateFromXMLNode();
	return(m);
}
//_____________________________________________________________________________
/**
 * Destructor
 *
 */
rdMaterialManager::~rdMaterialManager()
{
}
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdMaterialManager::
setNull()
{
	_availableMaterials=NULL;
	setupSerializedMembers();
}
//_____________________________________________________________________________
/**
 * Serialization support.
 */
void rdMaterialManager::
setupSerializedMembers()
{
	_propertySet.append( new rdPropertyObjArray("Materials") );
	_availableMaterials = (rdArrayPtrs<rdMaterial> *)
		&_propertySet.get("Materials")->getValueObjArray();

}
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.
 *
 * @return Reference to this object.
 */
rdMaterialManager& rdMaterialManager::
operator=(const rdMaterialManager &aObject)
{
	// BASE CLASS
	rdObject::operator=(aObject);

	// Class Members
	*_availableMaterials = (*aObject._availableMaterials);
	return(*this);
}
//_____________________________________________________________________________
/**
 * Add a material
 *
 */
bool rdMaterialManager::
addMaterial(rdMaterial& aMaterial)
{
	if(materialExists(aMaterial.getName()))
		return(false);

	_availableMaterials->append(&aMaterial);
	return(true);
}

//_____________________________________________________________________________
/**
 * Modify/Update a material
 *
 */
bool rdMaterialManager::
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
bool rdMaterialManager::
removeMaterial(rdMaterial& materialToRemove)
{
	if (!materialExists(materialToRemove.getName()))
		return false;

	bool found = false;
	for (int i=0; i < _availableMaterials->getSize() && !found; i++){
		rdMaterial &currentMaterial = *(*_availableMaterials)[i];
		if (currentMaterial==materialToRemove){
			found= true;
			_availableMaterials->remove(i);
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
bool rdMaterialManager::
materialExists(const string &materialName) const
{
	bool exists = false;
	for (int i=0; i < _availableMaterials->getSize(); i++){
		rdMaterial &currentMaterial = *(*_availableMaterials)[i];
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
int rdMaterialManager::
getNumberOfMaterials() const
{
	return _availableMaterials->getSize();
}

//_____________________________________________________________________________
/**
 * Retrieve a material based on index 
 * if material is not found then a default material as defined by rdMaterial::getDefaultMaterial
 * is returned. This allows the caller to reliably assume that it has a const ref to a material 
 */
const rdMaterial &rdMaterialManager::
getMaterialByIndex(int idx) const
{
	const rdMaterial &retMaterial = rdMaterial::GetDefaultMaterial();
	if(idx < _availableMaterials->getSize())
		return( *(*_availableMaterials)[idx] );

	return retMaterial;
}

//_____________________________________________________________________________
/**
 * Retrieve a material based on name 
 * if material is not found then a default material as defined by rdMaterial::getDefaultMaterial
 * is returned. This allows the caller to reliably assume that it has a const ref to a material
 *
 */
const rdMaterial &rdMaterialManager::
getMaterialByName(const char *materialName) const
{
	for (int i=0; i < _availableMaterials->getSize(); i++){
		rdMaterial &currentMaterial = *(*_availableMaterials)[i];
		if (currentMaterial.getName() == materialName){
			return currentMaterial;
		}
	}
	// If material was not found return default
	return(rdMaterial::GetDefaultMaterial());
}
