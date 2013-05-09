%module opensim

%feature("autodoc", "3");

%{
#include <OpenSim/version.h>

using namespace OpenSim;
/*using namespace SimTK;*/

%}

%include "std_string.i"
%include <OpenSim/version.h>
