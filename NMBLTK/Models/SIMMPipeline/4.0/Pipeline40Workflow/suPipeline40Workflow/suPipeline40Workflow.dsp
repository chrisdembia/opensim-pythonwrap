# Microsoft Developer Studio Project File - Name="suPipeline40Workflow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=suPipeline40Workflow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "suPipeline40Workflow.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "suPipeline40Workflow.mak" CFG="suPipeline40Workflow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "suPipeline40Workflow - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "suPipeline40Workflow - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
RSC=rc.exe

!IF  "$(CFG)" == "suPipeline40Workflow - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\suPipeline40" /I "..\..\suPipeline40\dp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
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
PreLink_Desc=Updating .h files...
PreLink_Cmds=$(RDI_INSTALL)\Bin\cphq
PostBuild_Desc=Updating libraries...
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl
# End Special Build Tool

!ELSEIF  "$(CFG)" == "suPipeline40Workflow - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\suPipeline40" /I "..\..\suPipeline40\dp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_POSIX_" /D "RDSDFAST_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\suPipeline40Workflow_D.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl D
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "suPipeline40Workflow - Win32 Release"
# Name "suPipeline40Workflow - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=..\assigns.c
# End Source File
# Begin Source File

SOURCE=..\derivs.c
# End Source File
# Begin Source File

SOURCE=..\gmc_dt.c
# End Source File
# Begin Source File

SOURCE=..\inits.c
# End Source File
# Begin Source File

SOURCE="..\suPipeline40Workflow-helper.cpp"
# End Source File
# Begin Source File

SOURCE=..\suPipeline40Workflow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\functions.h
# End Source File
# Begin Source File

SOURCE=..\gmc_dt.h
# End Source File
# Begin Source File

SOURCE=..\model.h
# End Source File
# Begin Source File

SOURCE="..\suPipeline40Workflow-helper.h"
# End Source File
# Begin Source File

SOURCE=..\suPipeline40Workflow.h
# End Source File
# End Group
# End Target
# End Project
