#include "stdafx.h"

#include "vpc.h"
#include "vpcdoc.h"
#include "vpcview.h"

#include <math.h>

#include "vpcdlg.h"

////////////////////////////////////////////////////////////////////////////
// Convert Functions

void CVpcView::OnConUndo()
{
	iCurBmp = 1 - iCurBmp; // Bitmapが２個のときだけ
	Invalidate(FALSE);	
}

#pragma warning (disable : 4051) // int value = ... の文の為

void CVpcView::OnConMono()
{
	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			int value = CRGB(pOldDC->GetPixel(j, i)).Density();
            pNewDC->SetPixel(j, i, RGB(value, value, value));
		}
	}
	EndConvert();
}

void CVpcView::OnConAdlight()
{
	CValueDlg dlg;
	dlg.csMess = "明度を％で入力。";
	dlg.m_value = AfxGetApp()->GetProfileInt("value", "Adlight", 100);
	if (dlg.DoModal() != IDOK)
		return;
	AfxGetApp()->WriteProfileInt("value", "Adlight", dlg.m_value);

	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			pNewDC->SetPixel(j, i, CRGB(pOldDC->GetPixel(j, i)) * ((double)dlg.m_value / 100));
		}
	}
	EndConvert();
}

void CVpcView::Filter(int* ratio, int divide)
{
	static CPoint point[9] = {CPoint(-1, -1), CPoint( 0, -1), CPoint(1, -1), CPoint(-1,  0), CPoint(0, 0),
							  CPoint( 1,  0), CPoint(-1,  1), CPoint(0,  1), CPoint( 1,  1)};
	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			CRGB rgb = 0;
			for (int k = 0; k < 9; k++)
				if (ratio[k])
                	rgb += CRGB(pOldDC->GetPixel(j + point[k].x, i + point[k].y)) * ratio[k];
			pNewDC->SetPixel(j, i, rgb / divide);
		}
	}			
	EndConvert();
}

void CVpcView::Filter2(int* ratio)
{
	static CPoint point[9] = {CPoint(-1, -1), CPoint( 0, -1), CPoint(1, -1), CPoint(-1,  0), CPoint(0, 0),
							  CPoint( 1,  0), CPoint(-1,  1), CPoint(0,  1), CPoint( 1,  1)};
	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			CLRGB buf = 0;
			for (int k = 0; k < 9; k++)
				if (ratio[k])
                	buf += CLRGB(pOldDC->GetPixel(j + point[k].x, i + point[k].y)) * ratio[k];
			CLRGB rgb = 0;
			for (k = 0; k < 9; k++)
				if (ratio[k + 9])
                	rgb += CLRGB(pOldDC->GetPixel(j + point[k].x, i + point[k].y)) * ratio[k + 9];
			pNewDC->SetPixel(j, i, average(rgb, buf));
		}
	}			
	EndConvert();
}

void CVpcView::OnConCnoise()
{
	BeginConvert();
	CRGB rgb[9], buf;
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			for (int k = 0; k < 9; k++)
				rgb[k] = pOldDC->GetPixel(j - 1 + k % 3, i - 1 + k / 3);
			for (k = 0; k < 5; k++)
				for (int l = 0; l < 8 - k; l++)
					if (rgb[l].Density() < rgb[l + 1].Density())
						buf = rgb[l], rgb[l] = rgb[l + 1], rgb[l + 1] = buf;
			pNewDC->SetPixel(j, i, rgb[4]);
		}
	}	
	EndConvert();
}

void CVpcView::OnConEdges()
{
	BeginConvert();
	CRGB rgb, buf;
	for (int i = reObj.top; i < reObj.bottom; i++) {
		buf = pOldDC->GetPixel(reObj.left, i);
		for (int j = reObj.left + 1; j < reObj.right; j++) {
			rgb = pOldDC->GetPixel(j, i);
			pNewDC->SetPixel(j - 1, i, abs(rgb - buf));
			buf = rgb;
		}
		pNewDC->SetPixel(--j, i, 0);
	}
	EndConvert();
}

void CVpcView::OnConEdges2()
{
	int ratio[9] = { 0,  1,  0,
					 1, -4,  1,
					 0,  1,  0 };
	Filter(ratio);
}

void CVpcView::OnConNegap()
{
	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			pNewDC->SetPixel(j, i, -CRGB(pOldDC->GetPixel(j, i)));
		}
	}
	EndConvert();
}

void CVpcView::OnConBinary()
{
	CValueDlg dlg;
	dlg.csMess = "境界明度を入力。";
	dlg.m_value = AfxGetApp()->GetProfileInt("value", "Binary", 32);
	if (dlg.DoModal() != IDOK)
		return;
	AfxGetApp()->WriteProfileInt("value", "Binary", dlg.m_value);

	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			pNewDC->SetPixel(j, i, (CRGB(pOldDC->GetPixel(j, i)).Density() > dlg.m_value) * RGB(255, 255, 255));
		}
	}
	EndConvert();
}

void CVpcView::OnConBesmart()
{
	BeginConvert();
	int mid = (reObj.right - reObj.left) / 2;
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.left + mid; j++) {
			if (pOldDC->GetPixel(j - 1, i))
				pNewDC->SetPixel(j, i, 0);
		}
		for (j = reObj.right; j >= reObj.right - mid; j--) {
			if (pOldDC->GetPixel(j + 1, i))
				pNewDC->SetPixel(j, i, 0);
		}
	}
	EndConvert();	
}

void CVpcView::OnConMosaic()
{
	CValueDlg dlg;
	dlg.csMess = "１ブロックのピクセル数を入力。";
	dlg.m_value = AfxGetApp()->GetProfileInt("value", "Mosaic", 4);
	if (dlg.DoModal() != IDOK)
		return;
	AfxGetApp()->WriteProfileInt("value", "Mosaic", dlg.m_value);
	int value = dlg.m_value;

	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i += value) {
		for (int j = reObj.left; j < reObj.right; j += value) {
			CLRGB rgb = 0;
			int x, y, ps = 0;
			for (int k = 0; k < value * value; k++) {
				if ( (x = j + k % value) >= reObj.right || (y = i + k / value) >= reObj.bottom)
					continue;
				rgb += pOldDC->GetPixel(x, y);
				ps++;
			}
			COLORREF cr	= rgb / ps;
			for (k = 0; k < value * value; k++) {
				if ( (x = j + k % value) >= reObj.right || (y = i + k / value) >= reObj.bottom)
					continue;
				pNewDC->SetPixel(x, y, cr);
			}
		}
	}
    EndConvert();
}

void CVpcView::OnConSoft()
{
	int ratio[9] = { 1, 1, 1,
					 1, 2, 1,
					 1, 1, 1 };
	Filter(ratio, 10);
}

void CVpcView::OnConPrewitt()
{
	int ratio[18] = { -1,  0,  1,
					  -1,  0,  1,
					  -1,  0,  1,
					  
					  -1, -1, -1,
					   0,  0,  0,
					   1,  1,  1, }; 
	Filter2(ratio);
}

void CVpcView::OnConSobel()
{
	int ratio[18] = { -1,  0,  1,
					  -2,  0,  2,
					  -1,  0,  1,
					  
					  -1, -2, -1,
					   0,  0,  0,
					   1,  2,  1, }; 
	Filter2(ratio);
}

void CVpcView::OnConRotate()
{
	BeginDraw(4);
}

void CVpcView::Linear(double a, double b, double c, double d)
{
	// (1, 0) -> (a, c)  (0, 1) -> (b, d)
	double det = a * d - b * c;
	if (det) {
		double ad = d / det;
		double bd = -b / det;
		double cd = -c / det;
		double dd = a / det;
		int xmid = (reObj.right + reObj.left) / 2;
		int ymid = (reObj.bottom + reObj.top) / 2;
		BeginConvert();
		for (int i = reObj.top; i < reObj.bottom; i++) {
			for (int j = reObj.left; j < reObj.right; j++) {
            	int xd = j - xmid;
				int yd = i - ymid;
				int x = (int)(ad * xd + bd * yd) + xmid;
				int y = (int)(cd * xd + dd * yd) + ymid;
				pNewDC->SetPixel(j, i, pOldDC->GetPixel(x, y));
			}
		}
		EndConvert();
	}
}

void CVpcView::OnConZoom()
{
	CValueDlg dlg;
	dlg.csMess = "倍率を％で入力。";
	dlg.m_value = AfxGetApp()->GetProfileInt("value", "Zoom", 100);
	if (dlg.DoModal() != IDOK)
		return;
	AfxGetApp()->WriteProfileInt("value", "Zoom", dlg.m_value);

	double a, b, c, d;
	a = d = (double)dlg.m_value / 100, b = c = 0;
	Linear(a, b, c, d);		
}

void CVpcView::OnConAdcenter()
{
	BeginDraw(5);
}

void CVpcView::AdjustCenter(CPoint point)
{
	BeginConvert();
	int xad = point.x - (reObj.right + reObj.left) / 2;
	int yad = point.y - (reObj.bottom + reObj.top) / 2;
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			pNewDC->SetPixel(j, i, pOldDC->GetPixel(j + xad, i + yad));
		}
	}
	EndConvert();
}

void CVpcView::OnConSscale()
{
	BeginDraw(6);
}

void CVpcView::OnConAdheight()
{
	BeginDraw(7);	
}

void CVpcView::OnConCdcolor()
{
	BeginConvert();
	for (int i = reObj.top; i < reObj.bottom; i++) {
		for (int j = reObj.left; j < reObj.right; j++) {
			pNewDC->SetPixel(j, i, CRGB(pOldDC->GetPixel(j, i)) - crCurCol);
		}
	}
	EndConvert();
}
