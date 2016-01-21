// SetBatteryUPSShutdown.cpp : DLL の初期化ルーチンです。
//

#include "Stdafx.h"
#include "SetBatteryUPSShutdown.h"
#include "CfgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされたどの関数も
//		関数の最初に追加される AFX_MANAGE_STATE マクロを
//		持たなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな 
//		らないことを意味します、コンストラクタが MFC
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//


// CSetBatteryUPSShutdownApp

BEGIN_MESSAGE_MAP(CSetBatteryUPSShutdownApp, CWinApp)
END_MESSAGE_MAP()


// CSetBatteryUPSShutdownApp コンストラクション

CSetBatteryUPSShutdownApp::CSetBatteryUPSShutdownApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CSetBatteryUPSShutdownApp オブジェクトです。

CSetBatteryUPSShutdownApp theApp;


// CSetBatteryUPSShutdownApp 初期化

BOOL CSetBatteryUPSShutdownApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

LONG WINAPI CPlApplet(
    HWND hwndCPl, // コントロールパネルウィンドウのハンドル
    UINT uMsg, // コントロールパネルアプリケーションへ送信されるメッセージ
    LONG lParam1, // 1 番目のメッセージパラメータ
    LONG lParam2 // 2 番目のメッセージパラメータ
)
{
	switch (uMsg) {
		case CPL_INIT:
			{
				return 1;
			}
		case CPL_GETCOUNT:
			{
				return 1;
			}
		case CPL_INQUIRE:
			{
				CPLINFO *pInfo = reinterpret_cast<CPLINFO *>(lParam2);
				pInfo->idIcon = 1;
				pInfo->idName = IDS_NAME;
				pInfo->idInfo = IDS_INFO;
				pInfo->lData = reinterpret_cast<LONG_PTR>(&theApp);
				return 0;
			}
		case CPL_DBLCLK:
			{
				CCfgDlg wndDlg;
				wndDlg.DoModal();
				return 0;
			}
	}
	return 0;
}
