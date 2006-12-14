SET(KIT S26)
SET(UKIT S26)

FILE(GLOB SOURCE_FILES *.cpp *.c )
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${XERCES_INCLUDE_DIR}
		    ${OpenSim_SOURCE_DIR}/OpenSim/Models/SIMMPipeline/4.0/suPipeline40
		    ${OpenSim_SOURCE_DIR}/OpenSim/Models/SIMMPipeline/4.0/suPipeline40/dp
		    ${OpenSim_SOURCE_DIR}/OpenSim/Models/SIMMPipeline/4.0/Pipeline40Workflow
)

IF(WIN32)
LINK_LIBRARIES( rdTools rdSimulation rdSDFast suPipeline40 suPipeline40Workflow suAnalyses acpp)
ELSE(WIN32) # no acpp library for linux
LINK_LIBRARIES( rdTools rdSimulation rdSDFast suPipeline40 suPipeline40Workflow suAnalyses)
ENDIF(WIN32)

ADD_EXECUTABLE(su${KIT} ${SOURCE_FILES} ${INCLUDE_FILES}) 

ADD_DEFINITIONS(-DRDSDFAST_EXPORTS)

INSTALL_TARGETS(/bin/ su${KIT})
INSTALL_FILES(/include/OpenSim/Models/Subjects/su${KIT} .h ${INCLUDE_FILES})
