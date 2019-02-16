/*
* Header for VGM Logging
* (C) 2018 Datajake
* (C) 2013-2014 James Alan Nguyen
* Original code adapted from MidiPlay/VGMPlay (C) 201X ValleyBell
* 
* Released under LGPL
*/

#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <math.h>
#ifndef VGM_LOGGING_H
#define VGM_LOGGING_H

#include "VGMFile.h"

void VGMLog_Init(int samplerate);
void VGMLog_CmdWrite(BYTE Cmd, BYTE Reg, BYTE Data);
void VGMLog_FlushWait();
void VGMLog_IncrementSamples(int len);
void VGMLog_Close();
void VGMLog_MarkLoopStartNow();
DWORD VGMLog_CountSamplesFromOffset(DWORD offset);

#endif //VGM_LOGGING_H