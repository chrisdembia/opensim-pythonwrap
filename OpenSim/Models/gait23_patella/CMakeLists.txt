SET(KIT gait23_patella)
SET(UKIT GAIT23_PATELLA)

FILE(GLOB SOURCE_FILES *.cpp *.c ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/*.cpp ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/*.c)
FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} ${XERCES_INCLUDE_DIR} ${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline)

LINK_LIBRARIES(
	debug osimSimulation_d optimized osimSimulation
	debug osimSdfastEngine_d optimized osimSdfastEngine)

ADD_LIBRARY(${KIT} SHARED ${SOURCE_FILES} ${INCLUDE_FILES}) 

SET_TARGET_PROPERTIES(${KIT} PROPERTIES PROJECT_LABEL "Models - gait23_patella")

IF(WIN32)
SET_TARGET_PROPERTIES(${KIT} PROPERTIES
	LINK_FLAGS "/DEF:${OpenSim_SOURCE_DIR}/OpenSim/DynamicsEngines/SdfastEngine/SIMMPipeline/SdfastModelDLL.def"
)
ENDIF(WIN32)

#INSTALL_TARGETS(/lib/ RUNTIME_DIRECTORY /bin ${KIT})
INSTALL_FILES(/models/ FILES gait23_patella_simm.jnt gait54_patella_simm.msl gait92_patella_simm.msl gait2354_patella_simm.osim gait2392_patella_simm.osim)
