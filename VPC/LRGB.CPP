//////////////////////////////////////////
// RGB 楽々クラス (long)

#include "stdafx.h"
#include "lrgb.h"
#include "math.h"

BYTE CLRGB::FitByte(long n)
{
	if (n < 0)
		return 0;
	if (n > 255)
		return 255;
	return n;
}

CLRGB abs(CLRGB rgb)
{
	return CLRGB(::abs(rgb.iR), ::abs(rgb.iG), ::abs(rgb.iB));
}

CLRGB average(CLRGB a, CLRGB b)
{
	return CLRGB(::sqrt(a.iR * a.iR + b.iR * b.iR),
				 ::sqrt(a.iG * a.iG + b.iG * b.iG),
				 ::sqrt(a.iB * a.iB + b.iB * b.iB));
}
