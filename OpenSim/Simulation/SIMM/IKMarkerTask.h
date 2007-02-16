#ifndef __IKMarkerTask_h__
#define __IKMarkerTask_h__

#include <OpenSim/Simulation/rdSimulationDLL.h>
#include "IKTask.h"

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * @authors Eran Guendelman
 * @version 1.0
 */

class RDSIMULATION_API IKMarkerTask : public IKTask
{
public:
	IKMarkerTask();
	IKMarkerTask(const IKMarkerTask &aIKMarkerTask);
	virtual Object* copy() const;

#ifndef SWIG
	IKMarkerTask& operator=(const IKMarkerTask &aIKMarkerTask);
#endif

//=============================================================================
};	// END of class IKMarkerTask
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __IKMarkerTask_h__
