#include <NMBLTK/Tools/rdArray.h>
#include <NMBLTK/Tools/rdStorage.h>
#include <NMBLTK/Tools/suScaleSet.h>
#include <NMBLTK/SQP/rdFSQP.h>
#include <NMBLTK/Simulation/Model/nmblKinematicsEngine.h>
#include <NMBLTK/Simulation/SIMM/simmModel.h>
#include "simmScalerImpl.h"

using namespace std;

simmScalerImpl::simmScalerImpl(rdModel &aModel):
ScalerInterface(aModel)
{
}

bool simmScalerImpl::scaleModel(const suScaleSet& aScaleSet, bool aPreserveMassDist, double aFinalMass)
{

	// Here we know we're in SIMM implementation so we may convert to the concrete simm* classes
	// Though it would be better to keep using the rdModel, nmblKinematicsEngine and add whatever methods (e.g. getBodies())
	// and abstract classes (e.g. suBody and suJoint). This's all academic though until we have another 
	// kinematics engine -Ayman 2/06 
	simmModel& sModel = dynamic_cast<simmModel&> (_theModel);
	
	// Scale the muscles
	simmMuscle* sm;
	int i, j;
	for (i = 0; i < sModel.getNumberOfMuscles(); i++)
	{
		if (sm = dynamic_cast<simmMuscle*>(sModel.getMuscle(i)))
			sm->scale(aScaleSet);
	}

	// Scale the rest (KinematicsEngine stuff)
	sModel.getSimmKinematicsEngine().scale(aScaleSet, aPreserveMassDist, aFinalMass);
	return true;
}
