@ECHO OFF
set path="C:\Program Files\Inno Setup 5"
call "c:\program files\microsoft visual studio 8\vc\bin\vcvars32.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV32 /RETAIL
cd Driver\Apogee
NMAKE /f "opl3apogee.mak" CFG="opl3apogee - Win32 Release"
cd..\Doom
NMAKE /f "opl3doom.mak" CFG="opl3doom - Win32 Release"
cd..\Doom_Ext
NMAKE /f "opl3doom_ext.mak" CFG="opl3doom_ext - Win32 Release"
cd..\Windows
NMAKE /f "opl3windows.mak" CFG="opl3windows - Win32 Release"
cd..\..\Installer\Apogee
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Doom
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Doom_Ext
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Windows
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\..\MidiPlyr
NMAKE /f "MidiPlyr.mak" CFG="MidiPlyr - Win32 Release"
cd..\MidiSel
NMAKE /f "MidiSel.mak" CFG="MidiSel - Win32 Release"
cd..\OPL3EMU_CFG
NMAKE /f "OPL3EMU_CFG.mak" CFG="OPL3EMU_CFG - Win32 Release"
cd..\SetEnv
NMAKE /f "SetEnv.mak" CFG="SetEnv - Win32 Release"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV64 /RETAIL
cd..\Driver\IA64\Apogee
NMAKE /f "opl3apogee.mak" CFG="opl3apogee - Win32 Release"
cd..\Doom
NMAKE /f "opl3doom.mak" CFG="opl3doom - Win32 Release"
cd..\Doom_Ext
NMAKE /f "opl3doom_ext.mak" CFG="opl3doom_ext - Win32 Release"
cd..\Windows
NMAKE /f "opl3windows.mak" CFG="opl3windows - Win32 Release"
cd..\..\..\Installer\IA64\Apogee
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Doom
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Doom_Ext
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Windows
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\..\..\MidiPlyr\IA64
NMAKE /f "MidiPlyr.mak" CFG="MidiPlyr - Win32 Release"
cd..\..\MidiSel\IA64
NMAKE /f "MidiSel.mak" CFG="MidiSel - Win32 Release"
cd..\..\OPL3EMU_CFG\IA64
NMAKE /f "OPL3EMU_CFG.mak" CFG="OPL3EMU_CFG - Win32 Release"
cd..\..\SetEnv\IA64
NMAKE /f "SetEnv.mak" CFG="SetEnv - Win32 Release"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /X64 /RETAIL
cd..\..\Driver\X64\Apogee
NMAKE /f "opl3apogee.mak" CFG="opl3apogee - Win32 Release"
cd..\Doom
NMAKE /f "opl3doom.mak" CFG="opl3doom - Win32 Release"
cd..\Doom_Ext
NMAKE /f "opl3doom_ext.mak" CFG="opl3doom_ext - Win32 Release"
cd..\Windows
NMAKE /f "opl3windows.mak" CFG="opl3windows - Win32 Release"
cd..\..\..\Installer\X64\Apogee
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Doom
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Doom_Ext
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\Windows
NMAKE /f "drvsetup.mak" CFG="drvsetup - Win32 Release"
cd..\..\..\MidiPlyr\X64
NMAKE /f "MidiPlyr.mak" CFG="MidiPlyr - Win32 Release"
cd..\..\MidiSel\X64
NMAKE /f "MidiSel.mak" CFG="MidiSel - Win32 Release"
cd..\..\OPL3EMU_CFG\X64
NMAKE /f "OPL3EMU_CFG.mak" CFG="OPL3EMU_CFG - Win32 Release"
cd..\..\SetEnv\X64
NMAKE /f "SetEnv.mak" CFG="SetEnv - Win32 Release"
cd..\..
iscc "OPL3EMU.iss"
