g++ -c "..\MIDI Selector.cpp"
windres "..\MIDI Selector.rc" resource.o
g++ *.o -ladvapi32 -lcomctl32 -lgdi32 -lkernel32 -luser32 -lwinmm -o MidiSel.exe
