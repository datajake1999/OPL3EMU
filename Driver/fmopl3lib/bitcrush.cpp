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

static unsigned int bits = 8;

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

#define PI 3.1415926536

static double AWGN_generator()
{/* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */

	double temp1;
	double temp2;
	double result;
	int p;

	p = 1;

	while( p > 0 )
	{
		temp2 = ( rand() / ( (double)RAND_MAX ) ); /*  rand() function generates an
													integer between 0 and  RAND_MAX,
													which is defined in stdlib.h.
												*/

		if ( temp2 == 0 )
		{// temp2 is >= (RAND_MAX / 2)
			p = 1;
		}// end if
		else
		{// temp2 is < (RAND_MAX / 2)
			p = -1;
		}// end else

	}// end while()

	temp1 = cos( ( 2.0 * (double)PI ) * rand() / ( (double)RAND_MAX ) );
	result = sqrt( -2.0 * log( temp2 ) ) * temp1;

	return result;	// return the generated random sample to the caller

}// end AWGN_generator()

void SetCrushAmount(unsigned int amount)
{
	bits = amount;
	if (bits > 16)
	{
		bits = 16;
	}
	else if (bits < 1)
	{
		bits = 1;
	}
}

void SetCrushAmountEnv()
{
	char *crushamount = getenv("CRUSHAMOUNT");
	if (crushamount)
	{
		SetCrushAmount(atoi(crushamount));
	}
}

void RectangleDither(signed short *buffer, unsigned int len) {
	unsigned int i;
	signed short noise;
	for(i = 0; i < len; i++)
	{
		noise = Gen_RectPDF() >> bits;
		buffer[0] = buffer[0] + noise;
		noise = Gen_RectPDF() >> bits;
		buffer[1] = buffer[1] + noise;
		buffer += 2;
	}
}

void TriangleDither(signed short *buffer, unsigned int len) {
	unsigned int i;
	signed short noise;
	for(i = 0; i < len; i++)
	{
		noise = Gen_TriPDF() >> bits;
		buffer[0] = buffer[0] + noise;
		noise = Gen_TriPDF() >> bits;
		buffer[1] = buffer[1] + noise;
		buffer += 2;
	}
}

void GaussianDither(signed short *buffer, unsigned int len) {
	unsigned int i;
	unsigned int nmult = (1 << (16 - bits)) / 4;
	signed short noise;
	for(i = 0; i < len; i++)
	{
		noise = AWGN_generator() * nmult;
		buffer[0] = buffer[0] + noise;
		noise = AWGN_generator() * nmult;
		buffer[1] = buffer[1] + noise;
		buffer += 2;
	}
}

void BitCrush(signed short *buffer, unsigned int len) {
	unsigned int i;
	unsigned int crush = 16 - bits;
	for(i = 0; i < len; i++)
	{
		buffer[0] = buffer[0] >> crush << crush;
		buffer[1] = buffer[1] >> crush << crush;
		buffer += 2;
	}
}

void SwapStereo(signed short *buffer, unsigned int len) {
	unsigned int i;
	signed short swap[2];
	for(i = 0; i < len; i++)
	{
		swap[0] = buffer[1];
		swap[1] = buffer[0];
		buffer[0] = swap[0];
		buffer[1] = swap[1];
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

void SurroundSoundLeft(signed short *buffer, unsigned int len) {
	unsigned int i;
	for(i = 0; i < len; i++)
	{
		buffer[0] = buffer[0] * -1;
		buffer += 2;
	}
}

void SurroundSoundRight(signed short *buffer, unsigned int len) {
	unsigned int i;
	for(i = 0; i < len; i++)
	{
		buffer[1] = buffer[1] * -1;
		buffer += 2;
	}
}

void LimitOutput(signed short limit, signed short *buffer, unsigned int len) {
	unsigned int i;
	if (limit > 32767)
	{
		limit = 32767;
	}
	else if (limit < 0)
	{
		limit = 0;
	}
	for(i = 0; i < len; i++)
	{
		if (buffer[0] > limit)
		{
			buffer[0] = limit;
		}
		else if (buffer[0] < limit * -1)
		{
			buffer[0] = limit * -1;
		}
		if (buffer[1] > limit)
		{
			buffer[1] = limit;
		}
		else if (buffer[1] < limit * -1)
		{
			buffer[1] = limit * -1;
		}
		buffer += 2;
	}
}
