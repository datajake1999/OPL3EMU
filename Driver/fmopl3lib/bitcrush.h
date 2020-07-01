/*
Interface for bit crusher
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

#ifndef BITCRUSH_H
#define BITCRUSH_H

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct {
		unsigned int bits;
		unsigned int AutoDither;
		unsigned int OnlyError;
	} bitcrusher;

	void SetCrushAmount(bitcrusher *bc, unsigned int amount);
	unsigned int GetCrushAmount(bitcrusher *bc);
	void SetAutoDither(bitcrusher *bc, unsigned int val);
	unsigned int GetAutoDither(bitcrusher *bc);
	void SetOnlyError(bitcrusher *bc, unsigned int val);
	unsigned int GetOnlyError(bitcrusher *bc);
	void RectangleDither(bitcrusher *bc, signed short *buffer, unsigned int length);
	void TriangleDither(bitcrusher *bc, signed short *buffer, unsigned int length);
	void GaussianDither(bitcrusher *bc, signed short *buffer, unsigned int length);
	void BitCrush(bitcrusher *bc, signed short *buffer, unsigned int length);
	void SwapStereo(signed short *buffer, unsigned int length);
	void MonoMixdown(signed short *buffer, unsigned int length);
	void SurroundSoundLeft(signed short *buffer, unsigned int length);
	void SurroundSoundRight(signed short *buffer, unsigned int length);
	void LimitOutput(signed long limit, signed short *buffer, unsigned int length);
#ifdef __cplusplus
}
#endif

#endif //BITCRUSH_H