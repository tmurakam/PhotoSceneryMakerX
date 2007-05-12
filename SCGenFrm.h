/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * SCGenFrm.h : Scenery generation dialog
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

#ifndef SCGenFrmH
#define SCGenFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Project.h"
#include "SCGenThread.h"
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TSCGenForm : public TForm
{
__published:	// IDE managed components
	TButton *ButtonDoAll;
	TButton *ButtonClose;
	TGroupBox *GroupBox1;
	TButton *ButtonMakeInf;
	TButton *ButtonResample;
	TButton *ButtonConvertTexture;
	TButton *ButtonGenBGL;
	TButton *ButtonMergeAlpha;
	TButton *ButtonStop;
	TStatusBar *StatusBar;
	void __fastcall ButtonMakeInfClick(TObject *Sender);
	void __fastcall ButtonResampleClick(TObject *Sender);
	void __fastcall ButtonGenBGLClick(TObject *Sender);
	void __fastcall ButtonConvertTextureClick(TObject *Sender);
	void __fastcall ButtonDoAllClick(TObject *Sender);
	void __fastcall ButtonMergeAlphaClick(TObject *Sender);
	void __fastcall ButtonStopClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User decl.
	PSMProject *proj;

	SCGenThread *thr;

	void StartThread(int sw);
	void __fastcall OnThreadTerminate(TObject *Sender);
	void ProcessState(bool isStart);
	bool SanityCheck(void);

public:		// User decl.
	__fastcall TSCGenForm(TComponent* Owner);
	void SetParam(PSMProject *proj);
	void WriteIni(TIniFile * ini);
	void ReadIni(TIniFile * ini);
};
//---------------------------------------------------------------------------
extern PACKAGE TSCGenForm *SCGenForm;
//---------------------------------------------------------------------------
#endif

