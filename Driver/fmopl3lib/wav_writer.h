/*
Interface for WAV file writer
*/

#include <windows.h>
#include <stdio.h>
#ifndef WAV_WRITER_H
#define WAV_WRITER_H

#include "wavhdr.h"

void WavFileOpen(unsigned int rate);
void WavFileWrite(signed short*buffer, unsigned int length);
void WavFileClose();

#endif //WAV_WRITER_H