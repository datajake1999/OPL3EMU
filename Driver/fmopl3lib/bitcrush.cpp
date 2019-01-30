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

/*
Sources for dither noise generators
Rectangle and Triangle probability density functions: http://github.com/Metabog/ADither/blob/master/DSP_dither.c
Additive White Gaussian Noise Generator: http://www.embeddedrelated.com/showcode/311.php
*/

static short Gen_Random()
{
	return   (rand() - RAND_MAX/2);
}

static short Gen_RectPDF()
{
	return Gen_Random();
}

static short Gen_TriPDF()
{
	short s1 = Gen_Random();
	short s2 = Gen_Random();
	short out = s1+s2;
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

void RectangleDither(signed short *buffer, unsigned int length)
{
	unsigned int i;
	signed short noise;
	signed long add;
	for(i = 0; i < length; i++)
	{
		noise = Gen_RectPDF() >> bits;
		add = buffer[0] + noise;
		if (add > 32767)
		{
			add = 32767;
		}
		else if (add < -32768)
		{
			add = -32768;
		}
		buffer[0] = (short)add;
		noise = Gen_RectPDF() >> bits;
		add = buffer[1] + noise;
		if (add > 32767)
		{
			add = 32767;
		}
		else if (add < -32768)
		{
			add = -32768;
		}
		buffer[1] = (short)add;
		buffer += 2;
	}
}

void TriangleDither(signed short *buffer, unsigned int length)
{
	unsigned int i;
	signed short noise;
	signed long add;
	for(i = 0; i < length; i++)
	{
		noise = Gen_TriPDF() >> bits;
		add = buffer[0] + noise;
		if (add > 32767)
		{
			add = 32767;
		}
		else if (add < -32768)
		{
			add = -32768;
		}
		buffer[0] = (short)add;
		noise = Gen_TriPDF() >> bits;
		add = buffer[1] + noise;
		if (add > 32767)
		{
			add = 32767;
		}
		else if (add < -32768)
		{
			add = -32768;
		}
		buffer[1] = (short)add;
		buffer += 2;
	}
}

void GaussianDither(signed short *buffer, unsigned int length)
{
	unsigned int i;
	unsigned int nmult = (1 << (16 - bits)) / 4;
	signed short noise;
	signed long add;
	for(i = 0; i < length; i++)
	{
		noise = AWGN_generator() * nmult;
		add = buffer[0] + noise;
		if (add > 32767)
		{
			add = 32767;
		}
		else if (add < -32768)
		{
			add = -32768;
		}
		buffer[0] = (short)add;
		noise = AWGN_generator() * nmult;
		add = buffer[1] + noise;
		if (add > 32767)
		{
			add = 32767;
		}
		else if (add < -32768)
		{
			add = -32768;
		}
		buffer[1] = (short)add;
		buffer += 2;
	}
}

void BitCrush(signed short *buffer, unsigned int length)
{
	unsigned int i;
	unsigned int crush = 16 - bits;
	for(i = 0; i < length; i++)
	{
		buffer[0] = buffer[0] >> crush << crush;
		buffer[1] = buffer[1] >> crush << crush;
		buffer += 2;
	}
}

void SwapStereo(signed short *buffer, unsigned int length)
{
	unsigned int i;
	signed short swap[2];
	for(i = 0; i < length; i++)
	{
		swap[0] = buffer[1];
		swap[1] = buffer[0];
		buffer[0] = swap[0];
		buffer[1] = swap[1];
		buffer += 2;
	}
}

void MonoMixdown(signed short *buffer, unsigned int length)
{
	unsigned int i;
	signed short mixdown;
	for(i = 0; i < length; i++)
	{
		mixdown = (buffer[0] + buffer[1]) / 2;
		buffer[0] = mixdown;
		buffer[1] = mixdown;
		buffer += 2;
	}
}

void SurroundSoundLeft(signed short *buffer, unsigned int length)
{
	unsigned int i;
	for(i = 0; i < length; i++)
	{
		if (buffer[0] < -32767)
		{
			buffer[0] = -32767;
		}
		buffer[0] = buffer[0] * -1;
		buffer += 2;
	}
}

void SurroundSoundRight(signed short *buffer, unsigned int length)
{
	unsigned int i;
	for(i = 0; i < length; i++)
	{
		if (buffer[1] < -32767)
		{
			buffer[1] = -32767;
		}
		buffer[1] = buffer[1] * -1;
		buffer += 2;
	}
}

void LimitOutput(signed long limit, signed short *buffer, unsigned int length)
{
	unsigned int i;
	if (limit > 32767)
	{
		limit = 32767;
	}
	else if (limit < 0)
	{
		limit = 0;
	}
	for(i = 0; i < length; i++)
	{
		if (buffer[0] > limit)
		{
			buffer[0] = (short)limit;
		}
		else if (buffer[0] < limit * -1)
		{
			buffer[0] = limit * -1;
		}
		if (buffer[1] > limit)
		{
			buffer[1] = (short)limit;
		}
		else if (buffer[1] < limit * -1)
		{
			buffer[1] = limit * -1;
		}
		buffer += 2;
	}
}
