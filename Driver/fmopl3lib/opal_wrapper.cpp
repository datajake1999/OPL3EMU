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

#include "opal_wrapper.h"

void opal_wrapper::Init(unsigned int rate) {
	chip = new Opal(rate);
}

void opal_wrapper::WriteReg(unsigned short reg, unsigned char data) {
	chip->Port(reg, data);
}

void opal_wrapper::Generate(signed short *buffer, unsigned int len) {
	for(unsigned int i = 0; i < len; i++)
	{
		chip->Sample(buffer, buffer + 1);
		buffer += 2;
	}
}
