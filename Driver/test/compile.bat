g++ -c opl3midi_test.cpp
g++ -c ..\fmopl3lib\dbopl.cpp
g++ -c ..\fmopl3lib\emulator.cpp
g++ -c ..\fmopl3lib\hardware.cpp
g++ -c ..\fmopl3lib\InpOut32Helper.cpp
g++ -c ..\fmopl3lib\opl.cpp
g++ -c ..\fmopl3lib\opl3.cpp
g++ -c ..\fmopl3lib\opl3class.cpp
g++ -c ..\fmopl3lib\opl_hw.cpp
g++ -c ..\fmopl3lib\opl_lpt.cpp
g++ -c ..\fmopl3lib\resampler.cpp
g++ -c ..\fmopl3lib\silence.cpp
g++ -c ..\fmopl3lib\vgm_logging.cpp
g++ -c ..\fmopl3lib\wav_writer.cpp
g++ -c ..\fmopl3lib\ymf262.cpp
g++ -c ..\synthlib\opl3midi.cpp
g++ -s -static *.o -o opl3midi_test.exe
