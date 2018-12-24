cl -c /I "..\..\include" ..\oplclone.cpp ..\..\fmopl3lib\*.cpp
link *.obj bufferoverflowU.lib kernel32.lib user32.lib /OUT:oplclone.exe
