%module _MODEL_NAME_HERE_Module
%{
#include <RD/Tools/rdToolsDLL.h>
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdArray.h>
#include <RD/Tools/rdArrayPtrs.h>
#include <RD/Tools/rdProperty.h>
#include <RD/Tools/rdPropertySet.h>
#include <RD/Tools/rdObject.h>
#include <RD/Tools/rdMaterial.h>
#include <RD/Tools/rdVisibleProperties.h>
#include <RD/Tools/rdTransform.h>
#include <RD/Tools/rdVisibleObject.h>

#include <RD/Tools/rdSet.h>
#include <RD/Simulation/Model/rdBody.h>
#include <RD/Simulation/Model/rdBodySet.h>

#include <RD/Tools/rdMaterialSet.h>

#include <RD/Simulation/Model/rdActuator.h>
#include <RD/Simulation/Model/rdActuatorSet.h>

#include <RD/Simulation/Model/rdContactForceSet.h>

#include <RD/Tools/rdStateVector.h>
#include <RD/Tools/rdStorage.h>

#include <RD/Simulation/Model/rdModel.h>
#include <RD/Simulation/SDFast/rdSDFastDLL.h>
#include <RD/Simulation/SDFast/rdSDFast.h>
#include <RD/Simulation/SDFast/rdActuatedModel_SDFast.h>
#include <SU/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>
#include <SU/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
#include "_MODEL_NAME_HERE_.h"
%}

/* This file is for creation/handling of arrays */
%include "sarrays.i"

/* This interface file is for better handling of pointers and references */
%include "typemaps.i"
%include "std_string.i"

/* inline code for rdObject.java */
%typemap(javacode) rdObject %{
  public boolean equals(Object aObject) {
    if (! (aObject instanceof rdObject))
      return false;
    rdObject rObj = (rdObject) aObject;
    return (this.getName().equals(rObj.getName()) &&
            this.getType().equals(rObj.getType()));
  }
  public int hashCode() {
    return( this.getName().hashCode()+10000 * getType().hashCode());
  }
%}
/* rest of header files to be wrapped */
%include <RD/Tools/rdToolsDLL.h>
%include <RD/Simulation/rdSimulationDLL.h>
%include <RD/Tools/rdArray.h>
%include <RD/Tools/rdArrayPtrs.h>
%include <RD/Tools/rdProperty.h>
%include <RD/Tools/rdPropertySet.h>
%include <RD/Tools/rdObject.h>
%include <RD/Tools/rdMaterial.h>
%include <RD/Tools/rdVisibleProperties.h>
%include <RD/Tools/rdTransform.h>
%include <RD/Tools/rdVisibleObject.h>

%include <RD/Tools/rdSet.h>

%include <RD/Simulation/Model/rdBody.h>
%template(rdSetBodies) rdSet<rdBody>;
%include <RD/Simulation/Model/rdBodySet.h>

%template(rdSetMaterials) rdSet<rdMaterial>;
%include <RD/Tools/rdMaterialSet.h>

%include <RD/Simulation/Model/rdActuator.h>
%template(rdSetActuators) rdSet<rdActuator>;
%include <RD/Simulation/Model/rdActuatorSet.h>

%include <RD/Simulation/Model/rdContactForceSet.h>

%include <RD/Tools/rdStateVector.h>
%include <RD/Tools/rdStorage.h>
%include <RD/Simulation/Model/rdModel.h>

%template(rdArrayBool) rdArray<bool>;
%template(rdArrayDouble) rdArray<double>;
%template(rdArrayInt) rdArray<int>;
%template(rdArrayStr) rdArray<std::string>;
%template(rdArrayPtrsObj) rdArrayPtrs<rdObject>;

%include <RD/Simulation/SDFast/rdSDFastDLL.h>
%include <RD/Simulation/SDFast/rdSDFast.h>
%include <RD/Simulation/SDFast/rdActuatedModel_SDFast.h>
%include <SU/Models/SIMMPipeline/4.0/suPipeline40/suPipeline40.h>
%include <SU/Models/SIMMPipeline/4.0/Pipeline40Workflow/suPipeline40Workflow.h>
%include "_MODEL_NAME_HERE_.h"
