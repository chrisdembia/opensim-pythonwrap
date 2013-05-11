
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

// None is a python keyword.
%rename(NoneType) OpenSim::Geometry::None;
%include <OpenSim/Common/Geometry.h>

%rename(NonePreference) OpenSim::DisplayGeometry::None;
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
// TODO does not avert warning intended to avert %template(FunctionDouble) SimTK::Function_<double>;

%template(SetFunctions) OpenSim::Set<OpenSim::Function>;
%include <OpenSim/Common/FunctionSet.h>

// Extends all templated versions of Set to return both a list() and a dict().
// TODO really need docstrings for these methods.
// TODO how to write an iterator in python C api:
// http://stackoverflow.com/questions/1815812/how-to-create-a-generator-iterator-with-the-python-c-api
// http://eli.thegreenplace.net/2012/04/05/implementing-a-generatoryield-in-a-python-c-extension/
//     T& __iter__():
//    bool __contains__(T& value) {
//        if $self->contains(value.getName())
//            return true;
//        else
//            return false;
// TODO use PyDict_Contains()
//    }
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
%extend OpenSim::Set<OpenSim::Function> {
    bool __contains__(OpenSim::Function& value) {
        if (value.getName() == "")
            PyErr_SetString(PyExc_ValueError,
                    "Object has empty name. Cannot check if Set contains it.");
        if ($self->contains(value.getName()))
            return true;
        else
            return false;
    }
};

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
