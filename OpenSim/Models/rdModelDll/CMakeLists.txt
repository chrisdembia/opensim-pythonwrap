SET(KIT ModelDll)
SET(UKIT MODELDLL)


INCLUDE(${CMAKE_ROOT}/Modules/FindJava.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindJNI.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindSWIG.cmake)

IF(JAVA_INCLUDE_PATH)

# Run command to generate ModelJNI_wrap.cxx
SET(swig_generated_file_fullname ${OpenSim_SOURCE_DIR}/OpenSim/Models/rdModelDll/ModelJNI_wrap.cxx)
SET(swig_interface_file_fullname ${OpenSim_SOURCE_DIR}/OpenSim/Resources/Swig/genericTemplate.i)

ADD_CUSTOM_TARGET(JavaWrap ${SWIG_EXECUTABLE} -v -c++ -java -package org.opensim.modeling -I${OpenSim_SOURCE_DIR} -I${OpenSim_SOURCE_DIR}/OpenSim/Resources/Swig/ -o ${swig_generated_file_fullname} -outdir ${OpenSim_SOURCE_DIR}/OpenSim/Applications/Gui/opensim/modeling/src/org/opensim/modeling ${swig_interface_file_fullname})

FILE(GLOB SOURCE_FILES ${swig_generated_file_fullname})

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
					${OpenSim_SOURCE_DIR}/Vendors 
					${XERCES_INCLUDE_DIR}
					${JAVA_INCLUDE_PATH}
					${JAVA_INCLUDE_PATH2}
)

SET(EXPORT_MACRO RD${UKIT}_EXPORTS)

LINK_LIBRARIES( rdTools rdSimulation suAnalyses workflow rdCMC
		debug xerces-c_2D optimized  xerces-c_2)

ADD_LIBRARY(rd${KIT} SHARED ${SOURCE_FILES}) 

SET_TARGET_PROPERTIES(rd${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)

ADD_DEPENDENCIES(rd${KIT} JavaWrap)

INSTALL_TARGETS(/lib/ RUNTIME_DIRECTORY /lib rd${KIT})


ENDIF (JAVA_INCLUDE_PATH)