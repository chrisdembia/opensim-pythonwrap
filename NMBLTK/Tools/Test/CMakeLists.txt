INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} 
					${NMBLApp_SOURCE_DIR}/Vendors 
					${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 rdTools)
ADD_EXECUTABLE(testTools testTools.cpp ExampleVectorFunctionUncoupledNxN.cpp rdSerializableObject2.cpp rdSerializableObject.cpp)

ADD_TEST(testTools ${TEST_PATH}/testTools)
