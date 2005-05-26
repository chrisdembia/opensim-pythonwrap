%module Model
%{
#include <RD/Tools/rdToolsDLL.h>
#include <RD/Simulation/rdSimulationDLL.h>
#include <RD/Tools/rdException.h>
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
#include <RD/Simulation/Control/rdControl.h>
#include <RD/Simulation/Control/rdControlSet.h>
#include <RD/Simulation/Control/rdControlConstant.h>
#include <RD/Simulation/Control/rdControlLinear.h>
#include <RD/Simulation/Integrator/rdRKF.h>
#include <RD/Simulation/Integrator/rdIntegRKF.h>
#include <RD/Simulation/Manager/rdManager.h>
#include <RD/Simulation/Model/rdCallback.h>
#include <RD/Simulation/Model/rdCallbackSet.h>
#include <RD/Simulation/Model/rdIntegCallback.h>
#include <RD/Simulation/Simtk/rdSimtkAnimationCallback.h>
#include <RD/Simulation/Model/rdAnalysis.h>
#include <RD/Simulation/Model/rdAnalysisFactory.h>

#include <RD/Simulation/Model/suMarker.h>
#include <RD/Simulation/Model/suMarkerSet.h>
#include <RD/Tools/suRange.h>
#include <RD/Tools/suScale.h>
#include <RD/Tools/suScaleSet.h>

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
/* make getCPtr public not package private */
%typemap(javagetcptr) SWIGTYPE, SWIGTYPE *, SWIGTYPE &, SWIGTYPE [], SWIGTYPE (CLASS::*)  %{
  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}
/* make constructor(log, <type>) public as well */
%typemap(javaptrconstructormodifiers) SWIGTYPE, SWIGTYPE *, SWIGTYPE &, SWIGTYPE [], SWIGTYPE (CLASS::*)  %{
  public %}

%include "exception.i"
// Exception handler (intended for JNI calls that have a non void return)
%exception {
  try {
    $function
  }
  catch (rdException) {
    jclass clazz = jenv->FindClass("simtkModel/rdException");
    jenv->ThrowNew(clazz, "Native Exception");
    return NULL;
  }
}

// This overrides anything in the %except(java) typemap
// Used for JNI calls that return void
%typemap(except) void {
  try {
    $function
  }
  catch (rdException) {
    jclass clazz = jenv->FindClass("simtkModel/rdException");
    jenv->ThrowNew(clazz, "Native Exception");
    return;
  }
}


/* rest of header files to be wrapped */
%include <RD/Tools/rdToolsDLL.h>
%include <RD/Simulation/rdSimulationDLL.h>
%include <RD/Tools/rdException.h>
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

%include <RD/Simulation/Control/rdControl.h>
%template(rdSetControls) rdSet<rdControl>;
%include <RD/Simulation/Control/rdControlSet.h>
%include <RD/Simulation/Control/rdControlConstant.h>
%include <RD/Simulation/Control/rdControlLinear.h>

%include <RD/Simulation/Integrator/rdRKF.h>
%include <RD/Simulation/Integrator/rdIntegRKF.h>
%include <RD/Simulation/Manager/rdManager.h>
%include <RD/Simulation/Model/rdCallback.h>
%template(rdSetCallback) rdSet<rdCallback>;
%include <RD/Simulation/Model/rdCallbackSet.h>
%include <RD/Simulation/Model/rdIntegCallback.h>
%include <RD/Simulation/Simtk/rdSimtkAnimationCallback.h>

%include <RD/Simulation/Model/rdAnalysis.h>
%template(rdArrayAnalysis) rdArrayPtrs<rdAnalysis>;
%include <RD/Simulation/Model/rdAnalysisFactory.h>
%template(rdArrayBool) rdArray<bool>;
%template(rdArrayDouble) rdArray<double>;
%template(rdArrayInt) rdArray<int>;
%template(rdArrayStr) rdArray<std::string>;
%template(rdArrayPtrsObj) rdArrayPtrs<rdObject>;
%include <RD/Simulation/Model/suMarker.h>
%template(suSetMarkers) rdSet<suMarker>;
%include <RD/Simulation/Model/suMarkerSet.h>
%include <RD/Tools/suRange.h>
%include <RD/Tools/suScale.h>
%template(suSetScales) rdSet<suScale>;
%include <RD/Tools/suScaleSet.h>
