g++ ..\..\c_interface\c_interface.cpp ..\..\fmopl3lib\*.cpp ..\..\opal\*.cpp ..\..\src\MidiSynth.cpp ..\..\src\winmm_drv_windows.cpp ..\..\synthlib\opl3midi.cpp ..\..\zdopl\*.cpp -s -static -shared -Wl,--add-stdcall-alias -lwinmm -Wl,-subsystem,windows -o opl3windows.dll
