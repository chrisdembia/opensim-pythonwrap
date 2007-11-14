##SUBDIRS(Tutorials)

SET(DOC_FILES "Tutorials/OpenSim Tutorial 1.pdf" "Tutorials/OpenSim Tutorial 2.pdf" "Tutorials/OpenSim Tutorial 3.pdf")

INSTALL_FILES(/doc/ FILES  ${DOC_FILES})
##INSTALL(DIRECTORY tutorials development DESTINATION doc PATTERN ".svn" EXCLUDE)

