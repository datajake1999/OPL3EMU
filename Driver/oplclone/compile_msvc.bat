@ECHO OFF
call "c:\program files\microsoft visual studio 8\vc\bin\vcvars32.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV32 /RETAIL
cd X86
call "compile.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /SRV64 /RETAIL
cd..\IA64
call "compile.bat"
call "C:\program files\Microsoft Platform SDK\SetEnv.Cmd" /X64 /RETAIL
cd..\X64
call "compile.bat"
cd..
