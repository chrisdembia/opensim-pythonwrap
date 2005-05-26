// suGeneralizedForceApplier.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, May Q. Liu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suGeneralizedForceApplier_h__
#define __suGeneralizedForceApplier_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdDerivCallback.h>
#include <RD/Simulation/Manager/rdManager.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suDecomp.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for applying a generalized force during a
 * simulation.
 *
 * @author Frank C. Anderson, Saryn Goldberg
 * @version 1.0
 */
class SUANALYSES_API suGeneralizedForceApplier : public rdDerivCallback 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Which generalized coordinate. */
	int _genCoord;
	/** Generalized force to be applied. */
	double _generalizedForce;
	/** Factor that generalized force will be scaled by. */
	double _scaleFactor;
	/** rdStorage containing generalized force to be applied */
	rdStorage* _generalizedForceStorage;
	/** Index of collumn in rdStorage where generalized force is stored */
	int _genForceIndex;
	/** Storage for the generalized force that was actually applied during 
	the simulation */
	rdStorage *_appliedGeneralizedForceStore;
	/** variable for testing */
	double _aTSet;



//=============================================================================
// METHODS
//=============================================================================
public:
	suGeneralizedForceApplier(rdModel *aModel);	
	suGeneralizedForceApplier(rdModel *aModel,int aGenCoord);
	suGeneralizedForceApplier(rdModel *aModel,int aGenCoord,double aGeneralizedForce);
	suGeneralizedForceApplier(rdModel *aModel,int aGenCoord,rdStorage* aGeneralizedForceStorage,int aIndex);
	virtual ~suGeneralizedForceApplier();
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
	void setGeneralizedCoordinate(int aGenCoord);
	int getGeneralizedCoordinate() const;
	void setScaleFactor(double aFactor);
	double getScaleFactor() const;
	void setGeneralizedForce(double aGeneralizedForce);
	double getGeneralizedForce() const;
	void setGeneralizedForceStorage(rdStorage* aGeneralizedForceStorage);
	rdStorage* getGeneralizedForceStorage() const;
	void setGeneralizedForceIndex(int aIndex);
	int getGeneralizedForceIndex() const;
	rdStorage* getAppliedGeneralizedForceStorage();
	void setStorageCapacityIncrements(int aIncrement);


	
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
		printResults(char *aBaseName,char *aDir=NULL,double aDT=-1.0,
		char *aExtension=".sto");

//=============================================================================
};	// END of class suGeneralizedForceApplier
//=============================================================================
//=============================================================================


#endif // #ifndef __suGeneralizedForceApplier_h__
