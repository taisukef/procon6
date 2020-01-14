//////////////////////////////////////////
// RGB äyÅXä÷êî

#include "stdafx.h"
#include "rgb.h"

BYTE CRGB::FitByte(int n)
{
	if (n < 0)
		return 0;
	if (n > 255)
		return 255;
	return n;
}

CRGB abs(CRGB rgb)
{
	return CRGB(::abs(rgb.iR), ::abs(rgb.iG), ::abs(rgb.iB));
}
