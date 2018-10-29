g++ -c ..\..\c_interface\c_interface.cpp
g++ -c ..\..\fmopl3lib\*.cpp
g++ -c ..\..\src\MidiSynth.cpp
g++ -c ..\..\src\winmm_drv_windows.cpp
g++ -c ..\..\synthlib\opl3midi.cpp
g++ -s -static -shared -Wl,--add-stdcall-alias *.o -lwinmm -Wl,-subsystem,windows -o opl3windows.dll
