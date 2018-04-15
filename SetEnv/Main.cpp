#include "Main.h"
#include "RegKey.h"
#include "OSVersion.h"

using namespace xfc;

	// The registry location under 2000/XP/etc. where environment variables are stored
const TCHAR szREG_SYSTEM[] = _T("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"); // System Variables (HKEY_LOCAL_MACHINE)
const TCHAR szREG_USER[] = _T("Environment"); // User Variables (HKEY_CURRENT_USER)

	// Our output routines for displaying messages to the console window or to stderr
/*lint -e534 -e537 */
void xfc::Output(LPCTSTR pBuff)
{
	if(!pBuff) return;

	OutputDebugString(pBuff);

#if _MSC_VER >= 1300 // Visual Studio.NET (2003 and above)
	std::wcout << pBuff;
#else
	std::cout << pBuff;
#endif
}

void xfc::OutputErr(LPCTSTR pBuff)
{
	if(!pBuff) return;

	OutputDebugString(pBuff);

#if _MSC_VER >= 1300 // Visual Studio.NET (2003 and above)
	std::wcout << pBuff;
#else
	std::cout << pBuff;
#endif
}

	// Display a system error message to the console window
void xfc::DisplaySysError(LPCTSTR pszBuff, DWORD dwErr)
{
	TCHAR szBuff[_MAX_PATH];
	memset(szBuff, 0, sizeof(szBuff));

	StringCchPrintfEx(szBuff, _MAX_PATH, NULL, NULL, STRSAFE_IGNORE_NULLS, "Error - %s : ", pszBuff);

		// Get the system error message
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
		, NULL, dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);

	StringCchCat(szBuff, _MAX_PATH, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);

	OutputErr((LPCTSTR)szBuff);
}

void ShowCopyright()
{
	Output(_T("\r\nSetEnv - Version 1.08 - Copyright (C) 2005-2007 - Jonathan Wilkes\r\n\r\n"));
}

	// Display the application's usage information

	// Now supports dynamic mode.
	// Sets the new variable to be equal to the value of the %MEDIADIR% variable even if the MEDIADIR variable changes:
	// E.g
	//		setenv -a MEDIADIR D:\Media				// MEDIADIR = D:\Media
	//		setenv -a MUSICDIR ~MEDIADIR~\Music		// MUSICDIR = D:\Media\Music (i.e. %MEDIADIR%\Music)
    //		setenv -a MEDIADIR C:\Media				// MUSICDIR = C:\Media\Music
void Usage(bool bError = true)
{
	ShowCopyright();

	if(bError)
	{
		Output(_T("Allows you to set/update/delete User or System Environment Variables, e.g. PATH.\r\n"));
		Output(_T("For Windows 9x/NT/2000/XP/S2K3/Vista\r\n\r\n"));
		Output(_T("Usage: SetEnv -<options> <name> <value>\r\n\r\n"));

		Output(_T("Options (Default is System variable, add -u for User):\r\n"));
		Output(_T("\tSetEnv -a name value \t\tSet the variable to the specified value\r\n"));
		Output(_T("\tSetEnv -a name %value \t\tAdd a value to an expanded variable\r\n"));
		Output(_T("\tSetEnv -ap name %value \t\tPrepend a value to an expanded variable\r\n"));
		Output(_T("\tSetEnv -d name\t\t\tDelete the variable\r\n"));
		Output(_T("\tSetEnv -d name %value\t\tDelete the value from the expanded variable\r\n"));
		Output(_T("\tSetEnv -ua name\t\t\tAdd a USER environment variable\r\n"));
		Output(_T("\tSetEnv -ud name\t\t\tDeletes a USER environment variable\r\n"));
		Output(_T("\tSetEnv -e\t\t\tShow examples of using SetEnv\r\n\r\n"));

		Output(_T("Return Values:\r\n"));
		Output(_T("\t0\t\tSuccess\r\n"));
		Output(_T("\t5\t\tAccess Denied\r\n"));
		Output(_T("\t1\t\tOther Error (Error messages go to stderr)\r\n\r\n"));

		Output(_T("Notes:\r\n"));
		Output(_T("\tIf you want to create an expanded variable with multiple values, e.g. PATH\r\n"));
		Output(_T("\tspecify the value with a preceeding '%' character, e.g. SetEnv PATH %d:\\Bin\r\n"));
		Output(_T("\r\n\tUse double quotes around any value which contains spaces.\r\n\r\n"));
	}
}

void ShowExamples()
{
	ShowCopyright();

	Output(_T("Examples:\r\n\r\n"));

	Output(_T("setenv -ua INSTALLPATH C:\\SetEnv \r\n\tSets the value of INSTALLPATH to \"C:\\SetEnv\" in the USER environment.\r\n\r\n"));

	Output(_T("setenv -a PATH %D:\\Bin \r\n\tAdds \"D:\\Bin\" to the current PATH, will create PATH if necessary.\r\n\r\n"));

	Output(_T("setenv -a MEDIA C:\\Media \r\n\tSets the value of MEDIA to \"C:\\Media\" in the MACHINE environment.\r\n\r\n"));

	Output(_T("setenv -a MUSIC ~MEDIA~\\Music \r\n\tSets the value of MUSIC to be ALWAYS equal to the value of MEDIA\\Music,\r\n"));
	Output(_T("\teven if the value of MEDIA changes, so MUSIC becomes \"C:\\Media\\Music\".\r\n"));
	Output(_T("\tIf MEDIA becomes \"D:\\Media\" then MUSIC becomes \"D:\\Media\\Music\", etc.\r\n"));
}

bool IsWindows9x() // Is this windows 95/98 or ME ?
{
	OSVersion osVer;

	if(osVer.IsWin95() || osVer.IsWin98() || osVer.IsWinME())
		return true;

	return false;
}

	// Find a string value within an expanded string, returns the offset if found, else string::npos
	// We need to match the entire string, so that we can match '3' in the following
	// 1,2,33,3 and not match the 33
string::size_type FindValueInExpandedString(const string& szData, const string& szSearch, string::size_type iValueIndex)
{
	if(szData.empty())
		return string::npos;

	bool bCompleted = false;
	size_t iValueOffset = 0;
	string szTmpVal;

	if(iValueIndex > 0)
		iValueOffset = iValueIndex;
	else
		iValueIndex = string::npos;

	while(!bCompleted)
	{
		if(iValueOffset >= szData.length())
		{
			bCompleted = true;
			continue;
		}

		string::size_type iTmpIndex = szData.find(";", iValueOffset);

		if(iTmpIndex != string::npos)
			szTmpVal = szData.substr(iValueOffset, iTmpIndex - iValueOffset); // Grab up to the next seperator
		else
			szTmpVal = szData.substr(iValueOffset, szData.length()); // Grab up to the end of the line

		if(szTmpVal == szSearch) // Found it so stop searching
		{
			iValueIndex = iValueOffset;
			bCompleted = true;
			continue;
		}

		iValueOffset += szTmpVal.length() + 1; // Move to the next entry
	}

	return iValueIndex;
}

	// Replace ALL '~' chars with '%')
string DynamicCheckAndReplace(const string& szValue, bool& expand)
{
	string tmpVal = szValue;

	string::size_type index = tmpVal.find("~");

	if(index != string::npos)
		expand = true;

	while(index != string::npos)
	{
		tmpVal.replace(index, 1, "%");
		index = tmpVal.find("~");
	}

	return tmpVal;
}

	// Sets either a USER or a SYSTEM enviroment variable (Win 2000 and above)
	// And the value can be a normal string or an expanded string, e.g. PATH
bool SetRegistryKey(RegKey& obKey, bool bSystem, bool bExpandedStr, const string& szName, const string& szValue)
{
	bool bRetVal = false;

    if(bExpandedStr)
		bRetVal = obKey.SetKeyValueEx(((bSystem)? szREG_SYSTEM : szREG_USER), szName.c_str(), szValue.c_str(), (DWORD)szValue.length(), true, false, ((bSystem)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER));
	else
		bRetVal = obKey.SetKeyValue(((bSystem)? szREG_SYSTEM : szREG_USER), szName.c_str(), szValue.c_str(), (DWORD)szValue.length(), true, false, ((bSystem)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER));

	return bRetVal;
}

	// Sets either a USER or a SYSTEM enviroment variable (Win 2000 and above)
	// And the value can be a normal string or an expanded string, e.g. PATH
bool DeleteRegistryKey(RegKey& obKey, bool bSystem, const string& szName)
{
	return obKey.DeleteKeyValue(((bSystem)? szREG_SYSTEM : szREG_USER), szName.c_str(), false, ((bSystem)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER));
}

/*lint -e774 */
int ProcessWinXP(const string& szName, string& szValue, bool bAddValue, bool bSystemValue, bool bPrepend) // Process WinNT/2000 and XP
{
		// Bugfix for problem found by attiasr
		// http://www.codeproject.com/tools/SetEnv.asp#xx1454198xx
		// Original code corrupted the destination value if it exceeded _MAX_PATH as I was using
		// a static buffer size, the buffer is now dynamic.

		// Get the size of the current registry value
	RegKey obKey;
	DWORD dwSize = obKey.GetSizeOfValue(((bSystemValue)? szREG_SYSTEM : szREG_USER), szName.c_str(), ((bSystemValue)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER));

	string::size_type iLen = szValue.size();

	DWORD iTotalLength = dwSize + iLen + 1;
	TCHAR* pszRegkey = new TCHAR[iTotalLength];
	memset(pszRegkey, 0, iTotalLength);

	bool bExpandedString = false;

		// Pre-process the string (i.e. is it expanded or dynamic)
		// Is this an expanded string ?
	if(szValue[0] == '%')
	{
		szValue = szValue.substr(1, szValue.length() - 1); // Remove the % character
		bExpandedString = true;
	}

		// If this is a dynamic string, i.e. contains "~PATH~", then replace ALL '~' chars with '%')
	szValue = DynamicCheckAndReplace(szValue, bExpandedString);

		// Does the value already exist ?
	bool bExists = obKey.GetKeyValue(((bSystemValue)? szREG_SYSTEM : szREG_USER), szName.c_str(), pszRegkey, iTotalLength, false, ((bSystemValue)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER));
	if(bExists)
	{
			// Already exists, so we need to modify it or delete it
			// First, check the type of value, i.e. REG_SZ or REG_EXPAND_SZ as we need to process them differently
		if(obKey.OpenKey(((bSystemValue)? szREG_SYSTEM : szREG_USER), false, ((bSystemValue)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER)))
		{
			DWORD dwLen = 0;
			DWORD dwType = REG_SZ;
			if(obKey.QueryValue(szName.c_str(), dwLen, dwType))
			{
				if(dwType == REG_EXPAND_SZ)
					bExpandedString = true;
			}

			obKey.CloseKey();
		}

		if(bAddValue) // Add the value to the registry
		{
			if(bExpandedString)
			{
				string szOriginalValue = pszRegkey;

					// Does it already contain our new value ?
				size_t iValueIndex = 0;
				string::size_type index = FindValueInExpandedString(szOriginalValue, szValue, iValueIndex);
				if(index == string::npos) // Did we find it ?
				{
					string szNewValue; // No, so add it

					if(szOriginalValue.length() > 0)
					{
							// We may need to add a semi colon seperator if the last character of the original value is not a semi colon
						if(bPrepend)
							szNewValue = szValue + ";" + szOriginalValue; // Add semi colon
						else
						{
							if(szOriginalValue[szOriginalValue.length() - 1] != ';')
								szNewValue = szOriginalValue + ";" + szValue; // Add semi colon
							else
								szNewValue = szOriginalValue + szValue; // Do not add the semi colon
						}
					}
					else
						szNewValue = szValue;

					if(!SetRegistryKey(obKey, bSystemValue, true, szName, szNewValue))
					{
						DisplaySysError("Set Value", obKey.GetLastErrorCode()); // Failed
						delete [] pszRegkey; pszRegkey = NULL;
						return (obKey.GetLastErrorCode() == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
					}
				}
			}
			else // Just overwrite it
			{
				if(!SetRegistryKey(obKey, bSystemValue, bExpandedString, szName, szValue))
				{
					DisplaySysError("Set Value", obKey.GetLastErrorCode()); // Failed
					delete [] pszRegkey; pszRegkey = NULL;
					return (obKey.GetLastErrorCode() == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
				}
			}
		}
		else // Delete the entry
		{
			if(szValue.length() == 0 || !bExpandedString) // Delete the whole key
			{
				if(!obKey.DeleteKeyValue(((bSystemValue)? szREG_SYSTEM : szREG_USER), szName.c_str(), false, ((bSystemValue)? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER)))
				{
					DisplaySysError("Delete Value", obKey.GetLastErrorCode()); // Failed
					delete [] pszRegkey; pszRegkey = NULL;
					return (obKey.GetLastErrorCode() == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
				}
			}
			else
			if(bExpandedString) // We need to delete our bit only and leave the rest of the value alone
			{
				string szOriginalValue = pszRegkey;

				size_t iValueIndex = 0;
				string::size_type index = FindValueInExpandedString(szOriginalValue, szValue, iValueIndex);
				if(index != string::npos) // Did we find it ?
				{
						// We should only delete our value if it actually exists in the environment variable
					string szNewValue;

					if(szOriginalValue[index + szValue.length()] == ';') // Any terminating ; to remove ?
						szNewValue = szOriginalValue.replace(index, szValue.length() + 1, "");
					else
						szNewValue = szOriginalValue.replace(index, szValue.length(), "");

					if(szNewValue.empty())
						DeleteRegistryKey(obKey, bSystemValue, szName);
					else
					if(!SetRegistryKey(obKey, bSystemValue, true, szName, szNewValue))
					{
						DisplaySysError("Delete Value", obKey.GetLastErrorCode()); // Failed
						delete [] pszRegkey; pszRegkey = NULL;
						return (obKey.GetLastErrorCode() == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
					}
				}
			}
		}
	}
	else // Value does NOT exist yet so create it
	{
		if(bAddValue)
		{
			bool bOK = SetRegistryKey(obKey, bSystemValue, bExpandedString, szName, szValue);

			if(!bOK)
			{
				DisplaySysError("Set Value", obKey.GetLastErrorCode()); // Failed
				delete [] pszRegkey; pszRegkey = NULL;
				return (obKey.GetLastErrorCode() == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
			}
		}
	}

		// Tell the system that we have changed a setting (can take 5 seconds to return)
	DWORD_PTR dwReturnValue = 0;
	SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) "Environment", SMTO_ABORTIFHUNG, 5000, &dwReturnValue);

	delete [] pszRegkey; pszRegkey = NULL;
	return ERR_SUCCESS;
}
/*lint +e774 */

/*lint -e732 -e774 -e776 -e834 */
int ProcessWin9x(const string& szName, string& szValue, bool bAddValue) // Process Win95/Win98 and Win ME
{
		// Open the Autoexec.bat file and see if the environment variable already exists
	WIN32_FIND_DATA obFindFileData;
	memset(&obFindFileData, 0, sizeof(WIN32_FIND_DATA));
	
	TCHAR szBuffer[i98_BUFFERLEN] = {'\0'};

		// Get the location of the "autoexec.bat" file folder
	StringCchCopy(szBuffer, i98_BUFFERLEN, _T("c:\\autoexec.bat"));

	bool bFound = false;
	bool bCDrive = true; // Did we find this file on the C: drive ?

    HANDLE hFind = FindFirstFile(szBuffer, &obFindFileData);
    if(hFind != INVALID_HANDLE_VALUE) // Did we find any matching files ?
		bFound = true;
	else // Try the D: drive
	{
		StringCchCopy(szBuffer, i98_BUFFERLEN, _T("d:\\autoexec.bat"));
		hFind = FindFirstFile(szBuffer, &obFindFileData);
		if(hFind != INVALID_HANDLE_VALUE) // Did we find any matching files ?
		{
			bFound = true;
			bCDrive = false; // Found on the D: drive
		}
	}

	if(hFind != INVALID_HANDLE_VALUE)
		FindClose(hFind);
	hFind = NULL;

	bool bExpandedString = false; // This is an expanded string variable (with several values), e.g. PATH = 1;2;3;4

	if(bFound) // Did we find the autoexec.bat file ?
	{
		string szPath;
		if(bCDrive)
			szPath = _T("c:\\autoexec.bat");
		else
			szPath = _T("d:\\autoexec.bat");
		
		HANDLE hFile = CreateFile(szPath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//		HANDLE hFile = CreateFile(szPath.c_str(), FILE_READ_DATA | FILE_WRITE_DATA | FILE_APPEND_DATA | STANDARD_RIGHTS_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
				// We are going to read the entire file in and then parse it
			TCHAR* pszData = new TCHAR[obFindFileData.nFileSizeLow + 1];
			if(pszData)
			{
				memset(pszData, 0, obFindFileData.nFileSizeLow + 1);

				DWORD dwBytes = 0;

				if(obFindFileData.nFileSizeLow > 0)
				{
					if(!ReadFile(hFile, pszData, obFindFileData.nFileSizeLow, &dwBytes, NULL)) // Read the entire file in one go
					{
						DWORD dwErrVal = GetLastError();
						DisplaySysError("Open Autoexec.bat", dwErrVal); // Failed
						delete [] pszData; pszData = NULL;
						return (dwErrVal == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
					}
				}

				string szOriginalValue = pszData;
				string szNewValue;

					// Pre-process the string (i.e. is it expanded or dynamic)
					// Is this an expanded string ?
				if(szValue[0] == '%')
				{
					szValue = szValue.substr(1, szValue.length() - 1); // Remove the % character
					bExpandedString = true;
				}

					// If this is a dynamic string, i.e. contains "~PATH~", then replace ALL '~' chars with '%')
				szValue = DynamicCheckAndReplace(szValue, bExpandedString);

				if(dwBytes == 0) // If the file is empty, just write the new value (if necessary)
				{
					if(bAddValue)
					{
						if(bExpandedString)
							szNewValue = _T("set ") + szName + _T("=%") + szName + _T("%;") + szValue + _T("\r\n");
						else
							szNewValue = _T("set ") + szName + _T("=") + szValue + _T("\r\n");

						if(!WriteFile(hFile, (LPVOID) szNewValue.c_str(), (DWORD)szNewValue.length(), &dwBytes, NULL))
						{
							DWORD dwErrVal = GetLastError();
							DisplaySysError("Writing to Autoexec.bat", dwErrVal); // Failed
							delete [] pszData; pszData = NULL;
							return (dwErrVal == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
						}
					}

					CloseHandle(hFile); hFile = NULL;
					delete [] pszData; pszData = NULL;
					return ERR_SUCCESS;
				}
				else
				{
						// We need to break the file up into seperate lines
					ULONGLONG ulFileLen = szOriginalValue.length();

					TCHAR szFullLine[_MAX_PATH] = {'\0'};
					TCHAR* pBase = (TCHAR*)szOriginalValue.c_str();
					size_t iOffset = 0; // Offset into the file
					size_t iLength = 0;
					bool bDone = false;
					bool bVariableFound = false; // true if the variable already exists in the autoexec.bat file
					bool bValueFound = false; // true if our value is already set

					string::size_type iValueIndex = string::npos;

					while(!bDone && !bVariableFound)
					{
						if(iOffset >= ulFileLen) // Finished
						{
							bDone = true;
							continue;
						}

						TCHAR* pEndOfLine = (TCHAR*)_tcschr(szOriginalValue.c_str() + iOffset, '\n'); // Find the end of the line

						if(pEndOfLine == NULL) // No end of line, so assume only a single line file
							iLength = _tcslen(pBase); // Calculate the length of the line
						else
							iLength = pEndOfLine - (pBase + iOffset); // Calculate the length of the line

						memset(szFullLine, 0, _MAX_PATH * sizeof(TCHAR));
						StringCchCopy(szFullLine, min(iLength, _MAX_PATH), pBase + iOffset); // Take a copy of the line
						
							// Only process valid lines
						if(iLength > 1)
						{
							string szTmp = szFullLine;
							string szSearch = "set " + szName;
							string::size_type index = szTmp.find(szSearch);
							if(index != string::npos) // Is this the line we want ?
							{
								bVariableFound = bDone = true;

								index = szTmp.find(";");
								if(index != string::npos) // Did the value contain a ';' character
									bExpandedString = true;

								continue;
							}
						}

						iOffset += (iLength + 1); // Step over the line + the end of line character
					}

					if(bVariableFound) // Did we find the variable name in the autoexec file ?
					{
							// Yes, Does it already contain our value ?
						string szTmp = szFullLine;
						iValueIndex = szTmp.find(szValue.c_str());
						if(iValueIndex != string::npos) // Did we find it ?
						{
								// We need to match the entire string, so that we can match '3' in the following
								// 1,2,33,3 and not match the 33
							string szTmpVal;

							if(bExpandedString) // Search through the expanded string
							{
								iValueIndex = FindValueInExpandedString(szTmp, szValue, iValueIndex);
								if(iValueIndex != string::npos)
								{
									bValueFound = true;
									szTmpVal = szTmp.substr(iValueIndex, szValue.length());
								}
							}
							else
							{
								szTmpVal = szTmp.substr(iValueIndex, szTmp.length());
								if(szTmpVal == szValue)
									bValueFound = true;
							}
						}
					}

						// Decide what we need to process based on what we found
					if(bAddValue) // Attempt to add the variable
					{
						if(!bVariableFound) // Not set already, so just write it
						{
								// Is this an expanded string ?
							if(bExpandedString)
								szNewValue = _T("set ") + szName + _T("=%") + szName + _T("%;") + szValue + _T("\r\n");
							else
								szNewValue = _T("set ") + szName + _T("=") + szValue + _T("\r\n");
						}
						else
						{
							if(!bValueFound) // Value is not set
							{
									// Reconstruct the contents of the file, adding our new value to the existing variable
									// Done using pointer manipulation and copying of substrings
								szNewValue = szOriginalValue.substr(0, iOffset); // Copy everything up to the line we are interested in

								string szTmp;
								if(bExpandedString)
								{
										// We may need to add a semi colon seperator if the last character of the original value is not a semi colon
									string szTmpFullLine = szFullLine;
									if(szTmpFullLine[szTmpFullLine.length() - 1] != ';')
										szTmp = szTmpFullLine + ";" + szValue; // Add semi colon
									else
										szTmp = szTmpFullLine + szValue; // Do not add the semi colon
								}
								else
									szTmp = "set " + szName + "=" + szValue; // Set the new value

								szNewValue += szTmp;

									// Copy everything after the the line we are interested in
								if((iOffset + iLength) <= ulFileLen)
									szNewValue += szOriginalValue.substr(iOffset + iLength - 1, (string::size_type)(ulFileLen - (iOffset + iLength) + 2));
							}
						}
					}
					else // Attempt to delete
					{
						if(bVariableFound)
						{
							if(szValue.length() == 0 || !bExpandedString) // No value specified, so delete the entire variable
							{
									// Reconstruct the contents of the file, adding our new value to the existing variable
									// Done using pointer manipulation and copying of substrings
								szNewValue = szOriginalValue.substr(0, iOffset); // Copy everything up to the line we are interested in

									// Copy everything after the the line we are interested in
								if(iOffset + iLength <= ulFileLen)
									szNewValue += szOriginalValue.substr(iOffset + iLength + 1, (string::size_type)(ulFileLen - (iOffset + iLength)));
							}
							else
							if(bExpandedString)
							{
									// Remove the specified value from the variable
								string szTmp;

								if(szOriginalValue[iOffset + iValueIndex + szValue.length()] == ';') // Any terminating ; to remove ?
									szTmp = szOriginalValue.replace(iOffset + iValueIndex, szValue.length() + 1, "");
								else
									szTmp = szOriginalValue.replace(iOffset + iValueIndex, szValue.length(), "");

								szNewValue += szTmp;
							}
						}
					}

						// Write any changes to the file
					if(!szNewValue.empty())
					{
						if(bAddValue && !bVariableFound)
							SetFilePointer(hFile, 0, 0, FILE_END); // Move to the END of the file
						else
							SetFilePointer(hFile, 0, 0, FILE_BEGIN); // Move to the START of the file

						if(!WriteFile(hFile, (LPVOID) szNewValue.c_str(), (DWORD)szNewValue.length(), &dwBytes, NULL))
						{
							DWORD dwErrVal = GetLastError();
							DisplaySysError("Updating Autoexec.bat", dwErrVal); // Failed
							delete [] pszData; pszData = NULL;
							return (dwErrVal == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
						}

						SetEndOfFile(hFile);
					}
				}

				delete [] pszData; pszData = NULL;
			}
			else
				return ERR_ERROR;

			CloseHandle(hFile); hFile = NULL;
		}
		else
		{
			DWORD dwErrVal = GetLastError();
			DisplaySysError("Open Autoexec.bat", GetLastError()); // Failed
			return (dwErrVal == 0x05) ? ERR_ACCESS_DENIED : ERR_ERROR;
		}
	}
	else
	{
		Output(_T("Failed to locate Autoexec.bat on c:\\ or d:\\ ")); // Failed
		return ERR_ERROR;
	}

	return ERR_SUCCESS;
}
/*lint +e732 +e774 +e776 +e834 */

	// Our main entry point
/*lint -e818 */
int main(int argc, char** argv)
{
	if(argc < 2 || argc > 5) // Did they specify enough arguments ?
	{
		Usage();
		return -1;
	}
   
		// Default our options
	bool bSystemValue = true; // Default to system variable (/u = user)
	bool bAddValue = true; // Default to ADD
	bool bPrepend = false; // Default is to append value, if this is true then prepend instead

	string szName; // The name of the variable to set
	string szValue; // The value
	string szErr; // The error to display if any

		// Process the command line arguments
	for(int i = 1; i <= argc; ++i)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/')) // Switch
		{
			if(_tcschr(argv[i], 'h') || _tcschr(argv[i], '?')) // Help
			{
				Usage();
				return 0;
			}

			if(_tcschr(argv[i], 'e')) // Examples
			{
				ShowExamples();
				return 0;
			}

			if(_tcschr(argv[i], 'u'))
				bSystemValue = false; // User variable

			if(_tcschr(argv[i], 'a')) // Add variable / value
				bAddValue = true;

			if(_tcschr(argv[i], 'd')) // Delete variable / value
				bAddValue = false;

				// Prepend new value to existing expanded variable, default is to append
				// So normally 'c:\bin;NEW VALUE' with -p 'NEW VALUE;c:\bin'
				// Not supported on Win9x
			if(_tcschr(argv[i], 'p'))
				bPrepend = true;
		}
		else // Option
		{
			int iCnt = argc - i; // How many remaining args ?
			if(iCnt > 0) // Did we get the parameters we wanted ?
			{
					// Extract the remaining options, i.e. name and value (if any)
				szName = argv[i];

				if(iCnt == 2)
					szValue = argv[i + 1]; 
			}
			else
				szErr = "Error: You need to specify a name and/or a value.\r\n";

			break; // We do not want to go back through the loop
		}
	}

	if(bAddValue && szValue.empty()) // User forgot to add the value
		szErr = "Error: When adding a variable you MUST specify a name and value.\r\n";

	if(!szErr.empty()) // Show any errors
	{
		Usage(false);
		OutputErr(szErr.c_str());
		return 1;
	}

		// Now, update the environment variable as necessary
	if(IsWindows9x()) // On Windows 95/98/Me, we need to modify AUTOEXEC.BAT to set environment variables, then reboot
		return ProcessWin9x(szName, szValue, bAddValue);
	else // Win NT/2000/XP, etc.
		return ProcessWinXP(szName, szValue, bAddValue, bSystemValue, bPrepend);
}
/*lint +e534 +e537 +e818 */
