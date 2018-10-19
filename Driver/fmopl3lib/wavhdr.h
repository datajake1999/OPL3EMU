/*
Wave header structure
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

//just a quick hack, but it works...
#pragma pack(2)//this gave me a headache...
struct waveheader{
	UINT32 rID, rSize;
	UINT32 wID;
	UINT32 fID, fSize;
	UINT16 fFormat, fChannels;
	UINT32 fHertz, fBytesPerSec;
	UINT16 fBlockAlign, fBits;
	UINT32 dID, dSize;
};
#pragma pack()
