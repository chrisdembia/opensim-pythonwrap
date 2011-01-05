// GeometryPath.cpp
// Author: Peter Loan, Ajay Seth
/*
 * Copyright (c)  2009, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//=============================================================================
// INCLUDES
//=============================================================================
#include "GeometryPath.h"
#include <OpenSim/Simulation/SimbodyEngine/Coordinate.h>
#include <OpenSim/Simulation/SimbodyEngine/Body.h>
#include <OpenSim/Simulation/SimbodyEngine/SimbodyEngine.h>
#include "ConditionalPathPoint.h"
#include "PointForceDirection.h"
#include <OpenSim/Simulation/Wrap/PathWrapPoint.h>
#include <OpenSim/Simulation/Wrap/WrapResult.h>
#include <OpenSim/Simulation/Wrap/PathWrap.h>
#include "CoordinateSet.h"
#include "Model.h"
#include <OpenSim/Common/SimmMacros.h>
#include <OpenSim/Common/NaturalCubicSpline.h>
#include <OpenSim/Common/DebugUtilities.h>
#include "SimTKsimbody.h"

#include <OpenSim/Simulation/MomentArmSolver.h>

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;
using SimTK::Vec3;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
GeometryPath::GeometryPath() :
   ModelComponent(),
	_pathPointSetProp(PropertyObj("", PathPointSet())),
	_pathPointSet((PathPointSet&)_pathPointSetProp.getValueObj()),
 	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj()),
	_pathWrapSetProp(PropertyObj("", PathWrapSet())),
	_pathWrapSet((PathWrapSet&)_pathWrapSetProp.getValueObj()),
	_subsystemIndex(SimTK::InvalidIndex),
	_owner(NULL)
{
	setNull();
	setupProperties();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
GeometryPath::~GeometryPath()
{

	VisibleObject* disp;
	if ((disp = getDisplayer())){
		 // Free up allocated geometry objects
		disp->freeGeometry();
	}
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aPath GeometryPath to be copied.
 */
GeometryPath::GeometryPath(const GeometryPath &aPath) :
   ModelComponent(aPath),
	_pathPointSetProp(PropertyObj("", PathPointSet())),
	_pathPointSet((PathPointSet&)_pathPointSetProp.getValueObj()),
 	_displayerProp(PropertyObj("", VisibleObject())),
   _displayer((VisibleObject&)_displayerProp.getValueObj()),
	_pathWrapSetProp(PropertyObj("", PathWrapSet())),
	_pathWrapSet((PathWrapSet&)_pathWrapSetProp.getValueObj()),
	_subsystemIndex(SimTK::InvalidIndex),
	_owner(NULL)
{
	setNull();
	setupProperties();
	copyData(aPath);
}

//_____________________________________________________________________________
/**
 * Copy this path and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this GeometryPath.
 */
Object* GeometryPath::copy() const
{
	GeometryPath *path = new GeometryPath(*this);
	return path;
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one GeometryPath to another.
 *
 * @param aPath GeometryPath to be copied.
 */
void GeometryPath::copyData(const GeometryPath &aPath)
{
	_pathPointSet = aPath._pathPointSet;
	_displayer = aPath._displayer;
	_pathWrapSet = aPath._pathWrapSet;
}

//_____________________________________________________________________________
/**
 * Set the data members of this GeometryPath to their null values.
 */
void GeometryPath::setNull()
{
	setType("GeometryPath");

}

//_____________________________________________________________________________
/**
 * Perform set up functions after model has been deserialized or copied.
 *
 * @param aModel The model containing this path.
 */
void GeometryPath::setup(Model& aModel) {

	// Base class
	ModelComponent::setup(aModel);

	// aModel will be NULL when objects are being registered.
	if (&aModel == NULL)
		return;

   // Name the path points based on the current path
   // (i.e., the set of currectly active points is numbered
   // 1, 2, 3, ...).
	namePathPoints(0);

	for (int i = 0; i < _pathWrapSet.getSize(); i++)
 		_pathWrapSet[i].setup(aModel, *this);

	for (int i = 0; i < _pathPointSet.getSize(); i++){
		_pathPointSet.get(i).setup(aModel, *this);
		// GeometryPath points depend on the path itself
		// Removing the dependency since path points now display as part of the
		// path itself, extracted directly from the set of line segments
		// representing the path path. -Ayman 02/07
		//getDisplayer()->addDependent(_pathPointSet.get(i)->getDisplayer());
	}

	_displayer.setOwner(this);
}

//_____________________________________________________________________________
/**
 * Create the SimTK state, dicrete and/or cache for this GeometryPath.
 */
 void GeometryPath::createSystem(SimTK::MultibodySystem& system) const 
{
	ModelComponent::createSystem(system);
    // Beyond the const Component get the index so we can access the SimTK::Force later
	GeometryPath* mutableThis = const_cast<GeometryPath *>(this);

	mutableThis->_subsystemIndex = getIndexOfSubsystemForAllocations();

    // allocate a slot to save the current length of the path in the cache
	// given that the path is dependent on q's only, this variable should be valid at Position
	mutableThis->addCacheVariable<double>("length", 0.0, SimTK::Stage::Position);
	Array<PathPoint *> pathPrototype;
	mutableThis->addCacheVariable<Array<PathPoint *> >("current_path", pathPrototype, SimTK::Stage::Position);
	mutableThis->addCacheVariable<Array<PathPoint *> >("current_display_path", pathPrototype, SimTK::Stage::Position);
}

void GeometryPath::initState( SimTK::State& s) const
{
	// Beyond the const Component get the index so we can access the SimTK::Force later
	GeometryPath* mutableThis = const_cast<GeometryPath *>(this);

	// keep track of the length index
	mutableThis->_lengthIndex = getCacheVariableIndex("length");
	
	// keep track of the path index
	mutableThis->_currentPathIndex = getCacheVariableIndex("current_path");

	// keep track of the display path index
	mutableThis->_currentDisplayPathIndex = getCacheVariableIndex("current_display_path");

}


void GeometryPath::setLength( const SimTK::State& s, double length ) const {
    SimTK::Value<double>::downcast(s.updCacheEntry( _subsystemIndex, _lengthIndex)).upd() = length;
}

void GeometryPath::setPreScaleLength( const SimTK::State& s, double length ) {
    _preScaleLength = length;
}
double GeometryPath::getPreScaleLength( const SimTK::State& s) const {
    return( _preScaleLength);
}

//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void GeometryPath::setupProperties()
{
	_pathPointSetProp.setName("PathPointSet");
	_propertySet.append(&_pathPointSetProp);

	_displayerProp.setName("display");
	_propertySet.append(&_displayerProp);

	_pathWrapSetProp.setName("PathWrapSet");
	_propertySet.append(&_pathWrapSetProp);
}

//_____________________________________________________________________________
/**
 * Set the name of the path. This method overrides the one in Object
 * so that the path points can be [re]named accordingly.
 *
 * @param aName The new name of the path.
 */
void GeometryPath::setName(const string &aName)
{
	// base class
	ModelComponent::setName(aName);

	// Rename all of the path points.
	namePathPoints(0);
}

//_____________________________________________________________________________
/**
 * Name the path points based on their position in the set. To keep the
 * names up to date, this method should be called every time the path changes.
 *
 * @param aStartingIndex The index of the first path point to name.
 */
void GeometryPath::namePathPoints(int aStartingIndex)
{
	char indx[5];
	for (int i = aStartingIndex; i < _pathPointSet.getSize(); i++)
	{
		sprintf(indx,"%d",i+1);
		PathPoint& point = _pathPointSet.get(i);
		if(point.getName()=="" && _owner){
			point.setName(_owner->getName() + "-P" + indx);
		}
	}
}

//_____________________________________________________________________________
/**
 * get the current path of the path
 *
 * @return The array of currently active path points.
 * 
 */
const OpenSim::Array <PathPoint*> & GeometryPath:: 
		getCurrentPath(const SimTK::State& s)  const
{
    compute(s);   // compute checks if path needs to be recomputed

	return( SimTK::Value<Array<PathPoint*> >::downcast(s.getCacheEntry( _subsystemIndex, _currentPathIndex)).get() );
}

OpenSim::Array <PathPoint*> & GeometryPath:: 
updCurrentPath(const SimTK::State& s) const {

	return( SimTK::Value<Array<PathPoint*> >::downcast(s.updCacheEntry( _subsystemIndex, _currentPathIndex)).upd() );
}

/** get the the path as PointForceDirections directions */
void GeometryPath::getPointForceDirections(const SimTK::State& s, OpenSim::Array<PointForceDirection*> *rPFDs) const
{
	int i;
	PathPoint* start;
	PathPoint* end;
	const OpenSim::Body* startBody;
	const OpenSim::Body* endBody;
    const Array<PathPoint*>& currentPath = getCurrentPath(s);

	int np = currentPath.getSize();

	const SimbodyEngine& engine = _model->getSimbodyEngine();

	rPFDs->ensureCapacity(np);
	
	for (i = 0; i < np; i++){
		PointForceDirection *pfd = new PointForceDirection(currentPath[i]->getLocation(), currentPath[i]->getBody(), Vec3(0));
		rPFDs->append(pfd);
	}

	for (i = 0; i < np-1; i++) {
		start = currentPath[i];
		end = currentPath[i+1];
		startBody = &start->getBody();
		endBody = &end->getBody();

		if (startBody != endBody)
		{
			Vec3 posStart, posEnd;
			Vec3 direction(0);

			// Find the positions of start and end in the inertial frame.
			engine.getPosition(s, start->getBody(), start->getLocation(), posStart);
			engine.getPosition(s, end->getBody(), end->getLocation(), posEnd);

			// Form a vector from start to end, in the inertial frame.
			direction = (posEnd - posStart).normalize();

			// Get resultant direction at each point 
			rPFDs->get(i)->addToDirection(direction);
			rPFDs->get(i+1)->addToDirection(-direction);
		}
	}
}

//_____________________________________________________________________________
/**
 * get the current display path of the path
 *
 * @return The array of currently active path points, plus points along the
 * surfaces of the wrap objects (if any).
 * 
 */
const OpenSim::Array<PathPoint*>& GeometryPath::getCurrentDisplayPath(const SimTK::State& s) 
{
	// update the geometry to make sure the current display path is up to date.
    updateGeometry(s);

	return( SimTK::Value<Array<PathPoint*> >::downcast(s.getCacheEntry( _subsystemIndex, _currentDisplayPathIndex)).get() );
}
OpenSim::Array <PathPoint*> & GeometryPath:: 
updCurrentDisplayPath(const SimTK::State& s) const {

	return( SimTK::Value<Array<PathPoint*> >::downcast(s.updCacheEntry( _subsystemIndex, _currentDisplayPathIndex)).upd() );
}

//_____________________________________________________________________________
/**
 * updateGeometrySize updates the size of the array of geometry items to be of the
 * correct size based on changes to the path.
 * 
 */
void GeometryPath::updateGeometrySize(const SimTK::State& s)
{
	int numberOfSegements = _displayer.countGeometry();
    OpenSim::Array<PathPoint*>& currentDisplayPath = updCurrentDisplayPath(s);

	// Track whether we're creating geometry from scratch or
	// just updating
	bool update = (numberOfSegements!=0);  
	int newNumberOfSegments=currentDisplayPath.getSize()-1;
	if (newNumberOfSegments <= 0)
		return;
	// update geom array to have correct number of entries
	if (!update || (update && (newNumberOfSegments != numberOfSegements))){	
		if (newNumberOfSegments > numberOfSegements){ // add entries
			for(int segment = numberOfSegements; 
						segment < newNumberOfSegments; 
						segment++){
							Geometry *g = new LineGeometry();
							g->setFixed(false);
							_displayer.addGeometry(g);
						}

		}
		else {	// remove entries
			for(int segment = numberOfSegements-1;
						segment >= newNumberOfSegments; 
						segment--) // Remove back to front so no array packing is needed
				_displayer.removeGeometry(_displayer.getGeometry(segment));
		}
	}
}
//_____________________________________________________________________________
/**
 * updateGeometryLocations updates the locations of the array of geometry items 
 * to be in the right place based changes to the path.
 * 
 */
void GeometryPath::updateGeometryLocations(const SimTK::State& s)
{
	SimTK::Vec3 globalLocation;
	SimTK::Vec3 previousPointGlobalLocation;
    OpenSim::Array<PathPoint*>& currentDisplayPath = updCurrentDisplayPath(s);

	for (int i = 0; i < currentDisplayPath.getSize(); i++){
		PathPoint* nextPoint =currentDisplayPath.get(i);
		// xform point to global frame
		const Vec3& location=nextPoint->getLocation();
		const OpenSim::Body& body = nextPoint->getBody();
		if (i > 0){
			previousPointGlobalLocation = globalLocation;
		}
		_model->getSimbodyEngine().transformPosition(s, body, location, globalLocation);
		// Make a segment between globalLocation, previousPointGlobalLocation
		if (i > 0){
			// Geometry will be deleted when the object is deleted.
			LineGeometry *g = static_cast<LineGeometry *>(_displayer.getGeometry(i-1));
			g->setPoints(previousPointGlobalLocation, globalLocation);
		}
	}
}
//_____________________________________________________________________________
/**
 * Update the geometric representation of the path.
 * The resulting geometry is maintained at the VisibleObject layer.
 * This function should not be made public. It is called internally
 * by compute() only when the path has changed.
 * 
 */
void GeometryPath::updateGeometry(const SimTK::State& s)
{
    // check if the current path needs to recomputed
    compute(s);

    // if display path is current do not need to recompute it
    if (s.isCacheValueRealized(_subsystemIndex, _currentDisplayPathIndex)) return;
   
    updateDisplayPath(s);
    updateGeometrySize(s);
    updateGeometryLocations(s);

    // mark the currentDisplayPath as current 
    s.markCacheValueRealized(_subsystemIndex, _currentDisplayPathIndex);
}

//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @param aPath The path from which to copy its data
 * @return Reference to this object.
 */
GeometryPath& GeometryPath::operator=(const GeometryPath &aPath)
{
	// base class
	ModelComponent::operator=(aPath);

	copyData(aPath);

	return(*this);
}


//=============================================================================
// GET
//=============================================================================
//-----------------------------------------------------------------------------
// LENGTH
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Compute the total length of the path.
 *
 * @return Total length of the path.
 */
double GeometryPath::getLength( const SimTK::State& s) const {

    compute(s);  // compute checks if path needs to be recomputed

    return( SimTK::Value<double>::downcast(s.getCacheEntry( _subsystemIndex, _lengthIndex)).get());
}

//=============================================================================
// UTILITY
//=============================================================================
//_____________________________________________________________________________
/**
 * Add a new path point, with default location, to the path.
 *
 * @param aIndex The position in the pathPointSet to put the new point in.
 * @param aBody The body to attach the point to.
 * @return Pointer to the newly created path point.
 */
PathPoint* GeometryPath::addPathPoint(const SimTK::State& s, int aIndex, OpenSim::Body& aBody)
{
	PathPoint* newPoint = new PathPoint();
	newPoint->setBody(aBody);
	Vec3& location = newPoint->getLocation();
	placeNewPathPoint(s, location, aIndex, aBody);
	newPoint->setup(getModel(), *this);
	_pathPointSet.insert(aIndex, newPoint);

	// Rename the path points starting at this new one.
	namePathPoints(aIndex);

	// Update start point and end point in the wrap instances so that they
	// refer to the same path points they did before the new point
	// was added. These indices are 1-based.
	aIndex++;
	for (int i=0; i<_pathWrapSet.getSize(); i++) {
		int startPoint = _pathWrapSet.get(i).getStartPoint();
		int endPoint = _pathWrapSet.get(i).getEndPoint();
		if (startPoint != -1 && aIndex <= startPoint)
			_pathWrapSet.get(i).setStartPoint(s,startPoint + 1);
		if (endPoint != -1 && aIndex <= endPoint)
			_pathWrapSet.get(i).setEndPoint(s,endPoint + 1);
	}


	return newPoint;
}

PathPoint* GeometryPath::appendNewPathPoint(const std::string& proposedName, 
								OpenSim::Body& aBody, const SimTK::Vec3& aPositionOnBody)
{
	PathPoint* newPoint = new PathPoint();
	newPoint->setBody(aBody);
	newPoint->setName(proposedName);
	for (int i=0; i<3; i++) newPoint->setLocationCoord(i, aPositionOnBody[i]);
	_pathPointSet.append(newPoint);

	return newPoint;
}

//_____________________________________________________________________________
/**
 * Determine an appropriate default XYZ location for a new path point.
 * Note that this method is internal and should not be called directly on a new point
 *    as the point is not really added to the path (done in addPathPoint() instead)
 * @param aOffset The XYZ location to be determined.
 * @param aIndex The position in the pathPointSet to put the new point in.
 * @param aBody The body to attach the point to.
 */
void GeometryPath::placeNewPathPoint(const SimTK::State& s, SimTK::Vec3& aOffset, int aIndex, const OpenSim::Body& aBody)
{
	// The location of the point is determined by moving a 'distance' from 'base' along
	// a vector from 'start' to 'end.' 'base' is the existing path point that is
	// in or closest to the index aIndex. 'start' and 'end' are existing path points--
	// which ones depends on where the new point is being added. 'distance' is 0.5 for points
	// added to the middle of a path (so the point appears halfway between the two adjacent
	// points), and 0.2 for points that are added to either end of the path. If there is only
	// one point in the path, the new point is put 0.01 units away in all three dimensions.
	if (_pathPointSet.getSize() > 1) {
	   int start, end, base;
	   double distance;
		if (aIndex == 0) {
			start = 1;
			end = 0;
			base = end;
			distance = 0.2;
		} else if (aIndex >= _pathPointSet.getSize()) {
			start = aIndex - 2;
			end = aIndex - 1;
			base = end;
			distance = 0.2;
		} else {
			start = aIndex;
			end = aIndex - 1;
			base = start;
			distance = 0.5;
		}
	   const Vec3& startPt = _pathPointSet.get(start).getLocation();
	   const Vec3& endPt = _pathPointSet.get(end).getLocation();
	   const Vec3& basePt = _pathPointSet.get(base).getLocation();
		Vec3 startPt2(0.0);
		Vec3 endPt2(0.0);
	   getModel().getSimbodyEngine().transformPosition(s, _pathPointSet.get(start).getBody(), startPt, aBody, startPt2);
	   getModel().getSimbodyEngine().transformPosition(s, _pathPointSet.get(end).getBody(), endPt, aBody, endPt2);
		aOffset = basePt + distance * (endPt2 - startPt2);
	} else if (_pathPointSet.getSize() == 1){
		int foo = 0;
		for (int i = 0; i < 3; i++) {
         aOffset[i] = _pathPointSet.get(foo).getLocation()[i] + 0.01;
		}
	}
	else {	// first point, do nothing?
	}
}

//_____________________________________________________________________________
/**
 * See if a path point can be deleted. All paths must have at least two
 * active path points to define the path.
 *
 * @param aIndex The index of the point to delete.
 * @return Whether or not the point can be deleted.
 */
bool GeometryPath::canDeletePathPoint( int aIndex)
{
	// A path point can be deleted only if there would remain
	// at least two other fixed points.
	int numOtherFixedPoints = 0;
	for (int i = 0; i < _pathPointSet.getSize(); i++) {
		if (i != aIndex) {
			if (!_pathPointSet.get(i).isA("ConditionalPathPoint"))
				numOtherFixedPoints++;
		}
	}

	if (numOtherFixedPoints >= 2)
		return true;

	return false;
}

//_____________________________________________________________________________
/**
 * Delete a path point.
 *
 * @param aIndex The index of the point to delete.
 * @return Whether or not the point was deleted.
 */
bool GeometryPath::deletePathPoint(const SimTK::State& s, int aIndex)
{
	if (canDeletePathPoint(aIndex) == false)
		return false;

	_pathPointSet.remove(aIndex);

	// rename the path points starting at the deleted position
	namePathPoints(aIndex);

	// Update start point and end point in the wrap instances so that they
	// refer to the same path points they did before the point was
	// deleted. These indices are 1-based. If the point deleted is start
	// point or end point, the path wrap range is made smaller by one point.
	aIndex++;
	for (int i=0; i<_pathWrapSet.getSize(); i++) {
	  	int startPoint = _pathWrapSet.get(i).getStartPoint();
	  	int endPoint = _pathWrapSet.get(i).getEndPoint();
		if ((startPoint != -1 && aIndex < startPoint) || (startPoint > _pathPointSet.getSize()))
			_pathWrapSet.get(i).setStartPoint(s, startPoint - 1);
		if (endPoint > 1 && aIndex <= endPoint && ((endPoint > startPoint) || (endPoint > _pathPointSet.getSize())))
			_pathWrapSet.get(i).setEndPoint(s, endPoint - 1);
	}


	return true;
}

//_____________________________________________________________________________
/**
 * Replace a path point in the set with another point. The new one is made a
 * member of all the same groups as the old one, and is inserted in the same
 * place the old one occupied.
 *
 *	@param aOldPathPoint Path point to remove.
 *	@param aNewPathPoint Path point to add.
 */
bool GeometryPath::replacePathPoint(const SimTK::State& s, PathPoint* aOldPathPoint, PathPoint* aNewPathPoint) 
{
	if (aOldPathPoint != NULL && aNewPathPoint != NULL) {
		int count = 0;
		int index = _pathPointSet.getIndex(aOldPathPoint);
		// If you're switching from non-via to via, check to make sure that the path
		// will be left with at least 2 non-via points.
		ConditionalPathPoint* oldVia = dynamic_cast<ConditionalPathPoint*>(aOldPathPoint);
		ConditionalPathPoint* newVia = dynamic_cast<ConditionalPathPoint*>(aNewPathPoint);
		if (oldVia == NULL && newVia != NULL) {
			for (int i=0; i<_pathPointSet.getSize(); i++) {
				if (i != index) {
					if (dynamic_cast<ConditionalPathPoint*>(&_pathPointSet.get(i)) == NULL)
						count++;
				}
			}
		} else {
			count = 2;
		}
		if (count >= 2 && index >= 0) {
			_pathPointSet.set(index, aNewPathPoint, true);
			setup(*_model);
			return true;
		}
	}
	return false;
}

//_____________________________________________________________________________
/**
 * Create a new wrap instance and add it to the set.
 *
 * @param aWrapObject The wrap object to use in the new wrap instance.
 */
void GeometryPath::addPathWrap(const SimTK::State& s, WrapObject& aWrapObject)
{
	PathWrap* newWrap = new PathWrap();
	newWrap->setWrapObject(aWrapObject);
	newWrap->setMethod(PathWrap::hybrid);
	newWrap->setup(getModel(), *this);
	_pathWrapSet.append(newWrap);

}

//_____________________________________________________________________________
/**
 * Move a wrap instance up in the list. Changing the order of wrap instances for
 * a path may affect how the path wraps over the wrap objects.
 *
 * @param aIndex The index of the wrap instance to move up.
 */
void GeometryPath::moveUpPathWrap(const SimTK::State& s, int aIndex)
{
	if (aIndex > 0) {
	   _pathWrapSet.setMemoryOwner(false); // so the wrap object is not deleted by remove()
	   PathWrap& wrap = _pathWrapSet.get(aIndex);
	   _pathWrapSet.remove(aIndex);
	   _pathWrapSet.insert(aIndex - 1, &wrap);
	   _pathWrapSet.setMemoryOwner(true);
	}

}

//_____________________________________________________________________________
/**
 * Move a wrap instance down in the list. Changing the order of wrap instances for
 * a path may affect how the path wraps over the wrap objects.
 *
 * @param aIndex The index of the wrap instance to move down.
 */
void GeometryPath::moveDownPathWrap(const SimTK::State& s, int aIndex)
{
	if (aIndex < _pathWrapSet.getSize() - 1) {
	   _pathWrapSet.setMemoryOwner(false); // so wrap is not deleted by remove()
	   PathWrap& wrap = _pathWrapSet.get(aIndex);
	   _pathWrapSet.remove(aIndex);
	   _pathWrapSet.insert(aIndex + 1, &wrap);
	   _pathWrapSet.setMemoryOwner(true);
	}

}

//_____________________________________________________________________________
/**
 * Delete a wrap instance.
 *
 * @param aIndex The index of the wrap instance to delete.
 */
void GeometryPath::deletePathWrap(const SimTK::State& s, int aIndex)
{
	_pathWrapSet.remove(aIndex);

}

//=============================================================================
// SCALING
//=============================================================================
//_____________________________________________________________________________
/**
 * Perform computations that need to happen before the path is scaled.
 * For this object, that entails calculating and storing the path
 * length in the current body position.
 *
 * @param aScaleSet XYZ scale factors for the bodies.
 */
void GeometryPath::preScale(const SimTK::State& s, const ScaleSet& aScaleSet)
{
	setPreScaleLength( s,  getLength(s) );
}

//_____________________________________________________________________________
/**
 * Scale the path based on XYZ scale factors for each body.
 *
 * @param aScaleSet XYZ scale factors for the bodies.
 * @return Whether path was successfully scaled or not.
 */
void GeometryPath::scale(const SimTK::State& s, const ScaleSet& aScaleSet)
{
	for (int i = 0; i < _pathPointSet.getSize(); i++)
	{
		const string& bodyName = _pathPointSet.get(i).getBodyName();
		for (int j = 0; j < aScaleSet.getSize(); j++)
		{
			Scale& aScale = aScaleSet.get(j);
			if (bodyName == aScale.getSegmentName())
			{
				Vec3 scaleFactors(1.0);
				aScale.getScaleFactors(scaleFactors);
				_pathPointSet.get(i).scale(s, scaleFactors);
			}
		}
	}
}

//_____________________________________________________________________________
/**
 * Perform computations that need to happen after the path is scaled.
 * For this object, that entails updating the path.
 *
 * @param aScaleSet XYZ scale factors for the bodies.
 */
void GeometryPath::postScale(const SimTK::State& s, const ScaleSet& aScaleSet)
{
	// Recalculate the path. This will also update the geometry.
	// Done here since scale is invoked before bodies are scaled
	// so we may not have enough info to update (e.g. wrapping, via points)
	compute(s);
}

//--------------------------------------------------------------------------
// COMPUTATIONS
//--------------------------------------------------------------------------
//=============================================================================
// PATH, WRAPPING, AND MOMENT ARM
//=============================================================================
//_____________________________________________________________________________
/**
 * Calculate the current path.
 *
 */
void GeometryPath::compute(const SimTK::State& s) const
{

	const SimTK::Stage& sg = s.getSystemStage();
	/*
    if (s.isCacheValueRealized(_subsystemIndex, _currentPathIndex))  {
        return;
    } */

	// Clear the current path.
	Array<PathPoint*>& currentPath = updCurrentPath(s);
	currentPath.setSize(0);

	// Add the fixed and active via points to the path.
	int i;
    for (i = 0; i < _pathPointSet.getSize(); i++) {
		_pathPointSet[i].update(s);
		if( _pathPointSet[i].isActive(s))
		currentPath.append(&_pathPointSet[i]);

 	}
  
   // Use the current path so far to check for intersection
	// with wrap objects, which may add additional points to
	// the path.
	applyWrapObjects(s, currentPath);
    calcLengthAfterPathComputation(s, currentPath);

    s.markCacheValueRealized(_subsystemIndex, _currentPathIndex);
}

//_____________________________________________________________________________
/**
 * Apply the wrap objects to the current path.
 */
void GeometryPath::applyWrapObjects(const SimTK::State& s, Array<PathPoint*>& path) const 
{
	if (_pathWrapSet.getSize() < 1)
		return;

   int i, j, kk, pt1, pt2, maxIterations;
   int start, end, wrapStart, wrapEnd;
   double min_length_change, last_length;
   WrapResult best_wrap;
   PathPoint *smp, *emp;
   WrapObject* wo;
   Array<int> result;
	Array<int> order;

	result.setSize(_pathWrapSet.getSize());
	order.setSize(_pathWrapSet.getSize());

   // Set the initial order to be the order they are listed in the path.
   for (i = 0; i < _pathWrapSet.getSize(); i++)
      order[i] = i;

   // If there is only one wrap object, calculate the wrapping only once.
   // If there are two or more objects, perform up to 8 iterations where
   // the result from one wrap object is used as the starting point for
   // the next wrap.
   if (_pathWrapSet.getSize() < 2)
      maxIterations = 1;
   else
      maxIterations = 8;

   for (kk = 0, last_length = SimTK::Infinity; kk < maxIterations; kk++)
   {
      for (i = 0; i < _pathWrapSet.getSize(); i++)
      {
         result[i] = 0;
            PathWrap& ws = _pathWrapSet.get(order[i]);
			wo = ws.getWrapObject();
         best_wrap.wrap_pts.setSize(0);
			min_length_change = SimTK::Infinity;

         // First remove this object's wrapping points from the current path.
         for (j = 0; j <path.getSize(); j++)
         {
				if( path.get(j) == &ws.getWrapPoint(0))
            {
				   path.remove(j); // remove the first wrap point
				   path.remove(j); // remove the second wrap point
               break;
            }
         }


         if (wo->getActive())
         {
            // startPoint and endPoint in wrapStruct represent the user-defined
            // starting and ending points in the array of path points that should
            // be considered for wrapping. These indices take into account via points,
            // whether or not they are active. Thus they are indices into mp_orig[],
            // not mp[] (also, mp[] may contain wrapping points from previous wrap
            // objects, which would mess up the starting and ending indices). But the
            // goal is to find starting and ending indices in mp[] to consider for
            // wrapping over this wrap object. Here is how that is done:

            // 1. startPoint and endPoint are 1-based, so subtract 1 from them to get
            // indices into _pathPointSet. -1 (or any value less than 1) means use the first
            // (or last) point.
				if (ws.getStartPoint() < 1)
               wrapStart = 0;
            else
               wrapStart = ws.getStartPoint() - 1;

            if (ws.getEndPoint() < 1)
               wrapEnd = _pathPointSet.getSize() - 1;
            else
               wrapEnd = ws.getEndPoint() - 1;

				// 2. Scan forward from wrapStart in _pathPointSet to find the first point
				// that is active. Store a pointer to it (smp).
				for (j = wrapStart; j <= wrapEnd; j++)
					if (_pathPointSet.get(j).isActive(s))
						break;
				if (j > wrapEnd) // there are no active points in the path
					return;
				smp = &_pathPointSet.get(j);

				// 3. Scan backwards from wrapEnd in _pathPointSet to find the last
				// point that is active. Store a pointer to it (emp).
				for (j = wrapEnd; j >= wrapStart; j--)
					if (_pathPointSet.get(j).isActive(s))
						break;
				if (j < wrapStart) // there are no active points in the path
					return;
				emp = &_pathPointSet.get(j);

				// 4. Now find the indices of smp and emp in _currentPath.
				for (j = 0, start = -1, end = -1; j < path.getSize(); j++)
				{
					if (path.get(j) == smp)
						start = j;
					if (path.get(j) == emp)
						end = j;
				}
				if (start == -1 || end == -1) // this should never happen
					return;

				// You now have indices into _currentPath (which is a list of all currently active points,
            // including wrap points) that represent the used-defined range of points to consider
            // for wrapping over this wrap object. Check each path segment in this range, choosing
            // the best wrap as the one that changes the path segment length the least:
            for (pt1 = start; pt1 < end; pt1++)
            {
               pt2 = pt1 + 1;

               // As long as the two points are not auto wrap points on the
               // same wrap object, check them for wrapping.
					if (path.get(pt1)->getWrapObject() == NULL ||
						 path.get(pt2)->getWrapObject() == NULL ||
						 (path.get(pt1)->getWrapObject() != path.get(pt2)->getWrapObject()))
               {
                  WrapResult wr;

						wr.startPoint = pt1;
						wr.endPoint = pt2;

                  result[i] = wo->wrapPathSegment(s, *path.get(pt1), *path.get(pt2), ws, wr);
                  if (result[i] == WrapObject::mandatoryWrap)
                  {
                     // mandatoryWrap means the path actually intersected
                     // the wrap object. In this case, you *must* choose this segment
                     // as the "best" one for wrapping. If the path has more than
                     // one segment that intersects the object, the first one is taken
                     // as the mandatory wrap (this is considered an ill-conditioned case).
                     best_wrap = wr;
							// store the best wrap in the pathWrap for possible use next time
							ws.setPreviousWrap(wr);
                     break;
                  }
                  else if (result[i] == WrapObject::wrapped)
                  {
                     // E_WRAPPED means the path segment was wrapped over the object,
                     // but you should consider the other segments as well to see if one
                     // wraps with a smaller length change.
                     double path_length_change = _calc_path_length_change(s, *wo, wr, path);
                     if (path_length_change < min_length_change)
                     {
                        best_wrap = wr;
								// store the best wrap in the pathWrap for possible use next time
								ws.setPreviousWrap(wr);
                        min_length_change = path_length_change;
                     }
                     else
                     {
                        // the wrap was not shorter than the current minimum,
                        // so just free the wrap points that were allocated.
								wr.wrap_pts.setSize(0);
                     }
                  }
                  else
                  {
                  }
               }
            }

            // Deallocate previous wrapping points if necessary.
				ws.getWrapPoint(1).getWrapPath().setSize(0);

			if (best_wrap.wrap_pts.getSize() == 0)
            {
 				  ws.resetPreviousWrap();
                  ws.getWrapPoint(1).getWrapPath().setSize(0);
            }
            else
            {
               // If wrapping did occur, copy wrap information into the PathStruct.
               ws.getWrapPoint(0).getWrapPath().setSize(0);

			   Array<SimTK::Vec3>& wrapPath = ws.getWrapPoint(1).getWrapPath();
					wrapPath = best_wrap.wrap_pts;

					// In OpenSim, all conversion to/from the wrap object's reference
					// frame will be performed inside wrapPathSegment(). Thus, all
					// points in this function will be in their respective body
					// reference frames.
               // for (j = 0; j < wrapPath.getSize(); j++){
               //    convert_from_wrap_object_frame(wo, wrapPath.get(j));
               //    convert(ms->modelnum, wrapPath.get(j), wo->segment, ms->ground_segment);
               // }

					ws.getWrapPoint(0).setWrapLength(0.0);
					ws.getWrapPoint(1).setWrapLength(best_wrap.wrap_path_length);
					ws.getWrapPoint(0).setBody(wo->getBody());
					ws.getWrapPoint(1).setBody(wo->getBody());

					ws.getWrapPoint(0).setLocation(s,best_wrap.r1);
					ws.getWrapPoint(1).setLocation(s,best_wrap.r2);

               // Now insert the two new wrapping points into the mp[] array.
					path.insert(best_wrap.endPoint, &ws.getWrapPoint(0));
					path.insert(best_wrap.endPoint + 1, &ws.getWrapPoint(1));
            }
         }
      }

		double length = calcLengthAfterPathComputation(s, path); 

      if (DABS(length - last_length) < 0.0005)
      {
         break;
      }
      else
      {
         last_length = length;
      }

      if (kk == 0 && _pathWrapSet.getSize() > 1)
      {
         // If the first wrap was a no wrap, and the second was a no wrap
         // because a point was inside the object, switch the order of
         // the first two objects and try again.
			if (result[0] == WrapObject::noWrap && result[1] == WrapObject::insideRadius)
         {
            order[0] = 1;
            order[1] = 0;

            // remove wrap object 0 from the list of path points
				int index = 0;

            PathWrap& ws = _pathWrapSet.get(index);
				for (j = 0; j < path.getSize(); j++)
				{
					if (path.get(j) == &ws.getWrapPoint(0))
					{
						path.remove(j); // remove the first wrap point
						path.remove(j); // remove the second wrap point
						break;
					}
				}
         }
      }
   }
}

//_____________________________________________________________________________
/**
 * _calc_path_length_change - given the output of a successful path wrap
 * over a wrap object, determine the percent change in length of the
 * path segment incurred by wrapping.
 */
double GeometryPath::_calc_path_length_change(const SimTK::State& s, WrapObject& wo, WrapResult& wr, const Array<PathPoint*>& path)  const
{
	const PathPoint* pt1 = path.get(wr.startPoint);
	const PathPoint* pt2 = path.get(wr.endPoint);

   double straight_length = getModel().getSimbodyEngine().calcDistance(s, pt1->getBody(), pt1->getLocation(),
		pt2->getBody(), pt2->getLocation());

	const Vec3& p1 = pt1->getLocation();
	const Vec3& p2 = pt2->getLocation();
   double wrap_length = getModel().getSimbodyEngine().calcDistance(s, pt1->getBody(), p1, wo.getBody(), wr.r1);
   wrap_length += wr.wrap_path_length;
   wrap_length += getModel().getSimbodyEngine().calcDistance(s, wo.getBody(), wr.r2, pt2->getBody(), p2);

   return wrap_length - straight_length; // return absolute diff, not relative
}

//_____________________________________________________________________________
/**
 * Compute the total length of the path. This function
 * assumes that the path has already been updated.
 */
double GeometryPath::calcLengthAfterPathComputation(const SimTK::State& s, const Array<PathPoint*>& currentPath) const
{
	double length = 0.0;

	const SimbodyEngine& engine = _model->getSimbodyEngine();

	for (int i = 0; i < currentPath.getSize() - 1; i++) {
		const PathPoint* p1 = currentPath[i];
		const PathPoint* p2 = currentPath[i+1];

      // If both points are wrap points on the same wrap object, then this path
      // segment wraps over the surface of a wrap object, so just add in the
      // pre-calculated length.
      if (p1->getWrapObject() && p2->getWrapObject() && p1->getWrapObject() == p2->getWrapObject()) {
			const PathWrapPoint* smwp = dynamic_cast<const PathWrapPoint*>(p2);
			if (smwp) {
				length += smwp->getWrapLength();
			}
      } else {
         length += engine.calcDistance(s, p1->getBody(), p1->getLocation(), p2->getBody(), p2->getLocation());
      }
   }

   setLength(s,length);
   return( length );
}
//_____________________________________________________________________________
/**
 * Compute the path's moment arms for  specified coordinate.
 *
 * @param aCoord, the coordinate
 */   
double GeometryPath::computeMomentArm(const SimTK::State& s, const Coordinate& aCoord)
{
	// Get the underlying geometry of the muscle in terms of individual point 
	// force directions
	OpenSim::Array<PointForceDirection*> PFDs;
	getPointForceDirections(s, &PFDs);
	
	MomentArmSolver maSolver(*_model);
	double ma = maSolver.solve(s, aCoord, PFDs);

	for(int i=0; i < PFDs.getSize(); i++)
		delete PFDs[i];

	return ma;
}

//_____________________________________________________________________________
/**
 * Update the visible object used to represent the path.
 */
void GeometryPath::updateDisplayer(const SimTK::State& s)
{
    updateGeometry(s);
}

void GeometryPath::updateDisplayPath(const SimTK::State& s)
{
    Array<PathPoint*>& currentDisplayPath = updCurrentDisplayPath(s);
	// Clear the current display path. Delete all path points
	// that have a NULL path pointer. This means that they were
	// created by an earlier call to updateDisplayPath() and are
	// not part of the _currentPath.
	for (int i=0; i<currentDisplayPath.getSize(); i++) {
		PathPoint* mp = currentDisplayPath.get(i);
		if (!mp->getPath())
			delete mp;
	}
	currentDisplayPath.setSize(0);

    Array<PathPoint*>& currentPath =  updCurrentPath(s);
	for (int i=0; i<currentPath.getSize(); i++) {
		PathPoint* mp = currentPath.get(i);
		PathWrapPoint* mwp = dynamic_cast<PathWrapPoint*>(mp);
		if (mwp) {
			// If the point is a PathWrapPoint and has surfacePoints,
			// then this is the second of two tangent points for the
			// wrap instance. So add the surface points to the display
			// path before adding the second tangent point.
			// Note: the first surface point is coincident with the
			// first tangent point, so don't add it to the path.
		   const Array<Vec3>& surfacePoints = mwp->getWrapPath();
			for (int j=1; j<surfacePoints.getSize(); j++) {
				PathWrapPoint* p = new PathWrapPoint();
				p->setLocation(s, surfacePoints.get(j));
				p->setBody(mwp->getBody());
				currentDisplayPath.append(p);
			}
		}
		currentDisplayPath.append(mp);
	}
}
