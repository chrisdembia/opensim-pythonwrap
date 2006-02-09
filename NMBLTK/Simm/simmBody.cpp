// simmBody.cpp
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
#include "simmBody.h"
#include "simmBone.h"
#include "simmKinematicsEngine.h"
#include "simmMacros.h"

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
simmBody::simmBody() :
   _mass(_massProp.getValueDbl()),
   _massCenter(_massCenterProp.getValueDblArray()),
   _inertia(_inertiaProp.getValueDblArray()),
   _bones((rdArrayPtrs<rdVisibleObject>&)_bonesProp.getValueObjArray()),
	_markers((rdArrayPtrs<simmMarker>&)_markersProp.getValueObjArray())
{
	setNull();
}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmBody::simmBody(DOMElement *aElement) :
   rdObject(aElement),
   _mass(_massProp.getValueDbl()),
   _massCenter(_massCenterProp.getValueDblArray()),
   _inertia(_inertiaProp.getValueDblArray()),
   _bones((rdArrayPtrs<rdVisibleObject>&)_bonesProp.getValueObjArray()),
	_markers((rdArrayPtrs<simmMarker>&)_markersProp.getValueObjArray())
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmBody::~simmBody()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aBody simmBody to be copied.
 */
simmBody::simmBody(const simmBody &aBody) :
   rdObject(aBody),
   _mass(_massProp.getValueDbl()),
   _massCenter(_massCenterProp.getValueDblArray()),
   _inertia(_inertiaProp.getValueDblArray()),
   _bones((rdArrayPtrs<rdVisibleObject>&)_bonesProp.getValueObjArray()),
	_markers((rdArrayPtrs<simmMarker>&)_markersProp.getValueObjArray())
{
	setupProperties();
	copyData(aBody);
}
//_____________________________________________________________________________
/**
 * Copy this body and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmBody.
 */
rdObject* simmBody::copy() const
{
	simmBody *body = new simmBody(*this);
	return(body);
}
//_____________________________________________________________________________
/**
 * Copy this simmBody and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmBody::simmBody(DOMElement*) in order to establish the
 * relationship of the simmBody object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmBody object. Finally, the data members of the copy are
 * updated using simmBody::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmBody.
 */
rdObject* simmBody::copy(DOMElement *aElement) const
{
	simmBody *body = new simmBody(aElement);
	*body = *this;
	body->updateFromXMLNode();
	return(body);
}

void simmBody::copyData(const simmBody &aBody)
{
	_mass = aBody._mass;
	_massCenter = aBody._massCenter;
	_inertia = aBody._inertia;
	_bones = aBody._bones;
	_markers = aBody._markers;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmBody to their null values.
 */
void simmBody::setNull()
{
	setupProperties();
	setType("body");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmBody::setupProperties()
{
	_massProp.setName("mass");
	_massProp.setValue(5.5);
	_propertySet.append(&_massProp);

	const double defaultMC[] = {1.1, 2.2, 3.3};
	_massCenterProp.setName("massCenter");
	_massCenterProp.setValue(3, defaultMC);
	_propertySet.append(&_massCenterProp);

	const double defaultInertia[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
	_inertiaProp.setName("inertia");
	_inertiaProp.setValue(9, defaultInertia);
	_propertySet.append(&_inertiaProp);

	_bonesProp.setName("Bones");
	rdArrayPtrs<rdObject> bones;
	_bonesProp.setValue(bones);
	_propertySet.append(&_bonesProp);

	_markersProp.setName("Markers");
	rdArrayPtrs<rdObject> markers;
	_markersProp.setValue(markers);
	_propertySet.append(&_markersProp);
}

simmBody& simmBody::operator=(const simmBody &aBody)
{
	// BASE CLASS
	rdObject::operator=(aBody);

	copyData(aBody);

	return(*this);
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmBody::setup(simmKinematicsEngine* aEngine)
{
	simmBone* sb;

	/* The _bones array can contain any rdVisibleObject.
	 * Check for ones of type simmBone and call the
	 * setup function for them (to read in the VTK
	 * files, etc.).
	 */
	for (int i = 0; i < _bones.getSize(); i++)
	{
		if (sb = dynamic_cast<simmBone*>(_bones[i]))
			sb->setup(aEngine);
	}

	for (int i = 0; i < 3; i++)
		_scaleFactor[i] = 1.0;
}

void simmBody::addMarker(simmMarker* aMarker)
{
	// newMarker will be deleted when the _markers array
	// is deleted because _memoryOwner is set to true.
	simmMarker* newMarker = new simmMarker(*aMarker);
	_markers.append(newMarker);
}

simmMarker* simmBody::getMarker(int index) const
{
	if (index >= 0 && index < _markers.getSize())
		return _markers[index];

	return NULL;
}

int simmBody::deleteAllMarkers()
{
	int numDeleted = _markers.getSize();

	_markers.clearAndDestroy();

	return numDeleted;
}

void simmBody::deleteMarker(const simmMarker* aMarker)
{
	_markers.remove(aMarker);
}

/* Remove all markers from the body that are not in the passed-in list. */
int simmBody::deleteUnusedMarkers(const rdArrayPtrs<string>& aMarkerNames)
{
	for (int i = 0, numDeleted = 0; i < _markers.getSize(); i++)
	{
		for (int j = 0; j < aMarkerNames.getSize(); j++)
		{
			if (*aMarkerNames[j] == _markers[i]->getName())
				break;
		}
		if (j == aMarkerNames.getSize())
		{
			_markers.remove(i);
			numDeleted++;
			i--; // decrement i so the next marker will not be skipped
		}
	}

	return numDeleted;
}

void simmBody::scale(rdArray<double>& aScaleFactors)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		_massCenter[i] *= aScaleFactors[i];
		_scaleFactor[i] *= aScaleFactors[i];
	}

	scaleInertialProperties(aScaleFactors);

	simmBone* sb;
	for (i = 0; i < _bones.getSize(); i++)
	{
		if (sb = dynamic_cast<simmBone*>(_bones[i]))
			sb->scale(aScaleFactors);
	}

	for (i = 0; i < _markers.getSize(); i++)
		_markers[i]->scale(aScaleFactors);
}

void simmBody::scaleInertialProperties(rdArray<double>& aScaleFactors)
{
	int i;

	/* If the mass is zero, then make the inertia tensor zero as well.
	 * If the X, Y, Z scale factors are equal, then you can scale the
	 * inertia tensor exactly by the square of the scale factor, since
	 * each element in the tensor is proportional to the square of one
	 * or more dimensional measurements. For determining if the scale
	 * factors are equal, ignore reflections-- look only at the
	 * absolute value of the factors.
	 */
	if (_mass <= ROUNDOFF_ERROR)
	{
		for (i = 0; i < 9; i++)
			_inertia[i] = 0.0;
	}
	else if (EQUAL_WITHIN_ERROR(DABS(aScaleFactors[0]), DABS(aScaleFactors[1])) &&
		      EQUAL_WITHIN_ERROR(DABS(aScaleFactors[1]), DABS(aScaleFactors[2])))
	{
		_mass *= DABS((aScaleFactors[0] * aScaleFactors[1] * aScaleFactors[2]));

		for (i = 0; i < 9; i++)
			_inertia[i] *= (aScaleFactors[0] * aScaleFactors[0]);
	}
	else
	{
		/* If the scale factors are not equal, then assume that the segment
		 * is a cylinder and the inertia is calculated about one end of it.
		 */
		int axis;

		/* 1. Find the smallest diagonal component. This dimension is the axis
		 *    of the cylinder.
		 */
		if (_inertia[0] <= _inertia[4])
		{
			if (_inertia[0] <= _inertia[8])
				axis = 0;
			else
				axis = 2;
		}
		else if (_inertia[4] <= _inertia[8])
		{
			axis = 1;
		}
		else
		{
			axis = 2;
		}

		/* 2. The smallest inertial component is equal to 0.5 * mass * radius * radius,
		 *    so you can rearrange and solve for the radius.
		 */
		int oa;
		double radius, rad_sqr, length;
		double term = 2.0 * _inertia[axis * 3 + axis] / _mass;
		if (term < 0.0)
			radius = 0.0;
		else
			radius = sqrt(term);

		/* 3. Choose either of the other diagonal components and use it to solve for the
		*    length of the cylinder. This component is equal to:
		*    0.333 * mass * length * length  +  0.25 * mass * radius * radius
		*/
		if (axis == 0)
			oa = 1;
		else
			oa = 0;
		term = 3.0 * (_inertia[oa * 3 + oa] - 0.25 * _mass * radius * radius) / _mass;
		if (term < 0.0)
			length = 0.0;
		else
			length = sqrt(term);

		/* 4. Scale the mass, radius, and length, and recalculate the diagonal inertial terms. */
		_mass *= DABS((aScaleFactors[0] * aScaleFactors[1] * aScaleFactors[2]));
		length *= DABS(aScaleFactors[axis]);

		if (axis == 0)
		{
			rad_sqr = radius * DABS(aScaleFactors[1]) * radius * DABS(aScaleFactors[2]);
			_inertia[0] = 0.5 * _mass * rad_sqr;
			_inertia[4] = _mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			_inertia[8] = _mass * ((length * length / 3.0) + 0.25 * rad_sqr);
		}
		else if (axis == 1)
		{
			rad_sqr = radius * DABS(aScaleFactors[0]) * radius * DABS(aScaleFactors[2]);
			_inertia[0] = _mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			_inertia[4] = 0.5 * _mass * rad_sqr;
			_inertia[8] = _mass * ((length * length / 3.0) + 0.25 * rad_sqr);
		}
		else
		{
			rad_sqr = radius * DABS(aScaleFactors[0]) * radius * DABS(aScaleFactors[1]);
			_inertia[0] = _mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			_inertia[4] = _mass * ((length * length / 3.0) + 0.25 * rad_sqr);
			_inertia[8] = 0.5 * _mass * rad_sqr;
		}

		/* 5. Scale the cross terms, in case some are non-zero. */
		_inertia[1] *= DABS((aScaleFactors[0] * aScaleFactors[1]));
		_inertia[2] *= DABS((aScaleFactors[0] * aScaleFactors[2]));
		_inertia[3] *= DABS((aScaleFactors[1] * aScaleFactors[0]));
		_inertia[5] *= DABS((aScaleFactors[1] * aScaleFactors[2]));
		_inertia[6] *= DABS((aScaleFactors[2] * aScaleFactors[0]));
		_inertia[7] *= DABS((aScaleFactors[2] * aScaleFactors[1]));
	}
}

void simmBody::writeSIMM(ofstream& out) const
{
	int i;
	simmBone* sb;

	out << "beginsegment " << getName() << endl;
	out << "mass " << _mass << endl;
	out << "masscenter " << _massCenter[0] << " " << _massCenter[1] << " " << _massCenter[2] << endl;
	out << "inertia " << _inertia[0] << " " << _inertia[1] << " " << _inertia[2] << endl;
	out << "        " << _inertia[3] << " " << _inertia[4] << " " << _inertia[5] << endl;
	out << "        " << _inertia[6] << " " << _inertia[7] << " " << _inertia[8] << endl;
	for (i = 0; i < _bones.getSize(); i++)
	{
		if (sb = dynamic_cast<simmBone*>(_bones[i]))
			sb->writeSIMM(out);
	}
	for (i = 0; i < _markers.getSize(); i++)
		_markers[i]->writeSIMM(out);

	out << "scale " << _scaleFactor[0] << " " << _scaleFactor[1] << " " << _scaleFactor[2] << endl;
	out << "endsegment" << endl << endl;
}

void simmBody::writeMarkers(ofstream& out) const
{
	/* The code to write a marker to a file could be
	 * turned into a simmMarker method, but what gets
	 * written to the file is not a standard marker
	 * node, but rather one that can be pasted into
	 * a MarkerSet node in a simmSubject definition.
	 * The bodyName field is needed for this, and
	 * bodyName is not used by every marker in the model.
	 */
	for (int i = 0; i < _markers.getSize(); i++)
	{
		const double* pos = _markers[i]->getOffset();

		out << "   <marker name=\"" << _markers[i]->getName() << "\">" << endl;
		out << "      <body>" << getName() << "</body>" << endl;
		out << "      <location>" << pos[0] << " " << pos[1] << " " << pos[2] << "</location>" << endl;
		out << "      <weight>" << _markers[i]->getWeight() << "</weight>" << endl;
		out << "      <fixed>" << ((_markers[i]->getFixed()) ? ("true") : ("false")) << "</fixed>" << endl;
		out << "   </marker>" << endl;
	}
}

void simmBody::peteTest() const
{
	int i;
	simmBone* sb;

	cout << "Body: " << getName() << endl;
	cout << "   mass: " << _mass << endl;
	cout << "   massCenter: " << _massCenter << endl;
	cout << "   inertia: " << _inertia << endl;
	for (i = 0; i < _bones.getSize(); i++)
	{
		if (sb = dynamic_cast<simmBone*>(_bones[i]))
			sb->peteTest();
	}
	for (i = 0; i < _markers.getSize(); i++)
		_markers[i]->peteTest();
}
