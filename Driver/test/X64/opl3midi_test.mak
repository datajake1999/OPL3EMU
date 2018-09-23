# Microsoft Developer Studio Generated NMAKE File, Based on opl3midi_test.dsp
!IF "$(CFG)" == ""
CFG=opl3midi_test - Win32 Debug
!MESSAGE No configuration specified. Defaulting to opl3midi_test - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "opl3midi_test - Win32 Release" && "$(CFG)" != "opl3midi_test - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "opl3midi_test.mak" CFG="opl3midi_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "opl3midi_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "opl3midi_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "opl3midi_test - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\opl3midi_test.exe"


CLEAN :
	-@erase "$(INTDIR)\bitcrush.obj"
	-@erase "$(INTDIR)\dbopl.obj"
	-@erase "$(INTDIR)\emulator.obj"
	-@erase "$(INTDIR)\hardware.obj"
	-@erase "$(INTDIR)\InpOut32Helper.obj"
	-@erase "$(INTDIR)\opl.obj"
	-@erase "$(INTDIR)\opl3.obj"
	-@erase "$(INTDIR)\opl3class.obj"
	-@erase "$(INTDIR)\opl3midi.obj"
	-@erase "$(INTDIR)\opl3midi_test.obj"
	-@erase "$(INTDIR)\opl_hw.obj"
	-@erase "$(INTDIR)\opl_lpt.obj"
	-@erase "$(INTDIR)\resampler.obj"
	-@erase "$(INTDIR)\silence.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vgm_logging.obj"
	-@erase "$(INTDIR)\wav_writer.obj"
	-@erase "$(INTDIR)\ymf262.obj"
	-@erase "$(OUTDIR)\opl3midi_test.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\opl3midi_test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\opl3midi_test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\opl3midi_test.pdb" /machine:IX86 /out:"$(OUTDIR)\opl3midi_test.exe" /machine:AMD64 
LINK32_OBJS= \
	"$(INTDIR)\bitcrush.obj" \
	"$(INTDIR)\dbopl.obj" \
	"$(INTDIR)\emulator.obj" \
	"$(INTDIR)\hardware.obj" \
	"$(INTDIR)\InpOut32Helper.obj" \
	"$(INTDIR)\opl.obj" \
	"$(INTDIR)\opl3.obj" \
	"$(INTDIR)\opl3class.obj" \
	"$(INTDIR)\opl3midi.obj" \
	"$(INTDIR)\opl3midi_test.obj" \
	"$(INTDIR)\opl_hw.obj" \
	"$(INTDIR)\opl_lpt.obj" \
	"$(INTDIR)\resampler.obj" \
	"$(INTDIR)\silence.obj" \
	"$(INTDIR)\vgm_logging.obj" \
	"$(INTDIR)\wav_writer.obj" \
	"$(INTDIR)\ymf262.obj"

"$(OUTDIR)\opl3midi_test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "opl3midi_test - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\opl3midi_test.exe"


CLEAN :
	-@erase "$(INTDIR)\bitcrush.obj"
	-@erase "$(INTDIR)\dbopl.obj"
	-@erase "$(INTDIR)\emulator.obj"
	-@erase "$(INTDIR)\hardware.obj"
	-@erase "$(INTDIR)\InpOut32Helper.obj"
	-@erase "$(INTDIR)\opl.obj"
	-@erase "$(INTDIR)\opl3.obj"
	-@erase "$(INTDIR)\opl3class.obj"
	-@erase "$(INTDIR)\opl3midi.obj"
	-@erase "$(INTDIR)\opl3midi_test.obj"
	-@erase "$(INTDIR)\opl_hw.obj"
	-@erase "$(INTDIR)\opl_lpt.obj"
	-@erase "$(INTDIR)\resampler.obj"
	-@erase "$(INTDIR)\silence.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vgm_logging.obj"
	-@erase "$(INTDIR)\wav_writer.obj"
	-@erase "$(INTDIR)\ymf262.obj"
	-@erase "$(OUTDIR)\opl3midi_test.exe"
	-@erase "$(OUTDIR)\opl3midi_test.ilk"
	-@erase "$(OUTDIR)\opl3midi_test.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\opl3midi_test.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\opl3midi_test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\opl3midi_test.pdb" /debug /machine:IX86 /out:"$(OUTDIR)\opl3midi_test.exe" /pdbtype:sept /machine:AMD64 
LINK32_OBJS= \
	"$(INTDIR)\bitcrush.obj" \
	"$(INTDIR)\dbopl.obj" \
	"$(INTDIR)\emulator.obj" \
	"$(INTDIR)\hardware.obj" \
	"$(INTDIR)\InpOut32Helper.obj" \
	"$(INTDIR)\opl.obj" \
	"$(INTDIR)\opl3.obj" \
	"$(INTDIR)\opl3class.obj" \
	"$(INTDIR)\opl3midi.obj" \
	"$(INTDIR)\opl3midi_test.obj" \
	"$(INTDIR)\opl_hw.obj" \
	"$(INTDIR)\opl_lpt.obj" \
	"$(INTDIR)\resampler.obj" \
	"$(INTDIR)\silence.obj" \
	"$(INTDIR)\vgm_logging.obj" \
	"$(INTDIR)\wav_writer.obj" \
	"$(INTDIR)\ymf262.obj"

"$(OUTDIR)\opl3midi_test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("opl3midi_test.dep")
!INCLUDE "opl3midi_test.dep"
!ELSE 
!MESSAGE Warning: cannot find "opl3midi_test.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "opl3midi_test - Win32 Release" || "$(CFG)" == "opl3midi_test - Win32 Debug"
SOURCE=..\..\fmopl3lib\bitcrush.cpp

"$(INTDIR)\bitcrush.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\dbopl.cpp

"$(INTDIR)\dbopl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\emulator.cpp

"$(INTDIR)\emulator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\hardware.cpp

"$(INTDIR)\hardware.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\InpOut32Helper.cpp

"$(INTDIR)\InpOut32Helper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\opl.cpp

"$(INTDIR)\opl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\opl3.cpp

"$(INTDIR)\opl3.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\opl3class.cpp

"$(INTDIR)\opl3class.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\synthlib\opl3midi.cpp

"$(INTDIR)\opl3midi.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\opl3midi_test.cpp

"$(INTDIR)\opl3midi_test.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\opl_hw.cpp

"$(INTDIR)\opl_hw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\opl_lpt.cpp

"$(INTDIR)\opl_lpt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\resampler.cpp

"$(INTDIR)\resampler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\silence.cpp

"$(INTDIR)\silence.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\vgm_logging.cpp

"$(INTDIR)\vgm_logging.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\wav_writer.cpp

"$(INTDIR)\wav_writer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\ymf262.cpp

"$(INTDIR)\ymf262.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

