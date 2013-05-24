IF(BUILD_PYTHON_WRAPPING)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

SET(swig_interface_file_python
    ${CMAKE_CURRENT_SOURCE_DIR}/pythonWrapOpenSim.i)

# Compile the library.
# http://www.swig.org/Doc2.0/SWIGDocumentation.html#Introduction_build_system
FIND_PACKAGE(PythonLibs REQUIRED)

SET(SimTKSWIG_INCLUDE_PATH ${OpenSim_SOURCE_DIR}/OpenSim/Wrapping/SimTKSWIG)

# TODO
# Find python home dir on path
SET(PYTHON_LIB ${PYTHON_LIBRARIES} CACHE FILEPATH 
      "Location of Python library")

# Get Python.h directory for first python on path.
EXECUTE_PROCESS(COMMAND python -c "from distutils.sysconfig import get_python_inc; print get_python_inc()"
    OUTPUT_VARIABLE FIND_PYTHON_INCLUDE_ON_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(PYTHON_INCLUDE_ON_PATH ${FIND_PYTHON_INCLUDE_ON_PATH} CACHE PATH 
      "Location of Python includes for first Python.exe on path")
	  
# Get numpy include directory for first python on path.
EXECUTE_PROCESS(COMMAND python -c "from numpy import get_include; print get_include()"
    OUTPUT_VARIABLE FIND_NUMPY_INCLUDE_ON_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(NUMPY_INCLUDE_ON_PATH ${FIND_NUMPY_INCLUDE_ON_PATH} CACHE PATH 
      "Location of Python includes for first Python.exe on path")

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SimTKSWIG_INCLUDE_PATH}
    ${PYTHON_INCLUDE_ON_PATH}
	${NUMPY_INCLUDE_ON_PATH}
    ${OpenSim_SOURCE_DIR}
    ${OpenSim_SOURCE_DIR}/Vendors
    )

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${swig_interface_file_python}
    PROPERTIES CPLUSPLUS ON)
# The below forces include of pound-included files in the *.i file.
#SET_SOURCE_FILES_PROPERTIES(${swig_interface_file_python}
#    PROPERTIES SWIG_FLAGS "-includeall")
# Provide any additional source files here.
SWIG_ADD_MODULE(opensim python ${swig_interface_file_python})
SWIG_LINK_LIBRARIES(opensim ${PYTHON_LIBRARIES}
    osimCommon osimSimulation osimAnalyses osimTools)

# Get the site-packages directory.
EXECUTE_PROCESS(COMMAND python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

INSTALL(TARGETS _opensim DESTINATION ${PYTHON_SITE_PACKAGES})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/opensim.py
    DESTINATION ${PYTHON_SITE_PACKAGES})
# This may be useful ( gives the name of target): ${SWIG_FILE_opensim_REAL_NAME}

# Test the code.
# TODO

ENDIF(BUILD_PYTHON_WRAPPING)
