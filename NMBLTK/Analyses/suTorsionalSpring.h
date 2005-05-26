// suTorsionalSpring.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suTorsionalSpring_h__
#define __suTorsionalSpring_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdDerivCallback.h>
#include <RD/Simulation/Manager/rdManager.h>
#include <RD/Tools/rdFunctionSet.h>
#include <RD/Tools/rdVectorFunction.h>
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
	/** Vector function containing nominal Euler angles of body. */
	rdVectorFunction* _posFunction;
	/** Vector function containing nominal angular velocity of body, expressed
		 in global coordinates. */
	rdVectorFunction* _velFunction;
	/** Function containing values for the time-dependent torque scaling factor. */
	rdFunction* _scaleFunction;
	/** Scale factor that pre-multiplies the applied torque */
	double _scaleFactor;
	double _k[3];
	double _b[3];

//=============================================================================
// METHODS
//=============================================================================
public:
	suTorsionalSpring(rdModel *aModel);	
	suTorsionalSpring(rdModel *aModel,int aBody);
	suTorsionalSpring(rdModel *aModel,int aBody,rdVectorFunction *aPosFunction,
		rdVectorFunction *aVelFunction, double aK[3], double aB[3]);
	virtual ~suTorsionalSpring();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setPosFunction(rdVectorFunction* aPosFunction);
	rdVectorFunction* getPosFunction() const;
	void setVelFunction(rdVectorFunction* aVelFunction);
	rdVectorFunction* getVelFunction() const;
	void setKValue(double aK[3]);
	void getKValue(double aK[3]);
	void setBValue(double aB[3]);
	void getBValue(double aB[3]);
	void setScaleFunction(rdFunction* _scaleFunction);
	rdFunction* getScaleFunction() const;
	void setScaleFactor(double aScaleFactor);
	double getScaleFactor();

	
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
