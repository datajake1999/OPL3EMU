/*
WAV file writer for OPL3 emulation
Copyright (C) 2018 Datajake
Lucely bassed on code from K1n9_Duk3's IMF to WAV converter - Converts IMF files to WAV.
Copyright (C) 2013-2014 K1n9_Duk3

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

#include "wav_writer.h"

//create the file object:
static FILE *out;

//fill in the wave header:
static waveheader head = 
{
	0x46464952,	//rID = "RIFF"
	0,	//rSize (dummy value)
	0x45564157,	//wID = "WAVE"
	0x20746D66,	//fID = "fmt "
	16,	//fSize
	1,	//fFormat
	2,	//fChannels
	0,	//fHertz (dummy value)
	0,	//fBytesPerSec (dummy value)
	4,	//fBlockAlign
	16,	//fBits
	0x61746164,	//dID = "data"
	0,	//dSize (dummy value)
};

//file exists function:
static int fileexists(const char * filename)
{
	FILE *check;
	if (check = fopen(filename, "r"))
	{
		fclose(check);
		return 1;
	}
	return 0;
}

void WavFileOpen(unsigned int rate)
{
	if (out == NULL)
	{
		//file open routines:
		char filename[100];
		UINT32 i;
#ifdef WIN32
		CreateDirectory("C:\\OPLSynth", NULL);
		sprintf(filename, "C:\\OPLSynth\\output.wav");
#else
		sprintf(filename, "output.wav");
#endif
		if (fileexists(filename) == 0)
		{
			out = fopen(filename, "wb");
		}
		else
		{
			//if the file already exists, try opening the file with a number appended to the end of the filename:
			for(i = 0; i >= 0; i++)
			{
#ifdef WIN32
				sprintf(filename, "C:\\OPLSynth\\output%d.wav", i);
#else
				sprintf(filename, "output%d.wav", i);
#endif
				if (fileexists(filename) == 0)
				{
					out = fopen(filename, "wb");
					break;
				}
			}
		}
		if (out == NULL)
		{
			//inform the user if the file fails to open:
#ifdef WIN32
			MessageBoxW(NULL, L"Failed to open output.wav.", L"WAV File Writer", MB_OK | MB_ICONEXCLAMATION);
#else
			printf("Failed to open %s.\n", filename);
#endif
			return;
		}
	}
	else
	rewind(out);
	//fill header with correct rate values:
	head.fHertz = rate;
	head.fBytesPerSec = 4*rate;
	//write dummy wave header:
	fwrite(&head, sizeof(head), 1, out);
}

void WavFileWrite(signed short *buffer, unsigned int length)
{
	if (out == NULL)
	return;
	//write 16 bit stereo samples:
	fwrite(buffer, sizeof(INT32), length, out);
}

void WavFileClose()
{
	UINT32 size;
	if (out == NULL)
	return;
	//get the current size of the file:
	size = ftell(out);
	//fill header with correct size values:
	head.dSize = size-sizeof(head);
	head.rSize = size-8;
	//write real wave header:
	fseek(out, 0, SEEK_SET);
	fwrite(&head, sizeof(head), 1, out);
	//close the file:
	fclose(out);
	//clear the file object:
	out = NULL;
	//if running in debug mode, inform the user when the file is saved:
#ifdef _DEBUG
#ifdef WIN32
	MessageBoxW(NULL, L"File output.wav saved.", L"WAV File Writer", MB_OK | MB_ICONINFORMATION);
#else
	printf("File saved.\n");
#endif
#endif //_DEBUG
}
