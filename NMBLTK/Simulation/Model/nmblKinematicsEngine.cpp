// nmblKinematicsEngine.cpp
// Authors: Frank C. Anderson, Ayman Habib, Peter Loan
/*
 * Copyright (c) 2005, Stanford University. All rights reserved. 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions
 * are met: 
 *  - Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 *  - Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  - Neither the name of the Stanford University nor the names of its 
 *    contributors may be used to endorse or promote products derived 
 *    from this software without specific prior written permission. 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE. 
 */

//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include <string>
#include <math.h>
#include <float.h>
#include <NMBLTK/Tools/rdMath.h>
#include <NMBLTK/Tools/rdMtx.h>
#include <NMBLTK/Tools/rdMemory.h>
#include "nmblKinematicsEngine.h"

using namespace std;


//=============================================================================
// CONSTANTS
//=============================================================================



//=============================================================================
// CONSTRUCTOR(S) AND DESTRUCTOR
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */
nmblKinematicsEngine::~nmblKinematicsEngine()
{
}

//_____________________________________________________________________________
/**
 * Default constructor.
 */
nmblKinematicsEngine::nmblKinematicsEngine()
{
	// NULL
	setNull();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML Document
 */
nmblKinematicsEngine::nmblKinematicsEngine(const string &aFileName) :
	rdObject(aFileName)
{
	// NULL
	setNull();

	// DESERIALIZE
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Constructor from an XML node
 */
nmblKinematicsEngine::nmblKinematicsEngine(DOMElement *aElement) :
	rdObject(aElement)
{
	// NULL
	setNull();

	// DESERIALIZE
	updateFromXMLNode();
}

//_____________________________________________________________________________
/**
 * Copy constructor.
 */
nmblKinematicsEngine::nmblKinematicsEngine(const nmblKinematicsEngine& aKE)
{
	// NULL
	setNull();
}

nmblKinematicsEngine& nmblKinematicsEngine::operator=(const nmblKinematicsEngine &aKE)
{
	// BASE CLASS
	rdObject::operator=(aKE);

	return(*this);
}

//=============================================================================
// CONSTRUCTION METHODS
//=============================================================================
//_____________________________________________________________________________
/**
 * Set NULL values for all the variable members of this class.
 */
void nmblKinematicsEngine::setNull()
{
	setupProperties();
	setType("nmblKinematicsEngine");
}


//=============================================================================
// TYPE REGISTRATION
//=============================================================================
///_____________________________________________________________________________
/**
 * Register the types of objects used by nmblKinematicsEngine and that need to be registered 
 * for xml serialization purposes
 *
 */
void nmblKinematicsEngine::setupProperties()
{	
}
