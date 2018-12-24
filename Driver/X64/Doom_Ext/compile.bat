cl -c /I "..\..\include" ..\..\c_interface\c_interface.cpp ..\..\fmopl3lib_ext\*.cpp ..\..\src\MidiSynth.cpp ..\..\src\winmm_drv_doom_ext.cpp ..\..\synthlib_ext\i_oplmusic.cpp
link *.obj bufferoverflowU.lib kernel32.lib user32.lib winmm.lib /dll /def:"..\..\src\winmm_drv.def" /OUT:opl3doom_ext.dll
del *.obj
