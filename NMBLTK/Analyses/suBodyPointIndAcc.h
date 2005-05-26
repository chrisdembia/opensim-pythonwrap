// suBodyPointIndAcc.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suBodyPointIndAcc_h__
#define __suBodyPointIndAcc_h__


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "suAnalysesDLL.h"
#include "suIndAcc.h"

const int suBodyPointIndAcc_NAME_LENGTH = 256;
const int suBodyPointIndAcc_BUFFER_LENGTH = 2048;

//=============================================================================
//=============================================================================
/**
 * A class for computing the induced accelerations of a point on a body
 * segment of a model.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API suBodyPointIndAcc : public suIndAcc 
{
//=============================================================================
// DATA
//=============================================================================
public:
	static const int NAME_LENGTH;
	static const int BUFFER_LENGTH;
private:
	char _buffer[suBodyPointIndAcc_BUFFER_LENGTH];
	char _tmp[suBodyPointIndAcc_BUFFER_LENGTH];
protected:
	int _body;
	double _point[3];
	char _pointName[suBodyPointIndAcc_NAME_LENGTH];
	rdStorage *_axPointStore;
	rdStorage *_ayPointStore;
	rdStorage *_azPointStore;
	rdStorage *_vxPointStore;
	rdStorage *_vyPointStore;
	rdStorage *_vzPointStore;
	rdStorage *_pxPointStore;
	rdStorage *_pyPointStore;
	rdStorage *_pzPointStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	suBodyPointIndAcc(rdModel *aModel,int aBody,double aPoint[3]);
	suBodyPointIndAcc(rdModel *aModel,int aBody,double aPoint[3],
		rdStorage *aStates,rdStorage *aControls,char *aBaseName,
		char *aDir=NULL,char *aExtension=NULL);
	virtual ~suBodyPointIndAcc();
private:
	void setNull();
	void constructDescription();
	void allocatePointStorage();
	void deletePointStorage();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setBody(int aBody);
	int getBody();
	void setPoint(double aPoint[3]);
	void getPoint(double rPoint[3]);
	void setPointName(const char *aName);
	const char* getPointName();
	virtual void setStorageCapacityIncrements(int aIncrement);
	char* getColumnLabels(const char *aTag);

	//--------------------------------------------------------------------------
	// OPERATIONS
	//--------------------------------------------------------------------------
	int computePointAccelerations();

	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	virtual int
		printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class suBodyPointIndAcc
//=============================================================================
//=============================================================================


#endif // #ifndef __suBodyPointIndAcc_h__
