/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * OptDlg.h : Option dialog
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

#ifndef OptDlgH
#define OptDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#define	REG_KEY		"\\Software\\Takuya Murakami\\Photo Scenery Maker X"

//---------------------------------------------------------------------------
class TOptionDlg : public TForm
{
__published:	// IDE managed components
	TButton *ButtonOK;
	TButton *Button2;
	TLabel *Label1;
	TEdit *EditSDKPath;
	TButton *ButtonBrowseSDK;
	TComboBox *ListLang;
	TLabel *Label3;
	TOpenDialog *OpenDialog;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonOKClick(TObject *Sender);
	void __fastcall ButtonBrowseSDKClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User decl
	void LoadReg(void);
	void ChangeLang(void);
	int curLangIdx;

public:		// User decl
	__fastcall TOptionDlg(TComponent* Owner);
	AnsiString GetSDKPath(void);
	AnsiString GetLangCode(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionDlg *OptionDlg;
//---------------------------------------------------------------------------
#endif
