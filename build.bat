@ECHO OFF
set path="C:\Program Files\Inno Setup 5"
call "c:\program files\microsoft visual studio 8\vc\bin\vcvars32.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV32 /RETAIL
cd Driver\X86
call "compile_all.bat"
cd..\..\Installer\X86
call "compile_all.bat"
cd..\..\MidiPlyr\X86
call "compile.bat"
cd..\..\MidiSel\X86
call "compile.bat"
cd..\..\OPL3EMU_CFG\X86
call "compile.bat"
cd..\..\SetEnv\X86
call "compile.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV64 /RETAIL
cd..\..\Driver\IA64
call "compile_all.bat"
cd..\..\Installer\IA64
call "compile_all.bat"
cd..\..\MidiPlyr\IA64
call "compile.bat"
cd..\..\MidiSel\IA64
call "compile.bat"
cd..\..\OPL3EMU_CFG\IA64
call "compile.bat"
cd..\..\SetEnv\IA64
call "compile.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /X64 /RETAIL
cd..\..\Driver\X64
call "compile_all.bat"
cd..\..\Installer\X64
call "compile_all.bat"
cd..\..\MidiPlyr\X64
call "compile.bat"
cd..\..\MidiSel\X64
call "compile.bat"
cd..\..\OPL3EMU_CFG\X64
call "compile.bat"
cd..\..\SetEnv\X64
call "compile.bat"
cd..\..
iscc "OPL3EMU.iss"
