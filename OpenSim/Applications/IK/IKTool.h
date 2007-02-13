#ifndef __IKTool_h__
#define __IKTool_h__
// IKTool.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <OpenSim/Applications/Workflow/workflowDLL.h>
#include <OpenSim/Tools/Object.h>
#include <OpenSim/Tools/PropertyDbl.h>
#include <OpenSim/Tools/PropertyStrArray.h>
#include <OpenSim/Simulation/Model/SimulationTool.h>

#ifdef SWIG
	#ifdef workflow_API
		#undef workflow_API
		#define workflow_API
	#endif
#endif

namespace OpenSim {

class MarkerSet;
class CoordinateSet;
class SimmIKTrialSet;


//=============================================================================
//=============================================================================
/**
 * An investigation class for the IK solver.
 *
 * @author Eran Guendelman
 * @version 1.0
 */
class workflow_API IKTool: public SimulationTool
{
//=============================================================================
// MEMBER VARIABLES
//=============================================================================
private:
	// marker set for updating markers in model before doing IK
	PropertyObj _markerSetProp;
	MarkerSet &_markerSet;

	// coordinate set for updating coordinates in model before doing IK
	PropertyObj _coordinateSetProp;
	CoordinateSet &_coordinateSet;

	// names of coordinates whose values should be read from a file for IK
	PropertyStrArray _coordinatesFromFileProp;
	Array<std::string>& _coordinatesFromFile;

	// the set of IK trials to perform
	PropertyObj _IKTrialSetProp;
	SimmIKTrialSet &_IKTrialSet;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	virtual ~IKTool();
	IKTool();
	IKTool(const std::string &aFileName, AbstractModel* guiModel=0);
	IKTool(const IKTool &aObject);
	virtual OpenSim::Object* copy() const;

	/* Register types to be used when reading an IKTool object from xml file. */
	static void registerTypes();
private:
	void setNull();
	void setupProperties();
	void constructCorrectiveSprings();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	IKTool&
		operator=(const IKTool &aIKTool);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	MarkerSet& getMarkerSet()
	{
	   return _markerSet;
	}

	CoordinateSet &getCoordinateSet() const
	{
		return _coordinateSet;
	}

	SimmIKTrialSet& getIKTrialSet()
	{
		return _IKTrialSet;
	}

	//--------------------------------------------------------------------------
	// INTERFACE
	//--------------------------------------------------------------------------
	virtual void run();

//=============================================================================
};	// END of class IKTool
//=============================================================================
} // namespace

#endif // __IKTool_h__
