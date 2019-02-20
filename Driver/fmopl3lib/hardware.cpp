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

#ifndef DISABLE_HW_SUPPORT
static char *hwsupport = getenv("OPLHWSUPPORT");
#endif /*DISABLE_HW_SUPPORT*/

void hardware_Init() 
{
#ifndef DISABLE_HW_SUPPORT
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
#endif /*DISABLE_HW_SUPPORT*/
};

void hardware_WriteReg(unsigned short reg, unsigned char data) {
#ifndef DISABLE_HW_SUPPORT
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
#endif /*DISABLE_HW_SUPPORT*/
}

void hardware_Close()
{
#ifndef DISABLE_HW_SUPPORT
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
#endif /*DISABLE_HW_SUPPORT*/
};
