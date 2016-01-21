
#include "Stdafx.h"
#include "evt.h"

CWinApp theApp;

LPTSTR pszServiceName = _T("MyBatteryUPSShutdown");

SERVICE_STATUS          MyServiceStatus = {0};
SERVICE_STATUS_HANDLE   MyServiceStatusHandle = NULL; 

HANDLE hTimerShutdn2 = NULL;

int nSecsLeft = 0;
int nShutdnLaunched = 0;
bool fIsOnline = false;

#define UPSSTAT_LIVE 0x80000000U
#define UPSSTAT_TIMER_RUNNING 0x40000000U

DWORD QueryDWORDVal(LPCTSTR pszValue, DWORD defval) {
	CRegKey rkParm;
	DWORD val = 0;
	LONG res;
	if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown")))) {
		if (0 == (res = rkParm.QueryDWORDValue(pszValue, val))) {
			return val;
		}
	}
	return defval;
}

bool WriteDWORDVal(LPCTSTR pszValue, DWORD val) {
	CRegKey rkParm;
	LONG res;
	if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown"), KEY_WRITE))) {
		if (0 == (res = rkParm.SetDWORDValue(pszValue, val))) {
			return true;
		}
	}
	return false;
}

bool QueryStr(LPCTSTR pszValue, CString &str) {
	CRegKey rkParm;
	DWORD val = 0;
	LONG res;
	if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown")))) {
		ULONG cch = 5000;
		LPTSTR pszBuff = str.GetBuffer(cch);
		if (0 == (res = rkParm.QueryStringValue(pszValue, pszBuff, &cch))) {
			str.ReleaseBuffer(cch);
			return true;
		}
		str.ReleaseBuffer(0);
	}
	return false;
}

void StartShutdnTimer();

void StopShutdnTimer();

void UpdateCurrentStatus(DWORD flags) {
	// fedcba9876543210 fedcba9876543210
	// ---------------- ----------------
	// ||          xxxx SHUTDN_REM_SECS_
	// ||          +- count of shutdn started (15 max)
	// |+-- shutdown timer running
	// +--- software alive
	if (flags != 0) {
		flags |= (std::min<int>(15, nShutdnLaunched)) << 16;
	}

	WriteDWORDVal(_T("CurrentStatus"), flags);
}

void Wr0(WORD wType, DWORD dwEventID, WORD wCategory = 0) {
	HANDLE hEvl = OpenEventLog(NULL, _T("Application"));
	if (hEvl != NULL) {
		ATLVERIFY(ReportEvent(hEvl, wType, wCategory, dwEventID, NULL, 0, 0, NULL, NULL));
	}
	ATLVERIFY(CloseEventLog(hEvl));
}

void Wr1(WORD wType, DWORD dwEventID, LPCTSTR psz1, WORD wCategory = 0) {
	HANDLE hEvl = OpenEventLog(NULL, _T("Application"));
	if (hEvl != NULL) {
		LPCTSTR pszMany[] = {psz1};
		ATLVERIFY(ReportEvent(hEvl, wType, wCategory, dwEventID, NULL, 1, 0, pszMany, NULL));
	}
	ATLVERIFY(CloseEventLog(hEvl));
}

void Wr2(WORD wType, DWORD dwEventID, LPCTSTR psz1, int n2, WORD wCategory = 0) {
	HANDLE hEvl = OpenEventLog(NULL, _T("Application"));
	if (hEvl != NULL) {
		CString str2; str2.Format(_T("%d"), n2);
		LPCTSTR pszMany[] = {psz1, str2};
		ATLVERIFY(ReportEvent(hEvl, wType, wCategory, dwEventID, NULL, 2, 0, pszMany, NULL));
	}
	ATLVERIFY(CloseEventLog(hEvl));
}

void ShutdnNow() {
	CRegKey rkParm;
	LONG res;
	if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown")))) {
		TCHAR tcCmdline[1001] = {0};
		ULONG cchCmdline = 1000;
		if (0 == (res = rkParm.QueryStringValue(_T("Cmdline"), tcCmdline, &cchCmdline))) {
			STARTUPINFO si;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(pi));
			if (CreateProcess(NULL, tcCmdline, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				Wr1(EVENTLOG_SUCCESS, MSG_UPS_CMDLINE_LAUNCHED, tcCmdline);
			}
			else {
				Wr1(EVENTLOG_WARNING_TYPE, MSG_UPS_CMDLINE_FAILED, tcCmdline);
			}
		}
		TCHAR tcServers[1001] = {0};
		ULONG cch = 1000;
		if (0 == (res = rkParm.QueryStringValue(_T("Servers"), tcServers, &cch))) {
			DWORD nSecs = QueryDWORDVal(_T("SecondsSecs"), 120);
			tcServers[cch] = 0;
			CString strServers = tcServers;
			int i = 0;
			CString strMsg;
			strMsg.Format(_T("停電が発生しました。%u秒後にシャットダウン開始します。"), nSecs);
			CAccessToken at;
			bool fEnabled = false;
			if (at.GetProcessToken(TOKEN_READ|TOKEN_ADJUST_PRIVILEGES)) {
				fEnabled |= at.EnablePrivilege(SE_REMOTE_SHUTDOWN_NAME);
				fEnabled |= at.EnablePrivilege(SE_SHUTDOWN_NAME);
			}
			while (true) {
				CString strServer = strServers.Tokenize(_T(";"), i);
				if (i < 0)
					break;
				strServer.Trim();
				if (strServer.IsEmpty())
					continue;
				BOOL fInited = InitiateSystemShutdownEx(
					const_cast<LPTSTR>(static_cast<LPCTSTR>(strServer)),
					const_cast<LPTSTR>(static_cast<LPCTSTR>(strMsg)),
					nSecs,
					true,
					false,
					SHTDN_REASON_MAJOR_POWER | SHTDN_REASON_MINOR_ENVIRONMENT
					);
				int lasterr = GetLastError();
				Wr2(fInited ? EVENTLOG_SUCCESS : EVENTLOG_WARNING_TYPE, fInited ? MSG_UPS_SHUTDOWN_INITED : MSG_UPS_SHUTDOWN_FAILED, strServer, lasterr);
			}
			if (fEnabled) {
				at.DisablePrivilege(SE_SHUTDOWN_NAME);
				at.DisablePrivilege(SE_REMOTE_SHUTDOWN_NAME);
			}
			++nShutdnLaunched;
		}
	}
	UpdateCurrentStatus(UPSSTAT_LIVE);
}

HANDLE hMutex = CreateMutex(NULL, false, NULL);

class CAtMtx {
	HANDLE h;
public:
	CAtMtx(HANDLE h): h(h) {
		ATLVERIFY(WAIT_OBJECT_0 == WaitForSingleObject(h, INFINITE));
	}
	~CAtMtx() {
		ATLVERIFY(ReleaseMutex(h));
	}
};

VOID CALLBACK WaitOrTimerCallback_Shutdn(  PVOID lpParameter,  BOOLEAN TimerOrWaitFired
)
{
	CAtMtx atm(hMutex);

	--nSecsLeft;
	if (nSecsLeft < 0) {
		ShutdnNow();

		// run this at last
		StopShutdnTimer();
	}
	else {
		UpdateCurrentStatus(UPSSTAT_LIVE|UPSSTAT_TIMER_RUNNING|std::min<DWORD>(65535, nSecsLeft));
	}
}

void StartShutdnTimer()
{
	StopShutdnTimer();

	if (CreateTimerQueueTimer(&hTimerShutdn2, NULL, WaitOrTimerCallback_Shutdn, NULL, 0, 1000, WT_EXECUTEINTIMERTHREAD)) {
		Wr0(EVENTLOG_SUCCESS, MSG_UPS_TIMER1_STARTED);
	}
	else {
		Wr0(EVENTLOG_WARNING_TYPE, MSG_UPS_TIMER1_FAILED);
	}
}

void StopShutdnTimer()
{
	if (hTimerShutdn2 != NULL) {
		ATLVERIFY(DeleteTimerQueueTimer(NULL, hTimerShutdn2, NULL));
		hTimerShutdn2 = NULL;
	}
}

void UPSUpdated(bool first) {
	CAtMtx atm(hMutex);

	SYSTEM_POWER_STATUS st;
	if (!GetSystemPowerStatus(&st))
		return;
	if (st.ACLineStatus == 0) {
		// do shutdown
		if (hTimerShutdn2 == NULL && fIsOnline) {
			nSecsLeft = QueryDWORDVal(_T("FirstSecs"), 300);
			StartShutdnTimer();
			UpdateCurrentStatus(UPSSTAT_LIVE|UPSSTAT_TIMER_RUNNING|std::min<DWORD>(65535, nSecsLeft));
		}
		fIsOnline = false;
	}
	else {
		// cancel
		StopShutdnTimer();
		UpdateCurrentStatus(UPSSTAT_LIVE);
		fIsOnline = true;
	}
}

VOID SvcDebugOut(LPSTR String, DWORD Status);
DWORD WINAPI MyServiceCtrlHandler (DWORD opcode, DWORD dwEventType,
  LPVOID lpEventData,
  LPVOID lpContext
); 
VOID  WINAPI MyServiceStart (DWORD argc, LPTSTR *argv); 
DWORD MyServiceInitialization (DWORD argc, LPTSTR *argv, 
        DWORD *specificError); 

DWORD WINAPI MyServiceCtrlHandler (DWORD Opcode, DWORD dwEventType,
  LPVOID lpEventData,
  LPVOID lpContext
) 
{ 
   DWORD status; 
 
   switch(Opcode) 
   { 
      case SERVICE_CONTROL_PAUSE: 
      // Do whatever it takes to pause here. 
         MyServiceStatus.dwCurrentState = SERVICE_PAUSED; 
         break; 
 
      case SERVICE_CONTROL_CONTINUE: 
      // Do whatever it takes to continue here. 
         MyServiceStatus.dwCurrentState = SERVICE_RUNNING; 
         break; 
 
      case SERVICE_CONTROL_STOP: 
      // Do whatever it takes to stop here. 
		 UpdateCurrentStatus(0);
		 
		 StopShutdnTimer();

         MyServiceStatus.dwWin32ExitCode = 0; 
         MyServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
         MyServiceStatus.dwCheckPoint    = 0; 
         MyServiceStatus.dwWaitHint      = 0; 

         if (!SetServiceStatus (MyServiceStatusHandle, 
           &MyServiceStatus))
         { 
            status = GetLastError(); 
            SvcDebugOut(" [MyBatteryUPSShutdown] SetServiceStatus error %ld\n", 
               status); 
         } 
 
         SvcDebugOut(" [MyBatteryUPSShutdown] Leaving MyService \n",0); 
         return NO_ERROR; 
 
      case SERVICE_CONTROL_INTERROGATE: 
      // Fall through to send current status. 
         break; 

	case SERVICE_CONTROL_POWEREVENT:
		if (dwEventType == PBT_APMPOWERSTATUSCHANGE) {
			UPSUpdated(false);
		}
		return NO_ERROR; 

	case 222:
		ShutdnNow();
		return NO_ERROR;

      default: 
         SvcDebugOut(" [MyBatteryUPSShutdown] Unrecognized opcode %ld\n", 
             Opcode); 
		 return ERROR_CALL_NOT_IMPLEMENTED;
   } 
 
   // Send current status. 
   if (!SetServiceStatus (MyServiceStatusHandle,  &MyServiceStatus)) 
   { 
      status = GetLastError(); 
      SvcDebugOut(" [MyBatteryUPSShutdown] SetServiceStatus error %ld\n", 
         status); 
   } 
   return NO_ERROR;
}

void WINAPI MyServiceStart (DWORD argc, LPTSTR *argv) 
{ 
    DWORD status; 
    DWORD specificError; 
 
    MyServiceStatus.dwServiceType        = SERVICE_WIN32; 
    MyServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    MyServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | 
        SERVICE_ACCEPT_POWEREVENT; 
    MyServiceStatus.dwWin32ExitCode      = 0; 
    MyServiceStatus.dwServiceSpecificExitCode = 0; 
    MyServiceStatus.dwCheckPoint         = 0; 
    MyServiceStatus.dwWaitHint           = 0; 
 
    MyServiceStatusHandle = RegisterServiceCtrlHandlerEx( 
        pszServiceName, 
        MyServiceCtrlHandler,
		NULL); 
 
    if (MyServiceStatusHandle == (SERVICE_STATUS_HANDLE)0) 
    { 
        SvcDebugOut(" [MyBatteryUPSShutdown] RegisterServiceCtrlHandler failed %d\n", GetLastError()); 
        return; 
    } 
 
    // Initialization code goes here. 
    status = MyServiceInitialization(argc,argv, &specificError); 
 
    // Handle error condition 
    if (status != NO_ERROR) 
    { 
        MyServiceStatus.dwCurrentState       = SERVICE_STOPPED; 
        MyServiceStatus.dwCheckPoint         = 0; 
        MyServiceStatus.dwWaitHint           = 0; 
        MyServiceStatus.dwWin32ExitCode      = status; 
        MyServiceStatus.dwServiceSpecificExitCode = specificError; 
 
        SetServiceStatus (MyServiceStatusHandle, &MyServiceStatus); 
        return; 
    } 
 
    // Initialization complete - report running status. 
    MyServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
    MyServiceStatus.dwCheckPoint         = 0; 
    MyServiceStatus.dwWaitHint           = 0; 
 
    if (!SetServiceStatus (MyServiceStatusHandle, &MyServiceStatus)) 
    { 
        status = GetLastError(); 
        SvcDebugOut(" [MyBatteryUPSShutdown] SetServiceStatus error %ld\n",status); 
    } 
 
    // This is where the service does its work. 
    SvcDebugOut(" [MyBatteryUPSShutdown] Returning the Main Thread \n",0); 
 
    return; 
} 
 
// Stub initialization function. 
DWORD MyServiceInitialization(DWORD   argc, LPTSTR  *argv, 
    DWORD *specificError) 
{ 
    argv; 
    argc; 
    specificError; 

	UPSUpdated(true);
    return(0); 
}

int WINAPI _tWinMain(  HINSTANCE hInstance,   HINSTANCE hPrevInstance, 
  LPTSTR lpCmdLine,   int nShowCmd )
{
	if (!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nShowCmd))
		return 1;

   SERVICE_TABLE_ENTRY   DispatchTable[] = 
   { 
      { pszServiceName, MyServiceStart      }, 
      { NULL,              NULL          } 
   }; 
 
   if (!StartServiceCtrlDispatcher( DispatchTable)) 
   { 
      SvcDebugOut(" [MyBatteryUPSShutdown] StartServiceCtrlDispatcher (%d)\n", 
         GetLastError()); 
	  return 1;
   } 

   return 0;
} 
 
VOID SvcDebugOut(LPSTR String, DWORD Status) 
{ 
   CHAR  Buffer[1024]; 
   if (strlen(String) < 1000) 
   { 
      sprintf_s(Buffer, String, Status); 
      OutputDebugStringA(Buffer); 
   } 
}

