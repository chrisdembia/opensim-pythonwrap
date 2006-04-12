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
	rdArrayPtrs<simmBody>&	bodies = sModel.getBodies();
	// 
	for (i = 0; i < bodies.getSize(); i++)
	{
		for (j = 0; j < aScaleSet.getSize(); j++)
		{
			suScale *aScale = aScaleSet.get(j);
			if (bodies[i]->getName() == aScale->getSegmentName())
			{
				rdArray<double> scaleFactors(1.0, 3);
				aScale->getScaleFactors(scaleFactors);
				bodies[i]->scale(scaleFactors, aPreserveMassDist);	
			}
		}
	}

	// Now that the masses of the individual bodies have
	// been scaled (if aPreserveMassDist == false), get the
	// total mass and compare it to aFinalMass in order to
	// determine how much to scale the body masses again,
	// so that the total model mass comes out to aFinalMass.
	if (aFinalMass > 0.0)
	{
		double mass = sModel.getMass();
		if (mass > 0.0)
		{
			double factor = pow(aFinalMass / mass, 1.0 / 3.0);
			rdArray<double> scaleFactor(factor, 3);
			for (i = 0; i < bodies.getSize(); i++)
				bodies[i]->scaleInertialProperties(scaleFactor);	
		}
	}

	// Now scale the joints.
	simmKinematicsEngine &engine = sModel.getSimmKinematicsEngine();
	for (i = 0; i < engine.getNumJoints(); i++){
		engine.getJoint(i)->scale(aScaleSet); 
	}

	return true;
}
