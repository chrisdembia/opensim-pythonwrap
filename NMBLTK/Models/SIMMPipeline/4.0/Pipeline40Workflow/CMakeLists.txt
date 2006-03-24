SET(KIT Pipeline40Workflow)

FILE(GLOB SOURCE_FILES *.cpp *.c)
FILE(GLOB INCLUDE_FILES *.h )

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/NMBLTK/Models/SIMMPipeline/4.0/suPipeline40
		    ${OpenSim_SOURCE_DIR}/NMBLTK/Models/SIMMPipeline/4.0/suPipeline40/dp
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${OpenSim_SOURCE_DIR}/Tools)


ADD_DEFINITIONS("-DRDSDFAST_EXPORTS")

ADD_LIBRARY(su${KIT} ${SOURCE_FILES} ${INCLUDE_FILES}) 

INSTALL_TARGETS(/lib/ su${KIT})
INSTALL_FILES(/include/NMBLTK/Models/SIMMPipeline/4.0/Pipeline40Workflow .h ${INCLUDE_FILES})
