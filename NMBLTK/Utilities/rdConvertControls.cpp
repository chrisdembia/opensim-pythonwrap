// rdConvertControls.cpp

// INCLUDES
#include <string>
#include <RD/Tools/rdTools.h>
#include <RD/Tools/rdIO.h>
#include <RD/Tools/rdXMLDocument.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Control/rdControlSet.h>


using namespace std;


// DECLARATIONS
rdControlLinear*
ExtractControl(DOMElement *aElmt);


//______________________________________________________________________________
/**
 * Convert a controls file from the old XML format to the new XML format.
 *
 * @param argc Number of command line arguments (should be 2).
 * @param argv Command line arguments:  convertControls inFile [outFile]
 */
int main(int argc,char **argv)
{
	// PARSE COMMAND LINE
	string inName,outName;
	if((argc!=2)&&(argc!=3)) {
		printf("Usage:  convertControls inFile [outFile]\n");
		exit(-1);
	} else {
		inName = argv[1];
		if(argc==3) {
			outName = argv[2];
		} else {
			outName = "convertControls.out";
		}
	}

	// OUTPUT PRECISION
	rdIO::SetPrecision(16);
	rdIO::SetDigitsPad(-1);

	// REGISTER TYPES
	rdObject::RegisterType(rdControlLinear());
	rdObject::RegisterType(rdControlLinearNode());

	// CREATE AN EMPTY CONTROL SET
	rdControlSet controlSet;

	// LOAD OLD XML DOCUMENT
	cout<<"Loading file "<<inName<<" in old XML format..."<<endl;
	rdXMLDocument *doc = new rdXMLDocument(inName);
	DOMDocument *dom = doc->getDOMDocument();
	if(dom==NULL) {
		cout<<"Unable to load document "<<inName<<"."<<endl;
		exit(-1);
	}

	// GET ROOT NODE
	DOMElement *root = dom->getDocumentElement();


	// GET LIST OF CONTROL NODES
	unsigned int j;
	string type = "rdControlLinear";
	XMLCh *tagName = XMLString::transcode(type.c_str());
	DOMNodeList *list = root->getElementsByTagName(tagName);
	delete[] tagName;

	// LOOP THROUGH LIST
	DOMElement *elmt;
	rdControlLinear *controlNode;
	for(j=0;j<list->getLength();j++) {

		// GET ELEMENT
		elmt = (DOMElement*) list->item(j);

		// EXTRACT CONTROL NODE
		controlNode = ExtractControl(elmt);

		// APPEND ON TO CONTROL SET
		controlSet.append(controlNode);
	}


	// WRITE CONTROL SET TO FILE
	controlSet.print(outName);

	return(0);
}



rdControlLinear*
ExtractControl(DOMElement *aElmt)
{
	if(aElmt==NULL) return(NULL);


	// NAME ATTRIBUTE
	char *elmtName = rdXMLNode::GetAttribute(aElmt,"name");
	cout<<"\nFound control node "<<elmtName<<endl;


	// TIME
	int nTimes;
	double *times;
	DOMElement *elmt = rdXMLNode::GetFirstChildElementByTagName(aElmt,"time");
	nTimes = rdXMLNode::GetDblArray(elmt,times);
	cout<<"nTimes = "<<nTimes<<", ";

	// VALUE
	int nValues;
	double *values;
	elmt = rdXMLNode::GetFirstChildElementByTagName(aElmt,"value");
	nValues = rdXMLNode::GetDblArray(elmt,values);
	cout<<"nValue = "<<nValues<<", ";

	// MIN
	int nMins;
	double *mins;
	elmt = rdXMLNode::GetFirstChildElementByTagName(aElmt,"min");
	nMins = rdXMLNode::GetDblArray(elmt,mins);
	cout<<"nMins = "<<nMins<<", ";

	// MAX
	int nMaxs;
	double *maxs;
	elmt = rdXMLNode::GetFirstChildElementByTagName(aElmt,"max");
	nMaxs = rdXMLNode::GetDblArray(elmt,maxs);
	cout<<"nMaxs = "<<nMaxs<<endl;

	// CONSTRUCT LINEAR CONTROL NODE
	rdControlLinear *control = new rdControlLinear(NULL,elmtName);
	rdArrayPtrs<rdControlLinearNode> &nodes = control->getNodeArray();
	nodes.setSize(0);

	// APPEND CONTROL ELEMENTS
	int i;
	int n = nTimes;
	if(n>nValues) n = nValues;
	if(n>nMins) n = nMins;
	if(n>nMaxs) n = nMaxs;
	rdControlLinearNode *node;
	char nodeName[256];
	for(i=0;i<n;i++) {
		node = new rdControlLinearNode(times[i],values[i],mins[i],maxs[i]);
		sprintf(nodeName,"%d",i);
		node->setName(nodeName);
		nodes.append(node);
	}

	// CHECK
	cout<<"Control "<<control->getName()<<" has "<<nodes.getSize()<<" nodes."
		<<endl;

	// CLEAN UP
	delete[] elmtName;


	return(control);
}