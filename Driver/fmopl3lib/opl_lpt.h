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

void opl2lpt_write(unsigned char reg, unsigned char data);
void opl3lpt_write(unsigned int reg, unsigned char data);
void opl_lpt_write(unsigned int reg, unsigned char data);
void opl_lpt_reset(void);
void OPL_LPT_Init();
void OPL_LPT_Close();

#endif /*OPL_LPT_H*/