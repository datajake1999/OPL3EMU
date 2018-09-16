@ECHO OFF
call "c:\program files\microsoft visual studio 8\vc\bin\vcvars32.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV32 /RETAIL
NMAKE /f "opl3midi_test.mak" CFG="opl3midi_test - Win32 Release"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV64 /RETAIL
cd IA64
NMAKE /f "opl3midi_test.mak" CFG="opl3midi_test - Win32 Release"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /X64 /RETAIL
cd..\X64
NMAKE /f "opl3midi_test.mak" CFG="opl3midi_test - Win32 Release"
