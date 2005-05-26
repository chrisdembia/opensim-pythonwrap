// suActuatorPerturbation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suActuatorPerturbation_h__
#define __suActuatorPerturbation_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallback.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suDecomp.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for perturbing the actuator forces during a
 * simulation.
 *
 * @author Frank C. Anderson, Saryn R. Goldberg
 * @version 1.0
 */
class SUANALYSES_API suActuatorPerturbation : public rdDerivCallback 
{
//=============================================================================
// DATA
//=============================================================================
public:
	/** Perturbation types. See setPerturbation(). */
	enum PertType {SCALE, DELTA, CONSTANT};

protected:
	/** Which actuator. */
	int _actuator;
	/** Negative force flag **/
	bool _allowNegForce;
	/** Force perturbation. */
	double _perturbation;
	/** Type of perturbation */
	PertType _perturbationType;
	/** Nominal actuator force. */
	double _force;
	/** Storage for holding nominal and perturbed force. */
	rdStorage *_forceStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suActuatorPerturbation(rdModel *aModel);
	virtual ~suActuatorPerturbation();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setActuator(int aActuatorIndex);
	int getActuator() const;
	void setAllowNegForce(bool aTrueFalse);
	bool getAllowNegForce() const;
	void setPerturbation(PertType aPerturbationType, double aPerturbation);
	double getPerturbation() const;
	PertType getPerturbationType() const;
	rdStorage* getForceStorage();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void reset();

	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		computeActuation(double aT,double *aX,double *aY);
	virtual void
		applyActuation(double aT,double *aX,double *aY);

//=============================================================================
};	// END of class suActuatorPerturbation
//=============================================================================
//=============================================================================


#endif // #ifndef __suActuatorPerturbation_h__
