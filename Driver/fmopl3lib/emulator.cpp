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

static char *core = getenv("OPL3CORE");
static char *silence = getenv("OPLEMUSILENCE");

void emulator::Init(unsigned int rate) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			return;
		}
	}
	if (core)
	{
		if (strstr(core, "-dbcompat"))
		{
			chip2.adlib_init(rate, 2, 2);
			return;
		}
		if (strstr(core, "-dbfast"))
		{
			chip3.Init(rate);
			chip3.WriteReg(0x105, 0x01);
			return;
		}
		if (strstr(core, "-mame"))
		{
			chip4 = ymf262_init(49716*288, rate);
			return;
		}
#ifdef __GNUC__
		if (strstr(core, "-rad"))
		{
			chip5.Init(rate);
			return;
		}
#endif
	}
	OPL3_Reset(&chip, rate);
}

void emulator::WriteReg(unsigned short reg, unsigned char data) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			return;
		}
	}
	if (core)
	{
		if (strstr(core, "-dbcompat"))
		{
			chip2.adlib_write(reg, data);
			return;
		}
		if (strstr(core, "-dbfast"))
		{
			chip3.WriteReg(reg, data);
			return;
		}
		if (strstr(core, "-mame"))
		{
			ymf262_write_reg(chip4, reg, data);
			return;
		}
#ifdef __GNUC__
		if (strstr(core, "-rad"))
		{
			chip5.WriteReg(reg, data);
			return;
		}
#endif
	}
	OPL3_WriteRegBuffered(&chip, reg, data);
}

void emulator::Generate(signed short *buffer, unsigned int len) {
	if (silence)
	{
		if (strstr(silence, "-on"))
		{
			GenerateSilence(buffer, len);
			return;
		}
	}
	if (core)
	{
		if (strstr(core, "-dbcompat"))
		{
			chip2.adlib_getsample(buffer, len);
			return;
		}
		if (strstr(core, "-dbfast"))
		{
			chip3.Generate(buffer, len);
			return;
		}
		if (strstr(core, "-mame"))
		{
			ymf262_update_one(chip4, buffer, len);
			return;
		}
#ifdef __GNUC__
		if (strstr(core, "-rad"))
		{
			chip5.Generate(buffer, len);
			return;
		}
#endif
	}
	OPL3_GenerateStream(&chip, buffer, len);
}
