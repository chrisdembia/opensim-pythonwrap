#-----------------------------------------------------------------------------
IF(WIN32)
ADD_CUSTOM_TARGET(xerces-c_2D ALL devenv ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/Projects/Win32/VC7/xerces-all/xerces-all.sln /build Debug)
ENDIF(WIN32)
