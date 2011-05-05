#---------------------------------------------------
# Prerequisites
#
# Simbody has dependencies on several low-level packages
# for which the details differ on different platforms.
# Dependencies are:
#    - pthreads
#    - Lapack
# Pthreads is standard on Linux platforms, and close enough
# on Macs. On Windows we have to supply our own.
# We provide our own high-performance Lapack libraries
# on all platforms, but you can provide your own if you
# prefer by giving the library names. However, the 
# signatures must match our include file SimTKlapack.h.
#
#----------------------------------------------------

IF (USE_LIBRARIES_FROM_REPOSITORY)

SET(PLATFORM_ROOT  ${OpenSim_SOURCE_DIR}/Vendors/SimTK/${Platform})

IF(WIN32)
SET(LIB_ABI_DIR "${PLATFORM_ROOT}/${VCVERSION}")
ELSE(WIN32)
SET(LIB_ABI_DIR "${PLATFORM_ROOT}")
ENDIF(WIN32)

FILE(GLOB LIB_FILES 
	"${LIB_ABI_DIR}/*.a"
	"${LIB_ABI_DIR}/*.so"
	"${LIB_ABI_DIR}/*.so.*"
	"${LIB_ABI_DIR}/*.dylib"
	"${LIB_ABI_DIR}/*.lib"
	"${LIB_ABI_DIR}/*.dll")
ELSE(USE_LIBRARIES_FROM_REPOSITORY)
	FILE(GLOB LIB_FILES2 "${SIMTK_BIN_DIR}/*.a"
						 "${SIMTK_BIN_DIR}/*.so"
						 "${SIMTK_BIN_DIR}/*.so.*"
					     "${SIMTK_BIN_DIR}/*.dylib"
						 "${SIMTK_BIN_DIR}/*.dll")
	SET(LIB_FILES ${THIRDPARTY_DYNLIB_FILES} ${LIB_FILES2})
	# MESSAGE("SIMTK_LIB_DIR" ${SIMTK_LIB_DIR})
	# MESSAGE("SIMTK_BIN_DIR" ${SIMTK_BIN_DIR})
	# MESSAGE("LIB_FILES: " ${LIB_FILES})
ENDIF(USE_LIBRARIES_FROM_REPOSITORY)
# This is where we're going to put these binaries.
SET(COPIED_LIB_FILES)
FOREACH(LIBF ${LIB_FILES})
    GET_FILENAME_COMPONENT(LIBF_ROOT ${LIBF} NAME)
    SET(COPIED_LIB_FILES ${COPIED_LIB_FILES}
	"${BUILD_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${LIBF_ROOT}")
ENDFOREACH()


ADD_CUSTOM_TARGET(PlatformFiles ALL DEPENDS ${COPIED_LIB_FILES})
SET_TARGET_PROPERTIES(PlatformFiles
    PROPERTIES PROJECT_LABEL "Library - Platform Files")

#
# During build, we want to copy all the platform binaries
# into the same binary directory that we are using for all
# the ones we build. That ensure that our build will always
# use the current versions of these.
#
# At installation, we copy both includes and binaries into
# the appropriate locations of the SimTK_INSTALL_DIR.
#

FOREACH(LIBF ${LIB_FILES})
##    MESSAGE("LIB_FILE" ${LIBF})
    GET_FILENAME_COMPONENT(LIBF_ROOT ${LIBF} NAME)
    GET_FILENAME_COMPONENT(LIBF_SUFFIX ${LIBF} EXT)
    SET(COPIED_LIBF "${BUILD_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${LIBF_ROOT}")
    FILE(TO_NATIVE_PATH "${LIBF}" LIBF_SRC)
    FILE(TO_NATIVE_PATH "${COPIED_LIBF}" LIBF_DEST)

    ADD_CUSTOM_COMMAND(OUTPUT "${COPIED_LIBF}"
	    COMMAND ${NATIVE_COPY_CMD} "${LIBF_SRC}" "${LIBF_DEST}"
	    DEPENDS "${LIBF}"
	    COMMENT "Copy ${LIBF_SRC} -> ${LIBF_DEST}"
	    VERBATIM)

ENDFOREACH()

