// RegisterTypes_rdSimulation.cpp
// author: Frank C. Anderson
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <iostream>
#include <NMBLTK/Tools/rdObject.h>
#include "RegisterTypes_rdSimulation.h"
#include "rdActuatorSet.h"
#include "rdContactForceSet.h"
#include "rdForce.h"
#include "rdTorque.h"
#include "rdMuscle.h"
#include "rdGeneralizedForce.h"
#include "rdAnalysisSet.h"
#include <NMBLTK/Simulation/Control/rdControlSet.h>
#include <NMBLTK/Simulation/Control/rdControlConstant.h>
#include <NMBLTK/Simulation/Control/rdControlLinear.h>
#include <NMBLTK/Simulation/SIMM/simmBody.h>
#include <NMBLTK/Simulation/SIMM/simmBodyScale.h>
#include <NMBLTK/Simulation/SIMM/simmBone.h>
#include <NMBLTK/Simulation/SIMM/simmConstant.h>
#include <NMBLTK/Simulation/SIMM/simmCoordinate.h>
#include <NMBLTK/Simulation/SIMM/simmGenericModelParams.h>
#include <NMBLTK/Simulation/SIMM/simmIKParams.h>
#include <NMBLTK/Simulation/SIMM/simmIKTrialParams.h>
#include <NMBLTK/Simulation/SIMM/simmJoint.h>
#include <NMBLTK/Simulation/SIMM/simmKinematicsEngine.h>
#include <NMBLTK/Simulation/SIMM/simmMarker.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerPair.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerPlacementParams.h>
#include <NMBLTK/Simulation/SIMM/simmMarkerSet.h>
#include <NMBLTK/Simulation/SIMM/simmMeasurement.h>
#include <NMBLTK/Simulation/SIMM/simmModel.h>
#include <NMBLTK/Simulation/SIMM/simmMotionEvent.h>
#include <NMBLTK/Simulation/SIMM/simmMuscle.h>
#include <NMBLTK/Simulation/SIMM/simmMuscleGroup.h>
#include <NMBLTK/Simulation/SIMM/simmMuscleViaPoint.h>
#include <NMBLTK/Simulation/SIMM/simmMusclePoint.h>
#include <NMBLTK/Simulation/SIMM/simmPoint.h>
#include <NMBLTK/Simulation/SIMM/simmRotationDof.h>
#include <NMBLTK/Simulation/SIMM/simmScalingParams.h>
#include <NMBLTK/Simulation/SIMM/simmSubject.h>
#include <NMBLTK/Simulation/SIMM/simmTranslationDof.h>

using namespace std;


//_____________________________________________________________________________
/**
 * The purpose of this routine is to register all class types exported by
 * the rdSimulation library.
 */
RDSIMULATION_API void RegisterTypes_rdSimulation()
{
	cout<<"RegisterTypes_rdSimulation:\n";

	rdObject::RegisterType( rdControlSet() );
	rdObject::RegisterType( rdControlConstant() );
	rdObject::RegisterType( rdControlLinear() );
	rdObject::RegisterType( rdControlLinearNode() );

	rdObject::RegisterType( rdActuatorSet() );
	rdObject::RegisterType( rdForce() );
	rdObject::RegisterType( rdGeneralizedForce() );
	rdObject::RegisterType( rdTorque() );
	//rdObject::RegisterType( rdMuscle() );

	rdObject::RegisterType( rdContactForceSet() );

	rdObject::RegisterType( rdAnalysisSet() );
	rdObject::RegisterType( simmBody() );
	rdObject::RegisterType( simmBodyScale() );
	rdObject::RegisterType( simmBone() );
	rdObject::RegisterType( simmConstant() );
	rdObject::RegisterType( simmCoordinate() );
	rdObject::RegisterType( simmGenericModelParams() );
	rdObject::RegisterType( simmIKParams() );
	rdObject::RegisterType( simmIKTrialParams() );
	rdObject::RegisterType( simmJoint() );
	rdObject::RegisterType( simmKinematicsEngine() );
	rdObject::RegisterType( simmMarker() );
	rdObject::RegisterType( simmMarkerPair() );
	rdObject::RegisterType( simmMarkerPlacementParams() );
	rdObject::RegisterType( simmMarkerSet() );
	rdObject::RegisterType( simmMeasurement() );
	rdObject::RegisterType( simmModel() );
	rdObject::RegisterType( simmMotionEvent() );
	rdObject::RegisterType( simmMuscle() );
	rdObject::RegisterType( simmMuscleGroup() );
	rdObject::RegisterType( simmMuscleViaPoint() );
	rdObject::RegisterType( simmMusclePoint() );
	rdObject::RegisterType( simmPoint() );
	rdObject::RegisterType( simmRotationDof() );
	rdObject::RegisterType( simmScalingParams() );
	rdObject::RegisterType( simmSubject() );
	rdObject::RegisterType( simmTranslationDof() );

	//rdObject::RegisterType( rdIntegCallbackSet() );
	//rdObject::RegisterType( rdDerivCallbackSet() );

}

