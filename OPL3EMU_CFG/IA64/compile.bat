cl -c ..\OPL3EMU_CFG.c
rc ..\OPL3EMU_CFG.rc
copy ..\OPL3EMU_CFG.RES OPL3EMU_CFG.RES
del ..\OPL3EMU_CFG.RES
link *.obj OPL3EMU_CFG.RES bufferoverflowU.lib kernel32.lib user32.lib /OUT:OPL3EMU_CFG.exe
del *.obj OPL3EMU_CFG.RES
