#include "suGenCoord.h"
#include <RD/Tools/suRange.h>

using namespace std;
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
suGenCoord::~suGenCoord(void)
{
}
//_____________________________________________________________________________
/**
 * Default constructor of an suGenCoord
 */
suGenCoord::suGenCoord():
_propGencoordRange(rdPropertyObj("Range", suRange())),
_range((suRange &)_propGencoordRange.getValueObj()),
_inDegrees(_propInDegrees.getValueBool())
{
	setNull();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * @param aGencoord Gencoord to copy.
 */
suGenCoord::suGenCoord(const suGenCoord &aGencoord) :
rdObject(aGencoord),
_propGencoordRange(rdPropertyObj("Range", suRange())),
_range((suRange &)_propGencoordRange.getValueObj()),
_inDegrees(_propInDegrees.getValueBool())
{
	setNull();

	// ASSIGN
	*this = aGencoord;
}
//_____________________________________________________________________________
/**
 * Construct an suGenCoord from DOMElement.
 *
 * @param aElement to use for construction
 */
suGenCoord::suGenCoord(DOMElement *aElement) :
rdObject(aElement),
_propGencoordRange(rdPropertyObj("Range", suRange())),
_range((suRange &)_propGencoordRange.getValueObj()),
_inDegrees(_propInDegrees.getValueBool())
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
rdObject* suGenCoord::
copy() const
{
	rdObject *object = new suGenCoord(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Create object from DOMElement.
 *
 * @param aElement XMLnode to construct suGenCoord from.
 */

rdObject* suGenCoord::
copy(DOMElement *aElement) const
{
	suGenCoord *m = new suGenCoord(aElement);
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
suGenCoord& suGenCoord::
operator=(const suGenCoord &aGencoord)
{
	// BASE CLASS
	rdObject::operator=(aGencoord);
	_range = aGencoord.getRange();
	_inDegrees = aGencoord.getInDegrees();
	return(*this);
}



void suGenCoord::setNull()
{
	setType("suGenCoord");
	setName("");
	setupProperties();
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  
 */
void suGenCoord::
setupProperties()
{
	// Range
	_propertySet.append( &_propGencoordRange );
	// InDegrees
	_propInDegrees.setName("InDegrees");
	_propInDegrees.setValue(true);
	_propertySet.append( &_propInDegrees );


}
//=============================================================================
// GET AND SET
//=============================================================================
//------------- Get range -------------------------------------------
/**
 * gets the range for the suGenCoord
 */
const suRange &suGenCoord::
	getRange() const
{
	return _range;
}
//_____________________________________________________________________________
/**
 * gets the range for the suGenCoord, const object
 */
suRange &suGenCoord::
getRange()
{
	return _range;
}
//_____________________________________________________________________________
/**
 * Sets the range for the suGenCoord
 */
void suGenCoord::
setRange(const suRange &aRange)
{
	_range = aRange;
}
//_____________________________________________________________________________
/**
 * Get inDegrees attribute, const object
 */
const bool suGenCoord::
getInDegrees() const
{
	return _inDegrees;
}
//_____________________________________________________________________________
/**
 * Get inDegrees attribute
 */
bool suGenCoord::
getInDegrees()
{
	return _inDegrees;
}
//_____________________________________________________________________________
/**
 * Set inDegrees attribute
 */
void suGenCoord::
setInDegrees(const bool &aInDegrees)
{
	_inDegrees = aInDegrees;
}
