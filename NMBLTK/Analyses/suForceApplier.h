// suForceApplier.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, May Q. Liu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suForceApplier_h__
#define __suForceApplier_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdStorage.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdDerivCallback.h>
#include <RD/Simulation/Manager/rdManager.h>
#include <RD/Tools/rdVectorFunction.h>
#include <RD/Tools/rdFunctionSet.h>
#include "suAnalysesDLL.h"
#include "suContact.h"
#include "suDecomp.h"


//=============================================================================
//=============================================================================
/**
 * A derivatives callback used for applying external forces during a
 * simulation.
 *
 * @author Frank C. Anderson, May Q. Liu
 * @version 1.0
 */
class SUANALYSES_API suForceApplier : public rdDerivCallback 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Which body segment. */
	int _body;
	/** Point of force application. */
	double _point[3];
	/** Force to be applied. */
	double _force[3];
	/** VectorFunction containing points of force application (t,x,y,z). */
	rdVectorFunction* _pointFunction;
	/** VectorFunction containing force to be applied (t,x,y,z). */
	rdVectorFunction* _forceFunction;
	/** rdStorage containing points of force application (t,x,y,z). */
	rdStorage* _pointStorage;
	/** rdStorage containing force to be applied (t,x,y,z). */
	rdStorage* _forceStorage;
	/** Flag to set reference frame of input resultant force points */
	bool _inputPositionsInLocalFrame;
	/** Flag to set reference frame of input force */
	bool _inputForcesInGlobalFrame;
	/** FunctionSet containing the force to be applied (t,x,y,z). */
	rdFunctionSet* _forceSet;
	/** FunctionSet containing the point where the force is applied (t,x,y,z). */
	rdFunctionSet* _pointSet;
	/** Storage for the force that was actually applied during the simulation */
	rdStorage *_appliedForceStore;

		

//=============================================================================
// METHODS
//=============================================================================
public:
	suForceApplier(rdModel *aModel,int aBody);	
	suForceApplier(rdModel *aModel,int aBody,double aPoint[3]);
	suForceApplier(rdModel *aModel,int aBody,double aPoint[3],double aForce[3]);
	suForceApplier(rdModel *aModel,int aBody,rdVectorFunction* aPointFunction,rdVectorFunction* aForceFunction);
	suForceApplier(rdModel *aModel,int aBody,double aPoint[3],rdVectorFunction* aForceFunction);
	suForceApplier(rdModel *aModel,int aBody,rdStorage* aPointStorage,rdStorage* aForceStorage);
	suForceApplier(rdModel *aModel,int aBody,double aPoint[3],rdStorage* aForceStorage);
	suForceApplier(rdModel *aModel,int aBody,rdFunctionSet* aPointSet,rdFunctionSet* aForceSet);
	virtual ~suForceApplier();
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
	void setPoint(double aPoint[3]);
	void getPoint(double rPoint[3]) const;
	void setForce(double aForce[3]);
	void getForce(double rPoint[3]) const;
	void setForceFunction(rdVectorFunction* aForceFunction);
	rdVectorFunction* getForceFunction() const;
	void setPointFunction(rdVectorFunction* aPointFunction);
	rdVectorFunction* getPointFunction() const;
	void setForceStorage(rdStorage* aForceStorage);
	rdStorage* getForceStorage() const;
	void setPointStorage(rdStorage* aPointStorage);
	rdStorage* getPointStorage() const;

	void setForceSet(rdFunctionSet* aForceSet);
	rdFunctionSet* getForceSet() const;
	void setPointSet(rdFunctionSet* aPointSet);
	rdFunctionSet* getPointSet() const;

	void setInputPositionsInLocalFrame(bool aTrueFalse);
	bool getInputPositionsInLocalFrame() const;
	void setInputForcesInGlobalFrame(bool aTrueFalse);
	bool getInputForcesInGlobalFrame() const;

	rdStorage* getAppliedForceStorage();
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
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");


//=============================================================================
};	// END of class suForceApplier
//=============================================================================
//=============================================================================


#endif // #ifndef __suForceApplier_h__
