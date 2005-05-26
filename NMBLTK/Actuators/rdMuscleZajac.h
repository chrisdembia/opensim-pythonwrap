// rdMuscleZajac.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdMuscleZajac_h__
#define __rdMuscleZajac_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdStorage.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdForce.h>
#include "rdActuators.h"


//=============================================================================
//=============================================================================
/**
 * A class that represents a lumped parameter muscle in series with a linear
 * tendon.  The muscle is comprised of three elements: the contractile
 * element models the force-length-velocity properties of muscle; the series
 * elastic element is in series with the contractile element an models the
 * short-range elastic response of muscle; the parallel elastic element is
 * in parallel with both the series elastic element and the contractile
 * element and models the passive elastic properties of muscle.
 *
 * For details concerning this model consult
 * Zajac, F.E. (1989).  ??.  Reviews in Sports Science ??.
 *
 * Controls (1):
 *	0) excitation
 *
 * States (2):
 * 0) activation level
 * 1) musculotendon force
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDACTUATORS_API rdMuscleZajac : public rdForce 
{
//=============================================================================
// DATA
//=============================================================================
public:
	// MUSCLE CONSTANTS
	static const double C1;
	static const double C2;
	static const double PE1;
	static const double SIG0;
	static const double AF;
	static const double AS;
	static const double MS;
	static const double MF;
	static const double CONPE1 ;


	static const double LMNORMMAX;
	static const double flcoef[30][6];
	static const double fvcoef[30][6];
	static const double vfcoef[30][6];

protected:
	/** Excitation (control 0). */
	double _x;
	/** Activation level (state 0). */
	double _a;
	/** Actuator force (state 1).  Note that this state is a member variable
	of class rdForce. */ 
	/** Rise time of muscle activation in seconds. (serialized) */
	double *_tRise;
	/** Fall time of muscle activation in seconds.  (serialized) */
	double *_tFall;
	/** Optimal muscle force in Newtons.  (serialized) */
	double *_fmOpt;
	/** Optimal muscle fiber length in meters. (serialized) */
	double *_lmOpt;
	/** Optimal muscle pennation angle in degrees.  (serialized) */
	double *_alphaOpt;
	/** Maximum muscle fiber shortening velocity in optimal fiber lengths per
	second.  (serialized) */
	double *_vmMax;
	/** Tendon slack length in meters.  (serialized) */
	double *_ltSlack;
	// INITIALIZED VARIABLES
	/** Reciprocal of muscle length. */
	double _lmOptRecip;
	/** Muscle width in meters. */
	double _width;
	/** Muscle width squared. */
	double _widthSquared;
	/** Reciprocal of normalized tendon stiffness. */
	double _ktRecip;
	/** Reciprocal of normalized tendon stiffness times optimal fiber length. */
	double _ktLmOptRecip;
	// WORK VARIABLES
	/** Actuator length. */
	double _lmt;
	
	// ILSE ADDED CLAY would define them locally
	/** length of contractile part */
	double _lm;

	
	//=============================================================================
// METHODS
//=============================================================================
public:
	rdMuscleZajac(int aQID=-1,int aNX=1,int aNY=2,int aNYP=0);
	rdMuscleZajac(DOMElement *aElement,
		int aNX=1,int aNY=2,int aNYP=0);
	rdMuscleZajac(const rdMuscleZajac &aActuator);
	virtual ~rdMuscleZajac();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupSerializedMembers();
	void copyData(const rdMuscleZajac &aActuator);

public:

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
	rdMuscleZajac&
		operator=(const rdMuscleZajac &aActuator);

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setControls(const double aX[]);
	virtual void getControls(double rX[]) const;
	virtual void setStates(const double aY[]);
	virtual void getStates(double rY[]) const;
	void setRiseTime(double aTime);
	double getRiseTime() const;
	void setFallTime(double aTime);
	double getFallTime() const;
	void setOptimalForce(double aForce);
	double getOptimalForce() const;
	void setOptimalFiberLength(double aLength);
	double getOptimalFiberLength() const;
	void setOptimalPennationAngle(double aAngle);
	double getOptimalPennationAngle() const;
	void setTendonSlackLength(double aLength);
	double getTendonSlackLength() const;
	void setMaxShorteningVelocity(double aVelocity);
	double getMaxShorteningVelocity() const;
	void setMslMass(double aMass);
	double getMslMass() const;
	//--------------------------------------------------------------------------
	// APPLICATION
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void promoteControlsToStates(const double aX[],double aDT);
	virtual void computeActuation();
	virtual void computeStateDerivatives(double rDYDT[]);
	virtual double computeDFDT();
	
	virtual double ComputeMuscleForce(); //NOT SURE ABOUT THE VIRTUAL
	virtual double ComputeActivation(double aForce, double aLength, double asvel);
			// Not sure about the argument list
	
    virtual double ComputeMsForce(double aLength);
	virtual double ComputeMuscleZero(double aLength);
	virtual double ComputeMuscleLength(double ax, double bx, double tol);

	//Why change to static//
	
	static double ComputeForceLengthCurve(double aLmNorm);
	static double ComputeShorteningVelocity(double aFmNormIso,double aFmNorm);
	
	static double ComputeVelocityEffect(double aVNorm);



	// To be included
	//ComputeACtivationRate
//=============================================================================
};	// END of class rdMuscleZajac
//=============================================================================
//=============================================================================


#endif // #ifndef __rdMuscleZajac_h__
