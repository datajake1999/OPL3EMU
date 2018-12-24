cl -c ..\Main.cpp ..\Regkey.cpp
rc ..\SetEnv.rc
copy ..\SetEnv.RES SetEnv.RES
del ..\SetEnv.RES
link *.obj SetEnv.RES advapi32.lib bufferoverflowU.lib kernel32.lib user32.lib /OUT:SetEnv.exe
del *.obj SetEnv.RES
