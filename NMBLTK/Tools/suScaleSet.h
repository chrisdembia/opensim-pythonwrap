// suScaleSet.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Stanford University
// All rights reserved.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __suScaleSet_h__
#define __suScaleSet_h__

// INCLUDES
#include "suScale.h"
#include "rdSet.h"

class suPipeline40;
class rdStorage;
//class rdModel;

//=============================================================================
/*
 * A set of scale factors to scale a model 
 *
 * @author Ayman Habib
 * @version 1.0
 */
class RDTOOLS_API suScaleSet : public rdSet<suScale>
{
private:
	void setNull();
public:
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
	suScaleSet();
	suScaleSet(const std::string& scalesFileName);
	~suScaleSet(void);
};
#endif