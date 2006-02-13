// simmPoint.cpp
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
#include "simmMacros.h"
#include "simmPoint.h"

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
simmPoint::simmPoint()
{
}

simmPoint::simmPoint(double coords[3])
{
	for (int i = 0; i < 3; i++)
		_location[i] = coords[i];
}

simmPoint::simmPoint(const simmPoint& aPoint) :
   rdObject(aPoint)
{
	for (int i = 0; i < 3; i++)
		_location[i] = aPoint._location[i];
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmPoint::~simmPoint()
{
}

//_____________________________________________________________________________
/**
 * Copy this simmPoint and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmPoint.
 */
rdObject* simmPoint::copy() const
{
	simmPoint *point = new simmPoint(*this);
	return(point);
}

simmPoint& simmPoint::operator=(const simmPoint &aPoint)
{
	// BASE CLASS
	rdObject::operator=(aPoint);

	for (int i = 0; i < 3; i++)
		_location[i] = aPoint._location[i];

	return(*this);
}

simmPoint& simmPoint::operator+=(const simmPoint &aPoint)
{
	for (int i = 0; i < 3; i++)
		_location[i] += aPoint._location[i];

	return(*this);
}

simmPoint& simmPoint::operator/=(double factor)
{
	for (int i = 0; i < 3; i++)
		_location[i] /= factor;

	return(*this);
}

void simmPoint::set(double x, double y, double z)
{
	_location[0] = x;
	_location[1] = y;
	_location[2] = z;
}

/* The point is considered not visible (valid) if any
 * coordinate is NAN.
 */
bool simmPoint::isVisible() const
{
	if (EQUAL_WITHIN_ERROR(_location[0], rdMath::NAN) ||
		 EQUAL_WITHIN_ERROR(_location[1], rdMath::NAN) ||
		 EQUAL_WITHIN_ERROR(_location[2], rdMath::NAN))
	{
		return false;
	}

	return true;
}

void simmPoint::peteTest() const
{
	cout << "      simmPoint: " << _location[0] << ", " << _location[1] << ", " << _location[2] << endl;
}
