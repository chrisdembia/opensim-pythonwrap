#-----------------------------------------------------------------------------
IF(WIN32)
	ADD_CUSTOM_TARGET(xerces-c_2D_cmake ALL devenv ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Projects/Win32/VC7.1/xerces-all/xerces-all.sln /build Debug)
	ADD_CUSTOM_TARGET(xerces-c_2_cmake ALL devenv ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Projects/Win32/VC7.1/xerces-all/xerces-all.sln /build Release)
# ADD commands to copy built dlls and libraries to executable paths
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Release/xerces-c_2.lib
        ${EXECUTABLE_OUTPUT_PATH}/Release/xerces-c_2.lib)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Release/xerces-c_2_7.dll
        ${EXECUTABLE_OUTPUT_PATH}/Release/xerces-c_2_7.dll)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2D_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Debug/xerces-c_2D.lib
        ${EXECUTABLE_OUTPUT_PATH}/Debug/xerces-c_2D.lib)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2D_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Debug/xerces-c_2_7D.dll
        ${EXECUTABLE_OUTPUT_PATH}/Debug/xerces-c_2_7D.dll)
    ## Essentially installation stuff
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Release/xerces-c_2.lib
        ${CMAKE_INSTALL_PREFIX}/lib/xerces-c_2.lib)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Release/xerces-c_2_7.dll
        ${CMAKE_INSTALL_PREFIX}/lib/xerces-c_2_7.dll)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2D_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Debug/xerces-c_2D.lib
        ${CMAKE_INSTALL_PREFIX}/lib/xerces-c_2D.lib)
	ADD_CUSTOM_COMMAND(
        TARGET xerces-c_2D_cmake
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy
        ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src_2_7_0/Build/Win32/VC7.1/Debug/xerces-c_2_7D.dll
        ${CMAKE_INSTALL_PREFIX}/lib/xerces-c_2_7D.dll)
ENDIF(WIN32)



#---- There must be a better way than repeating this for every directory
# ---- but GLOB_RECURSE flattened the list which is bad and mailing list up to 
#----- http://public.kitware.com/pipermail/cmake/2005-March/006234.html
#
# These are all the places to search for header files which are
# to be part of the API.
SET(XERCES_INCLUDE_DIRS 
src/xercesc/dom
src/xercesc/util
src/xercesc/internal
src/xercesc/sax
src/xercesc/sax2
src/xercesc/parsers
src/xercesc/dom/impl
src/xercesc/util/Platforms/Win32
src/xercesc/util/Platforms/Linux
src/xercesc/util/Platforms/MacOS
src/xercesc/util/Compilers
src/xercesc/framework
src/xercesc/validators/datatype
src/xercesc/util/regx
src/xercesc/framework/psvi
src/xercesc/validators/schema
src/xercesc/validators/DTD
)

FOREACH(dir ${XERCES_INCLUDE_DIRS})
    FILE(GLOB HEADERS ../../../../${dir}/*.hpp)	# returns full pathnames
	INSTALL_FILES(/include/Vendors/xerces-c-src_2_7_0/${dir} .hpp ${HEADERS})
ENDFOREACH(dir)

FILE(GLOB UTIL_C_FILES ../../../../src/xercesc/util/*.c)
INSTALL_FILES(/include/Vendors/xerces-c-src_2_7_0/src/xercesc/util .c ${UTIL_C_FILES})

