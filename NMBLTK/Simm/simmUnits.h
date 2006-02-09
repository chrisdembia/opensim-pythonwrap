#ifndef __simmUnits_h__
#define __simmUnits_h__

// simmUnits.h
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
#include <iostream>
#include <string>
#include <fstream>

//=============================================================================
//=============================================================================
/**
 * A class implementing various units for measuring quantities.
 *
 * @author Peter Loan
 * @version 1.0
 */
class simmUnits
{

public:
	enum UnitType
	{
		simmUnknownUnits = 0,
		simmRadians,
		simmDegrees,
		simmMillimeters,
		simmCentimeters,
		simmMeters,
		simmSeconds,
		simmMilliseconds,
		simmNewtons
	};

//=============================================================================
// DATA
//=============================================================================
private:
	UnitType _type;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	simmUnits();
	simmUnits(const simmUnits& aUnits);
	simmUnits(std::string& str);
	simmUnits(UnitType aType);
	virtual ~simmUnits();
	double convertTo(UnitType aType, double aValue) const;
	double convertTo(UnitType aType) const;
	double convertTo(const simmUnits& aUnit) const;
	UnitType getType() const { return _type; }
	const char* getLabel() const;

	void peteTest() const;

//=============================================================================
};	// END of class simmUnits
//=============================================================================
//=============================================================================

#endif // __simmUnits_h__


