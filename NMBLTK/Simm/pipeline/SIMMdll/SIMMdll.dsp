# Microsoft Developer Studio Project File - Name="SIMMdll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SIMMdll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SIMMdll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SIMMdll.mak" CFG="SIMMdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SIMMdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SIMMdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SIMMdll - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SIMMDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SIMMDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib acpp.lib solid.lib qhull.lib /nologo /dll /machine:I386 /out:"..\simulation.dll" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "SIMMdll - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SIMMDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SIMMDLL_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib acpp.lib solid.lib qhull.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libc" /out:"..\simulation.dll" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "SIMMdll - Win32 Release"
# Name "SIMMdll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\dynsim\src\assigns.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\constraint.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\contact.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\cylinder_wrap.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\derivs.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\dllmain.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\ellipsoid_wrap.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\gcvspl.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\gmc.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\impact.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\inits.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\invert.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\lcp_solver.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\lmdif_c.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\mathtools.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\model.sd

!IF  "$(CFG)" == "SIMMdll - Win32 Release"

# Begin Custom Build - Running SD/FAST...
InputPath=..\dynsim\src\model.sd

BuildCmds= \
	cd ..\dynsim\src \
	..\..\sdfast\sdfast model.sd \
	..\..\sdfast\sdfast -gl -lc \
	

"..\dynsim\src\model_d.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\dynsim\src\model_s.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\dynsim\src\sdlib.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "SIMMdll - Win32 Debug"

# PROP Intermediate_Dir "obj"
# Begin Custom Build - Running SD/FAST...
InputPath=..\dynsim\src\model.sd

BuildCmds= \
	cd ..\dynsim\src \
	..\..\sdfast\sdfast model.sd \
	..\..\sdfast\sdfast -gl -lc \
	

"..\dynsim\src\model_d.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\dynsim\src\model_s.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\dynsim\src\sdlib.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\dynsim\src\model_d.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\model_s.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\object.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\output.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\pipetools.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\readmuscles.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\readtools.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\sdlib.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\sdufuncs.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\sphere_wrap.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\spring_based.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\torus_wrap.c
# End Source File
# Begin Source File

SOURCE=..\dynsim\src\wrapping.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
