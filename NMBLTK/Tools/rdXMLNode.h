// rdXMLNode.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdXMLNode_h__
#define __rdXMLNode_h__


// INCLUDES
#include <iostream>	// Ayman: Remove .h extension per .NET 2003
#include <xercesc/dom/DOM.hpp>
#include "rdTools.h"
XERCES_CPP_NAMESPACE_USE


//using namespace std;	// Ayman:per .NET 2003


//=============================================================================
//=============================================================================
/**
 * A class for performing operations on XML nodes.
 *
 * The methods in this class are generally static methods that take
 * an DOMNode as their first argument.
 *
 * This product includes software developed by the
 * Apache Software Foundation (http://www.apache.org/).
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdXMLNode {
//=============================================================================
// DATA
//=============================================================================
//	DOMNode *dumNode;
	static const int TABLIMIT;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION AND DESTRUCTION
	//--------------------------------------------------------------------------
public:

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	static int GetNumberOfParents(const DOMNode *node);

	//--------------------------------------------------------------------------
	// ADD AND REMOVE NODES
	//--------------------------------------------------------------------------
	static DOMElement*
		AppendNewElement(DOMNode *aParent,const std::string &aTag,
		const std::string &aName="");
	static void
		RemoveChildren(DOMNode *aNode);

	//--------------------------------------------------------------------------
	// GET NODES
	//--------------------------------------------------------------------------
	static DOMElement*
		GetFirstChildElementByTagName(const DOMNode *aNode,
		const std::string &aTagName);
	static DOMCharacterData*
		GetCDataSectionNode(const DOMNode *aNode);
	static DOMText*
		GetTextNode(const DOMNode *aNode);

	//--------------------------------------------------------------------------
	// FUNDAMENTAL VALUE TYPES
	//--------------------------------------------------------------------------
	static bool
		GetBool(const DOMNode *aNode);
	static int
		GetInt(const DOMNode *aNode);
	static double
		GetDbl(const DOMNode *aNode);
	static char*
		GetStr(const DOMNode *aNode);

	//--------------------------------------------------------------------------
	// FUNDAMENTAL ARRAY TYPES
	//--------------------------------------------------------------------------
	// BOOL ARRAY
	static void
		SetBoolArray(DOMNode *aNode,int aN,const bool *aData);
	static int
		GetBoolArray(const DOMNode *aNode,bool *&rData);
	// INT ARRAY
	static void
		SetIntArray(DOMNode *aNode,int aN,const int *aData);
	static int
		GetIntArray(const DOMNode *aNode,int *&rData);
	// DOUBLE ARRAY
	static void
		SetDblArray(DOMNode *aNode,int aN,const double *aData);
	static int
		GetDblArray(const DOMNode *aNode,double *&rData);
	// STRING ARRAY
	static void
		SetStrArray(DOMNode *aNode,int aN,char **aData);
	static void
		SetStrArray(DOMNode *aNode,int aN,std::string *aData);
	static int
		GetStrArray(const DOMNode *aNode,char** &rData);
	static int
		GetStrArray(const DOMNode *aNode,std::string* &rData);

	//--------------------------------------------------------------------------
	// ELEMENT ATTRIBUTES
	//--------------------------------------------------------------------------
	static void
		SetAttribute(DOMNode *aNode,const std::string &aName,
		const std::string &aValue);
	static char*
		GetAttribute(DOMNode *aNode,const std::string &aName);


//=============================================================================
};	// END CLASS rdXMLNode
//=============================================================================
//=============================================================================

#endif // __rdXMLNode_h__
