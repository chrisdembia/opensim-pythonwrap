// Copied directly from Java's .i file.
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

// State & Stage
%include <SWIG/Stage.h>
%include <SWIG/State.h>
