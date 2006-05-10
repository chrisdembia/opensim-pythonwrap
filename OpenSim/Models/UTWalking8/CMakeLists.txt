SET(KIT UTWalking8)
SET(UKIT UTWALKING8)

SET(SOURCE_FILES 
	23skgspec.f
	cylinder.c
	matrix.c
	musmodel.f
	rdUTWalking8.cpp
	rdUTWalking8_sdufuncs.c
	rdUTWalkingIntegCallback.cpp
	sdtransform.f
	str_funcs.f
	utModel_dyn.c
	utModel_sar.c
	w23sforce.f
	w23intl.f
	w23moddat.f
	w23newynode.f
	w23parameters.f
	w23ref_intl.f
	w23sforce.f
	w23xbound.f
)

FILE(GLOB INCLUDE_FILES *.h)

INCLUDE_DIRECTORIES(${NMBLApp_SOURCE_DIR} ${NMBLApp_SOURCE_DIR}/Vendors/xerces-c-src2_4_0/src)

SET(EXPORT_MACRO "RDSDFAST_EXPORTS,_USRDLL")

LINK_LIBRARIES( rdTools rdSimulation rdSDFast)

ADD_LIBRARY(rd${KIT} SHARED SOURCE_FILES) 

SET_TARGET_PROPERTIES(rd${KIT} PROPERTIES
   DEFINE_SYMBOL ${EXPORT_MACRO}
)

