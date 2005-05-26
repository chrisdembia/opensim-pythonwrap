// suIndAcc.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suIndAcc_h__
#define __suIndAcc_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdMath.h>
#include <RD/Tools/rdStorage.h>
#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/Model/rdAnalysis.h>
#include "suAnalysesDLL.h"


//=============================================================================
//=============================================================================
/**
 * A class that performs a basic induced acceleration analysis.
 *
 * An induced acceleration analysis can be peformed in two ways using this
 * class:  1) during the course of a simulation and 2) after a simulation
 * has completed.  For the second way, the states recorded during
 * the simulation as well an appropriate contact force decomposition must be
 * used to construct the suIndAcc instance.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suIndAcc : public rdAnalysis 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	int _nc;
	int _nic;
	int _ne;
	int _cAct;
	int _cGrav;
	int _cVel;
	int _cIner;
	int _cAllAct;
	int _cAll;
	double _ti;
	double _tf;

	const char **_cNames;
	double _contactThreshold;
	bool *_contactEstablished;
	double *_feContig,***_fe;
	rdStorage *_yStore;
	rdStorage *_xStore;
	rdStorage **_feStore;
	rdStorage **_aeStore;
	rdStorage **_velStore;
	rdStorage **_posStore;
	rdStorage *_iPosStore;
	rdStorage *_iVelStore;
	char *_aeDescrip;
	char *_aeLabels;
	/** Flag that determines whether accelerations are normalized by force. */
	bool _computeNormalizedAccelerations;

private:
	/** Flag which indicates whether or not accelerations are being computed
	using a NULL decomposition. */
	bool _useNullDecomposition;

//=============================================================================
// METHODS
//=============================================================================
public:
	suIndAcc(rdModel *aModel);
	suIndAcc(rdModel *aModel,rdStorage *aStates,rdStorage *aControls,
		char *aBaseName,char *aDir=NULL,char *aExtension=NULL);
	virtual ~suIndAcc();
private:
	void setNull();
	void initializeNumbers();
	void constructComponentNames();
	void constructDescription();
	void constructColumnLabels();
	void allocateElementVectors();
	void allocateStoragePointers();
	void allocateStorage();
	void deleteStorage();
	void createNullDecomposition();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// NUMBERS
	int getNumComponents();
	int getNumIndependentComponents();
	int getNumElements();
	// INDICES
	int getLastActuatorIndex();
	int getGravityIndex();
	int getVelocityIndex();
	int getInertialIndex();
	int getAllActuatorsIndex();
	int getAllIndex();
	// CONTACT TOLERANCE
	void setContactThreshold(double aThreshold);
	double getContactThreshold();
	// NAMES
	const char* getComponentName(int aC);
	// STORAGE
	virtual void setStorageCapacityIncrements(int aIncrement);
	rdStorage** getForceStorage();
	// NULL DECOMPOSITION
	bool getUseNullDecomposition();
	// NORMALIZED ACCELERATIONS
	void setComputeNormalizedAccelerations(bool aBool);
	bool getComputeNormalizedAccelerations();

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	int computeAccelerations();

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void sumForceResults();
	void sumAccelerationResults();
	void sumDecomposition();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	virtual void store();
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");
private:
	virtual int
		readDecomposition(char *aBaseName,char *aDir=NULL,
		char *aExtension=NULL);


//=============================================================================
};	// END of class suIndAcc
//=============================================================================
//=============================================================================


#endif // #ifndef __suIndAcc_h__
