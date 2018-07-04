#include <stdio.h>
#include <windows.h>
#include <math.h>
#ifndef VGM_LOGGING_H
#define VGM_LOGGING_H

#include "VGMFile.h"

void VGMLog_Init(unsigned int rate);
void VGMLog_CmdWrite(BYTE Cmd, BYTE Reg, BYTE Data);
inline void VGMLog_FlushWait();
void VGMLog_IncrementSamples(int len);
void VGMLog_Close();
void VGMLog_MarkLoopStartNow();
DWORD VGMLog_CountSamplesFromOffset(DWORD offset);

#endif //VGM_LOGGING_H