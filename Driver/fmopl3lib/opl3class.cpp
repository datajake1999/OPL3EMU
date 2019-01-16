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

#include <stdlib.h>
#include <string.h>
#include "opl3class.h"

static char *hqresampler = getenv("HQRESAMPLER");
static char *bitcrush = getenv("BITCRUSH");
static char *dither = getenv("DITHER");
static char *swapstereo = getenv("SWAPSTEREO");
static char *mono = getenv("MONO");
static char *surround = getenv("SURROUND");
static char *limit = getenv("LIMIT");
static char *wavwrite = getenv("WAVWRITE");
static char *vgmlog = getenv("VGMLOG");
static char *vgmloop = getenv("VGMLOOP");

int opl3class::fm_init(unsigned int rate) {
	if (hqresampler)
	{
		if (strstr(hqresampler, "-on"))
		{
			emul.Init(49716);
#ifdef _DEBUG
			rawsamples = fopen("C:\\OPLSynth\\rawsamples.pcm", "ab");
#endif
			resampler = resampler_create();
			resampler_set_rate(resampler, 49716.0 / (double)rate);
		}
	}
	else
	{
		emul.Init(rate);
	}
	if (bitcrush)
	{
		if (strstr(bitcrush, "-on"))
		{
			SetCrushAmountEnv();
		}
	}
	hardware_Init();
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
	emul.WriteReg(reg, data);
	hardware_WriteReg(reg, data);
	if (vgmlog)
	{
		if (strstr(vgmlog, "-on"))
		{
			VGMLog_CmdWrite((0x5E | (reg>>8)), (BYTE)reg, data);
		}
	}
}

void opl3class::fm_generate_resampled(signed short *buffer, unsigned int len) {
	for(unsigned int i = 0; i < len; i++)
	{
		sample_t ls, rs;
		for(unsigned int j = 0; j = resampler_get_min_fill(resampler); j++)
		{
			signed short samples[2];
			emul.Generate(samples, 1);
#ifdef _DEBUG
			fwrite(samples, 4, 1, rawsamples);
#endif
			resampler_write_pair(resampler, samples[0], samples[1]);
		}
		resampler_peek_pair(resampler, &ls, &rs);
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
		emul.Generate(buffer, len);
	}
	if (bitcrush)
	{
		if (strstr(bitcrush, "-on"))
		{
			if (dither)
			{
				if (strstr(dither, "-rectangle"))
				{
					RectangleDither(buffer, len);
				}
				if (strstr(dither, "-triangle"))
				{
					TriangleDither(buffer, len);
				}
				if (strstr(dither, "-gaussian"))
				{
					GaussianDither(buffer, len);
				}
			}
			BitCrush(buffer, len);
		}
	}
	if (swapstereo)
	{
		if (strstr(swapstereo, "-on"))
		{
			SwapStereo(buffer, len);
		}
	}
	if (mono)
	{
		if (strstr(mono, "-on"))
		{
			MonoMixdown(buffer, len);
		}
	}
	if (surround)
	{
		if (strstr(surround, "-left"))
		{
			SurroundSoundLeft(buffer, len);
		}
		if (strstr(surround, "-right"))
		{
			SurroundSoundRight(buffer, len);
		}
	}
	if (limit)
	{
		LimitOutput(atoi(limit), buffer, len);
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
	if (hqresampler)
	{
		if (strstr(hqresampler, "-on"))
		{
#ifdef _DEBUG
			fclose(rawsamples);
#endif
			resampler_clear(resampler);
			resampler_destroy(resampler);
		}
	}
	hardware_Close();
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
