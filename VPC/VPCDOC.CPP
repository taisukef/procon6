// vpcdoc.cpp : CVpcDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "vpc.h"

#include "vpcdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVpcDoc

IMPLEMENT_DYNCREATE(CVpcDoc, CDocument)

BEGIN_MESSAGE_MAP(CVpcDoc, CDocument)
	//{{AFX_MSG_MAP(CVpcDoc)
		// ���� �| ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVpcDoc �N���X�̍\�z/����

CVpcDoc::CVpcDoc()
{
	// TODO: ���̈ʒu�Ɉ�񂾂��\�z�p�̃R�[�h��ǉ����Ă��������B
}

CVpcDoc::~CVpcDoc()
{
}

BOOL CVpcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVpcDoc �N���X�̃V���A���C�[�[�V����

void CVpcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}


/////////////////////////////////////////////////////////////////////////////
// CVpcDoc �N���X�̐f�f

#ifdef _DEBUG
void CVpcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVpcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVpcDoc �N���X�̃R�}���h