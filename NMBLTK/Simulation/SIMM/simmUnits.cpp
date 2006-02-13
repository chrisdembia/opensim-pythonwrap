// simmUnits.cpp
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
#include "simmUnits.h"
#include <NMBLTK/Tools/rdMath.h>

//=============================================================================
// STATICS
//=============================================================================
using namespace std;

simmUnits::simmUnits() :
	_type(simmUnknownUnits)
{
}

simmUnits::simmUnits(const simmUnits& aUnits)
{
	_type = aUnits._type;
}

simmUnits::simmUnits(string& str) :
	_type(simmUnknownUnits)
{
   if (str == "RADIANS" || str == "RAD" || str == "radians" || str == "rad")
      _type = simmRadians;
   if (str == "DEGREES" || str == "DEG" || str == "degrees" || str == "deg")
      _type = simmDegrees;
   if (str == "MM" || str == "MILLIMETERS" || str == "mm" || str == "millimeters")
      _type = simmMillimeters;
   if (str == "CM" || str == "CENTIMETERS" || str == "cm" || str == "centimeters")
      _type = simmCentimeters;
   if (str == "M" || str == "METERS" || str == "m" || str == "meters")
      _type = simmMeters;
   if (str == "SEC" || str == "SECONDS" || str == "sec" || str == "seconds")
      _type = simmSeconds;
   if (str == "MSEC" || str == "MILLISECONDS" || str == "msec" || str == "milliseconds")
      _type = simmMilliseconds;
	if (str == "N" || str == "NEWTONS" || str == "Newtons")
		_type = simmNewtons;
}

simmUnits::simmUnits(UnitType aType)
{
	_type = aType;
}

simmUnits::~simmUnits()
{
}

/* Returns a factor for converting a number from
 * the units of 'this' to the units of aType.
 */
double simmUnits::convertTo(const simmUnits& aUnit) const
{
	return convertTo(aUnit._type);
}

/* Converts a number from the units of 'this' to the
 * units of aType.
 */
double simmUnits::convertTo(UnitType aType, double aValue) const
{
	return aValue * convertTo(aType);
}

/* Returns a factor for converting a number from
 * the units of 'this' to the units of aType.
 */
double simmUnits::convertTo(UnitType aType) const
{
	if (_type == aType)
		return 1.0;

	if (_type == simmRadians)
	{
		if (aType == simmDegrees)
			return rdMath::RTD;
		else
			return rdMath::NAN;
	}
	else if (_type == simmDegrees)
	{
		if (aType == simmRadians)
			return rdMath::DTR;
		else
			return rdMath::NAN;
	}
	else if (_type == simmMillimeters)
	{
		if (aType == simmCentimeters)
			return 0.1;
		else if (aType == simmMeters)
			return 0.001;
		else
			return rdMath::NAN;
	}
	else if (_type == simmCentimeters)
	{
		if (aType == simmMillimeters)
			return 10.0;
		else if (aType == simmMeters)
			return 0.01;
		else
			return rdMath::NAN;
	}
	else if (_type == simmMeters)
	{
		if (aType == simmMillimeters)
			return 1000.0;
		else if (aType == simmCentimeters)
			return 100.0;
		else
			return rdMath::NAN;
	}
	else if (_type == simmSeconds)
	{
		if (aType == simmMilliseconds)
			return 1000.0;
		else
			return rdMath::NAN;
	}
	else if (_type == simmMilliseconds)
	{
		if (aType == simmSeconds)
			return 0.001;
		else
			return rdMath::NAN;
	}

	return rdMath::NAN;
}

const char* simmUnits::getLabel() const
{
	switch(_type)
	{
	   case simmRadians:
		   return "radians";
	   case simmDegrees:
		   return "radians";
	   case simmMillimeters:
		   return "millimeters";
	   case simmCentimeters:
		   return "centimeters";
	   case simmMeters:
		   return "meters";
		case simmSeconds:
			return "seconds";
		case simmMilliseconds:
			return "milliseconds";
		case simmNewtons:
			return "N";
		case simmUnknownUnits:
		default:
			return "unknown";
	}
}

void simmUnits::peteTest() const
{
	cout << "   simmUnits: " << getLabel() << endl;
}

