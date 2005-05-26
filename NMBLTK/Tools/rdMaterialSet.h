// rdMaterialSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdMaterialSet_h__
#define __rdMaterialSet_h__

#include "rdTools.h"
#include "rdObject.h"
#include "rdArrayPtrs.h"
#include "rdSet.h"
#include "rdMaterial.h"

class rdXMLNode;
class rdXMLDocument;


#ifndef SWIG
//template class RDTOOLS_API rdSet<rdMaterial>;
#endif


//=============================================================================
/**
 * A class for representing the list of rdMaterials in a model
 * It maintains a list (eventually a hashTable between names and rdMaterials)
 *
 * @author Ayman Habib
 * @version 1.0
 */
class RDTOOLS_API rdMaterialSet: public rdSet<rdMaterial>
{

//=============================================================================
// DATA
//=============================================================================
protected:
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdMaterialSet();
	rdMaterialSet(const std::string &aFileName);
	rdMaterialSet(const rdMaterialSet &aMaterial);
	virtual ~rdMaterialSet();

private:
	void setNull();
protected:
	// Serialization support
	virtual void setupProperties();
	
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
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
};	// END of class rdMaterialSet
//=============================================================================
//=============================================================================

#endif //__rdMaterialSet_h__
