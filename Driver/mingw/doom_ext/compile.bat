g++ -c ..\..\fmopl3lib_ext\opl3.cpp
g++ -c ..\..\fmopl3lib_ext\opl3class.cpp
g++ -c ..\..\src\MidiSynth.cpp
g++ -c ..\..\src\winmm_drv_doom_ext.cpp
g++ -c ..\..\synthlib_ext\i_oplmusic.cpp
g++ -shared -Wl,--add-stdcall-alias *.o C:\MinGW\lib\libwinmm.a -o opl3doom_ext.dll
