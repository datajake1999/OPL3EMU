# Microsoft Developer Studio Generated NMAKE File, Based on MidiPlyr.dsp
!IF "$(CFG)" == ""
CFG=MidiPlyr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MidiPlyr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MidiPlyr - Win32 Release" && "$(CFG)" != "MidiPlyr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MidiPlyr.mak" CFG="MidiPlyr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MidiPlyr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MidiPlyr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MidiPlyr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MidiPlyr.exe"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\MainWND.obj"
	-@erase "$(INTDIR)\MidiPlyr.obj"
	-@erase "$(INTDIR)\MidiPlyr.res"
	-@erase "$(INTDIR)\SEQUENCE.obj"
	-@erase "$(INTDIR)\SMF.obj"
	-@erase "$(INTDIR)\SMFREAD.obj"
	-@erase "$(INTDIR)\TIMEWND.obj"
	-@erase "$(INTDIR)\UIUTILS.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MidiPlyr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\MidiPlyr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MidiPlyr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MidiPlyr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MidiPlyr.pdb" /machine:I386 /out:"$(OUTDIR)\MidiPlyr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\MainWND.obj" \
	"$(INTDIR)\MidiPlyr.obj" \
	"$(INTDIR)\SEQUENCE.obj" \
	"$(INTDIR)\SMF.obj" \
	"$(INTDIR)\SMFREAD.obj" \
	"$(INTDIR)\TIMEWND.obj" \
	"$(INTDIR)\UIUTILS.obj" \
	"$(INTDIR)\MidiPlyr.res"

"$(OUTDIR)\MidiPlyr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MidiPlyr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MidiPlyr.exe"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\MainWND.obj"
	-@erase "$(INTDIR)\MidiPlyr.obj"
	-@erase "$(INTDIR)\MidiPlyr.res"
	-@erase "$(INTDIR)\SEQUENCE.obj"
	-@erase "$(INTDIR)\SMF.obj"
	-@erase "$(INTDIR)\SMFREAD.obj"
	-@erase "$(INTDIR)\TIMEWND.obj"
	-@erase "$(INTDIR)\UIUTILS.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MidiPlyr.exe"
	-@erase "$(OUTDIR)\MidiPlyr.ilk"
	-@erase "$(OUTDIR)\MidiPlyr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\MidiPlyr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MidiPlyr.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MidiPlyr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MidiPlyr.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MidiPlyr.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\MainWND.obj" \
	"$(INTDIR)\MidiPlyr.obj" \
	"$(INTDIR)\SEQUENCE.obj" \
	"$(INTDIR)\SMF.obj" \
	"$(INTDIR)\SMFREAD.obj" \
	"$(INTDIR)\TIMEWND.obj" \
	"$(INTDIR)\UIUTILS.obj" \
	"$(INTDIR)\MidiPlyr.res"

"$(OUTDIR)\MidiPlyr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MidiPlyr.dep")
!INCLUDE "MidiPlyr.dep"
!ELSE 
!MESSAGE Warning: cannot find "MidiPlyr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MidiPlyr - Win32 Release" || "$(CFG)" == "MidiPlyr - Win32 Debug"
SOURCE=.\src\Debug.c

"$(INTDIR)\Debug.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\MainWND.c

"$(INTDIR)\MainWND.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\MidiPlyr.c

"$(INTDIR)\MidiPlyr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\MidiPlyr.Rc

!IF  "$(CFG)" == "MidiPlyr - Win32 Release"


"$(INTDIR)\MidiPlyr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\MidiPlyr.res" /i "src" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "MidiPlyr - Win32 Debug"


"$(INTDIR)\MidiPlyr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\MidiPlyr.res" /i "src" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\src\SEQUENCE.c

"$(INTDIR)\SEQUENCE.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\SMF.c

"$(INTDIR)\SMF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\SMFREAD.c

"$(INTDIR)\SMFREAD.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\TIMEWND.c

"$(INTDIR)\TIMEWND.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UIUTILS.c

"$(INTDIR)\UIUTILS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

