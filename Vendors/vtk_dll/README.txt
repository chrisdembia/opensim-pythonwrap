These vtk dll's were generated from a patched version of vtk as follows:

- Download vtk-5.0.2 source
- Modify Common/vtkJavaUtil.cxx as follows:

	REPLACE
		vtkPointerLookup->AddHashEntry(ptr,(void *)env->NewWeakGlobalRef(obj));
	WITH
		vtkPointerLookup->AddHashEntry(ptr,(void *)env->NewGlobalRef(obj));

	AND REPLACE
		env->DeleteWeakGlobalRef((jweak)vptr);
	WITH
	  env->DeleteGlobalRef((jobject)vptr);

Basically weak global refs seem like the wrong thing to use (or are being used incorrectly), because we run into cases where the C++ object is deleted before the java side object is deleted.

- Compile
- The resulting vtk.jar file (java wrapped file) was also copied to Applications/Gui/opensim/vtk50/release/modules/ext/vtk50.jar
