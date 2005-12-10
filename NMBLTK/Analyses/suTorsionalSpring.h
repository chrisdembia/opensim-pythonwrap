// suTorsionalSpring.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suTorsionalSpring_h__
#define __suTorsionalSpring_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallback.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Tools/rdFunctionSet.h>
#include <NMBLTK/Tools/rdVectorFunction.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suDecomp.h"
#include "suTorqueApplier.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for applying external torques during a
 * simulation.  The magnitude of the torque is calculated based on the 
 * deviation in angular position and velocity of the body from a prescribed
 * position and velocity.
 *
 * @author Frank C. Anderson, Saryn Goldberg
 * @version 1.0
 */
class SUANALYSES_API suTorsionalSpring : public suTorqueApplier 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Vector function containing target orientation of the body. */
	rdVectorFunction *_targetPosition;
	/** Vector function containing target angular velocity of the body. */
	rdVectorFunction *_targetVelocity;
	/** Function containing values for the time-dependent torque scaling factor. */
	rdFunction *_scaleFunction;
	/** Scale factor that pre-multiplies the applied torque */
	double _scaleFactor;
	/** Stiffness. */
	double _k[3];
	/** Damping. */
	double _b[3];
	/** Flag indicating whether or not to store the applied torques. */
	bool _storeTorques;

//=============================================================================
// METHODS
//=============================================================================
public:
	suTorsionalSpring(rdModel *aModel,int aBody);
	virtual ~suTorsionalSpring();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setTargetPosition(rdVectorFunction* aPosFunction);
	rdVectorFunction* getTargetPosition() const;
	void setTargetVelocity(rdVectorFunction* aVelFunction);
	rdVectorFunction* getTargetVelocity() const;
	void setKValue(double aK[3]);
	void getKValue(double aK[3]);
	void setBValue(double aB[3]);
	void getBValue(double aB[3]);
	void setScaleFunction(rdFunction* _scaleFunction);
	rdFunction* getScaleFunction() const;
	void setScaleFactor(double aScaleFactor);
	double getScaleFactor();
	void setStoreTorques(bool aTrueFalse);
	bool getStoreTorques();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void computeTargetFunctions(rdStorage *aQStore,rdStorage *aUStore);
	
	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		applyActuation(double aT,double *aX,double *aY);

//=============================================================================
};	// END of class suTorsionalSpring
//=============================================================================
//=============================================================================


#endif // #ifndef __suTorsionalSpring_h__
