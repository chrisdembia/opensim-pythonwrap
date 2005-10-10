SET(KIT SDFast)
SET(UKIT SDFAST)

SET(SOURCE_FILES rdActuatedModelIntegCallback.cpp
	rdActuatedModel_SDFast.cpp
	rdSDFast.cpp
	rdSDFastDLL.cpp
	sdlib.c
	sdfast_f2c.c)

FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${NMBLApp_SOURCE_DIR}/Tools)

LINK_LIBRARIES( rdTools rdSimulation )
				
ADD_LIBRARY(rd${KIT} ${SOURCE_FILES} ${INCLUDE_FILES}) 

ADD_DEFINITIONS(-DRDSDFAST_EXPORTS,_USRDLL)
