#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/SQP/rdFSQP.h>
#include <NMBLTK/Simulation/Model/nmblKinematicsEngine.h>
#include "simmScalerImpl.h"

using namespace std;

simmScalerImpl::simmScalerImpl(nmblKinematicsEngine &aKinematicsEngine):
ScalerInterface(aKinematicsEngine)
{
}

bool simmScalerImpl::scaleModel(const suScaleSet& aScaleSet)
{

	// Here we know we're in SIMM implementation so we may convert to the concrete simmKinematicsEngine class
	// Though it would be better to keep using the nmblKinematicsEngine and add whatever methods (e.g. getBodies())
	// and abstract classes (e.g. suBody and suJoint). This's all academic though until we have another 
	// kinematics engine -Ayman 2/06 
	simmKinematicsEngine& engine = dynamic_cast<simmKinematicsEngine&> (_theKinematiceEngine);
	
	rdArrayPtrs<simmBody>&	bodies = engine.getBodies();

	int i, j;
	for (i = 0; i < bodies.getSize(); i++)
	{
		for (j = 0; j < aScaleSet.getSize(); j++)
		{
			suScale *aScale = aScaleSet.get(j);
			if (bodies[i]->getName() == aScale->getSegmentName())
			{
				rdArray<double> scaleFactors(1.0, 3);
				aScale->getScaleFactors(scaleFactors);
				bodies[i]->scale(scaleFactors);	
			}
		}
	}


	for (i = 0; i < engine.getNumJoints(); i++){
		engine.getJoint(i)->scale(aScaleSet); 
	}

	return true;
}
