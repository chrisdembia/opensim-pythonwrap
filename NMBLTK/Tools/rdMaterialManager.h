// rdMaterialManager.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdMaterialManager_h__
#define __rdMaterialManager_h__

#include "rdTools.h"
#include "rdObject.h"
#include "rdMaterial.h"

class rdXMLNode;
class rdXMLDocument;

//=============================================================================
/**
 * A class for representing the list of rdMaterials in a model
 * It maintains a list (eventually a hashTable between names and rdMaterials)
 *
 * @author Ayman Habib
 * @version 1.0
 */
class RDTOOLS_API rdMaterialManager: public rdObject
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/* serialized data members */
	/** List of rdMaterials in the model */
	rdArrayPtrs<rdMaterial>		*_availableMaterials;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdMaterialManager();
	rdMaterialManager(const std::string &aFileName);
	rdMaterialManager(DOMElement *aElement);
	rdMaterialManager(const rdMaterialManager &aMaterial);
	virtual ~rdMaterialManager();

	// Other operators to support rdObject API
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
protected:
	// Serialization support
	virtual void setupSerializedMembers();
	
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdMaterialManager& operator=(const rdMaterialManager &aMaterialManager);
#endif

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	bool addMaterial(rdMaterial &materialToAdd);
	bool updateMaterial(rdMaterial &materialToUpdate);
	bool removeMaterial(rdMaterial &materialToRemove);
	bool materialExists(const std::string &materialName) const;
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	int getNumberOfMaterials() const;
	const rdMaterial& getMaterialByIndex(int idx) const;
	const rdMaterial& getMaterialByName(const char *materialName) const;

//=============================================================================
};	// END of class rdMaterialManager
//=============================================================================
//=============================================================================

#endif //__rdMaterialManager_h__
