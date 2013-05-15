
// ----- osimCommon library
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
%include <OpenSim/Common/Object.h>
%include <OpenSim/Common/ObjectGroup.h>

// None is a python keyword.
%rename(NoneType) OpenSim::Geometry::None;
%include <OpenSim/Common/Geometry.h>

// None is a python keyword.
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
