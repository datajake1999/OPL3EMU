g++ -c "..\MIDI Selector.cpp"
windres "..\MIDI Selector.rc" resource.o
g++ *.o C:\MinGW\lib\libadvapi32.a C:\MinGW\lib\libcomctl32.a C:\MinGW\lib\libgdi32.a C:\MinGW\lib\libkernel32.a C:\MinGW\lib\libuser32.a C:\MinGW\lib\libwinmm.a -o MidiSel.exe
