// RegisterTypes_rdSimulation.h
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __RegisterTypes_rdSimulation_h__
#define __RegisterTypes_rdSimulation_h__

#include <NMBLTK/Simulation/rdSimulationDLL.h>


extern "C" {

RDSIMULATION_API void RegisterTypes_rdSimulation(); 

}

class rdSimulationInstantiator
{
public:
	rdSimulationInstantiator();
private:
	void registerDllClasses();
};

#endif // __RegisterTypes_rdSimulation_h__


