cl -c /I "..\..\include" ..\opl3midi_test.cpp ..\..\fmopl3lib\*.cpp ..\..\synthlib\opl3midi.cpp
link *.obj bufferoverflowU.lib kernel32.lib user32.lib /OUT:opl3midi_test.exe
