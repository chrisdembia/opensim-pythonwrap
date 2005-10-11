SET(KIT Analyses)
SET(UKIT ANALYSES)

FILE(GLOB SOURCE_FILES *.cpp)
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${NMBLApp_SOURCE_DIR}/Tools)

SET(EXPORT_MACRO SU${UKIT}_EXPORTS)

LINK_LIBRARIES( debug rdTools_D optimized rdTools
				debug rdSimulation_D optimized rdSimulation
				debug rdSQP_D optimized rdSQP)

ADD_LIBRARY(su${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

SET_TARGET_PROPERTIES(su${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)
