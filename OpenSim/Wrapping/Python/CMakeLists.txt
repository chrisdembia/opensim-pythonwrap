IF(BUILD_PYTHON_WRAPPING)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})
# [chrisdembia] This is the way that Ayman finds SWIG, but I want to use
# certain macros that the below does not find.
#INCLUDE(${CMAKE_ROOT}/Modules/FindSWIG.cmake)

#SET(swig_generated_file_python
#    ${CMAKE_CURRENT_SOURCE_DIR}/OpenSimPython_wrap.cxx)
SET(swig_interface_file_python
    ${CMAKE_CURRENT_SOURCE_DIR}/pythonWrapOpenSim.i)

#ADD_CUSTOM_TARGET(PythonWrap ${SWIG_EXECUTABLE} -v -c++ -python
#    -I${OpenSim_SOURCE_DIR} -I${Simbody_INCLUDE_DIR}
#    -o ${swig_generated_file_python}
#    -outdir ${CMAKE_CURRENT_SOURCE_DIR}/opensim
#    ${swig_interface_file_python})

#SET_TARGET_PROPERTIES(PythonWrap PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD on)

# Compile the library.
# http://www.swig.org/Doc2.0/SWIGDocumentation.html#Introduction_build_system
FIND_PACKAGE(PythonLibs REQUIRED)
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${OpenSim_SOURCE_DIR}
    ${OpenSim_SOURCE_DIR}/Vendors
    )

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${swig_interface_file_python}
    PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(${swig_interface_file_python}
#    PROPERTIES SWIG_FLAGS "-includeall")
# Provide any additional source files here.
SWIG_ADD_MODULE(opensim python ${swig_interface_file_python} testsrc.h)
SWIG_LINK_LIBRARIES(opensim ${PYTHON_LIBRARIES})

# Get the site-packages directory.
EXECUTE_PROCESS(COMMAND python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

INSTALL(TARGETS _opensim DESTINATION ${PYTHON_SITE_PACKAGES})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/opensim.py
    DESTINATION ${PYTHON_SITE_PACKAGES})
#${SWIG_FILE_opensim_REAL_NAME}

# Test the code.

ENDIF(BUILD_PYTHON_WRAPPING)
