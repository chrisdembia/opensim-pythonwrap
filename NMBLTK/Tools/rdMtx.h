// rdMtx.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2000 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdMtx_h__
#define __rdMtx_h__


// INCLUDES
#include "rdTools.h"


//=============================================================================
//=============================================================================
/**
 * A class for performing vector and matrix operations.  Most all the
 * methods in this class are static.
 */
class RDTOOLS_API rdMtx
{
//=============================================================================
// DATA
//=============================================================================
private:
	static int _PSpaceSize;
	static int _WSpaceSize;
	static double **_P1Space;
	static double **_P2Space;
	static double *_WSpace;

//=============================================================================
// METHODS
//=============================================================================
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	//rdMtx();
	//virtual ~rdMtx();

	//--------------------------------------------------------------------------
	// VECTOR
	//--------------------------------------------------------------------------
	static double Angle(const double *aV1,const double *aV2);
	static double Normalize(int aN,const double aV[],double rV[]);
	static double Magnitude(int aN,const double aV[]);
	static double DotProduct(int aN,const double aV1[],const double aV2[]);
	static int CrossProduct(double *aV1,double *aV2,double *aV);
	static void
	 Interpolate(int aN,double aT1,double *aY1,double aT2,double *aY2,
	 double t,double *aY);
	static double
	 Interpolate(double aT1,double aY1,double aT2,double aY2,
	 double t);

	//--------------------------------------------------------------------------
	// TRANSLATION AND ROTATION
	//--------------------------------------------------------------------------
	static void
		Translate(double aX,double aY,double aZ,const double aP[3],double rP[3]);
	static void
		Rotate(int aXYZ,double aRadians,const double aP[3],double rP[3]);
	static void
		Rotate(const double aAxis[3],double aRadians,const double aP[3],
		double rP[3]);
	static void
		RotateDeg(int aXYZ,double aDegrees,const double aP[3],double rP[3]);
	static void
		RotateDeg(const double aAxis[3],double aDegrees,const double aP[3],
		double rP[3]);

	//--------------------------------------------------------------------------
	// MATRIX
	//--------------------------------------------------------------------------
	static int Identity(int aNR,double *rI);
	static int Assign(int aNR,int aNC,double aScalar,double *rM);
	static int Assign(int aNR,int aNC,const double *aM,double *rM);
	static int Add(int aNR,int aNC,const double *aM1,double aScalar,double *aM);
	static int Add(int aNR,int aNC,const double *aM1,const double *aM2,double *aM);
	static int Subtract(int aNR,int aNC,const double *aM1,const double *aM2,
		double *aM);
	static int Multiply(int aNR,int aNC,const double *aM,double aScalar,double *rM);
	static int Multiply(int aNR1,int aNCR,int aNC2,const double *aM1,
		const double *aM2,double *aM);
	static int Invert(int aN,const double *aM,double *aMInv);
	static int Transpose(int aNR,int aNC,const double *aM,double *aMT);
	static void Print(int aNR,int aNC,const double *aM,int aPrecision=8);

	//--------------------------------------------------------------------------
	// INDEX OPERATIONS
	//--------------------------------------------------------------------------
	static int FindIndex(int aStartIndex,double aTime,int aNT,double *aT);
	static int FindIndexLess(int aNX,double *aX,double aValue);
	static int FindIndexGreater(int aNX,double *aX,double aValue);
	static int ComputeIndex(int i2,int n1,int i1);
	static int ComputeIndex(int i3,int n2,int i2,int n1,int i1);
	static void GetDim3(int n3,int n2,int n1,int i2,int i1,double *m,double *a);
	static void SetDim3(int n3,int n2,int n1,int i2,int i1,double *m,double *a);

	//--------------------------------------------------------------------------
	// WORKSPACE MANAGEMENT
	//--------------------------------------------------------------------------
	static int EnsureWorkSpaceCapacity(int aN);
	static int EnsurePointerSpaceCapacity(int aN);
	static void FreeWorkAndPointerSpaces();

//=============================================================================
};	// END class rdMtx
//=============================================================================
//=============================================================================

#endif  // __rdMtx_h__
