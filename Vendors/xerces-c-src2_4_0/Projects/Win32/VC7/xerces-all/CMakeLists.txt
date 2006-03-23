#-----------------------------------------------------------------------------
IF(WIN32)
	ADD_CUSTOM_TARGET(xerces-c_2D ALL devenv ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Projects/Win32/VC7/xerces-all/xerces-all.sln /build Debug)
	ADD_CUSTOM_TARGET(xerces-c_2 ALL devenv ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Projects/Win32/VC7/xerces-all/xerces-all.sln /build Release)
# ADD commands to copy built dlls and libraries to executable paths
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Build/Win32/VC7/Release/xerces-c_2.lib
        ${EXECUTABLE_OUTPUT_PATH}/Release/xerces-c_2.lib)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Build/Win32/VC7/Release/xerces-c_2_4_0.dll
        ${EXECUTABLE_OUTPUT_PATH}/Release/xerces-c_2_4_0.dll)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2D
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Build/Win32/VC7/Debug/xerces-c_2D.lib
        ${EXECUTABLE_OUTPUT_PATH}/Debug/xerces-c_2D.lib)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2D
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Build/Win32/VC7/Debug/xerces-c_2_4_0D.dll
        ${EXECUTABLE_OUTPUT_PATH}/Debug/xerces-c_2_4_0D.dll)
ENDIF(WIN32)

