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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "biquad.h"

class filter {
private:
	unsigned int samplerate;
	unsigned int type;
	float freq;
	float res;
	float gain;
	bool Dither;
	sf_biquad_state_st bq_state;
	float AWGN_generator();
public:
	void SetType(unsigned int val);
	const char *GetFilterName(unsigned int filter);
	void SetFreq(float val);
	void SetRes(float val);
	void SetGain(float val);
	void SetDither(bool val);
	unsigned int GetRate();
	unsigned int GetType();
	float GetFreq();
	float GetRes();
	float GetGain();
	bool GetDither();
	void Init(unsigned int rate);
	void Reload();
	void Generate(signed short *buffer, unsigned int length);
	void Generate_float(float *buffer, unsigned int length);
};