gcc -c ..\OPL3EMU_CFG.c
windres ..\OPL3EMU_CFG.rc resource.o
gcc *.o -o OPL3EMU_CFG.exe
