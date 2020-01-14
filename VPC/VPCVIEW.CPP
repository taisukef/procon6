// vpcview.cpp : CVpcView クラスの動作の定義を行います。
//

#include "stdafx.h"

#include "vpc.h"
#include "vpcdoc.h"
#include "vpcview.h"

#include <math.h>
const double PI = 3.14159265358979;

#include <fstream.h>

#include "vpcdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVpcView

IMPLEMENT_DYNCREATE(CVpcView, CView)

BEGIN_MESSAGE_MAP(CVpcView, CView)
	//{{AFX_MSG_MAP(CVpcView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_SIZE()
	ON_COMMAND(ID_CON_MONO, OnConMono)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_WND_JUST, OnWndJust)
	ON_COMMAND(ID_CON_EDGES, OnConEdges)
	ON_COMMAND(ID_CON_CNOISE, OnConCnoise)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_DRAW_FREE, OnDrawFree)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_GETC, OnDrawGetc)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_WND_MAX, OnWndMax)
	ON_COMMAND(ID_CON_UNDO, OnConUndo)
	ON_COMMAND(ID_CON_EDGES2, OnConEdges2)
	ON_COMMAND(ID_CON_NEGAP, OnConNegap)
	ON_COMMAND(ID_CON_BINARY, OnConBinary)
	ON_COMMAND(ID_CON_ADLIGHT, OnConAdlight)
	ON_COMMAND(ID_CON_BESMART, OnConBesmart)
	ON_COMMAND(ID_CON_MOSAIC, OnConMosaic)
	ON_COMMAND(ID_DRAW_CLIP, OnDrawClip)
	ON_COMMAND(ID_DRAW_NOCLIP, OnDrawNoclip)
	ON_COMMAND(ID_CON_SOFT, OnConSoft)
	ON_COMMAND(ID_CON_PREWITT, OnConPrewitt)
	ON_COMMAND(ID_CON_SOBEL, OnConSobel)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_COMMAND(ID_DRAW_SELECTC, OnDrawSelectc)
	ON_COMMAND(ID_CON_ROTATE, OnConRotate)
	ON_COMMAND(ID_CON_ZOOM, OnConZoom)
	ON_COMMAND(ID_CON_ADCENTER, OnConAdcenter)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_FILE_DATAOUT, OnFileDataout)
	ON_COMMAND(ID_FILE_CLEAR, OnFileClear)
	ON_COMMAND(ID_FILE_COPY, OnFileCopy)
	ON_COMMAND(ID_FILE_PASTE, OnFilePaste)
	ON_UPDATE_COMMAND_UI(ID_FILE_PASTE, OnUpdateFilePaste)
	ON_COMMAND(ID_WND_CRATIO, OnWndCratio)
	ON_COMMAND(ID_CON_SSCALE, OnConSscale)
	ON_COMMAND(ID_CON_ADHEIGHT, OnConAdheight)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_FRECT, OnDrawFrect)
	ON_COMMAND(ID_CON_CDCOLOR, OnConCdcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVpcView クラスの構築/消滅

CVpcView::CVpcView()
{
	for (int i = 0; i < 2; i++)
		pBitmap[i] = NULL;
	iCurBmp = 0;
	iDrawMode = 0;
	hCurArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	hCurCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	hCurWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	hCurNormal = AfxGetApp()->LoadCursor(IDC_CUR_NORMAL);
	hCur = hCurNormal;
	crCurCol = atol(AfxGetApp()->GetProfileString("draw", "color", "0"));
	bIsRDown = FALSE;
	cxSpace = 0;
	bWndJust = FALSE;
	fScale = 1.0;
	sFilename = "";
/*	pPalette = NULL;
	CDC* pDC = GetDC();
	int Raster = pDC->GetDeviceCaps(RASTERCAPS);
	Raster = (Raster & RC_PALETTE) ? TRUE : FALSE;
	int nColors = (Raster) ? pDC->GetDeviceCaps(SIZEPALETTE) : pDC->GetDeviceCaps(NUMCOLORS);
	pLogPal = (NPLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * (nColors)));
	ReleaseDC(pDC);
	if (!pLogPal) {
		AfxMessageBox("not enough memory...!?", MB_ICONEXCLAMATION | MB_OK);
	} else {
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = nColors;
		for (int i = 0; i < nColors; i++) {
			pLogPal->palPalEntry[i].peRed = i;
			pLogPal->palPalEntry[i].peBlue = 0;
			pLogPal->palPalEntry[i].peGreen = 0;
			pLogPal->palPalEntry[i].peFlags = PC_EXPLICIT;
		}
		pPalette = new CPalette;
		pPalette->CreatePalette((LPLOGPALETTE)pLogPal);
	}
*/	iMouseFilter = AfxGetApp()->GetProfileInt("draw", "mousefilter", 2);
	bIsDeg = AfxGetApp()->GetProfileInt("dataout", "isdeg", TRUE);
}

CVpcView::~CVpcView()
{
	for (int i = 0; i < 2; i++) {
		if (pBitmap[i]) {
			pBitmap[i]->DeleteObject();
			delete pBitmap[i];
		}
	}
	char* szBuf = new char[33];
	AfxGetApp()->WriteProfileString("draw", "color", _ltoa(crCurCol, szBuf, 10));
	delete szBuf;
/*	if (!pPalette) {
		pPalette->DeleteObject();
		delete pPalette;
	}
	LocalFree(pLogPal);
*/
	AfxGetApp()->WriteProfileInt("draw", "mousefilter", iMouseFilter);
	AfxGetApp()->WriteProfileInt("dataout", "isdeg", bIsDeg);
}

/////////////////////////////////////////////////////////////////////////////
// CVpcView クラスの描画

void CVpcView::OnDraw(CDC* pDC)
{
	CVpcDoc* pDoc = GetDocument();
	
	if (!pBitmap[0]) {
		char far* token = _fstrtok(AfxGetApp()->m_lpCmdLine, " ");
		if (token) {
			FileOpen(token);
			for (;;) {
				token = _fstrtok(NULL, " ");
				if (!token)
					break;
				NewInstance(token);
			}
		} else
			OnFileClear();
	} else {
		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);
		dcMem.SelectObject(pBitmap[iCurBmp]);
//		CPalette* pOldPal = pDC->SelectPalette(pPalette, 0);
//		pDC->RealizePalette();
		pDC->StretchBlt(0, 0, cxClient - cxSpace, cyClient, &dcMem, 0, 0, cxBmp, cyBmp, SRCCOPY);
		
		RECT rect = DRtoCR(reObj);
		rect.top--, rect.left--;
		rect.bottom++, rect.right++;
		pDC->DrawFocusRect(&rect);
/*	
		const int haba = 15;
		const int aki = 3;
		int py = 5;
		for (i = 0; i < 20; i++) {
			int px = 5 + i * (haba + aki);
			CBrush Brs(PALETTEINDEX(i));
			CBrush* oldBrs = pDC->SelectObject(&Brs);
			pDC->Rectangle(px, py, px + haba, py + haba);
			pDC->SelectObject(oldBrs);
		}
		
		int nColors = 256;
		int num = 0, gyo = 0;
		while (num < nColors) {
			int py = 10 +(gyo++) * (haba + aki);
			for (int i = 0; i < 20; i++, num++) {
				if (num >= nColors)
					break;
				int px = 10 + i * (haba + aki);
				CBrush Brs(PALETTEINDEX(num));
				CBrush* oldBrs = pDC->SelectObject(&Brs);
				pDC->Rectangle(px, py, px + haba, py + haba);
				pDC->SelectObject(oldBrs);
			}
			if (num >= nColors)
				break;
		}
*/
//		pDC->SelectPalette(pOldPal, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVpcView クラスの診断

#ifdef _DEBUG
void CVpcView::AssertValid() const
{
	CView::AssertValid();
}

void CVpcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVpcDoc* CVpcView::GetDocument() // デバッグ環境でない場合はインライン展開となります。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVpcDoc)));
	return (CVpcDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVpcView クラスのメッセージ ハンドラ

////////////////////////////////////////////////////////////////////////////
// File I/O

void CVpcView::NewInstance(CString filename)
{
	HINSTANCE hInst = ShellExecute(m_hWnd, NULL, AfxGetApp()->m_pszExeName, filename, NULL, SW_SHOWNORMAL);
	if ((WORD)hInst < 32) {
		char* szMsg = new char[80];
		sprintf(szMsg, "WinExec error : %d", hInst);
		MessageBox(szMsg);
		delete szMsg;
	}
}

void CVpcView::OnFileNew()
{
	CString filter = "Bitmap Files (*.bmp) | *.bmp||";
	CFileDialog dlg(TRUE, "bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if (dlg.DoModal() == IDOK)
		NewInstance(dlg.GetPathName());
}

void CVpcView::OnFileClear()
{
	cxBmp = cxClient, cyBmp = cyClient;
	reObj.top = reObj.left = 0;
	reObj.bottom = cyBmp, reObj.right = cxBmp;
	for (int i = 0; i < 2; i++) {
		if (pBitmap[i]) {
			pBitmap[i]->DeleteObject();
			delete pBitmap[i];
		}
		pBitmap[i] = CreateNewBitmap();
	}
	iCurBmp = 0;
	sFilename = "";
	AfxGetApp()->m_pMainWnd->SetWindowText("VPC");
	OnWndJust();
}

CBitmap* CVpcView::CreateNewBitmap()
{
	CDC dcMem, * pDC = GetDC();
	CBitmap* pBmp = new CBitmap;
	pBmp->CreateCompatibleBitmap(pDC, cxBmp, cyBmp);
	dcMem.CreateCompatibleDC(pDC);
	ReleaseDC(pDC);
	if (!pBmp) {
		MessageBox("Can't get enough memory!", "VPC");
		PostQuitMessage(0);
		return NULL;
	}
	dcMem.SelectObject(pBmp);
	dcMem.PatBlt(0, 0, cxBmp, cyBmp, WHITENESS);
	return pBmp;
}

void CVpcView::OnFileOpen()
{
	CString filter = "Bitmap Files (*.bmp) | *.bmp||";
	CFileDialog dlg(TRUE, "bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if (dlg.DoModal() == IDOK)
		FileOpen(dlg.GetPathName());
}

void CVpcView::FileOpen(CString filename)
{
	if (filename == "")
		OnFileClear();
	SetCursor(hCurWait);
	if (!dib.Read(filename)) {
		MessageBox("Could not open DIB file", "VPC", MB_ICONEXCLAMATION | MB_OK);
		return;
	} else {
		sFilename = filename.Left(filename.GetLength() - 4);
		AfxGetApp()->m_pMainWnd->SetWindowText("VPC - " + ToLowers(sFilename));
	}
	PrepareBitmap();
//	pPalette = dib.CreatePalette(); // ここ！
	SetCursor(hCurNormal);
}

CString CVpcView::ToLowers(CString s)
{
	for (int i = 0; i < s.GetLength(); i++)
		s.SetAt(i, tolower(s.GetAt(i)));
	return s;
}

void CVpcView::PrepareBitmap()
{
	CDC* pDC = GetDC();
	cxBmp = dib.GetWidth(), cyBmp = dib.GetHeight();
	reObj.top = reObj.left = 0;
	reObj.bottom = cyBmp, reObj.right = cxBmp;
	for (int i = 0; i < 2; i++) {
		if (pBitmap[i]) {
			pBitmap[i]->DeleteObject();
			delete pBitmap[i];
		}
		pBitmap[i] = dib.ConvertCBitmap(pDC);
		if (!pBitmap[i]) {
			MessageBox("Can't get enough memory!", "VPC");
			PostQuitMessage(0);
			return;
		}
	}
	iCurBmp = 0;
	ReleaseDC(pDC);
	OnWndJust();
}

void CVpcView::OnFileSaveas()
{
	OnDrawNoclip();
	CString filter = "Bitmap Files (*.bmp) | *.bmp||";
	CFileDialog dlg(FALSE, "bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if (dlg.DoModal() == IDOK) {
		SetCursor(hCurWait);
		CDC* pDC = GetDC();
		dib.RestoreCBitmap(pBitmap[iCurBmp], pDC);
		ReleaseDC(pDC);
		if (!dib.Write(dlg.GetPathName()))
			MessageBox("Could not write DIB file", "VPC", MB_ICONEXCLAMATION | MB_OK);
		SetCursor(hCurNormal);
	}
}

////////////////////////////////////////////////////////////////////////////
// Clipboard

void CVpcView::OnFileCopy()
{
	SetCursor(hCurWait);
	CDC* pDC = GetDC();
	// DIBでコピーする
	dib.RestoreCBitmap(pBitmap[iCurBmp], pDC);
	if (!dib.Copy()) {
		MessageBox("Can't copy", "VPC");
		return;
	}
	// Bitmapでコピーする
/*	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	HBITMAP hbm = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), cxBmp, cyBmp);
	HGDIOBJ hold = SelectObject(dcMem.GetSafeHdc(), hbm);
	CDC dcSrc;
	dcSrc.CreateCompatibleDC(pDC);
	dcSrc.SelectObject(pBitmap[iCurBmp]);
	dcMem.BitBlt(0, 0, cxBmp, cyBmp, &dcSrc, 0, 0, SRCCOPY);
	SelectObject(dcMem.GetSafeHdc(), hold);
	OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbm);
	CloseClipboard();
*/
	ReleaseDC(pDC);
	SetCursor(hCurNormal);
}

void CVpcView::OnFilePaste()
{
	SetCursor(hCurWait);
	// DIBでペーストする
	if (!dib.Paste()) {
		MessageBox("Can't paste", "VPC");
		return;
	}
	PrepareBitmap();
	// Bitmapでペーストする
/*	OpenClipboard();
	HBITMAP hbm = (HBITMAP)GetClipboardData(CF_BITMAP);
	if (!hbm) {
		MessageBox("Can't paste", "VPC");
		CloseClipboard();
		return;
	}
    for (int i = 0; i < 2; i++)
		if (pBitmap[i]) {
			pBitmap[i]->DeleteObject();
			delete pBitmap[i];
		}
    CDC* pDC = GetDC();
	CDC dcSrc;
	dcSrc.CreateCompatibleDC(pDC);
	HGDIOBJ hold = SelectObject(dcSrc.GetSafeHdc(), hbm);
	BITMAP bmp;
	GetObject(hbm, sizeof(BITMAP), &bmp);
	cxBmp = bmp.bmWidth, cyBmp = bmp.bmHeight;
	pDC->BitBlt(0, 0, cxBmp, cyBmp, &dcSrc, 0, 0, SRCCOPY);
	MessageBox("hit");
	pBitmap[0]->CreateCompatibleBitmap(pDC, cxBmp, cyBmp);
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	dcMem.SelectObject(pBitmap[0]);
	dcMem.BitBlt(0, 0, cxBmp, cyBmp, &dcSrc, 0, 0, SRCCOPY);
 	SelectObject(dcSrc.GetSafeHdc(), hold);
	CloseClipboard();
	reObj.top = reObj.left = 0;
	reObj.bottom = cyBmp, reObj.right = cxBmp;
	pBitmap[1]->CreateCompatibleBitmap(pDC, cxBmp, cyBmp);
	dcSrc.SelectObject(pBitmap[1]);
	dcSrc.BitBlt(0, 0, cxBmp, cyBmp, &dcMem, 0, 0, SRCCOPY);
	iCurBmp = 0;
	ReleaseDC(pDC);
	OnWndJust();
*/
	SetCursor(hCurNormal);
}

void CVpcView::OnUpdateFilePaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_DIB));// || IsClipboardFormatAvailable(CF_BITMAP));
}

////////////////////////////////////////////////////////////////////////////
// Others

void CVpcView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	cxClient = cx, cyClient = cy;
	cxSpace = 0;
}

void CVpcView::OnWndJust()
{
	WindowSize(cxBmp, cyBmp);
}

void CVpcView::WindowSize(int cx, int cy)
{
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_RESTORE);
	int cWndx = cx + GetSystemMetrics(SM_CXFRAME) * 2;
	int cWndy = cy + GetSystemMetrics(SM_CYFRAME) * 2
			+ GetSystemMetrics(SM_CYCAPTION) - GetSystemMetrics(SM_CYBORDER);
	AfxGetApp()->m_pMainWnd->SetWindowPos(&wndTop, 0, 0, cWndx, cWndy, SWP_NOMOVE);
	LPRECT lpRect = new RECT;
	GetClientRect(lpRect);
	if (lpRect->right != cx)
		cxSpace = lpRect->right - cx;
	delete lpRect;
    bWndJust = TRUE;
	InvalidateRect(NULL);
}

void CVpcView::OnWndMax()
{
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);	
}

void CVpcView::OnWndCratio()
{
	if ((double)cxClient / cyClient > (double)cxBmp / cyBmp) {
		cxClient = (long)cyClient * cxBmp / cyBmp;
	} else {
		cyClient = (long)cxClient * cyBmp / cxBmp;
	}
	WindowSize(cxClient, cyClient);
}

BOOL CVpcView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(hCur);
	return TRUE;
//	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CVpcView::BeginConvert(BOOL bSetCur, BOOL bCopy)
{
	if (bSetCur) {
		SetCursor(hCur = hCurWait);
		bCopy = TRUE;
	}
	CDC* pDCDis = GetDC();
	pOldDC = new CDC;
	pOldDC->CreateCompatibleDC(pDCDis);
	pNewDC = new CDC;
	pNewDC->CreateCompatibleDC(pDCDis);
	ReleaseDC(pDCDis);
	pOldDC->SelectObject(pBitmap[iCurBmp]);
	iCurBmp = 1 - iCurBmp;	// Bitmapが２個の場合のみ通用
	pNewDC->SelectObject(pBitmap[iCurBmp]);
	if (bCopy)
		pNewDC->BitBlt(0, 0, cxBmp, cyBmp, pOldDC, 0, 0, SRCCOPY);	
}

void CVpcView::EndConvert(BOOL bSetCur, LPRECT pRect)
{
	delete pOldDC;
	delete pNewDC;
	if (bSetCur)
		SetCursor(hCur = hCurNormal);
	InvalidateRect(pRect, FALSE);
}

////////////////////////////////////////////////////////////////////////////
// Drag && Drop

void CVpcView::OnDropFiles(HDROP hDropInfo)
{
	char* filename = new char[128];
	int iFiles = DragQueryFile(hDropInfo, -1, filename, 128);
	if (iFiles > 64)
		iFiles = 64;
	DragQueryFile(hDropInfo, 0, filename, 128);
	FileOpen(filename);
	for (int i = 1;	i < iFiles; i++) {
		DragQueryFile(hDropInfo, i, filename, 128);
		NewInstance(filename);
	}
	delete filename;
	CView::OnDropFiles(hDropInfo);
}

int CVpcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	DragAcceptFiles();
	return 0;
}

void CVpcView::OnDestroy()
{
	CView::OnDestroy();
	DragAcceptFiles(FALSE);
}

////////////////////////////////////////////////////////////////////////////
// Draw Functions

void CVpcView::BeginDraw(int iMode)
{
	iDrawMode = iMode;
	bNewLine = FALSE;
	SetCursor(hCur = hCurArrow);
	MouseFilter();
}

void CVpcView::EndDraw()
{
	iDrawMode = 0;
	SetCursor(hCur = hCurNormal);
	MouseFilter(FALSE);
}

void CVpcView::MouseFilter(BOOL bSet)
{
	if (bSet) {
		switch (iMouseFilter) {
		case 0:
			// nothing;
			break;
		case 1:
			SetCapture();
			break;
		case 2:
			RECT rc;
			GetClientRect(&rc);
			ClientToScreen(&rc);
			ClipCursor(&rc);
			break;
		}
	} else {
		switch (iMouseFilter) {
		case 0:
			// nothing;
			break;
		case 1:
			ReleaseCapture();
			break;
		case 2:
			ClipCursor(NULL);
			break;
		}
	}
}

void CVpcView::OnDrawFree()
{
	BeginDraw(1);
}

void CVpcView::OnDrawLine()
{
	BeginDraw(8);
}

void CVpcView::OnDrawFrect()
{
	BeginDraw(9);
}

void CVpcView::OnDrawGetc()
{
	BeginDraw(2);
}

void CVpcView::OnDrawSelectc()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		crCurCol = dlg.GetColor();
	}
}

void CVpcView::OnDrawClip()
{
	BeginDraw(3);
}

void CVpcView::OnDrawNoclip()
{
	reObj.top = reObj.left = 0;
	reObj.bottom = cyBmp, reObj.right = cxBmp;
	Invalidate(FALSE);
}

void CVpcView::OnLButtonDown(UINT nFlags, CPoint p)
{
	bIsRDown = TRUE;
	POINT point = CPtoDP(p);
	RECT rect;
	CDC* pDC;
	switch (iDrawMode) {
	case 1:
		poBuf = point;
		BeginConvert(FALSE, TRUE);
		EndConvert(FALSE);
		OnConUndo();
		break;
	case 2:
		BeginConvert(FALSE);
		crCurCol = pOldDC->GetPixel(point);
		iCurBmp = 1 - iCurBmp; // Bitmapが２個のときだけ
		EndConvert(FALSE);
		EndDraw();
		Invalidate(FALSE);
		break;
	case 3:	case 9:
		reBak = reObj;
		reObj.top = reObj.bottom = point.y;
		reObj.left = reObj.right = point.x;
 		pDC = GetDC();
		rect = DRtoCR(reBak);
		rect.top--, rect.left--;
		rect.bottom++, rect.right++;
		pDC->DrawFocusRect(CorrectRect(rect));
		rect = DRtoCR(reObj);
		pDC->DrawFocusRect(CorrectRect(rect));
		ReleaseDC(pDC);
//      MouseFilter();
        break;
	case 4:	case 6:	case 7:	case 8:
		cpMv = cpLn = point;
//		MouseFilter();
		break;
	case 5:
		AdjustCenter(point);
		EndDraw();
		break;
	}
	CView::OnLButtonDown(nFlags, p);
}

void CVpcView::OnMouseMove(UINT nFlags, CPoint p)
{
	if (!iDrawMode) {
		CView::OnMouseMove(nFlags, p);
		return;
	}

	POINT point = CPtoDP(p);
	if (iDrawMode != 1) {
		static CPoint cpBuf;
		CDC* pDC = GetDC();
		CPen* pPen = new CPen;
		pPen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(pPen);
		pDC->SetROP2(R2_XORPEN);
		if (bNewLine) {
            pDC->MoveTo(0, cpBuf.y);
			pDC->LineTo(cxClient, cpBuf.y);
			pDC->MoveTo(cpBuf.x, 0);
			pDC->LineTo(cpBuf.x, cyClient);
		} else
			bNewLine = TRUE;
		cpBuf = p;
		pDC->MoveTo(0, cpBuf.y);
		pDC->LineTo(cxClient, cpBuf.y);
		pDC->MoveTo(cpBuf.x, 0);
		pDC->LineTo(cpBuf.x, cyClient);
		pDC->SelectObject(pOldPen);
		delete pPen;
		ReleaseDC(pDC);
	}

	if (!bIsRDown && iDrawMode != 5) {
		CView::OnMouseMove(nFlags, p);
		return;
	}
	CPen* pPen, * pOldPen;
	CDC* pDC;
	RECT rect;
	switch (iDrawMode) {
	case 1:
		iCurBmp = 1 - iCurBmp;
		BeginConvert(FALSE);
		pPen = new CPen;
		pPen->CreatePen(PS_SOLID, 1, crCurCol);
		pOldPen = pNewDC->SelectObject(pPen);
		pNewDC->MoveTo(poBuf);
		pNewDC->LineTo(point);
		rect.left = poBuf.x, rect.top = poBuf.y;
		poBuf = point;
		pNewDC->SelectObject(pOldPen);
		pPen->DeleteObject();
		delete pPen;
		rect.right = poBuf.x, rect.bottom = poBuf.y;
		CorrectRect(rect);
		rect.top--, rect.left--, rect.bottom++, rect.right++;
		rect = DRtoCR(rect);
		EndConvert(FALSE, &rect);
		break;
	case 3: case 9:
		pDC = GetDC();
		rect = DRtoCR(reObj);
		pDC->DrawFocusRect(CorrectRect(rect));
		reObj.bottom = point.y + 1;
		reObj.right = point.x + 1;
		rect = DRtoCR(reObj);
		pDC->DrawFocusRect(CorrectRect(rect));
		ReleaseDC(pDC);
		break;
	case 4:	case 6:	case 7: case 8:
		pDC = GetDC();
		pPen = new CPen;
		pPen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		pOldPen = pDC->SelectObject(pPen);
        pDC->SetROP2(R2_XORPEN);
		pDC->MoveTo(DPtoCP(cpMv));
		pDC->LineTo(DPtoCP(cpLn));
		cpLn = point;
		pDC->MoveTo(DPtoCP(cpMv));
		pDC->LineTo(DPtoCP(cpLn));
		pDC->SelectObject(pOldPen);
		delete pPen;
		ReleaseDC(pDC);
		break;
	}
	CView::OnMouseMove(nFlags, p);
}

void CVpcView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!bIsRDown) {
		CView::OnLButtonUp(nFlags, point);
		return;
	}
		bIsRDown = FALSE;
	double rad, a, b, c, d;
	CValueDlg dlg;
	char* szBuf;
	CPen* pPen, * pOldPen;
	CBrush* pBrush;
	switch (iDrawMode) {
	case 1:
		EndDraw();
//		MouseFilter(FALSE);
		break;
	case 3:
		CorrectRect(reObj);
		EndDraw();
		Invalidate(FALSE);
//		MouseFilter(FALSE);
		break;
	case 4:
		cpLn.x -= cpMv.x, cpLn.y -= cpMv.y;
		rad = PI / 2 - atan2(cpLn.y, cpLn.x);
		//double a, b, c, d;
		a = cos(rad), c = sin(rad);
		b = cos(rad + PI / 2), d = sin(rad + PI / 2);
		Linear(a, b, c, d);
		EndDraw();
//		MouseFilter(FALSE);
		break;
	case 6:
		EndDraw();
//		MouseFilter(FALSE);
		dlg.csMess = "実際の長さをmmで入力。";
		dlg.m_value = AfxGetApp()->GetProfileInt("value", "Adscale", 300);
		if (dlg.DoModal() == IDOK) {
			AfxGetApp()->WriteProfileInt("value", "Adscale", dlg.m_value);
			cpLn.x -= cpMv.x, cpLn.y -= cpMv.y;
			fScale = (float)dlg.m_value / (float)sqrt(cpLn.x * cpLn.x + cpLn.y * cpLn.y);
		}
		Invalidate(FALSE);
		break;
	case 7:
		EndDraw();
//		MouseFilter(FALSE);
		cpLn.y -= cpMv.y;
		szBuf = new char[17];
		dlg.csMess = "揃える長さをpixelで入力(org." + CString(_itoa(cpLn.y, szBuf, 10)) + ")";
		delete szBuf;
		dlg.m_value = AfxGetApp()->GetProfileInt("value", "Adheight", 150);
		if (dlg.DoModal() == IDOK) {
			AfxGetApp()->WriteProfileInt("value", "Adheight", dlg.m_value);
			a = d = (double)dlg.m_value / cpLn.y, b = c = 0;
			Linear(a, b, c, d);		
	    } else
			Invalidate(FALSE);
		break;
	case 8:
		EndDraw();
//		MouseFilter(FALSE);
		BeginConvert();
		pPen = new CPen;
		pPen->CreatePen(PS_SOLID, 1, crCurCol);
		pOldPen = pNewDC->SelectObject(pPen);
		pNewDC->MoveTo(cpMv);
		pNewDC->LineTo(cpLn);
		pNewDC->SelectObject(pOldPen);
		pPen->DeleteObject();
		delete pPen;
		EndConvert();
		break;
	case 9:
		EndDraw();
//		MouseFilter(FALSE);
		BeginConvert();
		pBrush = new CBrush;
		CorrectRect(reObj);
		pBrush->CreateSolidBrush(crCurCol);
		pNewDC->FillRect(&reObj, pBrush);
		reObj = reBak;
		delete pBrush;
		EndConvert();
		break;
	}
	CView::OnLButtonUp(nFlags, point);
}

void CVpcView::OnRButtonDown(UINT nFlags, CPoint point)
{
	switch (iDrawMode) {
	case 1:
		OnLButtonUp(nFlags, point);
		OnConUndo();
		break;
	case 2:
		bIsRDown = FALSE;
		EndDraw();
		Invalidate(FALSE);
		break;
	case 3:	case 9:
		reObj = reBak;
		OnLButtonUp(nFlags, point);
		break;
	case 4: case 5: case 6: case 7:
		bIsRDown = FALSE;
		EndDraw();
		Invalidate(FALSE);
		break;
	}
	CMenu bar;
	if (!iDrawMode && bar.LoadMenu(IDR_POPUP_MENU)) {
		CMenu& popup = *bar.GetSubMenu(0);
		ASSERT(popup.m_hMenu != NULL);
		ClientToScreen(&point);
		popup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetApp()->m_pMainWnd);
	}
	
	CView::OnRButtonDown(nFlags, point);
}

#pragma warning (disable : 4135) // int = long 文の為

POINT CVpcView::CPtoDP(POINT point)
{
	POINT p;
	p.x = (long)point.x * cxBmp / (cxClient - cxSpace);
	p.y = (long)point.y * cyBmp / cyClient;
	if (p.x > cxClient - cxSpace - 1)
		p.x = cxClient - cxSpace - 1;
	if (p.x < 0)
		p.x = 0;
	if (p.y > cyClient - 1)
		p.y = cyClient - 1;
	if (p.y < 0)
		p.y = 0;
	return p;
}

POINT CVpcView::DPtoCP(POINT point)
{
	POINT p;
	p.x = DXtoCX(point.x);//(long)point.x * (cxClient - cxSpace) / cxBmp;
	p.y = DYtoCY(point.y);(long)point.y * cyClient / cyBmp;
	return p;
}

RECT CVpcView::DRtoCR(RECT rect)
{
	RECT r;
	r.top = DYtoCY(rect.top);//(long)rect.top * cyClient / cyBmp;
	r.bottom = DYtoCY(rect.bottom);//(long)rect.bottom * cyClient / cyBmp;
	r.left = DXtoCX(rect.left);//(long)rect.left * (cxClient - cxSpace) / cxBmp;
	r.right = DXtoCX(rect.right);//(long)rect.right * (cxClient - cxSpace) / cxBmp;
	return r;
}

RECT* CVpcView::CorrectRect(RECT& rect)
{
	int buf;
	if (rect.top > rect.bottom)
		buf = rect.bottom, rect.bottom = rect.top, rect.top = buf;
	if (rect.left > rect.right)
		buf = rect.right, rect.right = rect.left, rect.left = buf;
	return &rect;
}

////////////////////////////////////////////////////////////////////////////
// Data Out

void CVpcView::OnFileDataout()
{
	int mid = cxBmp / 2;//(reObj.right + reObj.left) / 2;
	if (reObj.left > mid || reObj.right < mid) {
		MessageBox("Illegal clip\n  Please retry.", "VPC");
		return;
	}
	CString sPathName = sFilename;
	if (sPathName == "") {
		CString filter = "VPC Data Files (*.dat) | *.dat||";
		CFileDialog dlg(FALSE, "txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
		if (dlg.DoModal() == IDOK)
			sPathName = dlg.GetPathName();
	} else
		sPathName += ".dat";
	if (sPathName != "") {
		ofstream out(sPathName);
		if (!out)
			MessageBox("Can't open Data File.", "VPC");
		CValueDlg dlg;
		dlg.csMess = "入力画像数";
		dlg.m_value = 8;//AfxGetApp()->GetProfileInt("value", "dataout", 8);
		//if (dlg.DoModal() == IDOK)
		//	AfxGetApp()->WriteProfileInt("value", "dataout", dlg.m_value);
		BeginConvert();
		float* fRdata = new float[reObj.bottom - reObj.top];
		float* fLdata = new float[reObj.bottom - reObj.top];
		int iArrN = 0;
		for (int i = reObj.top; i < reObj.bottom; i++) {
			fRdata[iArrN] = 0;
			for (int j = reObj.right - 1; j >= mid; j--) {
				if (fRdata[iArrN])
					pNewDC->SetPixel(j, i, RGB(0, 255, 0));
				else if (pOldDC->GetPixel(j, i))
					fRdata[iArrN] = fScale * (j - mid);
			}
			fLdata[iArrN] = 0;
			for (j = reObj.left; j <= mid; j++) {
				if (fLdata[iArrN])
					pNewDC->SetPixel(j, i, RGB(255, 0, 0));
				else if (pOldDC->GetPixel(j, i))
					fLdata[iArrN] = fScale * (mid - j);
			}
			if (*fRdata || *fLdata)
				iArrN++;
		}
		int	iHeight = 0;
		for (i = --iArrN; i >= 0; i--) {
			if (!fRdata[i] && !fLdata[i] && !iHeight)
				continue;
			out.precision(7);
			if (!iHeight) {
				double deg = 90.0 - (double)(*(strchr(sPathName, '.') - 1) - '1') * 180.0 / dlg.m_value;
				if (bIsDeg)
					out << deg << endl;
				else
					out << deg / 180.0 * PI << endl;
				//out << i + 1 << " " << fScale << endl;
			}
			out << fScale * iHeight++ << " " << fRdata[i] << " " << fLdata[i] << endl;
		}
		out.close();
		delete fRdata;
		delete fLdata;				
		EndConvert();
		char* szInifile = new char[256];
		strcpy(szInifile, sPathName);
		*(strchr(szInifile, '.') - 1) = '\0';
		strcat(szInifile, ".ini");
		ifstream ifIni(szInifile);
		int iN, iAngle;
		ifIni >> iN;
		if (ifIni.eof()) {
			iN = iHeight;
			iAngle = 0;
		} else {
			if (iN != iHeight)	{
				char* buf = new char[256];
				wsprintf(buf, "not collect size\nN = %d\tH = %d", iN, iHeight);
				MessageBox(buf);
				delete buf;
				iN = __min(iN, iHeight);
			}
			//ifIni >> iAngle;
		}
		ifIni.close();
		ofstream ofIni(szInifile);
		ofIni << iN << endl;
		ofIni << dlg.m_value << endl;//++iAngle << endl;
		char* buf = new char[256];
		strcpy(buf, szInifile);
		*strchr(buf, '.') = '\0';
		ofIni << buf << endl;
		delete buf;
		ofIni.close();
		delete szInifile;
	}
}
