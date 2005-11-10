// rdToolsTemplates.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __rdToolsTemplates_h__
#define __rdToolsTemplates_h__


// NOTES:
// This header file should not be included in any file that is a part of
// the rdTools library.  If it is included in files in the rdTools project,
// templates will be instantiated multiple times.
//
// Other projects, such as libraries other than rdTools or executables, should
// include this header file to import the template classes below.
//


// INCLUDES
#include "rdToolsDLL.h"
#include <string>
#include "rdArray.h"
#include "rdArrayPtrs.h"
#include "rdNamedValueArray.h"
#include "rdSet.h"
#include "rdMaterial.h"


#ifdef WIN32

extern template class RDTOOLS_API rdArray<bool>;
extern template class RDTOOLS_API rdArray<int>;
extern template class RDTOOLS_API rdArray<double>;
extern template class RDTOOLS_API rdArray<std::string>;

extern template class RDTOOLS_API rdNamedValueArray<int>;
extern template class RDTOOLS_API rdNamedValueArray<double>;

extern template class RDTOOLS_API rdSet<rdMaterial>;

#endif  // WIN32


#endif  // __rdToolsTemplates_h__
