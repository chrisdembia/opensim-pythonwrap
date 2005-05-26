// rdBodySet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdBodySet_h__
#define __rdBodySet_h__


// INCLUDES
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdObject.h>
#include "rdBody.h"
#include <RD/Tools/rdSet.h>

#ifndef SWIG
template class RDSIMULATION_API rdSet<rdBody>;
#endif

//=============================================================================
//=============================================================================
/**
 * A class for holding and managing a set of bodies for a model.
 * The only reason it serves is for dll tag (RDSIMULATION_API)
 * accordingly there's no implementation cpp file
 *
 * @author Ayman Habib
 * @version 1.0
 */
typedef RDSIMULATION_API rdSet<rdBody> rdBodySet;
//=============================================================================


#endif // __rdBodySet_h__


