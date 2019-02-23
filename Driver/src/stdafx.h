// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma comment (lib, "winmm.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <mmsystem.h>
#include <mmddk.h>
#include <mmreg.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include "../interface.h"
#include "MidiSynth.h"
