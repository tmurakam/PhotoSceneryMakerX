/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * Transform.cpp : Transform coordinates.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>

#include "Transform.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

// Calculate transform parameters
//
bool Transform::CalcParameters(ControlPoint *cp)
{
	int dx, dy;
	double rx, ry;

	// Calculate degree per one pixel
	dx = cp[1].v.x - cp[0].v.x;
	dy = cp[1].v.y - cp[0].v.y;

	rx =  (cp[1].p.lon.deg - cp[0].p.lon.deg) / dx;
	ry = -(cp[1].p.lat.deg - cp[0].p.lat.deg) / dy;
	if (rx <= 0 || ry <= 0) {
		return false;
	}

	res.x = rx;
	res.y = ry;

	// Calculate north/west coordinates
	base.lon.deg = cp[0].p.lon.deg - cp[0].v.x * res.x;
	base.lat.deg = cp[0].p.lat.deg - (-cp[0].v.y) * res.y;

	CalcResolution();

	return true;
}

//------------------------------------------------------------------
void Transform::CalcResolution(void)
{
	// Optimal resolution
	//	Texture size is LOD13. Covered area with one texture 
	//	is 90/8192 degree(N-S), 120/8192 degree(E-W).
	//	Texture size is 256x256 pixel.
	optres.y = (90.0 / 8192.0 / 256.0);
	optres.x = 120.0 / 8192.0 / 256.0;

	// Calculate magnify rate
	mag.x = res.x / optres.x;
	mag.y = res.y / optres.y;
}

//------------------------------------------------------------------
// Convert pixel coordinates to latitude/longigute
//
LatLon Transform::CalcLatLon(int x, int y)
{
	LatLon ll;

	ll.lon.deg = base.lon.deg + res.x * x;
	ll.lat.deg = base.lat.deg + res.y * (-y);

	return ll;
}

// Reverse conversion
int Transform::CalcX(double lon)
{
	if (res.x == 0) return 0;
	return (lon - base.lon.deg) / res.x;
}

int Transform::CalcY(double lat)
{
	if (res.y == 0) return 0;
	return - (lat - base.lat.deg) / res.y;
}

//------------------------------------------------------------------
// Calculate optimal bitmap size
void Transform::CalcOptSize(int width, int height, int *correct_w, int *correct_h)
{
	*correct_w = width * mag.x;
	*correct_h = height * mag.y;
}

//--------------------------------------------------------------------------
// Optimize bitmaps
#if 0
inline void CMultiAdd(int &r, int &g, int &b, const TColor &cref, double m)
{
	int rc, gc, bc;

	rc = (cref >> 16) & 0xff;
	gc = (cref >> 8) & 0xff;
	bc = cref & 0xff;

	r += rc * m;
	g += gc * m;
	b += bc * m;
}	

TPicture *Transform::TransImage(TPicture *pict)
{
	int x, y, xx, yy;


	int owidth  = pict->Bitmap->Width;
	int oheight = pict->Bitmap->Height;
	TCanvas *oc = pict->Bitmap->Canvas;

	// Create reference data
	unsigned long *cref;
	cref = new unsigned long [owidth * oheight];

	for (y = 0; y < oheight; y++) {
		for (x = 0; x < owidth; x++) {
			cref[y * owidth + x] = oc->Pixels[x][y];
		}
	}

	// Calculate new bitmap size
	int cwidth, cheight;
	CalcOptSize(owidth, oheight, &cwidth, &cheight);

	// Create new bitmap
	Graphics::TBitmap *newbmp = new Graphics::TBitmap;
	newbmp->Width = cwidth;
	newbmp->Height = cheight;
	TCanvas *c = newbmp->Canvas;

	double ox, oy, wx, wy;
	unsigned long color, c00, c01, c10, c11;
	int r, g, b;
	for (y = 0; y < cheight; y++) {

		MainForm->SetProgress((double)y / cheight * 100.0);
		Application->ProcessMessages();

		for (x = 0; x < cwidth; x++) {
			// Reverse conversion
			ox = x / Xmag;
			oy = y / Ymag;

			// Calculate pixel with linear interpolation.
			xx = (int)ox;
			yy = (int)oy;

			wx = ox - xx;
			wy = oy - yy;

			c00 = cref[yy * owidth + xx];
			c01 = cref[(yy+1) * owidth + xx];
			c10 = cref[yy * owidth + (xx+1)];
			c11 = cref[(yy+1) * owidth + (xx+1)];

			r = g = b = 0;
			CMultiAdd(r, g, b, c00, (1.0 - wx) * (1.0 - wy));
			CMultiAdd(r, g, b, c01, (1.0 - wx) * wy);
			CMultiAdd(r, g, b, c10, wx * (1.0 - wy));
			CMultiAdd(r, g, b, c11, wx * wy);
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;

			color = (r << 16) | (g << 8) | b;
			c->Pixels[x][y] = color;
		}
	}

	TPicture *newpict = new TPicture;
	newpict->Bitmap = newbmp;

	delete cref;

	// Modify resolution
	Xres = OptXres;
	Yres = OptYres;
	
	return newpict;
}
#endif

