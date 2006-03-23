SET(KIT Pipeline40)

FILE(GLOB SOURCE_FILES *.cpp *.c)
FILE(GLOB INCLUDE_FILES *.h )

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/Vendors 		    		    
		    ${OpenSim_SOURCE_DIR}/NMBLTK/Models/SIMMPipeline/4.0/suPipeline40/dp
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${OpenSim_SOURCE_DIR}/Tools)


ADD_LIBRARY(su${KIT} ${SOURCE_FILES} ${INCLUDE_FILES}) 

ADD_DEFINITIONS("-DRDSDFAST_EXPORTS -D_POSIX_")

LINK_LIBRARIES( rdSDFast rdSimulation rdTools)

INSTALL_TARGETS(${OpenSim_BINARY_DIR}/LibDev/ su${KIT})
				
