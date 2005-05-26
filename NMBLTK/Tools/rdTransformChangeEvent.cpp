//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2005 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "rdTransformChangeEvent.h"
//=============================================================================
// DESTRUCTOR AND CONSTRUCTORS
//=============================================================================
//_____________________________________________________________________________
/**
 * Destructor.
 */

rdTransformChangeEvent::~rdTransformChangeEvent() {};
//_____________________________________________________________________________
/**
 * Constructor from a source object
 */
rdTransformChangeEvent::rdTransformChangeEvent(const rdObject& aSource):
rdEvent(aSource)
{}
