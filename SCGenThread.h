/*
 * Photo Scenery Maker X
 *
 * Copyright (C) 2003-2007 Takuya Murakami
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
#include <stdio.h>

#include "Project.h"


#define	EX_MAKEINF	0x1
#define	EX_GENBGL	0x2

//---------------------------------------------------------------------------
class SCGenThread : public TThread
{            
private:
protected:
	void __fastcall Execute();

	PSMProject *Proj;
	int Sw;

	void MakeInf(void);
	AnsiString InfFileName(void);
        void MakeInfSub(FILE *fp, int n, const char *layer, AnsiString bmpfile, Transform *trans);
	AnsiString variationString(int v);

	int ExecCmd(AnsiString cmdline, AnsiString desc);

	void Resample(void);

	void SetStatusMsg(AnsiString msg);

	void __fastcall ShowMsg(void);
	AnsiString ResultMsg;

public:
	__fastcall SCGenThread(PSMProject *proj, int sw);

};
//---------------------------------------------------------------------------
#endif
