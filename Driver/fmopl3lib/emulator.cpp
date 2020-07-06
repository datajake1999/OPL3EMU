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

#include "emulator.h"

void emulator::SetCore(unsigned int val) {
	core = val;
}

unsigned int emulator::GetCore() {
	return core;
}

void emulator::SetSilent(unsigned int val) {
	silent = val;
}

unsigned int emulator::GetSilent() {
	return silent;
}

void emulator::Init(unsigned int rate) {
#ifndef DISABLE_DSP_SUPPORT
	if (silent == 1)
	{
		return;
	}
#endif /*DISABLE_DSP_SUPPORT*/
	if (core == 1)
	{
		chip2.adlib_init(rate, 2, 2);
	}
	else if (core == 2)
	{
		chip3.Init(rate);
		chip3.WriteReg(0x105, 0x01);
	}
	else if (core == 3)
	{
		chip4 = ymf262_init(49716*288, rate);
	}
	else if (core == 4)
	{
		chip5.Init(rate, false);
	}
	else if (core == 5)
	{
		chip6.Init(rate);
	}
	else
	{
		OPL3_Reset(&chip, rate);
	}
}

void emulator::WriteReg(unsigned short reg, unsigned char data) {
#ifndef DISABLE_DSP_SUPPORT
	if (silent == 1)
	{
		return;
	}
#endif /*DISABLE_DSP_SUPPORT*/
	if (core == 1)
	{
		chip2.adlib_write(reg, data);
	}
	else if (core == 2)
	{
		chip3.WriteReg(reg, data);
	}
	else if (core == 3)
	{
		ymf262_write_reg(chip4, reg, data);
	}
	else if (core == 4)
	{
		chip5.WriteReg(reg, data);
	}
	else if (core == 5)
	{
		chip6.WriteReg(reg, data);
	}
	else
	{
		OPL3_WriteRegBuffered(&chip, reg, data);
	}
}

void emulator::Generate(signed short *buffer, unsigned int len) {
#ifndef DISABLE_DSP_SUPPORT
	if (silent == 1)
	{
		GenerateSilence(buffer, len);
		return;
	}
#endif /*DISABLE_DSP_SUPPORT*/
	if (core == 1)
	{
		chip2.adlib_getsample(buffer, len);
	}
	else if (core == 2)
	{
		chip3.Generate(buffer, len);
	}
	else if (core == 3)
	{
		ymf262_update_one(chip4, buffer, len);
	}
	else if (core == 4)
	{
		chip5.GenerateStream(buffer, len);
	}
	else if (core == 5)
	{
		chip6.Generate(buffer, len);
	}
	else
	{
		OPL3_GenerateStream(&chip, buffer, len);
	}
}
