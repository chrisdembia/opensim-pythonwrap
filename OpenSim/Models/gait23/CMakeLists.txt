SET(KIT gait23)
SET(UKIT GAIT23)

FILE(GLOB SOURCE_FILES *.cpp *.c ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/*.cpp ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/*.c)
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} ${XERCES_INCLUDE_DIR} ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline)

LINK_LIBRARIES(
	debug osimSimulation_d optimized osimSimulation
	debug osimSdfastEngine_d optimized osimSdfastEngine)

ADD_LIBRARY(${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

SET_TARGET_PROPERTIES(${KIT} PROPERTIES PROJECT_LABEL "Models - gait23")

IF(WIN32)
SET_TARGET_PROPERTIES(${KIT} PROPERTIES
	LINK_FLAGS "/DEF:${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/SdfastModelDLL.def"
)
ENDIF(WIN32)

INSTALL_TARGETS(/lib/ RUNTIME_DIRECTORY /bin ${KIT})
INSTALL_FILES(/models/ FILES gait23.jnt gait54.msl gait92.msl gait2354.osim gait2392.osim)
