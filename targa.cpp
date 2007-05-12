/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * targa.c : Targa file handling
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
#include <stdio.h>

#include "Project.h"
#include "targa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static int WriteMergedTGA(Graphics::TBitmap *bmp, Graphics::TBitmap *alpha,
	AnsiString tgafile);

//---------------------------------------------------------------------------
//
void MergeAlphaTextures(AnsiString bmpfiles[], AnsiString alphafile,
	AnsiString tgafiles[], bool HasSeason)
{
	Graphics::TBitmap *bmp, *alpha;

	if (alphafile.IsEmpty()) {
		alpha = NULL;
	} else {
		alpha = new Graphics::TBitmap;
		alpha->LoadFromFile(alphafile);
	}

	bmp = new Graphics::TBitmap;

	for (int i = 0; i < BM_MAX; i++) {
		if (i == BM_ALPHA) continue;
		if (i != BM_SUMMER && !HasSeason) continue;

		bmp->LoadFromFile(bmpfiles[i]);
		WriteMergedTGA(bmp, alpha, tgafiles[i]);
	}

	delete bmp;
	delete alpha;
}


//---------------------------------------------------------------------------
static int WriteMergedTGA(Graphics::TBitmap *bmp, Graphics::TBitmap *alpha,
	AnsiString tgafile)
{
	static unsigned char buf[sizeof(TGAHEADER) + sizeof(TGATRAILER)
		+ 4 * 256 * 256];
	static TGAHEADER *head = NULL;
	static TGATRAILER *trail;
	static unsigned char *datap;

	// Initialize TGA Header & Trailer
	if (head == NULL) {
		head = (TGAHEADER *)buf;
		trail = (TGATRAILER *)(buf + sizeof(TGAHEADER) + 4 * 256 * 256);

		ZeroMemory(head, sizeof(*head));
		head->format = 2;	// full color
		head->width = 256;
		head->height = 256;
		head->depth = 32;	// 24bit + 8bit alpha

		ZeroMemory(trail, sizeof(*trail));
		strcpy(trail->str, "TRUEVISION-TARGA");

		datap = buf + sizeof(TGAHEADER);
	}

	if (bmp->Height != 256 || bmp->Height != 256) {
		return -1;
	}
	if (alpha && (alpha->Height != 256 || alpha->Width != 256)) {
		return -1;
	}

	unsigned char *p = datap;

	unsigned char transbits = 0x0;
	if (!alpha) transbits = 0xff;

	if (bmp->PixelFormat == pf24bit &&
		(!alpha || alpha->PixelFormat == pf24bit)) {
		// Fast copy...
		unsigned char *bline, *aline;

		for (int y = 0; y < 256; y++) {
			bline = (unsigned char *)bmp->ScanLine[255-y];
			aline = (unsigned char *)(alpha ? alpha->ScanLine[255-y] : NULL);

			if (alpha) {
				transbits |= *aline;

				for (int x = 0; x < 256; x++) {
					*p++ = *bline++;
					*p++ = *bline++;
					*p++ = *bline++;
					*p++ = *aline++;
					aline+=2;
				}
			} else {
				for (int x = 0; x < 256; x++) {
					*p++ = *bline++;
					*p++ = *bline++;
					*p++ = *bline++;
					*p++ = 0;		// no alpha
				}
			}
		}
	} else {
		// Slow copy...
		for (int y = 0; y < 256; y++) {
			for (int x = 0; x < 256; x++) {
				TColor c = bmp->Canvas->Pixels[x][255 - y];
				*p++ = c & 0xff;		// R
				*p++ = (c >> 8) & 0xff;		// G
				*p++ = (c >> 16) & 0xff;	// B

				if (!alpha) {
					*p++ = 0;
				} else {
					c = alpha->Canvas->Pixels[x][255 - y];
					c &= 0xff;
					transbits |= c;
					*p++ = c;		// alpha (R)
				}
			}
		}
	}

	// dirty hack...
	// Imagetool.exe can't handle completely transparent bitmap.
	if (transbits == 0x0) {
		*(p - 1) = 0x1;
	}

	// write targa file
	FILE *fp = fopen(tgafile.c_str(), "wb");
	fwrite(buf, 1, sizeof(buf), fp);
	fclose(fp);

	return 0;
}

