/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * PJForm.h : Project property dialog
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

#ifndef PJFormH
#define PJFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "Project.h"
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
class TPrjForm : public TForm
{
__published:	// IDE managed components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TEdit *EditBmpSummer;
	TEdit *EditBmpSpring;
	TCheckBox *CheckSeason;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *EditBmpFall;
	TEdit *EditBmpWinter;
	TEdit *EditBmpHSWinter;
	TEdit *EditBmpLightmap;
	TEdit *EditBmpAlpha;
	TButton *ButtonRefBmpSummer;
	TButton *ButtonRefBmpSpring;
	TButton *ButtonRefBmpFall;
	TButton *ButtonRefBmpWinter;
	TButton *ButtonRefBmpHSWinter;
	TButton *ButtonRefBmpLightmap;
	TButton *ButtonRefBmpAlpha;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *EditOutDir;
	TEdit *EditBaseFile;
	TButton *ButtonRefOutDir;
	TOpenDialog *OpenDialog;
        TEdit *EditN;
        TEdit *EditS;
        TEdit *EditW;
        TEdit *EditE;
        TGroupBox *GroupBox1;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TGroupBox *GroupBox2;
        TLabel *Label14;
        TLabel *Label15;
        TEdit *EditXres;
        TEdit *EditYres;
	TEdit *EditWidth;
	TEdit *EditHeight;
	TLabel *Label16;
	TLabel *Label17;
	TEdit *EditXres2;
	TEdit *EditYres2;
	TLabel *Label18;
	TLabel *Label19;
	TGroupBox *GroupBoxInfo;
	TGroupBox *GroupFileOutput;
	TGroupBox *GroupBitmapBoundary;
	TCheckBox *CheckUseWhole;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TEdit *EditBoundTop;
	TEdit *EditBoundLeft;
	TEdit *EditBoundRight;
	TEdit *EditBoundBottom;
	void __fastcall ButtonRefOutDirClick(TObject *Sender);
	void __fastcall ButtonRefBmpSummerClick(TObject *Sender);
	void __fastcall ButtonRefBmpSpringClick(TObject *Sender);
	void __fastcall ButtonRefBmpFallClick(TObject *Sender);
	void __fastcall ButtonRefBmpWinterClick(TObject *Sender);
	void __fastcall ButtonRefBmpHSWinterClick(TObject *Sender);
	void __fastcall ButtonRefBmpLightmapClick(TObject *Sender);
	void __fastcall ButtonRefBmpAlphaClick(TObject *Sender);
	void __fastcall OnCoordEditExit(TObject *Sender);
	void __fastcall OnResEditExit(TObject *Sender);
	void __fastcall CheckSeasonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User decl.
public:		// User decl.
	__fastcall TPrjForm(TComponent* Owner);

	void LoadData(PSMProject *proj);
	void UpdateData(PSMProject *proj);

	void RefFolder(TEdit *edit);
	void RefBmpFile(TEdit *edit);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrjForm *PrjForm;
//---------------------------------------------------------------------------
#endif
