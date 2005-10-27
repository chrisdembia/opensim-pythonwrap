// suForceApplier.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson, May Q. Liu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suForceApplier_h__
#define __suForceApplier_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdStorage.h>
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
	/** Flag to set reference frame of input force */
	bool _inputForcesInGlobalFrame;
	/** Storage for the force that was actually applied during the simulation */
	rdStorage *_appliedForceStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suForceApplier(rdModel *aModel,int aBody);	
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

	void setInputForcesInGlobalFrame(bool aTrueFalse);
	bool getInputForcesInGlobalFrame() const;

	rdStorage* getAppliedForceStorage();
	void setStorageCapacityIncrements(int aIncrement);

	virtual void reset(); 
	
	void
		computePointFunction(rdStorage *aQStore,rdStorage *aUStore,
		rdVectorFunction &aPGlobal);

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
