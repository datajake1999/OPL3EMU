//
// Copyright (C) 2018 Datajake
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#ifndef EMULATOR_H
#define EMULATOR_H

void emulator_Init(unsigned int rate);
void emulator_WriteReg(unsigned short reg, unsigned char data);
void emulator_Generate(signed short *buffer, unsigned int length);

#endif /*EMULATOR_H*/