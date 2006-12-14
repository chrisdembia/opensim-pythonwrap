// rdCMC_Task.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright (c) 2006 Stanford University and Realistic Dynamics, Inc.
// Contributors: Frank C. Anderson
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject
// to the following conditions:
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS,
// CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
// THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This software, originally developed by Realistic Dynamics, Inc., was
// transferred to Stanford University on November 1, 2006.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef rdCMC_Task_h__
#define rdCMC_Task_h__

// INCLUDES
#include "rdCMCDLL.h"
#include <OpenSim/Tools/rdTools.h>
#include <OpenSim/Tools/PropertyBool.h>
#include <OpenSim/Tools/PropertyBoolArray.h>
#include <OpenSim/Tools/PropertyInt.h>
#include <OpenSim/Tools/PropertyDblArray.h>
#include <OpenSim/Tools/Function.h>
#include <OpenSim/Tools/FunctionSet.h>
#include <OpenSim/Simulation/SIMM/AbstractModel.h>

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * An abstract base class for specifying a task objective for
 * a dynamic simulation.  This class supports joint, point, and orientation
 * task objectives.  Specfic implementations for these kinds of control
 * tasks should inherit from this class.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDCMC_API rdCMC_Task : public Object
{

//=============================================================================
// DATA
//=============================================================================
protected:
	// PROPERTIES
	/** Property to indicate on or off state. */
	PropertyBool _propOn;
	/** Body with respect to which the task goals are specified. */
	PropertyInt _propWRTBody;
	/** Body frame in which the task goals are expressed. */
	PropertyInt _propExpressBody;
	/** Property to specify the active task goals. */
	PropertyBoolArray _propActive;
	/** Weights of the task goals. */
	PropertyDblArray _propW;
	/** Position error feedback gain. */
	PropertyDblArray _propKP;
	/** Velocity error feedback gain. */
	PropertyDblArray _propKV;
	/** Feedforward acceleration gain. */
	PropertyDblArray _propKA;
	/** Directions of the task goal 0. */
	PropertyDblArray _propR0;
	/** Directions of the task goal 1. */
	PropertyDblArray _propR1;
	/** Directions of the task goal 2. */
	PropertyDblArray _propR2;

	// REFERENCES TO PROPERTY VALUES
	// NOTE- These refrence variables must be listed in the class after
	// the properties to which they refer.  The order in which member
	// variables are listed determines the order in which the member
	// variables are initialized.  The properties must be initialized
	// before the references can be initialized to something meaningful.
	/** Reference to the value of the on property. */
	bool &_on;
	/** Reference to the value of the WRTBody property. */
	int &_wrtBody;
	/** Reference to the value of the ExpressBody property. */
	int &_expressBody;
	/** Reference to the value of the Active property. */
	Array<bool> &_active;
	/** Reference to the value of the Weight property. */
	Array<double> &_w;
	/** Reference to the value of the KP property. */
	Array<double> &_kp;
	/** Reference to the value of the KV property. */
	Array<double> &_kv;
	/** Reference to the value of the KA property. */
	Array<double> &_ka;
	/** Reference to the value of the R0 property. */
	Array<double> &_r0;
	/** Reference to the value of the R1 property. */
	Array<double> &_r1;
	/** Reference to the value of the R2 property. */
	Array<double> &_r2;


	/** Model. */
	AbstractModel *_model;

	/** Number of task functions. */
	int _nTrk;
	/** Position task functions.  Different types of tasks can 
	require different numbers of task functions.  For example, to track
	a joint angle, only one task function is needed.  However, to track
	a position, up to three task functions may be needed. */
	Function *_pTrk[3];
	/** Velocity task functions.  If velocity task functions are
	not specified, derivatives of the position task function are used. */
	Function *_vTrk[3];
	/** Acceleration task functions.  If acceleration task functions are
	not specified, derivatives of the position task function are used. */
	Function *_aTrk[3];
	/** Last position error. */
	double _pErrLast[3];
	/** Position error. */
	double _pErr[3];
	/** Last velocity error. */
	double _vErrLast[3];
	/** Velocity error. */
	double _vErr[3];
	/** Desired accelerations. */
	double _aDes[3];
	/** Accelerations. */
	double _a[3];
	/** Jacobian. */
	double *_j;
	/** Effective mass matrix. */
	double *_m;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdCMC_Task();
	rdCMC_Task(DOMElement *aElement);
	rdCMC_Task(const rdCMC_Task &aTaskObject);
	virtual ~rdCMC_Task();
	virtual Object* copy() const = 0;
	virtual Object* copy(DOMElement *aElement) const = 0;
private:
	void setNull();
	void setupProperties();
	void copyData(const rdCMC_Task &aTaskObject);

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:

#ifndef SWIG
	rdCMC_Task& operator=(const rdCMC_Task &aTaskObject);
#endif

	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// MODEL
	virtual void setModel(AbstractModel *aModel);
	AbstractModel* getModel() const;
	// ON,OFF
	void setOn(bool aTrueFalse);
	bool getOn() const;
	// WRT BODY
	void setWRTBody(int aBody);
	int getWRTBody() const;
	// EXPRESS BODY
	void setExpressBody(int aBody);
	int getExpressBody() const;
	// ACTIVE
	void setActive(bool a0,bool a1=false,bool a2=false);
	bool getActive(int aWhich) const;
	// WEIGHTS
	void setWeight(double aW0,double aW1=0.0,double aW2=0.0);
	double getWeight(int aWhich) const;
	// POSITION FEEDBACK GAINS
	void setKP(double aK0,double aK1=0.0,double aK2=0.0);
	double getKP(int aWhich) const;
	// VELOCITY FEEDBACK GAINS
	void setKV(double aK0,double aK1=0.0,double aK2=0.0);
	double getKV(int aWhich) const;
	// ACCELERATION FEEDFORWARD GAINS
	void setKA(double aK0,double aK1=0.0,double aK2=0.0);
	double getKA(int aWhich) const;
	// DIRECTION OF TASK 0
	void setDirection_0(const double aR[3]);
	void getDirection_0(double rR[3]) const;
	// DIRECTION OF TASK 1
	void setDirection_1(const double aR[3]);
	void getDirection_1(double rR[3]) const;
	// DIRECTION OF TASK 2
	void setDirection_2(const double aR[3]);
	void getDirection_2(double rR[3]) const;
	// TASK FUNCTIONS
	int getNumTaskFunctions() const;
	void setTaskFunctions(Function *aF0,
		Function *aF1=NULL,Function *aF2=NULL);
	Function* getTaskFunction(int aWhich) const;
	void setTaskFunctionsForVelocity(Function *aF0,
		Function *aF1=NULL,Function *aF2=NULL);
	Function* getTaskFunctionForVelocity(int aWhich) const;
	void setTaskFunctionsForAcceleration(Function *aF0,
		Function *aF1=NULL,Function *aF2=NULL);
	Function* getTaskFunctionForAcceleration(int aWhich) const;
	// TASK KINEMATICS
	double getTaskPosition(int aWhich,double aT) const;
	double getTaskVelocity(int aWhich,double aT) const;
	double getTaskAcceleration(int aWhich,double aT) const;
	// LAST ERRORS
	void setPositionErrorLast(double aE0,double aE1=0.0,double aE2=0.0);
	double getPositionErrorLast(int aWhich) const;
	void setVelocityErrorLast(double aE0,double aE1=0.0,double aE2=0.0);
	double getVelocityErrorLast(int aWhich) const;
	// ERRORS
	double getPositionError(int aWhich) const;
	double getVelocityError(int aWhich) const;
	// DESIRED ACCELERATIONS
	double getDesiredAcceleration(int aWhich) const;
	// ACCELERATIONS
	double getAcceleration(int aWhich) const;

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeErrors(double aT) = 0;
	virtual void computeDesiredAccelerations(double aT) = 0;
	virtual void computeDesiredAccelerations(double aTI,double aTF) = 0;
	virtual void computeAccelerations() = 0;
	virtual void computeJacobian();
	virtual void computeEffectiveMassMatrix();

	//--------------------------------------------------------------------------
	// XML
	//--------------------------------------------------------------------------
	virtual void updateFromXMLNode();


//=============================================================================
};	// END of class rdCMC_Task
//=============================================================================
//=============================================================================

}; // end namespace

#endif // __rdCMC_Task_h__


