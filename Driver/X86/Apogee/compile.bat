cl -c /I "..\..\include" ..\..\c_interface\c_interface.cpp ..\..\fmopl3lib\*.cpp ..\..\src\MidiSynth.cpp ..\..\src\winmm_drv_apogee.cpp ..\..\synthlib\al_midi.cpp
link *.obj bufferoverflowU.lib kernel32.lib user32.lib winmm.lib /dll /def:"..\..\src\winmm_drv.def" /OUT:opl3apogee.dll
del *.obj
