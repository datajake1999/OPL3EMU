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

void filter::SetDither(bool val) {
	Dither = val;
}

const char *filter::GetFilterName(unsigned int filter) {
	if (filter == 0)
	{
		return "lowpass";
	}
	else if (filter == 1)
	{
		return "highpass";
	}
	else if (filter == 2)
	{
		return "bandpass";
	}
	else if (filter == 3)
	{
		return "allpass";
	}
	else if (filter == 4)
	{
		return "notch";
	}
	else if (filter == 5)
	{
		return "peaking";
	}
	else if (filter == 6)
	{
		return "lowshelf";
	}
	else if (filter == 7)
	{
		return "highshelf";
	}
	else
	{
		return "none";
	}
}

unsigned int filter::GetRate() {
	return samplerate;
}

unsigned int filter::GetType() {
	return type;
}

float filter::GetFreq() {
	return freq;
}

float filter::GetRes() {
	return res;
}

float filter::GetGain() {
	return gain;
}

bool filter::GetDither() {
	return Dither;
}

#define PI 3.1415926536

float filter::AWGN_generator()
{/* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */

	float temp1;
	float temp2;
	float result;
	int p;

	p = 1;

	while( p > 0 )
	{
		temp2 = ( rand() / ( (float)RAND_MAX ) ); /*  rand() function generates an
													integer between 0 and  RAND_MAX,
													which is defined in stdlib.h.
												*/

		if ( temp2 == 0 )
		{// temp2 is >= (RAND_MAX / 2)
			p = 1;
		}// end if
		else
		{// temp2 is < (RAND_MAX / 2)
			p = -1;
		}// end else

	}// end while()

	temp1 = cosf( ( 2.0f * (float)PI ) * rand() / ( (float)RAND_MAX ) );
	result = sqrtf( -2.0f * logf( temp2 ) ) * temp1;

	return result;	// return the generated random sample to the caller

}// end AWGN_generator()

void filter::Init(unsigned int rate) {
	samplerate = rate;
	if (freq > rate/2-2)
	{
		freq = rate/2-2;
	}
	if (type == 0)
	{
		sf_lowpass(&bq_state, rate, freq/2, res);
	}
	else if (type == 1)
	{
		sf_highpass(&bq_state, rate, freq/2, res);
	}
	else if (type == 2)
	{
		sf_bandpass(&bq_state, rate, freq/2, res);
	}
	else if (type == 3)
	{
		sf_allpass(&bq_state, rate, freq/2, res);
	}
	else if (type == 4)
	{
		sf_notch(&bq_state, rate, freq/2, res);
	}
	else if (type == 5)
	{
		sf_peaking(&bq_state, rate, freq/2, res, gain);
	}
	else if (type == 6)
	{
		sf_lowshelf(&bq_state, rate, freq/2, res, gain);
	}
	else if (type == 7)
	{
		sf_highshelf(&bq_state, rate, freq/2, res, gain);
	}
	else
	{
		sf_highpass(&bq_state, rate, 0, 0);
	}
}

void filter::Reload() {
	Init(samplerate);
}

void filter::Generate(signed short *buffer, unsigned int len) {
	if (type > 7 && type < 0)
	{
		return;
	}
	sf_sample_st *buf =  new sf_sample_st[len];
	unsigned int i;
	for (i=0; i<len; i++)
	{
		buf[i].L = (float)buffer[0] / 32767.0f;
		buf[i].R = (float)buffer[1] / 32767.0f;
		buffer += 2;
	}
	buffer -= len*2;
	sf_biquad_process(&bq_state, len, buf, buf);
	if (Dither == true)
	{
		float n;
		for (i=0; i<len; i++)
		{
			n = AWGN_generator() / 32767.0f;
			buf[i].L = buf[i].L + n;
			n = AWGN_generator() / 32767.0f;
			buf[i].R = buf[i].R + n;
		}
	}
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

void filter::Generate_float(float *buffer, unsigned int len) {
	if (type > 7 && type < 0)
	{
		return;
	}
	sf_sample_st *buf =  new sf_sample_st[len];
	unsigned int i;
	for (i=0; i<len; i++)
	{
		buf[i].L = buffer[0];
		buf[i].R = buffer[1];
		buffer += 2;
	}
	buffer -= len*2;
	sf_biquad_process(&bq_state, len, buf, buf);
	for (i=0; i<len; i++)
	{
		buffer[0] = buf[i].L;
		buffer[1] = buf[i].R;
		buffer += 2;
	}
	delete[] buf;
}
