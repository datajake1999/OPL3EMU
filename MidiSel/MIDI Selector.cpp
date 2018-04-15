#define UNICODE
#define _UNICODE

#include <windows.h>
#include <winuser.h>
#include <commctrl.h>
#include <mmsystem.h>

#include <tchar.h>

#include "resource.h"

#define APPNAME _T("MIDI Selector v.1.0.1 by Steven Don")
#define CLASSNAME _T("MIDISelector")

//Tell Visual C++ to link to comctl32.lib and winmm.lib (do this yourself if using another compiler)
#pragma comment (lib, "comctl32.lib")
#pragma comment (lib, "winmm.lib")

//Names of registry keys
const TCHAR g_keyVista32 [] = _T("Software\\Microsoft\\ActiveMovie\\devenum\\{4EFE2452-168A-11D1-BC76-00C04FB9453B}\\Default MidiOut Device");
const TCHAR g_keyVista64 [] = _T("Software\\Microsoft\\ActiveMovie\\devenum 64-bit\\{4EFE2452-168A-11D1-BC76-00C04FB9453B}\\Default MidiOut Device");
const TCHAR g_keyWin7 [] = _T("Software\\Microsoft\\Windows\\CurrentVersion\\MultiMedia\\MIDIMap");

//Convenience functions
int g_dluX, g_dluY;
inline int dlu2px_x (int x) { return x * g_dluX / 4; }
inline int dlu2px_y (int y) { return y * g_dluY / 8; }

//Handles to GUI objects
WPARAM g_hFont = NULL;
HWND g_hSelect = NULL;
UINT g_numDevices = 0, g_curDevice = 0;
MIDIOUTCAPS *g_ptrDevices = NULL;

void LoadMIDIDeviceData ()
{
	HKEY hkey = NULL;

	//Count the devices
	g_numDevices = midiOutGetNumDevs ();

	//Load the current index (used on Windows Vista)
	UINT idx = 0;
	if (RegOpenKeyEx (HKEY_CURRENT_USER, g_keyVista32, 0, KEY_QUERY_VALUE, &hkey) == ERROR_SUCCESS)
	{
		DWORD size = sizeof (idx);
		DWORD type = 0;
		if (RegQueryValueEx (hkey, _T("MidiOutId"), NULL, &type, reinterpret_cast<LPBYTE>(&idx), &size) == ERROR_SUCCESS)
		{
			//Must be a DWORD
			if (type != REG_DWORD)
			{
				//Some other data - ignore it
				idx = 0;
			} else {
				//Must be within range
				if (idx >= g_numDevices) idx = 0;
			}
		}
		RegCloseKey (hkey);
	}
	g_curDevice = idx;

	//Load the device name (used on Windows 7)
	TCHAR curDevice [MAXPNAMELEN] = { 0 };
	if (RegOpenKeyEx (HKEY_CURRENT_USER, g_keyWin7, 0, KEY_QUERY_VALUE, &hkey) == ERROR_SUCCESS)
	{
		DWORD size = sizeof (curDevice);
		DWORD type = 0;
		RegQueryValueEx (hkey, _T("szPname"), NULL, &type, reinterpret_cast<LPBYTE>(curDevice), &size);
		if (type != REG_SZ)
		{
			//Non-string data - ignore it
			memset (curDevice, 0, sizeof (curDevice));
		}
		RegCloseKey (hkey);
	}

	//Get the data one each device
	g_ptrDevices = new MIDIOUTCAPS [g_numDevices];
	for (UINT i = 0; i < g_numDevices; ++i)
	{
		midiOutGetDevCaps (i, g_ptrDevices + i, sizeof (MIDIOUTCAPS));

		//Let the name override the index
		if (!_tcsncmp (curDevice, g_ptrDevices [i].szPname, MAXPNAMELEN))
		{
			g_curDevice = i;
		}
	}
}

void SetMIDIDevice (UINT idx)
{
	HKEY hkey = NULL;

	//Set the current index (used on Windows Vista)
	if (RegOpenKeyEx (HKEY_CURRENT_USER, g_keyVista32, 0, KEY_SET_VALUE, &hkey) == ERROR_SUCCESS)
	{
		//Windows Media Player uses this 32-bit version even on 64-bit Windows
		RegSetValueEx (hkey, _T("MidiOutId"), NULL, REG_DWORD, reinterpret_cast<LPBYTE>(&idx), sizeof (idx));
		RegCloseKey (hkey);
	}
	if (RegOpenKeyEx (HKEY_CURRENT_USER, g_keyVista64, 0, KEY_SET_VALUE, &hkey) == ERROR_SUCCESS)
	{
		//Programs such as the 64-bit version of MPC-HC do check the 64-bit key
		RegSetValueEx (hkey, _T("MidiOutId"), NULL, REG_DWORD, reinterpret_cast<LPBYTE>(&idx), sizeof (idx));
		RegCloseKey (hkey);
	}

	//Set the device name (used on Windows 7)
	if (RegOpenKeyEx (HKEY_CURRENT_USER, g_keyWin7, 0, KEY_SET_VALUE, &hkey) == ERROR_SUCCESS)
	{
		RegSetValueEx (hkey, _T("szPname"), NULL, REG_SZ, reinterpret_cast<LPBYTE>(g_ptrDevices [idx].szPname), MAXPNAMELEN * sizeof (TCHAR));
		RegCloseKey (hkey);
	}
}

LRESULT CALLBACK WinProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE :
		{
			//Create the selection list and caption
			HWND hCaption = CreateWindowEx (
				0,
				_T("Static"),
				_T("Default MIDI output device:"),
				WS_CHILD | WS_VISIBLE,
				dlu2px_x (7),
				dlu2px_y (7),
				dlu2px_x (173),
				dlu2px_y (8),
				hwnd,
				NULL,
				NULL,
				NULL
			);
			SendMessage (hCaption, WM_SETFONT, g_hFont, 0);

			g_hSelect = CreateWindowEx (
				0,
				_T("COMBOBOX"),
				NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | WS_TABSTOP,
				dlu2px_x (7),
				dlu2px_y (16),
				dlu2px_x (173),
				dlu2px_y (59),
				hwnd,
				NULL,
				NULL,
				NULL
			);
			SendMessage (g_hSelect, WM_SETFONT, g_hFont, 0);
			for (UINT i = 0; i < g_numDevices; ++i)
			{
				SendMessage (g_hSelect, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(g_ptrDevices [i].szPname));
			}

			//Create buttons
			HWND hOK = CreateWindowEx (
				0,
				_T("BUTTON"),
				_T("&Apply"),
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
				dlu2px_x (75),
				dlu2px_y (35),
				dlu2px_x (50),
				dlu2px_y (14),
				hwnd,
				reinterpret_cast<HMENU>(IDOK),
				NULL,
				NULL
			);
			SendMessage (hOK, WM_SETFONT, g_hFont, 0);

			HWND hCancel = CreateWindowEx (
				0,
				_T("BUTTON"),
				_T("&Quit"),
				WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				dlu2px_x (130),
				dlu2px_y (35),
				dlu2px_x (50),
				dlu2px_y (14),
				hwnd,
				reinterpret_cast<HMENU>(IDCANCEL),
				NULL,
				NULL
			);
			SendMessage (hCancel, WM_SETFONT, g_hFont, 0);

			//Select the current device and focus it
			SendMessage (g_hSelect, CB_SETCURSEL, g_curDevice, 0);
			SetFocus (g_hSelect);
		}
		return 0;

	case WM_CLOSE :
		PostQuitMessage (0);
		return 0;

	case WM_COMMAND :
		{
			int id = LOWORD (wParam);
			if (id == IDCANCEL)
			{
				PostQuitMessage (0);
			} else if (id == IDOK)
			{
				//Determine which device has been selected
				int idx = SendMessage (g_hSelect, CB_GETCURSEL, 0, 0);

				//Store it to the registry
				SetMIDIDevice (idx);

				//Inform the user
				MessageBox (
					hwnd,
					_T("Any open programs making use of the MIDI subsystem will need to be restarted to pick up the change in settings."),
					_T("Default MIDI output device changed"),
					MB_OK | MB_ICONINFORMATION
				);
			}
		}
		return 0;
	}
	return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

int DoInterface (HINSTANCE hInstance)
{
	InitCommonControls ();

	//Load the MIDI configuration from the registry
	LoadMIDIDeviceData ();

	//Initialise the window class
	WNDCLASS wc = {
		0,													//style
		WinProc,											//lpfnWndProc
		0,													//cbClsExtra
		0,													//cbWndExtra
		hInstance,											//hInstance
		LoadIcon (hInstance, MAKEINTRESOURCE(IDI_MAIN)),	//hIcon
		LoadCursor (NULL, IDC_ARROW),						//hCursor
		(HBRUSH)(COLOR_BTNFACE + 1),						//hbrBackground
		NULL,												//lpszMenuName
		CLASSNAME											//lpszClassName
	};
	if (!RegisterClass (&wc)) return 1;

	//Use the default GUI font (which oddly enough isn't default)
	g_hFont = reinterpret_cast<WPARAM>(GetStockObject (DEFAULT_GUI_FONT));

	//Determine how large a DLU is to get some nice dimensions
	g_dluX = LOWORD (GetDialogBaseUnits ());
	g_dluY = HIWORD (GetDialogBaseUnits ());

	//Create the actual window
	HWND hwnd = CreateWindowEx (
		WS_EX_CONTROLPARENT,
		CLASSNAME,
		APPNAME,
		WS_BORDER | WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT,				//Coordinates
		0,
		dlu2px_x (186) + 2 * GetSystemMetrics (SM_CXBORDER),
		dlu2px_y (55) + GetSystemMetrics (SM_CYCAPTION) + 2 * GetSystemMetrics (SM_CYBORDER),
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd) return 2;
	ShowWindow (hwnd, SW_SHOW);

	//Run the message pump
	MSG msg;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage (hwnd, &msg))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}

	//All done
	return msg.wParam;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCommandLine, int cmdShow)
{
	return DoInterface (hInstance);
}