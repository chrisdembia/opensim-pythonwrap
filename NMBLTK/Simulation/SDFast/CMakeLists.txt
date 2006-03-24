SET(KIT SDFast)
SET(UKIT SDFAST)

SET(SOURCE_FILES rdActuatedModelIntegCallback.cpp
	rdActuatedModel_SDFast.cpp
	rdSDFast.cpp
	rdSDFastDLL.cpp
	sdfast_f2c.c)

FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/Vendors 
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${OpenSim_SOURCE_DIR}/Tools)

LINK_LIBRARIES( rdTools rdSimulation )
				
ADD_LIBRARY(rd${KIT} ${SOURCE_FILES} ${INCLUDE_FILES}) 

ADD_DEFINITIONS("-DRDSDFAST_EXPORTS -D_USRDLL")

INSTALL_TARGETS(/lib/ rd${KIT})
INSTALL_FILES(/include/NMBLTK/Simulation/${KIT} .h ${INCLUDE_FILES})
