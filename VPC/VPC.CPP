// vpc.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "vpc.h"

#include "mainfrm.h"
#include "vpcdoc.h"
#include "vpcview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVpcApp

BEGIN_MESSAGE_MAP(CVpcApp, CWinApp)
	//{{AFX_MSG_MAP(CVpcApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// ���� �| ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVpcApp �N���X�̍\�z

CVpcApp::CVpcApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CVpcApp �I�u�W�F�N�g

CVpcApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CVpcApp �N���X�̏�����

BOOL CVpcApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y�����������������
	// �ȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜���Ă��������B

	SetDialogBkColor();        // �_�C�A���O�w�i�F���O���[�ɐݒ肵�܂��B
	LoadStdProfileSettings();  // �W�� INI �t�@�C�������[�h���܂��B(MRU ���܂�)

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B
	// �h�L�������g �e���v���[�g�̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[
	// ���������邽�߂ɋ@�\���܂��B

	AddDocTemplate(new CSingleDocTemplate(0, // ���͂��Ȃ�댯�Ȃ̂�������Ȃ��E�E�E
			RUNTIME_CLASS(CVpcDoc),
			RUNTIME_CLASS(CMainFrame),     // ���C�� SDI �t���[�� �E�B���h�E
			RUNTIME_CLASS(CVpcView)));

	// �V�K(���)�h�L�������g���쐬���܂��B
	OnFileNew();
	m_pMainWnd->SetWindowText("VPC");

	if (m_lpCmdLine[0] != '\0') {
		// �R�}���h���C���̏��������E�E�E
	}
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// App About ���g�p���� CAboutDlg �N���X�̃_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// �C���v�������e�[�V����
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//{{AFX_MSG(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O���N������ App �R�}���h
void CVpcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVpcApp �̃R�}���h