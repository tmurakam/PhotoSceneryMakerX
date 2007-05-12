/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * Bitmap.cpp : Another bitmap class
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

#ifndef bitmapH
#define bitmapH

//---------------------------------------------------------------------------
//
// Graphic::TBitmap class implementation of VCL is buggy :-(
// TBitmap2 class is compatible class (but subset) of TBitmap.

class TBitmap2 : public TGraphic
{
private:
	int width;
	int height;
	int height_per_bitmap;

	HBITMAP *hBitmaps;
	int	nBitmap;

public:
	__fastcall TBitmap2(void);
	__fastcall ~TBitmap2();
	
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall Draw(TCanvas *canvas, const TRect &rect);

	bool __fastcall GetEmpty(void);
	int __fastcall GetHeight(void);
	int __fastcall GetWidth(void);
	void __fastcall SetHeight(int Height);
	void __fastcall SetWidth(int Width);
	void __fastcall LoadFromStream(TStream *stream);
	void __fastcall SaveToStream(TStream *stream);
	void __fastcall LoadFromClipboardFormat(Word AFormat, unsigned AData,
		HPALETTE APalette);
	void __fastcall SaveToClipboardFormat(Word &AFormat, unsigned &AData,
		HPALETTE &APalette);
	void __fastcall SetPalette(HPALETTE Value) {};

};

//---------------------------------------------------------------------------
#endif
