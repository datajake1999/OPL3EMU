# Microsoft Developer Studio Project File - Name="opl3midi_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=opl3midi_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "opl3midi_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "opl3midi_test.mak" CFG="opl3midi_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "opl3midi_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "opl3midi_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "opl3midi_test - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "opl3midi_test - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "opl3midi_test - Win32 Release"
# Name "opl3midi_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\fmopl3lib\bitcrush.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\dbopl.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\emulator.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\hardware.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\InpOut32Helper.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl3.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl3class.cpp
# End Source File
# Begin Source File

SOURCE=..\synthlib\opl3midi.cpp
# End Source File
# Begin Source File

SOURCE=.\opl3midi_test.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl_hw.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl_lpt.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\resampler.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\silence.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\vgm_logging.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\wav_writer.cpp
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\ymf262.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\fmopl3lib\bitcrush.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\dbopl.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\emulator.h
# End Source File
# Begin Source File

SOURCE=..\synthlib\gmtimbre.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\hardware.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\InpOut32Helper.h
# End Source File
# Begin Source File

SOURCE=..\interface.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl3.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl3class.h
# End Source File
# Begin Source File

SOURCE=..\synthlib\opl3midi.h
# End Source File
# Begin Source File

SOURCE=..\synthlib\opl3type.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl_hw.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\opl_lpt.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\resampler.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\silence.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\vgm_logging.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\VGMFile.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\wav_writer.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\wavhdr.h
# End Source File
# Begin Source File

SOURCE=..\fmopl3lib\ymf262.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
