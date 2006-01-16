// Investigation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#ifndef __Investigation_h__
//#define __Investigation_h__

#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
class rdXMLDocument;


//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying the interface for an investigation.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API Investigation: public rdObject
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Pointer to the model being investigated. */
	rdModel *_model;

	/** Output precision. */
	rdPropertyInt _outputPrecisionProp;
	int &_outputPrecision;
	/** Initial time for the investigation. */
	rdPropertyDbl _tiProp;
	double &_ti;
	/** Final time for the investigation. */
	rdPropertyDbl _tfProp;
	double &_tf;
	/** Maximum number of steps for the integrator. */
	rdPropertyInt _maxStepsProp;
	int &_maxSteps;
	/** Maximum integration step size. */
	rdPropertyDbl _maxDTProp;
	double &_maxDT;
	/** Integrator error tolerance. */
	rdPropertyDbl _errorToleranceProp;
	double &_errorTolerance;
	/** Integrator find tolerance. */
	rdPropertyDbl _fineToleranceProp;
	double &_fineTolerance;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	Investigation();
	Investigation(const std::string &aFileName);
	Investigation(DOMElement *aElement);
	virtual ~Investigation();
	// Copy constrctor and virtual copy 
	Investigation(const Investigation &aObject);
private:
	void setNull();
	void setupProperties();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	Investigation& operator=(const Investigation &aInvestigation);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setModel(rdModel *aModel);
	virtual rdModel* getModel() const;
	void setOutputPrecision(int aPrecision);
	int getOutputPrecision() const;

	//--------------------------------------------------------------------------
	// INTERFACE
	//--------------------------------------------------------------------------
	virtual void run() = 0;
	virtual void printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto") = 0;

//=============================================================================
};	// END of class Investigation
//=============================================================================
//=============================================================================

//#endif // __Investigation_h__


