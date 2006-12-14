SET(KIT S26Gui)
SET(UKIT S26Gui)


INCLUDE(${CMAKE_ROOT}/Modules/FindJava.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindJNI.cmake)

IF(JAVA_INCLUDE_PATH)

FILE(GLOB SOURCE_FILES *.cpp *.c *.cxx)
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${XERCES_INCLUDE_DIR}
		    ${OpenSim_SOURCE_DIR}/OpenSim/Models/SIMMPipeline/4.0/suPipeline40
		    ${OpenSim_SOURCE_DIR}/OpenSim/Models/SIMMPipeline/4.0/suPipeline40/dp
		    ${OpenSim_SOURCE_DIR}/OpenSim/Models/SIMMPipeline/4.0/Pipeline40Workflow
		    ${OpenSim_SOURCE_DIR}/OpenSim/Tools
		    ${JAVA_INCLUDE_PATH}
		    ${JAVA_INCLUDE_PATH2}
)

SET(EXPORT_MACRO "RDSDFAST_EXPORTS")

LINK_LIBRARIES( rdTools rdSimulation rdSDFast suPipeline40Workflow suPipeline40 suAnalyses acpp)

ADD_LIBRARY(su${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

SET_TARGET_PROPERTIES(su${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)

INSTALL_TARGETS(/lib/ RUNTIME_DIRECTORY /lib su${KIT})

ENDIF (JAVA_INCLUDE_PATH)