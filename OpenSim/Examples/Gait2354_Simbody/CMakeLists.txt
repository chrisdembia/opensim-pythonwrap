SET(GAIT2354_FILES subject01_static.trc subject01_walk1.trc subject01_walk1.mot subject01_walk1_grf.mot gait2354_simbody.osim)
FILE(GLOB GAIT2354_SETUP_FILES *.xml)
FILE(GLOB BONE_FILES Geometry/*.vtp)

INSTALL_FILES(/examples/Gait2354_Simbody/ FILES ${GAIT2354_FILES})
INSTALL_FILES(/examples/Gait2354_Simbody/ FILES ${GAIT2354_SETUP_FILES})
INSTALL_FILES(/Geometry FILES ${BONE_FILES})
