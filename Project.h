/*
 * Photo Scenery Maker X
 *
 * Copyright (C) 2003-2007 Takuya Murakami
 *
 * Project.h : Project document class
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

#ifndef ProjectH
#define ProjectH

#include "Transform.h"

//---------------------------------------------------------------------------
// BMP def.


// variations
#define	BV_ALL		0x1 		// day and night
#define	BV_DAY		0x2		// day (all month)
#define	BV_NIGHT	0x4		// night
#define	BV_LWMASK	0x8		// land/water mask
#define	BV_MONTH(n)	(0x10 << (n))	// month (1-12, 0=all month)

#define	BM_MAX		14

class BitmapInfo
{
public:
        AnsiString	filename;
        int		variation;

public:
	bool isValid(void) {
        	if (filename.IsEmpty()) {
                        return false;
                }
                return true;
        }
};

//---------------------------------------------------------------------------
// Photo Scenery Maker Project management class

class PSMProject
{
private:
	bool modified;

	// Source information
        BitmapInfo bmpInfo[BM_MAX];

	// Transform information
	Transform trans;

	// Output information
	AnsiString outdir;
	AnsiString basefile;
        int lod;

	// project info
	AnsiString	prjpath;
 
	Transform *readTransform(void)		{ return &trans; }

	void writeOutDir(const AnsiString &d)	{ outdir = d; modified = true; }
	void writeBaseFile(const AnsiString &b)	{ basefile = b; modified = true; }
        void writeLod(int x) { lod = x; modified = true; }

	//        bool hasNight(void)		{ return !BmpFiles[BM_NIGHT].IsEmpty(); }
	//	bool hasAlpha(void)		{ return !BmpFiles[BM_ALPHA].IsEmpty(); }

public:
	PSMProject();

	void LoadFromFile(AnsiString file);
	bool SaveToFile(AnsiString file = "");

	BitmapInfo *BmpInfo(int n) { return &bmpInfo[n]; }
        void setBmpInfo(BitmapInfo *m, int n) { bmpInfo[n] = *m; modified = true; }

	void Packing(void);
        
        AnsiString MainBmpFile(void) { return bmpInfo[0].filename; }
        
	int numBmp(void);
        int lwmaskIdx(void);
        
	__property bool Modified = {read=modified, write=modified};
	__property Transform * Trans = {read=readTransform};

//	__property bool HasNight = {read=hasNight};
//	__property bool HasAlpha = {read=hasAlpha};
	__property AnsiString OutDir = {read=outdir, write=writeOutDir};
	__property AnsiString BaseFile = {read=basefile, write=writeBaseFile};
        __property int Lod = { read=lod, write=writeLod};
};

#endif
