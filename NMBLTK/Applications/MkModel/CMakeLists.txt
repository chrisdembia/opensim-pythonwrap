INCLUDE_DIRECTORIES(${OpenSim_SOURCE_DIR} 
		    ${OpenSim_SOURCE_DIR}/Vendors 		    
		    ${OpenSim_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)


LINK_LIBRARIES( debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug suAnalyses_D optimized suAnalyses)

ADD_EXECUTABLE(mkModel mkModel.cpp)

INSTALL_TARGETS(${OpenSim_BINARY_DIR}/LibDev/ mkModel)
