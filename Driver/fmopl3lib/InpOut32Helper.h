
#ifndef INPOUT32_HELPER_H
#define INPOUT32_HELPER_H

#ifndef _WIN32
#define DISABLE_HW_SUPPORT
#endif
#ifndef DISABLE_HW_SUPPORT
#include <stdio.h>
#include <windows.h>
#else
#include "types.h"
#endif /*DISABLE_HW_SUPPORT*/

BOOL OpenInpOut32(void);
void CloseInpOut32(void);
void outportb(unsigned short PortAddress, unsigned short Data);
unsigned char inportb(unsigned short PortAddress);

#endif /*INPOUT32_HELPER_H*/
