#-----------------------------------------------------------------------------
IF(OPENSIM_MINIMAL_BUILD)
SUBDIRS(SdfastEngine gait23)
ELSE(OPENSIM_MINIMAL_BUILD)
SUBDIRS(Block SdfastEngine rdModelDll gait23)
ENDIF(OPENSIM_MINIMAL_BUILD)
