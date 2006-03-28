#ifndef __simmPath_h__
#define __simmPath_h__

// simmPath.h
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
#include <iostream>
#include <math.h>
#include <vector>
#include <NMBLTK/Simulation/rdSimulationDLL.h>
#include <NMBLTK/Tools/rdTransform.h>
#include <NMBLTK/Tools/rdStorage.h>
#include "simmStep.h"

class simmBody;

typedef std::vector<simmStep> JointPath;

//=============================================================================
//=============================================================================
/**
 * A class implementing a path of SIMM joints, representing the transform[s]
 * between one SIMM body and another.
 *
 * @author Peter Loan
 * @version 1.0
 */
class RDSIMULATION_API simmPath
{

//=============================================================================
// DATA
//=============================================================================
private:
	JointPath _path;
	const simmBody* _from;
	const simmBody* _to;
	rdTransform _forwardTransform;
	rdTransform _inverseTransform;
	bool _transformsValid;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmPath();
	simmPath(JointPath aPath, const simmBody* aFromBody, const simmBody* aToBody);
	virtual ~simmPath();

	void invalidate() { _transformsValid = false; }
	const simmBody* getFromBody() { return _from; }
	const simmBody* getToBody() { return _to; }
	const JointPath& getPath() const { return _path; }
	rdTransform& getForwardTransform();
	rdTransform& getInverseTransform();

	void peteTest() const;

private:
	void calcTransforms();

//=============================================================================
};	// END of class simmPath
//=============================================================================
//=============================================================================

#endif // __simmPath_h__


