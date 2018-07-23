//
// Copyright (C) 2015 Alexey Khokholov (Nuke.YKT)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#include <string.h>
#include "opl3class.h"

char *core = getenv("OPL3CORE");
char *silence = getenv("OPLEMUSILENCE");
char *hwsupport = getenv("OPLHWSUPPORT");
char *wavwrite = getenv("WAVWRITE");
char *vgmlog = getenv("VGMLOG");
char *vgmloop = getenv("VGMLOOP");

static void SilentInit(unsigned int rate)
{
}

static void SilentWrite(unsigned short reg, unsigned char data)
{
}

static void GenerateSilence(signed short *buffer, unsigned int len)
{
	for(unsigned int i = 0; i < len; i++)
	{
		buffer[0] = 0;
		buffer[1] = 0;
		buffer += 2;
	}
}

int opl3class::fm_init(unsigned int rate) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			SilentInit(rate);
		}
	}
	else
	{
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				adlib_init(rate);
			}
			if (strstr(core, "-dbfast"))
			{
				chip2.Init(rate);
				chip2.WriteReg(0x105, 0x01);
			}
			if (strstr(core, "-mame"))
			{
				chip3 = ymf262_init(49716*288, rate);
			}
		}
		else
		{
			OPL3_Reset(&chip, rate);
		}
	}
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_Hardware_Detection();
			OPL_HW_Init();
		}
	}
	if (wavwrite)
	{
		if (strstr(wavwrite, "-on"))
		{
			WavFileOpen(rate);
		}
	}
	if (vgmlog)
	{
		if (strstr(vgmlog, "-on"))
		{
			VGMLog_Init(rate);
			if (vgmloop)
			{
				if (strstr(vgmloop, "-on"))
				{
					VGMLog_MarkLoopStartNow();
				}
			}
		}
	}

	return 1;
}

void opl3class::fm_writereg(unsigned short reg, unsigned char data) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			SilentWrite(reg, data);
		}
	}
	else
	{
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				adlib_write(reg, data);
			}
			if (strstr(core, "-dbfast"))
			{
				chip2.WriteReg(reg, data);
			}
			if (strstr(core, "-mame"))
			{
				ymf262_write_reg(chip3, reg, data);
			}
		}
		else
		{
			OPL3_WriteRegBuffered(&chip, reg, data);
		}
	}
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_HW_WriteReg(reg, data);
		}
	}
	if (vgmlog)
	{
		if (strstr(vgmlog, "-on"))
		{
			VGMLog_CmdWrite((0x5E | (reg>>8)), (BYTE)reg, data);
		}
	}
}

void opl3class::fm_generate(signed short *buffer, unsigned int len) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			GenerateSilence(buffer, len);
		}
	}
	else
	{
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				adlib_getsample(buffer, len);
			}
			if (strstr(core, "-dbfast"))
			{
				chip2.Generate(buffer, len);
			}
			if (strstr(core, "-mame"))
			{
				ymf262_update_one(chip3, buffer, len);
			}
		}
		else
		{
			OPL3_GenerateStream(&chip, buffer, len);
		}
	}
	if (wavwrite)
	{
		if (strstr(wavwrite, "-on"))
		{
			WavFileWrite(buffer, len);
		}
	}
	if (vgmlog)
	{
		if (strstr(vgmlog, "-on"))
		{
			VGMLog_IncrementSamples(len);
		}
	}
}

void opl3class::fm_close() {
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_HW_Close();
		}
	}
	if (wavwrite)
	{
		if (strstr(wavwrite, "-on"))
		{
			WavFileClose();
		}
	}
	if (vgmlog)
	{
		if (strstr(vgmlog, "-on"))
		{
			VGMLog_Close();
		}
	}
}

fm_chip *getchip() {
	opl3class *chip = new opl3class;
	return chip;
}
