# Microsoft Developer Studio Project File - Name="rdUTWalking8Prescribed" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=rdUTWalking8Prescribed - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rdUTWalking8Prescribed.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rdUTWalking8Prescribed.mak" CFG="rdUTWalking8Prescribed - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rdUTWalking8Prescribed - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rdUTWalking8Prescribed - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rdUTWalking8Prescribed - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE F90 /compile_only /dll /nologo /warn:nofileopt
# ADD F90 /compile_only /debug:none /dll /nologo /reentrancy:threaded /threads /warn:nofileopt
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RDSDFAST_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rdTools.lib rdSimulation.lib rdSDFast.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl
# End Special Build Tool

!ELSEIF  "$(CFG)" == "rdUTWalking8Prescribed - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE F90 /check:bounds /compile_only /dbglibs /debug:full /dll /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /dbglibs /debug:full /dll /nologo /reentrancy:threaded /threads /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RDSDFAST_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rdTools_D.lib rdSimulation_D.lib rdSDFast_D.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"Debug/rdUTWalking8Prescribed_D.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl D
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "rdUTWalking8Prescribed - Win32 Release"
# Name "rdUTWalking8Prescribed - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=..\23skgspec.f
# End Source File
# Begin Source File

SOURCE=..\cylinder.c
# End Source File
# Begin Source File

SOURCE=..\matrix.c
# End Source File
# Begin Source File

SOURCE=..\musmodel.f
# End Source File
# Begin Source File

SOURCE=..\rdUTWalking8_sdufuncs.c
# End Source File
# Begin Source File

SOURCE=..\rdUTWalking8Prescribed.cpp
# End Source File
# Begin Source File

SOURCE=..\rdUTWalkingPrescribedIntegCallback.cpp
# End Source File
# Begin Source File

SOURCE=..\sdtransform.f
# End Source File
# Begin Source File

SOURCE=..\str_funcs.f
# End Source File
# Begin Source File

SOURCE=..\utModelPrescribed_dyn.c
# End Source File
# Begin Source File

SOURCE=..\utModelPrescribed_sar.c
# End Source File
# Begin Source File

SOURCE=..\w23force.f
DEP_F90_W23FO=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23intl.f
DEP_F90_W23IN=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23moddat.f
DEP_F90_W23MO=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23newynode.f
DEP_F90_W23NE=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23parameters.f
DEP_F90_W23PA=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23ref_intl.f
DEP_F90_W23RE=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23sforce.f
DEP_F90_W23SF=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# Begin Source File

SOURCE=..\w23xbound.f
DEP_F90_W23XB=\
	"..\w23comblk.h"\
	"..\w23params.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\cylinder.h
# End Source File
# Begin Source File

SOURCE=..\matrix.h
# End Source File
# Begin Source File

SOURCE=..\rdUTWalking8Prescribed.h
# End Source File
# Begin Source File

SOURCE=..\rdUTWalkingPrescribedIntegCallback.h
# End Source File
# Begin Source File

SOURCE=..\utwalking.h
# End Source File
# Begin Source File

SOURCE=..\w23comblk.h
# End Source File
# Begin Source File

SOURCE=..\w23params.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
