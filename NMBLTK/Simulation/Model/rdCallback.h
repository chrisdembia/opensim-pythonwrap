// rdCallback.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2003 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdCallback_h__
#define __rdCallback_h__


// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdObject.h>

#include "rdModel.h"
#include <RD/Tools/rdPropertyBool.h>
#include <RD/Tools/rdPropertyDbl.h>

//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying a callback.
 *
 * Callbacks provide low-level access to aspects of an integration.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdCallback : public rdObject
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Model. */
	rdModel *_model;
private:
	/** On, off flag. */
	rdPropertyBool _onProp;
	bool &_on;
	/** Start time for the callback in normalized time. */
	rdPropertyDbl _startTimeProp;
	double &_startTime;
	/** End time for the callback in normalized time. */
	rdPropertyDbl _endTimeProp;
	double &_endTime;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdCallback(rdModel *aModel=NULL);
	rdCallback(const rdCallback &aCallback);
	rdCallback(const std::string &aFileName);
	rdCallback(DOMElement *aElement);
	virtual ~rdCallback();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	rdCallback& operator=(const rdCallback &aCallback);
#endif
private:
	void setNull();
	void setupProperties();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// MODEL
	virtual void setModel(rdModel *);
	rdModel* getModel() const;
	// ON,OFF
	void setOn(bool aTrueFalse);
	bool getOn() const;
	// START,END
	void setStartTime(double aStartTime);
	double getStartTime() const;
	void setEndTime(double aEndTime);
	double getEndTime() const;

//=============================================================================
};	// END of class rdCallback
//=============================================================================
//=============================================================================

#endif // __rdCallback_h__


