// RegisterTypes_suAnalyses.h
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __RegisterTypes_suAnalyses_h__
#define __RegisterTypes_suAnalyses_h__

#include <NMBLTK/Analyses/suAnalysesDLL.h>


extern "C" {

SUANALYSES_API void RegisterTypes_suAnalyses(); 

}

class suAnalysesInstantiator
{
public:
	suAnalysesInstantiator();
private:
	void registerDllClasses();
};

#endif // __RegisterTypes_suAnalyses_h__


