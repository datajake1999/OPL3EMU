cl ..\..\opl3windows_win32drv_setup.cpp ..\..\stdafx.cpp
link *.obj advapi32.lib bufferoverflowU.lib kernel32.lib user32.lib /OUT:drvsetup.exe
