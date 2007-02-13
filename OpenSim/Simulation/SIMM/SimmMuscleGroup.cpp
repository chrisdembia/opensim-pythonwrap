// SimmMuscleGroup.cpp
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

//=============================================================================
// INCLUDES
//=============================================================================
#include "SimmMuscleGroup.h"
#include "AbstractActuator.h"
#include "AbstractModel.h"

//=============================================================================
// STATICS
//=============================================================================
using namespace std;
using namespace OpenSim;

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Default constructor.
 */
SimmMuscleGroup::SimmMuscleGroup() :
	_muscles(NULL)
{
	setNull();

}

//_____________________________________________________________________________
/**
 * Destructor.
 */
SimmMuscleGroup::~SimmMuscleGroup()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aGroup Group to be copied.
 */
SimmMuscleGroup::SimmMuscleGroup(const SimmMuscleGroup &aGroup) :
   Object(aGroup),
	_muscles(NULL)
{
	copyData(aGroup);
}

//_____________________________________________________________________________
/**
 * Copy this muscle group and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this group.
 */
Object* SimmMuscleGroup::copy() const
{
	SimmMuscleGroup *grp = new SimmMuscleGroup(*this);
	return(grp);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Copy data members from one SimmMuscleGroup to another.
 *
 * @param aGroup SimmMuscleGroup to be copied.
 */
void SimmMuscleGroup::copyData(const SimmMuscleGroup &aGroup)
{
	_muscles = aGroup._muscles;
}

//_____________________________________________________________________________
/**
 * Set the data members of this SimmMuscleGroup to their null values.
 */
void SimmMuscleGroup::setNull()
{
	setType("SimmMuscleGroup");
}

//_____________________________________________________________________________
/**
 * Perform some set up functions that happen after the
 * object has been deserialized or copied.
 *
 * @param aModel model containing this SimmMuscleGroup.
 */
void SimmMuscleGroup::setup(AbstractModel* aModel)
{
	_muscles.setSize(0);

	const ActuatorSet* actSet = aModel->getActuatorSet();

	int i, j;
	for (i = 0; i < actSet->getSize(); i++)
	{
		const Array<string>* groupNames = actSet->get(i)->getGroupNames();
		if (groupNames)
		{
			for (j = 0; j < groupNames->getSize(); j++)
			{
				if ((*groupNames)[j] == getName())
					_muscles.append(actSet->get(i));
			}
		}
	}
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
SimmMuscleGroup& SimmMuscleGroup::operator=(const SimmMuscleGroup &aGroup)
{
	// BASE CLASS
	Object::operator=(aGroup);

	copyData(aGroup);

	return(*this);
}

//_____________________________________________________________________________
/**
 * Check if the group contains a muscle with a certain name.
 *
 * @param aName the name of the muscle.
 * @return Boolean indicating whether or not the group contains the muscle.
 */
bool SimmMuscleGroup::contains(const string& aName) const
{
	for (int i = 0; i < _muscles.getSize(); i++)
		if (_muscles[i]->getName() == aName)
			return true;

	return false;
}

void SimmMuscleGroup::peteTest() const
{
	cout << "Muscle Group: " << getName() << endl;
	cout << "   muscles: ";
	for (int i = 0; i < _muscles.getSize(); i++)
		cout << _muscles[i]->getName() << " ";
	cout << endl;
}

