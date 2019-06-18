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

//Bassed on EAXReverb: https://github.com/Relfos/EAXReverb

#include "EAXReverb.h"

void EAXReverb::Init(unsigned int rate) {
	sampleRate = rate;
	//initialize the effect
	effect.Create(rate);
	//update the effect
	effect.Update(rate);
}

void EAXReverb::SetPreset(unsigned int preset) {
	//set a preset
	if (preset == 0)
	{
		//castle
		effect.LoadPreset(26.0f, 8.3f, 0.890f, -1000.0f, -800.0f, -2000.0f, 1.22f, 0.83f, 0.31f, -100.0f, 0.022f, 0.0f, 0.0f, 0.0f, 600.0f, 0.011f, 0.0f, 0.0f, 0.0f, 0.138f, 0.080f, 0.250f, 0.0f, -5.0f, 5168.6f, 139.5f, 0.0f, 0x20);
	}
	else if (preset == 1)
	{
		//stadium
		effect.LoadPreset(26, 7.2f, 1.0f, -1000, -700, -200, 6.26f, 0.51f, 1.10f, -2400, 0.183f, 0.0f, 0.0f, 0.0f, -800, 0.038f, 0.0f, 0.0f, 0.0f, 0.250f, 0.0f, 0.250f, 0.0f, -5.0f, 5000.0f, 250.0f, 0.0f, 0x20);
	}
	else if (preset == 2)
	{
		// heaven
		effect.LoadPreset(26, 19.6f, 0.940f, -1000, -200, -700, 5.04f, 1.12f, 0.56f, -1230, 0.020f, 0.0f, 0.0f, 0.0f, 200, 0.029f, 0.0f, 0.0f, 0.0f, 0.250f, 0.080f, 2.742f, 0.050f, -2.0f, 5000.0f, 250.0f, 0.0f, 0x3f);
	}
	else if (preset == 3)
	{
		//sewer
		effect.LoadPreset(21, 1.7f, 0.800f, -1000, -1000, 0, 2.81f, 0.14f, 1.0f, 429, 0.014f, 0.0f, 0.0f, 0.0f, 1023, 0.021f, 0.0f, 0.0f, 0.0f, 0.250f, 0.0f, 0.250f, 0.0f, -5.0f, 5000.0f, 250.0f, 0.0f, 0x3f);
	}
	else if (preset == 4)
	{
		//psychotic
		effect.LoadPreset(25, 1.0f, 0.500f, -1000, -151, 0, 7.56f, 0.91f, 1.0f, -626, 0.020f, 0.0f, 0.0f, 0.0f, 774, 0.030f, 0.0f, 0.0f, 0.0f, 0.250f, 0.0f, 4.0f, 1.0f, -5.0f, 5000.0f, 250.0f, 0.0f, 0x1f);
	}
	//update the effect
	effect.Update(sampleRate);
}

void EAXReverb::Generate(signed short *buffer, unsigned int len) {
	//check the sample rate, since the effect has issues when working with sample rates below 10000 HZ
	if (sampleRate < 10000)
	{
		return;
	}
	//allocate memory for mono samples
	int16_t *samples = new int16_t[len];
	int i;
	//convert stereo samples into mono
	for (i=0; i<len; i++)
	{
		samples[i] = (buffer[0] + buffer[1]) / 2;
		buffer += 2;
	}
	//rewind the buffer back to the beginning, as it will be used for the final output
	buffer -= len*2;
	//allocate memory for mono samples in floating point
	float *floatSamplesIn =  new float[len];
	//convert mono samples into floating point for use by the reverb effect
	for (i=0; i<len; i++)
	{
		floatSamplesIn[i] = (float)samples[i] / 32767.0f;
	}
	//get rid of the original mono samples, as they are no longer needed
	delete[] samples;
	//set the offset for the audio buffer
	int offset = 0;
	//allocate memory for reverb output samples in floating point
	float floatSamplesOut[REVERB_BUFFERSIZE * OUTPUT_CHANNELS];
	do {
		//set the amount of samples to process at a time
		int workSamples = REVERB_BUFFERSIZE / 4;
		if (workSamples>len)
		{
			workSamples = len;
		}
		//process the effect
		effect.Process(workSamples, &floatSamplesIn[offset],  floatSamplesOut);
		//convert the floating point output to 32 bit integers, check to make sure they don't overflow, and convert them to 16 bit integers to write to the audio buffer
		for (i=0; i<workSamples; i++)
		{
			int32_t outSample = buffer[0] + (int32_t) (floatSamplesOut[i*2 + 0] * 32767.0f);
			if (outSample >= buffer[0] + 32767)
			{
				outSample = buffer[0];
			}
			else if (outSample <= buffer[0] - 32768)
			{
				outSample = buffer[0];
			}
			if (outSample > 32767)
			{
				outSample = 32767;
			}
			else if (outSample < -32768)
			{
				outSample = -32768;
			}
			buffer[0] = (short)outSample;
			outSample = buffer[1] + (int32_t) (floatSamplesOut[i*2 + 1] * 32767.0f);
			if (outSample >= buffer[1] + 32767)
			{
				outSample = buffer[1];
			}
			else if (outSample <= buffer[1] - 32768)
			{
				outSample = buffer[1];
			}
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
		//update the sample counters
		len -= workSamples;
		offset += workSamples;
	} while (len>0);
	//delete the floating point input samples
	delete[] floatSamplesIn;
}

void EAXReverb::Close() {
	//close the effect
	effect.Destroy();
}
