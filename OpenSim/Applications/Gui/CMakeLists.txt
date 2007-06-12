FILE(GLOB BIN_FILES opensim/build/launcher/bin/*.*)
FILE(GLOB ETC_FILES opensim/build/launcher/etc/*.*)

INSTALL_FILES(/bin/ FILES  ${BIN_FILES})
INSTALL_FILES(/etc/ FILES  ${ETC_FILES})
# This to be replaced with a CMake Variable
# Check if directory exists first to more gracefully handle case where it doesn't exist (otherwise cmake prints an error message)
IF(EXISTS ${NETBEANS_INSTALL_DIR}/platform6/)
INSTALL(DIRECTORY ${NETBEANS_INSTALL_DIR}/platform6/ DESTINATION platform6)
ENDIF(EXISTS ${NETBEANS_INSTALL_DIR}/platform6/)
IF(EXISTS opensim/build/cluster/)
INSTALL(DIRECTORY opensim/build/cluster/ DESTINATION opensim)
ENDIF(EXISTS opensim/build/cluster/)

# This to be replaced with a CMake Variable
FILE(GLOB VTK_LIBS ${VTK_LIB_DIR}/release/*.dll)
INSTALL_FILES(/bin/ FILES  ${VTK_LIBS})

