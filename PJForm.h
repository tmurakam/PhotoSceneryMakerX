/*
 * Photo Scenery Maker X
 *
 * Copyright (C) 2003-2007 Takuya Murakami
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
	TEdit *EditBmpFile;
	TLabel *Label1;
	TButton *ButtonRefBmpSummer;
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
	TGroupBox *GroupBox3;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *EditLOD;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *ComboBoxBmpNum;
	TGroupBox *GroupBox4;
	TRadioButton *RadioButtonAll;
	TRadioButton *RadioButtonDay;
	TRadioButton *RadioButtonNight;
	TRadioButton *RadioButtonLWMask;
	TLabel *Label6;
	TCheckBox *CheckBoxAllMonth;
	TCheckBox *CheckBoxM1;
	TCheckBox *CheckBoxM2;
	TCheckBox *CheckBoxM3;
	TCheckBox *CheckBoxM4;
	TCheckBox *CheckBoxM5;
	TCheckBox *CheckBoxM6;
	TCheckBox *CheckBoxM7;
	TCheckBox *CheckBoxM8;
	TCheckBox *CheckBoxM9;
	TCheckBox *CheckBoxM10;
	TCheckBox *CheckBoxM11;
	TCheckBox *CheckBoxM12;
	void __fastcall ButtonRefOutDirClick(TObject *Sender);
	void __fastcall ButtonRefBmpFileClick(TObject *Sender);
	void __fastcall OnCoordEditExit(TObject *Sender);
	void __fastcall OnResEditExit(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBoxBmpNumChange(TObject *Sender);
	void __fastcall updateBmpInfo(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:	// User decl.
	BitmapInfo bmpInfo[BM_MAX];
        bool blockUpdate;

public:		// User decl.
	__fastcall TPrjForm(TComponent* Owner);

	void LoadData(PSMProject *proj);
	void UpdateData(PSMProject *proj);

	void RefFolder(TEdit *edit);
	void RefBmpFile(TEdit *edit);
        int curBmpIdx(void) {
        	if (ComboBoxBmpNum->ItemIndex < 0) {
                	ComboBoxBmpNum->ItemIndex = 0;
		}
        	try {
                	return ComboBoxBmpNum->Text.ToInt() - 1;
                }
                catch(...) {
                        return 0;
                }
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TPrjForm *PrjForm;
//---------------------------------------------------------------------------
#endif
