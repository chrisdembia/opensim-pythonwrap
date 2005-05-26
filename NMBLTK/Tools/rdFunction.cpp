// rdFunction.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// INCLUDES
#include "rdFunction.h"
#include "rdPropertyDbl.h"
#include "rdMath.h"

using namespace std;


//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdFunction::~rdFunction()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdFunction::rdFunction() :
	_minX(_propMinX.getValueDbl()),
	_maxX(_propMaxX.getValueDbl()),
	_minY(_propMinY.getValueDbl()),
	_maxY(_propMaxY.getValueDbl()),
	_minZ(_propMinZ.getValueDbl()),
	_maxZ(_propMaxZ.getValueDbl())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Construct a function from an XML Element.
 *
 * @param aElement XML element.
 */
rdFunction::rdFunction(DOMElement *aElement) :
	rdObject(aElement),
	_minX(_propMinX.getValueDbl()),
	_maxX(_propMaxX.getValueDbl()),
	_minY(_propMinY.getValueDbl()),
	_maxY(_propMaxY.getValueDbl()),
	_minZ(_propMinZ.getValueDbl()),
	_maxZ(_propMaxZ.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aFunction Function to copy.
 */
rdFunction::rdFunction(const rdFunction &aFunction) :
	rdObject(aFunction),
	_minX(_propMinX.getValueDbl()),
	_maxX(_propMaxX.getValueDbl()),
	_minY(_propMinY.getValueDbl()),
	_maxY(_propMaxY.getValueDbl()),
	_minZ(_propMinZ.getValueDbl()),
	_maxZ(_propMaxZ.getValueDbl())
{
	setNull();

	// ASSIGN
	setEqual(aFunction);
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to NULL values.
 */
void rdFunction::
setNull()
{
	setType("rdFunction");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  This involves both generating
 * the properties and connecting them to the local pointers used to access
 * the serialized member variables.
 */
void rdFunction::
setupProperties()
{
	// X
	_propMinX.setName("min_x");
	_propMinX.setValue(0.0);
	_propertySet.append( &_propMinX );

	_propMaxX.setName("max_x");
	_propMaxX.setValue(0.0);
	_propertySet.append( &_propMaxX );

	// Y
	_propMinY.setName("min_y");
	_propMinY.setValue(0.0);
	_propertySet.append( &_propMinY );

	_propMaxY.setName("max_y");
	_propMaxY.setValue(0.0);
	_propertySet.append( &_propMaxY );


	// Z
	_propMinZ.setName("min_z");
	_propMinZ.setValue(0.0);
	_propertySet.append( &_propMinZ );

	_propMaxZ.setName("max_z");
	_propMaxZ.setValue(0.0);
	_propertySet.append( &_propMaxZ );

}

//_____________________________________________________________________________
/**
 * Set all member variables equal to the members of another object.
 * Note that this method is private.  It is only meant for copying the data
 * members defined in this class.  It does not, for example, make any changes
 * to data members of base classes.
 */
void rdFunction::
setEqual(const rdFunction &aFunction)
{
	setMinX(aFunction.getMinX());
	setMinY(aFunction.getMinY());
	setMinZ(aFunction.getMinZ());
	setMaxX(aFunction.getMaxX());
	setMaxY(aFunction.getMaxY());
	setMaxZ(aFunction.getMaxZ());
}

//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
rdFunction& rdFunction::
operator=(const rdFunction &aFunction)
{
	// BASE CLASS
	rdObject::operator=(aFunction);

	// DATA
	setEqual(aFunction);

	return(*this);
}


//=============================================================================
// SET AND GET
//=============================================================================
//-----------------------------------------------------------------------------
// MIN AND MAX X
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum x independent variable.
 *
 * @param aMinX Minimum x.
 */
void rdFunction::
setMinX(double aMinX)
{
	_minX = aMinX;
}
//_____________________________________________________________________________
/**
 * Get the minimum x independent variable.
 *
 * @return Minimum x.
 */
double rdFunction::
getMinX() const
{
	return(_minX);
}

//_____________________________________________________________________________
/**
 * Set the maximum x independent variable.
 *
 * @param aMaxX Maximum x.
 */
void rdFunction::
setMaxX(double aMaxX)
{
	_maxX = aMaxX;
}
//_____________________________________________________________________________
/**
 * Get the maximum x independent variable.
 *
 * @return Maximum x.
 */
double rdFunction::
getMaxX() const
{
	return(_maxX);
}

//-----------------------------------------------------------------------------
// MIN AND MAX Y
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum y independent variable.
 *
 * @param aMinY Minimum y.
 */
void rdFunction::
setMinY(double aMinY)
{
	_minY = aMinY;
}
//_____________________________________________________________________________
/**
 * Get the minimum y independent variable.
 *
 * @return Minimum y.
 */
double rdFunction::
getMinY() const
{
	return(_minY);
}

//_____________________________________________________________________________
/**
 * Set the maximum y independent variable.
 *
 * @param aMaxY Maximum y.
 */
void rdFunction::
setMaxY(double aMaxY)
{
	_maxY = aMaxY;
}
//_____________________________________________________________________________
/**
 * Get the maximum y independent variable.
 *
 * @return Maximum y.
 */
double rdFunction::
getMaxY() const
{
	return(_maxY);
}

//-----------------------------------------------------------------------------
// MIN AND MAX Z
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the minimum z independent variable.
 *
 * @param aMinZ Minimum z.
 */
void rdFunction::
setMinZ(double aMinZ)
{
	_minZ = aMinZ;
}
//_____________________________________________________________________________
/**
 * Get the minimum z independent variable.
 *
 * @return Minimum z.
 */
double rdFunction::
getMinZ() const
{
	return(_minZ);
}

//_____________________________________________________________________________
/**
 * Set the maximum z independent variable.
 *
 * @param aMaxZ Maximum z.
 */
void rdFunction::
setMaxZ(double aMaxZ)
{
	_maxZ = aMaxZ;
}
//_____________________________________________________________________________
/**
 * Get the maximum z independent variable.
 *
 * @return Maximum z.
 */
double rdFunction::
getMaxZ() const
{
	return(_maxZ);
}


//=============================================================================
// EVALUATE
//=============================================================================
