#-----------------------------------------------------------------------------
IF(OPENSIM_MINIMAL_BUILD)
SUBDIRS(gait23)
ELSE(OPENSIM_MINIMAL_BUILD)
SUBDIRS(Block rdModelDll gait23)
ENDIF(OPENSIM_MINIMAL_BUILD)
