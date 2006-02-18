INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 		  
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)

FILE(GLOB SOURCE_FILES *.cpp)
FILE(GLOB INCLUDE_FILES *.h)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
		debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug rdSQP_D optimized rdSQP)

ADD_EXECUTABLE(solveIK ${SOURCE_FILES} ${INCLUDE_FILES})

INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ solveIK)

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

SUBDIRS(test)
