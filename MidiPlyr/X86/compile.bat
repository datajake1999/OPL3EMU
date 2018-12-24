cl -c ..\src\*.c
rc ..\src\MidiPlyr.Rc
copy ..\src\MidiPlyr.RES MidiPlyr.RES
del ..\src\MidiPlyr.RES
link *.obj MidiPlyr.res bufferoverflowU.lib comctl32.lib comdlg32.lib gdi32.lib kernel32.lib shell32.lib user32.lib winmm.lib /OUT:MidiPlyr.exe
del *.obj MidiPlyr.res
