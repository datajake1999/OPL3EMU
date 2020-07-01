/*
* OPL3LPT support functions
* (C) 2018 Datajake
* (C) 2013-2014 James Alan Nguyen
* Original code adapted from MidiPlay/VGMPlay (C) 201X ValleyBell
* 
* Released under LGPL
*/

#include "opl_lpt.h"

#ifndef DISABLE_HW_SUPPORT
static UINT32 lpt_base = 0x378;
static UINT32 lpt_mode = 0;
#endif /*DISABLE_HW_SUPPORT*/

void opl2lpt_write(WORD reg, BYTE data) {
#ifndef DISABLE_HW_SUPPORT
	UINT32 i;
	UINT32 lpt_data;
	UINT32 lpt_ctrl;
	if (!lpt_base) {
		return;
	}
	lpt_data = lpt_base;
	lpt_ctrl = lpt_base + 2;

	/* Select OPL2 register */
	outportb(lpt_data, reg);
	outportb(lpt_ctrl, 13);
	outportb(lpt_ctrl, 9);
	outportb(lpt_ctrl, 13);

	/* Wait at least 3.3 microseconds */
	for (i = 0; i < 6; i++) {
		inportb(lpt_ctrl);
	}

	/* Set value */
	outportb(lpt_data, data);
	outportb(lpt_ctrl, 12);
	outportb(lpt_ctrl, 8);
	outportb(lpt_ctrl, 12);

	/* Wait at least 23 microseconds */
	for (i = 0; i < 35; i++) {
		inportb(lpt_ctrl);
	}
#endif /*DISABLE_HW_SUPPORT*/
}

void opl3lpt_write(WORD reg, BYTE data) {
#ifndef DISABLE_HW_SUPPORT
	UINT32 i;
	UINT32 lpt_data;
	UINT32 lpt_ctrl;
	if (!lpt_base) {
		return;
	}
	lpt_data = lpt_base;
	lpt_ctrl = lpt_base + 2;

	/* Select OPL3 register */
	outportb(lpt_data, reg & 0xFF);
	if (reg < 0x100) {
		outportb(lpt_ctrl, 13);
		outportb(lpt_ctrl, 9);
		outportb(lpt_ctrl, 13);
	} else {
		outportb(lpt_ctrl, 5);
		outportb(lpt_ctrl, 1);
		outportb(lpt_ctrl, 5);
	}

	/* Wait at least 3.3 microseconds */
	for (i = 0; i < 6; i++) {
		inportb(lpt_ctrl);
	}

	/* Set value */
	outportb(lpt_data, data);
	outportb(lpt_ctrl, 12);
	outportb(lpt_ctrl, 8);
	outportb(lpt_ctrl, 12);

	/* 3.3 microseconds is sufficient here as well for OPL3 */
	for (i = 0; i < 6; i++) {
		inportb(lpt_ctrl);
	}
#endif /*DISABLE_HW_SUPPORT*/
}

void opl_lpt_write(WORD reg, BYTE data) {
#ifndef DISABLE_HW_SUPPORT
	if (lpt_mode == 1)
	{
		opl2lpt_write(reg, data);
	}
	else
	{
		opl3lpt_write(reg, data);
	}
#endif /*DISABLE_HW_SUPPORT*/
}

void opl_lpt_reset(void)
{
#ifndef DISABLE_HW_SUPPORT
	UINT16 Reg;
	//float FnlVolBak;
	
	//FnlVolBak = FinalVol;
	//FinalVol = 1.0f;
	//memset(OPLRegForce, 0x01, 0x200);
	
	opl_lpt_write(0x105, 0x01);	// OPL3 Enable
	opl_lpt_write(0x001, 0x20);	// Test Register
	opl_lpt_write(0x002, 0x00);	// Timer 1
	opl_lpt_write(0x003, 0x00);	// Timer 2
	opl_lpt_write(0x004, 0x00);	// IRQ Mask Clear
	opl_lpt_write(0x104, 0x00);	// 4-Op-Mode Disable
	opl_lpt_write(0x008, 0x00);	// Keyboard Split
	
	// make sure all internal calulations finish sound generation
	for (Reg = 0x00; Reg < 0x09; Reg ++)
	{
		opl_lpt_write(0x0C0 | Reg, 0x00);	// silence all notes (OPL3)
		opl_lpt_write(0x1C0 | Reg, 0x00);
	}
	for (Reg = 0x00; Reg < 0x16; Reg ++)
	{
		if ((Reg & 0x07) >= 0x06)
		continue;
		opl_lpt_write(0x040 | Reg, 0x3F);	// silence all notes (OPL2)
		opl_lpt_write(0x140 | Reg, 0x3F);
		
		opl_lpt_write(0x080 | Reg, 0xFF);	// set Sustain/Release Rate to FASTEST
		opl_lpt_write(0x180 | Reg, 0xFF);
		opl_lpt_write(0x060 | Reg, 0xFF);
		opl_lpt_write(0x160 | Reg, 0xFF);
		
		opl_lpt_write(0x020 | Reg, 0x00);	// NULL the rest
		opl_lpt_write(0x120 | Reg, 0x00);
		
		opl_lpt_write(0x0E0 | Reg, 0x00);
		opl_lpt_write(0x1E0 | Reg, 0x00);
	}
	opl_lpt_write(0x0BD, 0x00);	// Rhythm Mode
	for (Reg = 0x00; Reg < 0x09; Reg ++)
	{
		opl_lpt_write(0x0B0 | Reg, 0x00);	// turn all notes off (-> Release Phase)
		opl_lpt_write(0x1B0 | Reg, 0x00);
		opl_lpt_write(0x0A0 | Reg, 0x00);
		opl_lpt_write(0x1A0 | Reg, 0x00);
	}
	
	// although this would be a more proper reset, it sometimes produces clicks
	/*for (Reg = 0x020; Reg <= 0x0FF; Reg ++)
		opl_lpt_write(Reg, 0x00);
	for (Reg = 0x120; Reg <= 0x1FF; Reg ++)
		opl_lpt_write(Reg, 0x00);*/
	
	// Now do a proper reset of all other registers.
	for (Reg = 0x040; Reg < 0x0A0; Reg ++)
	{
		if ((Reg & 0x07) >= 0x06 || (Reg & 0x1F) >= 0x18)
		continue;
		opl_lpt_write(0x000 | Reg, 0x00);
		opl_lpt_write(0x100 | Reg, 0x00);
	}
	for (Reg = 0x00; Reg < 0x09; Reg ++)
	{
		opl_lpt_write(0x0C0 | Reg, 0x30);	// must be 30 to make OPL2 VGMs sound on OPL3
		opl_lpt_write(0x1C0 | Reg, 0x30);	// if they don't send the C0 reg
	}
	
	//memset(OPLRegForce, 0x01, 0x200);
	//FinalVol = FnlVolBak;
	
	return;
#endif /*DISABLE_HW_SUPPORT*/
}

void SetLPTPort(UINT32 port) 
{
#ifndef DISABLE_HW_SUPPORT
	lpt_base = port;
#endif /*DISABLE_HW_SUPPORT*/
};

UINT32 GetLPTPort() 
{
#ifndef DISABLE_HW_SUPPORT
	return lpt_base;
#else
	return 0;
#endif /*DISABLE_HW_SUPPORT*/
};

void SetLPTMode(UINT32 mode) 
{
#ifndef DISABLE_HW_SUPPORT
	lpt_mode = mode;
#endif /*DISABLE_HW_SUPPORT*/
};

UINT32 GetLPTMode() 
{
#ifndef DISABLE_HW_SUPPORT
	return lpt_mode;
#else
	return 0;
#endif /*DISABLE_HW_SUPPORT*/
};

void OPL_LPT_Init() 
{
#ifndef DISABLE_HW_SUPPORT
	OpenInpOut32(); 
	opl_lpt_reset();
#endif /*DISABLE_HW_SUPPORT*/
};

void OPL_LPT_Close()
{
#ifndef DISABLE_HW_SUPPORT
	opl_lpt_reset();
	CloseInpOut32(); 
#endif /*DISABLE_HW_SUPPORT*/
};

