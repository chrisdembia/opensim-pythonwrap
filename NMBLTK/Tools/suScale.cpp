#include "suScale.h"

using namespace std;
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suScale::~suScale(void)
{
}
//_____________________________________________________________________________
/**
 * Default constructor of an suScale
 */
suScale::suScale():
_segmentName(_propSegmentName.getValueStr()),
_scaleFactors(_propScaleFactors.getValueDblArray()),
_apply(_propApply.getValueBool())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param an suScale to copy
 */
suScale::suScale(const suScale &aScale) :
rdObject(aScale),
_segmentName(_propSegmentName.getValueStr()),
_scaleFactors(_propScaleFactors.getValueDblArray()),
_apply(_propApply.getValueBool())
{
	setNull();

	// ASSIGN
	*this = aScale;
}
//_____________________________________________________________________________
/**
 * Construct an suScale from DOMElement.
 *
 * @param aElement to use for construction
 */
suScale::suScale(DOMElement *aElement) :
rdObject(aElement),
_segmentName(_propSegmentName.getValueStr()),
_scaleFactors(_propScaleFactors.getValueDblArray()),
_apply(_propApply.getValueBool())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Constructor of a scaleSet from a file.
 */
suScale::suScale(const string& scaleFileName):
rdObject(scaleFileName),
_segmentName(_propSegmentName.getValueStr()),
_scaleFactors(_propScaleFactors.getValueDblArray()),
_apply(_propApply.getValueBool())
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
rdObject* suScale::
copy() const
{
	rdObject *object = new suScale(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Create object from DOMElement.
 *
 * @param aElement XMLnode to construct suScale from.
 */

rdObject* suScale::
copy(DOMElement *aElement) const
{
	suScale *m = new suScale(aElement);
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
suScale& suScale::
operator=(const suScale &aScale)
{
	// BASE CLASS
	_segmentName = aScale.getSegmentName();
	aScale.getScaleFactors(_scaleFactors);
	_apply = aScale.getApply();

	return(*this);
}


void suScale::setNull()
{
	setType("suScale");
	setName("");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  
 */
void suScale::
setupProperties()
{
	rdArray<double> one3(1.0, 3);	

	// scale factors
	_propScaleFactors.setName("scales");
	_propScaleFactors.setValue(one3);
	_propertySet.append( &_propScaleFactors );

	// segment name
	_propSegmentName.setName("segment");
	_propSegmentName.setValue("unnamed_segment");
	_propertySet.append( &_propSegmentName );

	// whether or not to apply the scale
	_propApply.setName("apply");
	_propApply.setValue(true);
	_propertySet.append(&_propApply);
}
//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Get segment name
 */
const std::string& suScale::
getSegmentName() const
{
	return _segmentName;
}
//_____________________________________________________________________________
/**
 * Set the value of scale factors
 */
void suScale::
getScaleFactors(rdArray<double>& aScaleFactors) const
{
	aScaleFactors = _scaleFactors;
}

//_____________________________________________________________________________
/**
 * Set segment name
 */
void suScale::
setSegmentName(const string& aSegmentName)
{
	_segmentName = aSegmentName;
}
//_____________________________________________________________________________
/**
 * Set scale factors
 */
void suScale::
setScaleFactors(rdArray<double>& aScaleFactors)
{
	_scaleFactors = aScaleFactors;
}