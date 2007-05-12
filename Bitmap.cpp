/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * Bitmap.cpp : Another TBitmap class
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

#include "gnugettext.hpp"

#include <stdio.h>
#include "Bitmap.h"
//--------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TBitmap2::TBitmap2(void)
{
	height = width = 0;
	nBitmap = 0;
	hBitmaps = NULL;
	
	height_per_bitmap = 1000;	// default
}

__fastcall TBitmap2::~TBitmap2()
{
	if (nBitmap > 0) {
		for (int i = 0; i < nBitmap; i++) {
			if (hBitmaps[i]) DeleteObject(hBitmaps[i]);
		}
		delete hBitmaps;
	}
}

bool __fastcall TBitmap2::GetEmpty(void)
{
	return (nBitmap == 0) ? true : false;
}

int __fastcall TBitmap2::GetHeight(void)
{
	return height;
}

int __fastcall TBitmap2::GetWidth(void)
{
	return width;
}

//
// Load bitmap from file
//
void __fastcall TBitmap2::LoadFromFile(const AnsiString FileName)
{
	// Open bitmap file
	TFileStream *stream = new TFileStream(FileName,
		fmOpenRead | fmShareDenyWrite);

	try {
		LoadFromStream(stream);
	}
	__finally {
		delete stream;
	}
}

//
// Load from stream
//
void __fastcall TBitmap2::LoadFromStream(TStream *stream)
{
	BITMAPFILEHEADER 	bf;
	BITMAPINFOHEADER	bi;
	int i;

	if (nBitmap > 0) {
		for (i = 0; i < nBitmap; i++) {
			DeleteObject(hBitmaps[i]);
		}
		delete hBitmaps;
		nBitmap = 0;
	}

	stream->Seek(0, soFromBeginning);
	stream->ReadBuffer(&bf, sizeof(bf));
	stream->ReadBuffer(&bi, sizeof(bi));

	if (bf.bfType != 'B' + 'M' * 0x100
		|| bi.biSize != 40
		|| bi.biCompression != BI_RGB
		|| bi.biBitCount < 16) {

		AnsiString msg = _("Bitmap must be 16/24/32bit uncompressed windows BMP file.");
		throw Exception(msg);
	}
	width = bi.biWidth;
	height = bi.biHeight;

	stream->Seek(bf.bfOffBits,soFromBeginning);

	nBitmap = (height - 1) / height_per_bitmap + 1;
	hBitmaps = new HBITMAP [nBitmap];

	HDC dc = GetDC(NULL);

	int BytesPerLine =((bi.biWidth * bi.biBitCount + 31) / 32) * 4;
	int y, hh;

	for (y = 0, i = 0; y < height; y += height_per_bitmap, i++) {
		hh = height - y;
		if (hh > height_per_bitmap) hh = height_per_bitmap;

		bi.biHeight = hh;

		VOID *bits;
		hBitmaps[i] = CreateDIBSection(dc, (BITMAPINFO *)&bi,
					       DIB_RGB_COLORS, &bits, 0, 0);

		if (!hBitmaps[i]) {
			AnsiString msg = _(
			"Could not allocate memory for bitmap. Maybe bitmap file size is too large.");
			throw Exception(msg);
		}

		DWORD size = BytesPerLine * bi.biHeight;

		stream->ReadBuffer(bits, size);
	}

	ReleaseDC(NULL, dc);
}

//
// Draw function to TCanvas
//
void __fastcall TBitmap2::Draw(TCanvas *canvas, const TRect &rect)
{
	HDC hDC = CreateCompatibleDC(canvas->Handle);

	int i, y, hh, canvas_y;
	for (i = 0; i < nBitmap; i++) {
		y = i * height_per_bitmap;
		hh = height - y;
		if (hh > height_per_bitmap) hh = height_per_bitmap;

		canvas_y = height - y - hh;

		SelectObject(hDC, hBitmaps[i]);
		int ret = BitBlt(canvas->Handle,
				 rect.Left, rect.Top + canvas_y,
				 rect.Width(), hh,
				 hDC,
				 0, 0,
				 canvas->CopyMode);
	}

	DeleteDC(hDC);
}


//
// Not implemented...
//
#define	NOIMPL	{ throw Exception("TBitmap2 : Not implemented"); }

void __fastcall TBitmap2::SetHeight(int Height) NOIMPL
void __fastcall TBitmap2::SetWidth(int Width) NOIMPL
void __fastcall TBitmap2::SaveToStream(TStream *stream) NOIMPL
void __fastcall TBitmap2::LoadFromClipboardFormat(Word AFormat, unsigned AData,
		HPALETTE APalette) NOIMPL
void __fastcall TBitmap2::SaveToClipboardFormat(Word &AFormat, unsigned &AData,
		HPALETTE &APalette) NOIMPL

