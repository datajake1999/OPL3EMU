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

char *core;
char *silence;
char *hwsupport;
char *wavwrite;
char *vgmlog;
char *vgmloop;
const Bit64u lat = (50 * 49716) / 1000;


int opl3class::fm_init(unsigned int rate) {
	core = getenv("OPL3CORE");
	silence = getenv("OPLEMUSILENCE");
	hwsupport = getenv("OPLHWSUPPORT");
	wavwrite = getenv("WAVWRITE");
	vgmlog = getenv("VGMLOG");
	vgmloop = getenv("VGMLOOP");
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

	memset(command,0,sizeof(command));
	memset(time, 0, sizeof(time));
	counter = 0;
	lastwrite = 0;
	strpos = 0;
	endpos = 0;

	return 1;
}

void opl3class::fm_writereg(unsigned short reg, unsigned char data) {
	command[endpos % 8192][0] = reg;
	command[endpos % 8192][1] = data;
	Bit64u t1 = lastwrite + 2;
	Bit64u t2 = counter + lat;
	if (t2 > t1)
	{
		t1 = t2;
	}
	time[endpos % 8192] = t1;
	lastwrite = t1;
	endpos = (endpos + 1) % 8192;
}

void opl3class::fm_generate(signed short *buffer, unsigned int len) {
	for (unsigned int i = 0; i < len; i++)
	{
		while (strpos != endpos && time[strpos] < counter)
		{
			if (core)
			{
				if (strstr(core, "-dbcompat"))
				{
					if (silence)
					{
						if (strstr(silence, "-on"))
						{
							adlib_write(0x00, 0x00);
						}
					}
					else
					{
						adlib_write(command[strpos][0], command[strpos][1]);
					}
				}
				if (strstr(core, "-dbfast"))
				{
					if (silence)
					{
						if (strstr(silence, "-on"))
						{
							chip2.WriteReg(0x00, 0x00);
						}
					}
					else
					{
						chip2.WriteReg(command[strpos][0], command[strpos][1]);
					}
				}
				if (strstr(core, "-mame"))
				{
					if (silence)
					{
						if (strstr(silence, "-on"))
						{
							ymf262_write_reg(chip3, 0x00, 0x00);
						}
					}
					else
					{
						ymf262_write_reg(chip3, command[strpos][0], command[strpos][1]);
					}
				}
			}
			else
			{
				if (silence)
				{
					if (strstr(silence, "-on"))
					{
						OPL3_WriteReg(&chip, 0x00, 0x00);
					}
				}
				else
				{
					OPL3_WriteReg(&chip, command[strpos][0], command[strpos][1]);
				}
			}
			if (hwsupport)
			{
				if (strstr(hwsupport, "-on"))
				{
					OPL_HW_WriteReg(command[strpos][0], command[strpos][1]);
				}
			}
			if (vgmlog)
			{
				if (strstr(vgmlog, "-on"))
				{
					VGMLog_CmdWrite((0x5E | (command[strpos][0]>>8)), (BYTE)command[strpos][0], command[strpos][1]);
				}
			}
			strpos = (strpos + 1) % 8192;
		}
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				adlib_getsample((Bit16s*)buffer, 1);
			}
			if (strstr(core, "-dbfast"))
			{
				chip2.Generate(buffer, 1);
			}
			if (strstr(core, "-mame"))
			{
				ymf262_update_one(chip3, buffer, 1);
			}
		}
		else
		{
			OPL3_GenerateStream(&chip, (Bit16s*)buffer, 1);
		}
		if (wavwrite)
		{
			if (strstr(wavwrite, "-on"))
			{
				WavFileWrite(buffer, 1);
			}
		}
		if (vgmlog)
		{
			if (strstr(vgmlog, "-on"))
			{
				VGMLog_IncrementSamples(1);
			}
		}
		buffer += 2;
		counter++;
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
