// suContact.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson and Saryn Goldberg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suContact_h__
#define __suContact_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysis.h>
#include "suAnalysesDLL.h"


//=============================================================================
//=============================================================================
/**
 * A class for recording the contact forces (and torques) generated
 * during a simulation.  This class will record only the forces (and torques)
 * returned by the getContactForces() method of rdModel.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suContact : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
private:
	char _scalarLabels[DESCRIP_LENGTH];
	char _resultantForcePointLabels[DESCRIP_LENGTH];
	/** Array containing group assignemnts for each contact point in resultant
		 force point calc **/
	int *_resultantForcePointGroupAssignements;
	/** Number of resultant force point groups **/
	int _nResultantForcePointGroups;

protected:
	/** Array of contact points. */
	double *_points;
	/** Array of contact velocities. */
	double *_velocities;
	/** Array of contact forces. */
	double *_forces;
	/** Array of contact powers. */
	double *_powers;
	/** Array of resultant force point (x, y, and z direction for each RFP group). */
	double *_resultantForcePoints;
	/** Array of total contactforces (x, y and z direction for each RFP group). */
	double *_totContactForces;
	/** Array of total contactforces (x, y and z direction for each RFP group). */
	double *_totContactTorques;

	/** Storage for the contact points. */
	rdStorage *_pStore;
	/** Storage for the contact point velocities. */
	rdStorage *_vStore;
	/** Storage for the contact forces. */
	rdStorage *_fStore;
	/** Storage for contact powers. */
	rdStorage *_pwrStore;
	/** Storage for resultant force points. */
	rdStorage *_resultantForcePointsStore;
	/** Storage for total contact forces. */
	rdStorage *_totFStore;
	/** Storage for total torque. */
	rdStorage *_totTorqueStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suContact(rdModel *aModel, int *aResultantForcePointGroups=NULL);
	virtual ~suContact();
private:
	void setNull();
	void constructDescription();
	void constructColumnLabels(int nResultantForcePointgroups);
	void allocateStorage();
	void deleteStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	const char* getScalarColumnLabels() const;
	const char* getResultantForcePointColumnLabels() const;
	rdStorage* getPointsStorage() const;
	rdStorage* getVelocityStorage() const;
	rdStorage* getForceStorage() const;
	rdStorage* getPowerStorage() const;
	rdStorage* getResultantForcePointStorage() const;
	rdStorage* getTotForceStorage() const;
	rdStorage* getTotTorqueStorage() const;
	void setStorageCapacityIncrements(int aIncrement);


	//--------------------------------------------------------------------------
	// ANALYSIS
	//--------------------------------------------------------------------------
	virtual int
		begin(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData=NULL);
	virtual int
		step(double *aXPrev,double *aYPrev,
		int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData=NULL);
	virtual int
		end(int aStep,double aDT,double aT,double *aX,double *aY,
		void *aClientData=NULL);
protected:
	virtual int
		record(double aT,double *aX,double *aY);

	//--------------------------------------------------------------------------
	// UTILITIES
	//--------------------------------------------------------------------------
	void resetStorage();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
public:
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suContact
//=============================================================================
//=============================================================================


#endif // #ifndef __suContact_h__
