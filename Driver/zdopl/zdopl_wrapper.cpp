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

void zdopl_wrapper::Init(unsigned int rate) {
	chip = JavaOPLCreate(false);
	chip->Reset();
}

void zdopl_wrapper::WriteReg(unsigned short reg, unsigned char data) {
	chip->WriteReg(reg, data);
}

void zdopl_wrapper::Generate(signed short *buffer, unsigned int len)
{
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
			signed long sample = (signed long)24576 * buf[i];
			sample = (sample > -32768) ? sample : -32768;
			sample = (sample < +32767) ? sample : +32767;
			buffer[i] = (signed short)sample;
		}
		buffer += cursamples;
		len -= curframes;
	}
}
