// suBodyIndAccCOM.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson & Saryn R. Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suBodyIndAccCOM_h__
#define __suBodyIndAccCOM_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suAnalysesDLL.h"
#include "suIndAcc.h"
#include "suBodyIndAcc.h"


//=============================================================================
//=============================================================================
/**
 * A class for computing induced accelerations of the COM of a specified set of
 * the body segments of a model.
 *
 * @author Frank C. Anderson & Saryn R. Goldberg
 * @version 1.0
 */
class SUANALYSES_API suBodyIndAccCOM : public suBodyIndAcc 
{
//=============================================================================
// DATA
//=============================================================================
private:
	rdStorage *_aeCOMBodyStore;
	rdStorage *_veCOMBodyStore;
	rdStorage *_peCOMBodyStore;
	rdStorage *_posStore;
	rdStorage *_velStore;
	int _aN;
	int *_aBodyList;

//=============================================================================
// METHODS
//=============================================================================
public:
	suBodyIndAccCOM(rdModel *aModel, int aN=0, int aBodyList[] = NULL);
	suBodyIndAccCOM(rdModel *aModel,rdStorage *aStates,rdStorage *aControls,
		char *aBaseName,char *aDir=NULL,char *aExtension=NULL,
		int aN=0,int aBodyList[]=NULL);
	virtual ~suBodyIndAccCOM();
private:
	void constructDescription();
	void constructColumnLabels();
	void setBodyList(int aBodyList[]);
	void allocateBodyStorage();
	void deleteBodyStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setStorageCapacityIncrements(int aIncrement);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	int computeBodyCOMAccelerations();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void sumBodyCOMAccelerationResults();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suBodyIndAccCOM
//=============================================================================
//=============================================================================


#endif // #ifndef __suBodyIndAccCOM_h__
