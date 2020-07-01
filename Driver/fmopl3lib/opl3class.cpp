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

static char *core = getenv("OPL3CORE");
static char *hqresampler = getenv("HQRESAMPLER");
static char *reverb = getenv("REVERB");
static char *preset = getenv("PRESET");
static char *invertrev = getenv("INVERTREV");
static char *monorev = getenv("MONOREV");
static char *onlyrev = getenv("ONLYREV");
static char *filter = getenv("FILTER");
static char *flttype = getenv("FLTTYPE");
static char *fltfreq = getenv("FLTFREQ");
static char *fltres = getenv("FLTRES");
static char *fltgain = getenv("FLTGAIN");
#ifndef DISABLE_DSP_SUPPORT
static char *silence = getenv("OPLEMUSILENCE");
static char *bitcrush = getenv("BITCRUSH");
static char *crushamount = getenv("CRUSHAMOUNT");
static char *dither = getenv("DITHER");
static char *swapstereo = getenv("SWAPSTEREO");
static char *mono = getenv("MONO");
static char *surround = getenv("SURROUND");
static char *limit = getenv("LIMIT");
#endif /*DISABLE_DSP_SUPPORT*/
#ifndef DISABLE_HW_SUPPORT
static char *hwport = getenv("OPL3PORT");
static char *lptport = getenv("LPTPORT");
static char *opl2lptmode = getenv("OPL2LPTMODE");
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
				EAX.SetPreset(atoi(preset));
			}
			if (invertrev)
			{
				if (strstr(invertrev, "-on"))
				{
					EAX.SetInvertReverb(true);
				}
			}
			if (monorev)
			{
				if (strstr(monorev, "-on"))
				{
					EAX.SetMonoReverb(true);
				}
			}
			if (onlyrev)
			{
				if (strstr(onlyrev, "-on"))
				{
					EAX.SetOnlyReverb(true);
				}
			}
#ifdef _DEBUG
			printf("The sample rate is %d.\n", EAX.GetRate());
			printf("The name of the selected preset is %s, and its preset number is %d.\n", EAX.GetPresetName(EAX.GetPreset()), EAX.GetPreset());
			if (EAX.GetInvertReverb() == true)
			{
				printf("The reverb is inverted.\n");
			}
			if (EAX.GetMonoReverb() == true)
			{
				printf("The reverb is mono.\n");
			}
			if (EAX.GetOnlyReverb() == true)
			{
				printf("The output is only the reverb.\n");
			}
			if (EAX.GetDither() == true)
			{
				printf("The reverb is dithered.\n");
			}
#endif
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
#ifdef _DEBUG
			printf("The sample rate is %d.\n", FLT.GetRate());
			printf("The type of filter is %s, and its associated number is %d.\n", FLT.GetFilterName(FLT.GetType()), FLT.GetType());
			printf("The frequency is %f.\n", FLT.GetFreq());
			printf("The resonance is %f.\n", FLT.GetRes());
			printf("The gain is %f.\n", FLT.GetGain());
			if (FLT.GetDither() == true)
			{
				printf("The filtered audio is dithered.\n");
			}
#endif
		}
	}
#ifndef DISABLE_DSP_SUPPORT
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			emul.SetSilent(1);
		}
	}
#ifdef _DEBUG
	if (emul.GetSilent() == 1)
	{
		printf("Silent emulation mode is enabled.\n");
	}
#endif
#endif /*DISABLE_DSP_SUPPORT*/
	if (core)
	{
		if (strstr(core, "-dbcompat"))
		{
			emul.SetCore(1);
		}
		if (strstr(core, "-dbfast"))
		{
			emul.SetCore(2);
		}
		if (strstr(core, "-mame"))
		{
			emul.SetCore(3);
		}
		if (strstr(core, "-java"))
		{
			emul.SetCore(4);
		}
		if (strstr(core, "-opal"))
		{
			emul.SetCore(5);
		}
	}
#ifdef _DEBUG
	if (emul.GetCore() == 1)
	{
		printf("The current OPL3 core is DOSBox compat.\n");
	}
	else if (emul.GetCore() == 2)
	{
		printf("The current OPL3 core is DOSBox fast.\n");
	}
	else if (emul.GetCore() == 3)
	{
		printf("The current OPL3 core is MAME.\n");
	}
	else if (emul.GetCore() == 4)
	{
		printf("The current OPL3 core is Java OPL3.\n");
	}
	else if (emul.GetCore() == 5)
	{
		printf("The current OPL3 core is Opal.\n");
	}
	else
	{
		printf("The current OPL3 core is Nuked.\n");
	}
#endif
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
			if (crushamount)
			{
				SetCrushAmount(&bc, atoi(crushamount));
			}
			else
			{
				SetCrushAmount(&bc, 8);
			}
#ifdef _DEBUG
			printf("The new bit depth is %d.\n", GetCrushAmount(&bc));
#endif
		}
	}
#endif /*DISABLE_DSP_SUPPORT*/
#ifndef DISABLE_HW_SUPPORT
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			if (hwport)
			{
				SetFMPort(strtoul(hwport, 0, 16));
			}
#ifdef _DEBUG
			printf("The FM port is %x.\n", GetFMPort());
#endif
			OPL_Hardware_Detection();
			OPL_HW_Init();
		}
		if (strstr(hwsupport, "-lpt"))
		{
			if (lptport)
			{
				SetLPTPort(strtoul(lptport, 0, 16));
			}
			if (opl2lptmode)
			{
				if (strstr(opl2lptmode, "-on"))
				{
					SetLPTMode(1);		
				}
			}
#ifdef _DEBUG
			printf("The LPT port is %x.\n", GetLPTPort());
			if (GetLPTMode() == 1)
			{
				printf("The LPT driver is in OPL2LPT mode.\n");
			}
#endif
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
					RectangleDither(&bc, buffer, len);
				}
				if (strstr(dither, "-triangle"))
				{
					TriangleDither(&bc, buffer, len);
				}
				if (strstr(dither, "-gaussian"))
				{
					GaussianDither(&bc, buffer, len);
				}
			}
			BitCrush(&bc, buffer, len);
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
