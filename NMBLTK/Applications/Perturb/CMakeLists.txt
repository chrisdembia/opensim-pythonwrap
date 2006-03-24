INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/Vendors 		    
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)


LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
		debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug rdActuators_D optimized rdActuators
		debug suAnalyses_D optimized suAnalyses)
ADD_EXECUTABLE(perturb perturb.cpp)

INSTALL_TARGETS(/bin/ perturb)
