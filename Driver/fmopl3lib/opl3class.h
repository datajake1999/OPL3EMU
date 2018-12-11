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

#include "..\interface.h"
#include "emulator.h"
#include "resampler.h"
#include "bitcrush.h"
#include "hardware.h"
#include "wav_writer.h"
#include "vgm_logging.h"


class opl3class : public fm_chip {
private:
	emulator emulator;
	void *resampler;
#ifdef _DEBUG
	FILE *rawsamples;
#endif
	void fm_generate_resampled(signed short *buffer, unsigned int length);
public:
	int fm_init(unsigned int rate);
	void fm_writereg(unsigned short reg, unsigned char data);
	void fm_generate(signed short *buffer, unsigned int length);
	void fm_close();
};