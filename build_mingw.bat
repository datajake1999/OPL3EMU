@ECHO OFF
cd Driver\mingw
call "compile_all.bat"
cd..\..\Installer\mingw
call "compile_all.bat"
cd..\..\MidiSel\mingw
call "compile.bat"
cd..\..\OPL3EMU_CFG\mingw
call "compile.bat"
cd..\..
iscc "OPL3EMU_mingw.iss"
