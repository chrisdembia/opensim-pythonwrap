// suBodyIndAcc.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suBodyIndAcc_h__
#define __suBodyIndAcc_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdTools.h>
#include <RD/Simulation/Model/rdModel.h>
#include "suAnalysesDLL.h"
#include "suIndAcc.h"


//=============================================================================
//=============================================================================
/**
 * A class for computing induced accelerations of the body segments of a
 * model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suBodyIndAcc : public suIndAcc 
{
//=============================================================================
// DATA
//=============================================================================
private:
	rdStorage **_aeBodyStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suBodyIndAcc(rdModel *aModel);
	suBodyIndAcc(rdModel *aModel,rdStorage *aStates,rdStorage *aControls,
		char *aBaseName,char *aDir=NULL,char *aExtension=NULL);
	virtual ~suBodyIndAcc();
private:
	void constructDescription();
	void constructColumnLabels();
	void allocateBodyStoragePointers();
	void allocateBodyStorage();
	void deleteBodyStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setStorageCapacityIncrements(int aIncrement);
	rdStorage* getBodyStore(int index);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	int computeBodyAccelerations();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void sumBodyAccelerationResults();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suBodyIndAcc
//=============================================================================
//=============================================================================


#endif // #ifndef __suBodyIndAcc_h__
