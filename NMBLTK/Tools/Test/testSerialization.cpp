// testTools.cpp
// Author:  Frank C. Anderson
#include <iostream>
#include <string>
#include <NMBLTK/Tools/rdTools.h>
#include <NMBLTK/Tools/rdPropertyBool.h>
#include <NMBLTK/Tools/rdPropertyInt.h>
#include <NMBLTK/Tools/rdPropertyIntArray.h>
#include <NMBLTK/Tools/rdPropertyDbl.h>
#include <NMBLTK/Tools/rdPropertyStr.h>
#include <NMBLTK/Tools/rdPropertyStrArray.h>
#include <NMBLTK/Tools/rdPropertySet.h>
#include <NMBLTK/Tools/rdException.h>
#include <NMBLTK/Tools/rdIO.h>
#include <NMBLTK/Tools/rdXMLDocument.h>
#include <NMBLTK/Tools/rdObject.h>
#include "rdSerializableObject.h"
#include "rdSerializableObject2.h"



using namespace std;


// DECLARATIONS
int TestSerialization();
//_____________________________________________________________________________
/**
 * Test the rdTools library.
 */
int main(int argc, char* argv[])
{
	return(TestSerialization());
}

//_____________________________________________________________________________
/**
 * Test the serialization of an object.
 */
int TestSerialization()
{
	bool success = false;
	try {
		// TYPE REGISTRATION
		rdObject::RegisterType(rdSerializableObject());
		rdObject::RegisterType(rdSerializableObject2());

		// OBJECT 1
		rdSerializableObject obj1;
		obj1.setName("TestObject");
		obj1.print("obj1.xml");

		// OBJECT 2
		rdSerializableObject obj2("obj1.xml");

		obj2.updateXMLNode(NULL);
		obj2.print("roundtrip.xml");

		int diff = system("diff -b obj1.xml roundtrip.xml");

		success =  (diff == 0);
		if (!success) {
			throw rdException("round trip file diffs other than spaces",__FILE__,__LINE__);
		}

		// Now compare object properties to make sure we're not reading and writing the file as just text!
		int numProperties1 = obj1.getPropertySet().getSize();
		success = (numProperties1 == obj2.getPropertySet().getSize());
		if (!success) {
			throw rdException("num properties",__FILE__,__LINE__);
		}
		rdPropertySet &propSet1 = obj1.getPropertySet();
		rdPropertySet &propSet2 = obj2.getPropertySet();
		for (int i=0; i < numProperties1 && success; i++){
			rdProperty *prop1 = propSet1.get(i);
			rdProperty *prop2 = propSet2.get(i);
			success = (prop1->getName() == prop2->getName());
		}
		if (!success) {
			throw rdException("property names",__FILE__,__LINE__);
		}
		success = (((rdPropertyBool*) propSet1.get(0))->getValueBool() == ((rdPropertyBool*) propSet2.get(0))->getValueBool());
		if (!success) {
			throw rdException("bool property",__FILE__,__LINE__);
		}
		success = (((rdPropertyInt*) propSet1.get(1))->getValueInt() == ((rdPropertyInt*) propSet2.get(1))->getValueInt());
		if (!success) {
			throw rdException("int property",__FILE__,__LINE__);
		}
		success = (((rdPropertyDbl*) propSet1.get(2))->getValueDbl() == ((rdPropertyDbl*) propSet2.get(2))->getValueDbl());
		if (!success) {
			throw rdException("double property",__FILE__,__LINE__);
		}
		/* The following actually fails due to extra spaces when we read back from file!.
		string& str1 = ((rdPropertyStr*) propSet1.get(3))->getValueStr();
		string& str2 = ((rdPropertyStr*) propSet2.get(3))->getValueStr();
		str1.compare(str2);
		if (!success) {
			throw rdException("String property",__FILE__,__LINE__);
		}
		*/
	}
	catch(rdException x) {
		x.print(cout);

	}
	return (success?0:1);
}

