// vpcdlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "vpc.h"
#include "vpcdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValueDlg ダイアログ

CValueDlg::CValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CValueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CValueDlg)
	m_value = 0;
	//}}AFX_DATA_INIT
	csMess = "数字を入力してください。";
}

void CValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValueDlg)
	DDX_Text(pDX, IDC_EDIT, m_value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CValueDlg, CDialog)
	//{{AFX_MSG_MAP(CValueDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValueDlg メッセージハンドラ

BOOL CValueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_MESSAGE, csMess);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}
