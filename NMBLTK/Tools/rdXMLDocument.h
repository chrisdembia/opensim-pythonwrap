// rdXMLDocument.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2002 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdXMLDocument_h__
#define __rdXMLDocument_h__


// INCLUDES
#include <iostream>	// Ayman: Remove .h extension per .NET 2003
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include "rdTools.h"


XERCES_CPP_NAMESPACE_USE
//using namespace std;	// Ayman:per .NET 2003


//=============================================================================
//=============================================================================
/**
 * A class for managing and for performing operations on an XML document.
 * The document can originate from one of two sources:  1) parsed from an
 * XML source or 2) created locally in memory.
 *
 * This product includes software developed by the
 * Apache Software Foundation (http://www.apache.org/).
 *
 * @version 1.0
 * @author Frank C. Anderson
 */
class RDTOOLS_API rdXMLDocument {

//=============================================================================
// DATA
//=============================================================================
public:
	static const XMLCh UTF8[];
	static const XMLCh VERSION[];

private:
	/** XML parser. */
	XercesDOMParser *_parser;
	/** XML document. */
	DOMDocument *_document;
	/** Name of the XML Document */
	char *_fileName;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION AND DESTRUCTION
	//--------------------------------------------------------------------------
public:
	virtual ~rdXMLDocument();
	rdXMLDocument();
	rdXMLDocument(const std::string &aFileName);
	rdXMLDocument(const rdXMLDocument &aDocument);
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// SET AND GET
	//--------------------------------------------------------------------------
	DOMDocument* getDOMDocument() const;
	void setFileName(const char *aFileName);
	const char *getFileName() const;
	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
	bool print(const std::string &aFileName=NULL);
private:
	static void CreateFormatter(std::ostream *aOstream=&std::cout);
	void printDeclaration();

//=============================================================================
};	// END CLASS rdXMLDocument
//=============================================================================
//=============================================================================



// ---------------------------------------------------------------------------
//  Local classes
// ---------------------------------------------------------------------------

class DOMPrintFormatTarget : public XMLFormatTarget
{
	std::ostream *_out;
public:
	DOMPrintFormatTarget(std::ostream *aOStream= &std::cout)  {
		_out = aOStream;
	 };
    ~DOMPrintFormatTarget() {};

    // -----------------------------------------------------------------------
    //  Implementations of the format target interface
    // -----------------------------------------------------------------------

    void writeChars(const   XMLByte* const  toWrite,
                    const   unsigned int    count,
                            XMLFormatter * const formatter)
    {
        // Surprisingly, Solaris was the only platform on which
        // required the char* cast to print out the string correctly.
        // Without the cast, it was printing the pointer value in hex.
        // Quite annoying, considering every other platform printed
        // the string with the explicit cast to char* below.
        _out->write((char *) toWrite, (int) count);
    };

private:
    // -----------------------------------------------------------------------
    //  Unimplemented methods.
    // -----------------------------------------------------------------------
    DOMPrintFormatTarget(const DOMPrintFormatTarget& other);
    void operator=(const DOMPrintFormatTarget& rhs);
};


#endif // __rdXMLDocument_h__
