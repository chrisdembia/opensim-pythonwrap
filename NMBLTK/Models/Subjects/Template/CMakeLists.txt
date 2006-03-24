SET(NMBL_BUILD_LOCATION "$ENV{NMBL_INSTALL}")

IF(NOT NMBL_BUILD_LOCATION)
MESSAGE(FATAL_ERROR
     "Cannot build without NMBL.  Please set env var. NMBL_INSTALL to the directory of your top NMBL installation directory.")
ENDIF(NOT NMBL_BUILD_LOCATION)


INCLUDE_DIRECTORIES($(NMBL_INSTALL)/Include
		    $(NMBL_INSTALL)/Include/Vendors 
		    $(NMBL_INSTALL)/Include/Vendors/xerces-c-src2_4_0/src 
		    $(NMBL_INSTALL)/Include/dp
)

LINK_DIRECTORIES( $(NMBL_INSTALL)/Lib/$ENV{RDI_ARCH})

SET(SUBJECT_SOURCES _template__dyn.c _template__sar.c sdufuncs_darryl.c su_Template_.cpp dynsim/src/sdfor.c)

SET(SUBJECT_HEADERS su_Template_.h)


ADD_DEFINITIONS(-DRDSDFAST_EXPORTS)

LINK_LIBRARIES( debug xerces-c_2D optimized xerces-c_2 
				debug rdTools optimized rdTools_D
				debug rdSimulation optimized rdSimulation_D
				debug acpp optimized acpp_D
				debug rdSDFast optimized rdSDFast_D
				debug suPipeline40Workflow optimized suPipeline40Workflow_D
				debug suPipeline40 optimized suPipeline40_D
				debug suAnalyses optimized suAnalyses_D		
)
ADD_EXECUTABLE(su_Template__Forward su_Template__Forward.cpp ${SUBJECT_SOURCES} ${SUBJECT_HEADERS})

ADD_EXECUTABLE(su_Template__Perturb su_Template__Perturb.cpp ${SUBJECT_SOURCES} ${SUBJECT_HEADERS})

ADD_EXECUTABLE(su_Template__CMC su_Template__CMC.cpp ${SUBJECT_SOURCES} ${SUBJECT_HEADERS})

TARGET_LINK_LIBRARIES(su_Template__CMC
		rdCMC
		rdSQP
)

