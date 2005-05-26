// suMarkerSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suMarkerSet_h__
#define __suMarkerSet_h__

// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include "suMarker.h"
#include <RD/Tools/rdSet.h>

class suPipeline40;
class rdStorage;
class rdModel;
class suScaleSet;

//=============================================================================
//=============================================================================
/*
 * A Class representing a markerA set of markers
 *
 * @author Ayman Habib
 * @version 1.0
 */
#ifdef SWIG
	#ifdef RDSIMULATION_API
		#undef RDSIMULATION_API
		#define RDSIMULATION_API
	#endif
#endif

class RDSIMULATION_API suMarkerSet : public rdSet<suMarker>
{
private:
	void setNull();
public:
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	suMarkerSet();
	suMarkerSet(const std::string& markersFileName);
	suMarkerSet(const suMarkerSet& aMarkerSet);
	~suMarkerSet(void);
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	suMarkerSet& operator=(const suMarkerSet &aMarkerSet);
#endif
	//--------------------------------------------------------------------------
	// UTILITIES
	//--------------------------------------------------------------------------
	bool usesWeights() const;
	bool bindMarkersToModel(rdModel *model);
	void getMarkerNames(rdArray<std::string>& aMarkerNamesArray);
	void scale(suScaleSet& scaleSet);
	void makeRelativeToCom(rdModel *model);
	const rdSet<suMarker> &getMarkers() const;
};
#endif