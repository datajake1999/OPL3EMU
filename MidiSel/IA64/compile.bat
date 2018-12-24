cl -c "..\MIDI Selector.cpp"
rc "..\MIDI Selector.rc"
copy "..\MIDI Selector.RES" "MIDI Selector.RES"
del "..\MIDI Selector.RES"
link *.obj "MIDI Selector.res" advapi32.lib bufferoverflowU.lib comctl32.lib gdi32.lib kernel32.lib user32.lib winmm.lib /OUT:MidiSel.exe
del *.obj "MIDI Selector.res"
