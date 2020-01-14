#ifndef ___CRGB
#define ___CRGB

#pragma warning (disable : 4051)

class CRGB {
protected:
	BYTE FitByte(int);
public:
	int iR, iG, iB;
	CRGB(COLORREF cr = 0) { iR = GetRValue(cr), iG = GetGValue(cr), iB = GetBValue(cr); }
	CRGB(int r, int g, int b) { iR = r, iG = g, iB = b; }
	BYTE GetR() { return FitByte(iR); }
	BYTE GetG() { return FitByte(iG); }
	BYTE GetB() { return FitByte(iB); }
	int Density() { return .299 * iR + .587 * iG + .114 * iB; }
	CRGB operator+(CRGB c) { return CRGB(iR + c.iR, iG + c.iG, iB + c.iB); }
	CRGB operator-() { return CRGB(255 - iR, 255 - iG, 255 - iB); }
	CRGB operator-(CRGB c) { return CRGB(iR - c.iR, iG - c.iG, iB - c.iB); }
	CRGB operator*(double a) { return CRGB(a * iR, a * iG, a * iB); }
	CRGB operator*(int a) { return CRGB(a * iR, a * iG, a * iB); }
	CRGB operator/(double a) { return CRGB((double)iR / a, (double)iG / a, (double)iB / a); }
	CRGB operator/(int a) { return CRGB(iR / a, iG / a, iB / a); }
	CRGB operator+=(CRGB c) { return *this = *this + c; }
	CRGB operator-=(CRGB c) { return *this = *this - c; }
	CRGB operator*=(double a) { return *this = *this * a; }
	CRGB operator*=(int a) { return *this = *this * a; }
	CRGB operator/=(double a) { return *this = *this / a; }
   	CRGB operator/=(int a) { return *this = *this / a; }
   	friend CRGB abs(CRGB);
   	operator COLORREF() { return RGB(FitByte(iR), FitByte(iG), FitByte(iB)); }
};

#endif
