#-----------------------------------------------------------------------------
IF(OPENSIM_MINIMAL_BUILD)
SUBDIRS(SdfastEngine)
ELSE(OPENSIM_MINIMAL_BUILD)
SUBDIRS(Block SdfastEngine rdModelDll)
ENDIF(OPENSIM_MINIMAL_BUILD)
