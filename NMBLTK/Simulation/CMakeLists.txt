SUBDIRS(SDFast)

SET(KIT Simulation)
SET(UKIT SIMULATION)

## Name headers under individual directories so that INSTALL doesn't barf on them

FILE(GLOB LOCAL_HEADERS *.h)

FILE(GLOB ControlHeaders Control/*.h)
FILE(GLOB IntegratorHeaders Integrator/*.h)
FILE(GLOB ManagerHeaders Manager/*.h)
FILE(GLOB ModelHeaders Model/*.h)
FILE(GLOB SimtkHeaders Simtk/*.h)
FILE(GLOB SIMMHeaders SIMM/*.h)

FILE(GLOB SOURCE_FILES Control/*.cpp Integrator/*.cpp Manager/*.cpp Model/*.cpp Simtk/*.cpp SIMM/*.cpp *.cpp)
FILE(GLOB INCLUDE_FILES Control/*.h Integrator/*.h Manager/*.h Model/*.h Simtk/*.h SIMM/*.h *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/Vendors 
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src
		    ${OpenSim_SOURCE_DIR}/Tools)

SET(EXPORT_MACRO RD${UKIT}_EXPORTS)

LINK_LIBRARIES(debug rdTools_D optimized rdTools
		debug xerces-c_2D optimized xerces-c_2)

ADD_LIBRARY(rd${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

SET_TARGET_PROPERTIES(rd${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)

INSTALL_TARGETS(/lib/ rd${KIT})

INSTALL_FILES(/include/NMBLTK/Simulation .h ${LOCAL_HEADERS})
INSTALL_FILES(/include/NMBLTK/Simulation/Control .h ${ControlHeaders})
INSTALL_FILES(/include/NMBLTK/Simulation/Integrator .h ${IntegratorHeaders})
INSTALL_FILES(/include/NMBLTK/Simulation/Manager .h ${ManagerHeaders})
INSTALL_FILES(/include/NMBLTK/Simulation/Model .h ${ModelHeaders})
INSTALL_FILES(/include/NMBLTK/Simulation/Simtk .h ${SimtkHeaders})
INSTALL_FILES(/include/NMBLTK/Simulation/SIMM .h ${SIMMHeaders})
