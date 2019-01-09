/*
OPL3MIDI test program
Copyright (C) 2018 Datajake

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "..\interface.h"

midisynth *synth;
unsigned int byte1, byte2, byte3;
unsigned int msg;

void setprogram(unsigned int channel, unsigned int program)
{
	byte1 = program;
	byte2 = 0xc0 + channel;
	msg = (byte1<<8) | byte2;
	synth->midi_write(msg);
}

void setcontroll(unsigned int channel, unsigned int type, unsigned int data)
{
	byte1 = data;
	byte2 = type;
	byte3 = 0xb0 + channel;
	msg = (byte1<<16) | (byte2<<8) | byte3;
	synth->midi_write(msg);
}

void noteon(unsigned int channel, unsigned int note, unsigned int velocity)
{
	byte1 = velocity;
	byte2 = note;
	byte3 = 0x90 + channel;
	msg = (byte1<<16) | (byte2<<8) | byte3;
	synth->midi_write(msg);
}

void noteoff(unsigned int channel, unsigned int note)
{
	byte1 = note;
	byte2 = 0x80 + channel;
	msg = (byte1<<8) | byte2;
	synth->midi_write(msg);
}

int main(int argc, char *argv[])
{
	unsigned int i;
	//set up timer
	clock_t begin, end;
	double time_spent;
	begin = clock();
	//set the sample rate of the output
	unsigned int samplerate;
	if (argc == 2)
	{
		samplerate = atoi(argv[1]);
	}
	else
	{
		samplerate = 49716;
	}
	//create the audio buffer
	short *buffer = new short[8 * samplerate];
	//create the synth object
	synth = getsynth();
	//initialize the synth
	synth->midi_init(samplerate);
	//test melotic instruments
	printf("Testing melotic instruments.\n");
	//set channel volume
	setcontroll(0, 7, 127);
	for (i = 0; i < 128; i++)
	{
		//Set MIDI program and print the program number
		setprogram(0, i);
		printf("Testing program %d.\n", i);
		//turn on note c3 and generate half a second of audio
		noteon(0, 48, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note c3, turn on note d3 and generate half a second of audio
		noteoff(0, 48);
		noteon(0, 50, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note d3, turn on note e3 and generate half a second of audio
		noteoff(0, 50);
		noteon(0, 52, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note e3, turn on note f3 and generate half a second of audio
		noteoff(0, 52);
		noteon(0, 53, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note f3, turn on note g3 and generate half a second of audio
		noteoff(0, 53);
		noteon(0, 55, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note g3, turn on note a4 and generate half a second of audio
		noteoff(0, 55);
		noteon(0, 57, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note a4, turn on note b4 and generate half a second of audio
		noteoff(0, 57);
		noteon(0, 59, 127);
		synth->midi_generate(buffer, samplerate/2);
		//turn off note b4, turn on note c4 and generate 4 seconds of audio
		noteoff(0, 59);
		noteon(0, 60, 127);
		synth->midi_generate(buffer, samplerate*4);
		//turn off note c4 and generate 2 seconds of audio
		noteoff(0, 60);
		synth->midi_generate(buffer, samplerate*2);
	}
	//Test drum kit
	printf("Testing drum kit.\n");
	//set channel volume
	setcontroll(9, 7, 127);
	//turn on first drum and generate half a second of audio
	noteon(9, 35, 127);
	synth->midi_generate(buffer, samplerate/2);
	//turn off first drum, turn on next drum and generate half a second of audio
	//since we don't have to skip notes as we did for the melotic instruments, we can do this exact process until the last drum is turned on
	for (i = 35; i < 81; i++)
	{
		noteoff(9, i);
		noteon(9, i + 1, 127);
		synth->midi_generate(buffer, samplerate/2);
	}
	//turn off last drum and generate 2 seconds of audio
	noteoff(9, 81);
	synth->midi_generate(buffer, samplerate*2);
	//close the synth
	synth->midi_close();
	//clear the synth object
	delete synth;
	synth = NULL;
	//clear the audio buffer
	delete buffer;
	buffer = NULL;
	//get the time taken to perform the test.
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The OPL3MIDI test took %f seconds to complete. Press enter to exit.\n", time_spent);
	getchar();
	return 0;
}
