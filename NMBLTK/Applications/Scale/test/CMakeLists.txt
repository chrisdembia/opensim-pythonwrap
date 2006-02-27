INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 		  
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)

FILE(GLOB SOURCE_FILES ../../IK/simm*.cpp  ../simm*.cpp testScale.cpp)
FILE(GLOB INCLUDE_FILES ../../IK/simm*.h ../simm*.h)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
		debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug rdSQP_D optimized rdSQP)

ADD_EXECUTABLE(testScale ${SOURCE_FILES} ${INCLUDE_FILES})

SET(TEST_FILES dynamic.xml markerSet.xml scaleSet.xml CrouchGait.xml init100.trc 
				std_CrouchGaitSP.jnt std_CrouchGaitSP.msl std_CrouchGaitSP.xml std_CrouchGaitScale.xml)

#
# Copy files to run dir
#
FOREACH (dataFile ${TEST_FILES})
 ADD_CUSTOM_COMMAND(
    TARGET testScale
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy
    ${NMBLApp_SOURCE_DIR}/NMBLTK/Applications/Scale/test/${dataFile}
    ${NMBLApp_BINARY_DIR}/NMBLTK/Applications/Scale/test)
 ENDFOREACH (dataFile) 

#
# Testing
#

IF (UNIX)
  ADD_DEFINITIONS(-fprofile-arcs -ftest-coverage)
  LINK_LIBRARIES(gcov)
ENDIF (UNIX)

ENABLE_TESTING()

IF (EXECUTABLE_OUTPUT_PATH)
  SET (TEST_PATH ${EXECUTABLE_OUTPUT_PATH})
ELSE (EXECUTABLE_OUTPUT_PATH)
  SET (TEST_PATH .)
ENDIF (EXECUTABLE_OUTPUT_PATH)

ADD_TEST(testScale ${TEST_PATH}/testScale)

INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ testScale)
