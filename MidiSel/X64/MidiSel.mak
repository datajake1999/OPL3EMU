# Microsoft Developer Studio Generated NMAKE File, Based on MidiSel.dsp
!IF "$(CFG)" == ""
CFG=MidiSel - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MidiSel - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MidiSel - Win32 Release" && "$(CFG)" != "MidiSel - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MidiSel.mak" CFG="MidiSel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MidiSel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MidiSel - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MidiSel - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MidiSel.exe"


CLEAN :
	-@erase "$(INTDIR)\MIDI Selector.obj"
	-@erase "$(INTDIR)\MIDI Selector.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MidiSel.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\MidiSel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MIDI Selector.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MidiSel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MidiSel.pdb" /machine:IX86 /out:"$(OUTDIR)\MidiSel.exe" /machine:AMD64 
LINK32_OBJS= \
	"$(INTDIR)\MIDI Selector.obj" \
	"$(INTDIR)\MIDI Selector.res"

"$(OUTDIR)\MidiSel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MidiSel - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MidiSel.exe"


CLEAN :
	-@erase "$(INTDIR)\MIDI Selector.obj"
	-@erase "$(INTDIR)\MIDI Selector.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MidiSel.exe"
	-@erase "$(OUTDIR)\MidiSel.ilk"
	-@erase "$(OUTDIR)\MidiSel.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\MidiSel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MIDI Selector.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MidiSel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MidiSel.pdb" /debug /machine:IX86 /out:"$(OUTDIR)\MidiSel.exe" /pdbtype:sept /machine:AMD64 
LINK32_OBJS= \
	"$(INTDIR)\MIDI Selector.obj" \
	"$(INTDIR)\MIDI Selector.res"

"$(OUTDIR)\MidiSel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MidiSel.dep")
!INCLUDE "MidiSel.dep"
!ELSE 
!MESSAGE Warning: cannot find "MidiSel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MidiSel - Win32 Release" || "$(CFG)" == "MidiSel - Win32 Debug"
SOURCE="..\MIDI Selector.cpp"

"$(INTDIR)\MIDI Selector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\MIDI Selector.rc"

!IF  "$(CFG)" == "MidiSel - Win32 Release"


"$(INTDIR)\MIDI Selector.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\MIDI Selector.res" /i "\git\OPL3EMU\MidiSel" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "MidiSel - Win32 Debug"


"$(INTDIR)\MIDI Selector.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\MIDI Selector.res" /i "\git\OPL3EMU\MidiSel" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

