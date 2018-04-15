// license:GPL-2.0+
// copyright-holders:Jarek Burczynski
#ifndef MAME_SOUND_YMF262_H
#define MAME_SOUND_YMF262_H

#pragma once

/* select number of output bits: 8 or 16 */
#define OPL3_SAMPLE_BITS 16
/*
#if (OPL3_SAMPLE_BITS==16)
typedef int16_t OPL3SAMPLE;
#endif
#if (OPL3_SAMPLE_BITS==8)
typedef int8_t OPL3SAMPLE;
#endif
*/


void *ymf262_init(int clock, int rate);
void ymf262_post_load(void *chip);
void ymf262_shutdown(void *chip);
void ymf262_reset_chip(void *chip);
int  ymf262_write(void *chip, int a, int v);
void ymf262_write_reg(void *chip, int r, int v);
unsigned char ymf262_read(void *chip, int a);
int  ymf262_timer_over(void *chip, int c);
void ymf262_update_one(void *chip, short *buffers, int length);


#endif // MAME_SOUND_YMF262_H
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
