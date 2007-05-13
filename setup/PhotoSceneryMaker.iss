; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Photo Scenery Maker for FSX
AppVerName=Photo Scenery Maker for FSX 0.1
AppPublisher=Takuya Murakami
AppPublisherURL=http://scenerytools.sourceforge.net
AppSupportURL=http://scenerytools.sourceforge.net
AppUpdatesURL=http://scenerytools.sourceforge.net
DefaultDirName={pf}\Photo Scenery Maker for FSX
DefaultGroupName=Photo Scenery Maker for FSX
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
ShowLanguageDialog=yes
LicenseFile=D:\dev\scenerytools\PhotoSceneryMakerX\setup\license.txt

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\PhotoSceneryMakerX.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\default.po"; DestDir: "{app}"; Flags: ignoreversion
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\doc\*.html"; DestDir: "{app}\doc"; Flags: ignoreversion
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\doc\*.png"; DestDir: "{app}\doc"; Flags: ignoreversion
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\doc\*.gif"; DestDir: "{app}\doc"; Flags: ignoreversion
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\doc\*.css"; DestDir: "{app}\doc"; Flags: ignoreversion
Source: "d:\dev\SceneryTools\PhotoSceneryMakerX\locale\ja_JP\LC_MESSAGES\default.*o"; DestDir: "{app}\locale\ja_JP\LC_MESSAGES"; Flags: ignoreversion

[Icons]
Name: "{group}\Photo Scenery Maker for FSX"; Filename: "{app}\PhotoSceneryMakerX.exe"
Name: "{group}\{cm:UninstallProgram,Photo Scenery Maker for FSX}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Photo Scenery Maker for FSX"; Filename: "{app}\PhotoSceneryMakerX.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\PhotoSceneryMakerX.exe"; Description: "{cm:LaunchProgram,Photo Scenery Maker for FSX}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKCR; Subkey: ".psmx"; ValueType: string; ValueName: ""; ValueData: "PhotoSceneryMakerXProject"; Flags: uninsdeletevalue 

Root: HKCR; Subkey: "PhotoSceneryMakerXProject"; ValueType: string; ValueName: ""; ValueData: "Photo Scenery Maker X Project"; Flags: uninsdeletekey 

Root: HKCR; Subkey: "PhotoSceneryMakerXProject\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\PhotoSceneryMakerX.exe,0" 

Root: HKCR; Subkey: "PhotoSceneryMakerXProject\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\PhotoSceneryMakerX.exe"" ""%1"""
