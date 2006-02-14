SUBDIRS(Scale IK)

INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
		    ${NMBLApp_SOURCE_DIR}/Vendors 		    
		    ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)


LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
		debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug rdActuators_D optimized rdActuators
		debug suAnalyses_D optimized suAnalyses)
