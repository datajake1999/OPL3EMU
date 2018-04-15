# Microsoft Developer Studio Generated NMAKE File, Based on opl3windows.dsp
!IF "$(CFG)" == ""
CFG=opl3windows - Win32 Debug
!MESSAGE No configuration specified. Defaulting to opl3windows - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "opl3windows - Win32 Release" && "$(CFG)" != "opl3windows - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "opl3windows.mak" CFG="opl3windows - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "opl3windows - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "opl3windows - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "opl3windows - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\opl3windows.dll"


CLEAN :
	-@erase "$(INTDIR)\dbopl.obj"
	-@erase "$(INTDIR)\InpOut32Helper.obj"
	-@erase "$(INTDIR)\MidiSynth.obj"
	-@erase "$(INTDIR)\opl.obj"
	-@erase "$(INTDIR)\opl3.obj"
	-@erase "$(INTDIR)\opl3class.obj"
	-@erase "$(INTDIR)\opl3midi.obj"
	-@erase "$(INTDIR)\opl_hw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vgm_logging.obj"
	-@erase "$(INTDIR)\wav_writer.obj"
	-@erase "$(INTDIR)\winmm_drv_windows.obj"
	-@erase "$(INTDIR)\ymf262.obj"
	-@erase "$(OUTDIR)\opl3windows.dll"
	-@erase "$(OUTDIR)\opl3windows.exp"
	-@erase "$(OUTDIR)\opl3windows.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPL3WINDOWS_EXPORTS" /Fp"$(INTDIR)\opl3windows.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\opl3windows.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\opl3windows.pdb" /machine:IX86 /def:"..\..\src\winmm_drv.def" /out:"$(OUTDIR)\opl3windows.dll" /implib:"$(OUTDIR)\opl3windows.lib" /machine:AMD64 
DEF_FILE= \
	"..\..\src\winmm_drv.def"
LINK32_OBJS= \
	"$(INTDIR)\dbopl.obj" \
	"$(INTDIR)\InpOut32Helper.obj" \
	"$(INTDIR)\MidiSynth.obj" \
	"$(INTDIR)\opl.obj" \
	"$(INTDIR)\opl3.obj" \
	"$(INTDIR)\opl3class.obj" \
	"$(INTDIR)\opl3midi.obj" \
	"$(INTDIR)\opl_hw.obj" \
	"$(INTDIR)\vgm_logging.obj" \
	"$(INTDIR)\wav_writer.obj" \
	"$(INTDIR)\winmm_drv_windows.obj" \
	"$(INTDIR)\ymf262.obj"

"$(OUTDIR)\opl3windows.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "opl3windows - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\opl3windows.dll"


CLEAN :
	-@erase "$(INTDIR)\dbopl.obj"
	-@erase "$(INTDIR)\InpOut32Helper.obj"
	-@erase "$(INTDIR)\MidiSynth.obj"
	-@erase "$(INTDIR)\opl.obj"
	-@erase "$(INTDIR)\opl3.obj"
	-@erase "$(INTDIR)\opl3class.obj"
	-@erase "$(INTDIR)\opl3midi.obj"
	-@erase "$(INTDIR)\opl_hw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vgm_logging.obj"
	-@erase "$(INTDIR)\wav_writer.obj"
	-@erase "$(INTDIR)\winmm_drv_windows.obj"
	-@erase "$(INTDIR)\ymf262.obj"
	-@erase "$(OUTDIR)\opl3windows.dll"
	-@erase "$(OUTDIR)\opl3windows.exp"
	-@erase "$(OUTDIR)\opl3windows.ilk"
	-@erase "$(OUTDIR)\opl3windows.lib"
	-@erase "$(OUTDIR)\opl3windows.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPL3WINDOWS_EXPORTS" /Fp"$(INTDIR)\opl3windows.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\opl3windows.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\opl3windows.pdb" /debug /machine:IX86 /def:"..\..\src\winmm_drv.def" /out:"$(OUTDIR)\opl3windows.dll" /implib:"$(OUTDIR)\opl3windows.lib" /pdbtype:sept /machine:AMD64 
DEF_FILE= \
	"..\..\src\winmm_drv.def"
LINK32_OBJS= \
	"$(INTDIR)\dbopl.obj" \
	"$(INTDIR)\InpOut32Helper.obj" \
	"$(INTDIR)\MidiSynth.obj" \
	"$(INTDIR)\opl.obj" \
	"$(INTDIR)\opl3.obj" \
	"$(INTDIR)\opl3class.obj" \
	"$(INTDIR)\opl3midi.obj" \
	"$(INTDIR)\opl_hw.obj" \
	"$(INTDIR)\vgm_logging.obj" \
	"$(INTDIR)\wav_writer.obj" \
	"$(INTDIR)\winmm_drv_windows.obj" \
	"$(INTDIR)\ymf262.obj"

"$(OUTDIR)\opl3windows.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("opl3windows.dep")
!INCLUDE "opl3windows.dep"
!ELSE 
!MESSAGE Warning: cannot find "opl3windows.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "opl3windows - Win32 Release" || "$(CFG)" == "opl3windows - Win32 Debug"
SOURCE=..\..\fmopl3lib\dbopl.cpp

"$(INTDIR)\dbopl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\InpOut32Helper.cpp

"$(INTDIR)\InpOut32Helper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\MidiSynth.cpp

"$(INTDIR)\MidiSynth.obj" : $(SOURCE) "$(INTDIR)"
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


SOURCE=..\..\fmopl3lib\opl_hw.cpp

"$(INTDIR)\opl_hw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\vgm_logging.cpp

"$(INTDIR)\vgm_logging.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\wav_writer.cpp

"$(INTDIR)\wav_writer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\winmm_drv_windows.cpp

"$(INTDIR)\winmm_drv_windows.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\fmopl3lib\ymf262.cpp

"$(INTDIR)\ymf262.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

