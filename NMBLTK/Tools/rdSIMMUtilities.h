// rdSIMMUtilities.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdSIMMUtilities_h__
#define __rdSIMMUtilities_h__


#include "rdTools.h"


class rdLine;
class rdPlane;


//=============================================================================
//=============================================================================
/**
 * This class provides basic math functions and constants.
 */
class RDTOOLS_API rdSIMMUtilities
{
//=============================================================================
// DATA
//=============================================================================
public:
	static const double PI;
	static const double RTD;
	static const double DTR;
	static const double SMALL;
	static const double ZERO;
	static const double NAN;
	static const double INF;

//=============================================================================
// METHODS
//=============================================================================
public:

	//--------------------------------------------------------------------------
	// BONES
	//--------------------------------------------------------------------------
	static int
		LoadBone(const char *aFileName,double rBoundingBox[6],
		int &rNumVert,double *&rVerts,double *&rNormals,
		int &rNumFaces,int *&rFaceCounts,int *&rFaces);

//=============================================================================
};	// END class rdSIMMUtilities
//=============================================================================
//=============================================================================

#endif // __rdSIMMUtilities_h__

