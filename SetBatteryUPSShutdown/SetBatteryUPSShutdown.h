// SetBatteryUPSShutdown.h : SetBatteryUPSShutdown.DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSetBatteryUPSShutdownApp
// このクラスの実装に関しては SetBatteryUPSShutdown.cpp を参照してください。
//

class CSetBatteryUPSShutdownApp : public CWinApp
{
public:
	CSetBatteryUPSShutdownApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
