//
// Copyright (C) 2019 Datajake
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

//Bassed on sndfilter: https://github.com/voidqk/sndfilter

#include "filter.h"

static unsigned int type = -1;
static float freq = 0;
static float res = 0;
static float gain = 0;

void filter::SetType(unsigned int val) {
	type = val;
}

void filter::SetFreq(float val) {
	freq = val;
}

void filter::SetRes(float val) {
	res = val;
}

void filter::SetGain(float val) {
	gain = val;
}

void filter::Init(unsigned int rate) {
	if (type == 0)
	{
		sf_lowpass(&bq_state, rate, freq, res);
	}
	else if (type == 1)
	{
		sf_highpass(&bq_state, rate, freq, res);
	}
	else if (type == 2)
	{
		sf_bandpass(&bq_state, rate, freq, res);
	}
	else if (type == 3)
	{
		sf_allpass(&bq_state, rate, freq, res);
	}
	else if (type == 4)
	{
		sf_notch(&bq_state, rate, freq, res);
	}
	else if (type == 5)
	{
		sf_peaking(&bq_state, rate, freq, res, gain);
	}
	else if (type == 6)
	{
		sf_lowshelf(&bq_state, rate, freq, res, gain);
	}
	else if (type == 7)
	{
		sf_highshelf(&bq_state, rate, freq, res, gain);
	}
}

void filter::Generate(signed short *buffer, unsigned int len) {
	if (type > 7 && type < 0)
	{
		return;
	}
	sf_sample_st *buf =  new sf_sample_st[len];
	int i;
	for (i=0; i<len; i++)
	{
		buf[i].L = (float)buffer[0] / 32767.0f;
		buf[i].R = (float)buffer[1] / 32767.0f;
		buffer += 2;
	}
	buffer -= len*2;
	sf_biquad_process(&bq_state, len, buf, buf);
	for (i=0; i<len; i++)
	{
		signed long outSample = (signed long) (buf[i].L * 32767.0f);
		if (outSample > 32767)
		{
			outSample = 32767;
		}
		else if (outSample < -32768)
		{
			outSample = -32768;
		}
		buffer[0] = (short)outSample;
		outSample = (signed long) (buf[i].R * 32767.0f);
		if (outSample > 32767)
		{
			outSample = 32767;
		}
		else if (outSample < -32768)
		{
			outSample = -32768;
		}
		buffer[1] = (short)outSample;
		buffer += 2;
	}
	delete[] buf;
}
