; // ***** Sample.mc *****

; // This is the header section.

MessageIdTypedef=DWORD

SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
    Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
    Warning=0x2:STATUS_SEVERITY_WARNING
    Error=0x3:STATUS_SEVERITY_ERROR
    )

FacilityNames=(System=0x0:FACILITY_SYSTEM
    Runtime=0x2:FACILITY_RUNTIME
    Stubs=0x3:FACILITY_STUBS
    Io=0x4:FACILITY_IO_ERROR_CODE
)

LanguageNames=(English=0x409:MSG00409)
LanguageNames=(Japanese=0x411:MSG00411)

; // The following are message definitions.

MessageId=0x1
Severity=Success
Facility=Runtime
SymbolicName=MSG_UPS_TIMER1_STARTED
Language=English
Primary timer started. It counts on shutdown notice.
.
Language=Japanese
一次タイマーを開始しました。これは、シャットダウン予告が表示されるまでの時間になります。
.

MessageId=0x2
Severity=Warning
Facility=Runtime
SymbolicName=MSG_UPS_TIMER1_FAILED
Language=English
Primary timer failed to start.
.
Language=Japanese
一次タイマーが開始できませんでした。
.

MessageId=0x2
Severity=Success
Facility=Runtime
SymbolicName=MSG_UPS_CMDLINE_LAUNCHED
Language=English
Command line launched: %1
.
Language=Japanese
コマンドラインを実行しました。%1
.

MessageId=0x3
Severity=Warning
Facility=Runtime
SymbolicName=MSG_UPS_CMDLINE_FAILED
Language=English
Command line failed to launch: %1
.
Language=Japanese
コマンドラインの実行に失敗しました。
.

MessageId=0x4
Severity=Success
Facility=Runtime
SymbolicName=MSG_UPS_SHUTDOWN_INITED
Language=English
Shutdown notice initiated, PC: %1
.
Language=Japanese
パソコンのシャットダウン予告を開始しました。%1
.

MessageId=0x5
Severity=Warning
Facility=Runtime
SymbolicName=MSG_UPS_SHUTDOWN_FAILED
Language=English
Shutdown notice failed, PC: %1 (%2)
.
Language=Japanese
パソコンのシャットダウン予告に失敗しました。%1 (2)
.

