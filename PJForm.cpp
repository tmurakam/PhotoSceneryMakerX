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
}
//---------------------------------------------------------------------------
void __fastcall TPrjForm::FormCreate(TObject *Sender)
{
	Font->Handle = GetStockObject(DEFAULT_GUI_FONT);
}
//---------------------------------------------------------------------------
void TPrjForm::LoadData(PSMProject *proj)
{
	EditBmpDay->Text   = proj->BmpFile(BM_DAY);
	EditBmpLightmap->Text = proj->BmpFile(BM_NIGHT);
	EditBmpAlpha->Text    = proj->BmpFile(BM_ALPHA);

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
}

void TPrjForm::UpdateData(PSMProject *proj)
{
	proj->SetBmpFile(BM_DAY,   EditBmpDay->Text);
	proj->SetBmpFile(BM_NIGHT, EditBmpLightmap->Text);
	proj->SetBmpFile(BM_ALPHA, EditBmpAlpha->Text);

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
// Select BMP file
void TPrjForm::RefBmpFile(TEdit *edit)
{
	if (OpenDialog->Execute()) {
		edit->Text = OpenDialog->FileName;
	}
}

//---------------------------------------------------------------------------
void __fastcall TPrjForm::ButtonRefBmpDayClick(TObject *Sender)
{
	RefBmpFile(EditBmpDay);
}
//---------------------------------------------------------------------------

void __fastcall TPrjForm::ButtonRefBmpNightClick(TObject *Sender)
{
	RefBmpFile(EditBmpLightmap);
}
//---------------------------------------------------------------------------

void __fastcall TPrjForm::ButtonRefBmpAlphaClick(TObject *Sender)
{
	RefBmpFile(EditBmpAlpha);
}

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




