[Setup]
AppName=OPL3EMU MIDI Driver
AppVerName=OPL3EMU MIDI Driver
DefaultDirName={pf}\OPL3EMU
DefaultGroupName=OPL3EMU
AllowNoIcons=yes
OutputBaseFilename=OPL3EMU
Compression=lzma
SolidCompression=yes
LicenseFile=Docs\COPYING.LESSER.TXT
;InfoAfterFile=log.txt

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"
Name: ba; MessagesFile: "compiler:Languages\Basque.isl"
Name: br; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: ca; MessagesFile: "compiler:Languages\Catalan.isl"
Name: cz; MessagesFile: "compiler:Languages\Czech.isl"
Name: da; MessagesFile: "compiler:Languages\Danish.isl"
Name: nl; MessagesFile: "compiler:Languages\Dutch.isl"
Name: fi; MessagesFile: "compiler:Languages\Finnish.isl"
Name: fr; MessagesFile: "compiler:Languages\French.isl"
Name: de; MessagesFile: "compiler:Languages\German.isl"
Name: he; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: hu; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: it; MessagesFile: "compiler:Languages\Italian.isl"
Name: ja; MessagesFile: "compiler:Languages\Japanese.isl"
Name: no; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: pl; MessagesFile: "compiler:Languages\Polish.isl"
Name: pt; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: ru; MessagesFile: "compiler:Languages\Russian.isl"
Name: se; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: se2; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: sl; MessagesFile: "compiler:Languages\Slovak.isl"
Name: sl2; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: sp; MessagesFile: "compiler:Languages\Spanish.isl"
Name: uk; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Files]
Source: "Driver\mingw\Apogee\opl3apogee.dll"; DestDir: "{app}\Apogee"; Components: "Apogee"
Source: "Driver\opl3apogee.inf"; DestDir: "{app}\Apogee"; Components: "Apogee"
Source: "Installer\mingw\Apogee\drvsetup.exe"; DestDir: "{app}\Apogee"; Components: "Apogee"
Source: "Driver\mingw\Doom\opl3doom.dll"; DestDir: "{app}\Doom"; Components: "Doom"
Source: "Driver\opl3doom.inf"; DestDir: "{app}\Doom"; Components: "Doom"
Source: "Installer\mingw\Doom\drvsetup.exe"; DestDir: "{app}\Doom"; Components: "Doom"
Source: "Driver\mingw\Doom_ext\opl3doom_ext.dll"; DestDir: "{app}\Doom_Ext"; Components: "Doom_Ext"
Source: "Driver\opl3doom_ext.inf"; DestDir: "{app}\Doom_Ext"; Components: "Doom_Ext"
Source: "Installer\mingw\Doom_ext\drvsetup.exe"; DestDir: "{app}\Doom_Ext"; Components: "Doom_Ext"
Source: "GENMIDI\dmx_dmx.op2"; DestDir: "C:\OPLSynth"; DestName: "GENMIDI.op2"; Components: "Doom Doom_Ext"; Flags: onlyifdoesntexist uninsneveruninstall
Source: "Driver\mingw\Windows\opl3windows.dll"; DestDir: "{app}\Windows"; Components: "Windows"
Source: "Driver\opl3windows.inf"; DestDir: "{app}\Windows"; Components: "Windows"
Source: "Installer\mingw\Windows\drvsetup.exe"; DestDir: "{app}\Windows"; Components: "Windows"
Source: "Installer\install.bat"; DestDir: "{app}\Apogee"; Components: "Apogee"
Source: "Installer\install.bat"; DestDir: "{app}\Doom"; Components: "Doom"
Source: "Installer\install.bat"; DestDir: "{app}\Doom_Ext"; Components: "Doom_Ext"
Source: "Installer\install.bat"; DestDir: "{app}\Windows"; Components: "Windows"
Source: "MidiSel\mingw\MidiSel.exe"; DestDir: "{app}"; Components: "MidiSel"
Source: "OPL3EMU_CFG\mingw\OPL3EMU_CFG.exe"; DestDir: "{app}"; Components: "Configuration"
Source: "Apogee_TMB\*"; DestDir: "{app}\Apogee_TMB"; Components: "Patches_Apogee"
Source: "GENMIDI\*"; DestDir: "{app}\GENMIDI"; Components: "Patches_Doom"
Source: "MIDI_Samples\*"; DestDir: "{app}\MIDI_Samples"; Components: "MIDI_Samples"
Source: "Docs\COPYING*"; DestDir: "{app}\Docs"; Components: "Docs"
Source: "Docs\README.TXT"; DestDir: "{app}\Docs"; Components: "Docs"; Flags: isreadme

[Registry]
Root: HKCU; Subkey: "Software\Microsoft\ActiveMovie\devenum\{{4EFE2452-168A-11D1-BC76-00C04FB9453B}\Default MidiOut Device"; Components: "MidiSel"
Root: HKCU; Subkey: "Software\Microsoft\Windows\CurrentVersion\MultiMedia\MIDIMap"; Components: "MidiSel"

[Run]
Filename: "{app}\Apogee\install.bat"; Flags: runhidden; Components: "Apogee"
Filename: "{app}\Doom\install.bat"; Flags: runhidden; Components: "Doom"
Filename: "{app}\Doom_Ext\install.bat"; Flags: runhidden; Components: "Doom_Ext"
Filename: "{app}\Windows\install.bat"; Flags: runhidden; Components: "Windows"
Filename: "{app}\MidiSel"; Description: "{cm:LaunchProgram,MIDI Selector}"; Components: "MidiSel"; Flags: postinstall nowait unchecked
Filename: "{app}\OPL3EMU_CFG"; WorkingDir: "{app}"; Description: "{cm:LaunchProgram,OPL3EMU MIDI Driver Configuration Utility}"; Components: "Configuration"; Flags: postinstall nowait unchecked

[UninstallRun]
Filename: "{app}\Apogee\drvsetup"; Parameters: "uninstall"; Flags: runhidden; Components: "Apogee"
Filename: "{app}\Doom\drvsetup"; Parameters: "uninstall"; Flags: runhidden; Components: "Doom"
Filename: "{app}\Doom_Ext\drvsetup"; Parameters: "uninstall"; Flags: runhidden; Components: "Doom_Ext"
Filename: "{app}\Windows\drvsetup"; Parameters: "uninstall"; Flags: runhidden; Components: "Windows"

[UninstallDelete]
Type: files; Name: "{app}\drvsetup.log"

[Components]
Name: "Apogee"; Description: "Apogee Driver"; Types: "full"
Name: "Doom"; Description: "Doom Driver"; Types: "full"
Name: "Doom_Ext"; Description: "Extended Doom Driver"; Types: "full"
Name: "Windows"; Description: "Windows Driver"; Types: "full"
Name: "MidiSel"; Description: "MIDI Selector"; Types: "full"; MinVersion: 6.0,6.0
Name: "Configuration"; Description: "OPL3EMU MIDI Driver Configuration Utility"; Types: "full"
Name: "Patches_Apogee"; Description: "Custom Patches for Apogee Driver"; Types: "full"
Name: "Patches_Doom"; Description: "Custom Patches for Doom Driver"; Types: "full"
Name: "MIDI_Samples"; Description: "Sample MIDI Files"; Types: "full"
Name: "Docs"; Description: "Documentation"; Types: "full"

[Tasks]
Name: desktopicon; Description: "{cm:CreateDesktopIcon}"

[Icons]
Name: "{group}\MIDI Selector"; Filename: "{app}\MidiSel.exe"; Components: "MidiSel"
Name: "{group}\OPL3EMU MIDI Driver Configuration Utility"; Filename: "{app}\OPL3EMU_CFG.exe"; WorkingDir: "{app}"; Components: "Configuration"
Name: "{commondesktop}\MIDI Selector"; Filename: "{app}\MidiSel.exe"; Tasks: desktopicon; Components: "MidiSel"
Name: "{commondesktop}\OPL3EMU MIDI Driver Configuration Utility"; Filename: "{app}\OPL3EMU_CFG.exe"; WorkingDir: "{app}"; Tasks: desktopicon; Components: "Configuration"
Name: "{group}\Readme"; Filename: "{app}\Docs\README.TXT"; Components: "Docs"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"

[Code]
function InitializeSetup: Boolean;
var
  Version: TWindowsVersion;
begin
  GetWindowsVersionEx(Version);
  if Version.NTPlatform = False then
  begin
    SuppressibleMsgBox('This software only runs on Windows NT platforms.',
      mbCriticalError, MB_OK, MB_OK);
    Result := False;
    Exit;
  end;
  Result := True;
end;
