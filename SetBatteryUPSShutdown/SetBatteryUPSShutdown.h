// SetBatteryUPSShutdown.h : SetBatteryUPSShutdown.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CSetBatteryUPSShutdownApp
// ���̃N���X�̎����Ɋւ��Ă� SetBatteryUPSShutdown.cpp ���Q�Ƃ��Ă��������B
//

class CSetBatteryUPSShutdownApp : public CWinApp
{
public:
	CSetBatteryUPSShutdownApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
