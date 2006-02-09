// simmMuscle.cpp
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
#include "simmMuscle.h"
#include "simmMuscleGroup.h"
#include "simmMuscleViaPoint.h"
#include "simmModel.h"
#include "simmKinematicsEngine.h"

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
simmMuscle::simmMuscle() :
   rdActuator(0, 0, 0),
   _attachments((rdArrayPtrs<simmMusclePoint>&)_attachmentsProp.getValueObjArray()),
	_maxIsometricForce(_maxIsometricForceProp.getValueDbl()),
	_optimalFiberLength(_optimalFiberLengthProp.getValueDbl()),
	_tendonSlackLength(_tendonSlackLengthProp.getValueDbl()),
	_pennationAngle(_pennationAngleProp.getValueDbl()),
	_maxContractionVelocity(_maxContractionVelocityProp.getValueDbl()),
	_tendonForceLengthCurve((rdArrayPtrs<rdFunction>&)_tendonForceLengthCurveProp.getValueObjArray()),
	_activeForceLengthCurve((rdArrayPtrs<rdFunction>&)_activeForceLengthCurveProp.getValueObjArray()),
	_passiveForceLengthCurve((rdArrayPtrs<rdFunction>&)_passiveForceLengthCurveProp.getValueObjArray()),
	_forceVelocityCurve((rdArrayPtrs<rdFunction>&)_forceVelocityCurveProp.getValueObjArray()),
	_groupNames(_groupNamesProp.getValueStrArray()),
	_groups(NULL)
{
	setNull();

}
//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
simmMuscle::simmMuscle(DOMElement *aElement) :
   rdActuator(0, 0, 0, aElement),
   _attachments((rdArrayPtrs<simmMusclePoint>&)_attachmentsProp.getValueObjArray()),
	_maxIsometricForce(_maxIsometricForceProp.getValueDbl()),
	_optimalFiberLength(_optimalFiberLengthProp.getValueDbl()),
	_tendonSlackLength(_tendonSlackLengthProp.getValueDbl()),
	_pennationAngle(_pennationAngleProp.getValueDbl()),
	_maxContractionVelocity(_maxContractionVelocityProp.getValueDbl()),
	_tendonForceLengthCurve((rdArrayPtrs<rdFunction>&)_tendonForceLengthCurveProp.getValueObjArray()),
	_activeForceLengthCurve((rdArrayPtrs<rdFunction>&)_activeForceLengthCurveProp.getValueObjArray()),
	_passiveForceLengthCurve((rdArrayPtrs<rdFunction>&)_passiveForceLengthCurveProp.getValueObjArray()),
	_forceVelocityCurve((rdArrayPtrs<rdFunction>&)_forceVelocityCurveProp.getValueObjArray()),
	_groupNames(_groupNamesProp.getValueStrArray()),
	_groups(NULL)
{
	setNull();

	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Destructor.
 */
simmMuscle::~simmMuscle()
{
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aMuscle simmMuscle to be copied.
 */
simmMuscle::simmMuscle(const simmMuscle &aMuscle) :
   rdActuator(aMuscle),
   _attachments((rdArrayPtrs<simmMusclePoint>&)_attachmentsProp.getValueObjArray()),
	_maxIsometricForce(_maxIsometricForceProp.getValueDbl()),
	_optimalFiberLength(_optimalFiberLengthProp.getValueDbl()),
	_tendonSlackLength(_tendonSlackLengthProp.getValueDbl()),
	_pennationAngle(_pennationAngleProp.getValueDbl()),
	_maxContractionVelocity(_maxContractionVelocityProp.getValueDbl()),
	_tendonForceLengthCurve((rdArrayPtrs<rdFunction>&)_tendonForceLengthCurveProp.getValueObjArray()),
	_activeForceLengthCurve((rdArrayPtrs<rdFunction>&)_activeForceLengthCurveProp.getValueObjArray()),
	_passiveForceLengthCurve((rdArrayPtrs<rdFunction>&)_passiveForceLengthCurveProp.getValueObjArray()),
	_forceVelocityCurve((rdArrayPtrs<rdFunction>&)_forceVelocityCurveProp.getValueObjArray()),
	_groupNames(_groupNamesProp.getValueStrArray()),
	_groups(NULL)
{
	setupProperties();
	copyData(aMuscle);
}
//_____________________________________________________________________________
/**
 * Copy this muscle point and return a pointer to the copy.
 * The copy constructor for this class is used.
 *
 * @return Pointer to a copy of this simmMuscle.
 */
rdObject* simmMuscle::copy() const
{
	simmMuscle *musc = new simmMuscle(*this);
	return(musc);
}
//_____________________________________________________________________________
/**
 * Copy this simmMuscle and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using
 * simmMuscle::simmMuscle(DOMElement*) in order to establish the
 * relationship of the simmMuscle object with the XML node. Then, the
 * assignment operator is used to set all data members of the copy to the
 * values of this simmMuscle object. Finally, the data members of the copy are
 * updated using simmMuscle::updateFromXMLNode().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this simmMuscle.
 */
rdObject* simmMuscle::copy(DOMElement *aElement) const
{
	simmMuscle *pt = new simmMuscle(aElement);
	*pt = *this;
	pt->updateFromXMLNode();
	return(pt);
}

void simmMuscle::copyData(const simmMuscle &aMuscle)
{
	_attachments = aMuscle.getAttachmentArray();
	_maxIsometricForce = aMuscle._maxIsometricForce;
	_optimalFiberLength = aMuscle._optimalFiberLength;
	_tendonSlackLength = aMuscle._tendonSlackLength;
	_pennationAngle = aMuscle._pennationAngle;
	_maxContractionVelocity = aMuscle._maxContractionVelocity;
	_tendonForceLengthCurve = aMuscle._tendonForceLengthCurve;
	_activeForceLengthCurve = aMuscle._activeForceLengthCurve;
	_passiveForceLengthCurve = aMuscle._passiveForceLengthCurve;
	_forceVelocityCurve = aMuscle._forceVelocityCurve;
	_groupNames = aMuscle._groupNames;
	_groups = aMuscle._groups;
}


//=============================================================================
// CONSTRUCTION
//=============================================================================
//_____________________________________________________________________________
/**
 * Set the data members of this simmMuscle to their null values.
 */
void simmMuscle::setNull()
{
	setupProperties();
	setType("muscle");
	setName("");
}
//_____________________________________________________________________________
/**
 * Connect properties to local pointers.
 */
void simmMuscle::setupProperties()
{
	_attachmentsProp.setName("attachments");
	rdArrayPtrs<rdObject> pts;
	_attachmentsProp.setValue(pts);
	_propertySet.append(&_attachmentsProp);

	_maxIsometricForceProp.setName("maxIsometricForce");
	_maxIsometricForceProp.setValue(0.0);
	_propertySet.append(&_maxIsometricForceProp);

	_optimalFiberLengthProp.setName("optimalFiberLength");
	_optimalFiberLengthProp.setValue(0.0);
	_propertySet.append(&_optimalFiberLengthProp);

	_tendonSlackLengthProp.setName("tendonSlackLength");
	_tendonSlackLengthProp.setValue(0.0);
	_propertySet.append(&_tendonSlackLengthProp);

	_pennationAngleProp.setName("pennationAngle");
	_pennationAngleProp.setValue(0.0);
	_propertySet.append(&_pennationAngleProp);

	_maxContractionVelocityProp.setName("maxContractionVelocity");
	_maxContractionVelocityProp.setValue(0.0);
	_propertySet.append(&_maxContractionVelocityProp);

	rdArrayPtrs<rdObject> func;

	_tendonForceLengthCurveProp.setName("tendonForceLengthCurves");
	_tendonForceLengthCurveProp.setValue(func);
	_propertySet.append(&_tendonForceLengthCurveProp);

	_activeForceLengthCurveProp.setName("activeForceLengthCurves");
	_activeForceLengthCurveProp.setValue(func);
	_propertySet.append(&_activeForceLengthCurveProp);

	_passiveForceLengthCurveProp.setName("passiveForceLengthCurves");
	_passiveForceLengthCurveProp.setValue(func);
	_propertySet.append(&_passiveForceLengthCurveProp);

	_forceVelocityCurveProp.setName("forceVelocityCurves");
	_forceVelocityCurveProp.setValue(func);
	_propertySet.append(&_forceVelocityCurveProp);

	_groupNamesProp.setName("groups");
	_propertySet.append(&_groupNamesProp);
}

simmMuscle& simmMuscle::operator=(const simmMuscle &aMuscle)
{
	// BASE CLASS
	rdActuator::operator=(aMuscle);

	copyData(aMuscle);

	return(*this);
}

void simmMuscle::registerTypes()
{
	rdObject::RegisterType(simmMusclePoint());
	rdObject::RegisterType(simmMuscleViaPoint());
}

void simmMuscle::scale(const suScaleSet& aScaleSet)
{
	// TODO: this method should possibly scale force
	// parameters (e.g., resting tendon length based
	// on total muscle length change).

	for (int i = 0; i < _attachments.getSize(); i++)
	{
		const string& bodyName = _attachments[i]->getBodyName();
		for (int j = 0; j < aScaleSet.getSize(); j++)
		{
			suScale *aScale = aScaleSet.get(j);
			if (bodyName == aScale->getSegmentName())
			{
				rdArray<double> scaleFactors(1.0, 3);
				aScale->getScaleFactors(scaleFactors);
				_attachments[i]->scale(scaleFactors);
			}
		}
	}
}

/* Perform some set up functions that happen after the
 * object has been deserialized or copied.
 */
void simmMuscle::setup(simmModel* model, simmKinematicsEngine* ke)
{
	int i;

	for (i = 0; i < _attachments.getSize(); i++)
		_attachments[i]->setup(model, ke);

	_groups.setSize(0);
	for (i = 0; i < _groupNames.getSize(); i++)
		_groups.append(model->enterGroup(_groupNames[i]));
}

double simmMuscle::getLength(simmKinematicsEngine* ke) const
{
	double length = 0.0;
	simmMusclePoint *start, *end;

	//check wrapping??

   for (int i = 0; i < _attachments.getSize() - 1; i++)
   {
		start = _attachments[i];
      end = _attachments[i+1];
#if 0
      /* If both points are wrap points on the same wrap object, then this muscle
       * segment wraps over the surface of a wrap object, so just add in the
       * pre-calculated distance.
       */
      if (dynamic_cast<simmMuscleWrapPoint&>start &&
			 dynamic_cast<simmMuscleWrapPoint&>end &&
			 start.getWrapObject() == end.getWrapObject())
      {
         length += end.getWrapDistance();
      }
      else
      {
         length += ke->calcDistance(start->getAttachment(), start->getBody(), end->getAttachment(), end->getBody());
      }
#else
		length += ke->calcDistance(start->getAttachment(), start->getBody(), end->getAttachment(), end->getBody());
#endif
   }

	return length;
}

void simmMuscle::writeSIMM(ofstream& out) const
{
	out << "beginmuscle " << getName() << endl;

	out << "beginpoints" << endl;
	for (int i = 0; i < _attachments.getSize(); i++)
		_attachments[i]->writeSIMM(out);
	out << "endpoints" << endl;

	if (_groupNames.getSize() > 0)
	{
		out << "begingroups" << endl;
		for (int i = 0; i < _groupNames.getSize(); i++)
			out << " " << _groupNames[i];
		out << endl << "endgroups" << endl;
	}

	out << "max_force " << _maxIsometricForce << endl;
	out << "optimal_fiber_length " << _optimalFiberLength << endl;
	out << "tendon_slack_length " << _tendonSlackLength << endl;
	out << "pennation_angle " << _pennationAngle << endl;
	out << "max_contraction_velocity " << _maxContractionVelocity << endl;

	simmNatCubicSpline* ncs;

	if (_tendonForceLengthCurve.getSize() > 0)
		if (ncs = dynamic_cast<simmNatCubicSpline*>(_tendonForceLengthCurve[0]))
			ncs->writeSIMM(out, string("tendonforcelengthcurve"));

	if (_activeForceLengthCurve.getSize() > 0)
		if (ncs = dynamic_cast<simmNatCubicSpline*>(_activeForceLengthCurve[0]))
			ncs->writeSIMM(out, string("activeforcelengthcurve"));

	if (_passiveForceLengthCurve.getSize() > 0)
		if (ncs = dynamic_cast<simmNatCubicSpline*>(_passiveForceLengthCurve[0]))
			ncs->writeSIMM(out, string("passiveforcelengthcurve"));

	if (_forceVelocityCurve.getSize() > 0)
		if (ncs = dynamic_cast<simmNatCubicSpline*>(_forceVelocityCurve[0]))
			ncs->writeSIMM(out, string("forcevelocitycurve"));

	out << "endmuscle" << endl << endl;
}

void simmMuscle::peteTest(simmKinematicsEngine* ke) const
{
	int i;

	cout << "Muscle: " << getName() << endl;
	for (i = 0; i < _attachments.getSize(); i++)
		_attachments[i]->peteTest();
	cout << "   groups: ";
	for (i = 0; i < _groupNames.getSize(); i++)
		cout << _groupNames[i] << " ";
	cout << endl;
	cout << "   maxIsometricForce: " << _maxIsometricForce << endl;
	cout << "   optimalFiberLength: " << _optimalFiberLength << endl;
	cout << "   tendonSlackLength: " << _tendonSlackLength << endl;
	cout << "   pennationAngle: " << _pennationAngle << endl;
	cout << "   maxContractionVelocity: " << _maxContractionVelocity << endl;
	if (_tendonForceLengthCurve.getSize() > 0)
		cout << "   tendonForceLengthCurve: " << *(_tendonForceLengthCurve[0]) << endl;
	if (_activeForceLengthCurve.getSize() > 0)
		cout << "   activeForceLengthCurve: " << *(_activeForceLengthCurve[0]) << endl;
	if (_passiveForceLengthCurve.getSize() > 0)
		cout << "   passiveForceLengthCurve: " << *(_passiveForceLengthCurve[0]) << endl;
	if (_forceVelocityCurve.getSize() > 0)
		cout << "   forceVelocityCurve: " << *(_forceVelocityCurve[0]) << endl;
	cout << "   current length: " << getLength(ke) << endl;
}
