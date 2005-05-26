// suBodyIndPowers.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suBodyIndPowers_h__
#define __suBodyIndPowers_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suAnalysesDLL.h"
#include "suBodyIndAcc.h"


//=============================================================================
//=============================================================================
/**
 * A class for computing induced segmental powers.
 *
 *
 * @author Frank C. Anderson, Saryn R. Goldberg
 * @version 1.0
 */
class SUANALYSES_API suBodyIndPowers : public suBodyIndAcc
{
//=============================================================================
// DATA
//=============================================================================
private:

protected:
	rdStorage **_powerStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suBodyIndPowers(rdModel *aModel);
	suBodyIndPowers(rdModel *aModel,rdStorage *aStates,rdStorage *aControls,char *aBaseName,
		char *aDir=NULL,char *aExtension=NULL);
	virtual ~suBodyIndPowers();
private:
	void constructDescription();
	void constructColumnLabels();
	void allocateStoragePointers();
	void allocateStorage();
	void deleteStorage();


public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setStorageCapacityIncrements(int aIncrement);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	int computeBodyPowers();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void sumPowerResults();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suBodyIndPowers
//=============================================================================
//=============================================================================


#endif // #ifndef __suBodyIndPowers_h__
