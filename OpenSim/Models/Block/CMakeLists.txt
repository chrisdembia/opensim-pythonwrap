SET(KIT Block)
SET(UKIT BLOCK)

FILE(GLOB SOURCE_FILES *.cpp *.c ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/*.cpp ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/*.c)
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} ${XERCES_INCLUDE_DIR} ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline)

ADD_DEFINITIONS(-DOSIMSDFASTENGINE_EXPORTS)

LINK_LIBRARIES(
	debug osimSimulation_d optimized osimSimulation
	debug osimSdfastEngine_d optimized osimSdfastEngine)

ADD_LIBRARY(rd${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

INSTALL_TARGETS(/lib/ RUNTIME_DIRECTORY /lib rd${KIT})
INSTALL_FILES(/include/OpenSim/Models/${KIT} .h ${INCLUDE_FILES})
