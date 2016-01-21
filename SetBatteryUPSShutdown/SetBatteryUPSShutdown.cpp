// SetBatteryUPSShutdown.cpp : DLL �̏��������[�`���ł��B
//

#include "Stdafx.h"
#include "SetBatteryUPSShutdown.h"
#include "CfgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ�ǂ̊֐���
//		�֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE �}�N����
//		�����Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂� 
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//


// CSetBatteryUPSShutdownApp

BEGIN_MESSAGE_MAP(CSetBatteryUPSShutdownApp, CWinApp)
END_MESSAGE_MAP()


// CSetBatteryUPSShutdownApp �R���X�g���N�V����

CSetBatteryUPSShutdownApp::CSetBatteryUPSShutdownApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CSetBatteryUPSShutdownApp �I�u�W�F�N�g�ł��B

CSetBatteryUPSShutdownApp theApp;


// CSetBatteryUPSShutdownApp ������

BOOL CSetBatteryUPSShutdownApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

LONG WINAPI CPlApplet(
    HWND hwndCPl, // �R���g���[���p�l���E�B���h�E�̃n���h��
    UINT uMsg, // �R���g���[���p�l���A�v���P�[�V�����֑��M����郁�b�Z�[�W
    LONG lParam1, // 1 �Ԗڂ̃��b�Z�[�W�p�����[�^
    LONG lParam2 // 2 �Ԗڂ̃��b�Z�[�W�p�����[�^
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
