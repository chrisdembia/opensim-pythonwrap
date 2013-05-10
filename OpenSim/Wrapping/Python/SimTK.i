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
%include <SWIG/BigMatrix.h>
namespace SimTK {
%template(MatrixBaseDouble) SimTK::MatrixBase<double>;
%template(VectorBaseDouble) SimTK::VectorBase<double>;
%template(Vector) SimTK::Vector_<double>;
%template(Matrix) SimTK::Matrix_<double>;
}

%pythoncode %{
def newVector(arraylike):
    v = Vector()
    n = len(arraylike)
    v.resize(n)
    for i in range(n):
        v.set(i, arraylike[i])
    return v
%}
%typemap(in) const SimTK::Vector& {
    $1 = NULL;
    if (PyTuple_Check($input)) {
        int size = PyTuple_Size($input);

        // TODO [chrisdembia] this really shouldn't be a pointer.
        SimTK::Vector * v = new SimTK::Vector();
        v->resize(size);
        for (int i = 0; i < size; i++) {
            PyObject *o = PyTuple_GetItem($input, i);
            if (PyFloat_Check(o))
                v->set(i, PyFloat_AsDouble(PyTuple_GetItem($input, i)));
            else {
                // TODO improve error message.
                PyErr_SetString(PyExc_TypeError, "tuple must contain floats");
                return NULL;
            }
        }
        $1 = v;
    } else {
        // TODO improve error message.
        PyErr_SetString(PyExc_TypeError,"not a tuple");
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
