g++ -c ..\opl3midi_test.cpp
g++ -c ..\..\fmopl3lib\*.cpp
g++ -c ..\..\synthlib\opl3midi.cpp
g++ -s -static *.o -o opl3midi_test.exe
