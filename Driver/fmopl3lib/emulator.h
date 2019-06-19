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

#ifndef EMULATOR_H
#define EMULATOR_H

#include "opl3.h"
#include "opl.h"
#include "dbopl.h"
#include "ymf262.h"
#include "zdopl_wrapper.h"
#include "opal_wrapper.h"
#ifndef DISABLE_DSP_SUPPORT
#include "silence.h"
#endif /*DISABLE_DSP_SUPPORT*/

class emulator {
private:
	opl3_chip chip;
	OPLChipClass chip2;
	DBOPL::Handler chip3;
	void *chip4;
	zdopl_wrapper chip5;
	opal_wrapper chip6;
public:
	void Init(unsigned int rate);
	void WriteReg(unsigned short reg, unsigned char data);
	void Generate(signed short *buffer, unsigned int length);
};

#endif /*EMULATOR_H*/