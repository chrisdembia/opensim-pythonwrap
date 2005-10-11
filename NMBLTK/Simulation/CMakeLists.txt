SUBDIRS(SDFast)

SET(KIT Simulation)
SET(UKIT SIMULATION)

FILE(GLOB SOURCE_FILES Control/*.cpp Integrator/*.cpp Manager/*.cpp Model/*.cpp Simtk/*.cpp *.cpp)
FILE(GLOB INCLUDE_FILES Control/*.h Integrator/*.h Manager/*.h Model/*.h Simtk/*.h *.h)

INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${NMBLApp_SOURCE_DIR}/Tools)

SET(EXPORT_MACRO RD${UKIT}_EXPORTS)

LINK_LIBRARIES(debug rdTools_D optimized rdTools
		debug xerces-c_2D optimized xerces-c_2)

ADD_LIBRARY(rd${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

SET_TARGET_PROPERTIES(rd${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)
