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

#include <stdlib.h>
#include <string.h>
#include "emulator.h"

char *core = getenv("OPL3CORE");
char *silence = getenv("OPLEMUSILENCE");
char *mono = getenv("OPLEMUMONO");
char *bitcrush = getenv("OPLEMUBITCRUSH");

void emulator::init(unsigned int rate) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			return;
		}
	}
	else
	{
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				chip2.adlib_init(rate, 2, 2);
			}
			if (strstr(core, "-dbfast"))
			{
				chip3.Init(rate);
				chip3.WriteReg(0x105, 0x01);
			}
			if (strstr(core, "-mame"))
			{
				chip4 = ymf262_init(49716*288, rate);
			}
		}
		else
		{
			OPL3_Reset(&chip, rate);
		}
	}
}

void emulator::writereg(unsigned short reg, unsigned char data) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			return;
		}
	}
	else
	{
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				chip2.adlib_write(reg, data);
			}
			if (strstr(core, "-dbfast"))
			{
				chip3.WriteReg(reg, data);
			}
			if (strstr(core, "-mame"))
			{
				ymf262_write_reg(chip4, reg, data);
			}
		}
		else
		{
			OPL3_WriteRegBuffered(&chip, reg, data);
		}
	}
}

void emulator::generate(signed short *buffer, unsigned int len) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			GenerateSilence(buffer, len);
		}
	}
	else
	{
		if (core)
		{
			if (strstr(core, "-dbcompat"))
			{
				chip2.adlib_getsample(buffer, len);
			}
			if (strstr(core, "-dbfast"))
			{
				chip3.Generate(buffer, len);
			}
			if (strstr(core, "-mame"))
			{
				ymf262_update_one(chip4, buffer, len);
			}
		}
		else
		{
			OPL3_GenerateStream(&chip, buffer, len);
		}
	}
	if (mono)
	{
		if (strstr(mono, "-on"))
		{
			MonoMixdown(buffer, len);
		}
	}
	if (bitcrush)
	{
		if (strstr(bitcrush, "-on"))
		{
			Crush8Bit(buffer, len);
		}
	}
}

void emulator::MonoMixdown(signed short *buffer, unsigned int len) {
	signed short mixdown;
	for(unsigned int i = 0; i < len; i++)
	{
		mixdown = (buffer[0] + buffer[1]) / 2;
		buffer[0] = mixdown;
		buffer[1] = mixdown;
		buffer += 2;
	}
}

void emulator::Crush8Bit(signed short *buffer, unsigned int len) {
	for(unsigned int i = 0; i < len; i++)
	{
		buffer[0] = buffer[0] >> 8;
		buffer[0] = (buffer[0]) * 256;
		buffer[1] = buffer[1] >> 8;
		buffer[1] = (buffer[1]) * 256;
		buffer += 2;
	}
}
