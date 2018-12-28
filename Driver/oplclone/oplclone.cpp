#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "..\interface.h"
fm_chip *chip;

void writeopl(int r, int v)
{
	chip->fm_writereg(r, v);
}

int main(int argc, char *argv[])
{
	unsigned int samplerate = 49716;
	short *buffer = new short[20 * samplerate];
	chip = getchip();
	chip->fm_init(samplerate);
	printf("Set patch\n");
	writeopl(0x20, 0x03);
	writeopl(0x23, 0x01);
	writeopl(0x40, 0x2f);
	writeopl(0x43, 0x00);
	writeopl(0x61, 0x10);
	writeopl(0x63, 0x10);
	writeopl(0x80, 0x00);
	writeopl(0x83, 0x00);
	writeopl(0xa0, 0x44);
	writeopl(0xb0, 0x12);
	writeopl(0xc0, 0xfe);
	printf("Start voice\n");
	writeopl(0xb0, 0x32);
	Sleep(1);
	writeopl(0x60, 0xf0);
	chip->fm_generate(buffer, samplerate*10);
	printf("If you hear sine wave you have a real OPL3 or very accurate clone,\notherwise you have OPL clone.\nPress any key to close program.\n");
	getch();
	chip->fm_close();
	delete chip;
	chip = NULL;
	delete buffer;
	buffer = NULL;
	return 0;
}
