%module rdBlockModule
%{
#include "rdToolsDLL.h"
#include "rdSimulationDLL.h"
#include "rdArray.h"
#include "rdArrayPtrs.h"
#include "rdProperty.h"
#include "rdPropertySet.h"
#include "rdObject.h"
#include "rdMaterial.h"
#include "rdVisibleProperties.h"
#include "rdTransform.h"
#include "rdVisibleObject.h"

#include "rdSet.h"
#include "rdBody.h"
#include "rdBodySet.h"

#include "rdMaterialSet.h"

#include "rdActuator.h"
#include "rdActuatorSet.h"

#include "rdContactForceSet.h"

#include "rdStateVector.h"
#include "rdStorage.h"

#include "rdModel.h"
#include "rdSDFastDLL.h"
#include "rdSDFast.h"
#include "rdActuatedModel_SDFast.h"
#include "suPipeline40.h"

#include "rdBlock.h"
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
%include "rdToolsDLL.h"
%include "rdSimulationDLL.h"
%include "rdArray.h"
%include "rdArrayPtrs.h"
%include "rdProperty.h"
%include "rdPropertySet.h"
%include "rdObject.h"
%include "rdMaterial.h"
%include "rdVisibleProperties.h"
%include "rdTransform.h"
%include "rdVisibleObject.h"

%include "rdSet.h"

%include "rdBody.h"
%template(rdSetBodies) rdSet<rdBody>;
%include "rdBodySet.h"

%template(rdSetMaterials) rdSet<rdMaterial>;
%include "rdMaterialSet.h"

%include "rdActuator.h"
%template(rdSetActuators) rdSet<rdActuator>;
%include "rdActuatorSet.h"

%include "rdContactForceSet.h"

%include "rdStateVector.h"
%include "rdStorage.h"
%include "rdModel.h"

%template(rdArrayBool) rdArray<bool>;
%template(rdArrayDouble) rdArray<double>;
%template(rdArrayInt) rdArray<int>;
%template(rdArrayStr) rdArray<std::string>;
%template(rdArrayPtrsObj) rdArrayPtrs<rdObject>;

%include "rdSDFastDLL.h"
%include "rdSDFast.h"
%include "rdActuatedModel_SDFast.h"
%include "suPipeline40.h"
%include "rdBlock.h"
