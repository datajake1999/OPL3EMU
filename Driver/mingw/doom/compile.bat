g++ -c ..\..\c_interface\c_interface.cpp
g++ -c ..\..\fmopl3lib\*.cpp
g++ -c ..\..\src\MidiSynth.cpp
g++ -c ..\..\src\winmm_drv_doom.cpp
g++ -c ..\..\synthlib\i_oplmusic.cpp
g++ -s -static -shared -Wl,--add-stdcall-alias *.o -lwinmm -Wl,-subsystem,windows -o opl3doom.dll
