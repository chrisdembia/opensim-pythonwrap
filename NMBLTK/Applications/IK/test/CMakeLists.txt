INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 		  
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)

FILE(GLOB SOURCE_FILES ../simm*.cpp  ../../Scale/simm*.cpp testIK.cpp)
FILE(GLOB INCLUDE_FILES ../simm*.h ../../Scale/simm*.h)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
		debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug rdSQP_D optimized rdSQP)

# SET(EXECUTABLE_OUTPUT_PATH ${NMBLApp_SOURCE_DIR}/NMBLTK/Applications/IK/test)

ADD_EXECUTABLE(testIK ${SOURCE_FILES} ${INCLUDE_FILES})

SET(TEST_FILES dynamic.xml markerSet.xml scaleSet.xml CrouchGait.xml walk1.trc init100.trc walk1_IN.mot std_walk1.mot)

#
# Copy files to run dir
#
FOREACH (dataFile ${TEST_FILES})
 ADD_CUSTOM_COMMAND(
    TARGET testIK
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy
    ${NMBLApp_SOURCE_DIR}/NMBLTK/Applications/IK/test/${dataFile}
    ${EXECUTABLE_OUTPUT_PATH}/Release)
 ENDFOREACH (dataFile) 

ADD_TEST(testIK ${TEST_PATH}/testIK)

INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ testIK)
