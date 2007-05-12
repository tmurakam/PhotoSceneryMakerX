/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
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
// Season def.

enum {
	BM_SUMMER = 0,
	BM_SPRING,
	BM_FALL,
	BM_WINTER,
	BM_HSWINTER,
	BM_LIGHTMAP,
	BM_ALPHA,
	BM_MAX
};

#define	SEASON_SUFFIX	{"su", "sp", "fa", "wi", "hw", "lm", "al"}
#define	SEASON_NAME	{"summer", "spring", "fall", \
	"mild winter", "harsh winter", "lightmap", "summer"}

//---------------------------------------------------------------------------
// Photo Scenery Maker Project management class

class PSMProject
{
private:
	bool modified;

	// Source information
	AnsiString BmpFiles[BM_MAX];
	AnsiString BmpKey[BM_MAX];
	bool hasSeason;

	// Transform information
	Transform trans;

	// Output information
	AnsiString outdir;
	AnsiString basefile;

	// project info
	AnsiString	prjpath;
 
	Transform *readTransform(void)		{ return &trans; }

	void writeHasSeason(bool s)		{ hasSeason = s; modified = true; }
	void writeOutDir(const AnsiString &d)	{ outdir = d; modified = true; }
	void writeBaseFile(const AnsiString &b)	{ basefile = b; modified = true; }

	bool hasAlpha(void)		{ return !BmpFiles[BM_ALPHA].IsEmpty(); }

public:
	PSMProject();

	void LoadFromFile(AnsiString file);
	bool SaveToFile(AnsiString file = "");

	AnsiString BmpFile(int idx = BM_SUMMER)	{ return BmpFiles[idx]; }
	void SetBmpFile(int idx, const AnsiString &b)	{ BmpFiles[idx] = b; modified = true; }

	__property bool Modified = {read=modified, write=modified};
	__property Transform * Trans = {read=readTransform};

	__property bool HasSeason = {read=hasSeason, write=writeHasSeason};
	__property bool HasAlpha = {read=hasAlpha};
	__property AnsiString OutDir = {read=outdir, write=writeOutDir};
	__property AnsiString BaseFile = {read=basefile, write=writeBaseFile};
};

#endif
