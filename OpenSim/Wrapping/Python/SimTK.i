// Copied directly from Java's .i file, and then edited.
%include <SimTKcommon.h>

%include <SimTKcommon/Constants.h>
%include <SWIG/Vec.h>
%include <SimTKcommon/SmallMatrix.h>
// Vec3
namespace SimTK {
%template(Vec3) Vec<3>;
}

// Mat33
%include <SWIG/Mat.h>
namespace SimTK {
%template(Mat33) Mat<3, 3>;
}

// Vector and Matrix
// See http://docs.scipy.org/doc/numpy/reference/swig.interface-file.html
// for the difference between IN_ARRAY1 and INPLACE_ARRAY1: the former allows
// inputs of not just numpy arrays, but the former works more like a C++
// reference input.
// The bit of code inside the {}'s comes from the Vector_ constructor in
// BigMatrix.h.
%apply (int DIM1, double* IN_ARRAY1) {(int m, const double* cppInitialValues)};

%include <SWIG/BigMatrix.h>
namespace SimTK {
%template(MatrixBaseDouble) SimTK::MatrixBase<double>;
%template(VectorBaseDouble) SimTK::VectorBase<double>;
%template(Vector) SimTK::Vector_<double>;
%template(Matrix) SimTK::Matrix_<double>;
}

// TODO find out how to make this more general? so we don't have to redo it for
// all classes. maybe using a swig fragment or something.
%extend SimTK::Vector_<double> {
    void __setitem__(int i, double v) {
        if (i >= $self->size()) {
            PyErr_Format(PyExc_IndexError,
                    "Index less than %i required. Index %i given.",
                    $self->size(), i);
        } else {
            $self->operator[](i) = v;
        }
    }
    double __getitem__(int i) {
        return $self->operator[](i);
    }

    int __len__() {
        return $self->size();
    }
}

%extend OpenSim::Object {
    std::string __str__() {
        return $self->toString();
    }
}

/* TODO remove
%pythoncode %{
def newVector(arraylike):
    v = Vector()
    n = len(arraylike)
    v.resize(n)
    for i in range(n):
        v.set(i, arraylike[i])
    return v
%}
*/

// Functions looking for a const SimTK::Vector& will alternatively accept
// lists, tuples, etc.
// TODO allow lists to work as well...
%typemap(in) const SimTK::Vector& {
    $1 = NULL;
    if (PyTuple_Check($input)) {
        int size = PyTuple_Size($input);

        SimTK::Vector v = SimTK::Vector();
        v.resize(size);
        for (int i = 0; i < size; i++) {
            PyObject *o = PyTuple_GetItem($input, i);
            if (PyFloat_Check(o))
                v.set(i, PyFloat_AsDouble(PyTuple_GetItem($input, i)));
            else {
                PyErr_SetString(PyExc_TypeError, "tuple must contain floats");
                return NULL;
            }
        }
        $1 = &v;
        /*
    } else if (PyList_Check($input)) {
        int size = PyList_Size($input);
        SimTK::Vector v = SimTK::Vector();
        v.resize(size);
        for (int i = 0; i < size; i++) {
            PyObject *o = PyList_GetItem($input, i);
            if (PyFloat_Check(o))
                v.set(i, PyFloat_AsDouble(PyList_GetItem($input, i)));
            else {
                PyErr_SetString(PyExc_TypeError, "list must contain floats");
                return NULL;
            }
        }
        $1 = &v;
        */
    } else {
        // $1 = $input;
        PyErr_SetString(PyExc_TypeError,
                "Tuple required. Given some other type.");
        return NULL;
    }
}

%include <SWIG/SpatialAlgebra.h>
namespace SimTK {
%template(SpatialVec) Vec<2,   Vec3>;
%template(VectorOfSpatialVec) Vector_<SpatialVec>;
}
// Transform
%include <SWIG/Transform.h>
namespace SimTK {
%template(Transform) SimTK::Transform_<double>;
}

%include <SWIG/MassProperties.h>
namespace SimTK {
%template(Inertia) SimTK::Inertia_<double>;
%template(MassProperties) SimTK::MassProperties_<double>;
}

// State & Stage
%include <SWIG/Stage.h>
%include <SWIG/State.h>
