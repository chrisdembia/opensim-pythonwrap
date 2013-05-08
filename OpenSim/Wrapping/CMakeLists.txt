#-----------------------------------------------------------------------------
#SET(CMAKE_DEBUG_POSTFIX "_d" CACHE INTERNAL "" FORCE)

SUBDIRS(Java)

INSTALL(DIRECTORY Matlab DESTINATION sdk PATTERN ".svn" EXCLUDE)

