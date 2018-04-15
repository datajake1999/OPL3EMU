
#include "vgm_logging.h"

//static const double FMToVGMSamples = 0.887038377986966;
static const long double FMToVGMSamples = ((long double)44100.0 / 49716.0);

static VGM_HEADER VGMHead;
static DWORD ClockAdd, VGMSmplPlayed, SamplesBeforeLoop, LoopMarker;
static DWORD LastPBSample, LastVgmSmpl;
static FILE *hFileVGM = NULL;
//static WCHAR TempLogPath[BUFSIZ];

typedef struct
{
   UINT8
      CmdChip,
      RegMSB,
      RegLSB;
} vgmcmd_t;

void VGMLog_Init()
{
   LastVgmSmpl = 0;
   LastPBSample = 0;
   //VGMSmplPlayed = 0;
   LoopMarker = 0;
   SamplesBeforeLoop = 0;

   memset(&VGMHead, 0x00, sizeof(VGM_HEADER));
   /*switch(DROInf.iHardwareType)
   {
   case 0x00:	// Single OPL2 Chip
      VGMHead.lngHzYM3812 = 3579545;
      break;
   case 0x01:	// Dual OPL2 Chip
      VGMHead.lngHzYM3812 = 3579545 | 0xC0000000;
      break;
   case 0x02:	// Single OPL3 Chip*/
      VGMHead.lngHzYMF262 = 14318180;
      /*break;
   default:
      VGMHead.lngHzYM3812 = 3579545 | 0x40000000;
      break;
   }*/
		

   //if (OPL_CHIPS > 1)
   //   ClockAdd = 0x40000000;
   //else
   //   ClockAdd = 0x00;
   VGMHead.fccVGM = FCC_VGM;
   VGMHead.lngVersion = 0x00000151;
   VGMHead.lngEOFOffset = 0xC0;
   VGMHead.lngDataOffset = sizeof(VGM_HEADER) - 0x34;
   //if (VGMHead.lngHzYM3526)
   //   VGMHeadL.lngHzYM3526 = VGMHead.lngHzYM3526 | ClockAdd;
   //if (VGMHead.lngHzYM3812)
   //   VGMHeadL.lngHzYM3812 = VGMHead.lngHzYM3812 | ClockAdd;
   if (VGMHead.lngHzYMF262)
      VGMHead.lngHzYMF262 = VGMHead.lngHzYMF262 | ClockAdd;

   if (hFileVGM == NULL)
   {
		CreateDirectory("C:\\OPLSynth", NULL);
		LPCTSTR lpPath = TEXT("C:\\OPLSynth\\opl3vgmlog.vgm");
		if (PathFileExists(lpPath) == FALSE)
		{
			hFileVGM = fopen(lpPath, "wb");
		}
		else
		{
			for (int i = 0; i >= 0; i++)
			{
				char filename[100];
				sprintf(filename, "C:\\OPLSynth\\opl3vgmlog%d.vgm", i);
				if (PathFileExists(filename) == FALSE)
				{
					hFileVGM = fopen(filename, "wb");
					break;
				}
			}
		}

//      ExpandEnvironmentStringsW(L"%TEMP%\\opl3vgmlog.vgm", (LPWSTR)&TempLogPath, BUFSIZ);
//      hFileVGM = _wfopen(TempLogPath, L"wb");
   
      //strcpy_s(TempLogPath, getenv("TEMP"));
      //hFileVGM = fopen(TempLogPath, "wb");

      if (hFileVGM == NULL)
      {
         //hFileVGM = NULL;
         MessageBoxW(NULL, L"Handle for opl3vgmlog.vgm failed.", L"VGM Logger", MB_OK | MB_ICONEXCLAMATION);
         return;
      }
      
   } else
      rewind(hFileVGM);

   fwrite(&VGMHead, 0x01, sizeof(VGM_HEADER), hFileVGM);

   // TODO hax my anus
   fputc(0x5F, hFileVGM);
   fputc(0x05, hFileVGM);
   fputc(0x01, hFileVGM);
   fputc(0x5E, hFileVGM);
   fputc(0x04, hFileVGM);
   fputc(0x60, hFileVGM);
}

inline void VGMLog_FlushWait()
{
   DWORD CurPBSmpl, CurVGMSmpl;
   DWORD DelayDiff;//, CurTime;
	WORD WrtDly;
	
   if (hFileVGM == NULL) 
      return;

   // Save current time before processing
   //CurTime = VGMSmplPlayed;
   CurPBSmpl = LastPBSample;	// multithreading safety
   CurVGMSmpl = (DWORD)floor(FMToVGMSamples * CurPBSmpl + 0.5);
   DelayDiff = CurVGMSmpl - LastVgmSmpl;
   LastVgmSmpl = CurVGMSmpl;

	//DelayDiff = CurTime - LastVgmDelay;
   //DelayDiff = (DWORD)floor((FMToVGMSamples * (CurTime - LastVgmDelay) + 0.5));
   //DelayDiff = (DWORD)(FMToVGMSamples * CurTime - FMToVGMSamples * LastVgmDelay);

   // Write long waits
	while(DelayDiff)
	{
		if (DelayDiff > 0xFFFF)
         WrtDly = 0xFFFF;
		else
			WrtDly = (WORD)DelayDiff;

		fputc(0x61, hFileVGM);
		fwrite(&WrtDly, 0x02, 0x01, hFileVGM);
		DelayDiff -= WrtDly;
	}
	//LastVgmDelay = CurTime;	//PlayingTime;
}

// helper function
inline void VGMLog_CmdWrite(BYTE Cmd, BYTE Reg, BYTE Data)
{
   if (hFileVGM == NULL) 
      return;

   // Save current time before processing
   VGMLog_FlushWait();

	fputc(Cmd, hFileVGM);
	if (Cmd == 0x66)  // EOF
		return;
	fputc(Reg, hFileVGM);
	fputc(Data, hFileVGM);
	
	return;
}

void VGMLog_IncrementSamples(int len)
{
   if (hFileVGM == NULL)
      return;
   //VGMSmplPlayed += (DWORD)(len * FMToVGMSamples);
   LastPBSample += len;
}

DWORD VGMLog_CountSamplesFromOffset(DWORD offset)
{
   vgmcmd_t cmdBuf;
   DWORD DelayCount = 0;

   if (hFileVGM == NULL)
      return ~0;

   fseek(hFileVGM, offset, SEEK_SET);
   
   while (!feof(hFileVGM))
   {
      if (fread(&cmdBuf, sizeof(vgmcmd_t), 0x01, hFileVGM))
         break;

      // Assuming all commands logged (except for EOF)
      switch (cmdBuf.CmdChip)
      {
         case 0x62:	// 1/60s delay
				DelayCount += 735;
				break;
			case 0x63:	// 1/50s delay
				DelayCount += 882;
				break;
			case 0x61:	// xx Sample Delay
         {
            WORD delayVal;
				memcpy(&delayVal, &cmdBuf.RegMSB, 0x02);
            DelayCount += delayVal;
				break;
         }

         default:  // ignore all other commands
            break;
      }
   }

   return DelayCount;
}

//Stop the logger
void VGMLog_Close()
{
   DWORD TotalSamples = LastVgmSmpl;
      //TotalSamplesConv = (DWORD)floor(VGMSmplPlayed * FMToVGMSamples + 0.5),
      //VGMSamplesRecount;
   
   if (hFileVGM == NULL) 
      return;

   VGMLog_CmdWrite(0x66, 0x00, 0x00);
   TotalSamples = LastVgmSmpl;

   //fputc(0x66, hFileVGM);
   UINT32 AbsVol = (UINT32)(ftell(hFileVGM) - 0x04);
   fseek(hFileVGM, 0x04, SEEK_SET);
   fwrite(&AbsVol, sizeof(UINT32), 0x01, hFileVGM);
   
   // Recount samples (needed due to cumulative rounding errors from 49716 -> 44100)
   //  - no longer necessar..  thanks ValleyBell!
   //TotalSamples = VGMLog_CountSamplesFromOffset(sizeof(VGM_HEADER));

   // Write VGM total sample count
   fseek(hFileVGM, 0x18, SEEK_SET);
   fwrite(&TotalSamples, 0x04, 0x01, hFileVGM);

   // Write VGM loop sample count
   if (LoopMarker > 0)
   {
      //DWORD LoopSamples = (DWORD)floor(((TotalSamples - SamplesBeforeLoop) * FMToVGMSamples) + 0.5);
      DWORD LoopSamples = (DWORD)(TotalSamples - SamplesBeforeLoop);
      //DWORD LoopSamples = VGMLog_CountSamplesFromOffset(LoopMarker);

      //DWORD LoopSamples = (DWORD)floor((TotalSamplesConv - (SamplesBeforeLoop * FMToVGMSamples)) + 0.5);
      fseek(hFileVGM, 0x1C, SEEK_SET);
      fwrite(&LoopMarker, 0x04, 0x01, hFileVGM);
      fwrite(&LoopSamples, 0x04, 0x01, hFileVGM);
   }

   fclose(hFileVGM);
   hFileVGM = NULL;

#ifdef _DEBUG
   MessageBoxW(NULL, L"File opl3vgmlog.vgm saved.", L"VGM Logger", MB_OK | MB_ICONINFORMATION);
#endif //_DEBUG
}

void VGMLog_MarkLoopStartNow()
{
   if (hFileVGM == NULL) 
      return;

   //SamplesBeforeLoop = (DWORD)floor(VGMSmplPlayed * FMToVGMSamples + 0.5);
   VGMLog_FlushWait();
   SamplesBeforeLoop = LastVgmSmpl;
   LoopMarker = (DWORD)(ftell(hFileVGM) - 0x1C);
}

/*OPL_Write() / adlib_wite() etc. guide
static inline void OPL_Write(BYTE ChipID, WORD Register, BYTE Data)
{
	//if (ChipID >= OPL_VCHIPS)
	//{
	//	if (ErrMsg && ! SkipMode)
	//		printf("Illegal Chip Write!\n");
	//	return;
	//}
	
	BYTE RegSet;
	WORD RegAddr;
	
	RegAddr = (ChipID << 8) | Register;
	RegAddr %= OPL_VCHIPS << 8;
   switch(OPL_MODE)
   {
   case 0x01:	// OPL 1
      ym3526_w(ChipID, 0x00, Register & 0xFF);
      ym3526_w(ChipID, 0x01, Data);
      if (LogVGM)
         VGMLog_CmdWrite(0x5B + ChipID * 0x50, Register & 0xFF, Data);
      break;
   case 0x02:	// OPL 2
      ym3812_w(ChipID, 0x00, Register & 0xFF);
      ym3812_w(ChipID, 0x01, Data);
      if (LogVGM)
         VGMLog_CmdWrite(0x5A + ChipID * 0x50, Register & 0xFF, Data);
      break;
   case 0x03:	// OPL 3
      RegSet = Register >> 8;
      RegSet |= (ChipID & 0x01);
      ChipID >>= 1;
      
      ymf262_w(ChipID, 0x00 | (RegSet << 1), Register & 0xFF);d
      ymf262_w(ChipID, 0x01 | (RegSet << 1), Data);
      if (LogVGM)
         VGMLog_CmdWrite((0x5E | RegSet) + ChipID * 0x50, Register & 0xFF, Data);
      break;
   }
}*/