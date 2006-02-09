# Microsoft Developer Studio Project File - Name="solid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=solid - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "solid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "solid.mak" CFG="solid - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "solid - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "solid - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "solid - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj"
# PROP Intermediate_Dir "obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /GR /GX /O2 /I "include" /I "..\QHull\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USING_STD_NAMESPACE" /D "QHULL" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\solid.lib"

!ELSEIF  "$(CFG)" == "solid - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GR /GX /ZI /Od /I "include" /I "..\QHull\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USING_STD_NAMESPACE" /D "QHULL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\solid.lib"

!ENDIF 

# Begin Target

# Name "solid - Win32 Release"
# Name "solid - Win32 Debug"
# Begin Source File

SOURCE=src\BBoxTree.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Box.cpp
# End Source File
# Begin Source File

SOURCE=".\src\C-api.cpp"
# End Source File
# Begin Source File

SOURCE=.\src\Complex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Cone.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Convex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Cylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Endpoint.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pipesolid.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Polygon.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Polyhedron.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Polytope.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Response.cpp
# End Source File
# Begin Source File

SOURCE=.\src\RespTable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Simplex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Transform.cpp
# End Source File
# End Target
# End Project
