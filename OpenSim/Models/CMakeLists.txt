#-----------------------------------------------------------------------------
SUBDIRS(Block gait23 gait23_patella)

FILE(GLOB BONE_FILES Geometry/*.vtp)
INSTALL_FILES(/Geometry/ FILES  ${BONE_FILES})
