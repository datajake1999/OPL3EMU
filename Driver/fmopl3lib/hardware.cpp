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

#include "hardware.h"
#include "opl_hw.h"
#include "opl_lpt.h"

static char *hwsupport = getenv("OPLHWSUPPORT");

void hardware_Init() 
{
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_Hardware_Detection();
			OPL_HW_Init();
		}
		if (strstr(hwsupport, "-lpt"))
		{
			OPL_LPT_Init();
		}
	}
};

void hardware_WriteReg(unsigned short reg, unsigned char data) {
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_HW_WriteReg(reg, data);
		}
		if (strstr(hwsupport, "-lpt"))
		{
			opl_lpt_write(reg, data);
		}
	}
}

void hardware_Close()
{
	if (hwsupport)
	{
		if (strstr(hwsupport, "-on"))
		{
			OPL_HW_Close();
		}
		if (strstr(hwsupport, "-lpt"))
		{
			OPL_LPT_Close();
		}
	}
};
