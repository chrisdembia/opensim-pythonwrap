SET(KIT ModelDll)
SET(UKIT MODELDLL)


INCLUDE(${CMAKE_ROOT}/Modules/FindJava.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindJNI.cmake)

IF(JAVA_INCLUDE_PATH)

FILE(GLOB SOURCE_FILES ModelJNI_wrap.cxx)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
					${OpenSim_SOURCE_DIR}/Vendors 
					${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
					${JAVA_INCLUDE_PATH}
					${JAVA_INCLUDE_PATH2}
)

SET(EXPORT_MACRO RD${UKIT}_EXPORTS)

LINK_LIBRARIES( rdTools rdSimulation suAnalyses
		debug xerces-c_2D optimized  xerces-c_2)

ADD_LIBRARY(rd${KIT} SHARED ${SOURCE_FILES}) 

SET_TARGET_PROPERTIES(rd${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)

INSTALL_TARGETS(/lib/ RUNTIME_DIRECTORY /lib rd${KIT})


ENDIF (JAVA_INCLUDE_PATH)