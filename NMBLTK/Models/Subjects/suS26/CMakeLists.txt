SET(KIT S26)
SET(UKIT S26)

FILE(GLOB SOURCE_FILES *.cpp *.c )
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${OpenSim_SOURCE_DIR}/NMBLTK/Models/SIMMPipeline/4.0/suPipeline40
		    ${OpenSim_SOURCE_DIR}/NMBLTK/Models/SIMMPipeline/4.0/suPipeline40/dp
		    ${OpenSim_SOURCE_DIR}/NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow
)

LINK_LIBRARIES( rdTools rdSimulation rdSDFast suPipeline40Workflow suPipeline40 suAnalyses acpp)

ADD_EXECUTABLE(su${KIT} ${SOURCE_FILES} ${INCLUDE_FILES}) 

ADD_DEFINITIONS(-DRDSDFAST_EXPORTS)

