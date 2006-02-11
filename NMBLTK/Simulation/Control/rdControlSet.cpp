// rdControlSet.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2000-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdObject.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include "rdControlSet.h"


using namespace std;


//=============================================================================
// STATICS
//=============================================================================


//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 *
 * @todo Figure out why the default controls can't be deleted.
 */
rdControlSet::~rdControlSet()
{
}
//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdControlSet::rdControlSet() :
	_ptcMap(-1), _ptpMap(-1)
{
	setNull();
	generateParameterMaps();
}
//_____________________________________________________________________________
/**
 * Construct an control set from file.
 *
 * @param aFileName Name of the file.
 */
rdControlSet::rdControlSet(const string &aFileName) :
	rdSet<rdControl>(aFileName), _ptcMap(-1), _ptpMap(-1)
{
	setNull();
	updateFromXMLNode();
	// removeInvalidObjects();
	generateParameterMaps();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aSet Analysis set to be copied.
 */
rdControlSet::rdControlSet(const rdControlSet &aSet) :
	rdSet<rdControl>(aSet),
	_ptcMap(-1), _ptpMap(-1)
{
	setNull();
	_ptcMap = aSet._ptcMap;
	_ptpMap = aSet._ptpMap;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the member variables to their null values.
 */
void rdControlSet::
setNull()
{
	setType("rdControlSet");
	setName("Control Set");
	setupProperties();
	_ptcMap.setSize(0);
	_ptpMap.setSize(0);
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void rdControlSet::
setupProperties()
{
}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT (=)
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this set to another set.
 * This operator makes a complete copy of the specified set; all member
 * variables and objects in the set are copied.  Because all objects are
 * copied, this set takes ownership of the newly allocated objects (i.e.,
 * _memoryOwner is set to true. So, the result is two independent,
 * identical sets, with the possible exception of the _memoryOwner flag.
 *
 * @param aSet Set to be copied.
 * @return Reference to this set.
 */
#ifndef SWIG
rdControlSet& rdControlSet::
operator=(const rdControlSet &aSet)
{	
	// BASE CLASS
	rdSet<rdControl>::operator=(aSet);

	// MEMBERS
	_ptcMap = aSet._ptcMap;
	_ptpMap = aSet._ptpMap;

	return(*this);
}
#endif // SWIG



//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// SIZE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the size of the control set.
 *
 * @param aForModelControls Flag indicating whether or not to get the size
 * for only model controls or all controls in the set.  Model controls are
 * controls that are involved in controlling a model; the number of model
 * controls should be the same as that returned by rdModel::getNX().
 * Example of non-model controls include the final time of a simulation or
 * an initial value for a joint angle; these quantities are for setting up
 * a simulation, they are not involved in controlling a model.  If
 * aForModelControls is true, the number of model controls in the set is
 * returned; if false, the total number of controls in the set is returned.
 */
int rdControlSet::
getSize(bool aForModelControls) const
{
	if(!aForModelControls) return( rdSet<rdControl>::getSize() );

	int i,n;
	rdControl *control;
	for(n=i=0;i<rdSet<rdControl>::getSize();i++) {
		control = get(i);
		if(control==NULL) continue;
		if(control->getIsModelControl()) n++;
	}

	return(n);
}

//-----------------------------------------------------------------------------
// CONTROL LIST
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the list of controls of a specified type.
 *
 * This method can be slow, so minimize its use.
 *
 * @param aType Type of the control (e.g., rdControlLinear).
 * @param aList Array of indices of the controls of type aType.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @see get()
 */
void rdControlSet::
getControlList(const char *aType,rdArray<int> &rList,bool aForModelControls) const
{
	rList.setSize(0);

	int i;
	int size = getSize(false);
	rdControl *control;
	for(i=0;i<size;i++) {
		control = get(i);
		if(control==NULL) continue;
		if(aForModelControls) if(!control->getIsModelControl()) continue;

		if(control->getType()==aType) {
			rList.append(i);
		}
	}
}

//-----------------------------------------------------------------------------
// CONTROL VALUES
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the values of the control curves held in this set at a specified time.
 *
 * Normally to modify the value of a control curve setParameterValues()
 * would be used.  The shape of the control curve is determined by the
 * parameters.
 *
 * If parameters exist at the specified time, these parameters are modified
 * to give the control curve the specified value.  Otherwise, new parameters
 * are added to the control curve.
 *
 * @param aT Time at which the value of the control curve is to be set.
 * @param aX Array of control curve values, the length of which should
 * equal the number of controls.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @todo New controls do not appear to be inserting at the correct location
 * in the XML file.  Is this a problem?
 */
void rdControlSet::
setControlValues(double aT,const double aX[],
	bool aForModelControls)
{
	int i,j;
	int size = getSize(false);
	rdControl *control;
	for(i=j=0;j<size;j++) {
		control = get(j);
		if(control==NULL) continue;
		if(aForModelControls) if(!control->getIsModelControl()) continue;
	
		control->setControlValue(aT,aX[i]);
		i++;
	}
	generateParameterMaps();
}
//_____________________________________________________________________________
/**
 * Set the values of the control curves held in this set at a specified time.
 *
 * Normally to modify the value of a control curve setParameterValues()
 * would be used.  The shape of the control curve is determined by the
 * parameters.
 *
 * If parameters exist at the specified time, these parameters are modified
 * to give the control curve the specified value.  Otherwise, new parameters
 * are added to the control curve.
 *
 * @param aT Time at which the value of the control curve is to be set.
 * @param aX Array of control curve values, the length of which should
 * equal the number of controls.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @todo New controls do not appear to be inserting at the correct location
 * in the XML file.  Is this a problem?
 */
void rdControlSet::
setControlValues(double aT,const rdArray<double> &aX,
	bool aForModelControls)
{
	int i,n;
	int size = getSize(false);
	rdControl *control;
	for(n=i=0;(n<aX.getSize())&&(i<size);i++) {
		control = get(i);
		if(control==NULL) continue;
		if(aForModelControls) if(!control->getIsModelControl()) continue;
	
		control->setControlValue(aT,aX[n]);
		n++;
	}
	generateParameterMaps();
}
//_____________________________________________________________________________
/**
 * Get the values of the control curves held in this set at a specified time.
 *
 *	This is the bread-and-butter method of the controls class; it is called
 * repeatedly throughout an integration.
 *
 * @param aT Time at which to get the values of the control curves.
 * @param rX Array of control curve values.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 */
void rdControlSet::
getControlValues(double aT,double rX[],
	bool aForModelControls) const
{
	// GET VALUES
	int i,n;
	rdControl *control;
	int size = getSize(false);
	for(n=i=0;i<size;i++) {
		control = get(i);
		if(control==NULL) continue;
		if(aForModelControls) if(!control->getIsModelControl()) continue;
	
		rX[n] = control->getControlValue(aT);
		n++;
	}
}
//_____________________________________________________________________________
/**
 * Get the values of the control curves held in this set at a specified time.
 *
 *	This is the bread-and-butter method of the controls class; it is called
 * repeatedly throughout an integration.
 *
 * @param aT Time at which to get the values of the control curves.
 * @param rX Array of control curve values.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 */
void rdControlSet::
getControlValues(double aT,rdArray<double> &rX,
	bool aForModelControls) const
{
	// INITIALIZE SIZE
	rX.setSize(0);

	// GET VALUES
	int i;
	rdControl *control;
	int size = getSize(false);
	for(i=0;i<size;i++) {
		control = get(i);
		if(control==NULL) continue;
		if(aForModelControls) if(!control->getIsModelControl()) continue;
	
		rX.append(control->getControlValue(aT));
	}
}

//-----------------------------------------------------------------------------
// PARAMETER NUMBER
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the number of control parameters.
 *
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @return Number of control parameters.
 */
int rdControlSet::
getNumParameters(bool aForModelControls) const
{
	int i,n;
	int size = getSize(false);
	rdControl *control;
	for(n=i=0;i<size;i++) {
		control = get(i);
		if(control==NULL) continue;
		if(aForModelControls) if(!control->getIsModelControl()) continue;
		n += control->getNumParameters();
	}
	return(n);
}

//-----------------------------------------------------------------------------
// PARAMETER LISTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get a list of parameters for all controls or just the controls that
 * are model controls.  This list can be used to get parameter mins,
 * maxs, and values.
 *
 * @param rList List of parameters.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @see getParameterMins()
 * @see getParameterMaxs()
 * @see getParameterValues()
 */
void rdControlSet::
getParameterList(rdArray<int> &rList,bool aForModelControls) const
{
	rList.setSize(0);

	int i,j,sp,n;
	int size = getSize(false);
	rdControl *control;
	for(sp=i=0;i<size;i++) {
		control = get(i);
		if(control==NULL) continue;
		n = control->getNumParameters();
		for(j=0;j<n;j++,sp++) {
			if(aForModelControls) if(!control->getIsModelControl())
				continue;
			rList.append(sp);
		}
	}	
}
//_____________________________________________________________________________
/**
 * Get the list of parameters that affect the control curves at a specified
 * time.  This list can be used to get parameter mins, maxs, and values.
 *
 * @param aT Time in question.
 * @param rList List of parameters.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @see getParameterMins()
 * @see getParameterMaxs()
 * @see getParameterValues()
 */
void rdControlSet::
getParameterList(double aT,rdArray<int> &rList,
	bool aForModelControls) const
{
	rList.setSize(0);

	int i,j,n;
	int size = getSize(false);
	rdControl *control;
	rdArray<int> list(-1);
	for(n=i=0;i<size;i++) {

		// GET CONTROL
		control = get(i);
		if(control==NULL) continue;

		// ACTUATOR CONTROL?
		if(aForModelControls) if(!control->getIsModelControl()) {
			n += control->getNumParameters();
			continue;
		}

		// GET LIST
		control->getParameterList(aT,list);
		for(j=0;j<list.getSize();j++) {
			rList.append(n+list[j]);
		}
		n += control->getNumParameters();
	}	
}
//_____________________________________________________________________________
/**
 * Get the list of parameters that affect the control curves between two
 * specified times and that do NOT affect the control curve below the lower
 * of these two times.
 *
 * This method is useful when solving for a set of controls for a dynamic
 * simulation.  When solving for a set of controls, one always wants to
 * go forward in time.  Therefore, one does not want to change control
 * parameters that affect the control curve at past times.
 *
 * A control parameter is included in the list only if it affects
 * the control curve in the specified time interval AND does NOT
 * affect the control curve below the lower bound of the
 * specified time interval.  So, it is possible that some of the
 * parameters on the returned list could affect the control curve at
 * times greater than the upper bound of the specified time interval.
 *
 * @param aTLower Lower time bound.  The control curves are not affected
 * below this time by any of the returned parameters.
 * @param aTUpper Upper time bound.  The control curves may be affected
 * for times greater than this time.
 * @param rList List of control parameters (their indices to be exact) that
 * affect the curve between aTLower and aTUpper but not before aTLower.
 * @param aForModelControls If true, only model controls are
 * considered.  If false, all controls are considered.
 * @see getParameterMins()
 * @see getParameterMaxs()
 * @see getParameterValues()
 */
void rdControlSet::
getParameterList(double aTLower,double aTUpper,rdArray<int> &rList,
	bool aForModelControls) const
{
	rList.setSize(0);

	int i,j,n;
	int size = getSize(false);
	rdControl *control;
	rdArray<int> list(-1);
	for(n=i=0;i<size;i++) {

		// GET CONTROL
		control = get(i);
		if(control==NULL) continue;

		// ACTUATOR CONTROL?
		if(aForModelControls) if(!control->getIsModelControl()) {
			n += control->getNumParameters();
			continue;
		}

		// GET LIST
		control->getParameterList(aTLower,aTUpper,list);
		for(j=0;j<list.getSize();j++) {
			rList.append(n+list[j]);
		}
		n += control->getNumParameters();
	}	
}

//-----------------------------------------------------------------------------
// PARAMETER MIN AND MAX
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the minimum values allowed for the control parameters.
 *
 * @param rMins Array of minimum allowed values.
 * @param aList List of controls.  If NULL, the values for all parameters for
 * all controls in the control set are gotten.  Otherwise, the parameters for
 * the controls in the list are gotten.
 */
void rdControlSet::
getParameterMins(rdArray<double> &rMins,const rdArray<int> *aList) const
{
	// INITIALIZE SIZE
	rMins.setSize(0);

	// VARIABLE DECLARATIONS
	int i,p;
	int size = getSize(false);
	rdControl *control;

	// NO LIST
	if(aList==NULL) {
		for(i=0;i<size;i++) {
			control = get(i);
			if(control==NULL) continue;	
			for(p=0;p<control->getNumParameters();p++) {
				rMins.append(control->getParameterMin(p));
			}
		}

	// LIST
	} else {
		int c,sp;
		for(i=0;i<aList->getSize();i++) {

			// PARAMETER
			sp = (*aList)[i];

			// GET CONTROL
			try {
				c = _ptcMap.get(sp);
			} catch(rdException &x) {
				x.print(cout);
				continue;
			}
			control = get(c);
			if(control==NULL) continue;
		
			// GET PARAMETER MIN
			p = _ptpMap[sp];
			rMins.append(control->getParameterMin(p));
		}
	}
}
//_____________________________________________________________________________
/**
 * Get the maximum values allowed for the control parameters.
 *
 * @param rMaxs Array of maximum allowed values.
 * @param aList List of controls.  If NULL, the values for all parameters for
 * all controls in the control set are gotten.  Otherwise, the parameters for
 * the controls in the list are gotten.
 */
void rdControlSet::
getParameterMaxs(rdArray<double> &rMaxs,const rdArray<int> *aList) const
{
	// INITIALIZE SIZE
	rMaxs.setSize(0);

	// VARIABLE DECLARATIONS
	int i,p;
	int size = getSize(false);
	rdControl *control;

	// NO LIST
	if(aList==NULL) {
		for(i=0;i<size;i++) {
			control = get(i);
			if(control==NULL) continue;		
			for(p=0;p<control->getNumParameters();p++) {
				rMaxs.append(control->getParameterMax(p));
			}
		}

	// LIST
	} else {
		int c,sp;
		for(i=0;i<aList->getSize();i++) {

			// PARAMETER
			sp = (*aList)[i];

			// GET CONTROL
			try {
				c = _ptcMap.get(sp);
			} catch(rdException &x) {
				x.print(cout);
				continue;
			}
			control = get(c);
			if(control==NULL) continue;
		
			// GET PARAMETER MAX
			p = _ptpMap[sp];
			rMaxs.append(control->getParameterMax(p));
		}
	}
}

//-----------------------------------------------------------------------------
// PARAMETER VALUE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the values of the control parameters.
 *
 * @param rP Array of parameters values, the length of which should
 * equal the total number of parameters or the size of aList.
 * @param aList List of controls.  If NULL, the values for all parameters for
 * all controls in the control set are gotten.  Otherwise, the parameters for
 * the controls in the list are gotten.
 */
void rdControlSet::
getParameterValues(double rP[],const rdArray<int> *aList) const
{
	// VARIABLE DECLARATIONS
	int i,p;
	int size = getSize(false);
	rdControl *control;

	// NO LIST
	if(aList==NULL) {
		int n;
		for(n=i=0;i<size;i++) {
			control = get(i);
			if(control==NULL) continue;
			for(p=0;p<control->getNumParameters();p++,n++) {
				rP[n] = control->getParameterValue(p);
			}
		}

	// LIST
	} else {
		int c,sp;
		for(i=0;i<aList->getSize();i++) {

			// PARAMETER
			sp = (*aList)[i];

			// GET CONTROL
			try {
				c = _ptcMap.get(sp);
			} catch(rdException &x) {
				x.print(cout);
				continue;
			}
			control = get(c);
			if(control==NULL) continue;
		
			// GET PARAMETER MAX
			p = _ptpMap[sp];
			rP[i] = control->getParameterValue(p);
		}
	}
}
//_____________________________________________________________________________
/**
 * Get the values of the control parameters.
 *
 * @param rP Array of parameters values, the length of which should
 * equal the total number of parameters or the size of aList.
 * @param aList List of controls.  If NULL, the values for all parameters for
 * all controls in the control set are gotten.  Otherwise, the parameters for
 * the controls in the list are gotten.
 */
void rdControlSet::
getParameterValues(rdArray<double> &rP,const rdArray<int> *aList) const
{
	rP.setSize(0);

	// VARIABLE DECLARATIONS
	int i,p;
	int size = getSize(false);
	rdControl *control;

	// NO LIST
	if(aList==NULL) {
		for(i=0;i<size;i++) {
			control = get(i);
			if(control==NULL) continue;
			for(p=0;p<control->getNumParameters();p++) {
				rP.append(control->getParameterValue(p));
			}
		}

	// LIST
	} else {
		int c,sp;
		for(i=0;i<aList->getSize();i++) {

			// PARAMETER
			sp = (*aList)[i];

			// GET CONTROL
			try {
				c = _ptcMap.get(sp);
			} catch(rdException &x) {
				x.print(cout);
				continue;
			}
			control = get(c);
			if(control==NULL) continue;
		
			// GET PARAMETER MAX
			p = _ptpMap[sp];
			rP.append(control->getParameterValue(p));
		}
	}
}
//_____________________________________________________________________________
/**
 * Set the values of the control parameters.
 *
 * @param aP Array of control parameters, the length of which should be
 * either the total number of parameters (if aList=NULL) or the same
 * length as aList.
 * @param aList List of controls.  If NULL, the values for all parameters for
 * all controls in the control set are gotten.  Otherwise, the parameters for
 * the controls in the list are gotten.
 */
void rdControlSet::
setParameterValues(const double *aP,const rdArray<int> *aList)
{
	// VARIABLE DECLARATIONS
	int i,sp,p;
	int size = getSize(false);
	rdControl *control;

	// NO LIST
	if(aList==NULL) {
		for(sp=i=0;i<size;i++) {
			control = get(i);
			if(control==NULL) continue;
			for(p=0;p<control->getNumParameters();p++,sp++) {
				control->setParameterValue(p,aP[sp]);
			}
		}

	// LIST
	} else {
		int c;
		int n = aList->getSize();
		for(i=0;i<n;i++) {

			// PARAMETER
			sp = (*aList)[i];

			// GET CONTROL
			try {
				c = _ptcMap.get(sp);
			} catch(rdException &x) {
				x.print(cout);
				continue;
			}
			control = get(c);
			if(control==NULL) continue;
		
			// SET PARAMETER
			p = _ptpMap[sp];
			control->setParameterValue(p,aP[i]);
		}
	}
}

//_____________________________________________________________________________
/**
 * Set the values of the control parameters.
 *
 * @param aP Array of control parameters, the length of which should be
 * either the total number of parameters (if aList=NULL) or the same
 * length as aList.
 * @param aList List of controls.  If NULL, the values for all parameters for
 * all controls in the control set are gotten.  Otherwise, the parameters for
 * the controls in the list are gotten.
 */
void rdControlSet::
setParameterValues(const rdArray<double> &aP,const rdArray<int> *aList)
{
	// VARIABLE DECLARATIONS
	int i,sp,p;
	int size = getSize(false);
	rdControl *control;

	// NO LIST
	if(aList==NULL) {
		for(sp=i=0;i<size;i++) {
			control = get(i);
			if(control==NULL) continue;
			for(p=0;p<control->getNumParameters();p++,sp++) {
				if(sp>=aP.getSize()) {
					printf("rdControlSet.setParameterValues: ERR- incorrect ");
					printf("number of parameters.\n");
					return;
				}
				control->setParameterValue(p,aP[sp]);
			}
		}

	// LIST
	} else {
		int c;
		int n = aList->getSize();
		if(n > aP.getSize()) {
			n = aP.getSize();
			printf("rdControlSet.setParameterValues: WARN- aP and aList are ");
			printf("different sizes.\n");
		}

		for(i=0;i<n;i++) {

			// PARAMETER
			sp = (*aList)[i];

			// GET CONTROL
			try {
				c = _ptcMap.get(sp);
			} catch(rdException &x) {
				x.print(cout);
				continue;
			}
			control = get(c);
			if(control==NULL) continue;
		
			// SET PARAMETER
			p = _ptpMap[sp];
			control->setParameterValue(p,aP[i]);
		}
	}
}


//=============================================================================
// UTILITY
//=============================================================================
//-----------------------------------------------------------------------------
// SIMPLIFY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Simplify all the control curves in a control set.
 *
 * @param aProperties Set of properties containing the parameters used
 * to carry out the simplifications.  See each control class for the list
 * of properties needed to perform the simplification.
 */
void rdControlSet::
simplify(const rdPropertySet &aProperties)
{
	int i;
	int size = getSize();
	rdControl *control;
	for(i=0;i<size;i++) {

		// GET CONTROL
		control = get(i);
		if(control==0) continue;

		// SIMPLIFY
		try {
			control->simplify(aProperties);
		} catch(rdException x) {
			x.print(cout);
		}
	}
}
//-----------------------------------------------------------------------------
// STORAGE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Construct a storage object from the controls in the set over a specified
 * interval using a specified number of points.
 *
 * @param aN Number of times to sample the time interval.
 * @param aT1 Start of the interval.
 * @param aT2 End of the interval.
 * @param aForModelControls
 */
rdStorage* rdControlSet::
constructStorage(int aN,double aT1,double aT2,bool aForModelControls)
{
	if(aN<=2) aN=2;
	double dt = (aT2-aT1) / (aN-1);

	double t;
	rdArray<double> x(0.0);
	rdStorage *store = new rdStorage();
	for(t=aT1;t<aT2;t+=dt) {
		getControlValues(t,x,aForModelControls);
		store->append(t,x.getSize(),&x[0]);
	}

	store->setName(getName());

	return(store);
}
//-----------------------------------------------------------------------------
// PARAMETER MAPS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Map a control-set parameter to a control.
 *
 * In the control set, the paramters for each of the controls are
 * concatenated into an array.  Since there is not a one-to-one
 * correspondence between control-set parameters and controls (i.e., a
 * particular control may have many parameters), it is necessary
 * both to map to which control each control-set parameter belongs and
 * to map to which parameter within a particular control a control-set
 * parameter corresponds.
 *
 * @param aIndex Index of the parameter in this control set.
 * @return Index of the control to which the specified parameter belongs.  If
 * no such parameter exists, -1 is returned.
 * @see mapParameterToParameter()
 */
int rdControlSet::
mapParameterToControl(int aIndex) const
{
	if(aIndex<0) return(-1);
	if(aIndex>_ptcMap.getSize()) return(-1);
	return(_ptcMap[aIndex]);
}
//_____________________________________________________________________________
/**
 * Map a control-set parameter to a parameter of a particular control.
 *
 * In the control set, the paramters for each of the controls are
 * concatenated into an array.  Since there is not a one-to-one
 * correspondence between control-set parameters and controls (i.e., a
 * particular control may have many parameters), it is necessary
 * both to map to which control each control-set parameter belongs and
 * to map to which parameter within a particular control a control-set
 * parameter corresponds.
 *
 * @param aIndex Index of the parameter in the control set.
 * @return Index of the parameter with in a particular to which the specified
 * parameter corresponds.  If no such parameter exists, -1 is returned.
 * @see mapParameterToControl()
 */
int rdControlSet::
mapParameterToParameter(int aIndex) const
{
	if(aIndex<0) return(-1);
	if(aIndex>_ptcMap.getSize()) return(-1);
	return(_ptcMap[aIndex]);
}
//_____________________________________________________________________________
/**
 * Generate the maps relating a parmeter in the control set to a control
 * and a parameter of a control.
 *
 * This method should be called any time there is a change in the number or
 * types of controls held in the control set.
 */
void rdControlSet::
generateParameterMaps()
{
	_ptcMap.setSize(0);
	_ptpMap.setSize(0);

	int i,j;
	int size = getSize(false);
	rdControl *control;
	for(i=0;i<size;i++) {

		control = get(i);
		if(control==NULL) continue;

		for(j=0;j<control->getNumParameters();j++) {
			_ptcMap.append(i);
			_ptpMap.append(j);
		}
	}
}
