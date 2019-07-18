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

#include "biquad.h"

class filter {
private:
	unsigned int type;
	float freq;
	float res;
	float gain;
	sf_biquad_state_st bq_state;
public:
	void SetType(unsigned int val);
	void SetFreq(float val);
	void SetRes(float val);
	void SetGain(float val);
	void Init(unsigned int rate);
	void Generate(signed short *buffer, unsigned int length);
};