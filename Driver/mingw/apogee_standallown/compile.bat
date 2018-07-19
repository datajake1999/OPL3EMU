g++ -c ..\..\c_interface\c_interface.cpp
g++ -c ..\..\fmopl3lib\dbopl.cpp
g++ -c ..\..\fmopl3lib\InpOut32Helper.cpp
g++ -c ..\..\fmopl3lib\opl.cpp
g++ -c ..\..\fmopl3lib\opl3.cpp
g++ -c ..\..\fmopl3lib\opl3class.cpp
g++ -c ..\..\fmopl3lib\opl_hw.cpp
g++ -c ..\..\fmopl3lib\vgm_logging.cpp
g++ -c ..\..\fmopl3lib\wav_writer.cpp
g++ -c ..\..\fmopl3lib\ymf262.cpp
g++ -c ..\..\synthlib\al_midi.cpp
g++ -shared -Wl,--add-stdcall-alias *.o -lwinmm -o opl3apogee.dll