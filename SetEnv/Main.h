#ifndef _HDR_TestConsole_H
#define _HDR_TestConsole_H

	// Skeleton code for a simple console application

	/* History
		1.06 [New] - (Jan 14, 2007) - Added dynamic expansion support (same as using ~ with setx)
			- Originally requested by Andre Amaral
			- Further Request by Synetech (http://www.codeproject.com/tools/SetEnv.asp?df=100&forumid=230498&select=1808287#xx1808287xx)
		1.05 [New] - (Sep 06, 2006) - Added support to prepend (rather than append) a value to an expanded string 
			- Requested by Masuia (See http://www.codeproject.com/tools/SetEnv.asp)
		1.04 [New] - (May 30, 2006) - Added support for User environment variables.
		1.03 [Fix] - (Apr 20, 2006) - Bug fix in ProcessWinXP() discovered by attiasr 
			- See (http://www.codeguru.com/Cpp/W-P/win32/tutorials/comments.php/c10849/?thread=8491.
		1.01 [Fix] - (Nov 15, 2005) - Bug fix in IsWinME() discovered by frankd 
			- (http://www.codeguru.com/Cpp/W-P/win32/tutorials/comments.php/c10849/?thread=8491.
		1.00 [New] - (Oct 29, 2005) - Initial Public Release.
	*/

	// License - Free for any purpose, just do not remove the copyright
	// Copyright (C) 1997-2007 - Jonathan Wilkes

#ifndef _WINDOWS_
	#include <windows.h>
#endif

#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <strsafe.h> // Must be last include

namespace xfc
{
const int ERR_SUCCESS = 0;
const int ERR_ERROR = 1;
const int ERR_ACCESS_DENIED = 5;

const int i98_BUFFERLEN = 30;

	// Our output routine for displaying messages to the console window
void Output(LPCTSTR pBuff);

	// Outputs a message to stderr
void OutputErr(LPCTSTR pBuff);

	// Display a system error message to the console window
void DisplaySysError(LPCTSTR pszBuff, DWORD dwErr);
}

#endif // _HDR_TestConsole_H
