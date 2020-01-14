// vpcdlg.h : ヘッダー ファイル
//


/////////////////////////////////////////////////////////////////////////////
// CValueDlg ダイアログ

class CValueDlg : public CDialog
{
public:
	CString csMess;

// コンストラクタ
public:
	CValueDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CValueDlg)
	enum { IDD = IDD_VALUE_DLG };
	int		m_value;
	//}}AFX_DATA

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CValueDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
