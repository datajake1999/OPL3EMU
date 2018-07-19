# Microsoft Developer Studio Generated NMAKE File, Based on opl3doom.dsp
!IF "$(CFG)" == ""
CFG=opl3doom - Win32 Debug
!MESSAGE No configuration specified. Defaulting to opl3doom - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "opl3doom - Win32 Release" && "$(CFG)" != "opl3doom - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "opl3doom.mak" CFG="opl3doom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "opl3doom - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "opl3doom - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "opl3doom - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\opl3doom.dll"


CLEAN :
	-@erase "$(INTDIR)\c_interface.obj"
	-@erase "$(INTDIR)\dbopl.obj"
	-@erase "$(INTDIR)\i_oplmusic.obj"
	-@erase "$(INTDIR)\InpOut32Helper.obj"
	-@erase "$(INTDIR)\opl.obj"
	-@erase "$(INTDIR)\opl3.obj"
	-@erase "$(INTDIR)\opl3class.obj"
	-@erase "$(INTDIR)\opl_hw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vgm_logging.obj"
	-@erase "$(INTDIR)\wav_writer.obj"
	-@erase "$(INTDIR)\ymf262.obj"
	-@erase "$(OUTDIR)\opl3doom.dll"
	-@erase "$(OUTDIR)\opl3doom.exp"
	-@erase "$(OUTDIR)\opl3doom.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPL3DOOM_EXPORTS" /Fp"$(INTDIR)\opl3doom.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\opl3doom.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\opl3doom.pdb" /machine:I386 /out:"$(OUTDIR)\opl3doom.dll" /implib:"$(OUTDIR)\opl3doom.lib" 
LINK32_OBJS= \
	"$(INTDIR)\c_interface.obj" \
	"$(INTDIR)\dbopl.obj" \
	"$(INTDIR)\i_oplmusic.obj" \
	"$(INTDIR)\InpOut32Helper.obj" \
	"$(INTDIR)\opl.obj" \
	"$(INTDIR)\opl3.obj" \
	"$(INTDIR)\opl3class.obj" \
	"$(INTDIR)\opl_hw.obj" \
	"$(INTDIR)\vgm_logging.obj" \
	"$(INTDIR)\wav_writer.obj" \
	"$(INTDIR)\ymf262.obj"

"$(OUTDIR)\opl3doom.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "opl3doom - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\opl3doom.dll"


CLEAN :
	-@erase "$(INTDIR)\c_interface.obj"
	-@erase "$(INTDIR)\dbopl.obj"
	-@erase "$(INTDIR)\i_oplmusic.obj"
	-@erase "$(INTDIR)\InpOut32Helper.obj"
	-@erase "$(INTDIR)\opl.obj"
	-@erase "$(INTDIR)\opl3.obj"
	-@erase "$(INTDIR)\opl3class.obj"
	-@erase "$(INTDIR)\opl_hw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vgm_logging.obj"
	-@erase "$(INTDIR)\wav_writer.obj"
	-@erase "$(INTDIR)\ymf262.obj"
	-@erase "$(OUTDIR)\opl3doom.dll"
	-@erase "$(OUTDIR)\opl3doom.exp"
	-@erase "$(OUTDIR)\opl3doom.ilk"
	-@erase "$(OUTDIR)\opl3doom.lib"
	-@erase "$(OUTDIR)\opl3doom.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPL3DOOM_EXPORTS" /Fp"$(INTDIR)\opl3doom.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\opl3doom.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\opl3doom.pdb" /debug /machine:I386 /out:"$(OUTDIR)\opl3doom.dll" /implib:"$(OUTDIR)\opl3doom.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\c_interface.obj" \
	"$(INTDIR)\dbopl.obj" \
	"$(INTDIR)\i_oplmusic.obj" \
	"$(INTDIR)\InpOut32Helper.obj" \
	"$(INTDIR)\opl.obj" \
	"$(INTDIR)\opl3.obj" \
	"$(INTDIR)\opl3class.obj" \
	"$(INTDIR)\opl_hw.obj" \
	"$(INTDIR)\vgm_logging.obj" \
	"$(INTDIR)\wav_writer.obj" \
	"$(INTDIR)\ymf262.obj"

"$(OUTDIR)\opl3doom.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("opl3doom.dep")
!INCLUDE "opl3doom.dep"
!ELSE 
!MESSAGE Warning: cannot find "opl3doom.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "opl3doom - Win32 Release" || "$(CFG)" == "opl3doom - Win32 Debug"
SOURCE=..\c_interface\c_interface.cpp

"$(INTDIR)\c_interface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\dbopl.cpp

"$(INTDIR)\dbopl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\synthlib\i_oplmusic.cpp

"$(INTDIR)\i_oplmusic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\InpOut32Helper.cpp

"$(INTDIR)\InpOut32Helper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\opl.cpp

"$(INTDIR)\opl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\opl3.cpp

"$(INTDIR)\opl3.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\opl3class.cpp

"$(INTDIR)\opl3class.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\opl_hw.cpp

"$(INTDIR)\opl_hw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\vgm_logging.cpp

"$(INTDIR)\vgm_logging.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\wav_writer.cpp

"$(INTDIR)\wav_writer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\fmopl3lib\ymf262.cpp

"$(INTDIR)\ymf262.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 
