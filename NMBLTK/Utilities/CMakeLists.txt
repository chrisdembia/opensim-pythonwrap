INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} ${NMBLApp_SOURCE_DIR}/Vendors ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)


LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(rdConvertControls rdConvertControls.cpp)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(rdConvertStorageToControls rdConvertStorageToControls.cpp)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(rdSimplifyControls rdSimplifyControls.cpp)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(suPerturbStorage perturbStorage.cpp)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(suStorageAdd storageAdd.cpp)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(suStorageIntegrate storageIntegrate.cpp)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools rdSimulation)
ADD_EXECUTABLE(suStorageSubtract storageSubtract.cpp)

INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ rdConvertControls)
INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ rdConvertStorageToControls)
INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ rdSimplifyControls)
INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ suPerturbStorage)
INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ suStorageAdd)
INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ suStorageIntegrate)
INSTALL_TARGETS(${NMBLApp_BINARY_DIR}/LibDev/ suStorageSubtract)