// simmBone.cpp
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
#include "simmBone.h"
#include "simmKinematicsEngine.h"
#ifdef BUILD_GUI
#include <vtkPointData.h>
#include <vtkDataArray.h>
#endif
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
simmBone::simmBone() 
#ifdef BUILD_GUI
:
   _vtkBones(0),
	_vtkReaders(0)
#endif
{
	setNull();

}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmBone::simmBone(DOMElement *aElement) :
   rdVisibleObject(aElement)
#ifdef BUILD_GUI
	   ,
	_vtkBones(0),
	_vtkReaders(0)
#endif
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmBone::~simmBone()
{
#ifdef BUILD_GUI
	for (int i = 0; i < _vtkReaders.getSize(); i++)
		_vtkReaders[i]->Delete();
#endif
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aBone Bone to be copied.
 */
simmBone::simmBone(const simmBone &aBone) :
   rdVisibleObject(aBone)
#ifdef BUILD_GUI
	   ,
	_vtkBones(0),
	_vtkReaders(0)
#endif
{
	setupProperties();
	copyData(aBone);
}
//_____________________________________________________________________________
/**
 * Copy this bone and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this bone.
 */
rdObject* simmBone::copy() const
{
	simmBone *bone = new simmBone(*this);
	return(bone);
}
//_____________________________________________________________________________
/**
 * Copy this simmBone and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmBone::simmBone(DOMElement*) in order to establish the
 * relationship of the simmBone object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmBone object. Finally, the data members of the copy are
 * updated using simmBone::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmBone.
 */
rdObject* simmBone::copy(DOMElement *aElement) const
{
	simmBone *bone = new simmBone(aElement);
	*bone = *this;
	bone->updateFromXMLNode();
	return(bone);
}

void simmBone::copyData(const simmBone &aBone)
{
	// TODO: should probably copy the vtkPolyData/vtkXMLPolyDataReader
	// objects themselves, not just the pointers, but can't figure out
	// how to do that.
#ifdef BUILD_GUI
	_vtkBones = aBone._vtkBones;
	_vtkReaders = aBone._vtkReaders;
#endif
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmBone to their null values.
 */
void simmBone::setNull()
{
	setupProperties();
	setType("bone");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmBone::setupProperties()
{
}

simmBone& simmBone::operator=(const simmBone &aBone)
{
	// BASE CLASS
	rdVisibleObject::operator=(aBone);

	copyData(aBone);

	return(*this);
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmBone::setup(simmKinematicsEngine* aEngine)
{
#ifdef BUILD_GUI
	int index;

	/* Each VTK file needs its own reader, which owns the
	 * poly data in the VTK file. The simmBone destructor
	 * calls vtkXMLPolyDataReader::Delete() to free this
	 * memory.
	 */
	for (int i = 0; i < getNumGeometryFiles(); i++)
	{
		index = _vtkReaders.append(vtkXMLPolyDataReader::New()) - 1;
		_vtkReaders[index]->SetFileName(getGeometryFileName(i));
		_vtkReaders[index]->Update();
		vtkPolyData* data = _vtkReaders[index]->GetOutput();
		/* vtkXMLPolyDataReader::GetOutput() returns a non-NULL
		 * pointer in all cases, even if the file is not found.
		 * So check for # polygons and # vertices before adding
		 * the vtkPolyData object to the array. If the data is
		 * bad, add a NULL pointer so the _vtkBones array still
		 * lines up with the _vtkReaders array.
		 */
		if (data && (data->GetNumberOfPolys() > 0 || data->GetNumberOfPoints() > 0))
			_vtkBones.append(_vtkReaders[index]->GetOutput());
		else
			_vtkBones.append(NULL);
	}
#endif
}

/* Scale the vertices in a bone (vtkPolyData object). You'd think
 * there'd be a more efficient way to get and set the points
 * (e.g., a GetPoints() method that returned an array of doubles,
 * and a SetPoints() method to put them back), but I could not
 * find one. I also don't know if the bounding box, normals,
 * and other derivative information is automatically updated.
 */
void simmBone::scale(rdArray<double>& aScaleFactors)
{
#ifdef BUILD_GUI
	for (int i = 0; i < _vtkBones.getSize(); i++)
	{
		if (_vtkBones[i])
		{
			vtkPoints* pts = _vtkBones[i]->GetPoints();
			for (int j = 0; j < pts->GetNumberOfPoints(); j++)
			{
				double* pt = pts->GetPoint(j);
				for (int k = 0; k < 3; k++)
					pt[k] *= aScaleFactors[k];
				pts->SetPoint(j, pt);
			}
		}
	}
#endif
}

void simmBone::writeSIMM(ofstream& out) const
{
	string fileName;

	for (int i = 0; i < getNumGeometryFiles(); i++)
	{
		fileName = string(getGeometryFileName(i));
		int dot = fileName.find_last_of(".");
		if (dot > 0)
			fileName.erase(dot, 4);
		fileName += ".asc";
		out << "bone " << fileName << endl;
	}
}

void simmBone::peteTest() const
{
	cout << "   Bone: " << getName() << endl;
#ifdef BUILD_GUI
	for (int i = 0; i < _vtkBones.getSize(); i++)
	{
		if (_vtkBones[i] == NULL)
			cout << "      file " << getGeometryFileName(i) << " is empty or missing." << endl;
		else
			cout << "      file " << getGeometryFileName(i) << " has " << _vtkBones[i]->GetNumberOfPolys() <<
			     " polygons and " << _vtkBones[i]->GetNumberOfPoints() << " vertices." << endl;
	}
#endif
}

