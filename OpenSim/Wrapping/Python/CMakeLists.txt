IF(BUILD_PYTHON_WRAPPING)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

SET(swig_interface_file_python
    ${CMAKE_CURRENT_SOURCE_DIR}/pythonWrapOpenSim.i)

# Need access to the Python C++ headers and libraries (Python C API).
# http://www.swig.org/Doc2.0/SWIGDocumentation.html#Introduction_build_system
FIND_PACKAGE(PythonLibs REQUIRED)

SET(SimTKSWIG_INCLUDE_PATH ${OpenSim_SOURCE_DIR}/OpenSim/Wrapping/SimTKSWIG)

# Find Python installation, etc.
# =============================================================================
# TODO the below may be worth using on Windows, but PythonLibs
# already lets the user modify these via PYTHON_INCLUDE_DIR and PYTHON_LIBRARY.
## Get the python shared library file. TODO not used yet.
#SET(PYTHON_LIB ${PYTHON_LIBRARIES} CACHE FILEPATH 
#    "Location of Python library (e.g, libpythonX.X.dll or libpythonX.X.so)")
#
## Python headers
## -----------------------------------------------------------------------------
## Get path containing Python.h for first Python installation on the PATH.
#EXECUTE_PROCESS(COMMAND
#    python -c "from distutils.sysconfig import get_python_inc; print get_python_inc()"
#    OUTPUT_VARIABLE FIND_PYTHON_INCLUDE_DIR_ON_PATH
#    OUTPUT_STRIP_TRAILING_WHITESPACE)
#
## Let the user choose actual dir, but set default based on what we found.
#SET(PYTHON_INCLUDE_DIR ${FIND_PYTHON_INCLUDE_DIR_FIRST_ON_PATH} CACHE PATH 
#    "Location of Python headers of Python installation you want to use for wrapping.")
# ^ The above may be unnecessary.
	  
# Numpy headers
# -----------------------------------------------------------------------------
# Get numpy include directory for first Python installation on the PATH.
# Need to do this for Windows machines. It seems that on Linux machines there
# may be a symlink, in the Python headers directory, to the NumPy headers.
EXECUTE_PROCESS(COMMAND
    python -c "from numpy import get_include; print get_include()"
    OUTPUT_VARIABLE FIND_NUMPY_INCLUDE_DIR_FIRST_ON_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(PYTHON_NUMPY_INCLUDE_DIR ${FIND_NUMPY_INCLUDE_DIR_FIRST_ON_PATH} CACHE PATH 
    "Location of Numpy headers of Python installation you want to use for wrapping.")

# Include the directories containing headers needed for the wrapping.
# Our own headers/interface files, Python headers, and OpenSim headers.
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR} # TODO need this?
    ${SimTKSWIG_INCLUDE_PATH}
    ${PYTHON_INCLUDE_DIR}
    ${PYTHON_NUMPY_INCLUDE_DIR}
    ${OpenSim_SOURCE_DIR}
    ${OpenSim_SOURCE_DIR}/Vendors
    )


# Set up SWIG target(s)
# =============================================================================
SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${swig_interface_file_python}
    PROPERTIES CPLUSPLUS ON)
# The below forces include of pound-included files in the *.i file.
#SET_SOURCE_FILES_PROPERTIES(${swig_interface_file_python}
#    PROPERTIES SWIG_FLAGS "-includeall")
# Provide any additional source files here.
SWIG_ADD_MODULE(opensim python ${swig_interface_file_python})
SWIG_LINK_LIBRARIES(opensim ${PYTHON_LIBRARIES}
    osimCommon osimSimulation osimAnalyses osimActuators osimTools)

# Install the python files and C++ wrapper libraries on the machine.
# =============================================================================
# Get the site-packages directory.
EXECUTE_PROCESS(COMMAND
    python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"
    OUTPUT_VARIABLE PYTHON_LIB_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

INSTALL(TARGETS _opensim DESTINATION ${PYTHON_LIB_DIR})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/opensim.py
    DESTINATION ${PYTHON_LIB_DIR})
# This may be useful ( gives the name of target): ${SWIG_FILE_opensim_REAL_NAME}

# Test the code.
# TODO

ENDIF(BUILD_PYTHON_WRAPPING)
