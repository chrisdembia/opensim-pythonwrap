// rdControlObjectSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdIO.h>
#include "rdControlObjectSet.h"


//=============================================================================
// STATICS
//=============================================================================
rdObjectArray rdControlObjectSet::_ObjectTypes;


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdControlObjectSet::~rdControlObjectSet()
{
}
//_____________________________________________________________________________
/**
 * Construct a default track object set for a specified model.
 *
 * @param aModel Model for which track objects will be set.
 */
rdControlObjectSet::rdControlObjectSet() :
	_pErrLast(0.0),_pErr(0.0),_vErrLast(0.0),_vErr(0.0),
	_w(0.0),_aDes(0.0),_a(0.0)
{
	setNull();
	constructDefaultObjects();
}
//_____________________________________________________________________________
/**
 * Construct a track object set from file.
 *
 * @param aModel Model for which track objects will be set.
 * @param aFileName Name of the file.
 */
rdControlObjectSet::rdControlObjectSet(const char *aFileName) :
	rdObjectArray(aFileName),
	_pErrLast(0.0),_pErr(0.0),_vErrLast(0.0),_vErr(0.0),
	_w(0.0),_aDes(0.0),_a(0.0)
{
	setNull();
	constructDefaultObjects();

	// CHECK FOR NULL NODE
	if(_node==NULL) return;

	// VARIABLES
	int i;
	unsigned int j;
	const char *type;
	XMLCh *tagName;
	DOMNodeList *list;
	DOMElement *elmt;
	rdControlObject *defaultObject,*object;

	// LOOP THROUGH SUPPORTED TYPES
	for(i=0;i<_defaultObjects.getFirstEmpty();i++) {

		// GET DEFAULT OBJECT
		defaultObject = (rdControlObject*)_defaultObjects.get(i);
		if(defaultObject==NULL) continue;

		// GET ELEMENTS
		type = defaultObject->getType();
		tagName = XMLString::transcode(type);
		list = _node->getElementsByTagName(tagName);
		if(tagName!=NULL) delete[] tagName;
		printf("rdControlObjectSet(aFileName): found %d elements of type %s.\n",
			list->getLength(),type);

		// CONSTRUCT
		for(j=0;j<list->getLength();j++) {

			// GET ELEMENT
			elmt = (DOMElement*) list->item(j);

			// COPY THE DEFAULT OBJECT WITH CHANGES FROM THE ELEMENT
			object = (rdControlObject*)defaultObject->copy(elmt);

			// CHANGE DEFAULT OBJECT
			if(strcmp(object->getName(),rdControlObject::DEFAULT_NAME)==0) {
				delete defaultObject;
				_defaultObjects.set(i,object);
				defaultObject = object;
				object = NULL;
			}

			// ADD
			if(object!=NULL) {
				appendTrackObject(object);
			} 
		}
	}
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this actuator to their null values.
 */
void rdControlObjectSet::
setNull()
{
	setType("rdControlObjectSet");

	_defaultObjects.reset();
	_model = NULL;
	_pErrLast.setSize(0);
	_pErr.setSize(0);
	_vErrLast.setSize(0);
	_vErr.setSize(0);
	_w.setSize(0);
	_aDes.setSize(0);
	_a.setSize(0);
}
//_____________________________________________________________________________
/**
 * Construct the default objects.
 */
void rdControlObjectSet::
constructDefaultObjects()
{
	// CONSTRUCT DEFAULT ACTUATORS
	int i;
	rdControlObject *object;
	for(i=0;i<_ObjectTypes.getFirstEmpty();i++) {
		object = (rdControlObject*)_ObjectTypes.get(i);
		if(object==NULL) continue;
		_defaultObjects.append(object->copy());
	}
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// TRACK OBJECTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Append a track object to the set.
 *
 * This method should always return NULL.  If it does not return NULL, it means
 * that an object was already stored at what was thought to be the first
 * empty location.
 *
 * @param aObject Actuator.
 * @return Pointer to the actuator previously held.
 */
rdControlObject* rdControlObjectSet::
appendTrackObject(rdControlObject *aObject)
{
	rdControlObject *prev = getTrackObject(getFirstEmpty());
	append(aObject);
	return(prev);
}
//_____________________________________________________________________________
/**
 * Set the track object at an index.
 *
 * Sending in NULL for the rdControlObject pointer essentially removes the
 * object at aIndex from the array.  Note that the caller is
 * responsible for deleting any objects that are removed from this list in
 * this way.  For this reason, the object pointer previously held at aIndex
 * is returned by this method.
 *
 * It is also permissible to send in any positive value for aIndex, and
 * there can be gaps in the array of actuators.  However, it is advisible to
 * use appendTrackObject(rdControlObject*) when adding an actutor so the array
 * of actuators remains contiguous.
 *
 * @param aIndex Array index where the actuator is to be stored.
 * @param aObject Object pointer.
 * @return Pointer to the object previously held at aIndex.
 */
rdControlObject* rdControlObjectSet::
setTrackObject(int aIndex,rdControlObject *aObject)
{
	if(aIndex>getFirstEmpty()) {
		printf("rdControlObjectSet.setActuator: WARN- setting actuator past first");
		printf(" available slot.\n");
	}

	// SET
	rdControlObject *prev = getTrackObject(aIndex);
	set(aIndex,aObject);

	return(prev);
}
//_____________________________________________________________________________
/**
 * Get the track object at an index.
 *
 * @param aIndex Array index of the object to be returned.
 * @return Object at index aIndex.
 */
rdControlObject* rdControlObjectSet::
getTrackObject(int aIndex) const
{
	return((rdControlObject*)get(aIndex));
}

//-----------------------------------------------------------------------------
// MODEL
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the model for which the tracking is performed.  The model is set
 * all rdControlObjects that are currently being managed by this set.
 *
 * @param aModel Model.
 */
void rdControlObjectSet::
setModel(rdModel *aModel)
{
	_model = aModel;

	int i;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {
		object = getTrackObject(i);
		if(object==NULL) continue;
		object->setModel(_model);
	}
}

//_____________________________________________________________________________
/**
 * Get the model for which the tracking is performed.
 *
 * @return Pointer to the model.
 */
rdModel* rdControlObjectSet::
getModel() const
{
	return(_model);
}

//-----------------------------------------------------------------------------
// FUNCTION SET - POSITIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the functions for the track objects.  Functions are set based on the
 * correspondence of the function and the track object.  For example,
 * a track object with the name "x" will search for a function or functions
 * with the name "x".  For track objects that require 3 functions, such
 * as rdControlPoint objects, the assumption is that there will be three
 * consecutive functions named "x" in the function set.  If the correct
 * number of functions is not found, the track object is disabled.
 *
 * @param aFuncSet Function set.
 * @return Pointer to the previous function set.
 */
void rdControlObjectSet::
setFunctions(rdFunctionSet &aFuncSet)
{
	// LOOP THROUGH TRACK OBJECTS
	int i,j,iFunc=0;
	int nTrk;
	const char *name;
	rdFunction *f[3];
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;

		// NAME
		name = object->getName();
		if(name==NULL) continue;
		if(strlen(name)<=0) continue;

		// FIND FUNCTION(S)
		f[0] = f[1] = f[2] = NULL;
		nTrk = object->getNumTrackFunctions();
		iFunc = aFuncSet.getIndex(name,iFunc);
		for(j=0;j<nTrk;j++) {
			f[j] = aFuncSet.getFunction(iFunc);
			if(f[j]==NULL) break;
			if(strcmp(name,f[j]->getName()) == 0) {
				iFunc++;
			} else {
				f[j] = NULL;
				break;
			}
		}
		object->setTrackFunctions(f[0],f[1],f[2]);
	}
}

//-----------------------------------------------------------------------------
// FUNCTION SET - VELOCITIES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the velocity functions for the track objects.  Functions are set based on the
 * correspondence of the function and the track object.  For example,
 * a track object with the name "x" will search for a function or functions
 * with the name "x".  For track objects that require 3 functions, such
 * as rdControlPoint objects, the assumption is that there will be three
 * consecutive functions named "x" in the function set.  If the correct
 * number of functions is not found, the track object is disabled.
 *
 * @param aFuncSet Function set.
 * @return Pointer to the previous function set.
 */
void rdControlObjectSet::
setFunctionsForVelocity(rdFunctionSet &aFuncSet)
{
	// LOOP THROUGH TRACK OBJECTS
	int i,j,iFunc=0;
	int nTrk;
	const char *name;
	rdFunction *f[3];
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;

		// NAME
		name = object->getName();
		if(name==NULL) continue;
		if(strlen(name)<=0) continue;

		// FIND FUNCTION(S)
		f[0] = f[1] = f[2] = NULL;
		nTrk = object->getNumTrackFunctions();
		iFunc = aFuncSet.getIndex(name,iFunc);
		for(j=0;j<nTrk;j++) {
			f[j] = aFuncSet.getFunction(iFunc);
			if(f[j]==NULL) break;
			if(strcmp(name,f[j]->getName()) == 0) {
				iFunc++;
			} else {
				f[j] = NULL;
				break;
			}
		}
		object->setTrackFunctionsForVelocity(f[0],f[1],f[2]);
	}
}

//-----------------------------------------------------------------------------
// FUNCTION SET - ACCELERATIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the acceleration functions for the track objects.  Functions are set based on the
 * correspondence of the function and the track object.  For example,
 * a track object with the name "x" will search for a function or functions
 * with the name "x".  For track objects that require 3 functions, such
 * as rdControlPoint objects, the assumption is that there will be three
 * consecutive functions named "x" in the function set.  If the correct
 * number of functions is not found, the track object is disabled.
 *
 * @param aFuncSet Function set.
 * @return Pointer to the previous function set.
 */
void rdControlObjectSet::
setFunctionsForAcceleration(rdFunctionSet &aFuncSet)
{
	// LOOP THROUGH TRACK OBJECTS
	int i,j,iFunc=0;
	int nTrk;
	const char *name;
	rdFunction *f[3];
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;

		// NAME
		name = object->getName();
		if(name==NULL) continue;
		if(strlen(name)<=0) continue;

		// FIND FUNCTION(S)
		f[0] = f[1] = f[2] = NULL;
		nTrk = object->getNumTrackFunctions();
		iFunc = aFuncSet.getIndex(name,iFunc);
		for(j=0;j<nTrk;j++) {
			f[j] = aFuncSet.getFunction(iFunc);
			if(f[j]==NULL) break;
			if(strcmp(name,f[j]->getName()) == 0) {
				iFunc++;
			} else {
				f[j] = NULL;
				break;
			}
		}
		object->setTrackFunctionsForAcceleration(f[0],f[1],f[2]);
	}
}

//-----------------------------------------------------------------------------
// ERRORS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the last position errors.
 * @return Array of last position errors.
 */
rdArray<double>& rdControlObjectSet::
getPositionErrorsLast()
{
	return(_pErrLast);
}
//_____________________________________________________________________________
/**
 * Get the position errors.
 * @return Array of position errors.
 */
rdArray<double>& rdControlObjectSet::
getPositionErrors()
{
	return(_pErr);
}
//_____________________________________________________________________________
/**
 * Get the last velocity errors.
 * @return Array of last velocity errors.
 */
rdArray<double>& rdControlObjectSet::
getVelocityErrorsLast()
{
	return(_vErrLast);
}
//_____________________________________________________________________________
/**
 * Get the velocity errors.
 * @return Array of velocity errors.
 */
rdArray<double>& rdControlObjectSet::
getVelocityErrors()
{
	return(_vErr);
}

//-----------------------------------------------------------------------------
// WEIGHTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the array of weights for the desired accelerations.
 * @return Array of weights.
 */
rdArray<double>& rdControlObjectSet::
getWeights()
{
	return(_w);
}

//-----------------------------------------------------------------------------
// DESIRED ACCELERATIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the desired accelerations.
 * @return Array of desired accelerations.
 */
rdArray<double>& rdControlObjectSet::
getDesiredAccelerations()
{
	return(_aDes);
}

//-----------------------------------------------------------------------------
// ACCELERATIONS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the accelerations.
 * @return Array of accelerations.
 */
rdArray<double>& rdControlObjectSet::
getAccelerations()
{
	return(_a);
}



//=============================================================================
// COMPUTATIONS
//=============================================================================
//_____________________________________________________________________________
/**
 * Record the current position errors of all track objects as the last errors
 * that were achieved during a simulation.
 *
 * This method assumes that the position errors have already been computed.
 */
void rdControlObjectSet::
recordErrorsAsLastErrors()
{
	_pErrLast.setSize(0);
	_vErrLast.setSize(0);

	int i,j;
	double e0,e1,e2;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;
		
		// POSITION ERRORS
		e0 = object->getPositionError(0);
		e1 = object->getPositionError(1);
		e2 = object->getPositionError(2);
		object->setPositionErrorLast(e0,e1,e2);

		// VELOCITY ERRORS
		e0 = object->getVelocityError(0);
		e1 = object->getVelocityError(1);
		e2 = object->getVelocityError(2);
		object->setVelocityErrorLast(e0,e1,e2);

		// SET ERRORS
		for(j=0;j<3;j++) {
			if(!object->getActive(j)) continue;
			_pErrLast.append(object->getPositionErrorLast(j));
			_vErrLast.append(object->getVelocityErrorLast(j));
		}
	}
}
//_____________________________________________________________________________
/**
 * Compute the errors for all track objects.
 *
 * @param aT Time at which to compute the errors in real time units.
 */
void rdControlObjectSet::
computeErrors(double aT)
{
	_pErr.setSize(0);
	_vErr.setSize(0);

	int i,j;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;
		
		// COMPUTE
		object->computeErrors(aT);

		// SET ERRORS
		for(j=0;j<3;j++) {
			if(!object->getActive(j)) continue;
			_pErr.append(object->getPositionError(j));
			_vErr.append(object->getVelocityError(j));
		}
	}
}
//_____________________________________________________________________________
/**
 * Compute the desired acceleration(s) for each track object.
 *
 * @param aT Time at which the desired accelerations are to be computed in
 * real time units.
 */
void rdControlObjectSet::
computeDesiredAccelerations(double aT)
{
	_w.setSize(0);
	_aDes.setSize(0);

	int i,j;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;
		
		// COMPUTE
		object->computeDesiredAccelerations(aT);

		// SET WEIGHTS AND ACCELERATIONS
		for(j=0;j<3;j++) {
			if(!object->getActive(j)) continue;
			_w.append(object->getWeight(j));
			_aDes.append(object->getDesiredAcceleration(j));
		}
	}

	//printf("rdControlObjectSet.computeDesiredAccelerations: %d ",_aDes.size());
	//printf("track goals are active.\n");
}
//_____________________________________________________________________________
/**
 * Compute the acceleration(s) for each track object.
 * The methods rdModel::deriv() or rdModel::computeAccelerations must be
 * called before this method is called for the results to be valid.
 */
void rdControlObjectSet::
computeAccelerations()
{
	_a.setSize(0);

	int i,j;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {

		// OBJECT
		object = getTrackObject(i);
		if(object==NULL) continue;
		
		// COMPUTE
		object->computeAccelerations();

		// SET WEIGHTS AND ACCELERATIONS
		for(j=0;j<3;j++) {
			if(!object->getActive(j)) continue;
			_a.append(object->getAcceleration(j));
		}
	}

	//printf("rdControlObjectSet.computeAccelerations: %d ",_a.size());
	//printf("track goals are active.\n");
}


//=============================================================================
// DEFAULT OBJECTS
//=============================================================================
//-----------------------------------------------------------------------------
// REGISTER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Register a supported object type.  Any object type that is supported
 * can be written to and read from an XML file. The object must have
 * implemented the following methods to be supported:
 *	1)	copy constructor (e.g., rdForce::rdForce(const rdForce &aForce))
 *	2)	virtual rdControlObject* copy() const,
 *	3)	virtual rdControlObject* copy(DOMElement*) const,
 *	4)	rdControlObject& operator=() (!! with the appropriate return type),
 *	5)	virtual void updateObject(bool aDeep=true),
 *	6) virtual void updateNode(bool aDeep=true), and
 * 7) virtual void generateNode(DOMElement *aParent).
 *
 * Because this method is static, registration of object types needs to be
 * done only once per process and an rdControlObjectSet does not need to be
 * instantiated to do so.
 *
 * This method makes a copy of the specified object, so the caller may
 * continue to use the spacified object for whatever purpose.
 *
 * @param aObject Object of the type to be added.
 */
void rdControlObjectSet::
RegisterType(const rdControlObject &aObject)
{
	// GET TYPE INFORMATION
	const char *type = aObject.getType();
	if(type==NULL) {
		printf("rdControlObjectSet.RegisterType: ERR- NULL type.\n");
		return;
	}
	if(strlen(type)<=0) {
		printf("rdControlObjectSet.RegisterType: ERR- no type set.\n");
		return;
	}

	// SEARCH FOR MATCHING TYPE
	// If a matching type is found, the type is not added to the default
	// list.
	int i;
	rdControlObject *object;
	for(i=0;i<_ObjectTypes.getFirstEmpty();i++) {
		object = (rdControlObject*)_ObjectTypes.get(i);
		if(object==NULL) continue;
		if(strcmp(object->getType(),type)==0) {
			printf("rdControlObjectSet.RegisterType: type %s ",type);
			printf("is already supported.\n");
			return;
		}
	}

	// ADD
	object = (rdControlObject*)aObject.copy();
	_ObjectTypes.append(object);
}


//=============================================================================
// XML
//=============================================================================
//-----------------------------------------------------------------------------
// UPDATE OBJECT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 *
 * @param aDeep If true, update this object and all its child objects
 * (that is, member variables that are rdObject's); if false, update only
 * the member variables that are not rdObject's.
 */
void rdControlObjectSet::
updateObject(bool aDeep)
{
	if(_node==NULL) return;

	// BASE CLASS
	rdObjectArray::updateObject(aDeep);

	// DEEP?
	if(!aDeep) return;

	// ACTUATORS
	int i;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {
		object = getTrackObject(i);
		if(object==NULL) continue;
		object->updateObject();
	}
}

//-----------------------------------------------------------------------------
// UPDATE NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the XML node representing this object.
 */
void rdControlObjectSet::
updateNode(bool aDeep)
{
	// BASE CLASS
	rdObjectArray::updateNode();

	// DEEP?
	if(!aDeep) return;

	// ACTUATORS
	int i;
	rdControlObject *object;
	for(i=0;i<getFirstEmpty();i++) {
		object = getTrackObject(i);
		if(object==NULL) continue;
		object->updateNode();
	}
}

//-----------------------------------------------------------------------------
// GENERATE NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Generate an XML node representing this object.
 *
 * @param aParent Intended parent of the node to be generated.  If
 * aParent is NULL, the intent is for this object to serve as the root
 * element of a new document.
 */
void rdControlObjectSet::
generateNode(DOMElement *aParent)
{
	// BASE CLASS
	rdObjectArray::generateNode(aParent);
	if(_node==NULL) return;

	// MEMBER DATA


	// DEFAULT OBJECTS
	int i;
	rdControlObject *object;
	for(i=0;i<_defaultObjects.getFirstEmpty();i++) {
		object = (rdControlObject*)_defaultObjects.get(i);
		if(object==NULL) continue;
		object->generateNode(_node);
	}

	// OBJECTS
	for(i=0;i<getFirstEmpty();i++) {
		object = getTrackObject(i);
		if(object==NULL) continue;
		object->generateNode(_node);
	}
}
