// simmPath.cpp
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


//=============================================================================
// INCLUDES
//=============================================================================
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include "simmPath.h"
#include "simmBody.h"
#include "simmJoint.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace std;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
simmPath::simmPath() :
   _from(NULL),
	_to(NULL),
	_transformsValid(false)
{
}

simmPath::simmPath(JointPath aPath, const simmBody* aFromBody, const simmBody* aToBody) :
   _path(aPath),
   _from(aFromBody),
	_to(aToBody),
	_transformsValid(false)
{
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmPath::~simmPath()
{
}

rdTransform& simmPath::getForwardTransform()
{
	if (!_transformsValid)
		calcTransforms();

	return _forwardTransform;
}

rdTransform& simmPath::getInverseTransform()
{
	if (!_transformsValid)
		calcTransforms();

	return _inverseTransform;
}

void simmPath::calcTransforms()
{
	if (_path.size() >= 1)
	{
		/* Get the transform for the first joint in the path. Copying it right into
		 * _forwardTransform saves the step of multiplying it by the identity matrix
		 * as the first iteration in the 'for' loop that follows.
		 */
		_forwardTransform = _path[0].getJointTransform();

		/* Now get the remaining joint transforms and append them onto the current stack,
		 * stored in _forwardTransform.
		 */
		for (unsigned int i = 1; i < _path.size(); i++)
		{
			rdMtx::Multiply(4, 4, 4, _path[i].getJointTransform().getMatrix(),
				_forwardTransform.getMatrix(), _forwardTransform.getMatrix());
		}

		/* Invert the forward transform to get the inverse. */
		rdMtx::Invert(4, _forwardTransform.getMatrix(), _inverseTransform.getMatrix());
	}

   _transformsValid = true;
}

void simmPath::peteTest() const
{
	cout << "simmPath from " << _from->getName() << " to " << _to->getName() << ": ";
	for (unsigned int i = 0; i < _path.size(); i++)
		cout << (_path[i].getDirection() == simmStep::forward ? "+" : "-") << _path[i].getJoint()->getName() << (i < _path.size() - 1 ? " -> " : "");
	cout << endl;
}
