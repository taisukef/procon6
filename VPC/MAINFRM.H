// mainfrm.h : CMainFrame クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
protected: // シリアライズ機能のみから作成します。
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// オペレーション
public:

// インプリメンテーション
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif



// メッセージ マップ関数の生成を行います。
protected:
	//{{AFX_MSG(CMainFrame)
		// 注意 － ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
