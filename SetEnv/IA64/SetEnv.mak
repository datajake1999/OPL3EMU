# Microsoft Developer Studio Generated NMAKE File, Based on SetEnv.dsp
!IF "$(CFG)" == ""
CFG=SetEnv - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SetEnv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SetEnv - Win32 Release" && "$(CFG)" != "SetEnv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SetEnv.mak" CFG="SetEnv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SetEnv - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SetEnv - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SetEnv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SetEnv.exe"


CLEAN :
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Regkey.obj"
	-@erase "$(INTDIR)\SetEnv.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SetEnv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SetEnv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SetEnv.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SetEnv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SetEnv.pdb" /machine:IX86 /out:"$(OUTDIR)\SetEnv.exe" /machine:IA64 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Regkey.obj" \
	"$(INTDIR)\SetEnv.res"

"$(OUTDIR)\SetEnv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SetEnv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SetEnv.exe"


CLEAN :
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Regkey.obj"
	-@erase "$(INTDIR)\SetEnv.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SetEnv.exe"
	-@erase "$(OUTDIR)\SetEnv.ilk"
	-@erase "$(OUTDIR)\SetEnv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SetEnv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SetEnv.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SetEnv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\SetEnv.pdb" /debug /machine:IX86 /out:"$(OUTDIR)\SetEnv.exe" /pdbtype:sept /machine:IA64 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Regkey.obj" \
	"$(INTDIR)\SetEnv.res"

"$(OUTDIR)\SetEnv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SetEnv.dep")
!INCLUDE "SetEnv.dep"
!ELSE 
!MESSAGE Warning: cannot find "SetEnv.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SetEnv - Win32 Release" || "$(CFG)" == "SetEnv - Win32 Debug"
SOURCE=..\Main.cpp

"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Regkey.cpp

"$(INTDIR)\Regkey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SetEnv.rc

!IF  "$(CFG)" == "SetEnv - Win32 Release"


"$(INTDIR)\SetEnv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\SetEnv.res" /i "\git\OPL3EMU\SetEnv" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "SetEnv - Win32 Debug"


"$(INTDIR)\SetEnv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\SetEnv.res" /i "\git\OPL3EMU\SetEnv" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

