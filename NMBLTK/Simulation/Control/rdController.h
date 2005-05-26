// rdController.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <RD/Simulation/Model/rdModel.h>
//============================================================================
#ifndef __rdController_h__
#define __rdController_h__


#include "rdControlSet.h"


const int rdController_NAME_LENGTH = 64;
const int rdController_DESCRIP_LENGTH = 8192;


//=============================================================================
//=============================================================================
/**
 * An abstract class for specifying the interface for controlling an
 * rdModel.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdController  
{

//=============================================================================
// DATA
//=============================================================================
public:
	static const int NAME_LENGTH;
	static const int DESCRIP_LENGTH;
protected:
	/** Model. */
	rdModel *_model;
	/** Flag to indicate on or off state. */
	bool _on;
	/** Name. */
	char _name[rdController_NAME_LENGTH];
	/** Description. */
	char _descrip[rdController_DESCRIP_LENGTH];

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdController(rdModel *aModel);
	virtual ~rdController();
	void setNull();

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// MODEL
	rdModel* getModel();
	// ON/OFF
	void setOn(bool aTrueFalse);
	bool getOn();
	// NAME
	void setName(const char *aName);
	const char* getName();
	// DESCRIPTION
	void setDescription(const char *aDescrip);
	const char* getDescription();

	//--------------------------------------------------------------------------
	// CONTROL
	//--------------------------------------------------------------------------
	virtual void
		computeControls(double &rDT,double aT,const double *aY,
		rdControlSet &rX) = 0;

//=============================================================================
};	// END of class rdController
//=============================================================================
//=============================================================================

#endif // __rdController_h__


