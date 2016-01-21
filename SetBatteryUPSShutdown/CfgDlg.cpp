// CfgDlg.cpp : 実装ファイル
//

#include "Stdafx.h"
#include "SetBatteryUPSShutdown.h"
#include "CfgDlg.h"

#ifdef DEBUG
# import "../SettingBatteryUPSShutdown/Debug/SettingBatteryUPSShutdown.tlb"
#else
# import "../SettingBatteryUPSShutdown/Release/SettingBatteryUPSShutdown.tlb"
#endif

using namespace SettingBatteryUPSShutdownLib;

class PCLUt {
public:
	static CString FrmREG(CString s) {
		s.Replace(_T(";"), _T("\r\n"));
		return s;
	}
	static CString ToREG(CString s) {
		s.Replace(_T("\r\n"), _T(";"));
		s.Replace(_T("\n"), _T(";"));
		return s;
	}
};

// CCfgDlg ダイアログ

IMPLEMENT_DYNAMIC(CCfgDlg, CDialog)

CCfgDlg::CCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgDlg::IDD, pParent)
	, m_secs1(0)
	, m_secs2(0)
	, m_PCs(_T(""))
	, m_Cmdline(_T(""))
{

}

CCfgDlg::~CCfgDlg()
{
}

void CCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SECS1, m_secs1);
	DDV_MinMaxInt(pDX, m_secs1, 0, 65535);
	DDX_Text(pDX, IDC_SECS2, m_secs2);
	DDV_MinMaxInt(pDX, m_secs2, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PCS, m_PCs);
	DDX_Control(pDX, IDC_SPIN1, m_wndSpin1);
	DDX_Control(pDX, IDC_SPIN2, m_wndSpin2);
	DDX_Control(pDX, IDC_STATIC_SERVICE_STATUS, m_wndSvc);
	DDX_Control(pDX, IDC_STATIC_REPORT, m_wndRep);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT_CMDLINE, m_Cmdline);
}


BEGIN_MESSAGE_MAP(CCfgDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REF_CMDLINE, &CCfgDlg::OnBnClickedRefCmdline)
END_MESSAGE_MAP()

#define UPSSTAT_LIVE 0x80000000U
#define UPSSTAT_TIMER_RUNNING 0x40000000U

// CCfgDlg メッセージ ハンドラ

BOOL CCfgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	const UINT _BCM_SETSHIELD = 0x160C;

	m_btnOK.SendMessage(_BCM_SETSHIELD, 0, TRUE);

	m_wndSpin1.SetRange32(0, 65535);
	m_wndSpin2.SetRange32(0, 65535);

	HRESULT hr;
	CComPtr<ICfgUPS> pCfg;
	if (SUCCEEDED(hr = pCfg.CoCreateInstance(__uuidof(CfgUPS)))) {
		LONG l;
		CComBSTR bs;
		if (SUCCEEDED(hr = pCfg->get_FirstSecs(&l))) m_secs1 = l;
		if (SUCCEEDED(hr = pCfg->get_SecondsSecs(&l))) m_secs2 = l;
		if (SUCCEEDED(hr = pCfg->get_Servers(&bs))) m_PCs = PCLUt::FrmREG(CString(bs));
		if (SUCCEEDED(hr = pCfg->get_Cmdline(&bs))) m_Cmdline = bs;

	}

	UpdateData(false);

	SetTimer(101, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

typedef struct _tagBIND_OPTS3 {
  DWORD        cbStruct;
  DWORD        grfFlags;
  DWORD        grfMode;
  DWORD        dwTickCountDeadline;
  DWORD        dwTrackFlags;
  DWORD        dwClassContext;
  LCID         locale;
  COSERVERINFO *pServerInfo;
  HWND         hwnd;
} _BIND_OPTS3, *_LPBIND_OPTS3;

HRESULT CoCreateInstanceAsAdmin(HWND hwnd, REFCLSID rclsid, REFIID riid, __out void ** ppv)
{
    _BIND_OPTS3 bo;
    WCHAR  wszCLSID[50];
    WCHAR  wszMonikerName[300];

    StringFromGUID2(rclsid, wszCLSID, sizeof(wszCLSID)/sizeof(wszCLSID[0])); 
    HRESULT hr = StringCchPrintf(wszMonikerName, sizeof(wszMonikerName)/sizeof(wszMonikerName[0]), L"Elevation:Administrator!new:%s", wszCLSID);
    if (FAILED(hr))
        return hr;
    memset(&bo, 0, sizeof(bo));
    bo.cbStruct = sizeof(bo);
    bo.hwnd = hwnd;
    bo.dwClassContext  = CLSCTX_LOCAL_SERVER;
    return CoGetObject(wszMonikerName, reinterpret_cast<LPBIND_OPTS>(&bo), riid, ppv);
}

#ifndef IID_PPV_ARGS
//  IID_PPV_ARGS(ppType)
//      ppType is the variable of type IType that will be filled
//
//      RESULTS in:  IID_IType, ppvType
//      will create a compiler error if wrong level of indirection is used.
//
extern "C++"
{
    template<typename T> void** IID_PPV_ARGS_Helper(T** pp)
    {
        // make sure everyone derives from IUnknown
        static_cast<IUnknown*>(*pp);
       
        return reinterpret_cast<void**>(pp);
    }
}
 
#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)
#endif

void CCfgDlg::OnOK() {
	if (!UpdateData())
		return;
	CComPtr<ICfgUPS> pCfg;
	HRESULT hr;
	int cnt = 0;
	int total = 0;
	if (false
		|| SUCCEEDED(hr = CoCreateInstanceAsAdmin(*this, __uuidof(CfgUPS), IID_PPV_ARGS(&pCfg)))
		|| SUCCEEDED(hr = pCfg.CoCreateInstance(__uuidof(CfgUPS)))
	) {
		total++; cnt += SUCCEEDED(hr = pCfg->put_FirstSecs(m_secs1)) ? 1 : 0;
		total++; cnt += SUCCEEDED(hr = pCfg->put_SecondsSecs(m_secs2)) ? 1 : 0;
		total++; cnt += SUCCEEDED(hr = pCfg->put_Servers(CComBSTR(PCLUt::ToREG(m_PCs)))) ? 1 : 0;
		total++; cnt += SUCCEEDED(hr = pCfg->put_Cmdline(CComBSTR(m_Cmdline))) ? 1 : 0;
	}
	AfxMessageBox((cnt == total) ? IDS_SAVE_OK : IDS_SAVE_FAILED, MB_ICONEXCLAMATION);
	return;
}

void CCfgDlg::OnDestroy()
{
	CDialog::OnDestroy();

	KillTimer(101);
}

void CCfgDlg::OnTimer(UINT_PTR nIDEvent)
{
	HRESULT hr;
	switch (nIDEvent) {
		case 101:
			{
				DWORD nCurrentStatus = 0;
				CComPtr<ICfgUPS> pCfg;
				if (SUCCEEDED(hr = pCfg.CoCreateInstance(__uuidof(CfgUPS)))) {
					LONG l;
					if (SUCCEEDED(hr = pCfg->get_CurrentStatus(&l))) nCurrentStatus = l;
				}

				{
					CString strRep;
					if (0 != (nCurrentStatus & UPSSTAT_LIVE)) {
						strRep.Format(_T("実行中です。 "));

						if (0 != (nCurrentStatus & UPSSTAT_TIMER_RUNNING)) {
							int nSecsLeft = (nCurrentStatus & 65535U);
							strRep.AppendFormat(_T("%d秒後にシャットダウン開始します。 "), 0 +nSecsLeft);
						}
						else {
						}
						int nCntPast = (nCurrentStatus >> 16) & 15;
						if (nCntPast != 0) {
							strRep.AppendFormat(_T("%d回シャットダウンを開始しました。 "), 0 +nCntPast);
						}
					}
					else {
						strRep.Format(_T("停止状態です。 "));
					}
					m_wndRep.SetWindowText(strRep);
				}

				{
					CString strStat = _T("(不明)");
					SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT|SC_MANAGER_ENUMERATE_SERVICE|GENERIC_READ);
					if (hSCM != NULL) {
						SC_HANDLE hSvc = OpenService(hSCM, _T("MyBatteryUPSShutdown"), SERVICE_QUERY_STATUS|GENERIC_READ);
						if (hSvc != NULL) {
							SERVICE_STATUS_PROCESS info;
							DWORD cb = sizeof(info);
							if (QueryServiceStatusEx(hSvc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&info), cb, &cb)) {
								switch (info.dwCurrentState) {
									case SERVICE_CONTINUE_PENDING: strStat = _T("再開を待っています。 "); break;
									case SERVICE_PAUSE_PENDING: strStat = _T("一時停止を待っています。 "); break;
									case SERVICE_PAUSED: strStat = _T("一時停止しています。 "); break;
									case SERVICE_RUNNING: strStat = _T("実行しています。 "); break;
									case SERVICE_START_PENDING: strStat = _T("実行を待っています。 "); break;
									case SERVICE_STOP_PENDING: strStat = _T("停止を待っています。 "); break;
									case SERVICE_STOPPED: strStat = _T("停止しています。 "); break;
								}
							}
							VERIFY(CloseServiceHandle(hSvc));
						}
						VERIFY(CloseServiceHandle(hSCM));
					}
					m_wndSvc.SetWindowText(strStat);
				}
				break;
			}
	}

	CDialog::OnTimer(nIDEvent);
}

void CCfgDlg::OnBnClickedRefCmdline()
{
	if (!UpdateData())
		return;
	CFileDialog wndDlg(true, _T("bat"), NULL, OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES, _T("*.BAT;*.CMD;*.EXE|*.BAT;*.CMD;*.EXE||"), this);
	if (wndDlg.DoModal() == IDOK) {
		m_Cmdline.Format(_T("\"%s\""), wndDlg.GetPathName());
		UpdateData(false);
	}
}
