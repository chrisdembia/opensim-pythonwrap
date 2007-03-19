// IKTrialSet.cpp
// Author: Peter Loan
/*
 * Copyright (c) 2006, Stanford University. All rights reserved. 
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

#include "IKTrialSet.h"

using namespace std;
using namespace OpenSim;

//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
IKTrialSet::~IKTrialSet(void)
{
}

//_____________________________________________________________________________
/**
 * Default constructor of a IKTrialSet.
 */
IKTrialSet::IKTrialSet() :
	Set<IKTrial>()
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Copy constructor of a IKTrialSet.
 */
IKTrialSet::IKTrialSet(const IKTrialSet& aSimmIKTrialSet):
	Set<IKTrial>(aSimmIKTrialSet)
{
	setNull();
	*this = aSimmIKTrialSet;
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
/**
 * Set the data members of this IKTrialSet to their null values.
 */
void IKTrialSet::setNull()
{
	setType("IKTrialSet");
}

//=============================================================================
// OPERATORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Assignment operator.
 *
 * @return Reference to this object.
 */
#ifndef SWIG
IKTrialSet& IKTrialSet::operator=(const IKTrialSet &aSimmIKTrialSet)
{
	Set<IKTrial>::operator=(aSimmIKTrialSet);
	return (*this);
}
#endif
