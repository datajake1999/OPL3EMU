g++ -c ..\..\c_interface\c_interface.cpp
g++ -c ..\..\fmopl3lib_ext\opl3.cpp
g++ -c ..\..\fmopl3lib_ext\opl3class.cpp
g++ -c ..\..\src\MidiSynth.cpp
g++ -c ..\..\src\winmm_drv_doom_ext.cpp
g++ -c ..\..\synthlib_ext\i_oplmusic.cpp
g++ -s -static -shared -Wl,--add-stdcall-alias *.o -lwinmm -o opl3doom_ext.dll
