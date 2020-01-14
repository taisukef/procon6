// vpcview.h : CVpcView クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#include "dib.h"
#include "rgb.h"
#include "lrgb.h"

class CVpcView : public CView
{
protected:
    CDIB dib;
	CString sFilename;
	short cxClient, cyClient;
	CBitmap* pBitmap[2];
//	NPLOGPALETTE pLogPal;
//	CPalette* pPalette; // 心配
	int iCurBmp;
	int cxBmp, cyBmp;
	int cxSpace;
	CRGB crCurCol;
	float fScale;
	int iDrawMode;
	CPoint poBuf;
	BOOL bIsRDown;
	int DXtoCX(int x) { return (long)x * (cxClient - cxSpace) / cxBmp; }
	int DYtoCY(int y) { return (long)y * cyClient / cyBmp; }
	POINT CPtoDP(POINT);
	POINT DPtoCP(POINT);
	RECT DRtoCR(RECT);
	RECT* CorrectRect(RECT&);
	HCURSOR hCur, hCurWait, hCurArrow, hCurCross, hCurNormal;
	CBitmap* CreateNewBitmap();
	CPoint cpMv, cpLn;
	BOOL bNewLine;
	void FileOpen(CString);
	void NewInstance(CString);
	void PrepareBitmap();
	BOOL bWndJust;
	void WindowSize(int, int);
	CString ToLowers(CString);
	BOOL bIsDeg;

protected:
	CDC* pNewDC, * pOldDC;
	void BeginConvert(BOOL = TRUE, BOOL = FALSE);
	void EndConvert(BOOL = TRUE, LPRECT = NULL);
	void BeginDraw(int);
	void EndDraw();
	void Filter(int*, int = 1);
	void Filter2(int*);
	void Linear(double, double, double, double);
	void AdjustCenter(CPoint);
	RECT reObj, reBak;
	int iMouseFilter;
	void MouseFilter(BOOL = TRUE);

protected: // シリアライズ機能のみから作成します。
	CVpcView();
	DECLARE_DYNCREATE(CVpcView)

// 属性
public:
	CVpcDoc* GetDocument();

// オペレーション
public:

// インプリメンテーション
public:
	virtual ~CVpcView();
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// メッセージ マップ関数の生成を行います。
protected:
	//{{AFX_MSG(CVpcView)
	afx_msg void OnFileOpen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnConMono();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWndJust();
	afx_msg void OnConEdges();
	afx_msg void OnConCnoise();
	afx_msg void OnFileNew();
	afx_msg void OnDrawFree();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawGetc();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnWndMax();
	afx_msg void OnConUndo();
	afx_msg void OnConEdges2();
	afx_msg void OnConNegap();
	afx_msg void OnConBinary();
	afx_msg void OnConAdlight();
	afx_msg void OnConBesmart();
	afx_msg void OnConMosaic();
	afx_msg void OnDrawClip();
	afx_msg void OnDrawNoclip();
	afx_msg void OnConSoft();
	afx_msg void OnConPrewitt();
	afx_msg void OnConSobel();
	afx_msg void OnFileSaveas();
	afx_msg void OnDrawSelectc();
	afx_msg void OnConRotate();
	afx_msg void OnConZoom();
	afx_msg void OnConAdcenter();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnFileDataout();
	afx_msg void OnFileClear();
	afx_msg void OnFileCopy();
	afx_msg void OnFilePaste();
	afx_msg void OnUpdateFilePaste(CCmdUI* pCmdUI);
	afx_msg void OnWndCratio();
	afx_msg void OnConSscale();
	afx_msg void OnConAdheight();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawFrect();
	afx_msg void OnConCdcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// vpcview.cpp ファイルがデバッグ環境の時使用されます。
inline CVpcDoc* CVpcView::GetDocument()
   { return (CVpcDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
