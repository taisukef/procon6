/////////////////////////////////////////////////////////////////////////////
// DIB 楽々クラス

#include "stdafx.h"
#include "dib.h"

CDIB::CDIB()
{
	hglbDib = NULL;
}

CDIB::~CDIB()
{
	if (hglbDib)
		GlobalFree(hglbDib);
}

WORD CDIB::GetBitCount()
{
	BYTE huge* lpDib = Lock();
	if (!lpDib)
		return 0;
	WORD bc = GetBitCount(lpDib);
	Unlock();
	return bc;
}

DWORD CDIB::GetInfoHeaderSize()
{
	BYTE huge* lpDib = Lock();
	if (!lpDib)
		return 0;
	DWORD size = GetInfoHeaderSize(lpDib);
	Unlock();
	return size;
}

WORD CDIB::GetWidth(BYTE huge* lpDib)
{
	if (GetInfoHeaderSize(lpDib) == sizeof (BITMAPCOREHEADER))
		return (WORD) (((BITMAPCOREHEADER huge*)lpDib)->bcWidth);
	else
		return (WORD) (((BITMAPINFOHEADER huge*)lpDib)->biWidth);
}

WORD CDIB::GetWidth()
{
	BYTE huge* lpDib = Lock();
	if (!lpDib)
		return 0;
	WORD width = GetWidth(lpDib);
	Unlock();
	return width;
}

WORD CDIB::GetHeight(BYTE huge* lpDib)
{
	if (GetInfoHeaderSize() == sizeof (BITMAPCOREHEADER))
		return (WORD) (((BITMAPCOREHEADER huge*)lpDib)->bcHeight);
	else
		return (WORD) (((BITMAPINFOHEADER huge*)lpDib)->biHeight);
}

WORD CDIB::GetHeight()
{
	BYTE huge* lpDib = Lock();
	if (!lpDib)
		return 0;
	WORD height = GetHeight(lpDib);
	Unlock();
	return height;
}
BYTE huge* CDIB::GetBitsAddr(BYTE huge* lpDib)
{
	DWORD dwNumColors, dwColorTableSize;
	WORD  wBitCount;

	if (GetInfoHeaderSize(lpDib) == sizeof(BITMAPCOREHEADER)) {
		wBitCount = ((BITMAPCOREHEADER huge*)lpDib)->bcBitCount;

		if (wBitCount != 24)
			dwNumColors = 1L << wBitCount;
		else
			dwNumColors = 0;

		dwColorTableSize = dwNumColors * sizeof(RGBTRIPLE);
	} else {
		wBitCount = ((BITMAPINFOHEADER huge*)lpDib)->biBitCount;

		if (GetInfoHeaderSize(lpDib) >= 36)
			dwNumColors = ((BITMAPINFOHEADER huge*)lpDib)->biClrUsed;
		else
			dwNumColors = 0;

		if (dwNumColors == 0) {
			if (wBitCount != 24)
				dwNumColors = 1L << wBitCount;
			else
				dwNumColors = 0;
		}

		dwColorTableSize = dwNumColors * sizeof(RGBQUAD);
	}

	return lpDib + GetInfoHeaderSize(lpDib) + dwColorTableSize;
}

BOOL CDIB::Read(const char* szFileName) // Read a DIB from a file into memory
{
	BYTE huge* lpDib;
	DWORD dwDibSize, dwHeaderSize;
	HFILE hFile;

	if (hglbDib)
		GlobalFree(hglbDib);

	OFSTRUCT of;
	if (HFILE_ERROR == (hFile = OpenFile(szFileName, &of, OF_READ | OF_SHARE_DENY_WRITE)))
		return FALSE;
    
	BITMAPFILEHEADER bmfh;
	if (_hread (hFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER)) {
		_lclose(hFile);
		return FALSE;
	}

	if (bmfh.bfType != *(WORD*)"BM") {
		_lclose(hFile);
		return FALSE;
	}

	dwDibSize = bmfh.bfSize - sizeof(BITMAPFILEHEADER);

	hglbDib = GlobalAlloc(GMEM_MOVEABLE, dwDibSize);

	if (!hglbDib) {
		_lclose(hFile);
		return FALSE;
	}

	lpDib = (BYTE huge*)GlobalLock(hglbDib);

	if (dwDibSize != (DWORD)_hread(hFile, lpDib, dwDibSize)) {
		_lclose(hFile);
		GlobalUnlock(hglbDib);
		GlobalFree(hglbDib);
		hglbDib = NULL;
		return FALSE;
	}

	_lclose(hFile);

	dwHeaderSize = GetInfoHeaderSize(lpDib);

	if (dwHeaderSize < 12 || (dwHeaderSize > 12 && dwHeaderSize < 16)) {
		GlobalUnlock(hglbDib);
		GlobalFree(hglbDib);
		hglbDib = NULL;
		return FALSE;
	}

//	char* buf = new char[256];
//	wsprintf(buf, "%d : %d", sizeof(BITMAPINFOHEADER), GetInfoHeaderSize(lpDib));
//	AfxMessageBox(buf);
//	delete buf;

	GlobalUnlock(hglbDib);
	return TRUE;
}

BOOL CDIB::Write(const char* szFileName)
{
	BYTE huge* lpDib;
	DWORD dwDibSize;
	HFILE hFile;

	if (!hglbDib)
		return FALSE;

	OFSTRUCT of;
	if (HFILE_ERROR == (hFile = OpenFile(szFileName, &of, OF_CREATE | OF_WRITE | OF_SHARE_DENY_WRITE)))
		return FALSE;
    
	lpDib = (BYTE huge*)GlobalLock(hglbDib);

	BITMAPFILEHEADER bmfh = MakeBmfh(lpDib);
	if (_hwrite (hFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER)) {
		_lclose(hFile);
		return FALSE;
	}

	dwDibSize = bmfh.bfSize - sizeof(BITMAPFILEHEADER);

	if (dwDibSize != (DWORD)_hwrite(hFile, (LPSTR)lpDib, dwDibSize)) {
		_lclose(hFile);
		return FALSE;
	}

	_lclose(hFile);

	GlobalUnlock(hglbDib);
	return TRUE;
}

int CDIB::StretchDIBits(HDC hdc, int XDest, int YDest, int cxDest, int cyDest,
		int XSrc, int YSrc, int cxSrc, int cySrc, UINT fuColorUse, DWORD fdwRop) {
	if (!hglbDib)
		return 0;
	BYTE huge* lpDib = Lock();
	int ret = ::StretchDIBits(hdc, XDest, YDest, cxDest, cyDest, XSrc, YSrc, cxSrc, cySrc,
			GetBitsAddr(lpDib), (LPBITMAPINFO)lpDib, fuColorUse, fdwRop);
	Unlock();
	return ret;
}

CBitmap* CDIB::ConvertCBitmap(CDC* pDC)
{
	CBitmap* pBitmap = new CBitmap;
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	WORD x = GetWidth(), y = GetHeight();
	if (!pBitmap->CreateCompatibleBitmap(pDC, x, y))
		return NULL;
	dcMem.SelectObject(pBitmap);
	StretchDIBits(dcMem.GetSafeHdc(), 0, 0, x, y, 0, 0, x, y, DIB_RGB_COLORS, SRCCOPY);
	return pBitmap;
}

BOOL CDIB::RestoreCBitmap(CBitmap* pBitmap, CDC* pDC)
{
	if (!hglbDib)
		return FALSE;
//	GlobalFree(hglbDib);
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	BITMAP bitmap;
	pBitmap->GetObject(sizeof(BITMAP), &bitmap);
	WORD cx = bitmap.bmWidth, cy = bitmap.bmHeight;
	HBITMAP hbm = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), cx, cy);
	HGDIOBJ hold = SelectObject(dcMem.GetSafeHdc(), hbm);
	CDC dcSrc;
	dcSrc.CreateCompatibleDC(pDC);
	dcSrc.SelectObject(pBitmap);
	dcMem.BitBlt(0, 0, cx, cy, &dcSrc, 0, 0, SRCCOPY);
	SelectObject(dcMem.GetSafeHdc(), hold);
//	hglbDib = GlobalAlloc(GMEM_MOVEABLE, (DWORD)bitmap.bmWidthBytes * bitmap.bmHeight * bitmap.bmPlanes + sizeof(BITMAPINFO));
		// BITMAPINFOのサイズがよく分からないから、足りてないかもしれない。
//	if (!hglbDib)
//		return FALSE;
	BYTE huge* lpDib = Lock();
//	GetDIBits(pDC->GetSafeHdc(), hbm, 0, cy, NULL, (LPBITMAPINFO)lpDib, DIB_RGB_COLORS);
	GetDIBits(pDC->GetSafeHdc(), hbm, 0, cy, GetBitsAddr(lpDib), (LPBITMAPINFO)lpDib, DIB_RGB_COLORS);
	Unlock();
	DeleteObject(hbm);
	return TRUE;
}

BOOL CDIB::Copy()
{
	if (!hglbDib)
		return FALSE;
	HGLOBAL hClip = GlobalAlloc(GHND, GlobalSize(hglbDib));
	if (!hClip) {
		CloseClipboard();
		return FALSE;
	}
	BYTE huge* lpClip = (BYTE huge*)GlobalLock(hClip);
	BYTE huge* lpDib = (BYTE huge*)GlobalLock(hglbDib);
	for (DWORD i = 0; i < GlobalSize(hglbDib); i++)
		*lpClip++ = *lpDib++;
	GlobalUnlock(hClip);
	GlobalUnlock(hglbDib);
	if (!OpenClipboard(NULL)) {
		CloseClipboard();
		return FALSE;
	}
	EmptyClipboard();
	SetClipboardData(CF_DIB, hClip);
	CloseClipboard();
	return TRUE;
}

BOOL CDIB::Paste()
{
	if (hglbDib)
		GlobalFree(hglbDib);
	if (!OpenClipboard(NULL)) {
		CloseClipboard();
		return FALSE;
	}
	HGLOBAL hClip = GetClipboardData(CF_DIB);
	if (!hClip) {
		CloseClipboard();
		return FALSE;
	}
	hglbDib = GlobalAlloc(GMEM_MOVEABLE, GlobalSize(hClip));
	if (!hglbDib) {
		CloseClipboard();
		return FALSE;
	}
	BYTE huge* lpClip = (BYTE huge*)GlobalLock(hClip);
	BYTE huge* lpDib = (BYTE huge*)GlobalLock(hglbDib);
	for (DWORD i = 0; i < GlobalSize(hClip); i++)
		*lpDib++ = *lpClip++;
	GlobalUnlock(hClip);
	GlobalUnlock(hglbDib);
	CloseClipboard();
	return TRUE;
}

BITMAPFILEHEADER CDIB::MakeBmfh(BYTE huge* lpDib)
{
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = *(WORD*)"BM";
    bmfh.bfSize = GlobalSize(hglbDib) + sizeof(BITMAPFILEHEADER);
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = (DWORD)GetBitsAddr(lpDib) - (DWORD)lpDib + sizeof(BITMAPFILEHEADER);
	return bmfh;
}
/*
CPalette* CDIB::CreatePalette()
{
	BYTE huge* lpDib = Lock();
	if (!lpDib)
		return NULL;
	BITMAPINFOHEADER huge* pInfHd = (BITMAPINFOHEADER huge*)lpDib;
	RGBQUAD huge* rgb = (RGBQUAD huge*)GetBitsAddr(lpDib);
	WORD nColors = !pInfHd->biClrUsed ? (0x01 << ((pInfHd->biBitCount) * (pInfHd->biPlanes))) :
										(WORD)(pInfHd->biClrUsed);
	NPLOGPALETTE pLogPal = (NPLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors));
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = nColors;
	for (int i = 0; i < (int)nColors; i++) {
   		pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
		pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
		pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
		pLogPal->palPalEntry[i].peFlags = NULL;
	}
	CPalette* pPalette = new CPalette;
	pPalette->CreatePalette((LPLOGPALETTE)pLogPal);
	LocalFree((HLOCAL)pLogPal);
	Unlock();
	return pPalette;
}
*/