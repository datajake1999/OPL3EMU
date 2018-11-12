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

void SetCrushAmount(unsigned int amount);
void SetCrushAmountEnv();
void RectangleDither(signed short *buffer, unsigned int length);
void TriangleDither(signed short *buffer, unsigned int length);
void GaussianDither(signed short *buffer, unsigned int length);
void BitCrush(signed short *buffer, unsigned int length);
void SwapStereo(signed short *buffer, unsigned int length);
void MonoMixdown(signed short *buffer, unsigned int length);
void SurroundSoundLeft(signed short *buffer, unsigned int length);
void SurroundSoundRight(signed short *buffer, unsigned int length);
void LimitOutput(signed short limit, signed short *buffer, unsigned int length);

#endif //BITCRUSH_H