#ifndef __simmBody_h__
#define __simmBody_h__

// simmBody.h
// Author: Peter Loan
/* Copyright (c) 2005, Stanford University and Peter Loan.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


// INCLUDE
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <math.h>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdSet.h>
#include <NMBLTK/Tools/rdVisibleObject.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyDblArray.h>
#include <NMBLTK/Tools/rdPropertyObjArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include "simmMarker.h"

class simmKinematicsEngine;

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM body segment. simmBodies can contain bones,
 * as well as mass properties.
 *
 * @author Peter Loan
 * @version 1.0
 */
class simmBody : public rdObject  
{

//=============================================================================
// DATA
//=============================================================================
public:
	typedef struct
	{
		bool used;
		int timesSplit;
		double massFactor;
		bool skippable;
	} sdfastBodyInfo;

	sdfastBodyInfo _sdfastInfo;

protected:
	rdPropertyDbl _massProp;
	double &_mass;

	rdPropertyDblArray _massCenterProp;
	rdArray<double> &_massCenter;

	rdPropertyDblArray _inertiaProp;
	rdArray<double> &_inertia;

	rdPropertyObjArray _bonesProp;
	rdArrayPtrs<rdVisibleObject> &_bones;

	rdPropertyObjArray _markersProp;
	rdArrayPtrs<simmMarker> &_markers;

	/* For holding cumulative scale factors, which are needed if
	 * a SIMM joint file is written (so SIMM knows how much to
	 * scale the bones.
	 */
	double _scaleFactor[3];

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmBody();
	simmBody(DOMElement *aElement);
	simmBody(const simmBody &aBody);
	virtual ~simmBody();
	virtual rdObject* copy() const;
	virtual rdObject* copy(DOMElement *aElement) const;

	simmBody& operator=(const simmBody &aBody);
   void simmBody::copyData(const simmBody &aBody);

   void setup(simmKinematicsEngine* aEngine);

	double getMass() { return _mass; }
	void getMassCenter(double vec[3]) { vec[0] = _massCenter[0]; vec[1] = _massCenter[1]; vec[2] = _massCenter[2]; }
	const rdArray<double>& getInertia() { return _inertia; }
	rdArrayPtrs<rdVisibleObject>& getBones() const { return _bones; }
	int getNumMarkers() { return _markers.getSize(); }
	simmMarker* getMarker(int index) const;
	int deleteAllMarkers();
	void deleteMarker(const simmMarker* aMarker);
	int deleteUnusedMarkers(const rdArray<std::string>& aMarkerNames);
	void scale(rdArray<double>& aScaleFactors);

	void addMarker(simmMarker* aMarker);
	void writeSIMM(std::ofstream& out) const;
	void writeMarkers(std::ofstream& out) const;

	void peteTest() const;

protected:

private:
	void setNull();
	void setupProperties();
	void scaleInertialProperties(rdArray<double>& aScaleFactors);
//=============================================================================
};	// END of class simmBody
//=============================================================================
//=============================================================================

typedef RDSIMULATION_API rdArrayPtrs<simmBody> simmBodyArray;

#endif // __simmBody_h__


