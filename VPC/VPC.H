// vpc.h : VPC �A�v���P�[�V�����̃��C���w�b�_�[�t�@�C��
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C���V���{��

/////////////////////////////////////////////////////////////////////////////
// CVpcApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� vpc.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CVpcApp : public CWinApp
{
public:
//	CString csFilename;

public:
	CVpcApp();

// �I�[�o�[���C�h
	virtual BOOL InitInstance();

// �C���v�������e�[�V����

	//{{AFX_MSG(CVpcApp)
	afx_msg void OnAppAbout();
		// ���� �| ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////