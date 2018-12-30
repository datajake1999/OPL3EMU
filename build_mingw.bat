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
cd driver\oplclone\mingw
call "compile.bat"
cd..\..\test\mingw
call "compile.bat"
cd..\..\..
