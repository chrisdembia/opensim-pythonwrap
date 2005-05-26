// suGenCoordSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suGenCoordSet_h__
#define __suGenCoordSet_h__

#include "suGenCoord.h"
#include <RD/Tools/rdSet.h>

//=============================================================================
//=============================================================================
/*
 * A Class representing a set of Generalized Coordinates. 
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
class RDSIMULATION_API suGenCoordSet : public rdSet<suGenCoord>
{
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	suGenCoordSet(const std::string &aFileName);
	suGenCoordSet();
	~suGenCoordSet();
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	/** Get all range mins in an rdArray **/
	void getAllMins(rdArray<double>& aAllMins) const;
	/** Get all range maxs in an rdArray **/
	void getAllMaxs(rdArray<double>& aAllMaxs) const;
	/** Get all GenCoord names in an rdArray **/
	void getAllNames(rdArray<std::string>& aAllNames) const;

};
#endif