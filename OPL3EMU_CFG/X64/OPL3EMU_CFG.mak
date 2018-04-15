# Microsoft Developer Studio Generated NMAKE File, Based on OPL3EMU_CFG.dsp
!IF "$(CFG)" == ""
CFG=OPL3EMU_CFG - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OPL3EMU_CFG - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OPL3EMU_CFG - Win32 Release" && "$(CFG)" != "OPL3EMU_CFG - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OPL3EMU_CFG.mak" CFG="OPL3EMU_CFG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OPL3EMU_CFG - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "OPL3EMU_CFG - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "OPL3EMU_CFG - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\OPL3EMU_CFG.exe"


CLEAN :
	-@erase "$(INTDIR)\OPL3EMU_CFG.obj"
	-@erase "$(INTDIR)\OPL3EMU_CFG.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OPL3EMU_CFG.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\OPL3EMU_CFG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPL3EMU_CFG.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPL3EMU_CFG.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\OPL3EMU_CFG.pdb" /machine:IX86 /out:"$(OUTDIR)\OPL3EMU_CFG.exe" /machine:AMD64 
LINK32_OBJS= \
	"$(INTDIR)\OPL3EMU_CFG.obj" \
	"$(INTDIR)\OPL3EMU_CFG.res"

"$(OUTDIR)\OPL3EMU_CFG.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OPL3EMU_CFG - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\OPL3EMU_CFG.exe"


CLEAN :
	-@erase "$(INTDIR)\OPL3EMU_CFG.obj"
	-@erase "$(INTDIR)\OPL3EMU_CFG.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OPL3EMU_CFG.exe"
	-@erase "$(OUTDIR)\OPL3EMU_CFG.ilk"
	-@erase "$(OUTDIR)\OPL3EMU_CFG.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\OPL3EMU_CFG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPL3EMU_CFG.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPL3EMU_CFG.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib bufferoverflowU.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\OPL3EMU_CFG.pdb" /debug /machine:IX86 /out:"$(OUTDIR)\OPL3EMU_CFG.exe" /pdbtype:sept /machine:AMD64 
LINK32_OBJS= \
	"$(INTDIR)\OPL3EMU_CFG.obj" \
	"$(INTDIR)\OPL3EMU_CFG.res"

"$(OUTDIR)\OPL3EMU_CFG.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OPL3EMU_CFG.dep")
!INCLUDE "OPL3EMU_CFG.dep"
!ELSE 
!MESSAGE Warning: cannot find "OPL3EMU_CFG.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OPL3EMU_CFG - Win32 Release" || "$(CFG)" == "OPL3EMU_CFG - Win32 Debug"
SOURCE=..\OPL3EMU_CFG.c

"$(INTDIR)\OPL3EMU_CFG.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\OPL3EMU_CFG.rc

!IF  "$(CFG)" == "OPL3EMU_CFG - Win32 Release"


"$(INTDIR)\OPL3EMU_CFG.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\OPL3EMU_CFG.res" /i "\opl3emu\OPL3EMU_CFG" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "OPL3EMU_CFG - Win32 Debug"


"$(INTDIR)\OPL3EMU_CFG.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\OPL3EMU_CFG.res" /i "\opl3emu\OPL3EMU_CFG" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

