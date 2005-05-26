// suGeneralizedForcePerturbation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suGeneralizedForcePerturbation_h__
#define __suGeneralizedForcePerturbation_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallback.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include "suAnalysesDLL.h"
#include <NMBLTK/Tools/rdGCVSpline.h>
#include "suContact.h"
#include "suDecomp.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for applying a generalized force during a
 * simulation.
 *
 * @author Frank C. Anderson, Saryn R. Goldberg
 * @version 1.0
 */
class SUANALYSES_API suGeneralizedForcePerturbation : public rdDerivCallback 
{
//=============================================================================
// DATA
//=============================================================================
public:

protected:
	/** Which generalized coordinate. */
	int _genCoord;
	/** Perturbation to be applied */
	double _perturbation;
	/** Scaling factor to be applied to perturbation */
	double _scaleFactor;
   /** The function defining the generalized force to be applied **/
	rdGCVSpline *_genForceSpline;


//=============================================================================
// METHODS
//=============================================================================
public:
	suGeneralizedForcePerturbation(rdModel *aModel);
	suGeneralizedForcePerturbation(rdModel *aModel, rdGCVSpline *_aSpline);
	virtual ~suGeneralizedForcePerturbation();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setGenCoord(int aGenCoord);
	int getGenCoord() const;

	void setScaleFactor(double aScaleFactor);
	double getScaleFactor() const;
	void setPerturbation(double aPerturbation);
	double getPerturbation() const;

	
	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		computeActuation(double aT,double *aX,double *aY);
	virtual void
		applyActuation(double aT,double *aX,double *aY);

//=============================================================================
};	// END of class suGeneralizedForcePerturbation
//=============================================================================
//=============================================================================


#endif // #ifndef __suGeneralizedForcePerturbation_h__
