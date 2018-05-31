/*
* OPL Hardware Passthrough support functions
* (C) 2013-2014 James Alan Nguyen
* Original code adapted from MidiPlay/VGMPlay (C) 201X ValleyBell
* 
* Released under LGPL
*/

#include "opl_hw.h"

BYTE OPL_MODE = 0x03;
BYTE OPL_CHIPS = 0x01;
INT64 HWusTime;
char *hwport = getenv("OPL3PORT");
WORD FMPort;

void OPL_Hardware_Detection(void)
{
#ifndef DISABLE_HW_SUPPORT
	BYTE Status1;
	BYTE Status2;
	//LARGE_INTEGER TempQud1;
	//LARGE_INTEGER TempQud2;
	LARGE_INTEGER TempQudFreq;
	//__int64 TempQudMid;
	
	HWusTime = 0;

	Status1 = OpenInpOut32();
	
	if (Status1)
	{
		OPL_MODE = 0x00;
		MessageBoxW(NULL, L"Error opening FM Port! Permission denied!", L"OPL3_HW", MB_OK | MB_ICONEXCLAMATION);
		goto FinishDetection;
	}
	
	OPL_MODE = 0x02;	// must be set to activate OPL2-Delays
	
	// OPL2 Detection
	OPL_HW_WriteReg(0x04, 0x60);
	OPL_HW_WriteReg(0x04, 0x80);
	Status1 = OPL_HW_GetStatus();
	Status1 &= 0xE0;
	
	OPL_HW_WriteReg(0x02, 0xFF);
	OPL_HW_WriteReg(0x04, 0x21);
	OPL_HW_WaitDelay(0, 80);
	
	Status2 = OPL_HW_GetStatus();
	Status2 &= 0xE0;
	
	OPL_HW_WriteReg(0x04, 0x60);
	OPL_HW_WriteReg(0x04, 0x80);
	
	if (! ((Status1 == 0x00) && (Status2 == 0xC0)))
	{
		// Detection failed
		OPL_MODE = 0x00;
		printf("No OPL Chip detected!\n");
		goto FinishDetection;
	}
	
	// OPL3 Detection
	Status1 = OPL_HW_GetStatus();
	Status1 &= 0x06;
	if (! Status1)
	{
		OPL_MODE = 0x03;
		OPL_CHIPS = 0x01;
		printf("OPL 3 Chip found.\n");
		goto FinishDetection;
	}
	
	// OPL2 Dual Chip Detection
	OPL_HW_WriteReg(0x104, 0x60);
	OPL_HW_WriteReg(0x104, 0x80);
	Status1 = OPL_HW_GetStatus();
	Status1 &= 0xE0;
	
	OPL_HW_WriteReg(0x102, 0xFF);
	OPL_HW_WriteReg(0x104, 0x21);
	OPL_HW_WaitDelay(0, 80);
	
	Status2 = OPL_HW_GetStatus();
	Status2 &= 0xE0;
	
	OPL_HW_WriteReg(0x104, 0x60);
	OPL_HW_WriteReg(0x104, 0x80);
	
	if ((Status1 == 0x00) && (Status2 == 0xC0))
	{
		OPL_CHIPS = 0x02;
		printf("Dual OPL 2 Chip found.\n");
	}
	else
	{
		OPL_CHIPS = 0x01;
		printf("OPL 2 Chip found.\n");
	}
	
FinishDetection:
	// note CPU time needed for 1 us
	QueryPerformanceFrequency(&TempQudFreq);
	HWusTime = TempQudFreq.QuadPart / 1000000;
	
	/*QueryPerformanceCounter(&TempQud1);
	OPL_HW_GetStatus();
	QueryPerformanceCounter(&TempQud2);
	TempQudMid = TempQud2.QuadPart - TempQud1.QuadPart;
	
	QueryPerformanceCounter(&TempQud1);
	OPL_HW_GetStatus();
	QueryPerformanceCounter(&TempQud2);
	TempQudMid += TempQud2.QuadPart - TempQud1.QuadPart;
	
	HWusTime = TempQudMid / 2;
	printf("Port Read Cycles: %I64u\tMSec Cycles: %I64u\n", HWusTime,
			TempQudFreq.QuadPart / 1000);
	printf("us per ms: %I64u\n", TempQudFreq.QuadPart / (HWusTime * 1000));
	HWusTime = TempQudFreq.QuadPart / 1000000;*/
	
	CloseInpOut32();

#endif /*DISABLE_HW_SUPPORT*/
	return;
}


void OPL_HW_WriteReg(WORD Reg, BYTE Data)
{
#ifndef DISABLE_HW_SUPPORT
	if (hwport)
	{
		if (strstr(hwport, getenv("OPL3PORT")))
		{
			FMPort = strtoul(hwport, 0, 16);
		}
	}
	else
	{
		FMPort = 0x388;
	}
	UINT16 Port;
	LARGE_INTEGER StartTime;
	//UINT8 DataOld;
	//UINT8 OpNum;
	//UINT8 TempVol;
	//float TempSng;
	
	Reg &= 0x01FF;
	
	//if (SkipMode)
	//{
	//	OPLReg[Reg] = Data;
	//	return;
	//}
	
	// Register = Rhythm Control and RhmythmOn-Bit changed
	// -> set/reset Modulator Volume of Channels 7 and 8 (Volume for HH/CYM)
	//if (Reg == 0x0BD && (OPLReg[Reg] ^ Data) & 0x20 && FinalVol != 1.0f)
	//{
	//	OPLReg[Reg] = Data;
	//	OPLRegForce[Reg] = 0x01;
	//	
	//	OPL_HW_WriteReg(0x51, OPLReg[0x51]);	// Ch 7 Mod TL
	//	OPL_HW_WriteReg(0x52, OPLReg[0x52]);	// Ch 8 Mod TL
	//}
	
	/*
	DataOld = Data;
	if ((Reg & 0xE0) == 0x40)
	{
		OpNum = (Reg & 0x07) / 0x03;	// Modulator 0x00, Carrier 0x01
		TempVol = ((Reg & 0x18) >> 3) * 0x03 + ((Reg & 0x07) % 0x03);
		
		if ((OPLReg[(Reg & 0x100) | 0xC0 | TempVol] & 0x01))
			OpNum = 0x01;	// Additive Syntheses - affects final volume
		if (! (Reg & 0x100) && TempVol >= 0x07 && (OPLReg[0xBD] & 0x20))
			OpNum = 0x01;	// used as Volume for Rhythm: Hi-Hat / Cymbal
		if (OpNum == 0x01 && FinalVol != 1.0f)
		{
			TempVol = Data & 0x3F;
			TempSng = (float)pow(2.0, -TempVol / 8.0);
			TempSng *= FinalVol;
			if (TempSng > 0.0f)
				TempSng = (float)(-8.0 * log(TempSng) / log(2.0));
			else
				TempSng = 64.0f;
			if (TempSng < 0.0f)
				TempVol = 0x00;
			else if (TempSng >= 64.0f)
				TempVol = 0x3F;
			else
				TempVol = (UINT8)TempSng;
			
			Data = (Data & 0xC0) | TempVol;
		}
	}


	if (Data == DataOld && Data == OPLReg[Reg] && ! OPLRegForce[Reg])
		return;	// only write neccessary registers (avoid spamming)

*/
	//OPLReg[Reg] = DataOld;
	//OPLRegForce[Reg] = (Data != DataOld) ? 0x01 : 0x00;	// force next write
	
	Port = (Reg & 0x100) ? (FMPort + 0x02) : (FMPort + 0x00);
	
	// 1. Set Register
	// 2. wait some time (short delay)
	// 3. Write Data
	// 4. wait some time (long delay)

	QueryPerformanceCounter(&StartTime);
	outportb(Port + 0x00, Reg & 0xFF);
	
	//switch(OPL_MODE)
	//{
	//case 0x02:
	//	OPL_HW_WaitDelay(StartTime.QuadPart, DELAY_OPL2_REG);
	//	break;
	//case 0x03:
	OPL_HW_WaitDelay(StartTime.QuadPart, DELAY_OPL3_REG);
	//	break;
	//}

	QueryPerformanceCounter(&StartTime);
	outportb(Port + 0x01, Data);
	
	//switch(OPL_MODE)
	//{
	//case 0x02:
	//	OPL_HW_WaitDelay(StartTime.QuadPart, DELAY_OPL2_DATA);
	//	break;
	//case 0x03:
	OPL_HW_WaitDelay(StartTime.QuadPart, DELAY_OPL3_DATA);
	//	break;
	//}

#endif	// DISABLE_HW_SUPPORT
	
	return;
}

inline UINT8 OPL_HW_GetStatus(void)
{
#ifndef DISABLE_HW_SUPPORT
	if (hwport)
	{
		if (strstr(hwport, getenv("OPL3PORT")))
		{
			FMPort = strtoul(hwport, 0, 16);
		}
	}
	else
	{
		FMPort = 0x388;
	}
	UINT8 RetStatus;
	
	RetStatus = inportb(FMPort);
	
	return RetStatus;
#endif	// DISABLE_HW_SUPPORT
}


inline void OPL_HW_WaitDelay(INT64 StartTime, float Delay)
{
#ifndef DISABLE_HW_SUPPORT
	LARGE_INTEGER CurTime;
	INT64 EndTime;
	UINT16 CurUS;
	
	// waits Delay us
	if (HWusTime)
	{
		OPL_HW_GetStatus();	// read once, just to be safe
		EndTime = (INT64)(StartTime + HWusTime * Delay);
		do
		{
			QueryPerformanceCounter(&CurTime);
		} while(CurTime.QuadPart < EndTime);
	}
	else if (Delay >= 1.0f)
	{
		for (CurUS = 0x00; CurUS < Delay; CurUS ++)
		OPL_HW_GetStatus();
	}
	else
	{
		OPL_HW_GetStatus();	// read once, just to be safe
	}
#endif	// DISABLE_HW_SUPPORT

	return;
}

void opl_chip_reset(void)
{
#ifndef DISABLE_HW_SUPPORT
	UINT16 Reg;
	//float FnlVolBak;
	
	//FnlVolBak = FinalVol;
	//FinalVol = 1.0f;
	//memset(OPLRegForce, 0x01, 0x200);
	
	OPL_HW_WriteReg(0x105, 0x01);	// OPL3 Enable
	OPL_HW_WriteReg(0x001, 0x20);	// Test Register
	OPL_HW_WriteReg(0x002, 0x00);	// Timer 1
	OPL_HW_WriteReg(0x003, 0x00);	// Timer 2
	OPL_HW_WriteReg(0x004, 0x00);	// IRQ Mask Clear
	OPL_HW_WriteReg(0x104, 0x00);	// 4-Op-Mode Disable
	OPL_HW_WriteReg(0x008, 0x00);	// Keyboard Split
	
	// make sure all internal calulations finish sound generation
	for (Reg = 0x00; Reg < 0x09; Reg ++)
	{
		OPL_HW_WriteReg(0x0C0 | Reg, 0x00);	// silence all notes (OPL3)
		OPL_HW_WriteReg(0x1C0 | Reg, 0x00);
	}
	for (Reg = 0x00; Reg < 0x16; Reg ++)
	{
		if ((Reg & 0x07) >= 0x06)
		continue;
		OPL_HW_WriteReg(0x040 | Reg, 0x3F);	// silence all notes (OPL2)
		OPL_HW_WriteReg(0x140 | Reg, 0x3F);
		
		OPL_HW_WriteReg(0x080 | Reg, 0xFF);	// set Sustain/Release Rate to FASTEST
		OPL_HW_WriteReg(0x180 | Reg, 0xFF);
		OPL_HW_WriteReg(0x060 | Reg, 0xFF);
		OPL_HW_WriteReg(0x160 | Reg, 0xFF);
		
		OPL_HW_WriteReg(0x020 | Reg, 0x00);	// NULL the rest
		OPL_HW_WriteReg(0x120 | Reg, 0x00);
		
		OPL_HW_WriteReg(0x0E0 | Reg, 0x00);
		OPL_HW_WriteReg(0x1E0 | Reg, 0x00);
	}
	OPL_HW_WriteReg(0x0BD, 0x00);	// Rhythm Mode
	for (Reg = 0x00; Reg < 0x09; Reg ++)
	{
		OPL_HW_WriteReg(0x0B0 | Reg, 0x00);	// turn all notes off (-> Release Phase)
		OPL_HW_WriteReg(0x1B0 | Reg, 0x00);
		OPL_HW_WriteReg(0x0A0 | Reg, 0x00);
		OPL_HW_WriteReg(0x1A0 | Reg, 0x00);
	}
	
	// although this would be a more proper reset, it sometimes produces clicks
	/*for (Reg = 0x020; Reg <= 0x0FF; Reg ++)
		OPL_HW_WriteReg(Reg, 0x00);
	for (Reg = 0x120; Reg <= 0x1FF; Reg ++)
		OPL_HW_WriteReg(Reg, 0x00);*/
	
	// Now do a proper reset of all other registers.
	for (Reg = 0x040; Reg < 0x0A0; Reg ++)
	{
		if ((Reg & 0x07) >= 0x06 || (Reg & 0x1F) >= 0x18)
		continue;
		OPL_HW_WriteReg(0x000 | Reg, 0x00);
		OPL_HW_WriteReg(0x100 | Reg, 0x00);
	}
	for (Reg = 0x00; Reg < 0x09; Reg ++)
	{
		OPL_HW_WriteReg(0x0C0 | Reg, 0x30);	// must be 30 to make OPL2 VGMs sound on OPL3
		OPL_HW_WriteReg(0x1C0 | Reg, 0x30);	// if they don't send the C0 reg
	}
	
	//memset(OPLRegForce, 0x01, 0x200);
	//FinalVol = FnlVolBak;
#endif	// DISABLE_HW_SUPPORT
	
	return;
}

void OPL_HW_Init() 
{
#ifndef DISABLE_HW_SUPPORT
	opl_chip_reset();
	OpenInpOut32(); 
#endif	// DISABLE_HW_SUPPORT
};

void OPL_HW_Close()
{
#ifndef DISABLE_HW_SUPPORT
	opl_chip_reset();
	CloseInpOut32(); 
#endif	// DISABLE_HW_SUPPORT
};

