/*
Bit crusher
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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bitcrush.h"

unsigned int bits = 8;

static int Gen_Random()
{
	return   (rand() - RAND_MAX/2);
}

static int Gen_RectPDF()
{
	return Gen_Random();
}

static int Gen_TriPDF()
{
	int s1 = Gen_Random();
	int s2 = Gen_Random();
	int out = s1+s2;
	return out;
}

void RectangleDither(signed short *buffer, unsigned int len) {
	unsigned int i;
	signed short noise;
	for(i = 0; i < len; i++)
	{
		noise = (Gen_RectPDF()) / pow((double)2, (double)bits);
		buffer[0] = (buffer[0]) + noise;
		buffer[1] = (buffer[1]) + noise;
		buffer += 2;
	}
}

void TriangleDither(signed short *buffer, unsigned int len) {
	unsigned int i;
	signed short noise;
	for(i = 0; i < len; i++)
	{
		noise = (Gen_RectPDF()) / pow((double)2, (double)bits);
		buffer[0] = (buffer[0]) + noise;
		buffer[1] = (buffer[1]) + noise;
		buffer += 2;
	}
}

void MonoMixdown(signed short *buffer, unsigned int len) {
	unsigned int i;
	signed short mixdown;
	for(i = 0; i < len; i++)
	{
		mixdown = (buffer[0] + buffer[1]) / 2;
		buffer[0] = mixdown;
		buffer[1] = mixdown;
		buffer += 2;
	}
}

void BitCrush(signed short *buffer, unsigned int len) {
	unsigned int i;
	unsigned int crush = 16 - bits;
	for(i = 0; i < len; i++)
	{
		buffer[0] = (buffer[0] >> crush) * pow((double)2, (double)crush);
		buffer[1] = (buffer[1] >> crush) * pow((double)2, (double)crush);
		buffer += 2;
	}
}

void SetCrushAmount()
{
	char *crushamount = getenv("CRUSHAMOUNT");
	if (crushamount)
	{
		if (strstr(crushamount, getenv("CRUSHAMOUNT")))
		{
			bits = atoi(crushamount);
		}
	}
	if (bits > 16)
	{
		bits = 16;
	}
	else if (bits < 1)
	{
		bits = 1;
	}
}
