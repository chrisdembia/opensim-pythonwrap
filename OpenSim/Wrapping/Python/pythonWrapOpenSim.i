%module opensim

/* From Java .i file: #pragma SWIG nowarn=822,451,503,516,325 */
// warning 314: print is a python keyword, renaming to _print.
// warning 451: Setting a const char * variable may leak memory. 
#pragma SWIG nowarn=314

%feature("autodoc", "3");

/*
// TODO ideally would not be redefining exceptions. Temporary so I can move
// forward.
namespace std {
    class exception {
        public:
            exception();
            exception(const exception& rhs);
            virtual ~exception();
            virtual const char *what(void);
    };
}
*/

%{
#include <OpenSim/version.h>
#include <SimTKsimbody.h>
#include <OpenSim/Common/osimCommonDLL.h>
#include <OpenSim/Simulation/osimSimulationDLL.h>
#include <OpenSim/Common/Exception.h>
#include <OpenSim/Common/Array.h>
#include <OpenSim/Common/ArrayPtrs.h>
#include <OpenSim/Common/AbstractProperty.h>
#include <OpenSim/Common/PropertyGroup.h>
#include <OpenSim/Common/Object.h>
#include <OpenSim/Common/ObjectGroup.h>
#include <OpenSim/Common/Geometry.h>
#include <OpenSim/Common/DisplayGeometry.h>
#include <OpenSim/Common/Set.h>
#include <OpenSim/Common/GeometrySet.h>
#include <OpenSim/Common/VisibleObject.h>
#include <OpenSim/Common/StateVector.h>
#include <OpenSim/Common/StorageInterface.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/Scale.h>
#include <OpenSim/Common/ScaleSet.h>
#include <OpenSim/Common/Units.h>
#include <OpenSim/Common/IO.h>
#include <OpenSim/Common/Function.h>
#include <OpenSim/Common/Constant.h>
#include <OpenSim/Common/SimmSpline.h>
#include <OpenSim/Common/StepFunction.h>
#include <OpenSim/Common/PiecewiseConstantFunction.h>
#include <OpenSim/Common/LinearFunction.h>
#include <OpenSim/Common/PiecewiseLinearFunction.h>
#include <OpenSim/Common/MultiplierFunction.h>
#include <OpenSim/Common/GCVSpline.h>
#include <OpenSim/Common/Sine.h>
#include <OpenSim/Common/SmoothSegmentedFunctionFactory.h>
#include <OpenSim/Common/SmoothSegmentedFunction.h>
#include <OpenSim/Common/XYFunctionInterface.h>
#include <OpenSim/Common/FunctionSet.h>

#include <OpenSim/Common/LoadOpenSimLibrary.h>

#include <OpenSim/Simulation/Model/ModelComponent.h>
#include <OpenSim/Simulation/Model/ModelComponentSet.h>
#include <OpenSim/Simulation/Model/ComponentSet.h>

#include <OpenSim/Simulation/Solver.h>
#include <OpenSim/Simulation/InverseDynamicsSolver.h>

#include <OpenSim/Simulation/Model/Force.h>
#include <OpenSim/Simulation/Model/PrescribedForce.h>
#include <OpenSim/Simulation/Model/CoordinateLimitForce.h>
#include <OpenSim/Simulation/Model/ExternalForce.h>
#include <OpenSim/Simulation/Model/ContactGeometry.h>
#include <OpenSim/Simulation/Model/ContactHalfSpace.h>
#include <OpenSim/Simulation/Model/ContactMesh.h>
#include <OpenSim/Simulation/Model/ContactSphere.h>

#include <OpenSim/Simulation/Model/ElasticFoundationForce.h>
#include <OpenSim/Simulation/Model/HuntCrossleyForce.h>

#include <OpenSim/Simulation/Model/ContactGeometrySet.h>
#include <OpenSim/Simulation/Model/Probe.h>
#include <OpenSim/Simulation/Model/ProbeSet.h>
#include <OpenSim/Simulation/Model/SystemEnergyProbe.h>
#include <OpenSim/Simulation/Model/JointInternalPowerProbe.h>
#include <OpenSim/Simulation/Model/ActuatorPowerProbe.h>
#include <OpenSim/Simulation/Model/ActuatorForceProbe.h>
#include <OpenSim/Simulation/Model/MuscleActiveFiberPowerProbe.h>
#include <OpenSim/Simulation/Model/MuscleMetabolicPowerProbeUmberger2010.h>

#include <OpenSim/Simulation/Model/ModelDisplayHints.h>
#include <OpenSim/Simulation/Model/ModelVisualizer.h>

#include <OpenSim/Simulation/Model/Actuator.h>
#include <OpenSim/Simulation/Model/ModelVisualizer.h>
#include <OpenSim/Simulation/Model/Model.h>
#include <OpenSim/Simulation/Control/Control.h>
#include <OpenSim/Simulation/Control/ControlSet.h>
#include <OpenSim/Simulation/Control/ControlConstant.h>
#include <OpenSim/Simulation/Control/ControlLinearNode.h>
#include <OpenSim/Simulation/Control/ControlLinear.h>
#include <OpenSim/Simulation/Control/Controller.h>
#include <OpenSim/Simulation/Control/PrescribedController.h>
#include <OpenSim/Simulation/Manager/Manager.h>
#include <OpenSim/Simulation/Model/Analysis.h>
#include <OpenSim/Simulation/Model/AnalysisSet.h>
#include <OpenSim/Simulation/Model/ForceSet.h>
#include <OpenSim/Simulation/Model/ControllerSet.h>
#include <OpenSim/Simulation/Model/ExternalLoads.h>
#include <OpenSim/Simulation/Model/AbstractTool.h>
#include <OpenSim/Simulation/Model/Marker.h>
#include <OpenSim/Simulation/Model/MarkerSet.h>
#include <OpenSim/Simulation/SimbodyEngine/SimbodyEngine.h>

#include <OpenSim/Tools/osimToolsDLL.h>
#include <OpenSim/Tools/ForwardTool.h>

#include <OpenSim/Analyses/osimAnalysesDLL.h>
#include <OpenSim/Analyses/Actuation.h>
#include <OpenSim/Analyses/Kinematics.h>
#include <OpenSim/Analyses/MuscleAnalysis.h>
#include <OpenSim/Analyses/InverseDynamics.h>
#include <OpenSim/Analyses/StaticOptimization.h>
#include <OpenSim/Analyses/ForceReporter.h>
#include <OpenSim/Analyses/PointKinematics.h>
#include <OpenSim/Analyses/BodyKinematics.h>
#include <OpenSim/Analyses/JointReaction.h>
#include <OpenSim/Analyses/StatesReporter.h>
#include <OpenSim/Analyses/InducedAccelerations.h>
#include <OpenSim/Analyses/ProbeReporter.h>

#include <OpenSim/Simulation/Wrap/WrapObject.h>
#include <OpenSim/Simulation/Wrap/PathWrapPoint.h>
#include <OpenSim/Simulation/Wrap/WrapSphere.h>
#include <OpenSim/Simulation/Wrap/WrapCylinder.h>
#include <OpenSim/Simulation/Wrap/WrapTorus.h>
#include <OpenSim/Simulation/Wrap/WrapEllipsoid.h>
#include <OpenSim/Simulation/Wrap/WrapObjectSet.h>
#include <OpenSim/Simulation/Wrap/PathWrap.h>
#include <OpenSim/Simulation/Wrap/PathWrapSet.h>
#include <OpenSim/Simulation/Wrap/WrapCylinderObst.h>
#include <OpenSim/Simulation/Wrap/WrapSphereObst.h>
#include <OpenSim/Simulation/Wrap/WrapDoubleCylinderObst.h>

#include <OpenSim/Simulation/SimbodyEngine/Body.h>
#include <OpenSim/Simulation/Model/BodySet.h>

#include <OpenSim/Simulation/Model/BodyScale.h>
#include <OpenSim/Simulation/Model/BodyScaleSet.h>

#include <OpenSim/Simulation/SimbodyEngine/Coordinate.h>
#include <OpenSim/Simulation/Model/CoordinateSet.h>

#include <OpenSim/Simulation/SimbodyEngine/TransformAxis.h>
#include <OpenSim/Simulation/SimbodyEngine/SpatialTransform.h>

#include <OpenSim/Simulation/SimbodyEngine/Joint.h>
#include <OpenSim/Simulation/SimbodyEngine/FreeJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/CustomJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/EllipsoidJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/BallJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/PinJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/SliderJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/WeldJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/GimbalJoint.h>
#include <OpenSim/Simulation/SimbodyEngine/UniversalJoint.h>
#include <OpenSim/Simulation/Model/JointSet.h>

#include <OpenSim/Simulation/Model/Marker.h>

#include <OpenSim/Simulation/Model/PathPoint.h>
#include <OpenSim/Simulation/Model/PathPointSet.h>
#include <OpenSim/Simulation/Model/ConditionalPathPoint.h>
#include <OpenSim/Simulation/Model/MovingPathPoint.h>
#include <OpenSim/Simulation/Model/GeometryPath.h>
#include <OpenSim/Simulation/Model/Ligament.h>

#include <OpenSim/Simulation/SimbodyEngine/Constraint.h>
#include <OpenSim/Simulation/Model/ConstraintSet.h>
#include <OpenSim/Simulation/SimbodyEngine/WeldConstraint.h>
#include <OpenSim/Simulation/SimbodyEngine/PointConstraint.h>
#include <OpenSim/Simulation/SimbodyEngine/ConstantDistanceConstraint.h>
#include <OpenSim/Simulation/SimbodyEngine/CoordinateCouplerConstraint.h>
#include <OpenSim/Simulation/SimbodyEngine/PointOnLineConstraint.h>

#include <OpenSim/Actuators/osimActuatorsDLL.h>
#include <OpenSim/Simulation/Model/Actuator.h>
#include <OpenSim/Simulation/Model/PathActuator.h>
#include <OpenSim/Simulation/Model/Muscle.h>
#include <OpenSim/Simulation/Model/ActivationFiberLengthMuscle.h>
#include <OpenSim/Simulation/Model/PointToPointSpring.h>
#include <OpenSim/Simulation/Model/PathSpring.h>
#include <OpenSim/Simulation/Model/BushingForce.h>
#include <OpenSim/Simulation/Model/FunctionBasedBushingForce.h>
#include <OpenSim/Simulation/Model/ExpressionBasedBushingForce.h>
#include <OpenSim/Actuators/CoordinateActuator.h>
#include <OpenSim/Actuators/PointActuator.h>
#include <OpenSim/Actuators/TorqueActuator.h>
#include <OpenSim/Actuators/PointToPointActuator.h>
#include <OpenSim/Actuators/SpringGeneralizedForce.h>
#include <OpenSim/Actuators/Thelen2003Muscle.h>
#include <OpenSim/Actuators/RigidTendonMuscle.h>
#include <OpenSim/Actuators/Millard2012EquilibriumMuscle.h>
#include <OpenSim/Actuators/Millard2012AccelerationMuscle.h>

#include <OpenSim/Tools/IKTask.h>
#include <OpenSim/Tools/IKMarkerTask.h>
#include <OpenSim/Tools/IKCoordinateTask.h>
#include <OpenSim/Tools/IKTaskSet.h>
#include <OpenSim/Common/MarkerData.h>

#include <OpenSim/Tools/MarkerPair.h>
#include <OpenSim/Tools/MarkerPairSet.h>
#include <OpenSim/Tools/Measurement.h>
#include <OpenSim/Tools/MeasurementSet.h>

#include <OpenSim/Tools/GenericModelMaker.h>
#include <OpenSim/Tools/ModelScaler.h>
#include <OpenSim/Tools/MarkerPlacer.h>
#include <OpenSim/Tools/Tool.h>

#include <OpenSim/Simulation/Solver.h>
#include <OpenSim/Simulation/AssemblySolver.h>
#include <OpenSim/Simulation/InverseKinematicsSolver.h>
#include <OpenSim/Tools/DynamicsTool.h>
#include <OpenSim/Tools/InverseDynamicsTool.h>

#include <OpenSim/Tools/CMCTool.h>
#include <OpenSim/Tools/RRATool.h>
#include <OpenSim/Tools/ScaleTool.h>
#include <OpenSim/Tools/AnalyzeTool.h>
#include <OpenSim/Tools/InverseKinematicsTool.h>

using namespace OpenSim;
using namespace SimTK;

%}

%rename(OpenSimObject) OpenSim::Object;
%rename(OpenSimException) OpenSim::Exception;

%include "exception.i"
%include "cpointer.i"
%include "std_string.i"
%include "typemaps.i"


%include <OpenSim/version.h>

// For modularity, [chrisdembia] split off the SimTK content to a separate
// .i file.
%include "SimTK.i"

// Exceptions.
// TODO could create multiple exception types.
// SWIG_exception comes from exception.i.
// TODO std::exception is being ignored.
// TODO see 'except' for swig.
%exception {
    try {
        $action
    }
    catch(std::exception& _ex){
        SWIG_exception(SWIG_RuntimeError, _ex.what());
    }
}

// ----- osimCommon library
%include <OpenSim/Common/osimCommonDLL.h>
%include <OpenSim/Common/Exception.h>

%include <OpenSim/Common/Array.h>
/* Convert from C --> Python; taken from swig2.0 docs */
// ArrayDouble.get(int) returns a double*; dont want that.
// TODO
//%typemap(out) double* {
//    $result = ptrvalue($1);
//}

%template(ArrayDouble) OpenSim::Array<double>;
// TODO other classes? string?

%include <OpenSim/Common/ArrayPtrs.h>
%include <OpenSim/Common/AbstractProperty.h>

%include <OpenSim/Common/Property.h>

/* TODO operator[] doesn't work for Property's.
%extend Property {
    double __getitem__(int i)const; // i is the index, returns the data
    void __setitem__(int i,double d); // i is the index, d is the data
}
*/
%include <OpenSim/Common/PropertyGroup.h>
%template(ArrayPtrsPropertyGroup) OpenSim::ArrayPtrs<OpenSim::PropertyGroup>;

/* TODO getfunctionclassnames extend 
   TODO javacode -> equals, hashcode, pickable, 
 */
%include <OpenSim/Common/Object.h>
%include <OpenSim/Common/ObjectGroup.h>

%include <OpenSim/Common/Geometry.h>
%include <OpenSim/Common/DisplayGeometry.h>
%include <OpenSim/Common/Set.h>
%template(SetGeometry) OpenSim::Set<OpenSim::DisplayGeometry>;
%include <OpenSim/Common/GeometrySet.h>
%include <OpenSim/Common/VisibleObject.h>
%include <OpenSim/Common/StateVector.h>
%include <OpenSim/Common/StorageInterface.h>
%include <OpenSim/Common/Storage.h>
%include <OpenSim/Common/Units.h>
%include <OpenSim/Common/IO.h>
%include <OpenSim/Common/Function.h>

%template(SetFunctions) OpenSim::Set<OpenSim::Function>;
%include <OpenSim/Common/FunctionSet.h>

%include <OpenSim/Common/Constant.h>
%include <OpenSim/Common/SimmSpline.h>
%include <OpenSim/Common/StepFunction.h>
%include <OpenSim/Common/PiecewiseConstantFunction.h>
%include <OpenSim/Common/LinearFunction.h>
%include <OpenSim/Common/PiecewiseLinearFunction.h>
%include <OpenSim/Common/MultiplierFunction.h>
%include <OpenSim/Common/GCVSpline.h>
%include <OpenSim/Common/Sine.h>
%include <OpenSim/Common/SmoothSegmentedFunctionFactory.h>
%include <OpenSim/Common/SmoothSegmentedFunction.h>
/*
1. Array.getitem() instead of get(), is this the expected use case?
2. Property::operator[]
3. Property::operator=
4. Set up a normal python package, with setup.py, etc.
5. implement __str__() as toString().
6. For Vec3, use np.array, etc.
7. Object class does not exist? virtual?
8. Geometry should be virtual.
9. Can extend and add a __iter__ method to allow for python iteration.
*/
