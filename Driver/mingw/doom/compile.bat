g++ -c ..\..\c_interface\c_interface.cpp
g++ -c ..\..\fmopl3lib\dbopl.cpp
g++ -c ..\..\fmopl3lib\emulator.cpp
g++ -c ..\..\fmopl3lib\hardware.cpp
g++ -c ..\..\fmopl3lib\InpOut32Helper.cpp
g++ -c ..\..\fmopl3lib\opl.cpp
g++ -c ..\..\fmopl3lib\opl3.cpp
g++ -c ..\..\fmopl3lib\opl3class.cpp
g++ -c ..\..\fmopl3lib\opl_hw.cpp
g++ -c ..\..\fmopl3lib\opl_lpt.cpp
g++ -c ..\..\fmopl3lib\resampler.cpp
g++ -c ..\..\fmopl3lib\silence.cpp
g++ -c ..\..\fmopl3lib\vgm_logging.cpp
g++ -c ..\..\fmopl3lib\wav_writer.cpp
g++ -c ..\..\fmopl3lib\ymf262.cpp
g++ -c ..\..\src\MidiSynth.cpp
g++ -c ..\..\src\winmm_drv_doom.cpp
g++ -c ..\..\synthlib\i_oplmusic.cpp
g++ -s -static -shared -Wl,--add-stdcall-alias *.o -lwinmm -Wl,-subsystem,windows -o opl3doom.dll
