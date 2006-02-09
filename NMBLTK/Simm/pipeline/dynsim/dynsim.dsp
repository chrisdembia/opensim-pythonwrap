# Microsoft Developer Studio Project File - Name="dynsim" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=dynsim - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dynsim.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dynsim.mak" CFG="dynsim - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dynsim - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dynsim - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dynsim - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj"
# PROP Intermediate_Dir "obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D CONTACT_DETECTION=0 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib acpp.lib solid.lib qhull.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc.lib" /out:"..\simulation.exe" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "dynsim - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D CONTACT_DETECTION=0 /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib acpp.lib solid.lib qhull.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrt.lib" /out:"..\simulation.exe" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "dynsim - Win32 Release"
# Name "dynsim - Win32 Debug"
# Begin Source File

SOURCE=src\assigns.c
# End Source File
# Begin Source File

SOURCE=.\src\constraint.c
# End Source File
# Begin Source File

SOURCE=src\contact.c
# End Source File
# Begin Source File

SOURCE=.\src\cylinder_wrap.c
# End Source File
# Begin Source File

SOURCE=src\derivs.c
# End Source File
# Begin Source File

SOURCE=.\src\ellipsoid_wrap.c
# End Source File
# Begin Source File

SOURCE=.\src\gcvspl.c
# End Source File
# Begin Source File

SOURCE=src\gmc.c
# End Source File
# Begin Source File

SOURCE=src\impact.c
# End Source File
# Begin Source File

SOURCE=src\inits.c
# End Source File
# Begin Source File

SOURCE=src\invert.c
# End Source File
# Begin Source File

SOURCE=src\lcp_solver.c
# End Source File
# Begin Source File

SOURCE=.\src\lmdif_c.c
# End Source File
# Begin Source File

SOURCE=.\src\main.c
# End Source File
# Begin Source File

SOURCE=src\mathtools.c
# End Source File
# Begin Source File

SOURCE=.\src\model.sd

!IF  "$(CFG)" == "dynsim - Win32 Release"

# Begin Custom Build - Running SD/FAST...
InputPath=.\src\model.sd

BuildCmds= \
	cd src \
	..\..\sdfast\sdfast model.sd \
	..\..\sdfast\sdfast -gl -lc \
	

".\src\model_d.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\src\model_s.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\src\sdlib.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "dynsim - Win32 Debug"

# Begin Custom Build - Running SD/FAST...
InputPath=.\src\model.sd

BuildCmds= \
	cd src \
	..\..\sdfast\sdfast model.sd \
	..\..\sdfast\sdfast -gl -lc \
	

".\src\model_d.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\src\model_s.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\src\sdlib.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=src\model_d.c
# End Source File
# Begin Source File

SOURCE=src\model_s.c
# End Source File
# Begin Source File

SOURCE=src\object.c
# End Source File
# Begin Source File

SOURCE=.\src\output.c
# End Source File
# Begin Source File

SOURCE=src\pipetools.c
# End Source File
# Begin Source File

SOURCE=src\readmuscles.c
# End Source File
# Begin Source File

SOURCE=src\readtools.c
# End Source File
# Begin Source File

SOURCE=src\sdfor.c
# End Source File
# Begin Source File

SOURCE=src\sdlib.c
# End Source File
# Begin Source File

SOURCE=.\src\sdufuncs.c
# End Source File
# Begin Source File

SOURCE=.\src\sphere_wrap.c
# End Source File
# Begin Source File

SOURCE=.\src\spring_based.c
# End Source File
# Begin Source File

SOURCE=.\src\torus_wrap.c
# End Source File
# Begin Source File

SOURCE=.\src\wrapping.c
# End Source File
# End Target
# End Project
