// rdControlSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2003-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fc.anderson@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdControlSet_h__
#define __rdControlSet_h__


// INCLUDES
#include <NMBLTK/Simulation/Model/rdModel.h>
#include "rdControl.h"
#include <NMBLTK/Tools/rdSet.h>


// EXPORT LINE FOR MICROSOFT VISUAL C++
#ifndef SWIG
#ifndef UNIX
//template class RDTOOLS_API rdArray<int>;
#endif
#endif

template class RDSIMULATION_API rdSet<rdControl>;


//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of controls for a dynamic
 * simulation.
 *
 * @author Frank C. Anderson
 * @version 1.0
 */
class RDSIMULATION_API rdControlSet : public rdSet<rdControl>
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Map from parameters to controls. */
	rdArray<int> _ptcMap;
	/** Map from set parameters to control parameters. */
	rdArray<int> _ptpMap;


//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	rdControlSet();
	rdControlSet(const std::string &aFileName);
	rdControlSet(const rdControlSet &aSet);
	virtual ~rdControlSet();
private:
	void setNull();
	void setupProperties();
	

	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
public:
#ifndef SWIG
	rdControlSet& operator=(const rdControlSet &aSet);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// SIZE
	int getSize(bool aForModelControls=true) const;
	// CONTROL LIST
	//int getControlIndex(const char *aName) const;
	void getControlList(const char *aType,rdArray<int> &rList,
		bool aForModelControls=true) const;
	// CONTROL VALUES
	void getControlValues(double aT,double rX[],
			bool aForModelControls=true) const;
	void getControlValues(double aT,rdArray<double> &rX,
			bool aForModelControls=true) const;
	void setControlValues(double aT,const double aX[],
			bool aForModelControls=true);
	void setControlValues(double aT,const rdArray<double> &aX,
			bool aForModelControls=true);
	// PARAMETERS
	int getNumParameters(bool aForModelControls=true) const;
	void getParameterList(rdArray<int> &rList,
			bool aForModelControls=true) const;
	void getParameterList(double aT,rdArray<int> &rList,
			bool aForModelControls=true) const;
	void getParameterList(double aTLower,double aTUpper,rdArray<int> &rList,
			bool aForModelControls=true) const;
	void getParameterMins(rdArray<double> &rMins,
			const rdArray<int> *aList=NULL) const;
	void getParameterMaxs(rdArray<double> &rMaxs,
			const rdArray<int> *aList=NULL) const;
	void getParameterValues(double rP[],
			const rdArray<int> *aList=NULL) const;
	void getParameterValues(rdArray<double> &rP,
			const rdArray<int> *aList=NULL) const;
	void setParameterValues(const double aP[],
			const rdArray<int> *aList=NULL);
	void setParameterValues(const rdArray<double> &aP,
			const rdArray<int> *aList=NULL);

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void simplify(const rdPropertySet &aProperties);
	rdStorage*
		constructStorage(int aN,double aT1,double aT2,bool aForModelControls);
	int mapParameterToControl(int aIndex) const;
	int mapParameterToParameter(int aIndex) const;
	void generateParameterMaps();

//=============================================================================
};	// END of class rdControlSet
//=============================================================================
//=============================================================================


#endif // __rdControlSet_h__


