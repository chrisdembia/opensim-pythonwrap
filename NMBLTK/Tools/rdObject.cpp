// rdObject.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002-2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//============================================================================
// INCLUDES
//============================================================================
#include "rdObject.h"
#include "rdException.h"
#include "rdProperty.h"
#include "rdPropertyInt.h"
#include "rdPropertyStr.h"

using namespace std;

//=============================================================================
// STATICS
//=============================================================================
rdArrayPtrs<rdObject> rdObject::_Types;
rdArray<XMLCh *> rdObject::_typeNames(0);

stringsToObjects rdObject::_mapTypesToDefaultObjects;
defaultsReadFromFile	rdObject::_defaultsReadFromFile;
bool rdObject::_serializeAllDefaults=false;

#include <vector>
#include <algorithm>  // Include algorithms

static vector<std::string> recognizedTypes;

//============================================================================
// CONSTANTS
//============================================================================
const string rdObject::DEFAULT_NAME(rdObjectDEFAULT_NAME);
static const bool rdObject_DEBUG = false;

void stripExtraWhiteSpace(std::string &aBuffer)
{
	int front = aBuffer.find_first_not_of(" \t\r\n");
	if(front==-1) {
		aBuffer = "";
	} else if (front > 0) {
		aBuffer.erase(0, front);
	}

	int back = aBuffer.find_last_not_of(" \t\r\n");
	if (back < aBuffer.size() - 1)
		aBuffer.erase(back + 1);
}


//=============================================================================
// CONSTRUCTOR(S)
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
rdObject::~rdObject()
{
	if(_document!=NULL) { delete _document;  _document=NULL; }
	if (_observable!=0) { delete _observable; _observable=0; }
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
rdObject::rdObject()
{
	setNull();
}

//_____________________________________________________________________________
/**
 * Construct an object from file.
 *
 * The object is constructed from the root element of the XML document.
 * The type of object is the tag name of the XML root element.
 *
 * @param aFileName File name of the document.
 */
rdObject::rdObject(const string &aFileName)
{
	// INITIALIZATION
	setNull();

	// CREATE DOCUMENT
	_document = new rdXMLDocument(aFileName);

	//try {
	// CONSTRUCT BASED ON ROOT ELEMENT
	DOMDocument *doc = _document->getDOMDocument();
	if(doc==0) {
		string msg =
			"rdObject: ERR- Failed to construct object from file " + aFileName;
		throw rdException(msg,__FILE__,__LINE__);
	}

	// GET DOCUMENT ELEMENT
	_node = doc->getDocumentElement();

	// Build array of type names to avoid calling xmlTranscode repeatedly with 
	// The side effect of allocating and releasing buffers. 
	// This should've been done right after registration however this seems to crash
	// (probably because XML initialization is not done until we try to read an object from a file).
	buildTypeNamesTable();
	// UPDATE OBJECT
	updateFromXMLNode();
	//}
	//catch(rdException &x) {
		//x.print(cout);
	//}
}
//_____________________________________________________________________________
/**
 * Construct an object from a document.
 *
 * The document is copied and this object, including its derived classes,
 * are constructed based on the nodes within the document.
 */
rdObject::rdObject(const rdXMLDocument *aDocument)
{
	setNull();

	// CHECK DOCUMENT
	if(aDocument==NULL) {
		cout<<"rdObject(aDocument): ERROR- document was null.\n";
		return;
	}

	// COPY DOCUMENT
	_document = new rdXMLDocument(*aDocument);

	// CONSTRUCT BASED ON ROOT ELEMENT
	DOMDocument *doc = _document->getDOMDocument();
	_node = doc->getDocumentElement();
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Construct an object from an DOMElement.
 */
rdObject::rdObject(DOMElement *aElement)
{
	setNull();

	// NODE
	_node = aElement;
	updateFromXMLNode();
}
//_____________________________________________________________________________
/**
 * Copy constructor.
 *
 * Copy constructors for all rdObject's only copy the non-XML variable
 * members of the object; that is, the object's DOMnode and rdXMLDocument
 * are not copied but set to NULL.  The reason for this is that for the
 * object and all its derived classes to establish the correct connection
 * to the XML document nodes, the the object would need to reconstruct based
 * on the XML document not the values of the object's member variables.
 *
 * There are three proper ways to generate an XML document for an rdObject:
 *
 * 1) Construction based on XML file (@see rdObject(const char *aFileName)).
 * In this case, the XML document is created by parsing the XML file.
 *
 * 2) Construction by rdObject(const rdXMLDocument *aDocument).
 * This constructor explictly requests construction based on an
 * XML document.  In this way the proper connection between an object's node
 * and the corresponding node within the XML document is established.
 * This constructor is a copy constructor of sorts because all essential
 * rdObject member variables should be held within the XML document.
 * The advantage of this style of construction is that nodes
 * within the XML document, such as comments that may not have any
 * associated rdObject member variable, are preserved.
 *
 * 3) A call to generateDocument().
 * This method generates an XML document for the rdObject from scratch.
 * Only the essential document nodes are created (that is, nodes that
 * correspond directly to member variables.).
 *
 * @param aObject Object to be copied.
 * @see rdObject(const rdXMLDocument *aDocument)
 * @see rdObject(const char *aFileName)
 * @see generateDocument()
 */
rdObject::rdObject(const rdObject &aObject)
{
	setNull();

	// COPY TYPE AND NAME
	*this = aObject;
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
rdObject* rdObject::
copy() const
{
	rdObject *object = new rdObject(*this);
	return(object);
}
//_____________________________________________________________________________
/**
 * Copy this object and modify the copy so that it is consistent
 * with a specified XML element node.
 *
 * The copy is constructed by first using the contructor for the DOMElement
 * in order to establish the relationship of the control with the
 * XML node.  Then, the assignment operator is used to set all member variables
 * of the copy to the values of this object.  Finally, the data members of
 * the copy are updated from the DOMElment using updateObject().
 *
 * @param aElement XML element. 
 * @return Pointer to a copy of this object.
 */
rdObject* rdObject::
copy(DOMElement *aElement) const
{
	// ESTABLISH RELATIONSHIP WITH XML NODE
	rdObject *object = new rdObject(aElement);

	// ASSIGNMENT OPERATOR
	*object = *this;

	// UPDATE BASED ON NODE
	object->updateFromXMLNode();

	return(object);
}

//_____________________________________________________________________________
/**
 * Build table of Type names to avoid allocating and deallocating
 * memory for XML tags repeatedly.
 */
void rdObject::
buildTypeNamesTable()
{
	// Fill up the _typeNames array for quick indexing
	if (_typeNames.getSize() != _Types.getSize()){
		for(int i=0;i<_Types.getSize();i++) {
			rdObject *object = _Types.get(i);
			string objType = object->getType();
			XMLCh *tagName = XMLString::transcode(objType.c_str());
			_typeNames.append(tagName);
			recognizedTypes.push_back(objType);
		}
		sort(recognizedTypes.begin(), recognizedTypes.end());
	}
}
//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set all member variables to their null or default values.
 */
void rdObject::
setNull()
{
	setType("rdObject");
	setName("");

	setupProperties();

	_document = NULL;
	_node = NULL;
	_refNode = NULL;
	_inLined = true;
	_propertySet.clear();

	_observable=0;
}
//_____________________________________________________________________________
/**
 * Set up the serialized member variables.  This involves both generating
 * the properties and connecting them to the local pointers used to access
 * the serialized member variables.
 */
void rdObject::
setupProperties()
{

	// CURRENTLY THERE ARE NO SERIALIZED MEMBERS IN rdObject

}

//_____________________________________________________________________________
/**
 * Perform any initializations that should occur upon instantiation.
 */
void rdObject::
init()
{

	// CURRENTLY THERE ARE NO INITIALIZATIONS NEEDED.

}


//=============================================================================
// OPERATORS
//=============================================================================
//-----------------------------------------------------------------------------
// ASSIGNMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Assign this object to the values of another.  The XML-associated variable
 * members are not copied-- the XML nodes and/or document must be generated
 * anew for a copied object.
 *
 * @return Reference to this object.
 * @see updateXMLNode()
 * @see generateXMLNode()
 */
rdObject& rdObject::
operator=(const rdObject &aObject)
{
	setType(aObject.getType());
	setName(aObject.getName());
	return(*this);
}

//-----------------------------------------------------------------------------
// EQUALITY
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if two objects are equal.
 *
 * @return True if the two objects are equal, false otherwise.
 */
bool rdObject::
operator==(const rdObject &aObject) const
{
	if(getType() != aObject.getType()) return(false);
	if(getName() != aObject.getName()) return(false);
	return(true);
}

//-----------------------------------------------------------------------------
// LESS THAN
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine if this property is less than another.
 *
 * This property is less than another if the name of this string is less
 * than the name of the other property.
 *
 * @param aProperty Property for which to make the less than test.
 * @return True if this property is less than the other, false otherwise.
 */
bool rdObject::
operator<(const rdObject &aObject) const
{
	return(_name < aObject._name);
}


//=============================================================================
// GET AND SET
//=============================================================================
//-----------------------------------------------------------------------------
// TYPE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the type of this object.
 *
 * @param aType Type of this object represented as a string.  In most all
 * cases, the type should be the name of the class.
 */
void rdObject::
setType(const string &aType)
{
	_type = aType;
	if(_type.size()>NAME_LENGTH) _type.resize(NAME_LENGTH);
}
//_____________________________________________________________________________
/**
 * Get the type of this object.
 *
 * @return The type of the object.  In most all cases, the type should be the
 * the name of the class.
 */
const string& rdObject::
getType() const
{
	return(_type);
}

//-----------------------------------------------------------------------------
// NAME
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the name of this object.
 */
void rdObject::
setName(const string &aName)
{
	_name = aName;
}
//_____________________________________________________________________________
/**
 * Get the name of this object.
 */
const string& rdObject::
getName() const
{
	return(_name);
}

//_____________________________________________________________________________
/**
 * Wrapper to be used on Java side to display objects in tree.
 */
const string& rdObject::
toString() const
{
	return(getName());
}

//-----------------------------------------------------------------------------
// DESCRIPTION
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the description of this object.
 */
void rdObject::
setDescription(const string &aDescrip)
{
	_description = aDescrip;
}
//_____________________________________________________________________________
/**
 * Get the description of this object.
 */
const string& rdObject::
getDescription() const
{
	return(_description);
}


//=============================================================================
// REGISTRATION
//=============================================================================
//-----------------------------------------------------------------------------
// REGISTER TYPE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Register a supported object type.  A global list of all supported objects
 * (i.e., objects derived from rdObject) is kept mainly for two purposes:
 *
 * ---- Object Deserialization ----
 * Once a type is registered, that type can be read from XML files
 * assuming that the type has implemented the following methods:
 *	1)	copy constructor
 *	2)	virtual rdObject* copy() const,
 *	3)	virtual rdObject* copy(DOMElement*) const,
 *	4)	<class>& operator=() (where the class name is substituted for <class>),
 *
 * ---- Initialization by Default Object ----
 * When objects are deserialized, they are constructed based on the registered
 * type and receive all of the registered type's property values.  These
 * values are over-ridden only if there is an element within an XML file that
 * overrides a default element.
 *
 * Because this method is static, registration of object types needs to be
 * done only once per process and an object does not need to be
 * instantiated to do so.
 *
 * This method makes a copy of the specified object.
 *
 * @param aObject Object of the type to be registered.  If the type is
 * already registered, the current object is replaced by a copy of
 * the specified object.
 * @see isValidDefault()
 */
void rdObject::
RegisterType(const rdObject &aObject)
{
	// GET TYPE
	const string &type = aObject.getType();
	if(type.empty()) {
		printf("rdObject.RegisterType: ERR- no type name has been set.\n");
		return;
	}
	// Keep track if the object being registered originated from a file vs. programmatically
	// for future use in the deserialization code.
	if (aObject._node!= 0)
		_defaultsReadFromFile[aObject.getType()] = true;
	else
		_defaultsReadFromFile[aObject.getType()] = false;

	// REPLACE IF A MATCHING TYPE IS ALREADY REGISTERED
	int i;
	for(i=0;i<_Types.getSize();i++) {
		rdObject *object = _Types.get(i);
		if(object->getType() == type) {
			if(rdObject_DEBUG) {
				cout<<"rdObject.RegisterType: replacing registered object of type ";
				cout<<type;
				cout<<"\n\twith a new default object of the same type."<<endl;
			}
			_Types.set(i,aObject.copy());
			_Types.get(i)->setName(DEFAULT_NAME);
			_mapTypesToDefaultObjects[aObject.getType()]= aObject.copy();
			return;
		} 
	}

	// APPEND
	rdObject *defaultObj = aObject.copy();
	_Types.append(defaultObj);
	_mapTypesToDefaultObjects[aObject.getType()]= defaultObj;
	_Types.getLast()->setName(DEFAULT_NAME);//0x00c067d8, 0x003b84f8
}


//=============================================================================
// XML NEW
//=============================================================================
//-----------------------------------------------------------------------------
// DEFAULT OBJECTS
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Determine whether a specified object is a valid or recognized type
 * for this object.
 *
 * This method is used during XML serialization to determine whether or not
 * objects in the type registry (@see rdObject::RegisterType()) should be
 * written to a header element containing the default objects for this
 * object.  An object is generally a valid type if that object could be a
 * member or sub-member of this object.  The header containing the default
 * objects has the tag name "defaults".
 *
 * The default elements allow a user to see all the available properties for
 * an object of a particular type and also allow a user to specify default
 * values for any member objects.
 *
 * The implementation of this method in rdObject always returns true.
 * This results in every object in the type registery being written to
 * the defaults header.  To be more restrictive about which objects are
 * valid (and written to the defaults header), this method should be
 * overridden by derived classes.  For example, class rdActuatorSet might
 * override this method to allow only object derived from rdActuator to be
 * valid.
 *
 * @param aObject Object to be tested as valid or invalid default type
 * for this object.
 * @see updateFromXMLNode()
 * @see updateXMLNode()
 * @see RegisterType()
 */
bool rdObject::
isValidDefaultType(const rdObject *aObject) const
{
	return(true);
}

//-----------------------------------------------------------------------------
// UPDATE OBJECT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update this object based on its XML node.
 * Added parameter sourceNode to handle external documents
 * For non-inlined objects the root of the childDocument is passed in else NULL.
 */
void rdObject::
updateFromXMLNode()
{
	if(_node==NULL) return;
	if(_type=="rdObject") return;

	// NAME 
	char *str = rdXMLNode::GetAttribute(_node,"name");
	string name = str;
	setName(name);
	if(str!=NULL) delete[] str;

	// UPDATE DEFAULT OBJECTS
	updateDefaultObjectsFromXMLNode();

	// LOOP THROUGH PROPERTIES
	int i,listLength;
	DOMElement *elmt;
	for(i=0;i<_propertySet.getSize();i++) {

		rdProperty *property = _propertySet.get(i);

		// TYPE
		rdProperty::rdPropertyType type = property->getType();

		// NAME
		string name = property->getName();
		if(rdObject_DEBUG) {
			cout << "rdObject.updateFromXMLNode: updating property " << name << endl;
		}


		//----------- TRY BLOCK FOR PROPERTIES ------------
		try {

		// VALUE
		switch(type) {

		// Bool
		case(rdProperty::Bool) : {
			property->setUseDefault(true);
			bool value;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt!=NULL) {
				value = rdXMLNode::GetBool(elmt);
				property->setValue(value);
				property->setUseDefault(false);
			}
			break; }

		// Int
		case(rdProperty::Int) : {
			property->setUseDefault(true);
			int value;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt!=NULL) {
				value = rdXMLNode::GetInt(elmt);
				property->setValue(value);
				property->setUseDefault(false);
			}
			break; }

		// Dbl
		case(rdProperty::Dbl) : {
			property->setUseDefault(true);
			double value;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			// The following if statement prevents an exception from being thrown
			// in GetDbl.  It is also computationally much faster.
			if(elmt!=NULL) {
				value = rdXMLNode::GetDbl(elmt);
				property->setValue(value);
				property->setUseDefault(false);
			}
			break; }

		// Str
		case(rdProperty::Str) : {
			property->setUseDefault(true);
			char *value;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			value = rdXMLNode::GetStr(elmt);
			if(value==NULL) {
				property->setValue("");
				property->setUseDefault(false);
			} else {
				string valueStr = value;
				stripExtraWhiteSpace(valueStr);
				property->setValue(valueStr);
				property->setUseDefault(false);
				delete[] value;
			}
			break; }

		// Obj
		case(rdProperty::Obj) : {
			property->setUseDefault(true);
			rdObject &object = property->getValueObj();
			elmt = object.getXMLNode();

			//-----------Begin inline support---------------------------
			// Collect inlining attributes
			bool inLinedObject = true;
			DOMElement *refNode;
			rdXMLDocument *childDocument;
			if (elmt){
				char *fileAttrib = rdXMLNode::GetAttribute(elmt, "file");
				if (fileAttrib!= NULL && strlen(fileAttrib) > 0){
					// Change _node to refer to the root of the external file
					refNode = elmt;
					childDocument = new rdXMLDocument(fileAttrib);
					elmt = childDocument->getDOMDocument()->getDocumentElement();
					inLinedObject = false;
				}
				if(fileAttrib!=NULL) delete[] fileAttrib;
			}
			//-----------End inline support---------------------

			// OBJECT ALREAD HAS AN ASSOCIATED XML NODE
			if(elmt!=NULL) {
				object.updateFromXMLNode();

			// NEED TO CONSTRUCT BASED ON NODE
			} else {

				// VARIABLES
				unsigned int j;
				XMLCh *tagName;
				DOMElement *objNode = NULL;
				DOMNodeList *list;

				// GET XML NODE
				string objType = object.getType();
				tagName = XMLString::transcode(objType.c_str());
				list = _node->getElementsByTagName(tagName);
				if(tagName!=NULL) delete[] tagName;

				// CHECK NAME
				string objName = object.getName();
				listLength = list->getLength();
				for(j=0;j<listLength;j++) {

					// GET ELEMENT
					elmt = (DOMElement*) list->item(j);
					if(elmt==NULL) continue;
					// Make sure this is not the default
					DOMNode *parent = elmt->getParentNode();
					char *parentName = XMLString::transcode(parent->getNodeName());
					if (string(parentName)=="defaults")
						continue;
					// NAME ATTRIBUTE
					char *elmtName =
						rdXMLNode::GetAttribute(elmt,"name");
					if(rdObject_DEBUG) cout<<"\nFound element "<<elmtName<<endl;
					if(objName == elmtName) {//? why
						objNode = elmt;
						delete[] elmtName;
						break;
					}

					// CLEAN UP
					delete[] elmtName;
				}

				// WAS A NODE NOT FOUND?
				if(objNode==NULL) {
					if (rdObject_DEBUG) {
						cout<<"rdObject.updateFromXMLNode: ERROR- could not find node ";
						cout<<objName<<" of type "<<objType<<"."<<endl;
					}
					break;
				}

				property->setUseDefault(false);
				// CONSTRUCT TEMPORARY OBJECT BASED ON NODE
				//rdObject *objTmp = object.copy(objNode);
				object.setXMLNode(objNode);
				//set default values
				object.updateFromXMLNode();

				// USE EQUALITY OPERATOR
				//object = (*objTmp);


				// Set inlining attributes on final object
				if (!inLinedObject){
					object._inLined = inLinedObject;
					object._refNode = refNode;
					object._document = childDocument;
				}

				// SET THE XML NODE
				//object.setXMLNode(objTmp->getXMLNode());

				// CLEAN UP
				//delete objTmp;

			}
			break; }

		// BoolArray
		case(rdProperty::BoolArray) : {
			property->setUseDefault(true);
			int n=0;
			bool *value=NULL;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt!=NULL) {
				property->setUseDefault(false);
				n = rdXMLNode::GetBoolArray(elmt,value);
				property->setValue(n,value);
				if(n>0) delete[] value;
			}
			break; }

		// IntArray
		case(rdProperty::IntArray) : {
			property->setUseDefault(true);
			int n=0;
			int *value=NULL;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt!=NULL) {
				property->setUseDefault(false);
				n = rdXMLNode::GetIntArray(elmt,value);
				// Moved setting and cleanup inside the if block so that values set by constructor are kept 
				// if property is not specified in the xml file
				property->setValue(n,value);
				if(n>0) delete[] value;
			}
			break; }

		// DblArray
		case(rdProperty::DblArray) : {
			property->setUseDefault(true);	// Indicate not read from file
			int n=0;
			double *value=NULL;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt!=NULL) {
				property->setUseDefault(false);
				n = rdXMLNode::GetDblArray(elmt,value);
				// Moved setting and cleanup inside the if block so that values set by constructor are kept 
				// if property is not specified in the xml file
				property->setValue(n,value);
				if(n>0) delete[] value;
			}
			break; }

		// StrArray
		case(rdProperty::StrArray) : {
			property->setUseDefault(true);
			int n=0;
			string *value=NULL;
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt!=NULL) {
				property->setUseDefault(false);
				n = rdXMLNode::GetStrArray(elmt,value);
				// Moved setting and cleanup inside the if block so that values set by constructor are kept 
				// if property is not specified in the xml file
				property->setValue(n,value);
				if(n>0) delete[] value;
			}
			break; }

		// ObjArray
		case(rdProperty::ObjArray) : {
			property->setUseDefault(true);

			// CLEAR EXISTING OBJECT ARRAY
			rdArrayPtrs<rdObject> &objArray = property->getValueObjArray();
			objArray.setSize(0);

			// GET ENCLOSING ELEMENT
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt==NULL) {
				if (rdObject_DEBUG) {
					cout<<"rdObject.updateFromXMLNode: ERR- failed to find element ";
					cout<<name<<endl;
				}
				break;
			}

			// VARIABLES
			int i;
			unsigned int j;
			XMLCh *tagName;
			DOMElement *objElmt;
			DOMNodeList *list;
			rdObject *defaultObject,*object;
			{
				// If top element has a "file attribute", the document needs to be opened
				// and elmt must be switched to the root of that document
				char *fileAttrib = rdXMLNode::GetAttribute(elmt, "file");
				bool inLinedObject = true;
				DOMElement *refNode;
				rdXMLDocument *childDocument;
				if ((fileAttrib!=NULL) && (strlen(fileAttrib)>0)){
					// Change _node to refer to the root of the external file
					refNode = elmt;
					childDocument = new rdXMLDocument(fileAttrib);
					elmt = childDocument->getDOMDocument()->getDocumentElement();
					inLinedObject = false;
				}
			}
			// LOOP THROUGH SUPPORTED OBJECT TYPES
			list = elmt->getChildNodes();
			listLength = list->getLength();
			char buffer[31];
			for(j=0;j<listLength;j++) {

				// GET ELEMENT
				objElmt = (DOMElement*) list->item(j);
				if(objElmt==NULL) continue;
				const XMLCh *objType = objElmt->getTagName();
				XMLString::transcode(objType, buffer, 30);
				XMLString::trim(buffer);
				string  objectType(buffer);
				if ( find(recognizedTypes.begin(), recognizedTypes.end(), objectType)== recognizedTypes.end()){
					continue;
				}
				defaultObject = _mapTypesToDefaultObjects[objectType];
					// GET ELEMENT
					objElmt = (DOMElement*) list->item(j);
					if(objElmt==NULL) continue;

					// If object is from non-inlined, detect it and set attributes
					// However we need to do that on the finalized object as copying
					// does not keep track of XML related issues
					//-----------Begin inline support---------------------------
					// Collect inlining attributes
					char *fileAttrib = rdXMLNode::GetAttribute(objElmt, "file");
					bool inLinedObject = true;
					DOMElement *refNode;
					rdXMLDocument *childDocument;
					if ((fileAttrib!=NULL) && (strlen(fileAttrib)>0)){
						// Change _node to refer to the root of the external file
						refNode = objElmt;
						childDocument = new rdXMLDocument(fileAttrib);
						objElmt = childDocument->getDOMDocument()->getDocumentElement();
						inLinedObject = false;
					}
					if(fileAttrib!=NULL) delete[] fileAttrib;
					//-----------End inline support---------------------
					// CHECK THAT THE ELEMENT IS AN IMMEDIATE CHILD
					DOMNode *parent = objElmt->getParentNode();
					if( (parent!=elmt) && (parent!=NULL) && (_node!=NULL) &&
						(parent->getOwnerDocument()==_node->getOwnerDocument()) ) {
						if(rdObject_DEBUG) {
							char *elmtName,*parentName,*nodeName;
							elmtName = XMLString::transcode(objElmt->getNodeName());
							parentName = XMLString::transcode(parent->getNodeName());
							nodeName = XMLString::transcode(elmt->getNodeName());
							cout<<"rdObject.updateFromXMLNode: "<<elmtName;
							cout<<" is a child of "<<parentName<<", not of ";
							cout<<nodeName<<endl;
							delete[] elmtName;
							delete[] parentName;
							delete[] nodeName;
						}
						continue;
					}
					
					property->setUseDefault(false);

					// CONSTRUCT THE OBJECT BASED ON THE ELEMENT
					object = defaultObject->copy(objElmt);

					// Set inlining attributes on final object
					if (!inLinedObject){
						object->_inLined = inLinedObject;
						object->_refNode = refNode;
						object->_document = childDocument;
					}

					// ADD
					if(object!=NULL) {
						objArray.append(object);
					}
				}
				
			break; }

		// NOT RECOGNIZED
		default : {
			cout<<"rdObject.UpdateObject: WARN- unrecognized property type."<<endl;

			break; }
		}

		//-----------------------------------------------------
		} catch(rdException x) {
			if(rdObject_DEBUG) x.print(cout);
		}
		//----------- END TRY BLOCK FOR PROPERTIES ------------
	}
}

//-----------------------------------------------------------------------------
// UPDATE DEFAULT OBJECTS FROM XML NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the registerred default objects based on an object's XML node.
 *
 * This method looks for an element with a tag name "defaults" and reads
 * the objects in that element and registers them using the method
 * rdObject::RegisterType().
 */
void rdObject::
updateDefaultObjectsFromXMLNode()
{
	// MUST BE ROOT ELEMENT
	if(_document==NULL) return;
	if(_node!=_document->getDOMDocument()->getDocumentElement()) return;

	// VARIABLES
	int i;
	DOMElement *defaultsElmt,*elmt;
	rdObject *defaultObject,*object;

	// GET DEFAULTS ELEMENT
	defaultsElmt = rdXMLNode::GetFirstChildElementByTagName(_node,"defaults");
	if(defaultsElmt==NULL) return;

	// LOOP THROUGH SUPPORTED OBJECT TYPES
	for(i=0;i<_Types.getSize();i++) {

		// GET DEFAULT OBJECT
		defaultObject = _Types.get(i);
		if(defaultObject==NULL) continue;
		if(!isValidDefaultType(defaultObject)) continue; // unused

		// GET ELEMENT
		const string &type = defaultObject->getType();
		elmt = rdXMLNode::GetFirstChildElementByTagName(defaultsElmt,type);
		if(elmt==NULL) continue;

		// CHECK THAT THE ELEMENT IS AN IMMEDIATE CHILD
		DOMNode *parent = elmt->getParentNode();
		if(parent != defaultsElmt) {
			string elmtName,parentName,nodeName;
			elmtName = XMLString::transcode(elmt->getNodeName());
			parentName = XMLString::transcode(parent->getNodeName());
			nodeName = XMLString::transcode(_node->getNodeName());
			if(rdObject_DEBUG) {
				cout<<"rdObject.updateFromXMLNode: "<<elmtName;
				cout<<" is a child of "<<parentName<<", not of ";
				cout<<nodeName<<endl;
			}
			continue;
		}

		// CONSTRUCT AND REGISTER DEFAULT OBJECT
		object = defaultObject->copy(elmt);
		if(object!=NULL) {
			object->setName(DEFAULT_NAME);
			RegisterType(*object);
			delete object;
		}
	}
}

//-----------------------------------------------------------------------------
// UPDATE XML NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Update the XML node that represents this object.
 *
 * @param aParent Parent XML node of this object.  Sending in a parent node
 * allows an XML node to be generated for this object if it doesn't already
 * have one.  If the parent node is sent in as NULL and this object doesn't
 * already have an XML node, this object will become the root node for a
 * new XML document.  If this object already has an XML node associated with
 * it, no new nodes are ever generated and the parent node is not used.
 *
 * @param aParent Parent XML element.
 */
void rdObject::
updateXMLNode(DOMElement *aParent)
{
	// If object is not inlined we don't want to generate node in original document
	// Handle not-inlined objects first.
	if (aParent==NULL && !getInlined()) {
		cout<<"Root node must be inlined"<<*this<<endl;
	}

	// Can we make this more efficient than recreating the node again?
	// We can possibly check when setInlined() is invoked if we need to do it or not
	if (!getInlined() && aParent){
		// Create a new document and write object to it
		const char *offLineFileName = getDocument()->getFileName();
		// The problem is that generateChildXMLDocument makes a root which allows print
		// to do its job but root is duplicated. If we don't create the node then generateDocument
		// is invoked which messes up the whole _childDocument mechanism as _document is overwritten.
		_inLined=true;
		print(offLineFileName);
		_inLined=false;
		
		if (!_refNode){
			_refNode = rdXMLNode::AppendNewElementWithComment(aParent, getType(),getName());
			rdXMLNode::SetAttribute(_refNode,"file",offLineFileName);
		}
		return;
	}

	// GENERATE XML NODE?
	if(_node==NULL) {
		if(rdObject_DEBUG) cout<<"Generating XML node for "<<*this<<endl;
		generateXMLNode(aParent);
	}

	// CHECK THAT IT IS AN ELEMENT NODE
	if(_node->getNodeType()!=DOMNode::ELEMENT_NODE) return;


	// NAME
	rdXMLNode::SetAttribute(_node,"name",getName());

	// DEFAULT OBJECTS
	int i;
	DOMElement *elmt;
	string defaultsTag = "defaults";
	elmt = rdXMLNode::GetFirstChildElementByTagName(_node,defaultsTag);
	// Not root element- remove defaults
	if((aParent!=NULL) && (elmt!=NULL)) {
		DOMNode *defaultsParent = elmt->getParentNode();
		defaultsParent->removeChild(elmt);
	// Root element- write valid defaults
	} else if(aParent==NULL) {
		if(elmt==NULL) elmt = rdXMLNode::AppendNewElementWithComment(_node,defaultsTag);
		rdXMLNode::RemoveChildren(elmt);
		for(i=0;i<_Types.getSize();i++) {
			rdObject *defaultObject = _Types.get(i);
			if( isValidDefaultType(defaultObject) && 
				(rdObject::getSerializeAllDefaults() || _defaultsReadFromFile[defaultObject->getType()])) {
				defaultObject->setXMLNode(NULL);
				defaultObject->updateXMLNode(elmt);
			}
		}
	}

	// LOOP THROUGH PROPERTIES
	for(i=0;i<_propertySet.getSize();i++) {

		rdProperty *property = _propertySet.get(i);

		// TYPE
		rdProperty::rdPropertyType type = property->getType();

		// NAME
		string name = property->getName();

		// VALUE
		switch(type) {

		// Bool
		case(rdProperty::Bool) : {
			bool &value = property->getValueBool();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt = rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetBoolArray(elmt,1,&value);
			break; }

		// Int
		case(rdProperty::Int) : {
			int &value = property->getValueInt();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetIntArray(elmt,1,&value);
			break; }

		// Dbl
		case(rdProperty::Dbl) : {
			double &value = property->getValueDbl();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetDblArray(elmt,1,&value);
			break; }

		// Str
		case(rdProperty::Str) : {
			string &value = property->getValueStr();
			char *str = (char *)value.c_str();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetStrArray(elmt,1,&str);
			break; }

		// Obj
		case(rdProperty::Obj) : {
			if (property->getComment()!=""){
				rdXMLNode::AppendNewCommentElement(_node, property->getComment());
			}
			rdObject &object = property->getValueObj();
			object.updateXMLNode(_node);
			break; }

		// BoolArray
		case(rdProperty::BoolArray) : {
			rdArray<bool> &value = property->getValueBoolArray();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetBoolArray(elmt,value.getSize(),&value[0]);
			break; }

		// IntArray
		case(rdProperty::IntArray) : {
			rdArray<int> &value = property->getValueIntArray();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetIntArray(elmt,value.getSize(),&value[0]);
			break; }

		// DblArray
		case(rdProperty::DblArray) : {
			rdArray<double> &value = property->getValueDblArray();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetDblArray(elmt,value.getSize(),&value[0]);
			break; }

		// StrArray
		case(rdProperty::StrArray) : {
			rdArray<string> &value = property->getValueStrArray();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if((elmt==NULL) && (!property->getUseDefault())) {
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			rdXMLNode::SetStrArray(elmt,value.getSize(),value.get());
			break; }

		// ObjArray
		case(rdProperty::ObjArray) : {
			rdArrayPtrs<rdObject> &value = property->getValueObjArray();
			elmt = rdXMLNode::GetFirstChildElementByTagName(_node,name);
			if(elmt==NULL) elmt = elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			if((elmt==NULL) && (!property->getUseDefault())) { // Is this ever used??
				elmt= rdXMLNode::AppendNewElementWithComment(_node, name, "", property->getComment());
			}
			for(int j=0;j<value.getSize();j++) {
				value.get(j)->updateXMLNode(elmt);
			}
			break; }

		// NOT RECOGNIZED
		default : {
			cout<<"rdObject.UpdateObject: WARN- unrecognized property type."<<
				endl;

			break; }
		}
	}
}

//_____________________________________________________________________________
/**
 * Generate an XML node to represent this object.
 *
 * If the parent node is NULL the intent is to generate a new document as
 * well as a new node.  Howerver, for this request to be successful,
 * a document must not already be associated with the object.
 *
 * If the parent node is not NULL and this object already has a node, the
 * node and the parent must be from the same document.  Requesting that a
 * new node be generated when one already exists is useful when it is
 * desired to remake a node entirely including elements for all the
 * properties of an object.
 *
 * @param aParent Intended parent of the node to be generated.  If aParent is
 * NULL, the intent is for this object to serve as the root element of
 * a new document.
 */
void rdObject::
generateXMLNode(DOMElement *aParent)
{
	// CHECK FOR DIFFERENT DOCUMENTS ERROR
	if((aParent!=NULL)&&(_node!=NULL)) {
		if(aParent->getOwnerDocument()!=_node->getOwnerDocument()) {
			printf("rdObject.generateNode: ERROR- object cannot switch ");
			printf("documents.\n");
			return;
		}
	}

	// REQUEST FOR NEW DOCUMENT BUT DOCUMENT ALREADY EXISTS ERROR
	if((aParent==NULL)&&(_node!=NULL)) {
		printf("rdObject.generateNode: ERROR- request to generate new ");
		printf("document, but a document already exists.\n\n");
		return;
	}

	// CREATE NEW DOCUMENT
	if(aParent==NULL) {
		generateXMLDocument();

	// ONLY CREATE A NEW NODE
	} else {

		// REMOVE EXISTING NODE
		if(_node!=NULL) {
			printf("rdObject.generateNode: WARN- node already existed.\n");
			printf("\t...Removing old node.\n");
			DOMNode *parent = _node->getParentNode();
			if(parent!=NULL) parent->removeChild(_node);
		}

		// GENERATE NEW NODE
		_node = rdXMLNode::AppendNewElementWithComment(aParent,getType(),getName(),"");
	}
}

//-----------------------------------------------------------------------------
// NODE
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Set the XML node for this object.
 *
 * This method is not intended for general use.  Generally, the XML node
 * of an object is assigned during construction.  In rare instances, however,
 * it is convenient to have the ability to set the XML node of an object.
 * This functionality is private and only accessible from within rdObject.
 *
 * @return Node set for this object.
 */
void rdObject::
setXMLNode(DOMElement *aNode)
{
	_node = aNode;
}
//_____________________________________________________________________________
/**
 * Get the XML node for this object.
 *
 * @return Node set for this object.
 */
DOMElement* rdObject::
getXMLNode() const
{
	return(_node);
}

//-----------------------------------------------------------------------------
// DOCUMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Get the document for this object.
 *
 * @return Document set for this object.
 */
rdXMLDocument* rdObject::
getDocument() const
{
	return(_document);
}


//-----------------------------------------------------------------------------
// GENERATE XML DOCUMENT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Generate a new XML document with this object as the root node.
 */
void rdObject::
generateXMLDocument()
{
	if(_node!=NULL) {
		printf("rdObject.generateDocument: ERROR- request to generate new ");
		printf("document, but a document already exists.\n\n");
		return;
	}

	// CREATE NEW DOCUMENT
	if (_document==NULL)
		_document = new rdXMLDocument();
	// NEW ROOT ELEMENT
	_node = rdXMLNode::AppendNewElementWithComment(_document->getDOMDocument(),
		getType(),getName(),"");

}
//_____________________________________________________________________________
/**
 * NULL out the _node pointers for an object and all its descendents
 */
void rdObject::
clearXMLNodes()
{
	// recursively traverse tree of objects under current object and reset _node to NULL
	_node = NULL;

	// LOOP THROUGH PROPERTIES
	for(int i=0;i<_propertySet.getSize();i++) {
		rdProperty *property = _propertySet.get(i);

		// TYPE, we're only interested in Obj and ObjArray
		rdProperty::rdPropertyType type = property->getType();

		//----------- TRY BLOCK FOR PROPERTIES ------------
		try {

		// VALUE
		switch(type) {

		// Obj
		case(rdProperty::Obj) : {
			rdObject &object = property->getValueObj();
			object.clearXMLNodes();
			break; }

		// ObjArray
		case(rdProperty::ObjArray) : {

			// CLEAR EXISTING OBJECT ARRAY
			rdArrayPtrs<rdObject> &objArray = property->getValueObjArray();

			for(int j=0;j<objArray.getSize();j++) {
				objArray[j]->clearXMLNodes();
			}

			break; }

		// Not an object so doesn't have a _node to worry about
		default : {

			break; }
		}

		//-----------------------------------------------------
		} catch(rdException x) {
			if(rdObject_DEBUG) x.print(cout);
		}
		//----------- END TRY BLOCK FOR PROPERTIES ------------
	}
}


//=============================================================================
// XML support for inlining/offlining objects
//=============================================================================
/**
 * Mark the object as inlined (written to same xml file as parent or not
 * If the object will not be inlined then a file name to associate with the
 * object is passed in.
 */
void rdObject::
setInlined(const bool aInLined, const char *aFileName)
{
	if (_inLined != aInLined ){	// Object needs to be regenerated
		if (_inLined==true){
			// Replace original node
			if (_node){
				DOMElement *aParent = (DOMElement *)_node->getParentNode();
				const XMLCh *parentName = aParent->getTagName();
				cout << "Removing Node "<< getType() << " from " << parentName << endl;
				aParent->removeChild(_node);
				// May need to remove other "space" siblings here as well

				// create a refNode in parent document that has file name and object name
				_refNode = rdXMLNode::AppendNewElementWithComment(aParent, getType(),getName(),"");
				rdXMLNode::SetAttribute(_refNode,"file",aFileName);
				// Zero out _node and children nodes so they get regenerated as well
				clearXMLNodes();
			}
			_document = new rdXMLDocument(); // Force regeneratopn of document
			_document->setFileName(aFileName);
			_node = NULL;
		}
		else {	//_inLined was false. 
			// Remove refNode and NULL the rest for regeneration
			if (_refNode){
				DOMElement *aParent = (DOMElement *)_refNode->getParentNode();
				aParent->removeChild(_refNode);
				_refNode = NULL;

			}
			if (_document){
				delete _document;
				_document = NULL;
			}
			// Zero out _node and children nodes so they get regenerated as well
			clearXMLNodes();
		}

	}
	_inLined = aInLined;
}
/**
 * Get the value of the inlined flag
 */
bool rdObject::
getInlined() const
{
	return _inLined;
}
/** 
 * If an object is not inlined, management of Offline file name to readFrom/writeTo */
const char *rdObject::
getOffLineFileName() const
{
	if(getDocument()!= NULL)
		return getDocument()->getFileName();
	return NULL;
}

//=============================================================================
// IO
//=============================================================================
//-----------------------------------------------------------------------------
// PRINT
//-----------------------------------------------------------------------------
//_____________________________________________________________________________
/**
 * Print the object.
 *
 * @param aFileName File name.  If the file name is NULL, which is the
 * default, the object is printed to standard out.  
 */
bool rdObject::
print(const string &aFileName)
{
	//	if(_node==NULL) 
	// Check removed per Clay so that users don't have to manually call
	// updateXMLNode for subsequent saves.  Ayman 5/07/04.
	updateXMLNode(NULL);
	if(_document==NULL) return false;
	return _document->print(aFileName);
}

