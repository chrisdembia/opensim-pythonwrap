FILE(GLOB BIN_FILES opensim/build/launcher/bin/*.*)
FILE(GLOB ETC_FILES opensim/build/launcher/etc/*.*)

INSTALL_FILES(/bin/ FILES  ${BIN_FILES})
INSTALL_FILES(/etc/ FILES  ${ETC_FILES})
# This to be replaced with a CMake Variable
INSTALL(DIRECTORY ${NETBEANS_INSTALL_DIR}/platform6/ DESTINATION platform6)
INSTALL(DIRECTORY opensim/build/cluster/ DESTINATION opensim)

# This to be replaced with a CMake Variable
FILE(GLOB VTK_LIBS ${VTK_LIB_DIR}/release/*.dll)
INSTALL_FILES(/bin/ FILES  ${VTK_LIBS})

