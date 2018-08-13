//
// Copyright (C) 2015 Alexey Khokholov (Nuke.YKT)
// Copyright (C) 2018 Datajake
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

char *hqresampler = getenv("HQRESAMPLER");
char *hwsupport = getenv("OPLHWSUPPORT");
char *wavwrite = getenv("WAVWRITE");
char *vgmlog = getenv("VGMLOG");
char *vgmloop = getenv("VGMLOOP");

int opl3class::fm_init(unsigned int rate) {
	if (hqresampler)
	{
		if (strstr(hqresampler, "-on"))
		{
			emul.init(49716);
			memset(samples, 0, sizeof(samples));
			resampler = resampler_create();
			if (!resampler) return 0;
			resampler_set_rate(resampler, 49716.0 / (double)rate);
		}
	}
	else
	{
		emul.init(rate);
	}
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_Hardware_Detection();
			OPL_HW_Init();
		}
		if (strstr(hwsupport, "-lpt"))
		{
			OPL_LPT_Init();
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
	emul.writereg(reg, data);
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_HW_WriteReg(reg, data);
		}
		if (strstr(hwsupport, "-lpt"))
		{
			opl_lpt_write(reg, data);
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

void opl3class::fm_generate_resampled(signed short *buffer, unsigned int len) {
	for (; len--;)
	{
		sample_t ls, rs;
		unsigned int to_write = resampler_get_min_fill(resampler);
		while (to_write)
		{
			emul.generate(samples, 1);
			resampler_write_pair(resampler, samples[0], samples[1]);
			--to_write;
		}
		resampler_read_pair(resampler, &ls, &rs);
		if ((ls + 0x8000) & 0xFFFF0000) ls = (ls >> 31) ^ 0x7FFF;
		if ((rs + 0x8000) & 0xFFFF0000) rs = (rs >> 31) ^ 0x7FFF;
		buffer[0] = (short)ls;
		buffer[1] = (short)rs;
		buffer += 2;
	}
}

void opl3class::fm_generate(signed short *buffer, unsigned int len) {
	if (hqresampler)
	{
		if (strstr(hqresampler, "-on"))
		{
			fm_generate_resampled(buffer, len);
		}
	}
	else
	{
		emul.generate(buffer, len);
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
		if (strstr(hwsupport, "-lpt"))
		{
			OPL_LPT_Close();
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
