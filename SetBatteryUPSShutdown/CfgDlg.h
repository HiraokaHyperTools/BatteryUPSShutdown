#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCfgDlg ダイアログ

class CCfgDlg : public CDialog
{
	DECLARE_DYNAMIC(CCfgDlg)

public:
	CCfgDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CCfgDlg();

// ダイアログ データ
	enum { IDD = IDD_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	int m_secs1;
	int m_secs2;
	CString m_PCs;
	CSpinButtonCtrl m_wndSpin1;
	CSpinButtonCtrl m_wndSpin2;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_wndSvc;
	CStatic m_wndRep;
	void OnOK();
	CButton m_btnOK;
	CString m_Cmdline;
	afx_msg void OnBnClickedRefCmdline();
};
