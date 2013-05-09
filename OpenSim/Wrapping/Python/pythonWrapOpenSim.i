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

using namespace OpenSim;
using namespace SimTK;

%}

%rename(OpenSimObject) OpenSim::Object;
%rename(OpenSimException) OpenSim::Exception;

%include "exception.i"
%include "pointer.i"
%include "std_string.i"
%include "typemaps.i"


%include <OpenSim/version.h>
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

/*
1. Array.getitem() instead of get(), is this the expected use case?
2. Property::operator[]
3. Property::operator=
*/
