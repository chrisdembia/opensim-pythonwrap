// Investigation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __Investigation_h__
#define __Investigation_h__

#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdArrayPtrs.h>
#include <NMBLTK/Simulation/Model/rdModel.h>
#include <NMBLTK/Simulation/Model/rdAnalysisSet.h>
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

	// SERIALIZED PROPERTIES
	/** Name of the model library to load.  Do not include the library
	extension (e.g., .dll or .lib). */
	rdPropertyStr _modelLibraryProp;
	std::string &_modelLibrary;
	/** Name of the xml file used to deserialize or construct a model. */
	rdPropertyStr _modelFileProp;
	std::string &_modelFile;
	/** Name of the xml file used to construct an actuator set for the
	model. */
	rdPropertyStr _actuatorSetFileProp;
	std::string &_actuatorSetFile;
	/** Name of the xml file used to construct a contact force set for the
	model. */
	rdPropertyStr _contactForceSetFileProp;
	std::string &_contactForceSetFile;
	/** Name of the params files used for a SIMM Pipeline model. */
	rdPropertyStr _paramsFileProp;
	std::string &_paramsFile;
	/** List of additional libraries to load.  do not include the library
	extensions (e.g., .dll or .lib). */
	rdPropertyStrArray _libraryListProp;
	rdArray<std::string> &_libraryList;
	/** Directory used for writing results. */
	rdPropertyStr _resultsDirProp;
	std::string &_resultsDir;
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
	/** Set of analyses to be run. */
	rdPropertyObj _analysisSetProp;
	rdAnalysisSet &_analysisSet;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	virtual ~Investigation();
	Investigation();
	Investigation(const std::string &aFileName);
	Investigation(DOMElement *aElement);
	Investigation(const Investigation &aObject);
	//rdObject* copy() const;
	//rdObject* copy(DOMElement *aElement) const;

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
	rdAnalysisSet& getAnalysisSet() const;


	//--------------------------------------------------------------------------
	// MODEL LOADING
	//--------------------------------------------------------------------------
	void constructCommandLineForLoadModel(rdArray<std::string> &args);
	void loadModel();

	//--------------------------------------------------------------------------
	// INTERFACE
	//--------------------------------------------------------------------------
	virtual void run() = 0;
	virtual void printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class Investigation
//=============================================================================
//=============================================================================

#endif // __Investigation_h__


