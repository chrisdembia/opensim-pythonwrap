#include "suRange.h"

using namespace std;
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suRange::~suRange(void)
{
}
//_____________________________________________________________________________
/**
 * Default constructor of an suRange
 */
suRange::suRange():
_min(_propMin.getValueDbl()),
_max(_propMax.getValueDbl())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aRange range to copy.
 */
suRange::suRange(const suRange &aRange) :
rdObject(aRange),
_min(_propMin.getValueDbl()),
_max(_propMax.getValueDbl())
{
	setNull();

	// ASSIGN
	*this = aRange;
}
//_____________________________________________________________________________
/**
 * Construct an suRange from DOMElement.
 *
 * @param aElement to use for construction
 */
suRange::suRange(DOMElement *aElement) :
rdObject(aElement),
_min(_propMin.getValueDbl()),
_max(_propMax.getValueDbl())
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
rdObject* suRange::
copy() const
{
	rdObject *object = new suRange(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Create object from DOMElement.
 *
 * @param aElement XMLnode to construct suRange from.
 */

rdObject* suRange::
copy(DOMElement *aElement) const
{
	suRange *m = new suRange(aElement);
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
suRange& suRange::
operator=(const suRange &aRange)
{
	// BASE CLASS
	rdObject::operator=(aRange);
	_min = aRange._min;
	_max = aRange._max;

	return(*this);
}

//=============================================================================
// GET AND SET
//=============================================================================
//_____________________________________________________________________________
/**
 * Range min. get
 */
const double suRange::getMin() const
{
	return _min;
}
//_____________________________________________________________________________
/**
 * Range max. get
 */
const double suRange::getMax() const
{
	return _max;
}

//_____________________________________________________________________________
/**
 * Range min. set
 */
void suRange::setMin(const double aMin)
{
	_min = aMin;
}
//_____________________________________________________________________________
/**
 * Range max. set
 */
void suRange::setMax(const double aMax)
{
	_max = aMax;
}


void suRange::setNull()
{
	setType("suRange");
	setName("");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  
 */
void suRange::
setupProperties()
{
	// _min
	_propMin.setName("min");
	_propMin.setValue(0.0);
	_propertySet.append( &_propMin );
	// _max
	_propMax.setName("max");
	_propMax.setValue(1.0);
	_propertySet.append( &_propMax );


}
