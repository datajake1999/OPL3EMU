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

//Bassed on EAXReverb: https://github.com/Relfos/EAXReverb

#include "EAXReverb.h"

void EAXReverb::Init(unsigned int rate) {
	sampleRate = rate;
	//initialize the effect
	effect.Create(rate);
	//update the effect
	effect.Update(rate);
}

void EAXReverb::SetPreset(unsigned int preset) {
	//set a preset
	if (preset == 0)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_GENERIC);
	}
	else if (preset == 1)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PADDEDCELL);
	}
	else if (preset == 2)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ROOM);
	}
	else if (preset == 3)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_BATHROOM);
	}
	else if (preset == 4)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_LIVINGROOM);
	}
	else if (preset == 5)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_STONEROOM);
	}
	else if (preset == 6)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_AUDITORIUM);
	}
	else if (preset == 7)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CONCERTHALL);
	}
	else if (preset == 8)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CAVE);
	}
	else if (preset == 9)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ARENA);
	}
	else if (preset == 10)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_HANGAR);
	}
	else if (preset == 11)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CARPETEDHALLWAY);
	}
	else if (preset == 12)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_HALLWAY);
	}
	else if (preset == 13)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_STONECORRIDOR);
	}
	else if (preset == 14)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ALLEY);
	}
	else if (preset == 15)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FOREST);
	}
	else if (preset == 16)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY);
	}
	else if (preset == 17)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_MOUNTAINS);
	}
	else if (preset == 18)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_QUARRY);
	}
	else if (preset == 19)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PLAIN);
	}
	else if (preset == 20)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PARKINGLOT);
	}
	else if (preset == 21)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SEWERPIPE);
	}
	else if (preset == 22)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_UNDERWATER);
	}
	else if (preset == 23)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRUGGED);
	}
	else if (preset == 24)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DIZZY);
	}
	else if (preset == 25)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PSYCHOTIC);
	}
	else if (preset == 26)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_SMALLROOM);
	}
	else if (preset == 27)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_SHORTPASSAGE);
	}
	else if (preset == 28)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_MEDIUMROOM);
	}
	else if (preset == 29)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_LARGEROOM);
	}
	else if (preset == 30)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_LONGPASSAGE);
	}
	else if (preset == 31)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_HALL);
	}
	else if (preset == 32)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_CUPBOARD);
	}
	else if (preset == 33)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_COURTYARD);
	}
	else if (preset == 34)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CASTLE_ALCOVE);
	}
	else if (preset == 35)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_SMALLROOM);
	}
	else if (preset == 36)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_SHORTPASSAGE);
	}
	else if (preset == 37)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_MEDIUMROOM);
	}
	else if (preset == 38)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_LARGEROOM);
	}
	else if (preset == 39)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_LONGPASSAGE);
	}
	else if (preset == 40)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_HALL);
	}
	else if (preset == 41)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_CUPBOARD);
	}
	else if (preset == 42)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_COURTYARD);
	}
	else if (preset == 43)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_FACTORY_ALCOVE);
	}
	else if (preset == 44)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_SMALLROOM);
	}
	else if (preset == 45)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_SHORTPASSAGE);
	}
	else if (preset == 46)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_MEDIUMROOM);
	}
	else if (preset == 47)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_LARGEROOM);
	}
	else if (preset == 48)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_LONGPASSAGE);
	}
	else if (preset == 49)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_HALL);
	}
	else if (preset == 50)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_CUPBOARD);
	}
	else if (preset == 51)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_COURTYARD);
	}
	else if (preset == 52)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_ICEPALACE_ALCOVE);
	}
	else if (preset == 53)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_SMALLROOM);
	}
	else if (preset == 54)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_SHORTPASSAGE);
	}
	else if (preset == 55)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_MEDIUMROOM);
	}
	else if (preset == 56)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_LARGEROOM);
	}
	else if (preset == 57)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_LONGPASSAGE);
	}
	else if (preset == 58)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_HALL);
	}
	else if (preset == 59)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_CUPBOARD);
	}
	else if (preset == 60)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPACESTATION_ALCOVE);
	}
	else if (preset == 61)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_SMALLROOM);
	}
	else if (preset == 62)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_SHORTPASSAGE);
	}
	else if (preset == 63)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_MEDIUMROOM);
	}
	else if (preset == 64)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_LARGEROOM);
	}
	else if (preset == 65)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_LONGPASSAGE);
	}
	else if (preset == 66)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_HALL);
	}
	else if (preset == 67)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_CUPBOARD);
	}
	else if (preset == 68)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_COURTYARD);
	}
	else if (preset == 69)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_WOODEN_ALCOVE);
	}
	else if (preset == 70)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_EMPTYSTADIUM);
	}
	else if (preset == 71)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_SQUASHCOURT);
	}
	else if (preset == 72)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_SMALLSWIMMINGPOOL);
	}
	else if (preset == 73)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_LARGESWIMMINGPOOL);
	}
	else if (preset == 74)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_GYMNASIUM);
	}
	else if (preset == 75)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_FULLSTADIUM);
	}
	else if (preset == 76)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SPORT_STADIUMTANNOY);
	}
	else if (preset == 77)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PREFAB_WORKSHOP);
	}
	else if (preset == 78)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PREFAB_SCHOOLROOM);
	}
	else if (preset == 79)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PREFAB_PRACTISEROOM);
	}
	else if (preset == 80)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PREFAB_OUTHOUSE);
	}
	else if (preset == 81)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PREFAB_CARAVAN);
	}
	else if (preset == 82)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DOME_TOMB);
	}
	else if (preset == 83)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PIPE_SMALL);
	}
	else if (preset == 84)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DOME_SAINTPAULS);
	}
	else if (preset == 85)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PIPE_LONGTHIN);
	}
	else if (preset == 86)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PIPE_LARGE);
	}
	else if (preset == 87)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_PIPE_RESONANT);
	}
	else if (preset == 88)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_OUTDOORS_BACKYARD);
	}
	else if (preset == 89)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_OUTDOORS_ROLLINGPLAINS);
	}
	else if (preset == 90)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_OUTDOORS_DEEPCANYON);
	}
	else if (preset == 91)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_OUTDOORS_CREEK);
	}
	else if (preset == 92)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_OUTDOORS_VALLEY);
	}
	else if (preset == 93)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_MOOD_HEAVEN);
	}
	else if (preset == 94)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_MOOD_HELL);
	}
	else if (preset == 95)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_MOOD_MEMORY);
	}
	else if (preset == 96)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_COMMENTATOR);
	}
	else if (preset == 97)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_PITGARAGE);
	}
	else if (preset == 98)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_INCAR_RACER);
	}
	else if (preset == 99)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_INCAR_SPORTS);
	}
	else if (preset == 100)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_INCAR_LUXURY);
	}
	else if (preset == 101)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_FULLGRANDSTAND);
	}
	else if (preset == 102)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_EMPTYGRANDSTAND);
	}
	else if (preset == 103)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DRIVING_TUNNEL);
	}
	else if (preset == 104)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY_STREETS);
	}
	else if (preset == 105)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY_SUBWAY);
	}
	else if (preset == 106)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY_MUSEUM);
	}
	else if (preset == 107)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY_LIBRARY);
	}
	else if (preset == 108)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY_UNDERPASS);
	}
	else if (preset == 109)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CITY_ABANDONED);
	}
	else if (preset == 110)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_DUSTYROOM);
	}
	else if (preset == 111)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_CHAPEL);
	}
	else if (preset == 112)
	{
		effect.LoadPreset(EFX_REVERB_PRESET_SMALLWATERROOM);
	}
	//update the effect
	effect.Update(sampleRate);
}

void EAXReverb::InvertReverb(bool val) {
	invert = val;
}

void EAXReverb::OnlyReverb(bool val) {
	only = val;
}

void EAXReverb::GenerateReverb(signed short *buffer, unsigned int len) {
	//check the sample rate, since the effect has issues when working with sample rates below 10000 HZ
	if (sampleRate < 10000)
	{
		return;
	}
	//allocate memory for mono samples
	int16_t *samples = new int16_t[len];
	unsigned int i;
	//convert stereo samples into mono
	for (i=0; i<len; i++)
	{
		samples[i] = (buffer[0] + buffer[1]) / 2;
		buffer += 2;
	}
	//rewind the buffer back to the beginning, as it will be used for the final output
	buffer -= len*2;
	//allocate memory for mono samples in floating point
	float *floatSamplesIn =  new float[len];
	//convert mono samples into floating point for use by the reverb effect
	for (i=0; i<len; i++)
	{
		floatSamplesIn[i] = (float)samples[i] / 32767.0f;
	}
	//get rid of the original mono samples, as they are no longer needed
	delete[] samples;
	//set the offset for the audio buffer
	unsigned int offset = 0;
	//allocate memory for reverb output samples in floating point
	float floatSamplesOut[REVERB_BUFFERSIZE * OUTPUT_CHANNELS];
	do {
		//set the amount of samples to process at a time
		unsigned int workSamples = REVERB_BUFFERSIZE / 4;
		if (workSamples>len)
		{
			workSamples = len;
		}
		//process the effect
		effect.Process(workSamples, &floatSamplesIn[offset],  floatSamplesOut);
		//invert the phase of the reverb if we set InvertReverb to true
		if (invert == true)
		{
			for (i=0; i<workSamples; i++)
			{
				floatSamplesOut[i*2 + 0] = floatSamplesOut[i*2 + 0] * -1;
				floatSamplesOut[i*2 + 1] = floatSamplesOut[i*2 + 1] * -1;
			}
		}
		//convert the floating point output to 32 bit integers, check to make sure they don't overflow, and convert them to 16 bit integers to write to the audio buffer
		for (i=0; i<workSamples; i++)
		{
			int32_t outSample = (int32_t) (floatSamplesOut[i*2 + 0] * 32767.0f);
			if (outSample > 32767)
			{
				outSample = 32767;
			}
			else if (outSample < -32768)
			{
				outSample = -32768;
			}
			buffer[0] = (short)outSample;
			outSample = (int32_t) (floatSamplesOut[i*2 + 1] * 32767.0f);
			if (outSample > 32767)
			{
				outSample = 32767;
			}
			else if (outSample < -32768)
			{
				outSample = -32768;
			}
			buffer[1] = (short)outSample;
			buffer += 2;
		}
		//update the sample counters
		len -= workSamples;
		offset += workSamples;
	} while (len>0);
	//delete the floating point input samples
	delete[] floatSamplesIn;
}

void EAXReverb::Generate(signed short *buffer, unsigned int len) {
	//check if we are only generating the reverb output
	if (only == true)
	{
		GenerateReverb(buffer, len);
		return;
	}
	//check the sample rate, since the effect has issues when working with sample rates below 10000 HZ
	if (sampleRate < 10000)
	{
		return;
	}
	//allocate memory for mono samples
	int16_t *samples = new int16_t[len];
	unsigned int i;
	//convert stereo samples into mono
	for (i=0; i<len; i++)
	{
		samples[i] = (buffer[0] + buffer[1]) / 2;
		buffer += 2;
	}
	//rewind the buffer back to the beginning, as it will be used for the final output
	buffer -= len*2;
	//allocate memory for mono samples in floating point
	float *floatSamplesIn =  new float[len];
	//convert mono samples into floating point for use by the reverb effect
	for (i=0; i<len; i++)
	{
		floatSamplesIn[i] = (float)samples[i] / 32767.0f;
	}
	//get rid of the original mono samples, as they are no longer needed
	delete[] samples;
	//set the offset for the audio buffer
	unsigned int offset = 0;
	//allocate memory for reverb output samples in floating point
	float floatSamplesOut[REVERB_BUFFERSIZE * OUTPUT_CHANNELS];
	do {
		//set the amount of samples to process at a time
		unsigned int workSamples = REVERB_BUFFERSIZE / 4;
		if (workSamples>len)
		{
			workSamples = len;
		}
		//process the effect
		effect.Process(workSamples, &floatSamplesIn[offset],  floatSamplesOut);
		//invert the phase of the reverb if we set InvertReverb to true
		if (invert == true)
		{
			for (i=0; i<workSamples; i++)
			{
				floatSamplesOut[i*2 + 0] = floatSamplesOut[i*2 + 0] * -1;
				floatSamplesOut[i*2 + 1] = floatSamplesOut[i*2 + 1] * -1;
			}
		}
		//convert the floating point output to 32 bit integers, check to make sure they don't overflow, and convert them to 16 bit integers to write to the audio buffer
		for (i=0; i<workSamples; i++)
		{
			int32_t outSample = buffer[0] + (int32_t) (floatSamplesOut[i*2 + 0] * 32767.0f);
			if (outSample > buffer[0] + 32767)
			{
				outSample = buffer[0];
			}
			else if (outSample < buffer[0] - 32768)
			{
				outSample = buffer[0];
			}
			if (outSample > 32767)
			{
				outSample = 32767;
			}
			else if (outSample < -32768)
			{
				outSample = -32768;
			}
			buffer[0] = (short)outSample;
			outSample = buffer[1] + (int32_t) (floatSamplesOut[i*2 + 1] * 32767.0f);
			if (outSample > buffer[1] + 32767)
			{
				outSample = buffer[1];
			}
			else if (outSample < buffer[1] - 32768)
			{
				outSample = buffer[1];
			}
			if (outSample > 32767)
			{
				outSample = 32767;
			}
			else if (outSample < -32768)
			{
				outSample = -32768;
			}
			buffer[1] = (short)outSample;
			buffer += 2;
		}
		//update the sample counters
		len -= workSamples;
		offset += workSamples;
	} while (len>0);
	//delete the floating point input samples
	delete[] floatSamplesIn;
}

void EAXReverb::Close() {
	//close the effect
	effect.Destroy();
}
