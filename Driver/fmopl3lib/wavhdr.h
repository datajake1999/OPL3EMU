/*
Wave header structure
*/

//just a quick hack, but it works...
#pragma pack(2)//this gave me a headache...
struct waveheader{
	UINT32 rID, rSize;
	UINT32 wID;
	UINT32 fID, fSize;
	UINT16 fFormat, fChannels;
	UINT32 fHertz, fBytesPerSec;
	UINT16 fBlockAlign, fBits, fSpecific;
	UINT32 dID, dSize;
};
#pragma pack()
