SET(DOC_FILES OpenSim_ReleaseStatus.doc SimTrack_Tutorial.doc HowToUseSimTrack.doc SimTrack_UsersGuide.doc)

INSTALL_FILES(/doc/ .doc ${DOC_FILES})
INSTALL(DIRECTORY tutorials development DESTINATION doc PATTERN ".svn" EXCLUDE)

