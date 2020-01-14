// vpcdoc.h : CVpcDoc クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

class CVpcDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CVpcDoc();
	DECLARE_DYNCREATE(CVpcDoc)

// 属性
public:

// オペレーション
public:

// インプリメンテーション
public:
	virtual ~CVpcDoc();
	virtual void Serialize(CArchive& ar);	// ドキュメント I/O に対してオーバーライドされます。
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// メッセージ マップ関数の生成を行います。
protected:
	//{{AFX_MSG(CVpcDoc)
		// 注意 － ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
