# Microsoft Developer Studio Project File - Name="MDLDialog" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MDLDialog - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MDLDocument.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MDLDocument.mak" CFG="MDLDialog - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDLDialog - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MDLDialog - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MDLDialog - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MDLDIALOG_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MDLDIALOG_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../bin/MDLDialog.dll"

!ELSEIF  "$(CFG)" == "MDLDialog - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MDLDIALOG_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /Od /I "../resource" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MDLDIALOG_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../bin/MDLDialog.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MDLDialog - Win32 Release"
# Name "MDLDialog - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\source\CBase3DDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CControl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CMDLDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CSequenceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CSlider.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\source\CBase3DDocument.h
# End Source File
# Begin Source File

SOURCE=..\source\CControl.h
# End Source File
# Begin Source File

SOURCE=..\source\CDialog.h
# End Source File
# Begin Source File

SOURCE=..\source\CMDLDocument.h
# End Source File
# Begin Source File

SOURCE=..\source\CSequenceDlg.h
# End Source File
# Begin Source File

SOURCE=..\source\CSlider.h
# End Source File
# Begin Source File

SOURCE=..\resource\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\resource\mdl.rc
# End Source File
# End Group
# Begin Group "hlsdk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\hlsdk\activity.h
# End Source File
# Begin Source File

SOURCE=..\hlsdk\cmdlib.c
# End Source File
# Begin Source File

SOURCE=..\hlsdk\cmdlib.h
# End Source File
# Begin Source File

SOURCE=..\hlsdk\mathlib.c
# End Source File
# Begin Source File

SOURCE=..\hlsdk\mathlib.h
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio.h
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio_event.h
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio_export.cpp
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio_import.cpp
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio_render.cpp
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio_render.h
# End Source File
# Begin Source File

SOURCE=..\hlsdk\studio_utils.cpp
# End Source File
# End Group
# End Target
# End Project
