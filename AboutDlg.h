/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * AboutDlg.h : About dialog
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

#ifndef AboutDlgH
#define AboutDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAboutDialog : public TForm
{
__published:	// IDE managed components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *LabelURL;
	TButton *Button1;
	TImage *Image1;
	TMemo *Memo1;
	void __fastcall LabelURLClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// user decl
public:		// user decl
	__fastcall TAboutDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutDialog *AboutDialog;
//---------------------------------------------------------------------------
#endif
