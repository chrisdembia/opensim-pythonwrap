# Microsoft Developer Studio Project File - Name="rdSimulation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=rdSimulation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rdSimulation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rdSimulation.mak" CFG="rdSimulation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rdSimulation - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rdSimulation - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rdSimulation - Win32 Release"

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
# ADD F90 /debug:none /libs:dll /threads
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RDSIMULATION_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\cygwin\home\fca\Dev\Source\Native\RD\Simulation" /I "C:\cygwin\home\fca\Dev\Source\Native\RD\Simulation\Model" /I "C:\cygwin\home\fca\Dev\Source\Native\RD\Simulation\Control" /I "C:\cygwin\home\fca\Dev\Source\Native\RD\Simulation\Integrator" /I "C:\cygwin\home\fca\Dev\Source\Native\RD\Simulation\Manager" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RDSIMULATION_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 xerces-c_2.lib rdTools.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating libraries...
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl
# End Special Build Tool

!ELSEIF  "$(CFG)" == "rdSimulation - Win32 Debug"

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
# ADD F90 /dbglibs /libs:dll /threads
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RDSIMULATION_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RDSIMULATION_EXPORTS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xerces-c_2D.lib rdTools_D.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/rdSimulation_D.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating libraries...
PostBuild_Cmds=$(RDI_INSTALL)\Bin\cpl D
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "rdSimulation - Win32 Release"
# Name "rdSimulation - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Model\rdActuator.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdActuatorSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdAnalysisSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdBody.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdCallback.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdCallbackSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdContactForce.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdContactForceSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Control\rdControl.cpp
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlConstant.cpp
# End Source File
# Begin Source File

SOURCE=..\Control\rdController.cpp
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlLinear.cpp
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlLinearNode.cpp
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdDerivCallback.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdDerivCallbackSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdForce.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdGeneralizedForce.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdIntegCallback.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdIntegCallbackSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Integrator\rdIntegRKF.cpp
# End Source File
# Begin Source File

SOURCE=..\Manager\rdManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdModel.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdModelIntegrand.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdModelIntegrandForActuators.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdMuscle.cpp
# End Source File
# Begin Source File

SOURCE=..\Integrator\rdRKF.cpp
# End Source File
# Begin Source File

SOURCE=..\rdSimulationDLL.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdSprings.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\rdTorque.cpp
# End Source File
# Begin Source File

SOURCE=..\Model\VectorFunctionForActuators.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Integrator\Integrand.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdActuator.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdActuatorSet.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdAnalysis.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdAnalysisSet.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdBody.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdCallback.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdCallbackSet.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdContactForce.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdContactForceSet.h
# End Source File
# Begin Source File

SOURCE=..\Control\rdControl.h
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlConstant.h
# End Source File
# Begin Source File

SOURCE=..\Control\rdController.h
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlLinear.h
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlLinearNode.h
# End Source File
# Begin Source File

SOURCE=..\Control\rdControlSet.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdDerivCallback.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdDerivCallbackSet.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdForce.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdGeneralizedForce.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdIntegCallback.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdIntegCallbackSet.h
# End Source File
# Begin Source File

SOURCE=..\Integrator\rdIntegrator.h
# End Source File
# Begin Source File

SOURCE=..\Integrator\rdIntegRKF.h
# End Source File
# Begin Source File

SOURCE=..\Manager\rdManager.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdModel.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdModelIntegrand.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdModelIntegrandForactuators.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdMuscle.h
# End Source File
# Begin Source File

SOURCE=..\Integrator\rdRKF.h
# End Source File
# Begin Source File

SOURCE=..\rdSimulationDLL.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdSprings.h
# End Source File
# Begin Source File

SOURCE=..\Model\rdTorque.h
# End Source File
# Begin Source File

SOURCE=..\Model\VectorFunctionForActuators.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
