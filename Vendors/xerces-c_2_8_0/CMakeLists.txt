#-----------------------------------------------------------------------------
INSTALL(DIRECTORY include/xercesc DESTINATION sdk/include PATTERN ".svn" EXCLUDE)

SET(PLATFORM_ROOT  ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/${Platform})

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

# This is where we're going to put these binaries.
SET(COPIED_LIB_FILES)
FOREACH(LIBF ${LIB_FILES})
    GET_FILENAME_COMPONENT(LIBF_ROOT ${LIBF} NAME)
    SET(COPIED_LIB_FILES ${COPIED_LIB_FILES}
	"${BUILD_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${LIBF_ROOT}")
ENDFOREACH()


ADD_CUSTOM_TARGET(XercesFiles ALL DEPENDS ${COPIED_LIB_FILES})
SET_TARGET_PROPERTIES(XercesFiles
    PROPERTIES PROJECT_LABEL "Library - Xerces Files")

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

IF(WIN32)
# Get VCVersion to pick up corret libraries
#	IF(CMAKE_GENERATOR MATCHES  "Visual Studio 8")
#	   SET(VCVERSION VC8)
#	ENDIF(CMAKE_GENERATOR MATCHES  "Visual Studio 8")
#	IF(CMAKE_GENERATOR MATCHES  "Visual Studio 9")
#	  SET(VCVERSION VC9)
#	ENDIF(CMAKE_GENERATOR MATCHES  "Visual Studio 9")

INSTALL_FILES(/sdk/lib/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Windows/${VCVERSION}/xerces-c_2.lib)
INSTALL_FILES(/sdk/lib/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Windows/${VCVERSION}/xerces-c_2D.lib)
INSTALL_FILES(/bin/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Windows/${VCVERSION}/xerces-c_2_8.dll)
INSTALL_FILES(/bin/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Windows/${VCVERSION}/xerces-c_2_8D.dll)
ELSE(WIN32)
INSTALL_FILES(/lib/ FILES ${LIB_FILES})
ENDIF(WIN32)
