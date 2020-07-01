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

#ifndef DISABLE_DSP_SUPPORT
/*
Sources for dither noise generators
Rectangle and Triangle Probability Density Functions: https://github.com/Metabog/ADither/blob/master/DSP_dither.c
Additive White Gaussian Noise Generator: https://www.embeddedrelated.com/showcode/311.php
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
#endif /*DISABLE_DSP_SUPPORT*/

void SetCrushAmount(bitcrusher *bc, unsigned int amount)
{
#ifndef DISABLE_DSP_SUPPORT
	bc->bits = amount;
	if (bc->bits > 16)
	{
		bc->bits = 16;
	}
	else if (bc->bits < 1)
	{
		bc->bits = 1;
	}
#endif /*DISABLE_DSP_SUPPORT*/
}

unsigned int GetCrushAmount(bitcrusher *bc)
{
#ifndef DISABLE_DSP_SUPPORT
	return bc->bits;
#else
	return 0;
#endif /*DISABLE_DSP_SUPPORT*/
}

void SetAutoDither(bitcrusher *bc, unsigned int val)
{
#ifndef DISABLE_DSP_SUPPORT
	bc->AutoDither = val;
#endif /*DISABLE_DSP_SUPPORT*/
}

unsigned int GetAutoDither(bitcrusher *bc)
{
#ifndef DISABLE_DSP_SUPPORT
	return bc->AutoDither;
#else
	return 0;
#endif /*DISABLE_DSP_SUPPORT*/
}

void SetOnlyError(bitcrusher *bc, unsigned int val)
{
#ifndef DISABLE_DSP_SUPPORT
	bc->OnlyError = val;
#endif /*DISABLE_DSP_SUPPORT*/
}

unsigned int GetOnlyError(bitcrusher *bc)
{
#ifndef DISABLE_DSP_SUPPORT
	return bc->OnlyError;
#else
	return 0;
#endif /*DISABLE_DSP_SUPPORT*/
}

void RectangleDither(bitcrusher *bc, signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
	unsigned int i;
	signed short noise;
	signed long add;
	for(i = 0; i < length; i++)
	{
		if (bc->AutoDither == 1 && buffer[0] == 0)
		noise = 0;
		else
		noise = Gen_RectPDF() >> bc->bits;
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
		if (bc->AutoDither == 1 && buffer[1] == 0)
		noise = 0;
		else
		noise = Gen_RectPDF() >> bc->bits;
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
#endif /*DISABLE_DSP_SUPPORT*/
}

void TriangleDither(bitcrusher *bc, signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
	unsigned int i;
	signed short noise;
	signed long add;
	for(i = 0; i < length; i++)
	{
		if (bc->AutoDither == 1 && buffer[0] == 0)
		noise = 0;
		else
		noise = Gen_TriPDF() >> bc->bits;
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
		if (bc->AutoDither == 1 && buffer[1] == 0)
		noise = 0;
		else
		noise = Gen_TriPDF() >> bc->bits;
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
#endif /*DISABLE_DSP_SUPPORT*/
}

void GaussianDither(bitcrusher *bc, signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
	unsigned int i;
	unsigned int nmult = (1 << (16 - bc->bits)) / 4;
	signed short noise;
	signed long add;
	if (nmult < 1)
	{
		nmult = 1;
	}
	for(i = 0; i < length; i++)
	{
		if (bc->AutoDither == 1 && buffer[0] == 0)
		noise = 0;
		else
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
		if (bc->AutoDither == 1 && buffer[1] == 0)
		noise = 0;
		else
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
#endif /*DISABLE_DSP_SUPPORT*/
}

void BitCrush(bitcrusher *bc, signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
	unsigned int i;
	unsigned int crush = 16 - bc->bits;
	for(i = 0; i < length; i++)
	{
		if (bc->OnlyError == 1)
		buffer[0] = buffer[0] + (buffer[0] >> crush << crush) * -1;
		else
		buffer[0] = buffer[0] >> crush << crush;
		if (bc->OnlyError == 1)
		buffer[1] = buffer[1] + (buffer[1] >> crush << crush) * -1;
		else
		buffer[1] = buffer[1] >> crush << crush;
		buffer += 2;
	}
#endif /*DISABLE_DSP_SUPPORT*/
}

void SwapStereo(signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
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
#endif /*DISABLE_DSP_SUPPORT*/
}

void MonoMixdown(signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
	unsigned int i;
	signed long mixdown;
	for(i = 0; i < length; i++)
	{
		mixdown = (buffer[0] + buffer[1]) / 2;
		if (mixdown > 32767)
		{
			mixdown = 32767;
		}
		else if (mixdown < -32768)
		{
			mixdown = -32768;
		}
		buffer[0] = (short)mixdown;
		buffer[1] = (short)mixdown;
		buffer += 2;
	}
#endif /*DISABLE_DSP_SUPPORT*/
}

void SurroundSoundLeft(signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
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
#endif /*DISABLE_DSP_SUPPORT*/
}

void SurroundSoundRight(signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
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
#endif /*DISABLE_DSP_SUPPORT*/
}

void LimitOutput(signed long limit, signed short *buffer, unsigned int length)
{
#ifndef DISABLE_DSP_SUPPORT
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
			buffer[0] = (short)limit * -1;
		}
		if (buffer[1] > limit)
		{
			buffer[1] = (short)limit;
		}
		else if (buffer[1] < limit * -1)
		{
			buffer[1] = (short)limit * -1;
		}
		buffer += 2;
	}
#endif /*DISABLE_DSP_SUPPORT*/
}
