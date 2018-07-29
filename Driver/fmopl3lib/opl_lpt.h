#ifndef OPL_LPT_H
#define OPL_LPT_H

#include "InpOut32Helper.h"

void opl_lpt_reset(void);
void opl2lpt_write(char reg, char data);
void opl3lpt_write(int reg, char data);
void OPL_LPT_Init();
void OPL_LPT_Close();

#endif /*OPL_LPT_H*/