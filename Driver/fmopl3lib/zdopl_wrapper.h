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

#include "zdopl.h"
#define RSM_FRAC    10

class zdopl_wrapper {
private:
	OPLEmul *chip;
	signed long rateratio;
	signed long samplecnt;
	signed short oldsamples[2];
	signed short samples[2];
public:
	void Init(unsigned int rate, bool fullpan);
	void WriteReg(unsigned short reg, unsigned char data);
	void SetPanning(int c, float left, float right);
	void Generate(signed short *buffer, unsigned int length);
	void GenerateResampled(signed short *buffer, unsigned int length);
	void GenerateStream(signed short *buffer, unsigned int length);
};