// suDecompHardUTWalk.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suDecompHardUTWalk_h__
#define __suDecompHardUTWalk_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Models/UTWalking8/rdUTWalking8.h>
#include <NMBLTK/Tools/rdBodyConstraint.h>
#include "suAnalyses.h"
#include "suDecomp.h"
#include "suDecompHard.h"


//=============================================================================
//=============================================================================
/**
 * A class for computing a decomposition by hard constraints for the
 * UT Walking Model or classes derived from the UT Walking Model.
 */
class SUANALYSES_API suDecompHardUTWalk : public suDecompHard
{
//=============================================================================
// DATA
//=============================================================================
public:

protected:
	/** Force component index. */
	int _c;
	/** Number of spring points in contact. */
	int _nxs;
	/** Map from spring points in contact to springs in the model. */
	int *_xsSprMap;
	/** Map from degrees of freedom (XYZ) of springs in contact to
	degrees of freedom of springs in the model. */
	int *_xsXYZMap;
	/** Constraints on the bodies: rhindfoot, rtoes, lhindfoot, ltoes. */
	rdBodyConstraint _bc[4];
	/** Performance criterion weight for the spring forces. */
	double _wXS;
	/** Performance criterion weight for the spring accelerations. */
	double _wAcc;
private:
	/** Point used for temporary storage of model spring point locations.
	See getContactPoint(). */
	double _point[3];
	/** Untouched copy of the states. */
	double *_yCopy;
	/** Manipulated copy of the states. */
	double *_yTmp;
	/** Untouched copy of the model controls. */
	double *_x;

//=============================================================================
// METHODS
//=============================================================================
public:
	suDecompHardUTWalk(rdUTWalking8 *aModel);
	virtual ~suDecompHardUTWalk();
private:
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	double* getContactPoint(int aIndex);

	//--------------------------------------------------------------------------
	// DECOMPOSITION
	//--------------------------------------------------------------------------
public:
	virtual void
		compute(double *aXPrev,double *aYPrev,int aStep,
		double aDT,double aT,double *aX,double *aY);
	int suComputePerformance(double *x,double *p);
	int suComputePerformanceGradient(double *x,double *dpdx);
	int suComputeConstraint(double *x,int ic,double *c);
	int suComputeContactPointAccelerations(double *x,int c,double cpa[][3]);
protected:
	int getNumberConstraints();
	void clearBodyConstraints();
	void clearBodyConstraintValues();
	void setBodyConstraintValues(int aN,int aID[],double aAcc[][3]);
	void decompose(int step,double dt,double t,double *xt,double *y,void *cd);
	void determineControls(double sfrc[][3]);
	void determineConstraints();
	void setSpringForces(double *aXS,double aFS[][3]);
	void applyComponentForce(int aC);

//=============================================================================
};	// END of class suDecompHardUTWalk
//=============================================================================
//=============================================================================


#endif // #ifndef __suDecompHardUTWalk_h__
