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
	/** Vector function containing target trajectory of the point expressed in
		the global reference frame. */
	rdVectorFunction* _target;
	/** Function containing values for the time-dependent scaling factor. */
	rdFunction* _scaleFunction;
	/** Scale factor that pre-multiplies the applied torque */
	double _scaleFactor;
	double _k[3];
	double _b[3];


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
	void setTarget(rdVectorFunction* aTarget);
	rdVectorFunction* getTarget() const;
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
};	// END of class suLinearSpring
//=============================================================================
//=============================================================================


#endif // #ifndef __suLinearSpring_h__
