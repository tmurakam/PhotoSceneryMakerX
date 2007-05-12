/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * SCGenThread.h : Scenery generation thread
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

#ifndef SCGenThreadH
#define SCGenThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#include "Project.h"

#define	EX_MAKEINF	0x1
#define	EX_RESAMPLE	0x2
#define	EX_MRGALPHA	0x4
#define	EX_CONVTEX	0x8
#define	EX_GENBGL	0x10

//---------------------------------------------------------------------------
class SCGenThread : public TThread
{            
private:
protected:
	void __fastcall Execute();

	PSMProject *Proj;
	int Sw;

	void MakeInf(void);
	AnsiString InfFileName(int season);
	AnsiString BmpPath(int season);
	void MakeInf(int season);

	int ExecCmd(AnsiString cmdline, AnsiString desc);

	void Resample(void);
	void MergeAlpha(void);
	void ConvTex(void);
	void GenBgl(void);

	void SetStatusMsg(AnsiString msg);

	void __fastcall ShowMsg(void);
	AnsiString ResultMsg;

public:
	__fastcall SCGenThread(PSMProject *proj, int sw);

};
//---------------------------------------------------------------------------
#endif
