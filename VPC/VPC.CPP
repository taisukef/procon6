// vpc.cpp : アプリケーション用クラスの機能定義を行います。
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
		// 注意 － ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVpcApp クラスの構築

CVpcApp::CVpcApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CVpcApp オブジェクト

CVpcApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CVpcApp クラスの初期化

BOOL CVpcApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたければ
	// 以下の特定の初期化ルーチンの中から不必要なものを削除してください。

	SetDialogBkColor();        // ダイアログ背景色をグレーに設定します。
	LoadStdProfileSettings();  // 標準 INI ファイルをロードします。(MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。
	// ドキュメント テンプレートはドキュメント、フレーム ウィンドウとビュー
	// を結合するために機能します。

	AddDocTemplate(new CSingleDocTemplate(0, // 実はかなり危険なのかもしれない・・・
			RUNTIME_CLASS(CVpcDoc),
			RUNTIME_CLASS(CMainFrame),     // メイン SDI フレーム ウィンドウ
			RUNTIME_CLASS(CVpcView)));

	// 新規(空の)ドキュメントを作成します。
	OnFileNew();
	m_pMainWnd->SetWindowText("VPC");

	if (m_lpCmdLine[0] != '\0') {
		// コマンドラインの処理だが・・・
	}
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// App About が使用する CAboutDlg クラスのダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//{{AFX_MSG(CAboutDlg)
		// メッセージ ハンドラはありません。
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
		// メッセージ ハンドラはありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを起動する App コマンド
void CVpcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVpcApp のコマンド
