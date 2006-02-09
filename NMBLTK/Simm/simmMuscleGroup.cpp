// simmMuscleGroup.cpp
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
#include "simmMuscleGroup.h"
#include "simmMuscle.h"
#include "simmModel.h"

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
simmMuscleGroup::simmMuscleGroup() :
	_muscles(NULL)
{
	setNull();

}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMuscleGroup::simmMuscleGroup(DOMElement *aElement) :
   rdObject(aElement),
	_muscles(NULL)
{
	setNull();
	//updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMuscleGroup::~simmMuscleGroup()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aGroup Group to be copied.
 */
simmMuscleGroup::simmMuscleGroup(const simmMuscleGroup &aGroup) :
   rdObject(aGroup),
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
rdObject* simmMuscleGroup::copy() const
{
	simmMuscleGroup *grp = new simmMuscleGroup(*this);
	return(grp);
}
//_____________________________________________________________________________
/**
 * Copy this simmMuscleGroup and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMuscleGroup::simmMuscleGroup(DOMElement*) in order to establish the
 * relationship of the simmMuscleGroup object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMuscleGroup object. Finally, the data members of the
 * copy are updated using simmMuscleGroup::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMuscleGroup.
 */
rdObject* simmMuscleGroup::copy(DOMElement *aElement) const
{
	simmMuscleGroup *grp = new simmMuscleGroup(aElement);
	*grp = *this;
	//grp->updateFromXMLNode();
	return(grp);
}

void simmMuscleGroup::copyData(const simmMuscleGroup &aGroup)
{
	_muscles = aGroup._muscles;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMuscleGroup to their null values.
 */
void simmMuscleGroup::setNull()
{
	setType("muscleGroup");
}

simmMuscleGroup& simmMuscleGroup::operator=(const simmMuscleGroup &aGroup)
{
	// BASE CLASS
	rdObject::operator=(aGroup);

	copyData(aGroup);

	return(*this);
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmMuscleGroup::setup(simmModel* aModel)
{
	_muscles.setSize(0);

	simmMuscle* sm;
	for (int i = 0; i < aModel->getNumberOfMuscles(); i++)
	{
		if (sm = dynamic_cast<simmMuscle*>(aModel->getMuscle(i)))
		{
			const rdArray<string>& groupNames = sm->getGroupNames();
			for (int j = 0; j < groupNames.getSize(); j++)
			{
				if (groupNames[j] == getName())
					_muscles.append(sm);
			}
		}
	}
}

bool simmMuscleGroup::contains(const std::string& aName) const
{
	for (int i = 0; i < _muscles.getSize(); i++)
		if (_muscles[i]->getName() == aName)
			return true;

	return false;
}

void simmMuscleGroup::peteTest() const
{
	cout << "Muscle Group: " << getName() << endl;
	cout << "   muscles: ";
	for (int i = 0; i < _muscles.getSize(); i++)
		cout << _muscles[i]->getName() << " ";
	cout << endl;
}

