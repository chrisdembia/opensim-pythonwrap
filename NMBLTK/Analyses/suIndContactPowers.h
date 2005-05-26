// suIndContactPowers.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suIndContactPowers_h__
#define __suIndContactPowers_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suAnalysesDLL.h"
#include "suIndAcc.h"


//=============================================================================
//=============================================================================
/**
 * A class for computing the powers delivered to contact elements induced by
 * the individual actuators of a model.  This analysis depends on a valid
 * contact force decomposition and the velocities of the contact points,
 * both expressed in the global frame.
 *
 * This class is derived from suIndContactPowers, which holds model
 * states and the contact force decomposition.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suIndContactPowers : public suIndAcc
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Storge for the velocities of the contact points. */
	rdStorage *_velStore;
	/** Storage for the computed induced contact powers. */
	rdStorage **_pwrStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suIndContactPowers(rdStorage *aContactVelocities,
		rdModel *aModel,rdStorage *aStates,rdStorage *aControls,char *aBaseName,
		char *aDir=NULL,char *aExtension=NULL);
	virtual ~suIndContactPowers();
private:
	void setNull();
	void constructDescription();
	void constructColumnLabels();
	void allocateStoragePointers();
	void allocateStorage();
	void deleteStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// CONTACT VELOCITIES
	rdStorage* getContactVelocities();

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	void computeContactPowers();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suIndContactPowers
//=============================================================================
//=============================================================================


#endif // #ifndef __suIndContactPowers_h__
