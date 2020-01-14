// vpcdoc.cpp : CVpcDoc クラスの動作の定義を行います。
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
		// 注意 － ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVpcDoc クラスの構築/消滅

CVpcDoc::CVpcDoc()
{
	// TODO: この位置に一回だけ構築用のコードを追加してください。
}

CVpcDoc::~CVpcDoc()
{
}

BOOL CVpcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVpcDoc クラスのシリアライゼーション

void CVpcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}


/////////////////////////////////////////////////////////////////////////////
// CVpcDoc クラスの診断

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
// CVpcDoc クラスのコマンド
