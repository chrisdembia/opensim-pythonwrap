SET(DOC_FILES SimTrack_Tutorial.doc HowToUseSimTrack.doc SimTrack_UsersGuide.doc)

INSTALL_FILES(/doc/ FILES ${DOC_FILES})
#INSTALL(DIRECTORY tutorials development DESTINATION doc PATTERN ".svn" EXCLUDE)

