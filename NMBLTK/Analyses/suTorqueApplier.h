// suTorqueApplier.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, May Q. Liu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suTorqueApplier_h__
#define __suTorqueApplier_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdDerivCallback.h>
#include <NMBLTK/Simulation/Manager/rdManager.h>
#include <NMBLTK/Tools/rdVectorFunction.h>
#include <NMBLTK/Tools/rdFunctionSet.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suDecomp.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for applying external torques during a
 * simulation.
 *
 * @author Frank C. Anderson, May Q. Liu
 * @version 1.0
 */
class SUANALYSES_API suTorqueApplier : public rdDerivCallback 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Which body segment. */
	int _body;
	/** Torque to be applied. */
	double _torque[3];
	/** Vector function containing torque to be applied (t,x,y,z). */
	rdVectorFunction* _torqueFunction;
	/** rdStorage containing torque to be applied (t,x,y,z). */
	rdStorage* _torqueStorage;	
	/** FunctionSet containing torque to be applied (t,x,y,z). */
	rdFunctionSet* _torqueSet;
	/** Storage for the torque that was actually applied during the simulation */
	rdStorage *_appliedTorqueStore;
	/** Flag to set reference frame of input torque */
	bool _inputTorquesInGlobalFrame;



//=============================================================================
// METHODS
//=============================================================================
public:
	suTorqueApplier(rdModel *aModel);	
	suTorqueApplier(rdModel *aModel,int aBody);
	suTorqueApplier(rdModel *aModel,int aBody,double aTorque[3]);
	suTorqueApplier(rdModel *aModel,int aBody,rdVectorFunction* aTorqueFunction);
	suTorqueApplier(rdModel *aModel,int aBody,rdStorage* aTorqueStorage);
	suTorqueApplier(rdModel *aModel,int aBody,rdFunctionSet* aTorqueSet);
	virtual ~suTorqueApplier();
private:
	void setNull();
	void constructDescription();
	void constructColumnLabels();
	void allocateStorage();
	void deleteStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setBody(int aBody);
	int getBody() const;
	void setTorque(double aTorque[3]);
	void getTorque(double rPoint[3]) const;
	void setTorqueFunction(rdVectorFunction* aTorqueFunction);
	rdVectorFunction* getTorqueFunction() const;
	void setTorqueStorage(rdStorage* aTorqueStorage);
	rdStorage* getTorqueStorage() const;
	void setTorqueSet(rdFunctionSet* aTorqueSet);
	rdFunctionSet* getTorqueSet() const;
	rdStorage* getAppliedTorqueStorage();
	void setStorageCapacityIncrements(int aIncrement);
	void setInputTorquesInGlobalFrame(bool aTrueFalse);
	bool getInputTorquesInGlobalFrame() const;


	
	//--------------------------------------------------------------------------
	// CALLBACKS
	//--------------------------------------------------------------------------
	virtual void
		applyActuation(double aT,double *aX,double *aY);

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
public:
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suTorqueApplier
//=============================================================================
//=============================================================================


#endif // #ifndef __suTorqueApplier_h__
