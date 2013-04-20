#ifndef OPENSIM_GEOMETRY_PATH_H_
#define OPENSIM_GEOMETRY_PATH_H_
/* -------------------------------------------------------------------------- *
 *                          OpenSim:  GeometryPath.h                          *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Peter Loan                                                      *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */


// INCLUDE
#include <iostream>
#include <math.h>
#include <OpenSim/Simulation/osimSimulationDLL.h>
#include "OpenSim/Simulation/Model/ModelComponent.h"
#include <OpenSim/Common/PropertyInt.h>
#include <OpenSim/Common/PropertyObj.h>
#include <OpenSim/Common/ScaleSet.h>
#include <OpenSim/Common/VisibleObject.h>
#include "PathPointSet.h"
#include <OpenSim/Simulation/Wrap/PathWrapSet.h>


#ifdef SWIG
	#ifdef OSIMSIMULATION_API
		#undef OSIMSIMULATION_API
		#define OSIMSIMULATION_API
	#endif
#endif

namespace OpenSim {

class Coordinate;
class WrapResult;
class WrapObject;
class PointForceDirection;

//=============================================================================
//=============================================================================
/**
 * A base class representing a path (muscle, ligament, etc.).
 *
 * @author Peter Loan
 * @version 1.0
 */
class OSIMSIMULATION_API GeometryPath : public ModelComponent {
OpenSim_DECLARE_CONCRETE_OBJECT(GeometryPath, ModelComponent);

//=============================================================================
// DATA
//=============================================================================
private:
	OpenSim_DECLARE_UNNAMED_PROPERTY(PathPointSet, "The set of points defining the path");

	OpenSim_DECLARE_PROPERTY(display, VisibleObject, "Used to display the path in the 3D window");

	OpenSim_DECLARE_UNNAMED_PROPERTY(PathWrapSet, "The wrap objecs that are associated with this path");
	
	OpenSim_DECLARE_OPTIONAL_PROPERTY(default_color, SimTK::Vec3, "Used to initialize the colour cache variable");

	// used for scaling tendon and fiber lengths
	double _preScaleLength;

	// object that owns this GeometryPath object
	Object* _owner;
	
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	GeometryPath();
	virtual ~GeometryPath();

	void setName(const std::string &aName);
#ifndef SWIG
	GeometryPath& operator=(const GeometryPath &aPath);
#endif
	void copyData(const GeometryPath &aPath);
	const PathPointSet& getPathPointSet() const { return get_PathPointSet(); }
	PathPointSet& updPathPointSet() { return upd_PathPointSet(); }
	const PathWrapSet& getWrapSet() const { return get_PathWrapSet(); }

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	PathPoint* addPathPoint(const SimTK::State& s, int aIndex, OpenSim::Body& aBody);
	PathPoint* appendNewPathPoint(const std::string& proposedName, 
								OpenSim::Body& aBody, const SimTK::Vec3& aPositionOnBody);
	bool canDeletePathPoint( int aIndex);
	bool deletePathPoint(const SimTK::State& s, int aIndex);
	void addPathWrap(const SimTK::State& s, WrapObject& aWrapObject);
	void moveUpPathWrap(const SimTK::State& s, int aIndex);
	void moveDownPathWrap(const SimTK::State& s, int aIndex);
	void deletePathWrap(const SimTK::State& s, int aIndex);
	bool replacePathPoint(const SimTK::State& s, PathPoint* aOldPathPoint, PathPoint* aNewPathPoint); 

    //--------------------------------------------------------------------------
    // GET
    //--------------------------------------------------------------------------
	Object* getOwner() const { return _owner; }
	void setOwner(Object *anObject) {_owner = anObject; };

    /** If you call this prior to addToSystem() it will be used to initialize
    the color cache variable. Otherwise %GeometryPath will choose its own
    default which will be some boring shade of gray. **/
	void setDefaultColor(const SimTK::Vec3& color) {set_default_color(color); };
    /** Returns the color that will be used to initialize the color cache
    at the next addToSystem() call. The actual color used to draw the path
    will be taken from the cache variable, so may have changed. **/
	const SimTK::Vec3& getDefaultColor() const { return get_default_color(); }

    /** Set the value of the color cache variable owned by this %GeometryPath
    object, in the cache of the given state. The value of this variable is used
    as the color when the path is drawn, which occurs with the state realized 
    to Stage::Dynamics. So you must call this method during realizeDynamics() or 
    earlier in order for it to have any effect. **/
	void setColor(const SimTK::State& s, const SimTK::Vec3& color) const;

    /** Get the current value of the color cache entry owned by this
    %GeometryPath object in the given state. You can access this value any time
    after the state is initialized, at which point it will have been set to
    the default color value specified in a call to setDefaultColor() earlier,
    or it will have the default default color value chosen by %GeometryPath.
    @see setDefaultColor() **/
	SimTK::Vec3 getColor(const SimTK::State& s) const;

	virtual double getLength( const SimTK::State& s) const;
	virtual void setLength( const SimTK::State& s, double length) const;
	virtual double getPreScaleLength( const SimTK::State& s) const;
	virtual void setPreScaleLength( const SimTK::State& s, double preScaleLength);
	virtual const Array<PathPoint*>& getCurrentPath( const SimTK::State& s) const;

	virtual const Array<PathPoint*>& getCurrentDisplayPath(const SimTK::State& s) const;
	
	/** get the the path as PointForceDirections directions */
	void getPointForceDirections(const SimTK::State& s, OpenSim::Array<PointForceDirection*> *rPFDs) const;

	virtual double getLengtheningSpeed(const SimTK::State& s) const;
	virtual void setLengtheningSpeed( const SimTK::State& s, double speed ) const;


	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
private:
	void computePath(const SimTK::State& s ) const;
	void computeLengtheningSpeed(const SimTK::State& s) const;
	void applyWrapObjects(const SimTK::State& s, Array<PathPoint*>& path ) const;
	double _calc_path_length_change(const SimTK::State& s, WrapObject& wo, WrapResult& wr, const Array<PathPoint*>& path) const; 
	virtual double calcLengthAfterPathComputation(const SimTK::State& s, const Array<PathPoint*>& currentPath) const;
public:
	virtual double computeMomentArm(const SimTK::State& s, const Coordinate& aCoord) const;

	//--------------------------------------------------------------------------
	// SCALING
	//--------------------------------------------------------------------------
	virtual void preScale(const SimTK::State& s, const ScaleSet& aScaleSet);
	virtual void scale(const SimTK::State& s, const ScaleSet& aScaleSet);
	virtual void postScale(const SimTK::State& s, const ScaleSet& aScaleSet);
	virtual int getNumStateVariables() const { return 0;};

protected:
    // ModelComponent interface.
	void connectToModel(Model& aModel) OVERRIDE_11;
	void initStateFromProperties(SimTK::State& s) const OVERRIDE_11;
	void addToSystem(SimTK::MultibodySystem& system) const OVERRIDE_11;

	// Visual support GeometryPath drawing in SimTK visualizer.
	void generateDecorations(
			bool 									    fixed,
			const ModelDisplayHints&				    hints,
			const SimTK::State&						    state,
			SimTK::Array_<SimTK::DecorativeGeometry>&	appendToThis) const
            OVERRIDE_11;

public:
	//--------------------------------------------------------------------------
	// Visible Object Support
	//--------------------------------------------------------------------------
	virtual const VisibleObject* getDisplayer() const { 
		return &get_display(); 
	}
	
	void updateDisplayer(const SimTK::State& s) const OVERRIDE_11;

    // Update the geometry attached to the path (location of path points and connecting segments
	//  all in global/interial frame)
	virtual void updateGeometry(const SimTK::State& s) const;

private:
	void setNull();
	void constructProperties();
	void updateDisplayPath(const SimTK::State& s) const;
	void updateGeometrySize(const SimTK::State& ) const;
	void updateGeometryLocations(const SimTK::State& s) const;
	void namePathPoints(int aStartingIndex);
    void placeNewPathPoint(const SimTK::State& s, SimTK::Vec3& aOffset, int aIndex, const OpenSim::Body& aBody);

//=============================================================================
};	// END of class GeometryPath
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // OPENSIM_GEOMETRY_PATH_H_


