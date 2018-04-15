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
FILE *out;

//fill in the wave header:
waveheader head = 
{
	0x46464952,	//rID = "RIFF"
	0,	//rSize (dummy value)
	0x45564157,	//wID = "WAVE"
	0x20746D66,	//fID = "fmt "
	18,	//fSize
	1,	//fFormat
	2,	//fChannels
	49716,	//fHertz
	198864,	//fBytesPerSec
	4,	//fBlockAlign
	16,	//fBits
	0,	//fSpecific
	0x61746164,	//dID = "data"
	0,	//dSize (dummy value)
};

void WavFileOpen(unsigned int rate)
{
	if (out == NULL)
	{
		//file open routines:
		CreateDirectory("C:\\OPLSynth", NULL);
		LPCTSTR lpPath = TEXT("C:\\OPLSynth\\output.wav");
		if (PathFileExists(lpPath) == FALSE)
		{
			out = fopen(lpPath, "wb");
		}
		else
		{
			//if the file already exists, try opening the file with a number appended to the end of the filename:
			for (int i = 0; i >= 0; i++)
			{
				char filename[100];
				sprintf(filename, "C:\\OPLSynth\\output%d.wav", i);
				if (PathFileExists(filename) == FALSE)
				{
					out = fopen(filename, "wb");
					break;
				}
			}
		}
		if (out == NULL)
		{
			//inform the user if the file fails to open:
			MessageBoxW(NULL, L"Failed to open output.wav.", L"WAV File Writer", MB_OK | MB_ICONEXCLAMATION);
			return;
		}
	}
	else
	//fill header with correct rate values if necessary:
	if (rate != 49716)
	{
		head.fHertz = rate;
		head.fBytesPerSec = 4*rate;
	}
	//write dummy wave header:
	rewind(out);
	fwrite(&head, sizeof(head), 1, out);
}

void WavFileWrite(signed short*buffer, unsigned int length)
{
	if (out == NULL)
	return;
	//write 16 bit stereo samples:
	fwrite(buffer, sizeof(INT32), length, out);
}

void WavFileClose()
{
	if (out == NULL)
	return;
	//get the current size of the file:
	UINT32 size = ftell(out);
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
	MessageBoxW(NULL, L"File output.wav saved.", L"WAV File Writer", MB_OK | MB_ICONINFORMATION);
#endif //_DEBUG
}
