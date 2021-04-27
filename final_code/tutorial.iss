; This is an Inno Setup Script for the dBASE
; Application Tutorial.
;
; This is the dBASE Plus 11.1 version, January, 2017,
; by Ken Mayer.
;
; Constants:
#DEFINE MyAppVersion "4.00"

[Setup] 
; -----------------------------------------------------
; Name of program to run
OutputBaseFilename=Tutorial_Install

; -----------------------------------------------------
; Output directory -- where the install program
; gets created (this will be "under" the source, i.e,
; C:\dBASE Tutorial\Installer):
OutputDir=Installer

; -----------------------------------------------------
; Source folder for files (where is your application?):
SourceDir=C:\dBASETutorial

; -----------------------------------------------------
; Application folder, C:\Program Files (x86)\dBASE Tutorial
DefaultDirName={pf}\dBASE Tutorial
; Don't allow user to select paths ...
DisableDirPage=yes
            
; -----------------------------------------------------
; Name of group that is created
DefaultGroupName=dBASE Tutorial
            
; -----------------------------------------------------
; Items involved in install program display:
AppCopyright=Copyright ©2017 - Ken Mayer
AppID=dBASE Tutorial Application
; Application Name -- as it will appear in Setup program (upper left corner)
AppName=dBASE Tutorial Application
; Version -- required
AppVerName=dBASE Tutorial, vers. 4.0
AppVersion=MyAppVersion
            
; -----------------------------------------------------
; Uninstallable ...?
Uninstallable=yes

[Dirs]
; This is where the data is supposed to be placed, this is editable:
;    C:\Users\username\AppData\Local\dBASE Tutorial\tables
Name: "{localappdata}\dBASE Tutorial\tables"; Permissions: everyone-modify;

; -----------------------------------------------------
; images folder -- using DEO, we can store the images used here:
; C:\Program Files (x86)\dBASE Tutorial\images
Name: "{app}\images"; Permissions: everyone-modify;

; -----------------------------------------------------
; custom folder -- using DEO, we can store the images used here:
; C:\Program Files (x86)\dBASE Tutorial\custom
Name: "{app}\custom"; Permissions: everyone-modify;

; -----------------------------------------------------
; Where the dBASE Plus Runtime Engine will go: "C:\Program Files (x86)" if on 
; 64-bit versions of Windows, or on 32-bit versions, "C:\Program Files"):
Name: "{pf}\dBASE\Plus\Runtime"; Permissions: everyone-readexec; Flags: uninsneveruninstall;
            
; -----------------------------------------------------
; Where the BDE will go:
Name: "{cf}\Borland\BDE"; Permissions: everyone-full; Flags: uninsneveruninstall;

[Files]
; -----------------------------------------------------
; The application itself, to the application folder:
Source: "deploy\tutorial.exe"; DestDir: "{app}"; Flags: ignoreversion;

; -----------------------------------------------------
; Don't forget your .INI file -- this should go in the {app} folder,
; note that it will be copied when the exe is first run, see above:
Source: "deploy\tutorial.ini"; DestDir: "{app}"; Flags: ignoreversion;

; -----------------------------------------------------
; object files in main folder
; data modules:
Source: "deploy\*.dmo"; DestDir: "{app}"; Flags: ignoreversion;
; forms:
Source: "deploy\*.wfo"; DestDir: "{app}"; Flags: ignoreversion;
; reports:
Source: "deploy\*.reo"; DestDir: "{app}"; Flags: ignoreversion;
; labels:
Source: "deploy\*.lao"; DestDir: "{app}"; Flags: ignoreversion;
; sql:
Source: "deploy\*.sql"; DestDir: "{app}"; Flags: ignoreversion;
; custom class:
Source: "deploy\*.co"; DestDir: "{app}"; Flags: ignoreversion;
; program:
Source: "deploy\*.pro"; DestDir: "{app}"; Flags: ignoreversion;
; menu:
Source: "deploy\*.mno"; DestDir: "{app}"; Flags: ignoreversion;

; -----------------------------------------------------
; custom folder -- custom classes, data modules, etc.
Source: "deploy\custom\*.*"; DestDir: "{app}\custom"; Flags: ignoreversion;

; -----------------------------------------------------
; images folder -- images used for the toolbars:
Source: "deploy\images\*.*"; DestDir: "{app}\images"; Flags: ignoreversion;

; -----------------------------------------------------
; tables folder
Source: "tables\*.*"; DestDir: "{localappdata}\dBASE Tutorial\tables"; Flags: ignoreversion;

; -----------------------------------------------------
; dBASE Runtime Installer
Source: "C:\Program Files (x86)\dBASE\Plus11\Runtime\PLUS1110Runtime-b2536_ALL.exe"; DestDir: "{tmp}"; Flags: ignoreversion deleteafterinstall;

; -----------------------------------------------------
; Manifest file for runtime:
Source: "C:\Program Files (x86)\dBASE\PLUS11\Runtime\plusrun.exe.manifest"; DestDir: "{pf}\dBASE\Plus\Runtime"

; Manifest file for our application:
Source: "deploy\tutorial.exe.manifest"; DestDir: "{app}"; Flags: ignoreversion;

[INI]
; -----------------------------------------------------
; Update the .ini file for the User BDE Alias:
Filename: {app}\tutorial.ini; Section: "UserBDEAliases";
Filename: {app}\tutorial.ini; Section: "UserBDEAliases"; Key: "0"; String: "dBASETutorial";
Filename: {app}\tutorial.ini; Section: "dBASETutorial";
Filename: {app}\tutorial.ini; Section: "dBASETutorial"; Key: "Driver"; String: "DBASE";
Filename: {app}\tutorial.ini; Section: "dBASETutorial"; Key: "Options"; String: "PATH: ""{localappdata}\dBASE Tutorial\tables""";

; DEO Paths:
Filename: {app}\tutorial.ini; Section: "ObjectPath";
Filename: {app}\tutorial.ini; Section: "ObjectPath"; Key: "objPath0"; String: "{app}";
Filename: {app}\tutorial.ini; Section: "ObjectPath"; Key: "objPath1"; String: "{app}\images";
Filename: {app}\tutorial.ini; Section: "ObjectPath"; Key: "objPath2"; String: "{app}\custom";

; Application Theme:
Filename: {app}\tutorial.ini; Section: "AppTheme";
Filename: {app}\tutorial.ini; Section: "AppTheme"; Key: "Type"; String: "6";

[Run]
; dBASE Plus 11 -- parameter of /S seems to be the "silent" install
Filename: {tmp}\PLUS1110Runtime-b2536_ALL.exe; Parameters: "/S"; Flags: runascurrentuser waituntilterminated runhidden; Description: "dBASE Runtime and BDE"; StatusMsg: "Installing dBASE Runtime and BDE..."; WorkingDir: {tmp};

[Icons] 
; -----------------------------------------------------
; Application icon
Name: "{group}\dBASE Tutorial"; Filename: "{app}\tutorial.exe"; WorkingDir: "{app}"
            
; Desktop icons:
Name: "{userdesktop}\dBASE Tutorial"; Filename: "{app}\tutorial.exe"; IconFilename: "{app}\tutorial.exe"; WorkingDir: "{app}"; Comment: "dBASE Tutorial Application";

; -----------------------------------------------------
; End of tutorial.iss Inno Setup script
; -----------------------------------------------------
