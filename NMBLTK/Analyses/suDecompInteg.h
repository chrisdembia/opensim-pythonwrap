// suDecompInteg.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suDecompInteg_h__
#define __suDecompInteg_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Manager/rdManager.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suActuation.h"
#include "suDecomp.h"
#include "suActuatorPerturbation.h"


//=============================================================================
//=============================================================================
/**
 * A class for computing induced reaction forces using the
 * "perturbed integration" methodology.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suDecompInteg : public suDecomp
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Nominal manager. */
	const rdManager *_managerNom;
	/** Nominal contact analysis. */
	const suContact *_contactNom;
	/** Nominal actuation analysis. */
	const suActuation *_actuationNom;
	/** Size of the integration time window. */
	double _dt;
	/** Perturbed simulation manager. */
	rdManager *_manager;
	/** Perturbed contact analysis. */
	suContact *_contact;
	/** Last index at which the perturbed integration was computed. */
	int _iLast;
	/** Local states array. */
	double *_y;
	/** Actuator forces. */
	double *_fAct;
	/** Local contact points array. */
	double *_pctx;
	/** Local contact forces array. */
	double *_fctx;
	/** Actuator perturbation callback instance. */
	suActuatorPerturbation *_perturbCallback;
	/** Flag to indicate whether to print detailed integration window
	information. */
	bool _printWindow;

//=============================================================================
// METHODS
//=============================================================================
public:
	suDecompInteg(const rdManager *aManager,const suContact *aContact,
		const suActuation *aActuation,rdModel *aModelTwin,
		double aDT=0.0,double aDF=0.0);
	virtual ~suDecompInteg();
private:
	void setNull();
	void constructManager();
	void constructContactAnalysis();
	void constructDescription();
	void updateStorageDescriptions();
	void allocate();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setIntegrationWindow(double aDT);
	double getIntegrationWindow() const;
//	void setPerturbation(double aDF);
	void setPerturbation(suActuatorPerturbation::PertType aPerturbationType,double aDF);
	double getPerturbation() const;
	suActuatorPerturbation::PertType getPerturbationType() const;
//	void setPerturbationFactor(double aFactor);
//	double getPerturbationFactor() const;
//	void setUseAbsolutePerturbation(bool aTrueFalse);
//	bool getUseAbsolutePerturbation() const;
	void setPrintWindow(bool aTrueFalse);
	bool getPrintWindow() const;

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	virtual void compute(double *aXPrev,double *aYPrev,
		int aStep,double aDT,double aT,double *aX,double *aY);

//=============================================================================
};	// END of class suDecompInteg
//=============================================================================
//=============================================================================


#endif // #ifndef __suDecompInteg_h__
