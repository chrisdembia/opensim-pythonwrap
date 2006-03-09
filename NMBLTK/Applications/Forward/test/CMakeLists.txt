INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 		  
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)


LINK_LIBRARIES( debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug suAnalyses_D optimized suAnalyses)

ADD_EXECUTABLE(testForward testForward.cpp)

SET(TEST_FILES forward.xml block_actuators.xml block_contacts.xml block_controls.xml block_states.sto
	std_check.xml std_test_Kinematics_u.sto std_test_Kinematics_dudt.sto std_test_Kinematics_q.sto
	std_test_Actuation_force.sto std_test_Actuation_speed.sto std_test_Actuation_power.sto
	std_test_ActuatorGeneralizedForces.sto std_test_BodyKinematics_vel.sto 
	std_test_BodyKinematics_acc.sto std_test_BodyKinematics_pos.sto
)

#
# Copy files to run dir
#
FOREACH (dataFile ${TEST_FILES})
 ADD_CUSTOM_COMMAND(
    TARGET testForward
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy
    ${NMBLApp_SOURCE_DIR}/NMBLTK/Applications/Forward/test/${dataFile}
    ${NMBLApp_BINARY_DIR}/NMBLTK/Applications/Forward/test)
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

ADD_TEST(testForward ${TEST_PATH}/testForward)

INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ testForward)
