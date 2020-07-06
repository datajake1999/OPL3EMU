//
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
#include "zdopl_wrapper.h"

void zdopl_wrapper::Init(unsigned int rate, bool fullpan) {
	chip = JavaOPLCreate(fullpan);
	chip->Reset();
	rateratio = (rate << RSM_FRAC) / 49716;
	samplecnt = 0;
	oldsamples[0] = 0;
	oldsamples[1] = 0;
	samples[0] = 0;
	samples[1] = 0;
}

void zdopl_wrapper::WriteReg(unsigned short reg, unsigned char data) {
	chip->WriteReg(reg, data);
}

void zdopl_wrapper::SetPanning(int c, float left, float right) {
	chip->SetPanning(c, left, right);
}

void zdopl_wrapper::Generate(signed short *buffer, unsigned int len)
{
	/*
Bassed on code from libADLMIDI found at https://github.com/Wohlstand/libADLMIDI/blob/master/src/chips/java_opl3.cpp
*/
	enum { maxframes = 256 };
	float buf[2 * maxframes];
	while(len > 0)
	{
		memset(buf, 0, sizeof(buf));
		unsigned int curframes = (len < (unsigned int)maxframes) ? len : (unsigned int)maxframes;
		chip->Update(buf, (int)curframes);
		unsigned int cursamples = 2 * curframes;
		for(unsigned int i = 0; i < cursamples; ++i)
		{
			buf[i] = 24576 * buf[i];
			signed long sample = (signed long)buf[i];
			sample = (sample > -32768) ? sample : -32768;
			sample = (sample < +32767) ? sample : +32767;
			buffer[i] = (signed short)sample;
		}
		buffer += cursamples;
		len -= curframes;
	}
}

void zdopl_wrapper::GenerateResampled(signed short *buffer, unsigned int len)
{
	for(unsigned int i = 0; i < len; i++)
	{
		while (samplecnt >= rateratio)
		{
			oldsamples[0] = samples[0];
			oldsamples[1] = samples[1];
			Generate(samples, 1);
			samplecnt -= rateratio;
		}
		buffer[0] = (signed short)((oldsamples[0] * (rateratio - samplecnt)
		+ samples[0] * samplecnt) / rateratio);
		buffer[1] = (signed short)((oldsamples[1] * (rateratio - samplecnt)
		+ samples[1] * samplecnt) / rateratio);
		samplecnt += 1 << RSM_FRAC;
		buffer += 2;
	}
}

void zdopl_wrapper::GenerateStream(signed short *buffer, unsigned int len)
{
	if (rateratio == 1 << RSM_FRAC)
	Generate(buffer, len);
	else
	GenerateResampled(buffer, len);
}
