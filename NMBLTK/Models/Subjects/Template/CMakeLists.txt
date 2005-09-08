SET(NMBL_BUILD_LOCATION "$ENV{NMBL_INSTALL}")

IF(NOT NMBL_BUILD_LOCATION)
MESSAGE(FATAL_ERROR
     "Cannot build without NMBL.  Please set env var. NMBL_INSTALL to the directory of your NMBL libraries.")
ENDIF(NOT NMBL_BUILD_LOCATION)

SET(RDI_BUILD_LOCATION "$ENV{RDI_INSTALL}")

IF(NOT RDI_BUILD_LOCATION)
MESSAGE(FATAL_ERROR
     "Cannot build without RDI install.  Please set env var. RDI_INSTALL to the directory of your RDI libraries.")
ENDIF(NOT RDI_BUILD_LOCATION)

INCLUDE_DIRECTORIES($(RDI_INSTALL)/Include
		    $(RDI_INSTALL)/Include/Vendors 
		    $(RDI_INSTALL)/Include/Vendors/xerces-c-src2_4_0/src 
		    $(RDI_INSTALL)/Include/dp
)

LINK_DIRECTORIES( $(NMBL_INSTALL)/bin $(RDI_INSTALL)/Lib/$ENV{RDI_ARCH})

SET(SUBJECT_SOURCES _template__dyn.c _template__sar.c sdufuncs_darryl.c su_Template_.cpp dynsim/src/sdfor.c)

SET(SUBJECT_HEADERS su_Template_.h)


ADD_DEFINITIONS(-DRDSDFAST_EXPORTS)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
		rdTools
		rdSimulation
		acpp
		rdSDFast
		suPipeline40Workflow
		suPipeline40
		suAnalyses
		
)
ADD_EXECUTABLE(su_Template__Forward su_Template__Forward.cpp ${SUBJECT_SOURCES} ${SUBJECT_HEADERS})

ADD_EXECUTABLE(su_Template__Perturb su_Template__Perturb.cpp ${SUBJECT_SOURCES} ${SUBJECT_HEADERS})

ADD_EXECUTABLE(su_Template__CMC su_Template__CMC.cpp ${SUBJECT_SOURCES} ${SUBJECT_HEADERS})

TARGET_LINK_LIBRARIES(su_Template__CMC
		debug rdCMC optimized rdCMC
		debug rdSQP optimized rdSQP
)

