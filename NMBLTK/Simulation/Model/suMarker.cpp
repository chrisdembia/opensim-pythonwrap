#include "suMarker.h"
#include <NMBLTK/Simulation/Model/rdBody.h>
using namespace std;
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suMarker::~suMarker(void)
{
}
//_____________________________________________________________________________
/**
 * Default constructor of an suMarker
 */
suMarker::suMarker():
rdVisibleObject(),
_markerLocation(_propMarkerLocation.getValueDblArray()),
_referenceSegmentName(_propReferenceSegmentName.getValueStr()),
_markerWeight(_propMarkerWeight.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aBody Body to copy.
 */
suMarker::suMarker(const suMarker &aMarker) :
rdVisibleObject(aMarker),
_markerLocation(_propMarkerLocation.getValueDblArray()),
_referenceSegmentName(_propReferenceSegmentName.getValueStr()),
_markerWeight(_propMarkerWeight.getValueDbl())
{
	setNull();

	// ASSIGN
	*this = aMarker;
}
//_____________________________________________________________________________
/**
 * Construct an suMarker from DOMElement.
 *
 * @param aElement to use for construction
 */
suMarker::suMarker(DOMElement *aElement) :
rdVisibleObject(aElement),
_markerLocation(_propMarkerLocation.getValueDblArray()),
_referenceSegmentName(_propReferenceSegmentName.getValueStr()),
_markerWeight(_propMarkerWeight.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct and return a copy of this object.
 *
 * The object is allocated using the new operator, so the caller is
 * responsible for deleting the returned object.
 *
 * @return Copy of this object.
 */
rdObject* suMarker::
copy() const
{
	rdObject *object = new suMarker(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Create object from DOMElement.
 *
 * @param aElement XMLnode to construct suMarker from.
 */

rdObject* suMarker::
copy(DOMElement *aElement) const
{
	suMarker *m = new suMarker(aElement);
	*m = *this;
	m->updateFromXMLNode();
	return(m);
}
//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.
 *
 * @return Reference to this object.
 */
suMarker& suMarker::
operator=(const suMarker &aMarker)
{
	// BASE CLASS
	rdVisibleObject::operator=(aMarker);
	rdArray<double>	aLocation(0.0);
	aMarker.getLocation(aLocation);
	setLocation(aLocation);
	_referenceSegmentName = aMarker.getReferenceSegmentName();
	_markerWeight = aMarker.getWeight();

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get the value of marker weight
 */
const double suMarker::
getWeight() const
{
	return _markerWeight;
}
//_____________________________________________________________________________
/**
 * Set the value of marker weight
 */
void suMarker::
setWeight(const double aWeight)
{
	_markerWeight = aWeight;
}
//_____________________________________________________________________________
/**
 * Get the name of the segment that the marker lives on
 */
const std::string& suMarker::
getReferenceSegmentName() const
{
	return _referenceSegmentName;
}
//_____________________________________________________________________________
/**
 * Set the name of the segment that the marker lives on
 */
void suMarker::
setRefSegment(const int aBodyIndex)
{
	_refSegmentForMarker=aBodyIndex;
}
//_____________________________________________________________________________
/**
 * Get the index of the segment that the marker lives on
 */
const int suMarker::
getRefSegment() const
{
	return _refSegmentForMarker;
}
//_____________________________________________________________________________
/**
 * Get the location of the marker in reference segment frame
 */
void suMarker::
getLocation(rdArray<double>& aLocation) const
{
	for(int i=0; i < aLocation.getSize(); i++)
	aLocation[i] = _markerLocation[i];
}
//_____________________________________________________________________________
/**
 * Set the location of the marker in reference segment frame
 */
void suMarker::
setLocation(rdArray<double>& aLocation)
{
	for(int i=0; i < aLocation.getSize(); i++)
	_markerLocation[i] = aLocation[i];
}
//_____________________________________________________________________________
/**
 * initialize object to null.  
 */
void suMarker::
setNull()
{
	setType("suMarker");
	setName("unnamed_marker");
	setupProperties();
	_refSegmentForMarker=-2;	// SDFast uses -1 for ground
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  
 */
void suMarker::
setupProperties()
{
	rdArray<double> zero3(0.0, 3);	

	// _markerLocation
	_propMarkerLocation.setName("marker_location");
	_propMarkerLocation.setValue(zero3);
	_propertySet.append( &_propMarkerLocation );

	// reference_segment
	_propReferenceSegmentName.setName("ref_segment");
	_propReferenceSegmentName.setValue("unnamed_segment");
	_propertySet.append( &_propReferenceSegmentName );

	// Weight
	_propMarkerWeight.setName("weight");
	_propMarkerWeight.setValue(1.0);
	_propertySet.append( &_propMarkerWeight );

}
//_____________________________________________________________________________
/**
 * Scale marker location by indicate dscale factors.  
 */
void suMarker::
scaleBy(rdArray<double>& aScales)
{
	for(int i=0; i < aScales.getSize(); i++)
	_markerLocation[i] *= aScales[i];

}

void suMarker::
update(const rdObject& aObject, rdEvent& aEvent)
{
//	const rdBody& refBody = dynamic_cast<const rdBody &>(aObject);
	
}
