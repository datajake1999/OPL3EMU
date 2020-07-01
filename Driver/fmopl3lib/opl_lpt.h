/*
* Header for OPL3LPT support
* (C) 2018 Datajake
* (C) 2013-2014 James Alan Nguyen
* Original code adapted from MidiPlay/VGMPlay (C) 201X ValleyBell
* 
* Released under LGPL
*/

#ifndef OPL_LPT_H
#define OPL_LPT_H

#include "InpOut32Helper.h"

void opl2lpt_write(WORD reg, BYTE data);
void opl3lpt_write(WORD reg, BYTE data);
void opl_lpt_write(WORD reg, BYTE data);
void opl_lpt_reset(void);
void SetLPTPort(UINT32 port);
UINT32 GetLPTPort();
void SetLPTMode(UINT32 mode);
UINT32 GetLPTMode();
void OPL_LPT_Init();
void OPL_LPT_Close();

#endif /*OPL_LPT_H*/