// simmKinematicsEngine.cpp
// Authors: Frank C. Anderson, Ayman Habib, and Peter Loan
/* Copyright (c) 2005, Stanford University, Frank C. Anderson, Ayman Habib, and Peter Loan.
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
#include <iostream>
#include <string>
#include <math.h>
#include <float.h>
#include <time.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdMemory.h>
#include <NMBLTK/Tools/rdGCVSpline.h>
#include <NMBLTK/SQP/rdFSQP.h>
#include "simmMacros.h"
#include "simmKinematicsEngine.h"
#include "simmStep.h"
#include "simmMarker.h"
#include "simmBone.h"
#include "simmModel.h"
#include "simmMarkerPair.h"
#include "simmUnits.h"

using namespace std;

void convertString(string& str, bool prependUnderscore);

//=============================================================================
// CONSTANTS
//=============================================================================

static char simmGroundName[] = "ground";
static char sdfastGroundName[] = "$ground";

//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */

simmKinematicsEngine::~simmKinematicsEngine()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
simmKinematicsEngine::simmKinematicsEngine() :
	_bodies((rdArrayPtrs<simmBody>&)_bodiesProp.getValueObjArray()),
	_coordinates((rdArrayPtrs<simmCoordinate>&)_coordinatesProp.getValueObjArray()),
	_joints((rdArrayPtrs<simmJoint>&)_jointsProp.getValueObjArray()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_path(0),
	_model(NULL),
	_sdfastInfo(),
	_groundBody(NULL),
	_dIKSolver(0)
{
	// NULL
	setNull();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML Document
 */
simmKinematicsEngine::simmKinematicsEngine(const string &aFileName) :
	nmblKinematicsEngine(aFileName),
	_bodies((rdArrayPtrs<simmBody>&)_bodiesProp.getValueObjArray()),
	_coordinates((rdArrayPtrs<simmCoordinate>&)_coordinatesProp.getValueObjArray()),
	_joints((rdArrayPtrs<simmJoint>&)_jointsProp.getValueObjArray()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_path(0),
	_model(NULL),
	_sdfastInfo(),
	_groundBody(NULL),
	_dIKSolver(0)
{
	// NULL
	setNull();

	// DESERIALIZE
	updateFromXMLNode();

	//setup(NULL);
}

//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmKinematicsEngine::simmKinematicsEngine(DOMElement *aElement) :
	nmblKinematicsEngine(aElement),
	_bodies((rdArrayPtrs<simmBody>&)_bodiesProp.getValueObjArray()),
	_coordinates((rdArrayPtrs<simmCoordinate>&)_coordinatesProp.getValueObjArray()),
	_joints((rdArrayPtrs<simmJoint>&)_jointsProp.getValueObjArray()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_path(0),
	_model(NULL),
	_sdfastInfo(),
	_groundBody(NULL),
	_dIKSolver(0)
{
	// NULL
	setNull();

	// DESERIALIZE
	updateFromXMLNode();

	//setup(NULL);
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 */
simmKinematicsEngine::simmKinematicsEngine(const simmKinematicsEngine& aKE) :
	_bodies((rdArrayPtrs<simmBody>&)_bodiesProp.getValueObjArray()),
	_coordinates((rdArrayPtrs<simmCoordinate>&)_coordinatesProp.getValueObjArray()),
	_joints((rdArrayPtrs<simmJoint>&)_jointsProp.getValueObjArray()),
	_lengthUnitsStr(_lengthUnitsStrProp.getValueStr()),
	_forceUnitsStr(_forceUnitsStrProp.getValueStr()),
	_path(0),
	_model(NULL),
	_sdfastInfo(),
	_groundBody(NULL),
	_dIKSolver(aKE._dIKSolver)
{
	// NULL
	setNull();

	// DESERIALIZE
	//updateFromXMLNode();

	//setup(NULL);
}

rdObject* simmKinematicsEngine::copy() const
{
	simmKinematicsEngine *object = new simmKinematicsEngine(*this);

	return object;
}

rdObject* simmKinematicsEngine::copy(DOMElement *aElement) const
{
	simmKinematicsEngine *object = new simmKinematicsEngine(aElement);

	*object = *this;

	object->updateFromXMLNode();

	//object->setup(_model);

	return object;
}

void simmKinematicsEngine::copyData(const simmKinematicsEngine &aKE)
{
	_bodies = aKE._bodies;
	_coordinates = aKE._coordinates;
	_joints = aKE._joints;
	_lengthUnits = aKE._lengthUnits;
	_forceUnits = aKE._forceUnits;
	_model = aKE._model;
	_sdfastInfo = aKE._sdfastInfo;
}

simmKinematicsEngine& simmKinematicsEngine::operator=(const simmKinematicsEngine &aKE)
{
	// BASE CLASS
	nmblKinematicsEngine::operator=(aKE);

	copyData(aKE);

	//setup(aKE._model);

	return(*this);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all the variable members of this class.
 */
void simmKinematicsEngine::setNull()
{
	setupProperties();
	setType("simmKinematicsEngine");
	setName("");
}


//=============================================================================
// TYPE REGISTRATION
//=============================================================================
///_____________________________________________________________________________
/**
 * Register the types of objects used by simmKinematicsEngine and that need to be registered 
 * for xml serialization purposes
 *
 */
void simmKinematicsEngine::setupProperties()
{
	_bodiesProp.setName("Bodies");
	rdArrayPtrs<rdObject> bdy;
	_bodiesProp.setValue(bdy);
	_propertySet.append(&_bodiesProp);

	_coordinatesProp.setName("Coordinates");
	rdArrayPtrs<rdObject> gc;
	_coordinatesProp.setValue(gc);
	_propertySet.append(&_coordinatesProp);

	_jointsProp.setName("Joints");
	rdArrayPtrs<rdObject> jnt;
	_jointsProp.setValue(jnt);
	_propertySet.append(&_jointsProp);

	_lengthUnitsStrProp.setName("lengthUnits");
	_propertySet.append(&_lengthUnitsStrProp);

	_forceUnitsStrProp.setName("forceUnits");
	_propertySet.append(&_forceUnitsStrProp);
}

void simmKinematicsEngine::registerTypes()
{
	rdObject::RegisterType(simmBody());
	rdObject::RegisterType(simmCoordinate());
	rdObject::RegisterType(simmJoint());
	rdObject::RegisterType(simmNatCubicSpline());
	rdObject::RegisterType(simmConstant());
	rdObject::RegisterType(rdGCVSpline());
	rdObject::RegisterType(simmTranslationDof());
	rdObject::RegisterType(simmRotationDof());
	rdObject::RegisterType(simmMarker());
	rdObject::RegisterType(simmBone());
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmKinematicsEngine::setup(simmModel* aModel)
{
	int i;

	_model = aModel;

	for (i = 0; i < _bodies.getSize(); i++)
		_bodies[i]->setup(this);

	_groundBody = identifyGroundBody();

	for (i = 0; i < _coordinates.getSize(); i++)
		_coordinates[i]->setup(this);

	for (i = 0; i < _joints.getSize(); i++)
		_joints[i]->setup(this);

	/* Generate paths from every body to every other one. */
	makePaths();

	/* For each coordinate, generate a list of the joints that use it. */
	createCoordinateJointLists();

	/* For each coordinate, generate a list of the paths that use it. */
	createCoordinatePathLists();

	/* Initialize the length and force units from the strings specified in the XML file.
	 * If they were not specified, use meters and Newtons.
	 */
	if (_lengthUnitsStrProp.getUseDefault())
		_lengthUnits = simmUnits(simmUnits::simmMeters);
	else
		_lengthUnits = simmUnits(_lengthUnitsStr);

	if (_forceUnitsStrProp.getUseDefault())
		_forceUnits = simmUnits(simmUnits::simmNewtons);
	else
		_forceUnits = simmUnits(_forceUnitsStr);
}

simmBody* simmKinematicsEngine::getBody(const string &aName) const
{
	for (int i = 0; i < _bodies.getSize(); i++)
	{
		if (aName == _bodies[i]->getName())
			return _bodies[i];
	}

	return NULL;
}

simmBody* simmKinematicsEngine::identifyGroundBody(void)
{
	// The ground body is the one that is named simmGroundName.
	for (int i = 0; i < _bodies.getSize(); i++)
	{
		if (_bodies[i]->getName() == simmGroundName)
			return _bodies[i];
	}

	// If that name is not found, then the first body is selected as ground.
	if (_bodies.getSize() > 0)
		return _bodies[0];

	return NULL;
}

suCoordinate* simmKinematicsEngine::getCoordinate(const string &aName) const
{
	for (int i = 0; i < _coordinates.getSize(); i++)
	{
		if (aName == _coordinates[i]->getName())
			return _coordinates[i];
	}

	return NULL;
}


void simmKinematicsEngine::convertPoint(double aPoint[3], const simmBody* aFrom, const simmBody* aTo) const
{
	if (aFrom == aTo)
		return;

	rdTransform& transform = _path.getSimmPath(aFrom, aTo)->getInverseTransform();	// Suspect, rdTransform by value

	transform.transformPoint(aPoint);
}


void simmKinematicsEngine::convertPoint(rdArray<double>& aPoint, const simmBody* aFrom, const simmBody* aTo) const
{
	if (aFrom == aTo)
		return;

	rdTransform& transform = _path.getSimmPath(aFrom, aTo)->getInverseTransform();

	transform.transformPoint(aPoint);
}


/* makePaths: this function makes a vector of paths.
 */
void simmKinematicsEngine::makePaths(void)
{
   int i, j, numPathsCompleted = 0;
   int numBodies = _bodies.getSize();
   int numPaths = numBodies*numBodies;

   /* Create space for the paths, and initialize each path to NULL */
	_path.initTable(numBodies);

   /* Count the trivial paths (from a body to itself) as completed */
	numPathsCompleted += numBodies;

   /* Each joint represents two simple paths- from parent to child and from
    * child to parent. Add these paths to the list and count them as completed.
    */
   for (i = 0; i < _joints.getSize(); i++)
   {
		JointPath p;
		p.push_back(simmStep(_joints[i], simmStep::forward));
		_path.setPath(_joints[i]->getParentBody(), _joints[i]->getChildBody(), p);
      numPathsCompleted++;
		p.clear();
		p.push_back(simmStep(_joints[i], simmStep::inverse));
		_path.setPath(_joints[i]->getChildBody(), _joints[i]->getParentBody(), p);
      numPathsCompleted++;
   }

   /* Until you have completed all paths, loop through the joint array and try to
    * fit that joint onto the end of a path in order to make a new path that is not
    * already defined.
    */
   while (numPathsCompleted < numPaths)
   {
      int k, oldCount = numPathsCompleted;

      for (i = 0; i < _joints.getSize(); i++)
      {
         const simmBody* bodyM = _joints[i]->getParentBody();
         const simmBody* bodyN = _joints[i]->getChildBody();

         if (bodyM == NULL || bodyN == NULL)
            continue;
         for (j = 0; j < numBodies; j++)
         {
            for (k = 0; k < numBodies; k++)
            {
               if (j == k)
                  continue;
					const simmBody* bodyJ = _bodies[j];
					const simmBody* bodyK = _bodies[k];
					const JointPath* jp = _path.getPath(bodyJ, bodyK);
					if (jp == NULL)
						continue;

               /* You've just accessed the path from j to k. If the current joint (i)
                * can be tacked onto the end of this path without looping back to j,
                * then create a path from j to n and see if it should be put in path[j][n].
                * Also check to see if the reverse joint can be tacked onto the end to
                * create a path from j to m.
                */
               if (bodyK == bodyM && bodyJ != bodyN)
               {
                  /* If path[j][n] does not yet exist, or if it is longer than the
                   * path you're about to make, replace it with the new path.
                   */
						const JointPath* curPath = _path.getPath(bodyJ, bodyN);
                  if (curPath == NULL || curPath->size() > jp->size() + 1)
                  {
							JointPath p = *jp;
							p.push_back(simmStep(_joints[i], simmStep::forward));
							_path.setPath(_bodies[j], bodyN, p);
                     numPathsCompleted++;
                  }
               }
               else if (bodyK == bodyN && bodyJ != bodyM)
               {
                  /* If path[j][m] does not yet exist, or if it is longer than the
                   * path you're about to make, replace it with the new path.
                   */
						const JointPath* curPath = _path.getPath(bodyJ, bodyM);
                  if (curPath == NULL || curPath->size() > jp->size() + 1)
                  {
							JointPath p = *jp;
							p.push_back(simmStep(_joints[i], simmStep::inverse));
							_path.setPath(bodyJ, bodyM, p);
                     numPathsCompleted++;
						}
               }
            }
         }
      }

      /* If you did not add any paths to the list in this pass, and you still haven't completed
       * them all, there must be something wrong (e.g., a missing joint).
       */
      if (numPathsCompleted == oldCount && numPathsCompleted < numPaths)
      {
         string name1, name2;
			cout << "makePaths : Error - cannot find joint path between the following pairs of bodies: \n";
         for (i = 0; i < numBodies; i++)
         {
            name1 = _bodies[i]->getName();
            for (j = i+1; j < numBodies; j++)
            {
               name2 = _bodies[j]->getName();

					const JointPath* jp = _path.getPath(_bodies[i], _bodies[j]);
               if (jp == NULL)
               {
                  cout << "(" << _bodies[i]->getName() << ", " << _bodies[j]->getName() << ")\n";
               }
					else
					{
						if (jp->back().getJoint()->getParentBody() != _bodies[j] &&
							 jp->back().getJoint()->getChildBody() != _bodies[j])
						{
							cout << "(" << _bodies[i]->getName() << ", " << _bodies[j]->getName() << ")\n";
						}
					}
            }
         }
         return;
      }
   }
}

/* CREATE COORDINATE JOINT LISTS: For each coordinate, create a list of the
 * joints that use it. These lists are used to mark joint transforms dirty
 * when a coordinate's value is changed.
 */
void simmKinematicsEngine::createCoordinateJointLists()
{
   for (int i = 0; i < _coordinates.getSize(); i++)
   {
      for (int j = 0; j < _joints.getSize(); j++)
      {
         if (_joints[j]->isCoordinateUsed(_coordinates[i]))
         {
            _coordinates[i]->addJointToList(_joints[j]);
         }
      }
   }
}

/* CREATE COORDINATE JOINT LISTS: For each coordinate, create a list of the
 * paths that use it. These lists are used to mark transform paths dirty
 * when a coordinate's value is changed.
 */
void simmKinematicsEngine::createCoordinatePathLists()
{
	for (int i = 0; i < _bodies.getSize(); i++)
	{
		for (int j = 0; j < _bodies.getSize(); j++)
		{
			const JointPath* p = _path.getPath(_bodies[i], _bodies[j]);
			if (p && p->size() > 0)
			{
				for (int c = 0; c < _coordinates.getSize(); c++)
				{
					for (unsigned int k = 0; k < p->size(); k++)
					{
						simmJoint* jnt = (*p)[k].getJoint();
						if (jnt->isCoordinateUsed(_coordinates[c]))
						{
							_coordinates[c]->addPathToList(_path.getSimmPath(_bodies[i], _bodies[j]));
							break;
						}
					}
				}
			}
		}
   }
}

double simmKinematicsEngine::calcDistance(rdArray<double>& aPoint1, const simmBody* aBody1, rdArray<double>& aPoint2, const simmBody* aBody2) const
{
	rdArray<double> pt1copy = aPoint1;

	convertPoint(pt1copy, aBody1, aBody2);

	return sqrt((pt1copy[0] - aPoint2[0])*(pt1copy[0] - aPoint2[0]) + (pt1copy[1] - aPoint2[1])*(pt1copy[1] - aPoint2[1]) +
		         (pt1copy[2] - aPoint2[2])*(pt1copy[2] - aPoint2[2]));
}

double simmKinematicsEngine::calcDistance(const double aPoint1[3], const simmBody* aBody1, const double aPoint2[3], const simmBody* aBody2) const
{
	double pt1copy[3];

	pt1copy[0] = aPoint1[0];
	pt1copy[1] = aPoint1[1];
	pt1copy[2] = aPoint1[2];

	convertPoint(pt1copy, aBody1, aBody2);

	return sqrt((pt1copy[0] - aPoint2[0])*(pt1copy[0] - aPoint2[0]) + (pt1copy[1] - aPoint2[1])*(pt1copy[1] - aPoint2[1]) +
		         (pt1copy[2] - aPoint2[2])*(pt1copy[2] - aPoint2[2]));
}

bool simmKinematicsEngine::checkDynamicParameters(void)
{
	bool dynamicsReady = true;

	for (int i = 0; i < _bodies.getSize(); i++)
	{
		if (_bodies[i] != _groundBody && !_bodies[i]->_sdfastInfo.skippable)
		{
			// Check mass of body
			double mass = _bodies[i]->getMass();
			if (EQUAL_WITHIN_ERROR(mass, 0.0))
			{
				cerr << "Mass of body " << _bodies[i]->getName() << " is zero." << endl;
				dynamicsReady = false;
			}

			// Check inertia matrix of body
			const rdArray<double>& inertia = _bodies[i]->getInertia();
			double inertiaSum = 0.0;
			for (int j = 0; j < 9; j++)
				inertiaSum += inertia[j];
			if (EQUAL_WITHIN_ERROR(inertiaSum, 0.0))
			{
				cerr << "Inertia matrix of body " << _bodies[i]->getName() << " is zero." << endl;
				dynamicsReady = false;
			}
		}
   }

	return dynamicsReady;
}

/* This function looks through all the dofs in all the joints which are a
 * function of the specified gencoord, and tries to find one which should
 * be treated as the unconstrained dof. If the dof has a function with two
 * points, and the slope of the function is 1.0 or -1.0, and the function
 * passes through zero, then it is a good match. The dof is marked as
 * unconstrained, and the function returns. If no such dof is found, the
 * function returns an error. If there are multiple dofs which meet these
 * criteria, the first one is treated as the unconstrained one, and the
 * others will end up constrained (which will create a correct model).
 */
simmDof* simmKinematicsEngine::markUnconstrainedDof(const simmCoordinate* aCoordinate)
{
   for (int i = 0; i < _joints.getSize(); i++)
   {
		rdArrayPtrs<simmDof>& dofs = _joints[i]->getDofs();

      for (int j = 0; j < dofs.getSize(); j++)
      {
			if (dofs[j]->getCoordinate() == aCoordinate)
	      {
				rdFunction* func = dofs[j]->getFunction();

				if (func->getNumberOfPoints() == 2)
				{
					double valueAtZero = func->evaluate(0, 0.0, 0.0, 0.0);
					double slopeAtZero = func->evaluate(1, 0.0, 0.0, 0.0);

					if (EQUAL_WITHIN_ERROR(valueAtZero, 0.0))
					{
						if (EQUAL_WITHIN_ERROR(slopeAtZero, 1.0))
						{
							dofs[j]->_sdfastInfo.constrained = false;
							dofs[j]->_sdfastInfo.conversionSign = 1.0;
							return dofs[j];
						}
						else if (EQUAL_WITHIN_ERROR(slopeAtZero, -1.0))
						{
							dofs[j]->_sdfastInfo.constrained = false;
	                  /* If slope is negative, set the conversion_sign to -1
		                * so the conversion factor (which is set later) will
		                * be negative.
		                */
							dofs[j]->_sdfastInfo.conversionSign = -1.0;
							return dofs[j];
						}
					}
				}
	      }
      }
   }

   return NULL;
}

/* Returns the simmDof which corresponds to the nth Q in the SD/FAST model. */
simmDof* simmKinematicsEngine::findNthSdfastQ(int n, simmJoint*& joint) const
{
	joint = NULL;

   for (int i = 0; i < _joints.getSize(); i++)
   {
		rdArrayPtrs<simmDof>& dofs = _joints[i]->getDofs();

		for (int j = 0; j < dofs.getSize(); j++)
      {
			if ((dofs[j]->getCoordinate() != NULL || dofs[j]->_sdfastInfo.fixed) &&
				 dofs[j]->_sdfastInfo.stateNumber == n)
			{
				joint = _joints[i];
            return dofs[j];
			}
      }
   }
   
   return NULL;
}

simmDof* simmKinematicsEngine::findUnconstrainedSdfastDof(const simmCoordinate* coord) const
{
   for (int i = 0; i < _joints.getSize(); i++)
   {
		rdArrayPtrs<simmDof>& dofs = _joints[i]->getDofs();

		for (int j = 0; j < dofs.getSize(); j++)
      {
			if (!dofs[j]->_sdfastInfo.constrained && dofs[j]->getCoordinate() == coord)
			{
            return dofs[j];
			}
      }
   }
   
   return NULL;
}

/* Return the marker with the passed-in name. Store the pointer to its body
 * in the 'body' argument.
 */
simmMarker* simmKinematicsEngine::getMarker(const string& name, simmBody*& body) const
{
	for (int i = 0; i < _bodies.getSize(); i++)
	{
		for (int j = 0; j < _bodies[i]->getNumMarkers(); j++)
		{
			if (_bodies[i]->getMarker(j)->getName() == name)
			{
				body = _bodies[i];
				return _bodies[i]->getMarker(j);
			}
		}
	}

	return NULL;
}

/* Return the marker with the passed-in name. Store the pointer to its body
 * in the 'body' argument.
 */
const simmMarker* simmKinematicsEngine::getMarker(const string& name, const simmBody*& body) const
{
	for (int i = 0; i < _bodies.getSize(); i++)
	{
		for (int j = 0; j < _bodies[i]->getNumMarkers(); j++)
		{
			if (_bodies[i]->getMarker(j)->getName() == name)
			{
				body = _bodies[i];
				return _bodies[i]->getMarker(j);
			}
		}
	}

	return NULL;
}

void simmKinematicsEngine::countSdfastQsAndConstraints(void)
{
   int i;

   for (i = 0, _sdfastInfo._numQs = 0; i < _joints.getSize(); i++)
	{
		rdArrayPtrs<simmDof>& dofs = _joints[i]->getDofs();

		for (int j = 0; j < dofs.getSize(); j++)
      {
			if (dofs[j]->getCoordinate() != NULL || dofs[j]->_sdfastInfo.fixed)
            _sdfastInfo._numQs++;
		}
	}

   _sdfastInfo._numConstraints = _sdfastInfo._numQs - _coordinates.getSize();

#if 0
   for (i = 0; i < ms->num_constraint_objects; i++)
      _sdfastInfo._numConstraints += ms->constraintobj[i].numPoints;
#endif
}

/* This function initializes all of the SdfastInfo structures
 * in the joints, bodies, and dofs. It needs to be called at
 * the beginning of every "save dynamics" call in order to
 * clear the values from the last call.
 */
void simmKinematicsEngine::initSdfastParameters(void)
{
	int i;

	_sdfastInfo._numConstraints = 0;
	_sdfastInfo._numQs = 0;
	_sdfastInfo._numRestraintFunctions = 0;

	for (i = 0; i < _joints.getSize(); i++)
   {
		_joints[i]->_sdfastInfo.used = false;
		_joints[i]->_sdfastInfo.name.clear();
		_joints[i]->_sdfastInfo.type = dpUnknownJoint;
		_joints[i]->_sdfastInfo.index = -1;
		_joints[i]->_sdfastInfo.direction = simmStep::forward;
		_joints[i]->_sdfastInfo.inbname.clear();
		_joints[i]->_sdfastInfo.outbname.clear();
		_joints[i]->_sdfastInfo.closesLoop = false;
	}

	for (i = 0; i < _bodies.getSize(); i++)
	{
		_bodies[i]->_sdfastInfo.used = false;
		_bodies[i]->_sdfastInfo.timesSplit = 0;
		_bodies[i]->_sdfastInfo.massFactor = 1.0;
		_bodies[i]->_sdfastInfo.skippable = false;
	}

	for (i = 0; i < _coordinates.getSize(); i++)
	{
		_coordinates[i]->_sdfastInfo.restraintFuncNum = -1;
		_coordinates[i]->_sdfastInfo.minRestraintFuncNum = -1;
		_coordinates[i]->_sdfastInfo.maxRestraintFuncNum = -1;
	}

	/* All dofs start as constrained. The function markUnconstrainedDof
	 * unconstains those dofs that correspond to a "true" degree of
	 * freedom in the model.
	 */
	for (i = 0; i < _joints.getSize(); i++)
   {
		rdArrayPtrs<simmDof>& dofList = _joints[i]->getDofs();

      for (int j = 0; j < dofList.getSize(); j++)
      {
			dofList[j]->_sdfastInfo.name.clear();
			dofList[j]->_sdfastInfo.constraintName.clear();
			dofList[j]->_sdfastInfo.initialValue = 0.0;
			dofList[j]->_sdfastInfo.constrained = true;
			dofList[j]->_sdfastInfo.fixed = false;
			dofList[j]->_sdfastInfo.stateNumber = -1;
			dofList[j]->_sdfastInfo.errorNumber = -1;
			dofList[j]->_sdfastInfo.joint = -1;
			dofList[j]->_sdfastInfo.axis = -1;
			dofList[j]->_sdfastInfo.conversion = 0.0;
			dofList[j]->_sdfastInfo.conversionSign = 1.0;
		}
	}
}

bool simmKinematicsEngine::validSdfastModel(void)
{
   int i;

	for (i = 0; i < _joints.getSize(); i++)
   {
		dpJointType type = _joints[i]->_sdfastInfo.type;

      if (type != dpPlanar &&
	       type != dpReversePlanar &&
	       type != dpPin &&
	       type != dpReversePin &&
	       type != dpUniversal &&
	       type != dpReverseUniversal &&
	       type != dpWeld &&
	       type != dpSlider &&
	       type != dpCylindrical &&
	       type != dpReverseCylindrical &&
	       type != dpGimbal &&
	       type != dpReverseGimbal &&
	       type != dpBushing &&
	       type != dpReverseBushing &&
	       type != dpSkippable)
      {
	      cerr << "===ERROR===: Joint " << _joints[i]->getName() << " cannot be converted to an SD/FAST joint." << endl;
         return false;
      }
   }

	for (i = 0; i < _coordinates.getSize(); i++)
   {
      if (_coordinates[i]->isUsedInModel())
      {
			/* markUnconstrainedDof() is called for each simmCoordinate as part of the
			 * setup() process, but it needs to be called again here because the model
			 * may have been modified. This might not be necessary if the setup()
			 * process is repeated every time the model is modified.
			 */
	      if (!markUnconstrainedDof(_coordinates[i]))
         {
	         cerr << "===ERROR===: At least one DOF must be a \"simple\" function of gencoord " <<
					     _coordinates[i]->getName() << " (2 points, slope=1, passes thru zero)." << endl;
            return false;
         }
      }
   }

   return true;
}

/* Names of unconstrained dofs will simply be the names of
 * the gencoords to which they correspond. Names of
 * constrained dofs will be formed from the joint name
 * and the dof keyword (e.g. "hip_tx" and "knee_r1").
 */
void simmKinematicsEngine::makeDofSdfastNames(void)
{
	static string constraintSuffix("_con");

	for (int i = 0; i < _joints.getSize(); i++)
   {
		rdArrayPtrs<simmDof>& dofList = _joints[i]->getDofs();

      for (int j = 0; j < dofList.getSize(); j++)
      {
			if (!dofList[j]->_sdfastInfo.constrained)
         {
				const simmCoordinate* coord = dofList[j]->getCoordinate();
				dofList[j]->_sdfastInfo.name = coord->getName();
				convertString(dofList[j]->_sdfastInfo.name, true);
            dofList[j]->_sdfastInfo.constraintName.clear();
         }
         else
         {
				dofList[j]->_sdfastInfo.name = _joints[i]->getName();
				dofList[j]->_sdfastInfo.name.append("_");
				dofList[j]->_sdfastInfo.name.append(dofList[j]->getName());
				convertString(dofList[j]->_sdfastInfo.name, true);
            dofList[j]->_sdfastInfo.constraintName = dofList[j]->_sdfastInfo.name;
            dofList[j]->_sdfastInfo.constraintName.append(constraintSuffix);
         }
      }
   }
}

string makeSdfastBodyName(string bodyName, int timesSplit)
{
	string sdfastName = bodyName;

   if (sdfastName[0] >= '0' && sdfastName[0] <= '9')
		sdfastName.insert(0, '_');

	for (int i = 0; i < timesSplit; i++)
		sdfastName.append("p");

   return sdfastName;
}

void simmKinematicsEngine::makeSdfastJointOrder(void)
{
   int i, jointsDone = 0, numSkippable = 0, jointsUsed = 0;

	_groundBody->_sdfastInfo.used = true;

	for (i = 0; i < _joints.getSize(); i++)
   {
		if (_joints[i]->getParentBody() == _groundBody)
      {
			_sdfastInfo._jointOrder.append(_joints[i]);
			_joints[i]->_sdfastInfo.index = jointsDone++;
			_joints[i]->getChildBody()->_sdfastInfo.used = true;
         _joints[i]->_sdfastInfo.used = true;
			_joints[i]->_sdfastInfo.direction = simmStep::forward;
         _joints[i]->_sdfastInfo.inbname = sdfastGroundName;
			_joints[i]->_sdfastInfo.outbname = _joints[i]->getChildBody()->getName();
         _joints[i]->_sdfastInfo.closesLoop = false;
      }
      else if (_joints[i]->getChildBody() == _groundBody)
      {
			_sdfastInfo._jointOrder.append(_joints[i]);
			_joints[i]->_sdfastInfo.index = jointsDone++;
			_joints[i]->getParentBody()->_sdfastInfo.used = true;
         _joints[i]->_sdfastInfo.used = true;
			_joints[i]->_sdfastInfo.direction = simmStep::inverse;
         _joints[i]->_sdfastInfo.inbname = sdfastGroundName;
			_joints[i]->_sdfastInfo.outbname = _joints[i]->getParentBody()->getName();
         _joints[i]->_sdfastInfo.closesLoop = false;
      }
   }

   jointsUsed = jointsDone;
   while (jointsDone + numSkippable < _joints.getSize())
   {
      for (i = 0; i < _joints.getSize(); i++)
      {
			if (_joints[i]->_sdfastInfo.used)
            continue;

			simmBody* parentBody = _joints[i]->getParentBody();
			simmBody* childBody = _joints[i]->getChildBody();

			if (!parentBody->_sdfastInfo.used && !childBody->_sdfastInfo.used)
			{
            continue;
			}
         else if (_joints[i]->_sdfastInfo.type == dpSkippable)
         {
            _joints[i]->_sdfastInfo.index = -1;
            numSkippable++;
            _joints[i]->_sdfastInfo.used = false;
            continue;
         }
			else if (!parentBody->_sdfastInfo.used)
         {
				_sdfastInfo._jointOrder.append(_joints[i]);
            _joints[i]->_sdfastInfo.index = jointsUsed++;
            parentBody->_sdfastInfo.used = true;
            _joints[i]->_sdfastInfo.used = true;
				_joints[i]->_sdfastInfo.direction = simmStep::inverse;
				_joints[i]->_sdfastInfo.inbname = childBody->getName();
				_joints[i]->_sdfastInfo.outbname = parentBody->getName();
            _joints[i]->_sdfastInfo.closesLoop = false;
				jointsDone++;
         }
         else if (!childBody->_sdfastInfo.used)
         {
				_sdfastInfo._jointOrder.append(_joints[i]);
            _joints[i]->_sdfastInfo.index = jointsUsed++;
            childBody->_sdfastInfo.used = true;
            _joints[i]->_sdfastInfo.used = true;
				_joints[i]->_sdfastInfo.direction = simmStep::forward;
				_joints[i]->_sdfastInfo.inbname = parentBody->getName();
				_joints[i]->_sdfastInfo.outbname = childBody->getName();
            _joints[i]->_sdfastInfo.closesLoop = false;
				jointsDone++;
         }
         else
         {
				_sdfastInfo._jointOrder.append(_joints[i]);
            _joints[i]->_sdfastInfo.index = jointsUsed++;
            _joints[i]->_sdfastInfo.used = true;
				_joints[i]->_sdfastInfo.direction = simmStep::forward;
				childBody->_sdfastInfo.massFactor += 1.0;
            childBody->_sdfastInfo.timesSplit++;
				_joints[i]->_sdfastInfo.inbname = parentBody->getName();
				_joints[i]->_sdfastInfo.outbname = makeSdfastBodyName(childBody->getName(), childBody->_sdfastInfo.timesSplit);
            _joints[i]->_sdfastInfo.closesLoop = true;
				jointsDone++;
         }
      }
   }

   /* Remove all special characters in the body names, so that the strings
    * are valid one-token C strings. Do not touch the ground segment name ($ground)
    * because SD/FAST requires exactly that name.
    */
   for (i = 0; i < _joints.getSize(); i++)
   {
		if (_joints[i]->_sdfastInfo.type != dpSkippable)
		{
			if (_joints[i]->_sdfastInfo.inbname != sdfastGroundName)
				convertString(_joints[i]->_sdfastInfo.inbname, true);
			if (_joints[i]->_sdfastInfo.outbname != sdfastGroundName)
				convertString(_joints[i]->_sdfastInfo.outbname, true);
		}
   }
}

string getCurrentTimeString(void)
{
   time_t t = time(NULL);

	char buf[100];
   strftime(buf, 100, "%m/%d/%Y %I:%M:%S %p", localtime(&t));
   
   return string(buf);
}

void simmKinematicsEngine::makeSdfastModel(string filename, bool writeFile)
{
	ofstream out;
	int i, j, dofCount = 0, constrainedCount = 0, bodyCount = 0;

   makeDofSdfastNames();
   makeSdfastJointOrder();

   /* Open the SD/FAST input file and write the header information. */
   if (writeFile)
   {
		out.open(filename.c_str());
		out.setf(ios::fixed);
		out.precision(10);

		string timeString = getCurrentTimeString();

		out << "# SD/FAST input file generated by NMBLTS" << endl;
		out << "# Created " << getCurrentTimeString() << endl;
      out << "# Name of original SIMM joints file: dynamicFull.xml" << endl;

      out << "language = c" << endl << endl;

		if (_model)
		{
			const double* gravity = _model->getGravity();
			out << "gravity = " << gravity[0] << "? " << gravity[1] << "? " << gravity[2] << "?" << endl << endl;
		}
   }

	/* Fill in the first body with information about ground. */
	simmSdfastBody* sdfastGround = new simmSdfastBody;
	sdfastGround->_name = _groundBody->getName();
   convertString(sdfastGround->_name, true);
   sdfastGround->_simmBody = _groundBody;
	_groundBody->getMassCenter(sdfastGround->_massCenter);
   sdfastGround->_mass = 0.0;
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         sdfastGround->_inertia[i][j] = 0.0;

	_sdfastInfo._bodies.append(sdfastGround);

	for (i = 0; i < _sdfastInfo._jointOrder.getSize(); i++)
		_sdfastInfo._jointOrder[i]->makeSdfastJoint(out, _sdfastInfo._bodies, &dofCount, &constrainedCount, writeFile);

   if (writeFile)
   {
		bool firstOne = true;

		for (i = 0; i < _bodies.getSize(); i++)
      {
         if (_bodies[i]->_sdfastInfo.timesSplit > 0)
         {
				if (firstOne)
				{
					cout << "# Loop Joints" << endl << endl;
					firstOne = false;
				}
				for (j = 0; j < _bodies[i]->_sdfastInfo.timesSplit; j++)
				{
					out << "body = " << _bodies[i]->getName() << " inb = " <<
						makeSdfastBodyName(_bodies[i]->getName(), j + 1) << " joint = weld" << endl;
					out << "bodytojoint = 0.0 0.0 0.0   inbtojoint = 0.0 0.0 0.0" << endl << endl;
				}
         }
      }
   }

   /* Write out the constraints. The number of constraints is the number of q's
    * minus the number of SIMM gencoords, plus the number of constraint object
	 * points.
    */
   if (writeFile)
   {
		simmDof* dof = NULL;
		simmJoint* joint = NULL;

		countSdfastQsAndConstraints();

      if (_sdfastInfo._numConstraints > 0)
		{
         out << endl << "#constraints = " << _sdfastInfo._numConstraints << endl << endl;

			for (i = 0; i < _sdfastInfo._numQs; i++)
			{
				dof = findNthSdfastQ(i, joint);
				if (dof != NULL && dof->_sdfastInfo.constrained)
					out << "constraint = " << dof->_sdfastInfo.constraintName << endl;
			}
#if 0
			for (i = 0; i < model[mod]->num_constraint_objects; i++)
			{
				for (j = 0; j < model[mod]->constraintobj[i].numPoints; j++)
				{
					out <<  "constraint = %s_", model[mod]->constraintobj[i].name);
					out <<  "%s\n", model[mod]->constraintobj[i].points[j].name);
				}
			}
#endif
		}
      out.close();
   }
}

void simmKinematicsEngine::writeSDHeaderFile(string filename)
{
   int i;
	ofstream out;
	simmDof* dof = NULL;
	simmJoint* joint = NULL;

	out.open(filename.c_str());
	out.setf(ios::fixed);
	out.precision(10);

	string timeString = getCurrentTimeString();

	out << "/*******************************************************************************" << endl << endl;
	out << "  " << filename << endl << endl;
	out << "  " << getCurrentTimeString() << endl << endl;
	out << "*******************************************************************************/" << endl << endl;

	out << "/*********** Joints ************/" << endl;
	for (i = 0; i < _sdfastInfo._jointOrder.getSize(); i++)
	{
		out << "#define ";
		out.width(22);
		out << _sdfastInfo._jointOrder[i]->_sdfastInfo.name << " ";
		out.width(2);
		out << i << endl;
	}

   out << endl << "/************* Qs **************/" << endl;
	for (i = 0; i < _sdfastInfo._numQs; i++)
	{
		dof = findNthSdfastQ(i, joint);
		if (dof && joint)
		{
			out << "#define ";
			out.width(22);
			out << dof->_sdfastInfo.name << " ";
			out.width(2);
			out << i << "   /* = sdindx(" << joint->_sdfastInfo.name << "," << dof->_sdfastInfo.axis << ") */" << endl;
		}
	}

   out << endl << "/******* Constrained Qs ********/" << endl;
	for (i = 0; i < _sdfastInfo._numQs; i++)
	{
		dof = findNthSdfastQ(i, joint);
      if (dof && dof->_sdfastInfo.constrained)
		{
			out << "#define ";
			out.width(22);
			out << dof->_sdfastInfo.constraintName << " ";
			out.width(2);
			out << dof->_sdfastInfo.errorNumber << endl;
		}
   }

   out << endl << "/******** Body Segments ********/" << endl;
	for (i = 0; i < _sdfastInfo._bodies.getSize(); i++)
	{
		out << "#define ";
		out.width(22);
		out << _sdfastInfo._bodies[i]->_name << " ";
		out.width(2);
		out << i - 1 << endl;
	}

	out.close();
}

/* This function writes the user-defined kinematic constraint functions to
 * the top of the SD/FAST C file (sdfor.c).
*/

void simmKinematicsEngine::writeSdfastConstraintData(ofstream& out)
{
   int i, j;
   bool constraintsExist = false;

   /* First see if there are any user-defined constraint functions.
    * If not, just return.
   */
	for (i = 0; i < _sdfastInfo._jointOrder.getSize(); i++)
	{
		rdArrayPtrs<simmDof>& dofs = _sdfastInfo._jointOrder[i]->getDofs();

		for (j = 0; j < dofs.getSize(); j++)
      {
			if (dofs[j]->getCoordinate() != NULL && dofs[j]->_sdfastInfo.constrained)
			{
				constraintsExist = true;
				break;
			}
      }
      if (constraintsExist)
         break;
   }

   if (!constraintsExist)
      return;

	out << "/* The following spline-function data points are copied directly from the" << endl;
   out << " * SIMM joints file." << endl << " */" << endl << endl;

	for (i = 0; i < _sdfastInfo._jointOrder.getSize(); i++)
	{
		rdArrayPtrs<simmDof>& dofs = _sdfastInfo._jointOrder[i]->getDofs();

		for (j = 0; j < dofs.getSize(); j++)
      {
			if (dofs[j]->getCoordinate() != NULL && dofs[j]->_sdfastInfo.constrained)
			{
				rdFunction* func = dofs[j]->getFunction();
				simmNatCubicSpline* bar = new simmNatCubicSpline;

				/* TODO: rdFunction needs some pure virtual getX() and getY() functions??? */
				simmBody* foo = dynamic_cast<simmBody*>(bar);
				simmBody* foo2 = dynamic_cast<simmBody*>(func);
				simmNatCubicSpline* cubicSpline = dynamic_cast<simmNatCubicSpline*>(func);
				if (cubicSpline)
				{
					out << "static double " << dofs[j]->_sdfastInfo.name << "_data[][2] =" << endl << "{" << endl;
					for (int k = 0; k < cubicSpline->getNumberOfPoints(); k++)
					{
						out << "{" << cubicSpline->getX()[k] << ", " << cubicSpline->getY()[k] << "}";
						if (k == cubicSpline->getNumberOfPoints() - 1)
							out << endl << "};" << endl << endl;
						else
							out << "," << endl;
					}
				}
			}
		}
   }

	for (i = 0; i < _sdfastInfo._jointOrder.getSize(); i++)
	{
		rdArrayPtrs<simmDof>& dofs = _sdfastInfo._jointOrder[i]->getDofs();

		for (j = 0; j < dofs.getSize(); j++)
      {
			if (dofs[j]->getCoordinate() != NULL && dofs[j]->_sdfastInfo.constrained)
				out << "static dpSplineFunction " << dofs[j]->_sdfastInfo.name << "_func;" << endl;
      }
   }
}

void simmKinematicsEngine::writeSdfastQRestraintData(ofstream& out)
{
	rdFunction* func;

   for (int i = 0; i < _coordinates.getSize(); i++)
   {
		if ((func = _coordinates[i]->getRestraintFunction()) && _coordinates[i]->isRestraintActive())
      {
			/* TODO: rdFunction needs some pure virtual getX() and getY() functions??? */
			simmNatCubicSpline* cubicSpline = dynamic_cast<simmNatCubicSpline*>(func);
			if (cubicSpline)
			{
				out << endl << "static double q_restraint_func" << _sdfastInfo._numRestraintFunctions + 1 << "_data[][2] = {" << endl;
				for (int k = 0; k < cubicSpline->getNumberOfPoints(); k++)
				{
					out << "{" << cubicSpline->getX()[k] << ", " << cubicSpline->getY()[k] << "}";
					if (k == cubicSpline->getNumberOfPoints() - 1)
						out << endl << "};" << endl << endl;
					else
						out << "," << endl;
				}
				_coordinates[i]->_sdfastInfo.restraintFuncNum = _sdfastInfo._numRestraintFunctions++;
         }
      }
      else
      {
			if (func = _coordinates[i]->getMinRestraintFunction())
			{
				/* TODO: rdFunction needs some pure virtual getX() and getY() functions??? */
				simmNatCubicSpline* cubicSpline = dynamic_cast<simmNatCubicSpline*>(func);
				if (cubicSpline)
				{
					out << endl << "static double q_restraint_func" << _sdfastInfo._numRestraintFunctions + 1 << "_data[][2] = {" << endl;
					for (int k = 0; k < cubicSpline->getNumberOfPoints(); k++)
					{
						out << "{" << cubicSpline->getX()[k] << ", " << cubicSpline->getY()[k] << "}";
						if (k == cubicSpline->getNumberOfPoints() - 1)
							out << endl << "};" << endl << endl;
						else
							out << "," << endl;
					}
					_coordinates[i]->_sdfastInfo.minRestraintFuncNum = _sdfastInfo._numRestraintFunctions++;
				}
			}

			if (func = _coordinates[i]->getMaxRestraintFunction())
			{
				/* TODO: rdFunction needs some pure virtual getX() and getY() functions??? */
				simmNatCubicSpline* cubicSpline = dynamic_cast<simmNatCubicSpline*>(func);
				if (cubicSpline)
				{
					out << endl << "static double q_restraint_func" << _sdfastInfo._numRestraintFunctions + 1 << "_data[][2] = {" << endl;
					for (int k = 0; k < cubicSpline->getNumberOfPoints(); k++)
					{
						out << "{" << cubicSpline->getX()[k] << ", " << cubicSpline->getY()[k] << "}";
						if (k == cubicSpline->getNumberOfPoints() - 1)
							out << endl << "};" << endl << endl;
						else
							out << "," << endl;
					}
					_coordinates[i]->_sdfastInfo.maxRestraintFuncNum = _sdfastInfo._numRestraintFunctions++;
				}
			}
		}
	}

   if (_sdfastInfo._numRestraintFunctions > 0)
      out << endl << "static dpSplineFunction q_restraint_func[" << _sdfastInfo._numRestraintFunctions << "];" << endl << endl;
}

void simmKinematicsEngine::writeSdfastQRestraintFunctions(ofstream& out)
{
   out << "/* INIT_Q_RESTRAINT_FUNCTIONS: this routine initializes the restraint" << endl;
   out << " * functions which are used to keep the Qs from exceeding their ranges of motion.\n */" << endl << endl;

   out << "void init_q_restraint_functions(void)" << endl << "{" << endl << "   int i, numpts;" << endl << endl;

   if (_sdfastInfo._numRestraintFunctions < 1)
   {
      out << "   /* There are no user-defined restraints in this model */" << endl << endl;
   }
   else
   {
      for (int i = 0; i < _sdfastInfo._numRestraintFunctions; i++)
      {
         out << "   numpts = sizeof(q_restraint_func" << i + 1 << "_data)/(sizeof(double)*2);" << endl;
         out << "   (void)malloc_function(&q_restraint_func[" << i << "],numpts);" << endl;
         out << "   q_restraint_func[" << i << "].numpoints = numpts;" << endl;
         out << "   for (i=0; i<numpts; i++)\n   {" << endl;
         out << "      q_restraint_func[" << i << "].x[i] = q_restraint_func" << i + 1 << "_data[i][0];" << endl;
         out << "      q_restraint_func[" << i << "].y[i] = q_restraint_func" << i + 1 << "_data[i][1];" << endl;
         out << "   }" << endl;
         out << "   calc_spline_coefficients(&q_restraint_func[" << i << "]);" << endl;
      }
   }

   out << "}" << endl << endl << endl;
}

void simmKinematicsEngine::writeSdfastQInitCode(ofstream& out)
{
	simmDof* dof;
	simmJoint* joint;

   out << "/* INIT_QS: this routine initializes the array of structures" << endl;
   out << " * that hold information about the Qs (gencoords)." << endl;
   out << " */" << endl << endl;
   
   out << "void init_qs(void)\n{\n\n   int i;" << endl << endl;
   
   out << "   sdm->q = (dpQStruct*)simm_malloc(sdm->nq*sizeof(dpQStruct));" << endl;
   
	for (int i = 0; i < _sdfastInfo._numQs; i++)
	{
		dof = findNthSdfastQ(i, joint);
		if (dof && joint)
		{
			const simmCoordinate* coord = dof->getCoordinate();

			out << "   mstrcpy(&sdm->q[" << dof->_sdfastInfo.name << "].name,\"" << dof->_sdfastInfo.name << "\");" << endl;
			if (dof->_sdfastInfo.fixed)
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].type = dpFixedQ;" << endl;
			}
			else if (!dof->_sdfastInfo.constrained)
			{
				/* Locked gencoords are modeled as fixed Qs (as of SIMM 4.1.1). */
				if (coord && coord->isLocked())
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].type = dpFixedQ;" << endl;
				else
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].type = dpUnconstrainedQ;" << endl;
			}
			else
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].type = dpConstrainedQ;" << endl;
			}
			out << "   sdm->q[" << dof->_sdfastInfo.name << "].joint = " << joint->_sdfastInfo.name << ";" << endl;
			out << "   sdm->q[" << dof->_sdfastInfo.name << "].axis = " << dof->_sdfastInfo.axis << ";" << endl;
			out << "   sdm->q[" << dof->_sdfastInfo.name << "].conversion = " << dof->_sdfastInfo.conversion << ";" << endl;
			out << "   sdm->q[" << dof->_sdfastInfo.name << "].initial_value = " << dof->_sdfastInfo.initialValue << ";" << endl;
			out << "   sdm->q[" << dof->_sdfastInfo.name << "].initial_velocity = 0.0;" << endl;
			if (!dof->_sdfastInfo.constrained && !dof->_sdfastInfo.fixed)
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].range_start = " << dof->getCoordinate()->getRangeMin() << ";" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].range_end = " << dof->getCoordinate()->getRangeMax() << ";" << endl;
			}
			else
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].range_start = -99999.9;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].range_end = 99999.9;" << endl;
			}
			if (dof->_sdfastInfo.constrained || dof->_sdfastInfo.fixed)
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].restraint_func = NULL;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].min_restraint_func = NULL;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].max_restraint_func = NULL;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].function_active = dpNo;" << endl;
			}
			else if (coord)
			{
				if (coord->_sdfastInfo.restraintFuncNum != -1)
				{
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].restraint_func = &q_restraint_func[" <<
						    coord->_sdfastInfo.restraintFuncNum << "];" << endl;
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].min_restraint_func = NULL;" << endl;
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].max_restraint_func = NULL;" << endl;
					if (coord->isRestraintActive())
						out << "   sdm->q[" << dof->_sdfastInfo.name << "].function_active = dpYes;" << endl;
					else
						out << "   sdm->q[" << dof->_sdfastInfo.name << "].function_active = dpNo;" << endl;
				}
				else
				{
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].restraint_func = NULL;" << endl;
					if (coord->_sdfastInfo.minRestraintFuncNum == -1)
						out << "   sdm->q[" << dof->_sdfastInfo.name << "].min_restraint_func = NULL;" << endl;
					else
						out << "   sdm->q[" << dof->_sdfastInfo.name << "].min_restraint_func = &q_restraint_func[" <<
						       coord->_sdfastInfo.minRestraintFuncNum << "];" << endl;
					if (coord->_sdfastInfo.maxRestraintFuncNum == -1)
						out << "   sdm->q[" << dof->_sdfastInfo.name << "].max_restraint_func = NULL;" << endl;
					else
						out << "   sdm->q[" << dof->_sdfastInfo.name << "].max_restraint_func = &q_restraint_func[" <<
						       coord->_sdfastInfo.maxRestraintFuncNum << "];" << endl;
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].function_active = dpNo;" << endl;
				}
			}
			if (dof->_sdfastInfo.constrained)
			{
				simmDof* indDof = findUnconstrainedSdfastDof(coord);
				if (indDof)
				{
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].constraint_func = &" << dof->_sdfastInfo.name << "_func;" << endl;
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].constraint_num = " << dof->_sdfastInfo.constraintName << ";" << endl;
					out << "   sdm->q[" << dof->_sdfastInfo.name << "].q_ind = " << indDof->_sdfastInfo.name << ";" << endl;
				}
			}
			else
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].constraint_func = NULL;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].constraint_num = -1;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].q_ind = -1;" << endl;
			}

			if (dof->_sdfastInfo.fixed || dof->_sdfastInfo.constrained)
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].output = dpNo;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].pd_stiffness = 0.0;" << endl;
			}
			else
			{
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].output = dpYes;" << endl;
				out << "   sdm->q[" << dof->_sdfastInfo.name << "].pd_stiffness = " << coord->getPDStiffness() << ";" << endl;
			}

			out << "   sdm->q[" << dof->_sdfastInfo.name << "].torque = 0.0;" << endl;
			out << "" << endl;
		}
   }
   
   out << "   for (i=0, sdm->num_gencoords=0; i<sdm->nq; i++)" << endl;
   out << "      if (sdm->q[i].type == dpUnconstrainedQ)" << endl;
   out << "         sdm->num_gencoords++;" << endl << endl;
   
   out << "   check_for_sderror(\"INIT_QS\");" << endl;
   
   out << "}" << endl << endl << endl;
}

void simmKinematicsEngine::writeSdfastInitCode(ofstream& out)
{
	out << "/* INIT_SEGMENTS: this routine should be called before" << endl;
	out << " * read_muscles() because it does two things that need to" << endl;
	out << " * be done before you read in the muscles. First, it assigns" << endl;
	out << " * numbers to the body segments in your model. These body" << endl;
	out << " * numbers should match the numbers in the \"_info\" file" << endl;
	out << " * that SD/FAST makes. Thus when you read in the muscle" << endl;
	out << " * attachment points, the segment name listed for each point" << endl;
	out << " * is converted into an SD/FAST body segment number." << endl;
	out << " * Second, this routine records the positions of the mass" << endl;
	out << " * centers of each body segment. These are the coordinates of" << endl;
	out << " * the mass centers with respect to the origins of the SIMM" << endl;
	out << " * bone file. When you read in a muscle attachment point, the" << endl;
	out << " * mass center coordinates are subtracted from it, so that the" << endl;
	out << " * muscle point is now w.r.t. the mass center of the body" << endl;
	out << " * segment, as SD/FAST expects." << endl;
	out << " * Note that you cannot use the #defined segment numbers as indices" << endl;
	out << " * into the sdm->body_segment[] array because they start at -1." << endl;
	out << " */" << endl << endl;

	out << "void init_segments(void)\n{" << endl << endl;

	out << "   int i, j;" << endl;
	out << "   sdm->body_segment = (dpBodyStruct*)simm_malloc(sdm->num_body_segments*sizeof(dpBodyStruct));" << endl << endl;

	/* Go thru the list of bodies. First write the code to enter the name
	 * in the SDModel structure. Then call several SD/FAST routines to get the
	 * mass, inertia, and mass_center coordinates from SD/FAST and store them in
	 * the SDModel structure.
	 */
	for (int i = 0; i < _sdfastInfo._bodies.getSize(); i++)
	{
		simmSdfastBody* body = _sdfastInfo._bodies[i];

		out << "   mstrcpy(&sdm->body_segment[" << body->_name << "+1].name,\"" << body->_name << "\");" << endl;
		if (i == 0)
		{
			out << "   sdm->body_segment[" << body->_name << "+1].output = dpNo;" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass = 0.0;" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass_center[0] = " << body->_massCenter[0] << ";" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass_center[1] = " << body->_massCenter[1] << ";" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass_center[2] = " << body->_massCenter[2] << ";" << endl;
			out << "   for (i=0; i<3; i++)" << endl;
			out << "      for (j=0; j<3; j++)" << endl;
			out << "         sdm->body_segment[" << body->_name << "+1].inertia[i][j] = 0.0;" << endl;
		}
		else
		{
			out << "   sdm->body_segment[" << body->_name << "+1].output = dpYes;" << endl;
			out << "   sdgetmass(" << body->_name << ", &(sdm->body_segment[" << body->_name << "+1].mass));" << endl;
			out << "   sdgetiner(" << body->_name << ", sdm->body_segment[" << body->_name << "+1].inertia);" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass_center[0] = " << body->_massCenter[0] << ";" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass_center[1] = " << body->_massCenter[1] << ";" << endl;
			out << "   sdm->body_segment[" << body->_name << "+1].mass_center[2] = " << body->_massCenter[2] << ";" << endl;
		}
		out << "   sdm->body_segment[" << body->_name << "+1].contactable = dpNo;" << endl;
		out << "" << endl;
	}

	out <<  "   mstrcpy(&sdm->name, \"" << _model->getName() << "\");" << endl << endl;
	out <<  "   check_for_sderror(\"INIT_SEGMENTS\");" << endl << endl;
	out <<  "}" << endl << endl << endl;
}

void simmKinematicsEngine::writeSdfastConstraintCode(ofstream& out)
{
   out << "/* INIT_JOINT_FUNCTIONS: this routine initializes the constraint functions" << endl;
   out << " * for the joints which have user-defined constraints.\n */" << endl << endl;

   out << "void init_joint_functions(void)\n{\n\n   int i, numpts;" << endl << endl;

	for (int i = 0, count = 0; i < _sdfastInfo._jointOrder.getSize(); i++)
   {
		rdArrayPtrs<simmDof>& dofs = _sdfastInfo._jointOrder[i]->getDofs();

		for (int j = 0; j < dofs.getSize(); j++)
      {
			if (dofs[j]->getCoordinate() != NULL && dofs[j]->_sdfastInfo.constrained)
			{
				out << "   numpts = sizeof(" << dofs[j]->_sdfastInfo.name << "_data)/(sizeof(double)*2);" << endl;
				out << "   (void)malloc_function(&" << dofs[j]->_sdfastInfo.name << "_func,numpts);" << endl;
				out << "   " << dofs[j]->_sdfastInfo.name << "_func.numpoints = numpts;" << endl;
				out << "   for (i=0; i<numpts; i++)\n   {" << endl;
				out << "      " << dofs[j]->_sdfastInfo.name << "_func.x[i] = " << dofs[j]->_sdfastInfo.name << "_data[i][0];" << endl;
				out << "      " << dofs[j]->_sdfastInfo.name << "_func.y[i] = " << dofs[j]->_sdfastInfo.name << "_data[i][1];" << endl;
				out << "   }" << endl;
				out << "   calc_spline_coefficients(&" << dofs[j]->_sdfastInfo.name << "_func);" << endl << endl;
				count++;
			}
      }
   }
   
   if (count == 0)
      out << "   /* There are no user-defined constraints in this model */" << endl << endl;
   
   out << "}" << endl << endl << endl;
}

void simmKinematicsEngine::writeSdfastWrapObjects(ofstream& out)
{
	//int i, j, k;
	//WrapObject* wo;

	out << "void init_wrap_objects(void)" << endl;
	out << "{" << endl << endl;

	//if (ms->num_wrap_objects < 1)
	{
		out << "   /* There are no wrap objects in this model. */" << endl << endl;
		out << "  sdm->num_wrap_objects = 0;" << endl;
		out << "  sdm->wrap_object = NULL;" << endl << endl;
		out << "}" << endl << endl;
	}
#if 0
	else
	{
		fprintf(*fp, "   int i;\n\n");

		fprintf(*fp, "   /* The from_local_xforms in this array of wrap objects are expressed relative to\n");
		fprintf(*fp, "    * the origin of the SIMM segment reference frame. The to_local_xforms are filled in with\n");
		fprintf(*fp, "    * zeros-- those transforms are calculated later, directly from the to_local_xforms.\n");
		fprintf(*fp, "    */\n");

		fprintf(*fp,"   dpWrapObject wrap_object[] = {\n");
		for (i = 0; i < ms->num_wrap_objects; i++)
		{
			wo = &ms->wrapobj[i];

			strcpy(buffer, wo->name);
			convert_string(buffer, yes);

			fprintf(*fp,"   {\"%s\", %s, %s, %d, %d, %.10lf, %.10lf, %.10lf, %.10lf, %d, %d,\n",
				buffer, get_wrap_name(wo->wrap_type), (wo->active == yes) ? "dpYes" : "dpNo",
				wo->wrap_algorithm, get_sd_seg_num(ms->segment[wo->segment].name),
				wo->radius.xyz[0], wo->radius.xyz[1], wo->radius.xyz[2], wo->height,
				wo->wrap_axis, wo->wrap_sign);

			fprintf(*fp,"   {%.10lf, %.10lf, %.10lf, %.10lf,\n", wo->from_local_xform[0][0], wo->from_local_xform[0][1],
				wo->from_local_xform[0][2], wo->from_local_xform[0][3]);
			fprintf(*fp,"    %.10lf, %.10lf, %.10lf, %.10lf,\n", wo->from_local_xform[1][0], wo->from_local_xform[1][1],
				wo->from_local_xform[1][2], wo->from_local_xform[1][3]);
			fprintf(*fp,"    %.10lf, %.10lf, %.10lf, %.10lf,\n", wo->from_local_xform[2][0], wo->from_local_xform[2][1],
				wo->from_local_xform[2][2], wo->from_local_xform[2][3]);
			fprintf(*fp,"    %.10lf, %.10lf, %.10lf, %.10lf},\n", wo->from_local_xform[3][0], wo->from_local_xform[3][1],
				wo->from_local_xform[3][2], wo->from_local_xform[3][3]);

			if (i == ms->num_wrap_objects - 1)
				fprintf(*fp,"   }\n");
			else
				fprintf(*fp,"   },\n");
		}
		fprintf(*fp,"   };\n\n");

		fprintf(*fp, "   sdm->num_wrap_objects = %d;\n\n", ms->num_wrap_objects);

		fprintf(*fp, "   sdm->wrap_object = (dpWrapObject*)simm_malloc(sdm->num_wrap_objects * sizeof(dpWrapObject));\n\n");

		fprintf(*fp, "   /* Copy the wrap objects into the sdm structure, and adjust the transforms so that they\n");
		fprintf(*fp, "    * are relative to the mass center of the segment. Then compute the to_local_xform as the\n");
		fprintf(*fp, "    * inverse of the from_local_xform.\n");
		fprintf(*fp, "    */\n");

		fprintf(*fp, "   for (i = 0; i < sdm->num_wrap_objects; i++)\n");
		fprintf(*fp, "   {\n");
		fprintf(*fp, "      sdm->wrap_object[i] = wrap_object[i];\n");
		fprintf(*fp, "      mstrcpy(&sdm->wrap_object[i].name, wrap_object[i].name);\n");
		fprintf(*fp, "      sdm->wrap_object[i].from_local_xform[3][XX] -= sdm->body_segment[sdm->wrap_object[i].segment+1].mass_center[XX];\n");
		fprintf(*fp, "      sdm->wrap_object[i].from_local_xform[3][YY] -= sdm->body_segment[sdm->wrap_object[i].segment+1].mass_center[YY];\n");
		fprintf(*fp, "      sdm->wrap_object[i].from_local_xform[3][ZZ] -= sdm->body_segment[sdm->wrap_object[i].segment+1].mass_center[ZZ];\n");
		fprintf(*fp, "      invert_4x4transform(sdm->wrap_object[i].from_local_xform, sdm->wrap_object[i].to_local_xform);\n");
		fprintf(*fp, "   }\n");

		fprintf(*fp,"}\n\n");
	}
#endif
}

void simmKinematicsEngine::writeSdfastConstraintObjects(ofstream& out)
{
	//int i, j, k, totalNumPts = 0;
	//ConstraintObject* co;
	//ConstraintPoint* pt;

	out << "void init_constraint_objects(void)" << endl;
	out << "{" << endl << endl;

	//if (ms->num_constraint_objects < 1)
	{
		out << "   /* There are no constraint objects in this model. */" << endl << endl;
		out << "  sdm->num_constraint_objects = 0;" << endl;
		out << "  sdm->constraint_object = NULL;" << endl;
		out << "}" << endl << endl;
	}
#if 0
	else
	{
		fprintf(*fp, "   int i, j, index, constraint_num, num_points, sdm_seg_index;\n\n");

		fprintf(*fp, "   /* The from_local_xforms in this array of constraint objects are expressed relative to\n");
		fprintf(*fp, "    * the origin of the SIMM segment reference frame. The to_local_xforms are filled in with\n");
		fprintf(*fp, "    * zeros-- those transforms are calculated later, directly from the to_local_xforms.\n");
		fprintf(*fp, "    */\n");

		fprintf(*fp,"   dpConstraintObject constraint_object[] = {\n");
		for (i = 0; i < ms->num_constraint_objects; i++)
		{
			co = &ms->constraintobj[i];

			strcpy(buffer, co->name);
			convert_string(buffer, yes);

			fprintf(*fp, "   {\"%s\", %s, ", buffer, get_constraint_name(co->constraintType));
			fprintf(*fp, "    %s, %d, \n", (co->active == yes) ? "dpYes" : "dpNo", get_sd_seg_num(ms->segment[co->segment].name));
			fprintf(*fp, "     %.10lf, %.10lf, %.10lf, %.10lf, ",
				co->radius.xyz[0], co->radius.xyz[1], co->radius.xyz[2], co->height);
			fprintf(*fp, "    %d, %d, \n", co->constraintAxis, co->constraintSign);

			fprintf(*fp, "    %d, %d,", co->numPoints, totalNumPts);

			fprintf(*fp,"   {%.10lf, %.10lf, %.10lf, %.10lf,\n", co->from_local_xform[0][0], co->from_local_xform[0][1],
				co->from_local_xform[0][2], co->from_local_xform[0][3]);
			fprintf(*fp,"    %.10lf, %.10lf, %.10lf, %.10lf,\n", co->from_local_xform[1][0], co->from_local_xform[1][1],
				co->from_local_xform[1][2], co->from_local_xform[1][3]);
			fprintf(*fp,"    %.10lf, %.10lf, %.10lf, %.10lf,\n", co->from_local_xform[2][0], co->from_local_xform[2][1],
				co->from_local_xform[2][2], co->from_local_xform[2][3]);
			fprintf(*fp,"    %.10lf, %.10lf, %.10lf, %.10lf}", co->from_local_xform[3][0], co->from_local_xform[3][1],
				co->from_local_xform[3][2], co->from_local_xform[3][3]);

			if (co->constraintType == constraint_plane)
			{
				fprintf(*fp, ",\n   {%.8lf, %.8lf, %.8lf, %.8lf}", co->plane.a,
					co->plane.b, co->plane.c, co->plane.d);
			}
			fprintf(*fp, "\n");

			if (i == ms->num_constraint_objects - 1)
				fprintf(*fp,"   }\n");
			else
				fprintf(*fp,"   },\n");
			totalNumPts += ms->constraintobj[i].numPoints;
		}
		fprintf(*fp,"   };\n\n");

		fprintf(*fp,"   dpConstraintPoint constraint_points[] = {\n");
		for (i = 0, k = 0; i < ms->num_constraint_objects; i++)
		{
			co = &ms->constraintobj[i];

			for (j = 0; j < co->numPoints; j++)
			{
				pt = &ms->constraintobj[i].points[j];
				strcpy(buffer, pt->name);
				convert_string(buffer, yes);

				/* print name and constrainttype */
				fprintf(*fp, "   {\"%s\", ", buffer);
				fprintf(*fp, "    %d, ", get_sd_seg_num(ms->segment[pt->segment].name));
				fprintf(*fp, "    %.10lf, %.10lf, %.10lf, %.10lf",
					pt->offset[0], pt->offset[1], pt->offset[2], pt->weight);

				if (k == totalNumPts - 1)
					fprintf(*fp," }\n");
				else
					fprintf(*fp," },\n");
				k++;
			}
		}
		fprintf(*fp,"   };\n\n");

		fprintf(*fp, "   sdm->num_constraint_objects = %d;\n\n", ms->num_constraint_objects);

		fprintf(*fp, "   sdm->constraint_object = (dpConstraintObject*)simm_malloc(sdm->num_constraint_objects * sizeof(dpConstraintObject));\n\n");

		fprintf(*fp, "   num_points = sizeof(constraint_points) / sizeof(dpConstraintPoint);\n");
		fprintf(*fp, "   constraint_num = sdm->num_user_constraints - num_points;\n\n");

		fprintf(*fp, "   /* Copy the constraint objects into the sdm structure, and adjust the point offsets so that they\n");
		fprintf(*fp, "    * are relative to the mass center of the segment. Then compute the to_local_xform as the\n");
		fprintf(*fp, "    * inverse of the from_local_xform.\n");
		fprintf(*fp, "    */\n");

		fprintf(*fp, "   for (i = 0; i < sdm->num_constraint_objects; i++)\n");
		fprintf(*fp, "   {\n");
		fprintf(*fp, "      sdm->constraint_object[i] = constraint_object[i];\n");
		fprintf(*fp, "      mstrcpy(&sdm->constraint_object[i].name, constraint_object[i].name);\n");
		fprintf(*fp, "      sdm->constraint_object[i].from_local_xform[3][XX] -= sdm->body_segment[sdm->constraint_object[i].segment+1].mass_center[XX];\n");
		fprintf(*fp, "      sdm->constraint_object[i].from_local_xform[3][YY] -= sdm->body_segment[sdm->constraint_object[i].segment+1].mass_center[YY];\n");
		fprintf(*fp, "      sdm->constraint_object[i].from_local_xform[3][ZZ] -= sdm->body_segment[sdm->constraint_object[i].segment+1].mass_center[ZZ];\n");
		fprintf(*fp, "      invert_4x4transform(sdm->constraint_object[i].from_local_xform, sdm->constraint_object[i].to_local_xform);\n");
		fprintf(*fp, "      sdm->constraint_object[i].points = (dpConstraintPoint*)simm_malloc(sdm->constraint_object[i].numPoints * sizeof(dpConstraintPoint));\n");
		fprintf(*fp, "      index = sdm->constraint_object[i].ptIndex;\n");
		fprintf(*fp, "      for (j = 0; j < sdm->constraint_object[i].numPoints; j++)\n");
		fprintf(*fp, "      {\n");
		fprintf(*fp, "         /* adjust the offset to be w.r.t. the mass center, rather than the origin. */\n");
		fprintf(*fp, "         sdm_seg_index = constraint_points[index].segment + 1;\n");
		fprintf(*fp, "         sdvsub(constraint_points[index].offset, sdm->body_segment[sdm_seg_index].mass_center,\n");
		fprintf(*fp, "            sdm->constraint_object[i].points[j].offset);\n");
		fprintf(*fp, "         sdm->constraint_object[i].points[j].segment = constraint_points[index].segment;\n");
		fprintf(*fp, "         sdm->constraint_object[i].points[j].weight = constraint_points[index].weight;\n");
		fprintf(*fp, "         mstrcpy(&sdm->constraint_object[i].points[j].name, constraint_points[index].name);\n");
		fprintf(*fp, "         sdm->constraint_object[i].points[j].constraint_num = constraint_num++;\n");
		fprintf(*fp, "         index++;\n");
		fprintf(*fp, "      }\n");
		fprintf(*fp, "   }\n");

		fprintf(*fp, "}\n\n");
	}
#endif
}

void simmKinematicsEngine::writeSdforCFile(string filename)
{
	ofstream out;

	out.open(filename.c_str());
	out.setf(ios::fixed);
	out.precision(10);

	string timeString = getCurrentTimeString();

   out << "/*******************************************************************************" << endl << endl;
   out << "   " << filename << endl << endl;
	out << "   Created by NMBLTS (from model " << _model->getName() << ")" << endl << endl;
   out << "   Time of creation: " << getCurrentTimeString() << endl << endl;
   out << "   Description: This file contains the routines needed to perform a forward" << endl;
   out << "      dynamics simulation of an SD/FAST model. The specific routines that it" << endl;
   out << "      contains depend on the SIMM model from which this code was generated." << endl << endl;
   out << "*******************************************************************************/" << endl << endl;
   out << "#include \"universal.h\"" << endl;
   out << "#include \"model.h\"" << endl << endl;

   out << "/*************** DEFINES (for this file only) *********************************/" << endl;

   out << "#define BAUMGARTE_STAB 20" << endl << endl;
   out << "/* Defines for the joints, Qs, and body segments are now found in model.h */" << endl << endl;

   out << "\n\n/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/" << endl << endl;

   writeSdfastConstraintData(out);

   writeSdfastQRestraintData(out);
   
   out << "\n\n/**************** GLOBAL VARIABLES (used in only a few files) *****************/" << endl;
   out << "extern dpModelStruct* sdm;" << endl << endl << endl;
   
   out << "/*************** EXTERNED VARIABLES (declared in another file) ****************/" << endl << endl << endl << endl;
   
   out << "/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/" << endl << endl << endl;
   
   writeSdfastQInitCode(out);
   
   writeSdfastInitCode(out);
   
   writeSdfastQRestraintFunctions(out);
   
   writeSdfastConstraintCode(out);
   
   writeSdfastWrapObjects(out);

   writeSdfastConstraintObjects(out);

   out.close();
}

void simmKinematicsEngine::writeSdfastParameterFile(string filename)
{
	int i;
	ofstream out;

	out.open(filename.c_str());
	out.setf(ios::fixed);
	out.precision(10);

   out << "# PARAMS.TXT" << endl;
   out << "# Dynamics Pipeline parameters file generated by NMBLTS" << endl;
   out << "# for use with the stand-alone version of a dynamic simulation." << endl;
   out << "# Created " << getCurrentTimeString() << endl;
	out << "# Name of original SIMM model: " << _model->getName() << endl;
   out << "#" << endl;
   out << "# This file contains all of the parameters that you can specify at" << endl;
   out << "# run-time in a dynamic simulation (stand-alone version). To change" << endl;
   out << "# one of them, remove the '#' from the beginning of the line (which" << endl;
   out << "# identifies the line as a comment), and change the parameter to the" << endl;
   out << "# desired value." << endl << endl;

   out << "############################# I/O Options #############################" << endl;
	out << "muscle_file dynamic.msl" << endl;
	out << "#bone_path path_to_bone_files" << endl;
	out << "output_motion_file results.mot" << endl;
   out << "#kinetics_file forces.ktx" << endl;
	out << "#output_kinetics_file results.ktx" << endl << endl;

   out << "######################## Integration Parameters #######################" << endl;
   out << "start_time 0.0  #start time of simulation" << endl;
   out << "end_time   1.0  #end time of simulation" << endl;
   out << "step_size  0.01 #reporting interval for integrator" << endl << endl;

   out << "######################### Segment Parameters ##########################" << endl;
   out << "# You can specify mass properties here if you add '?' after their" << endl;
   out << "# values in model.sd. Mass centers should only be changed by editing" << endl;
   out << "# your SIMM joint file and re-saving the dynamics files." << endl;
   out << "# segment_name mass value" << endl;
   out << "# segment_name inertia I11 I12 I13 I21 I22 I23 I31 I32 I33" << endl;

	for (i = 1; i < _sdfastInfo._bodies.getSize(); i++)
   {
      out << "#" << _sdfastInfo._bodies[i]->_name << " mass " << _sdfastInfo._bodies[i]->_mass << endl;
      out << "#" << _sdfastInfo._bodies[i]->_name << " inertia " <<
			_sdfastInfo._bodies[i]->_inertia[0][0] << " " <<
			_sdfastInfo._bodies[i]->_inertia[0][1] << " " <<
			_sdfastInfo._bodies[i]->_inertia[0][2] << " " <<
			_sdfastInfo._bodies[i]->_inertia[1][0] << " " <<
			_sdfastInfo._bodies[i]->_inertia[1][1] << " " <<
			_sdfastInfo._bodies[i]->_inertia[1][2] << " " <<
			_sdfastInfo._bodies[i]->_inertia[2][0] << " " <<
			_sdfastInfo._bodies[i]->_inertia[2][1] << " " <<
			_sdfastInfo._bodies[i]->_inertia[2][2] << endl;
   }
   out << endl;

   out << "####################### Gencoord Initialization #######################" << endl;
   out << "# gencoord_name initial_value initial_velocity" << endl;
   out << "#" << endl;

	for (i = 0; i < _sdfastInfo._numQs; i++)
	{
		simmJoint* joint;
		simmDof* dof = findNthSdfastQ(i, joint);
      if (dof)
			out << "#" << dof->_sdfastInfo.name << " " << dof->_sdfastInfo.initialValue << " 0.0" << endl;
   }
   out << endl;

   out << "########################### Output Options ############################" << endl;
   out << "# this one is for output printed to the shell window" << endl;
   out << "verbose no" << endl;
   out << "# these are for output written to output_motion_file" << endl;
   out << "output_gencoord_values yes" << endl;
   out << "output_muscle_activations yes" << endl;
   out << "output_muscle_lengths no" << endl;
   out << "output_muscle_forces yes" << endl;
   out << "output_muscle_fiber_lengths no" << endl;
   out << "output_muscle_fiber_velocities no" << endl;
   out << "output_muscle_moment_arms no" << endl;
   out << "output_muscle_joint_torques no" << endl;
   out << "output_total_muscle_joint_torques no" << endl;
   out << "output_joint_torques no" << endl;
   out << "output_corrected_joint_torques no" << endl;
   out << "output_joint_reaction_forces no" << endl;
   out << "output_joint_reaction_torques no" << endl;
   out << "output_optimized_muscle_activations no" << endl;
   out << "output_mass_center_positions no" << endl;
   out << "output_mass_center_velocities no" << endl;
   out << "output_system_energy no" << endl;
   out << "output_contact_forces no" << endl;
   out << "output_spring_forces no" << endl;
   out << "num_output_spring_forces 20" << endl << endl;

   out << "####################### Force Matte Definitions #######################" << endl;
   out << "# force mattes can be used to apply forces defined in the ground" << endl;
   out << "# reference frame to some other body segment." << endl;
   out << "# force_matte matte_name bone_file_name segment_name" << endl;
#if 0
   for (i = 0; i < model->numsegments; i++)
   {
      if (model->segment[i].forceMatte)
      {
         fprintf(file,"force_matte %s %s\t%s\n", model->segment[i].forceMatte->name,
            model->segment[i].forceMatte->filename, model->segment[i].name);
      }
   }
#endif
   out << endl;

   out << "##################### Contact Detection Variables #####################" << endl;
   out << "# object object_name bone_file_name segment_name" << endl;
   out << "# begin_group group_name object_name1 ... object_nameN end_group" << endl;
   out << "# contact_pair object_name1 object_name2 coef_rest mu_dynamic mu_static" << endl << endl;
#if 0
   for (i=0; i<model->numsegments; i++)
   {
      for (j=0; j<model->segment[i].numContactObjects; j++)
      {
         fprintf(file,"object %s %s\t%s\n", model->segment[i].contactObject[j].name,
            model->segment[i].contactObject[j].filename, model->segment[i].name);
      }
   }
   for (i=0; i<model->numContactGroups; i++)
   {
      fprintf(file,"begin_group %s\n", model->contactGroup[i].name);
      for (j=0; j<model->contactGroup[i].numElements; j++)
         fprintf(file,"%s ", model->contactGroup[i].element[j]);
      fprintf(file,"\nend_group" << endl;
   }
   for (i=0; i<model->numContactPairs; i++)
   {
      fprintf(file,"contact_pair %s %s %lf %lf %lf\n",
         model->contactPair[i].body1,
         model->contactPair[i].body2,
         model->contactPair[i].restitution,
         model->contactPair[i].mu_static,
         model->contactPair[i].mu_dynamic);
   }
#endif

   out << "######################## Spring-based Contacts ########################" << endl;
   out << "# spring_floor spring_floor_name file_name segment_name" << endl;
   out << "# spring segment_name Px Py Pz spring_floor_name friction param1 param2 param3 param4 param5 param6" << endl;
#if 0
   for (i=0; i<model->numsegments; i++)
   {
      if (model->segment[i].springFloor)
      {
         fprintf(file,"spring_floor %s %s %s\n", 
            model->segment[i].springFloor->name, 
            model->segment[i].springFloor->filename,
            model->segment[i].name);
      }
      for (j=0; j<model->segment[i].numSpringPoints; j++)
      {
         fprintf(file,"spring %s % 10.4f % 10.4f % 10.4f "
            "%s % 10.4f % 12.4f % 12.4f % 12.4f % 12.4f % 12.4f % 12.4f\n", 
            model->segment[i].name,
            model->segment[i].springPoint[j].point[0],
            model->segment[i].springPoint[j].point[1],
            model->segment[i].springPoint[j].point[2],
            model->segment[i].springPoint[j].floorName,
            model->segment[i].springPoint[j].friction,
            model->segment[i].springPoint[j].param_a,
            model->segment[i].springPoint[j].param_b,
            model->segment[i].springPoint[j].param_c,
            model->segment[i].springPoint[j].param_d,
            model->segment[i].springPoint[j].param_e,
            model->segment[i].springPoint[j].param_f);
      }
   }
#endif
   out << endl;

   out << "##################### Muscle State Initialization #####################" << endl;
   out << "# You can specify the initial values of the muscle model states for each" << endl;
   out << "# muscle by un-commenting the appropriate line[s] below and replacing" << endl;
   out << "# the zeros with the initial values. You must specify the state values" << endl;
   out << "# in the order that the states are numbered in the muscle derivative" << endl;
   out << "# function for that muscle model (in derivs.c). You can specify fewer" << endl;
   out << "# than the total number of states in the muscle model, but the N values" << endl;
   out << "# that you specify will be used to initialize the *first* N states in the" << endl;
   out << "# model. If you specify more states than there are in the muscle model," << endl;
   out << "# the extra values will be ignored." << endl;
   out << "# muscle_name state1_init_value state2_init_value ..." << endl;
   out << "#" << endl;

	for (i = 0; i < _model->getNumberOfMuscles(); i++)
		out << "#" << _model->getMuscle(i)->getName() << " 0.0 0.0 0.0" << endl;
   out << endl;

	out.close();
}

void simmKinematicsEngine::saveDynamics(const string &aFolderName)
{
	initSdfastParameters();

	for (int i = 0; i < _joints.getSize(); i++)
		_joints[i]->identifyDpType(_model);

	if (!validSdfastModel())
		goto error;

	if (!checkDynamicParameters())
		goto error;

	makeSdfastModel(aFolderName + "model.sd", true);

	writeSDHeaderFile(aFolderName + "model.h");

	writeSdforCFile(aFolderName + "sdfor.c");

	writeSdfastParameterFile("pipeline/params.txt");

	goto cleanup;

error:
	cerr << "Cannot save dynamics." << endl;

cleanup:
	_sdfastInfo._bodies.clearAndDestroy();
	_sdfastInfo._jointOrder.setSize(0);

	return;
}

/* Given a joint, this function returns which of its bodies, if either,
 * is a leaf node in the kinematic topology.
 */
simmBody* simmKinematicsEngine::getLeafBody(simmJoint* aJoint) const
{
	int parentCount = 0, childCount = 0;
	simmBody* parentBody = aJoint->getParentBody();
	simmBody* childBody = aJoint->getChildBody();

	for (int i = 0; i < _joints.getSize(); i++)
	{
		if (parentBody == _joints[i]->getParentBody() || parentBody == _joints[i]->getChildBody())
			parentCount++;
		if (childBody == _joints[i]->getParentBody() || childBody == _joints[i]->getChildBody())
			childCount++;
	}

	/* If the body is used in exactly one joint, and it is not ground,
	 * then it is a leaf node.
	 */
	if (parentCount == 1 && parentBody != _groundBody)
		return parentBody;
	else if (childCount == 1 && childBody != _groundBody)
		return childBody;
	else
		return NULL;
}

int simmKinematicsEngine::getNumMarkers() const
{
	int num = 0;

	for (int i = 0; i < _bodies.getSize(); i++)
		num += _bodies[i]->getNumMarkers();

	return num;
}

void simmKinematicsEngine::getUnlockedCoordinates(simmCoordinateArray& aUnlockedCoordinates) const
{
	aUnlockedCoordinates.setSize(0);

	for (int i = 0; i < _coordinates.getSize(); i++)
		if (!_coordinates[i]->isLocked())
			aUnlockedCoordinates.append(_coordinates[i]);
}

void simmKinematicsEngine::solveInverseKinematics(const simmIKTrialParams& aIKOptions, const std::string aMarkerDataFileName, const std::string aOutputFileName)
{
	// Experimental marker and coordinate data
	rdStorage inputStorage(aMarkerDataFileName.c_str());
	//TODO need to convert units

	// Set up output storage
	rdStorage outputStorage;
	outputStorage.setName("InverseKinematicsResults");

	assert(_dIKSolver);
	// Solve the frames.
	_dIKSolver->solveFrames(aIKOptions, inputStorage, outputStorage);

	outputStorage.setWriteSIMMHeader(true);
	outputStorage.print(aOutputFileName.c_str());
}

simmMotionData* simmKinematicsEngine::solveInverseKinematics(const simmIKTrialParams& aIKOptions, simmMarkerData& aMarkerData)
{
	// Convert experimental marker data to rdStorage object.
	rdStorage inputStorage;
	aMarkerData.makeRdStorage(inputStorage);

	// Set up output storage.
	rdStorage outputStorage;
	outputStorage.setName(aMarkerData.getFileName());

	assert(_dIKSolver);
	// Solve the frames.
	_dIKSolver->solveFrames(aIKOptions, inputStorage, outputStorage);

	// Store the result in a simmMotionData object.
	simmMotionData* outputMotionData = new simmMotionData(outputStorage);

	return outputMotionData;
}

simmMotionData* simmKinematicsEngine::solveInverseKinematics(const simmIKTrialParams& aIKOptions, simmMarkerData& aMarkerData, simmMotionData& aCoordinateData)
{

	/* Convert experimental marker data to an rdStorage object. */
	rdStorage inputStorage;
	aMarkerData.makeRdStorage(inputStorage);

	/* Adjust the user-defined start and end times to make sure they are in the
	 * range of the marker data. This must be done so that you only look in the
	 * coordinate data for rows that will actually be solved.
	 */
	double firstStateTime = inputStorage.getFirstTime();
	double lastStateTime = inputStorage.getLastTime();
	double startTime = MAX(firstStateTime, aIKOptions.getStartTime());
	double endTime = MIN(lastStateTime, aIKOptions.getEndTime());

	/* Add the coordinate data to the marker data. There must be a row of
	 * corresponding coordinate data for every row of marker data that will
	 * be solved, or it is a fatal error.
	 */
	aCoordinateData.addToRdStorage(inputStorage, startTime, endTime);

	// Set up output storage.
	rdStorage outputStorage;
	outputStorage.setName(aMarkerData.getFileName());

	assert(_dIKSolver);
	// Solve the frames.
	_dIKSolver->solveFrames(aIKOptions, inputStorage, outputStorage);

	// Store the result in a simmMotionData object.
	simmMotionData* outputMotionData = new simmMotionData(outputStorage);

	return outputMotionData;
}

/* Set the local offset of each non-fixed marker so that in the model's
 * current pose the marker coincides with the marker's global position
 * in the passed-in simmMarkerData.
 */
void simmKinematicsEngine::moveMarkersToCloud(simmMarkerData& aMarkerData)
{
	aMarkerData.averageFrames(0.01);
	simmMarkerFrame* frame = aMarkerData.getFrame(0);

	for (int i = 0; i < _bodies.getSize(); i++)
	{
		for (int j = 0; j < _bodies[i]->getNumMarkers(); j++)
		{
			simmMarker* localMarker = _bodies[i]->getMarker(j);
			if (!localMarker->getFixed())
			{
				int index = aMarkerData.getMarkerIndex(localMarker->getName());
				if (index >= 0)
				{
					simmPoint& globalMarker = frame->getMarker(index);
					if (globalMarker.isVisible())
					{
						double pt[3], *globalPt = globalMarker.get();
						double conversionFactor = aMarkerData.getUnits().convertTo(getLengthUnits());
						for (int k = 0; k < 3; k++)
							pt[k] = globalPt[k] * conversionFactor;
						convertPoint(pt, getGroundBodyPtr(), _bodies[i]);
						localMarker->setOffset(pt);
					}
					else
					{
						cout << "___WARNING___: marker " << localMarker->getName() << " does not have valid coordinates in " << aMarkerData.getFileName() << endl;
						cout << "               It will not be moved to match location in marker file." << endl;
					}
				}
			}
		}
	}

	cout << "Moved markers in model " << _model->getName() << " to match locations in marker file " << aMarkerData.getFileName() << endl;
}

/* Remove all markers from the model that are not in the passed-in list. */
int simmKinematicsEngine::deleteUnusedMarkers(const rdArray<string>& aMarkerNames)
{
	int numDeleted = 0;

	for (int i = 0; i < _bodies.getSize(); i++)
		numDeleted += _bodies[i]->deleteUnusedMarkers(aMarkerNames);

	cout << "Deleted " << numDeleted << " unused markers from model " << _model->getName() << endl;

	return numDeleted;
}

//_____________________________________________________________________________
/**
 * Replace all markers in the model with the ones in the
 * passed-in marker set. Return value is the number of markers
 * in the marker set that were successfully added to the model.
 */
int simmKinematicsEngine::replaceMarkerSet(simmMarkerSet& aMarkerSet)
{
	int i, numAdded = 0;
	simmBody* body;

	// First remove all existing markers from the model.
	for (i = 0; i < _bodies.getSize(); i++)
		_bodies[i]->deleteAllMarkers();

	for (i = 0; i < aMarkerSet.getSize(); i++)
	{
		simmMarker* nextMarker = aMarkerSet.get(i);
		const string* bodyName = nextMarker->getBodyName();
		// If the model contains a body by that name, add the marker to it.
		if (body = getBody(*bodyName))
		{
			body->addMarker(nextMarker);
			numAdded++;
		}
	}

	cout << "Replaced marker set in model " << _model->getName() << endl;
	return numAdded;
}

//_____________________________________________________________________________
/**
 * Update all markers in the model with the ones in the
 * passed-in marker set. If the marker does not yet exist
 * in the model, it is added.
 */
void simmKinematicsEngine::updateMarkers(rdArrayPtrs<simmMarker>& aMarkerArray)
{
	int i;
	simmBody* body;

	for (i = 0; i < aMarkerArray.getSize(); i++)
	{
		simmBody* modelMarkerBody = NULL;
		simmMarker* updatingMarker = aMarkerArray[i];
		simmMarker* modelMarker = getMarker(updatingMarker->getName(), modelMarkerBody);
		const string* updatingBodyName = updatingMarker->getBodyName();

		/* If there is already a marker in the model with that name,
		 * update it with the parameters from the updating marker,
		 * moving it to a new body if necessary.
		 */
		if (modelMarker)
		{
			/* If the updating marker is on a different body, delete the
			 * marker from the model and add the updating one (as long as
			 * the updating marker's body exists in the model).
			 */
			if (modelMarkerBody &&
				 updatingBodyName &&
				 modelMarkerBody->getName() != *updatingBodyName)
			{
				modelMarkerBody->deleteMarker(modelMarker);
				if (body = getBody(*updatingBodyName))
					body->addMarker(updatingMarker);
			}
			else
			{
				modelMarker->updateFromMarker(*updatingMarker);
			}
		}
		else
		{
			/* The model does not contain a marker by that name. If it has
			 * a body by that name, add the updating marker to it.
			 */
			if (updatingBodyName && (body = getBody(*updatingBodyName)))
				body->addMarker(updatingMarker);
		}
	}

	cout << "Updated markers in model " << _model->getName() << endl;
}

//_____________________________________________________________________________
/**
 * Update all coordinates in the model with the ones in the
 * passed-in coordinate set. If the coordinate does not exist
 * in the model, it is not added.
 */
void simmKinematicsEngine::updateCoordinates(rdArrayPtrs<simmCoordinate>& aCoordinateArray)
{
	for (int i = 0; i < aCoordinateArray.getSize(); i++)
	{
		simmCoordinate* modelCoordinate = dynamic_cast<simmCoordinate *> (getCoordinate(aCoordinateArray[i]->getName()));
		if (modelCoordinate)
			modelCoordinate->updateFromCoordinate(*aCoordinateArray[i]);
	}

	cout << "Updated coordinates in model " << _model->getName() << endl;
}

/* Measure a length on a model. The length is defined by the average distance
 * between 1 or more pairs of markers, as stored in a simmMeasurement.
 */
double simmKinematicsEngine::takeMeasurement(const simmMeasurement& aMeasurement)
{
	double length;
	const string *name1 = NULL, *name2 = NULL;
	int i, numPairs;
	const simmBody* body1 = NULL;
	const simmBody* body2 = NULL;

	/* For each pair of markers, calculate the distance between them
	 * and add it to the running total.
	 */
	for (i = 0, length = 0.0, numPairs = 0; i < aMeasurement.getNumMarkerPairs(); i++)
	{
		const simmMarkerPair& pair = aMeasurement.getMarkerPair(i);
		pair.getMarkerNames(name1, name2);
		const simmMarker* marker1 = getMarker(*name1, body1);
		const simmMarker* marker2 = getMarker(*name2, body2);
		if (marker1 && marker2)
		{
			length += calcDistance(marker1->getOffset(), body1, marker2->getOffset(), body2);
			numPairs++;
		}
		else
		{
			if (!marker1)
				cout << "___WARNING___: marker " << name1->c_str() << " in " << aMeasurement.getName() << " measurement not found in " << _model->getName() << endl;
			if (!marker2)
				cout << "___WARNING___: marker " << name2->c_str() << " in " << aMeasurement.getName() << " measurement not found in " << _model->getName() << endl;
		}
	}

	/* Divide by the number of pairs to get the average length. */
	if (numPairs == 0)
	{
		cout << "___WARNING___: could not calculate " << aMeasurement.getName() << " measurement on " << _model->getName() << endl;
		return rdMath::NAN;
	}
	else
	{
		return length / numPairs;
	}
}

void simmKinematicsEngine::writeSIMMJointFile(string& aFileName) const
{
   ofstream out;
	int functionIndex = 1;

   out.open(aFileName.c_str());
   out.setf(ios::fixed);
   out.precision(6);

   if (!out.good())
   {
      cout << "Unable to open output file " << aFileName << endl;
      return;
   }

   out << "/**********************************************************/\n";
   out << "/*            Joint file created by NMBLTS                */\n";
   if (_model->getInputFileName() != "")
      out << "/* name of original model file: " << _model->getInputFileName() << " */\n";
   out << "/**********************************************************/\n";
   out << "\nname " << _model->getName() << endl;
   out << "\n";
#if 0
   if (!mBonePath.empty())
      out << "bone_path " << mBonePath << endl;
   if (!mMuscleFilename.empty())
      out << "\nmuscle_file " << mMuscleFilename << endl;
   if (!mMotionFilename.empty())
      out << "motion_file " << mMotionFilename << endl;
#endif

	if (_lengthUnits.getType() != simmUnits::simmUnknownUnits)
		out << "length_units " << _lengthUnits.getLabel() << endl;
	if (_forceUnits.getType() != simmUnits::simmUnknownUnits)
		out << "force_units " << _forceUnits.getLabel() << endl;

#if 0
   if (mMarkerRadius != 0.01)
      out << "marker_radius " << mMarkerRadius << endl;
   if (mMVGear != 0.08)
      out << "MV_gear " << mMVGear << endl;
   if (mMarkerVisibility)
      out << "marker_visibility on\n";
   else
      out << "marker_visibility off\n";
   smOptions options;
   this->getOptions(options);
   out << "solver_accuracy " << options.accuracy << endl;
   out << "solver_method " << getSolverMethodString(options.method) << endl;
   if (options.orientBodyToFrame == smYes)
      out << "solver_orient_body yes" << endl;
   else
      out << "solver_orient_body no" << endl;
   if (options.jointLimitsOn == smYes)
      out << "solver_joint_limits yes" << endl;
   else
      out << "solver_joint_limits no" << endl;
   out << "solver_max_iterations " << options.maxIterations << endl;
#endif

	out << "gravity " << _model->getGravityLabel() << endl;

   out << "\n/****************************************************/\n";
   out << "/*                     SEGMENTS                     */\n";
   out << "/****************************************************/\n";
	for (int i = 0; i < _bodies.getSize(); i++)
		_bodies[i]->writeSIMM(out);

   out << "\n/****************************************************/\n";
   out << "/*                      JOINTS                      */\n";
   out << "/****************************************************/\n";
	for (int i = 0; i < _joints.getSize(); i++)
		_joints[i]->writeSIMM(out, functionIndex);

   out << "\n/****************************************************/\n";
   out << "/*                     GENCOORDS                    */\n";
   out << "/****************************************************/\n";
	for (int i = 0; i < _coordinates.getSize(); i++)
		_coordinates[i]->writeSIMM(out, functionIndex);

#if 0
   out << "\n/****************************************************/\n";
   out << "/*                     FUNCTIONS                    */\n";
   out << "/****************************************************/\n";
   for (ConsFuncListIterator cf = mConstraintFunction.begin(); cf != mConstraintFunction.end(); cf++)
      (*cf)->print(out);

   out << "\n/****************************************************/\n";
   out << "/*                CONSTRAINT OBJECTS                */\n";
   out << "/****************************************************/\n";
   for (ConstraintObjectListIterator co = mConstraintObject.begin(); co != mConstraintObject.end(); co++)
      (*co)->print(out);
#endif
   
   out << "\n/****************************************************/\n";
   out << "/*                     MATERIALS                    */\n";
   out << "/****************************************************/\n";
   out << "beginmaterial mat1\nambient 0.3 0.3 0.9\ndiffuse 0.3 0.3 0.9\n";
   out << "specular 1.0 1.0 1.0\nendmaterial\n\n";

   out << "beginmaterial mat2\nambient 0.3 0.3 0.3\ndiffuse 0.3 0.3 0.3";
   out << "\nspecular 0.3 0.3 0.3\nendmaterial\n\n";

   out << "beginmaterial my_bone\nambient 0.65 0.65 0.65\nspecular 0.7 0.55 0.4";
   out << "\ndiffuse 0.55 0.4 0.35\nshininess 10\nendmaterial\n\n";

   out << "beginmaterial red\nambient 0.9 0.1 0.1\nspecular 0.7 0.2 0.2";
   out << "\ndiffuse 0.2 0.2 0.2\nshininess 10\nendmaterial\n\n";

   out << "beginmaterial blue\nambient 0.1 0.1 0.9\nspecular 0.2 0.2 0.7";
   out << "\ndiffuse 0.2 0.2 0.2\nshininess 10\nendmaterial\n\n";

   out << "\n/****************************************************/\n";
   out << "/*                     WORLD OBJECTS                */\n";
   out << "/****************************************************/\n";

	const char* gravity = _model->getGravityLabel();

   out << "beginworldobject floor\n";
   if (gravity == "+X" || gravity == "-X")
      out << "filename floor_yz_plane.asc\n";
   else if (gravity == "+Y" || gravity == "-Y")
      out << "filename floor_xz_plane.asc\n";
   else if (gravity == "+Z" || gravity == "-Z")
      out << "filename floor_xy_plane.asc\n";
   else
      out << "filename floor1.asc\n";
   out << "origin 0.0 0.0 0.0" << endl;
   out << "\nmaterial mat2\n";
	/* The floor bone file is in meters, so scale it to fit this model. */
	double floorScale = 1.0 / getLengthUnits().convertTo(simmUnits::simmMeters);
	out << "scale " << floorScale << " " << floorScale * 2.0 << " " << floorScale * 4.0 << endl;
   out << " endworldobject\n\n";

   out << "\n/****************************************************/\n";
   out << "/*                    MOTION OBJECTS                */\n";
   out << "/****************************************************/\n";

	/* The default ball object in SIMM is in meters, so scale it to fit this model. */
	out << "beginmotionobject ball\n";
	double scale = 0.25 / getLengthUnits().convertTo(simmUnits::simmMeters);
	out << "material blue" << endl;
	out << "scale " << scale << " " << scale << " " << scale << endl;
   out << "endmotionobject\n\n";

   out.close();
	cout << "Wrote SIMM joint file " << aFileName << " from model " << _model->getName() << endl;
}

/* Write an XML file of all the markers in the model.
 * The contents of this file can be pasted into the
 * MarkerSet definition inside a simmMarkerPlacementParams,
 * or a simmGenericModelParams.
 */
void simmKinematicsEngine::writeMarkerFile(string& aFileName) const
{
   ofstream out;

   out.open(aFileName.c_str());
   out.setf(ios::fixed);
   out.precision(6);

	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	out << "<MarkerSet>" << endl;

	for (int i = 0; i < _bodies.getSize(); i++)
		_bodies[i]->writeMarkers(out);

	out << "</MarkerSet>" << endl;
	out.close();
}

void simmKinematicsEngine::peteTest() const
{
	int i;

	cout << "Kinematics Engine:" << endl;

	cout << "   lengthUnits: " << _lengthUnits.getLabel() << endl;
	cout << "   forceUnits: " << _forceUnits.getLabel() << endl;

	if (_bodies.getSize() < 1)
	{
		cout << "no bodies" << endl;
	}
	else
	{
		for (i = 0; i < _bodies.getSize(); i++)
			_bodies[i]->peteTest();
	}
#if 0
	if (_coordinates.getSize() < 1)
	{
		cout << "no coordinates" << endl;
	}
	else
	{
		for (i = 0; i < _coordinates.getSize(); i++)
			_coordinates[i]->peteTest();
	}

	if (_joints.getSize() < 1)
	{
		cout << "no joints" << endl;
	}
	else
	{
		for (i = 0; i < _joints.getSize(); i++)
			_joints[i]->peteTest();
	}

	_path.peteTest();
#endif
}

//--------------------------------------------------------------------------
// NUMBERS
//--------------------------------------------------------------------------

int simmKinematicsEngine::getNumControls() const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getNumContacts() const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getNumStates() const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getNumPseudoStates() const
{
	// TODO
	return 0;
}

//--------------------------------------------------------------------------
// NAMES
//--------------------------------------------------------------------------

void simmKinematicsEngine::setBodyName(int aIndex, const string &aName)
{
	// TODO
}

string simmKinematicsEngine::getBodyName(int aIndex) const
{
	// TODO
	return "";
}

string simmKinematicsEngine::getCoordinateName(int aIndex) const
{
	// TODO
	return "";
}

string simmKinematicsEngine::getSpeedName(int aIndex) const
{
	// TODO
	return "";
}

string simmKinematicsEngine::getControlName(int aIndex) const
{
	// TODO
	return "";
}

string simmKinematicsEngine::getStateName(int aIndex) const
{
	// TODO
	return "";
}

string simmKinematicsEngine::getPseudoStateName(int aIndex) const
{
	// TODO
	return "";
}

//--------------------------------------------------------------------------
// INDICES FROM NAMES
//--------------------------------------------------------------------------
int simmKinematicsEngine::getBodyIndex(const string &aName) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getCoordinateIndex(const string &aName) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getSpeedIndex(const string &aName) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getControlIndex(const string &aName) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getStateIndex(const string &aName) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getPseudoStateIndex(const string &aName) const
{
	// TODO
	return 0;
}

//--------------------------------------------------------------------------
// SET CURRENT TIME, CONTROLS, AND STATES
//--------------------------------------------------------------------------

void simmKinematicsEngine::set(double aT, const double aX[], const double aY[])
{
	// TODO
}

//--------------------------------------------------------------------------
// INITIAL STATES
//--------------------------------------------------------------------------

void simmKinematicsEngine::setInitialStates(const double aYI[])
{
	// TODO
}

void simmKinematicsEngine::getInitialStates(double rYI[]) const
{
	// TODO
}

double simmKinematicsEngine::getInitialState(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getInitialState(const string &aName) const
{
	// TODO
	return 0.0;
}

//--------------------------------------------------------------------------
// STATES
//--------------------------------------------------------------------------
void simmKinematicsEngine::setStates(const double aY[])
{
	// TODO
}

void simmKinematicsEngine::getStates(double rY[]) const
{
	// TODO
}

double simmKinematicsEngine::getState(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getState(const string &aName) const
{
	// TODO
	return 0.0;
}

//--------------------------------------------------------------------------
// INITIAL PSEUDO STATES
//--------------------------------------------------------------------------

void simmKinematicsEngine::setInitialPseudoStates(const double aYPI[])
{
	// TODO
}

void simmKinematicsEngine::getInitialPseudoStates(double rYPI[]) const
{
	// TODO
}

double simmKinematicsEngine::getInitialPseudoState(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getInitialPseudoState(const string &aName) const
{
	// TODO
	return 0.0;
}


//--------------------------------------------------------------------------
// PSEUDO STATES
//--------------------------------------------------------------------------

void simmKinematicsEngine::setPseudoStates(const double aYP[])
{
	// TODO
}

void simmKinematicsEngine::getPseudoStates(double rYP[]) const
{
	// TODO
}

double simmKinematicsEngine::getPseudoState(int aIndex) const
{
	// TODO
	return 0.0;
}

//--------------------------------------------------------------------------
// CONFIGURATION
//--------------------------------------------------------------------------

void simmKinematicsEngine::setConfiguration(const double aY[])
{
	// TODO
}

void simmKinematicsEngine::setConfiguration(const double aQ[], const double aU[])
{
	// TODO
}

void simmKinematicsEngine::getCoordinateValues(double rQ[]) const
{
	// TODO
}

double simmKinematicsEngine::getCoordinateValue(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getCoordinateValue(const string &aName) const
{
	// TODO
	return 0.0;
}

void simmKinematicsEngine::getSpeeds(double rU[]) const
{
	// TODO
}

double simmKinematicsEngine::getSpeed(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getSpeed(const string &aName) const
{
	// TODO
	return 0.0;
}

void simmKinematicsEngine::getAccelerations(double rDUDT[]) const
{
	// TODO
}

double simmKinematicsEngine::getAcceleration(int aIndex) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getAcceleration(const string &aSpeedName) const
{
	// TODO
	return 0.0;
}

void simmKinematicsEngine::extractConfiguration(const double aY[], double rQ[], double rU[]) const
{
	// TODO
}

//--------------------------------------------------------------------------
// ASSEMBLING THE MODEL
//--------------------------------------------------------------------------
int simmKinematicsEngine::assemble(double aTime, double *rState, int *aLock, double aTol, int aMaxevals, int *rFcnt, int *rErr)
{
	// TODO
	return 0;
}

//--------------------------------------------------------------------------
// SCALE THE MODEL
//--------------------------------------------------------------------------
bool simmKinematicsEngine::scale(const suScaleSet& aScaleSet)
{
	int i, j;

	for (i = 0; i < _bodies.getSize(); i++)
	{
		for (j = 0; j < aScaleSet.getSize(); j++)
		{
			suScale *aScale = aScaleSet.get(j);
			if (_bodies[i]->getName() == aScale->getSegmentName())
			{
				rdArray<double> scaleFactors(1.0, 3);
				aScale->getScaleFactors(scaleFactors);
				_bodies[i]->scale(scaleFactors);
			}
		}
	}

	for (i = 0; i < _joints.getSize(); i++)
		_joints[i]->scale(aScaleSet);

	return true;
}

//--------------------------------------------------------------------------
// GRAVITY
//--------------------------------------------------------------------------
void simmKinematicsEngine::getGravity(double rGrav[3]) const
{
	// TODO
}

void simmKinematicsEngine::setGravity(double aGrav[3])
{
	// TODO
}

//--------------------------------------------------------------------------
// BODY INFORMATION
//--------------------------------------------------------------------------

int simmKinematicsEngine::getGroundBodyIndex() const
{
	for (int i = 0; i < _bodies.getSize(); i++)
	{
		if (_bodies[i] == _groundBody)
			return i;
	}

	return 0;
}

void simmKinematicsEngine::setBodyToJointBodyLocal(int aBody, const double aBTJ[3])
{
	// TODO
}

void simmKinematicsEngine::getBodyToJointBodyLocal(int aBody, double rBTJ[3]) const
{
	// TODO
}

void simmKinematicsEngine::setInboardToJointBodyLocal(int aBody, const double aBTJ[3])
{
	// TODO
}

void simmKinematicsEngine::getInboardToJointBodyLocal(int aBody, double rBTJ[3]) const
{
	// TODO
}

//--------------------------------------------------------------------------
// INERTIA
//--------------------------------------------------------------------------
double simmKinematicsEngine::getMass(int aBody) const
{
	// TODO
	return 0.0;
}

int simmKinematicsEngine::getInertiaBodyLocal(int aBody, double rI[3][3]) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getInertiaBodyLocal(int aBody, double *rI) const
{
	// TODO
	return 0;
}

void simmKinematicsEngine::getSystemInertia(double *rM, double rCOM[3], double rI[3][3]) const
{
	// TODO
}

void simmKinematicsEngine::getSystemInertia(double *rM, double *rCOM, double *rI) const
{
	// TODO
}

//--------------------------------------------------------------------------
// KINEMATICS
//--------------------------------------------------------------------------
void simmKinematicsEngine::getPosition(int aBody, const double aPoint[3], double rPos[3]) const
{
	// TODO
}

void simmKinematicsEngine::getVelocity(int aBody, const double aPoint[3], double rVel[3]) const
{
	// TODO
}

void simmKinematicsEngine::getAcceleration(int aBody, const double aPoint[3], double rAcc[3]) const
{
	// TODO
}

void simmKinematicsEngine::getDirectionCosines(int aBody, double rDirCos[3][3]) const
{
	// TODO
}

void simmKinematicsEngine::getDirectionCosines(int aBody, double *rDirCos) const
{
	// TODO
}

void simmKinematicsEngine::getAngularVelocity(int aBody, double rAngVel[3]) const
{
	// TODO
}

void simmKinematicsEngine::getAngularVelocityBodyLocal(int aBody, double rAngVel[3]) const
{
	// TODO
}

void simmKinematicsEngine::getAngularAcceleration(int aBody, double rAngAcc[3]) const
{
	// TODO
}

void simmKinematicsEngine::getAngularAccelerationBodyLocal(int aBody, double rAngAcc[3]) const
{
	// TODO
}

//--------------------------------------------------------------------------
// LOAD APPLICATION
//--------------------------------------------------------------------------

// FORCES EXPRESSED IN INERTIAL FRAME
void simmKinematicsEngine::applyForce(int aBody, const double aPoint[3], const double aForce[3])
{
	// TODO
}

void simmKinematicsEngine::applyForces(int aN, const int aBodies[], const double aPoints[][3], const double aForces[][3])
{
	// TODO
}

void simmKinematicsEngine::applyForces(int aN, const int aBodies[], const double *aPoints, const double *aForces)
{
	// TODO
}

// FORCES EXPRESSED IN BODY-LOCAL FRAME
void simmKinematicsEngine::applyForceBodyLocal(int aBody, const double aPoint[3], const double aForce[3])
{
	// TODO
}

void simmKinematicsEngine::applyForcesBodyLocal(int aN, const int aBodies[], const double aPoints[][3], const double aForces[][3])
{
	// TODO
}

void simmKinematicsEngine::applyForcesBodyLocal(int aN, const int aBodies[], const double *aPoints, const double *aForces)
{
	// TODO
}

// TORQUES EXPRESSED IN INERTIAL FRAME
void simmKinematicsEngine::applyTorque(int aBody, const double aTorque[3])
{
	// TODO
}

void simmKinematicsEngine::applyTorques(int aN, const int aBodies[], const double aTorques[][3])
{
	// TODO
}

void simmKinematicsEngine::applyTorques(int aN, const int aBodies[], const double *aTorques)
{
	// TODO
}

// TORQUES EXPRESSED IN BODY-LOCAL FRAME (sdbodyt())
void simmKinematicsEngine::applyTorqueBodyLocal(int aBody, const double aTorque[3])
{
	// TODO
}

void simmKinematicsEngine::applyTorquesBodyLocal(int aN, const int aBodies[], const double aTorques[][3])
{
	// TODO
}

void simmKinematicsEngine::applyTorquesBodyLocal(int aN, const int aBodies[], const double *aTorques)
{
	// TODO
}

// GENERALIZED FORCES
void simmKinematicsEngine::applyGeneralizedForce(int aU, double aF)
{
	// TODO
}

void simmKinematicsEngine::applyGeneralizedForces(const double aF[])
{
	// TODO
}

void simmKinematicsEngine::applyGeneralizedForces(int aN, const int aU[], const double aF[])
{
	// TODO
}

//--------------------------------------------------------------------------
// LOAD ACCESS AND COMPUTATION
//--------------------------------------------------------------------------

double simmKinematicsEngine::getNetAppliedGeneralizedForce(int aU) const
{
	// TODO
	return 0.0;
}

void simmKinematicsEngine::computeGeneralizedForces(double aDUDT[], double rF[]) const
{
	// TODO
}

void simmKinematicsEngine::computeReactions(double rForces[][3], double rTorques[][3]) const
{
	// TODO
}


//--------------------------------------------------------------------------
// EQUATIONS OF MOTION
//--------------------------------------------------------------------------

void simmKinematicsEngine::formMassMatrix(double *rI)
{
	// TODO
}

void simmKinematicsEngine::formEulerTransform(int aBody, double *rE) const
{
	// TODO
}

void simmKinematicsEngine::formJacobianTranslation(int aBody, const double aPoint[3], double *rJ, int aRefBody) const
{
	// TODO
}

void simmKinematicsEngine::formJacobianOrientation(int aBody, double *rJ0, int aRefBody) const
{
	// TODO
}

void simmKinematicsEngine::formJacobianEuler(int aBody, double *rJE, int aRefBody) const
{
	// TODO
}

//--------------------------------------------------------------------------
// DERIVATIVES
//--------------------------------------------------------------------------

int simmKinematicsEngine::computeAccelerations(double *dqdt, double *dudt)
{
	// TODO
	return 0;
}

void simmKinematicsEngine::computeAuxiliaryDerivatives(double *dydt)
{
	// TODO
}

//--------------------------------------------------------------------------
// UTILITY
//--------------------------------------------------------------------------

void simmKinematicsEngine::transform(int aBody1, const double aVec1[3], int aBody2, double rVec2[3]) const
{
	// TODO
}

void simmKinematicsEngine::transformPosition(int aBody, const double aPos[3], double rPos[3]) const
{
	// TODO
}

void simmKinematicsEngine::convertQuaternionsToAngles(double *aQ, double *rQAng) const
{
	// TODO
}

void simmKinematicsEngine::convertQuaternionsToAngles(rdStorage *rQStore) const
{
	// TODO
}

void simmKinematicsEngine::convertAnglesToQuaternions(double *aQAng, double *rQ) const
{
	// TODO
}

void simmKinematicsEngine::convertAnglesToQuaternions(rdStorage *rQStore) const
{
	// TODO
}

void simmKinematicsEngine::convertRadiansToDegrees(double *aQRad, double *rQDeg) const
{
	// TODO
}

void simmKinematicsEngine::convertRadiansToDegrees(rdStorage *rQStore) const
{
	// TODO
}

void simmKinematicsEngine::convertDegreesToRadians(double *aQDeg, double *rQRad) const
{
	// TODO
}

void simmKinematicsEngine::convertDegreesToRadians(rdStorage *rQStore) const
{
	// TODO
}

void simmKinematicsEngine::convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, double rDirCos[3][3]) const
{
	// TODO
}

void simmKinematicsEngine::convertAnglesToDirectionCosines(double aE1, double aE2, double aE3, double *rDirCos) const
{
	// TODO
}

void simmKinematicsEngine::convertDirectionCosinesToAngles(double aDirCos[3][3], double *rE1, double *rE2, double *rE3) const
{
	// TODO
}

void simmKinematicsEngine::convertDirectionCosinesToAngles(double *aDirCos, double *rE1, double *rE2, double *rE3) const
{
	// TODO
}

void simmKinematicsEngine::convertDirectionCosinesToQuaternions(double aDirCos[3][3], double *rQ1, double *rQ2, double *rQ3, double *rQ4) const
{
	// TODO
}

void simmKinematicsEngine::convertDirectionCosinesToQuaternions(double *aDirCos, double *rQ1, double *rQ2, double *rQ3, double *rQ4) const
{
	// TODO
}

void simmKinematicsEngine::convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, double rDirCos[3][3]) const
{
	// TODO
}

void simmKinematicsEngine::convertQuaternionsToDirectionCosines(double aQ1, double aQ2, double aQ3, double aQ4, double *rDirCos) const
{
	// TODO
}

//--------------------------------------------------------------------------
// CONTACT
//--------------------------------------------------------------------------
void simmKinematicsEngine::computeContact()
{
	// TODO
}

void simmKinematicsEngine::applyContactForce(int aID)
{
	// TODO
}

void simmKinematicsEngine::applyContactForces()
{
	// TODO
}

int simmKinematicsEngine::getContactBodyA(int aID) const
{
	// TODO
	return 0;
}

int simmKinematicsEngine::getContactBodyB(int aID) const
{
	// TODO
	return 0;
}

void simmKinematicsEngine::setContactPointA(int aID, const double aPoint[3])
{
	// TODO
}

void simmKinematicsEngine::getContactPointA(int aID, double rPoint[3]) const
{
	// TODO
}

void simmKinematicsEngine::setContactPointB(int aID, const double aPoint[3])
{
	// TODO
}

void simmKinematicsEngine::getContactPointB(int aID, double rPoint[3]) const
{
	// TODO
}

void simmKinematicsEngine::getContactForce(int aID, double rF[3]) const
{
	// TODO
}

void simmKinematicsEngine::getContactNormalForce(int aID, double rFP[3], double rFV[3], double rF[3]) const
{
	// TODO
}

void simmKinematicsEngine::getContactTangentForce(int aID, double rFP[3], double rFV[3], double rF[3]) const
{
	// TODO
}

void simmKinematicsEngine::getContactStiffness(int aID, const double aDX[3], double rDF[3]) const
{
	// TODO
}

void simmKinematicsEngine::getContactViscosity(int aID, const double aDV[3], double rDF[3]) const
{
	// TODO
}

void simmKinematicsEngine::getContactFrictionCorrection(int aID, double aDFFric[3]) const
{
	// TODO
}

double simmKinematicsEngine::getContactForce(int aID) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getContactSpeed(int aID) const
{
	// TODO
	return 0.0;
}

double simmKinematicsEngine::getContactPower(int aID) const
{
	// TODO
	return 0.0;
}
