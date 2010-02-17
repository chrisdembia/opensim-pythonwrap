#-----------------------------------------------------------------------------
INSTALL(DIRECTORY include/xercesc DESTINATION sdk/include PATTERN ".svn" EXCLUDE)
IF(WIN32)
# Get VCVersion to pick up corret libraries
#	IF(CMAKE_GENERATOR MATCHES  "Visual Studio 8")
#	   SET(VCVERSION VC8)
#	ENDIF(CMAKE_GENERATOR MATCHES  "Visual Studio 8")
#	IF(CMAKE_GENERATOR MATCHES  "Visual Studio 9")
#	  SET(VCVERSION VC9)
#	ENDIF(CMAKE_GENERATOR MATCHES  "Visual Studio 9")

INSTALL_FILES(/sdk/lib/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Win32/${VCVERSION}/xerces-c_2.lib)
INSTALL_FILES(/sdk/lib/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Win32/${VCVERSION}/xerces-c_2D.lib)
INSTALL_FILES(/bin/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Win32/${VCVERSION}/xerces-c_2_8.dll)
INSTALL_FILES(/bin/ FILES ${OpenSim_SOURCE_DIR}/Vendors/${XERCES_DIR_NAME}/lib/Win32/${VCVERSION}/xerces-c_2_8D.dll)
ENDIF(WIN32)
