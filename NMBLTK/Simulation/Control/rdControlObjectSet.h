// rdControlObjectSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdControlObjectSet_h__
#define __rdControlObjectSet_h__

// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdArray.h>
#include <RD/Tools/rdObjectArray.h>
#include <RD/Simulation/Model/rdModel.h>
#include "rdControlObject.h"


// EXPORT LINE FOR MICROSOFT VISUAL C++
#ifndef UNIX
//template class RDSIMULATION_API rdArray<double>;
#endif


//=============================================================================
//=============================================================================
/**
 * An class for holding and managing a set of track objects.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdControlObjectSet : public rdObjectArray 
{

//=============================================================================
// DATA
//=============================================================================
private:
	/** Expandable array of supported object types. */
	static rdObjectArray _ObjectTypes;
protected:
	/** Expandable array of default objects. */
	rdObjectArray _defaultObjects;
	/** Model for which the tracking is conducted. */
	rdModel *_model;
	/** Array of last position errors. */
	rdArray<double> _pErrLast;
	/** Array of position errors. */
	rdArray<double> _pErr;
	/** Array of last velocity errors. */
	rdArray<double> _vErrLast;
	/** Array of velocity errors. */
	rdArray<double> _vErr;
	/** Array of weights of the desired acceleration. */
	rdArray<double> _w;
	/** Array of desired accelerations. */
	rdArray<double> _aDes;
	/** Array of accelerations. */
	rdArray<double> _a;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdControlObjectSet();
	rdControlObjectSet(const char *aFileName);
	virtual ~rdControlObjectSet();
private:
	void setNull();
	void constructDefaultObjects();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
public:
	// TRACK OBJECTS
	rdControlObject* appendTrackObject(rdControlObject *aObject);
	rdControlObject* setTrackObject(int aIndex,rdControlObject *aObject);
	rdControlObject* getTrackObject(int aIndex) const;
	// MODEL
	void setModel(rdModel *aModel);
	rdModel* getModel() const;
	// FUNCTIONS
	void setFunctions(rdFunctionSet &aFuncSet);
	void setFunctionsForVelocity(rdFunctionSet &aFuncSet);
	void setFunctionsForAcceleration(rdFunctionSet &aFuncSet);
	// ERRORS
	rdArray<double>& getPositionErrorsLast();
	rdArray<double>& getPositionErrors();
	rdArray<double>& getVelocityErrorsLast();
	rdArray<double>& getVelocityErrors();
	// WEIGHTS
	rdArray<double>& getWeights();
	// DESIRED ACCELERATIONS
	rdArray<double>& getDesiredAccelerations();
	// ACCELERATIONS
	rdArray<double>& getAccelerations();

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	void recordErrorsAsLastErrors();
	void computeErrors(double aT);
	void computeDesiredAccelerations(double aT);
	void computeAccelerations();

	//--------------------------------------------------------------------------
	// REGISTER SUPPORTED TRACK OBJECTS
	//--------------------------------------------------------------------------
	static void RegisterType(const rdControlObject &aObject);

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	void updateObject(bool aDeep=true);
	void updateNode(bool aDeep=true);
	void generateNode(DOMElement *aParent);

//=============================================================================
};	// END of class rdControlObjectSet
//=============================================================================
//=============================================================================

#endif // __rdControlObjectSet_h__


