#-----------------------------------------------------------------------------
#SUBDIRS(Block gait23 gait23_patella)

FILE(GLOB BONE_FILES Geometry/*.vtp)
FILE(GLOB OBJ_FILES Geometry/*.obj)
FILE(GLOB IMG_FILES Geometry/*.png)
INSTALL_FILES(/Geometry/ FILES  ${BONE_FILES})
INSTALL_FILES(/Geometry/ FILES  ${OBJ_FILES})
INSTALL_FILES(/Geometry/ FILES  ${IMG_FILES})
