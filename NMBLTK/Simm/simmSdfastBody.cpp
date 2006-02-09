// simmSdfastBody.cpp
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
#include "simmSdfastBody.h"

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
simmSdfastBody::simmSdfastBody(void) :
	_simmBody(NULL)
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aSdfastBody simmSdfastBody to be copied.
 */
simmSdfastBody::simmSdfastBody(const simmSdfastBody &aSdfastBody) :
	_simmBody(NULL)
{
	copyData(aSdfastBody);
}

void simmSdfastBody::copyData(const simmSdfastBody &aSdfastBody)
{
	_name = aSdfastBody._name;
	_mass = aSdfastBody._mass;
	_simmBody = aSdfastBody._simmBody;

	for (int i = 0; i < 3; i++)
	{
		_massCenter[i] = aSdfastBody._massCenter[i];
		_bodyToJoint[i] = aSdfastBody._bodyToJoint[i];
		_inboardToJoint[i] = aSdfastBody._inboardToJoint[i];
		for (int j = 0; j < 3; j++)
			_inertia[i][j] = aSdfastBody._inertia[i][j];
	}
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmSdfastBody::~simmSdfastBody(void)
{
	_name.clear();
}

simmSdfastBody* simmSdfastBody::copy(void) const
{
	simmSdfastBody *sdfastBody = new simmSdfastBody(*this);
	return sdfastBody;
}

simmSdfastBody& simmSdfastBody::operator=(const simmSdfastBody &aSdfastBody)
{
	copyData(aSdfastBody);

	return *this;
}
