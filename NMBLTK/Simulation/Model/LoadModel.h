// LoadModel.h
// author: Frank C. Anderson, Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __LoadModel_h__
#define __LoadModel_h__

#include <string>
#include "rdModel.h"


RDSIMULATION_API void LoadOpenSimLibraries(int argc,char **argv);
RDSIMULATION_API rdModel* LoadModel(const std::string &aModelLibraryName); 
RDSIMULATION_API rdModel* LoadModel(int argc,char **argv);


#endif // __Investigation_h__


