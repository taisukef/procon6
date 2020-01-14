// vpc.h : VPC アプリケーションのメインヘッダーファイル
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メインシンボル

/////////////////////////////////////////////////////////////////////////////
// CVpcApp:
// このクラスの動作の定義に関しては vpc.cpp ファイルを参照してください。
//

class CVpcApp : public CWinApp
{
public:
//	CString csFilename;

public:
	CVpcApp();

// オーバーライド
	virtual BOOL InitInstance();

// インプリメンテーション

	//{{AFX_MSG(CVpcApp)
	afx_msg void OnAppAbout();
		// 注意 － ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
