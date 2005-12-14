// InvestigationPerturbation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#ifndef __InvestigationPerturbation_h__
//#define __InvestigationPerturbation_h__

#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Simulation/Model/Investigation.h>
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include "suAnalyses.h"
class rdXMLDocument;


//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying the interface for an investigation.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class SUANALYSES_API InvestigationPerturbation: public Investigation
{
//=============================================================================
// MEMBER VARIABLES
//=============================================================================
private:
	/** Name of the controls file. */
	rdPropertyStr _controlsFileNameProp;
	std::string &_controlsFileName;
	/** Name of the center of pressure file. */
	rdPropertyStr _copFileNameProp;
	std::string &_copFileName;
	/** Name of the generalized coordinate file. */
	rdPropertyStr _qFileNameProp;
	std::string &_qFileName;
	/** Name of the generalized speed file. */
	rdPropertyStr _uFileNameProp;
	std::string &_uFileName;
	/** Name of the states file. */
	rdPropertyStr _yFileNameProp;
	std::string &_yFileName;

	// WORK VARIABLES
	/** Control set. */
	rdControlSet *_controlSet;
	/** Center of pressure storage. */
	rdStorage *_copStore;
	/** Generalized coordinates storage. */
	rdStorage *_qStore;
	/** Generalized speed storage. */
	rdStorage *_uStore;
	/** States storage. */
	rdStorage *_yStore;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	InvestigationPerturbation();
	InvestigationPerturbation(const std::string &aFileName);
	InvestigationPerturbation(DOMElement *aElement);
	virtual ~InvestigationPerturbation();
	// Copy constrctor and virtual copy 
	InvestigationPerturbation(const InvestigationPerturbation &aObject);
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
private:
	void setNull();
	void setupProperties();
	void constructCorrectiveSprings();

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	InvestigationPerturbation&
		operator=(const InvestigationPerturbation &aInvestigationPerturbation);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	virtual void setModel(rdModel *aModel);

	//--------------------------------------------------------------------------
	// INTERFACE
	//--------------------------------------------------------------------------
	virtual void run();
	virtual void printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class InvestigationPerturbation
//=============================================================================
//=============================================================================

//#endif // __InvestigationPerturbation_h__


