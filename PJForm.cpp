/*
 * Photo Scenery Maker X
 *
 * Copyright (C) 2003-2007 Takuya Murakami
 *
 * PJForm.cpp : Project property dialog
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
#include <math.h>

#include "gnugettext.hpp"

#include "PJForm.h"
#include "Util.h"
#include "latlon.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrjForm *PrjForm;
//---------------------------------------------------------------------------
__fastcall TPrjForm::TPrjForm(TComponent* Owner)
	: TForm(Owner)
{
	blockUpdate = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrjForm::FormCreate(TObject *Sender)
{
	Font->Handle = GetStockObject(DEFAULT_GUI_FONT);
}
//---------------------------------------------------------------------------
void __fastcall TPrjForm::FormShow(TObject *Sender)
{
        ComboBoxBmpNum->ItemIndex = 0;
	ComboBoxBmpNumChange(Sender);
}

//---------------------------------------------------------------------------
void TPrjForm::LoadData(PSMProject *proj)
{
	for (int i = 0; i < BM_MAX; i++) {
        	BitmapInfo *m = proj->BmpInfo(i);
                bmpInfo[i] = *m;
        }

	EditWidth->Text = proj->Trans->Width;
	EditHeight->Text = proj->Trans->Height;

	EditN->Text = proj->Trans->Base.lat.GetStr();
	EditW->Text = proj->Trans->Base.lon.GetStr();

	EditXres->Text = proj->Trans->Resolution.x * 3600;
	EditYres->Text = proj->Trans->Resolution.y * 3600;

	OnResEditExit(NULL);	// ad hoc...

	EditOutDir->Text = proj->OutDir;
	EditBaseFile->Text = proj->BaseFile;

	CheckUseWhole->Checked = proj->Trans->Boundary.useWhole;
	EditBoundTop->Text = proj->Trans->Boundary.top;
	EditBoundLeft->Text = proj->Trans->Boundary.left;
	EditBoundRight->Text = proj->Trans->Boundary.right;
	EditBoundBottom->Text = proj->Trans->Boundary.bottom;

        EditLOD->Text = proj->Lod;
}

void TPrjForm::UpdateData(PSMProject *proj)
{
	for (int i=0; i < BM_MAX; i++) {
        	BitmapInfo *m = proj->BmpInfo(i);
                *m = bmpInfo[i];
        }

	proj->Trans->Base.lat.SetStr(EditN->Text);
	proj->Trans->Base.lon.SetStr(EditW->Text);

	XYparam res;
	res.x = EditXres->Text.ToDouble() / 3600;
	res.y = EditYres->Text.ToDouble() / 3600;
	proj->Trans->Resolution = res;

	proj->OutDir = EditOutDir->Text;
	proj->BaseFile = EditBaseFile->Text;
	
	proj->Trans->Boundary.useWhole = CheckUseWhole->Checked;
	proj->Trans->Boundary.top = EditBoundTop->Text.ToInt();
	proj->Trans->Boundary.left = EditBoundLeft->Text.ToInt();
	proj->Trans->Boundary.right = EditBoundRight->Text.ToInt();
	proj->Trans->Boundary.bottom = EditBoundBottom->Text.ToInt();

        proj->Lod = EditLOD->Text.ToInt();

        proj->Packing();
}

//---------------------------------------------------------------------------
// Select folder
void TPrjForm::RefFolder(TEdit *edit)
{
	AnsiString f = SelectFolder(edit->Text, Handle);
	if (f.IsEmpty()) return;

	edit->Text = f;
}

void __fastcall TPrjForm::ButtonRefOutDirClick(TObject *Sender)
{
	RefFolder(EditOutDir);
}


//---------------------------------------------------------------------------
void __fastcall TPrjForm::OnCoordEditExit(TObject *Sender)
{
	TEdit *edit = (TEdit *)Sender;

        if (!edit->Modified) return;

	int width = EditWidth->Text.ToInt();
	int height = EditHeight->Text.ToInt();

	if (width <= 0 || height <= 0) return;
			
	// Update resolution
	LatLon nw, se;
	nw.lat.SetStr(EditN->Text);
	nw.lon.SetStr(EditW->Text);
	se.lat.SetStr(EditS->Text);
	se.lon.SetStr(EditE->Text);

	double xres = (se.lon.deg - nw.lon.deg) / width;
	double yres = (nw.lat.deg - se.lat.deg) / height;

        EditXres->Text = xres;
	EditYres->Text = yres;

	xres = 10000 * 1000 * xres / 90.0 * cos(nw.lat.deg / 180.0 * M_PI);
	yres = 10000 * 1000 * yres / 90.0;
	EditXres2->Text = xres;
	EditYres2->Text = yres;
}
//---------------------------------------------------------------------------
void __fastcall TPrjForm::OnResEditExit(TObject *Sender)
{
	TEdit *edit = (TEdit *)Sender;

	if (edit && !edit->Modified) return;

	int width = EditWidth->Text.ToInt();
	int height = EditHeight->Text.ToInt();

	// Update boundary
	double xres = EditXres->Text.ToDouble() / 3600;
	double yres = EditYres->Text.ToDouble() / 3600;
	LatLon nw, se;
	nw.lat.SetStr(EditN->Text);
	nw.lon.SetStr(EditW->Text);

	se.lat.deg = nw.lat.deg - height * yres;
	se.lon.deg = nw.lon.deg + width * xres;

	EditS->Text = se.lat.GetStr();
	EditE->Text = se.lon.GetStr();

	double xres2 = 10000 * 1000 * xres / 90.0 * cos(nw.lat.deg / 180.0 * M_PI);
	double yres2 = 10000 * 1000 * yres / 90.0;
	EditXres2->Text = xres2;
	EditYres2->Text = yres2;
}

//---------------------------------------------------------------------------
// Select BMP file
//---------------------------------------------------------------------------
void __fastcall TPrjForm::ButtonRefBmpFileClick(TObject *Sender)
{
	if (OpenDialog->Execute()) {
		EditBmpFile->Text = OpenDialog->FileName;

                int bmpIdx = curBmpIdx();
                bmpInfo[bmpIdx].filename = EditBmpFile->Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrjForm::ComboBoxBmpNumChange(TObject *Sender)
{
	blockUpdate = true;

	int bmpIdx = curBmpIdx();
	EditBmpFile->Text = bmpInfo[bmpIdx].filename;

        int v = bmpInfo[bmpIdx].variation;

        // uncheck month
        CheckBoxAllMonth->Checked = false;
        CheckBoxM1->Checked = false;
        CheckBoxM2->Checked = false;
        CheckBoxM3->Checked = false;
        CheckBoxM4->Checked = false;
        CheckBoxM5->Checked = false;
        CheckBoxM6->Checked = false;
        CheckBoxM7->Checked = false;
        CheckBoxM8->Checked = false;
        CheckBoxM9->Checked = false;
        CheckBoxM10->Checked = false;
        CheckBoxM11->Checked = false;
        CheckBoxM12->Checked = false;

        if (v & BV_ALL) {
        	RadioButtonAll->Checked = true;
        }
        else if (v & BV_NIGHT) {
        	RadioButtonNight->Checked = true;
        }
        else if (v & BV_LWMASK) {
        	RadioButtonLWMask->Checked = true;
	}
        else {
        	RadioButtonDay->Checked = true;
	}

        // month
	if (v & BV_MONTH(0)) CheckBoxAllMonth->Checked = true;
        if (v & BV_MONTH(1)) CheckBoxM1->Checked = true;
        if (v & BV_MONTH(2)) CheckBoxM2->Checked = true;
        if (v & BV_MONTH(3)) CheckBoxM3->Checked = true;
        if (v & BV_MONTH(4)) CheckBoxM4->Checked = true;
        if (v & BV_MONTH(5)) CheckBoxM5->Checked = true;
        if (v & BV_MONTH(6)) CheckBoxM6->Checked = true;
        if (v & BV_MONTH(7)) CheckBoxM7->Checked = true;
        if (v & BV_MONTH(8)) CheckBoxM8->Checked = true;
        if (v & BV_MONTH(9)) CheckBoxM9->Checked = true;
        if (v & BV_MONTH(10)) CheckBoxM10->Checked = true;
        if (v & BV_MONTH(11)) CheckBoxM11->Checked = true;
        if (v & BV_MONTH(12)) CheckBoxM12->Checked = true;

        blockUpdate = false;
}
//---------------------------------------------------------------------------

void __fastcall TPrjForm::updateBmpInfo(TObject *Sender)
{
	if (blockUpdate) return;

	int bmpIdx = curBmpIdx();
	bmpInfo[bmpIdx].filename = EditBmpFile->Text;

        // radio
	int v;
	if (RadioButtonAll->Checked) {
        	v = BV_ALL;
        }
	else if (RadioButtonNight->Checked) {
        	v = BV_NIGHT;
        }
	else if (RadioButtonLWMask->Checked) {
        	v = BV_LWMASK;
        }
        else {
        	v = BV_DAY;
        }

	if (CheckBoxAllMonth->Checked) v |= BV_MONTH(0);
       	if (CheckBoxM1->Checked) v |= BV_MONTH(1);
       	if (CheckBoxM2->Checked) v |= BV_MONTH(2);
       	if (CheckBoxM3->Checked) v |= BV_MONTH(3);
       	if (CheckBoxM4->Checked) v |= BV_MONTH(4);
       	if (CheckBoxM5->Checked) v |= BV_MONTH(5);
       	if (CheckBoxM6->Checked) v |= BV_MONTH(6);
       	if (CheckBoxM7->Checked) v |= BV_MONTH(7);
       	if (CheckBoxM8->Checked) v |= BV_MONTH(8);
       	if (CheckBoxM9->Checked) v |= BV_MONTH(9);
       	if (CheckBoxM10->Checked) v |= BV_MONTH(10);
       	if (CheckBoxM11->Checked) v |= BV_MONTH(11);
       	if (CheckBoxM12->Checked) v |= BV_MONTH(12);

        bmpInfo[bmpIdx].variation = v;
}
//---------------------------------------------------------------------------


