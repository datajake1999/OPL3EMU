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
#include "opl3.h"
#include "opl.h"
#include "dbopl.h"
#include "ymf262.h"
#include "resampler.h"
#include "silence.h"
#include "opl_hw.h"
#include "opl_lpt.h"
#include "wav_writer.h"
#include "vgm_logging.h"


class opl3class : public fm_chip {
private:
	opl3_chip chip;
	DBOPL::Handler chip2;
	void *chip3;
	void *resampler;
	Bit16s samples[2];
	int fm_init_emu(unsigned int rate);
	void fm_generate_stream(signed short *buffer, unsigned int length);
	void fm_generate_resampled(signed short *buffer, unsigned int length);
public:
	int fm_init(unsigned int rate);
	void fm_writereg(unsigned short reg, unsigned char data);
	void fm_generate(signed short *buffer, unsigned int length);
	void fm_close();
};