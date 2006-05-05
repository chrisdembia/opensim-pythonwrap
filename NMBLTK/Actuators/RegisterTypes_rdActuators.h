// RegisterTypes.h
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __RegisterTypes_rdActuators_h__
#define __RegisterTypes_rdActuators_h__

#include <NMBLTK/Actuators/rdActuatorsDLL.h>


extern "C" {

RDACTUATORS_API void RegisterTypes_rdActuators(); 

}

class rdActuatorsInstantiator
{
public:
	rdActuatorsInstantiator();
private:
	void registerDllClasses();
};

#endif // __RegisterTypes_rdActuators_h__


