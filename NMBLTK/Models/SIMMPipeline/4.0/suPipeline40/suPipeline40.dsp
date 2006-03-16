# Microsoft Developer Studio Project File - Name="suPipeline40" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=suPipeline40 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "suPipeline40.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "suPipeline40.mak" CFG="suPipeline40 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "suPipeline40 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "suPipeline40 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
RSC=rc.exe

!IF  "$(CFG)" == "suPipeline40 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE F90 /compile_only /nologo /warn:nofileopt
# ADD F90 /compile_only /nologo /warn:nofileopt
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\dp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "RDSDFAST_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating libraries...
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl
# End Special Build Tool

!ELSEIF  "$(CFG)" == "suPipeline40 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE F90 /check:bounds /compile_only /dbglibs /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /browser /check:bounds /compile_only /dbglibs /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\dp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "RDSDFAST_EXPORTS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\suPipeline40_D.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating libraries...
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl D
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "suPipeline40 - Win32 Release"
# Name "suPipeline40 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=.\constraint.c
# End Source File
# Begin Source File

SOURCE=.\contact.c
# End Source File
# Begin Source File

SOURCE=.\cylinder_wrap.c
# End Source File
# Begin Source File

SOURCE=.\ellipsoid_wrap.c
# End Source File
# Begin Source File

SOURCE=.\gcvspl.c
# End Source File
# Begin Source File

SOURCE=.\gmc.c
# End Source File
# Begin Source File

SOURCE=.\impact.c
# End Source File
# Begin Source File

SOURCE=.\invert.c
# End Source File
# Begin Source File

SOURCE=.\lcp_solver.c
# End Source File
# Begin Source File

SOURCE=.\lmdif_c.c
# End Source File
# Begin Source File

SOURCE=.\mathtools.c
# End Source File
# Begin Source File

SOURCE=.\object.c
# End Source File
# Begin Source File

SOURCE=.\output.c
# End Source File
# Begin Source File

SOURCE=.\pipetools.c
# End Source File
# Begin Source File

SOURCE=.\readmuscles.c
# End Source File
# Begin Source File

SOURCE=.\readtools.c
# End Source File
# Begin Source File

SOURCE=.\simm_init_40.c
# End Source File
# Begin Source File

SOURCE=.\sphere_wrap.c
# End Source File
# Begin Source File

SOURCE=.\spring_based.c
# End Source File
# Begin Source File

SOURCE=".\suPipeline40-helper.cpp"
# End Source File
# Begin Source File

SOURCE=.\suPipeline40.cpp
# End Source File
# Begin Source File

SOURCE=.\torus_wrap.c
# End Source File
# Begin Source File

SOURCE=.\wrapping.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\basic.h
# End Source File
# Begin Source File

SOURCE=.\dp.h
# End Source File
# Begin Source File

SOURCE=.\f2c.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\gcvspl.h
# End Source File
# Begin Source File

SOURCE=.\macros.h
# End Source File
# Begin Source File

SOURCE=.\mathtools.h
# End Source File
# Begin Source File

SOURCE=.\object.h
# End Source File
# Begin Source File

SOURCE=.\pipesolid.h
# End Source File
# Begin Source File

SOURCE=.\simm_init_40.h
# End Source File
# Begin Source File

SOURCE=.\structs.h
# End Source File
# Begin Source File

SOURCE=".\suPipeline40-helper.h"
# End Source File
# Begin Source File

SOURCE=.\suPipeline40.h
# End Source File
# Begin Source File

SOURCE=.\universal_40.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sdmassmat.c
# End Source File
# End Target
# End Project
