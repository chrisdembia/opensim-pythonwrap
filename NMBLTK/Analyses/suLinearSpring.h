// suLinearSpring.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suLinearSpring_h__
#define __suLinearSpring_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallback.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Tools/rdFunction.h>
#include <NMBLTK/Tools/rdVectorFunction.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suDecomp.h"
#include "suForceApplier.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for applying external forces during a
 * simulation.
 *
 * @author Frank C. Anderson, Saryn R. Goldberg
 * @version 1.0
 */
class SUANALYSES_API suLinearSpring : public suForceApplier 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Vector function containing the target position of the point expressed
	in the global reference frame. */
	rdVectorFunction *_targetPosition;
	/** Vector function containing the target velocity of the point expressed
	in  the global reference frame. */
	rdVectorFunction *_targetVelocity;
	/** Function containing values for the time-dependent scaling factor. */
	rdFunction *_scaleFunction;
	/** Scale factor that pre-multiplies the applied torque */
	double _scaleFactor;
	/** Stiffness. */
	double _k[3];
	/** Damping. */
	double _b[3];
	/** Flag indicating whether or not to store the applied forces. */
	bool _storeForces;

//=============================================================================
// METHODS
//=============================================================================
public:
	suLinearSpring(rdModel *aModel,int aBody);	
	virtual ~suLinearSpring();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setTargetPosition(rdVectorFunction* aTargetVelocity);
	rdVectorFunction* getTargetPosition() const;
	void setTargetVelocity(rdVectorFunction* aTargetVelocity);
	rdVectorFunction* getTargetVelocity() const;
	void setKValue(double aK[3]);
	void getKValue(double aK[3]);
	void setBValue(double aB[3]);
	void getBValue(double aB[3]);
	void setScaleFunction(rdFunction* _scaleFunction);
	rdFunction* getScaleFunction() const;
	void setScaleFactor(double aScaleFactor);
	double getScaleFactor();
	void setStoreForces(bool aTrueFalse);
	bool getStoreForces();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void
		computePointAndTargetFunctions(rdStorage *aQStore,rdStorage *aUStore,
		rdVectorFunction &aPGlobal);

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		applyActuation(double aT,double *aX,double *aY);

//=============================================================================
};	// END of class suLinearSpring
//=============================================================================
//=============================================================================


#endif // #ifndef __suLinearSpring_h__
