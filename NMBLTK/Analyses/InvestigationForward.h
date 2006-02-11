// InvestigationForward.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#ifndef __InvestigationForward_h__
//#define __InvestigationForward_h__

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
class SUANALYSES_API InvestigationForward: public Investigation
{
//=============================================================================
// MEMBER VARIABLES
//=============================================================================
private:
	/** Name of the controls file. */
	rdPropertyStr _controlsFileNameProp;
	std::string &_controlsFileName;
	/** Name of the initial states file. */
	rdPropertyStr _initialStatesFileNameProp;
	std::string &_initialStatesFileName;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	InvestigationForward();
	InvestigationForward(const std::string &aFileName);
	InvestigationForward(DOMElement *aElement);
	virtual ~InvestigationForward();
	// Copy constrctor and virtual copy 
	InvestigationForward(const InvestigationForward &aObject);
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
	InvestigationForward&
		operator=(const InvestigationForward &aInvestigationForward);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	// INTERFACE
	//--------------------------------------------------------------------------
	virtual void run();
	virtual void printResults(const char *aBaseName,const char *aDir=NULL,
		double aDT=-1.0,const char *aExtension=".sto");

//=============================================================================
};	// END of class InvestigationForward
//=============================================================================
//=============================================================================

//#endif // __InvestigationForward_h__


