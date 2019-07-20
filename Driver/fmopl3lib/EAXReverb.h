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

#include "ReverbEffect.h"

class EAXReverb {
private:
	unsigned int sampleRate;
	unsigned int reverbPreset;
	bool invert;
	bool only;
	ReverbEffect effect;
public:
	void Init(unsigned int rate);
	void SetPreset(unsigned int preset);
	const char *GetPresetName(unsigned int preset);
	void InvertReverb(bool val);
	void OnlyReverb(bool val);
	unsigned int GetRate();
	unsigned int GetPreset();
	bool GetInvertReverb();
	bool GetOnlyReverb();
	void Generate(signed short *buffer, unsigned int length);
	void Generate_float(float *buffer, unsigned int length);
	void Close();
};