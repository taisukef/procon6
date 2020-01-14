#ifndef ___CLRGB
#define ___CLRGB

#pragma warning (disable : 4051)
#pragma warning (disable : 4135)

class CLRGB {
protected:
	BYTE FitByte(long);
public:
	long iR, iG, iB;
	CLRGB(COLORREF cr = 0) { iR = GetRValue(cr), iG = GetGValue(cr), iB = GetBValue(cr); }
	CLRGB(long r, long g, long b) { iR = r, iG = g, iB = b; }
	BYTE GetR() { return FitByte(iR); }
	BYTE GetG() { return FitByte(iG); }
	BYTE GetB() { return FitByte(iB); }
	long Density() { return .299 * iR + .587 * iG + .114 * iB; }
	CLRGB operator+(CLRGB c) { return CLRGB(iR + c.iR, iG + c.iG, iB + c.iB); }
	CLRGB operator-() { return CLRGB(255 - iR, 255 - iG, 255 - iB); }
	CLRGB operator-(CLRGB c) { return CLRGB(iR - c.iR, iG - c.iG, iB - c.iB); }
	CLRGB operator*(double a) { return CLRGB(a * iR, a * iG, a * iB); }
	CLRGB operator*(int a) { return CLRGB(a * iR, a * iG, a * iB); }
	CLRGB operator/(double a) { return CLRGB((double)iR / a, (double)iG / a, (double)iB / a); }
	CLRGB operator/(int a) { return CLRGB(iR / a, iG / a, iB / a); }
	CLRGB operator+=(CLRGB c) { return *this = *this + c; }
	CLRGB operator-=(CLRGB c) { return *this = *this - c; }
	CLRGB operator*=(double a) { return *this = *this * a; }
	CLRGB operator*=(int a) { return *this = *this * a; }
	CLRGB operator/=(double a) { return *this = *this / a; }
   	CLRGB operator/=(int a) { return *this = *this / a; }
   	friend CLRGB abs(CLRGB);
	friend CLRGB average(CLRGB, CLRGB);
   	operator COLORREF() { return RGB(FitByte(iR), FitByte(iG), FitByte(iB)); }
};

#endif
