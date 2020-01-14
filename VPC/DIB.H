#ifndef ___CDIB
#define ___CDIB

class CDIB {
protected:
	HGLOBAL hglbDib;
	BYTE huge* Lock() { return (BYTE huge*)GlobalLock(hglbDib); }
	BOOL Unlock() { return GlobalUnlock(hglbDib); }
	BYTE huge* GetBitsAddr(BYTE huge*);
	WORD GetBitCount(BYTE huge* lp) { return ((BITMAPINFOHEADER huge*)lp)->biBitCount; }
	DWORD GetInfoHeaderSize(BYTE huge* lp) { return ((BITMAPINFOHEADER huge*)lp)->biSize; }
	WORD GetWidth(BYTE huge*);
	WORD GetHeight(BYTE huge*);
	BITMAPFILEHEADER MakeBmfh(BYTE huge*);
public:
	CDIB();
	~CDIB();
	WORD GetBitCount();
	DWORD GetInfoHeaderSize();
	WORD GetWidth();
	WORD GetHeight();
	BOOL Read(const char* szFileName);
	BOOL Write(const char* szFileName);
	int StretchDIBits(HDC, int, int, int, int, int, int, int, int, UINT, DWORD);
	BOOL IsRead() { return hglbDib ? TRUE : FALSE; }
	CBitmap* ConvertCBitmap(CDC*);	// 要delete && DeleteObject
	BOOL RestoreCBitmap(CBitmap*, CDC*);  // 元のDIBデータと同じサイズのみ。現在変更中。
//	CPalette* CreatePalette();  // 要delete && DeleteObject -- 失敗
	BOOL Copy();
	BOOL Paste();
};

#endif
							  