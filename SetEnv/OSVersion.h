#ifndef HDR_OSVERSION_INCLUDE
#define HDR_OSVERSION_INCLUDE

	// Class for identifying the Operating System Version

	// Version 3.10 (15th November)
	// License - Free for any purpose, just do not remove the copyright
	// Copyright (C) 1997-2006 - Jonathan Wilkes

	/* History
		v3.01	Bug fix in IsWinME() discovered by frankd (http://www.codeguru.com/Cpp/W-P/win32/tutorials/comments.php/c10849/?thread=8491)
		v3.00	Initial Public Release
	*/
	
#if !defined(STRICT)
	#define STRICT 1
#endif

	// Includes
#if !defined(_WINDOWS_)
	#include <windows.h>
#endif

#include <string>
using std::string;

namespace xfc
{
	class OSVersion
	{
	private:
		OSVERSIONINFO obVerInfo_;

	public:
			// Inline Constructor
		OSVersion()
		{ 
			obVerInfo_.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&obVerInfo_); 
		};

		inline DWORD GetMajorVersion() const { return obVerInfo_.dwMajorVersion; };
		inline DWORD GetMinorVersion() const { return obVerInfo_.dwMinorVersion; };
		inline DWORD GetBuildNumber() const { return obVerInfo_.dwBuildNumber; };

			// Returns a pointer to a null-terminated string that provides arbitrary additional information about the operating system, such as the Service Pack installed
		inline string GetVersionString() const { return string(obVerInfo_.szCSDVersion); };

			// Various OS methods
		inline bool IsWin32s() const { return obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32s ? true : false; } // Is this Win32s on Windows 3.1 ?

		inline bool IsWin95() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && (obVerInfo_.dwMajorVersion == 4) && (obVerInfo_.dwMinorVersion == 0)) ? true : false; } // Is this Windows 95 ?
		inline bool IsWinME() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && (obVerInfo_.dwMajorVersion == 4) && (obVerInfo_.dwMinorVersion == 90)) ? true : false; }; // Is this Windows ME ?
		inline bool IsWin98() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && (obVerInfo_.dwMajorVersion == 4) && (obVerInfo_.dwMinorVersion == 10)) ? true : false; } // Is this Windows 98 ?

		inline bool IsWinNT() const { return (IsWinNT351() || IsWinNT4()) ? true : false; } // Is this Windows NT ?
		inline bool IsWinNT351() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_NT) && (obVerInfo_.dwMajorVersion == 3) && (obVerInfo_.dwMinorVersion == 51)) ? true : false; }; // Is this Windows NT 3.51 ?
		inline bool IsWinNT4() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_NT) && (obVerInfo_.dwMajorVersion == 4) && (obVerInfo_.dwMinorVersion == 0)) ? true : false; }; // Is this Windows NT4 ?

		inline bool IsWin2000() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_NT) && (obVerInfo_.dwMajorVersion == 5) && (obVerInfo_.dwMinorVersion == 0)) ? true : false; } // Is this Windows 2000 ?
		inline bool IsWinXP() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_NT) && (obVerInfo_.dwMajorVersion == 5) && (obVerInfo_.dwMinorVersion == 1)) ? true : false; }; // Is this Windows XP ?
		inline bool IsWinServer2003() const { return ((obVerInfo_.dwPlatformId == VER_PLATFORM_WIN32_NT) && (obVerInfo_.dwMajorVersion == 5) && (obVerInfo_.dwMinorVersion == 2)) ? true : false; }; // Is this Windows Server 2003 ?
	};
} // End of namespace

#endif // HDR_OSVERSION_INCLUDE
