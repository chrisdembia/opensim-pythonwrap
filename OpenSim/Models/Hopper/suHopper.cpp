// suHopper.cpp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Authors:  Ines Barbosa and Clay Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=============================================================================
// INCLUDES
//=============================================================================
#include "OpenSim/Models/SdfastEngine/SdfastEngineDLL.h"
#include "OpenSim/Models/SdfastEngine/SdfastEngine.h"
#include "OpenSim/Models/SdfastEngine/RegisterTypes_SdfastEngine.h"
#include "OpenSim/Simulation/SIMM/AbstractModel.h"

using namespace OpenSim;

void SDFAST_ENGINE_API test()
{
	CreateModel();
	CreateModel_File("");
	RegisterTypes_SdfastEngine();
	//SdfastEngine *engine = new SdfastEngine();
	//engine->registerTypes();
}
