// rdSTL.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Copyright 2004 Realistic Dynamics, Inc.
// All rights reserved.
//
// Please do not read, copy, distribute, or use without permission.
// Contact: Frank C. Anderson, fca@RealisticDynamics.com
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RDTOOLSTEMPLATES


// INCLUDES
#include "rdToolsDLL.h"
#include <string>
#include "rdArray.h"
#include "rdArrayPtrs.h"
#include "rdNamedValueArray.h"
#include "rdSet.h"
#include "rdMaterial.h"



#ifdef WIN32

template class RDTOOLS_API rdArray<bool>;
template class RDTOOLS_API rdArray<int>;
template class RDTOOLS_API rdArray<double>;
template class RDTOOLS_API rdArray<std::string>;

template class RDTOOLS_API rdNamedValueArray<int>;
template class RDTOOLS_API rdNamedValueArray<double>;

template class RDTOOLS_API rdSet<rdMaterial>;

#endif  // WIN32


typedef rdArray<bool> rdArrayBool;
typedef rdArray<int> rdArrayInt;
typedef rdArray<double> rdArrayDbl;
typedef rdArray<std::string> rdArrayStr;

typedef rdNamedValueArray<int> rdNamedValueArrayInt;
typedef rdNamedValueArray<double> rdNamedValueArrayDbl;

typedef rdSet<rdMaterial> rdSetMaterial;

