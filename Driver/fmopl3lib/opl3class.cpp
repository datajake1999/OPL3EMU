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
static char *reverb = getenv("REVERB");
static char *preset = getenv("PRESET");
static char *invertrev = getenv("INVERTREV");
static char *onlyrev = getenv("ONLYREV");
static char *filter = getenv("FILTER");
static char *flttype = getenv("FLTTYPE");
static char *fltfreq = getenv("FLTFREQ");
static char *fltres = getenv("FLTRES");
static char *fltgain = getenv("FLTGAIN");
#ifndef DISABLE_DSP_SUPPORT
static char *bitcrush = getenv("BITCRUSH");
static char *dither = getenv("DITHER");
static char *swapstereo = getenv("SWAPSTEREO");
static char *mono = getenv("MONO");
static char *surround = getenv("SURROUND");
static char *limit = getenv("LIMIT");
#endif /*DISABLE_DSP_SUPPORT*/
#ifndef DISABLE_HW_SUPPORT
static char *hwsupport = getenv("OPLHWSUPPORT");
#endif /*DISABLE_HW_SUPPORT*/
#ifndef DISABLE_IO_SUPPORT
static char *wavwrite = getenv("WAVWRITE");
static char *vgmlog = getenv("VGMLOG");
static char *vgmloop = getenv("VGMLOOP");
#endif /*DISABLE_IO_SUPPORT*/

int opl3class::fm_init(unsigned int rate) {
	if (reverb)
	{
		if (strstr(reverb, "-on"))
		{
			EAX.Init(rate);
			if (preset)
			{
				if (strstr(preset, "-castle"))
				{
					EAX.SetPreset(26);
				}
				if (strstr(preset, "-stadium"))
				{
					EAX.SetPreset(70);
				}
				if (strstr(preset, "-heaven"))
				{
					EAX.SetPreset(93);
				}
				if (strstr(preset, "-sewer"))
				{
					EAX.SetPreset(21);
				}
				if (strstr(preset, "-psychotic"))
				{
					EAX.SetPreset(25);
				}
			}
			if (invertrev)
			{
				if (strstr(invertrev, "-on"))
				{
					EAX.InvertReverb(true);
				}
			}
			if (onlyrev)
			{
				if (strstr(onlyrev, "-on"))
				{
					EAX.OnlyReverb(true);
				}
			}
		}
	}
	if (flttype)
	{
		if (strstr(flttype, "-lowpass"))
		{
			FLT.SetType(0);
		}
		if (strstr(flttype, "-highpass"))
		{
			FLT.SetType(1);
		}
		if (strstr(flttype, "-bandpass"))
		{
			FLT.SetType(2);
		}
		if (strstr(flttype, "-allpass"))
		{
			FLT.SetType(3);
		}
		if (strstr(flttype, "-notch"))
		{
			FLT.SetType(4);
		}
		if (strstr(flttype, "-peaking"))
		{
			FLT.SetType(5);
		}
		if (strstr(flttype, "-lowshelf"))
		{
			FLT.SetType(6);
		}
		if (strstr(flttype, "-highshelf"))
		{
			FLT.SetType(7);
		}
	}
	if (fltfreq)
	{
		FLT.SetFreq(atof(fltfreq));
	}
	if (fltres)
	{
		FLT.SetRes(atof(fltres));
	}
	if (fltgain)
	{
		FLT.SetGain(atof(fltgain));
	}
	if (filter)
	{
		if (strstr(filter, "-on"))
		{
			FLT.Init(rate);
		}
	}
	if (hqresampler)
	{
		if (strstr(hqresampler, "-on"))
		{
			emul.Init(49716);
#ifdef _DEBUG
#ifdef _WIN32
			rawsamples = fopen("C:\\OPLSynth\\rawsamples.pcm", "ab");
#else
			rawsamples = fopen("rawsamples.pcm", "ab");
#endif
#endif
			resampler = resampler_create();
			resampler_set_rate(resampler, 49716.0 / (double)rate);
			goto InitUtils;
		}
	}
	emul.Init(rate);
InitUtils:
#ifndef DISABLE_DSP_SUPPORT
	if (bitcrush)
	{
		if (strstr(bitcrush, "-on"))
		{
			SetCrushAmountEnv();
		}
	}
#endif /*DISABLE_DSP_SUPPORT*/
#ifndef DISABLE_HW_SUPPORT
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
#endif /*DISABLE_HW_SUPPORT*/
#ifndef DISABLE_IO_SUPPORT
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
#endif /*DISABLE_IO_SUPPORT*/

	return 1;
}

void opl3class::fm_writereg(unsigned short reg, unsigned char data) {
	emul.WriteReg(reg, data);
#ifndef DISABLE_HW_SUPPORT
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
#endif /*DISABLE_HW_SUPPORT*/
#ifndef DISABLE_IO_SUPPORT
	if (vgmlog)
	{
		if (strstr(vgmlog, "-on"))
		{
			VGMLog_CmdWrite((0x5E | (reg>>8)), (BYTE)reg, data);
		}
	}
#endif /*DISABLE_IO_SUPPORT*/
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
			goto GenerateUtils;
		}
	}
	emul.Generate(buffer, len);
GenerateUtils:
	if (reverb)
	{
		if (strstr(reverb, "-on"))
		{
			EAX.Generate(buffer, len);
		}
	}
	if (filter)
	{
		if (strstr(filter, "-on"))
		{
			FLT.Generate(buffer, len);
		}
	}
#ifndef DISABLE_DSP_SUPPORT
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
#endif /*DISABLE_DSP_SUPPORT*/
#ifndef DISABLE_IO_SUPPORT
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
#endif /*DISABLE_IO_SUPPORT*/
	return;
}

void opl3class::fm_close() {
	if (reverb)
	{
		if (strstr(reverb, "-on"))
		{
			EAX.Close();
		}
	}
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
#ifndef DISABLE_HW_SUPPORT
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
#endif /*DISABLE_HW_SUPPORT*/
#ifndef DISABLE_IO_SUPPORT
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
#endif /*DISABLE_IO_SUPPORT*/
}

fm_chip *getchip() {
	opl3class *chip = new opl3class;
	return chip;
}
