/*
Interface for WAV file writer
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

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include "types.h"
#endif
#ifndef WAV_WRITER_H
#define WAV_WRITER_H

#include "wavhdr.h"

void WavFileOpen(unsigned int rate);
void WavFileWrite(signed short *buffer, unsigned int length);
void WavFileClose();

#endif //WAV_WRITER_H