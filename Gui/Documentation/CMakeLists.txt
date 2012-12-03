##SUBDIRS(Tutorials)

##SET(DOC_FILES "Tutorials/*.pdf")
FILE(GLOB DOC_FILES "Tutorials/*.pdf")
INSTALL_FILES(/doc/ FILES  ${DOC_FILES})
##INSTALL(DIRECTORY tutorials development DESTINATION doc PATTERN ".svn" EXCLUDE)

