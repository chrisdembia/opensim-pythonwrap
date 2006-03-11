PROJECT (RRA)

# TODO: Add CMC Include paths
# Lib path not set 

SET(RDI_ARCH $ENV{RDI_ARCH})
IF(WIN32)
	IF(${RDI_ARCH} MATCHES ".+")
	ELSE(${RDI_ARCH} MATCHES ".+")
		SET(RDI_ARCH VC71)
	ENDIF(${RDI_ARCH} MATCHES ".+")
ENDIF(WIN32)

SET (NMBL_INCLUDE_DIR  CACHE "" "Directory for NMBL headers (containing NMBLTK & Vendors)")
SET (NMBL_LIBS_DIR  CACHE "" "Top directory for own built libraries")
SET (CMC_INCLUDE_DIR  CACHE "" "Top directory for CMC headers=path to RDI/CMC/rdCMC.h")
SET(NMBL_INSTALL_LOCATION "$ENV{NMBL_INSTALL}")


SET(CMAKE_DEBUG_POSTFIX "_D" CACHE INTERNAL "" FORCE)

IF(USE_NMBL_INSTALL) 
    IF(NOT NMBL_INSTALL_LOCATION)
		MESSAGE(ERROR
     	"You selected to use NMBL_INSTALL but env var NMBL_INSTALL is not set.")
    ELSE(NOT NMBL_INSTALL_LOCATION)
		SET(NMBL_LIBS_DIR ${NMBL_INSTALL_LOCATION}/Lib)
		SET(NMBL_INCLUDE_DIR ${NMBL_INSTALL_LOCATION}/Include)
    ENDIF(NOT NMBL_INSTALL_LOCATION)
ELSE(USE_NMBL_INSTALL)
	IF(NOT NMBL_INCLUDE_DIR)
		MESSAGE(ERROR
     	"You selected to use your own headers but CMake variable NMBL_INCLUDE_DIR is not set.")
	ENDIF(NOT NMBL_INCLUDE_DIR)
	IF(NOT NMBL_LIBS_DIR)
		MESSAGE(ERROR
     	"You selected to use your own libraries but CMake variable NMBL_LIBS_DIR is not set.")
	ENDIF(NOT NMBL_LIBS_DIR)
	IF(NOT CMC_INCLUDE_DIR)
		MESSAGE(ERROR
     		"You need to specify the location for CMC headers in order to build with CMC.")
	ELSE(NOT CMC_INCLUDE_DIR)
		SET(RRA_INCLUDE_DIR ${CMC_INCLUDE_DIR})
	ENDIF(NOT CMC_INCLUDE_DIR)
ENDIF(USE_NMBL_INSTALL)

INCLUDE_DIRECTORIES(${NMBL_INCLUDE_DIR} 
		    ${CMC_INCLUDE_DIR})

LINK_DIRECTORIES(${NMBL_LIBS_DIR})

LINK_LIBRARIES(	debug acpp_D optimized acpp
		debug rdTools_D optimized rdTools
		debug rdSimulation_D optimized rdSimulation
		debug rdSDFast_D optimized rdSDFast
		debug suPipeline40_D optimized suPipeline40
		debug suPipeline40Workflow_D optimized suPipeline40Workflow
		debug rdCMC_D optimized rdCMC
		debug rdSQP_D optimized rdSQP
		debug suAnalyses_D optimized suAnalyses)

ADD_EXECUTABLE(rra rra.cpp)
