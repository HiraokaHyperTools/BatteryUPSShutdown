; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

!define APP "MyBatteryUPSShutdown"
!define COM "HIRAOKA HYPERS TOOLS, Inc."

!define VER "0.1.0.0"
!searchreplace APV ${VER} "." "_"

!define SVC "MyBatteryUPSShutdown"

!define BUILD "release"
;SetCompress off

; The name of the installer
Name "${APP} ${VER}"

; The file to write
OutFile "Setup_${APP}.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\${APP}"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\${COM}\${APP}" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "My Battery UPS Shutdown ƒVƒXƒeƒ€"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  File "sc\*.*"

  ExecWait 'sc.exe stop ${SVC}' $0
  DetailPrint "Œ‹‰Ê: $0"

  Sleep 500

  ExecWait 'sc.exe delete ${SVC}' $0
  DetailPrint "Œ‹‰Ê: $0"

  Sleep 500

  ; Put file there
  File "${BUILD}\MyBatteryUPSShutdown.exe"
  File "${BUILD}\MyBatteryUPSShutdown.pdb"
  
  File "${BUILD}\SettingBatteryUPSShutdown.dll"
  File "${BUILD}\SettingBatteryUPSShutdown.pdb"

  RegDLL "$INSTDIR\SettingBatteryUPSShutdown.dll"

  File "${BUILD}\SetBatteryUPSShutdown.cpl"
  File "${BUILD}\SetBatteryUPSShutdown.pdb"

  WriteRegStr HKLM "SYSTEM\CurrentControlSet\services\eventlog\Application\${APP}" "EventMessageFile" "$INSTDIR\MyBatteryUPSShutdown.exe"

  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Control Panel\Cpls\" "SetBatteryUPSShutdown.cpl" "$INSTDIR\SetBatteryUPSShutdown.cpl"

  ; Write the installation path into the registry
  WriteRegStr HKLM "Software\${COM}\${APP}" "Install_Dir" "$INSTDIR"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP}" "DisplayName" "${APP}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP}" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  ExecWait 'sc.exe create ${SVC} binPath= "$INSTDIR\MyBatteryUPSShutdown.exe" start= auto' $0
  DetailPrint "Œ‹‰Ê: $0"

  ExecWait 'sc.exe start ${SVC}' $0
  DetailPrint "Œ‹‰Ê: $0"

SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"

  ExecWait 'sc.exe stop ${SVC}' $0
  DetailPrint "Œ‹‰Ê: $0"

  ExecWait 'sc.exe delete ${SVC}' $0
  DetailPrint "Œ‹‰Ê: $0"

  UnRegDLL "$INSTDIR\SettingBatteryUPSShutdown.dll"

  ; Remove files and uninstaller
  Delete "$INSTDIR\MyBatteryUPSShutdown.*"
  Delete "$INSTDIR\SetBatteryUPSShutdown.cpl"
  Delete "$INSTDIR\SetBatteryUPSShutdown.pdb"
  Delete "$INSTDIR\SettingBatteryUPSShutdown.*"
  
  Delete "$INSTDIR\license_sc.txt"
  Delete "$INSTDIR\sc.exe"
  Delete "$INSTDIR\scdev.doc"
  Delete "$INSTDIR\scdev.txt"

  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Control Panel\Cpls\SetBatteryUPSShutdown.cpl"

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP}"
  DeleteRegKey HKLM "Software\${COM}\${APP}"

  ; Remove files and uninstaller
  Delete "$INSTDIR\uninstall.exe"

  ; Remove directories used
  RMDir "$INSTDIR"

SectionEnd
