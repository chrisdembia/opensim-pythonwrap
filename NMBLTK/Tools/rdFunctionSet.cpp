// rdFunctionSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// INCLUDES
#include "rdMath.h"
#include "rdPropertyDbl.h"
#include "rdPropertyObjArray.h"
#include "rdFunctionSet.h"
#include "rdGCVSplineSet.h"


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
rdFunctionSet::~rdFunctionSet()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 *
 * @param aName Name of the function set.
 */
rdFunctionSet::rdFunctionSet() :
	rdSet<rdFunction>(),
	_minX(_propMinX.getValueDbl()),
	_maxX(_propMaxX.getValueDbl()),
	_minY(_propMinX.getValueDbl()),
	_maxY(_propMaxX.getValueDbl()),
	_minZ(_propMinX.getValueDbl()),
	_maxZ(_propMaxX.getValueDbl())
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Construct a function set from file.
 *
 * @param aFileName Name of the file.
 */
rdFunctionSet::rdFunctionSet(const string &aFileName) :
	rdSet<rdFunction>(aFileName),
	_minX(_propMinX.getValueDbl()),
	_maxX(_propMaxX.getValueDbl()),
	_minY(_propMinX.getValueDbl()),
	_maxY(_propMaxX.getValueDbl()),
	_minZ(_propMinX.getValueDbl()),
	_maxZ(_propMaxX.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to NULL values.
 */
void rdFunctionSet::
setNull()
{
	setType("rdFunctionSet");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Setup serialized member variables.
 */
void rdFunctionSet::
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


	// ARRAY OF FUNCTIONS
	//_propertySet.append(	new rdPropertyObjArray("functions") );
	//_functions = (rdArrayPtrs<rdFunction>*)&
	//	_propertySet.get("functions")->getValueObjArray();
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
void rdFunctionSet::
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
double rdFunctionSet::
getMinX()
{
	return(_minX);
}

//_____________________________________________________________________________
/**
 * Set the maximum x independent variable.
 *
 * @param aMaxX Maximum x.
 */
void rdFunctionSet::
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
double rdFunctionSet::
getMaxX()
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
void rdFunctionSet::
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
double rdFunctionSet::
getMinY()
{
	return(_minY);
}

//_____________________________________________________________________________
/**
 * Set the maximum y independent variable.
 *
 * @param aMaxY Maximum y.
 */
void rdFunctionSet::
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
double rdFunctionSet::
getMaxY()
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
void rdFunctionSet::
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
double rdFunctionSet::
getMinZ()
{
	return(_minZ);
}

//_____________________________________________________________________________
/**
 * Set the maximum z independent variable.
 *
 * @param aMaxZ Maximum z.
 */
void rdFunctionSet::
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
double rdFunctionSet::
getMaxZ()
{
	return(_maxZ);
}


//=============================================================================
// EVALUATION
//=============================================================================
//_____________________________________________________________________________
/**
 * Update the bounding boxes of all functions in the set.
 *
 * @see rdGCVSplineSet::UpdateBoundingBox()
 */
void rdFunctionSet::
updateBoundingBox()
{
	int i,n = _objects.getSize();
	for(i=0;i<n;i++) updateBoundingBox(i);
}
//_____________________________________________________________________________
/**
 * Update the bounding box of a specified function.
 *
 * @param aIndex Index of the function for which to update the bounding box.
 * @see rdGCVSplineSet::UpdateBoundingBox()
 */
void rdFunctionSet::
updateBoundingBox(int aIndex)
{
	rdFunction *func = get(aIndex);
	if(func==NULL) return;
	func->updateBoundingBox();
}
//_____________________________________________________________________________
/**
 * Update the bounding box for this function set.
 * The bounding box is bounding box for all functions.  The bounding box
 * is determined by looping through all the functions in this set and
 * querying each for its bounding box. Note that none of the bounding boxes
 * of the functions in this set are changed by this method.
 *
 * @see rdFunction
 */
void rdFunctionSet::
updateSetBoundingBox()
{
	int i;
	bool initialized=false;
	rdFunction *func;
	for(i=0;i<getSize();i++) {

		// GET FUNCTION
		func = get(i);
		if(func==NULL) continue;

		// INITIALIZE
		if(!initialized) {
			setMinX(func->getMinX());
			setMaxX(func->getMaxX());
			setMinY(func->getMinY());
			setMaxY(func->getMaxY());
			setMinZ(func->getMinZ());
			setMaxZ(func->getMaxZ());
			initialized = true;

		// CHECK BOUNDS
		} else {

			if(func->getMinX()<getMinX()) setMinX(func->getMinX());
			if(func->getMinY()<getMinY()) setMinY(func->getMinY());
			if(func->getMinZ()<getMinZ()) setMinZ(func->getMinZ());

			if(func->getMaxX()>getMaxX()) setMaxX(func->getMaxX());
			if(func->getMaxY()>getMaxY()) setMaxY(func->getMaxY());
			if(func->getMaxZ()>getMaxZ()) setMaxZ(func->getMaxZ());

		}
	}
}

//_____________________________________________________________________________
/**
 * Evaluate a function or one of its derivatives.
 *
 * @param aIndex Index of the function to evaluate.
 * @param aDerivOrder Order of the derivative to evaluate.
 * @param aX Value of the x independent variable.
 * @param aY Value of the y independent variable.
 * @param aZ Value of the z independent variable.
 * @return Value of the function.  If the function is NULL or undefined,
 * rdMath::NAN is returned.
 * @see rdFunction
 */
double rdFunctionSet::
evaluate(int aIndex,int aDerivOrder,double aX,double aY,double aZ) const
{
	rdFunction *func = get(aIndex);
	if(func==NULL) return(rdMath::NAN);

	return( func->evaluate(aDerivOrder,aX,aY,aZ) );
}

//_____________________________________________________________________________
/**
 * Evaluate all the functions in the function set or their derivatives.
 *
 * @param rValues Array containing the values of the functions.
 * @param aDerivOrder Order of the derivative to evaluate.
 * @param aX Value of the x independent variable.
 * @param aY Value of the y independent variable.
 * @param aZ Value of the z independent variable.
 * @return Value of the function.  If the function is NULL or undefined,
 * rdMath::NAN is returned.
 * @see rdFunction
 */
void rdFunctionSet::
evaluate(rdArray<double> &rValues,int aDerivOrder,double aX,double aY,double aZ) const
{
	int size = getSize();
	rValues.setSize(size);

	int i;
	rdFunction *func;
	for(i=0;i<size;i++) {
		func = get(i);
		if(func==NULL) {
			rValues[i] = rdMath::NAN;
		} else {
			rValues[i] = func->evaluate(aDerivOrder,aX,aY,aZ);
		}
	}
}
