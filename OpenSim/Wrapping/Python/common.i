// ----- osimCommon library

%module common

%{

#define SWIG_FILE_WITH_INIT

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

%include "pythonWrapOpenSim.i"

%rename(OpenSimObject) OpenSim::Object;
%rename(OpenSimException) OpenSim::Exception;

%include <OpenSim/version.h>

%include <OpenSim/Common/osimCommonDLL.h>
%include <OpenSim/Common/Exception.h>

%typemap(in, numinputs=0) OpenSim::Array<double> &rTimes (OpenSim::Array<double> temp) {
    $1 = &temp;
}
%typemap(argout) OpenSim::Array<double> &rTimes {
    $result = PyList_New($1->getSize());
    for (int i = 0; i < $1->getSize(); i++)
    {
        PyList_SetItem($result, i, PyFloat_FromDouble($1->get(i)));
    }
//    PyTuple_SetItem($result, 0, PyInt_FromLong((long)result));
//    PyTuple_SetItem($result, 1, $1);
//    $result = $1;
}

%typemap(in, numinputs=1) OpenSim::Array<double> &rData (OpenSim::Array<double> temp) {
    $1 = &temp;
}
%typemap(argout) OpenSim::Array<double> &rData {
    // WOWEE
    $result = PyList_New($1->getSize());
    for (int i = 0; i < $1->getSize(); i++)
    {
        PyList_SetItem($result, i, PyFloat_FromDouble($1->get(i)));
    }
//    PyTuple_SetItem($result, 0, PyInt_FromLong((long)result));
//    PyTuple_SetItem($result, 1, $1);
//    $result = $1;
}
%typemap(out) OpenSim::Array<double> {
    // WOWEE
    $result = PyList_New($1.getSize());
    for (int i = 0; i < $1.getSize(); i++)
    {
        PyList_SetItem($result, i, PyFloat_FromDouble($1.get(i)));
    }
//    PyTuple_SetItem($result, 0, PyInt_FromLong((long)result));
//    PyTuple_SetItem($result, 1, $1);
//    $result = $1;
}
//%apply(double ARGOUT_ARRAY1[ANY]) {(double *& rTimes)};
//%numpy_typemaps(OpenSim::Array<double>, NPY_DOUBLE, double);
//%apply(OpenSim::Array<double> ARGOUT_ARRAY1[ANY]) {(OpenSim::Array<double>& rTimes)};


%include <OpenSim/Common/Array.h>
/* Convert from C --> Python; taken from swig2.0 docs */
// ArrayDouble.get(int) returns a double*; dont want that.
// TODO
//%typemap(out) double* {
//    $result = ptrvalue($1);
//}

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

%extend OpenSim::Object {
    std::string __str__() {
        return $self->toString();
    }
}
%include <OpenSim/Common/Object.h>
%include <OpenSim/Common/ObjectGroup.h>

// 'None' is a python keyword.
%rename(NoneType) OpenSim::Geometry::None;
%include <OpenSim/Common/Geometry.h>

// 'None' is a python keyword.
%rename(NonePreference) OpenSim::DisplayGeometry::None;
%include <OpenSim/Common/DisplayGeometry.h>

/*
   TODO neither of these work.
%apply OpenSim::Array<std::string>& OUTPUT {OpenSim::Array< std::string > &rNames};
%typemap(out) OpenSim::Array< std::string > &rNames {
    // $1 is a python list.
    $result = PyList_New();
    for (int i = 0; i , $1.size(); i++) {
        PyList_Append($result, $1[i]);
    }
}
*/

%include <OpenSim/Common/Set.h>
// Extends all templated versions of Set to return both a list() and a dict().
// TODO really need docstrings for these methods.
// TODO how to write an iterator in python C api:
// http://stackoverflow.com/questions/1815812/how-to-create-a-generator-iterator-with-the-python-c-api
// http://eli.thegreenplace.net/2012/04/05/implementing-a-generatoryield-in-a-python-c-extension/
//     T& __iter__():
/* TODO don't know how to typecast to PyObject *
%extend OpenSim::Set<OpenSim::Function> {

    PyObject * dict() {
        PyObject * d = PyDict_New();
        int size = $self->getSize();
        for (int i = 0; i < size; i++) {
            PyDict_SetItemString(d, $self->get(i).getName().c_str(),
                    (PyObject *)$self->get(i));
        }
        return d;
    }

};
*/

%extend OpenSim::Set {
    void __setitem__(int i, T& v) {
        if (i >= $self->getSize()) {
            PyErr_Format(PyExc_IndexError,
                    "Index less than %i required. "
                    "Index %i given.",
                    $self->getSize(), i);
        } else {
            $self->operator[](i) = v;
        }
    }
    T& __getitem__(int i) {
        return $self->operator[](i);
    }

    int __len__() {
        return $self->getSize();
    }

    bool __contains__(T& value) {
        /* TODO this check seems to have no effect.
        if (value.getName() == "")
            PyErr_SetString(PyExc_ValueError,
                    "Object has empty name. Cannot check if Set contains it.");
         */
        if ($self->contains(value.getName()))
            return true;
        else
            return false;
    }
    // TODO getNames returns list of str's.
};
%template(SetGeometry) OpenSim::Set<OpenSim::DisplayGeometry>;
%include <OpenSim/Common/GeometrySet.h>
%include <OpenSim/Common/VisibleObject.h>
%include <OpenSim/Common/StateVector.h>
%include <OpenSim/Common/StorageInterface.h>

//%extend OpenSim::StorageInterface {
%extend OpenSim::Storage {
    OpenSim::Array<double> getDataColumn(const std::string &columnName) {
        OpenSim::Array<double> a;
        $self->getDataColumn(columnName, a);
        return a;
    }
}

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
%include <OpenSim/Common/XYFunctionInterface.h>

%template(ArrayXYPoint) OpenSim::Array<XYPoint>;
%template(ArrayBool) OpenSim::Array<bool>;
%template(ArrayDouble) OpenSim::Array<double>;
%template(ArrayInt) OpenSim::Array<int>;
%template(ArrayStr) OpenSim::Array<std::string>;
%template(ArrayObjPtr) OpenSim::Array<OpenSim::Object*>;
%template(ArrayPtrsObj) OpenSim::ArrayPtrs<OpenSim::Object>;

%include <OpenSim/Common/Scale.h>
%template(SetScales) OpenSim::Set<OpenSim::Scale>;
%include <OpenSim/Common/ScaleSet.h>
%include <OpenSim/Common/MarkerData.h>
