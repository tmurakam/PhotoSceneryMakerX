/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * MForm.cpp : Main Form
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
#include <Registry.hpp>

#include "gnugettext.hpp"

#include "MForm.h"
#include "LLDlg.h"
#include "OptDlg.h"
#include "AboutDlg.h"
#include "SCGenFrm.h"
#include "PJForm.h"
#include "Bitmap.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
//
// Constructor
//
const crMove = 5;

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	proj = NULL;

	isCpSpecifing = false;
	isDragging = false;
        isTranslated = false;

	bitmap = NULL;
	curBmpIdx = BM_SUMMER;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	TRegistry *reg = NULL;

	// Load window position from registry
	try {
		reg = new TRegistry;
		reg->RootKey = HKEY_CURRENT_USER;
		reg->OpenKey(REG_KEY, true);
	
		int top, left, width, height;
		top = reg->ReadInteger("WindowTop");
		left = reg->ReadInteger("WindowLeft");
		width = reg->ReadInteger("WindowWidth");
		height = reg->ReadInteger("WindowHeight");

		if (top < 0) top = 0;
		if (left < 0) left = 0;

		if (top > Screen->Height - 50) top = Screen->Height - 50;
		if (left > Screen->Width - 50) left = Screen->Width - 50;

		if (width < 100) width = 100;
		if (height < 100) height = 100;
		if (width > Screen->Width) width = Screen->Width;
		if (height > Screen->Height) height = Screen->Height;

		Top = top;
		Left = left;
		Width = width;
		Height = height;
	}
	catch (const Exception &e) {
		// do nothing
	}
	delete reg;

	UpdateMenu();

	HICON h = ::LoadCursor(HInstance, "MOVECURSOR");
	Screen->Cursors[crMove] = h;

	// Load initial file
	if (ParamCount() > 0) {
		proj = new PSMProject;
		proj->LoadFromFile(ParamStr(1));
		ChangeBmp(curBmpIdx, true);
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
	TranslateAllForms();
}

//---------------------------------------------------------------------------
//
// Translate all text using gettext
//
void TMainForm::TranslateAllForms(void)
{
	if (isTranslated) {
		RetranslateComponent(this);
		RetranslateComponent(LatLonDlg);
		RetranslateComponent(OptionDlg);
		RetranslateComponent(AboutDialog);
		RetranslateComponent(SCGenForm);
		RetranslateComponent(PrjForm);
        } else {
		TranslateComponent(this);
		TranslateComponent(LatLonDlg);
		TranslateComponent(OptionDlg);
		TranslateComponent(AboutDialog);
		TranslateComponent(SCGenForm);
		TranslateComponent(PrjForm);
                isTranslated = true;
        }
}

//---------------------------------------------------------------------------
//
// Quit
//
void __fastcall TMainForm::MenuQuitClick(TObject *Sender)
{
	if (!CheckSave()) return;

	delete(proj);
	Application->Terminate();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = CheckSave();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	// save windows position
	try {
		TRegistry *reg = new TRegistry;
		reg->RootKey = HKEY_CURRENT_USER;
		reg->OpenKey(REG_KEY, true);

		reg->WriteInteger("WindowTop", Top);
		reg->WriteInteger("WindowLeft", Left);
		reg->WriteInteger("WindowWidth", Width);
		reg->WriteInteger("WindowHeight", Height);

		delete reg;
	}
	catch (Exception &e) {
		// do nothing
	}
}

//---------------------------------------------------------------------------
// Create new project
void __fastcall TMainForm::MenuNewPrjClick(TObject *Sender)
{
	if (proj) {
		if (!CheckSave()) return;
		delete proj;
	}

	proj = new PSMProject;
	MenuPrjPropertyClick(Sender);
}
//---------------------------------------------------------------------------
// Open project
void __fastcall TMainForm::MenuOpenPrjClick(TObject *Sender)
{
	if (proj && !CheckSave()) return;
	if (!OpenPrjDialog->Execute()) return;

	PSMProject *newproj = new PSMProject;
	try {
		newproj->LoadFromFile(OpenPrjDialog->FileName);
	}
	catch (Exception &e) {
		AnsiString msg = _("Can't load project file.");
		Application->MessageBox(msg.c_str(), "Error", MB_OK | MB_ICONERROR);
		return;	// abort
	}

	if (proj) delete proj;
	proj = newproj;

	// Reload BMP file
	ChangeBmp(curBmpIdx, true);
}
//---------------------------------------------------------------------------
// Save project
void __fastcall TMainForm::MenuPrjSaveClick(TObject *Sender)
{
	if (!proj->SaveToFile()) {
		MenuPrjSaveAsClick(Sender);
	} else {
		UpdateMenu();
	}
}

//---------------------------------------------------------------------------
// Save project as new file
void __fastcall TMainForm::MenuPrjSaveAsClick(TObject *Sender)
{
	if (!SavePrjDialog->Execute()) return;
	proj->SaveToFile(SavePrjDialog->FileName);
	UpdateMenu();
}

//---------------------------------------------------------------------------
// Check save
bool TMainForm::CheckSave(void)
{
	if (proj && proj->Modified) {
		int res;
		AnsiString title = _("Confirmation");
		AnsiString msg = _("Project is modified. Do you want to save?");
		res = Application->MessageBox(msg.c_str(), title.c_str(),
			MB_YESNOCANCEL | MB_ICONQUESTION);

		if (res == IDCANCEL) return false;
		if (res == IDYES) {
			proj->SaveToFile();
		}
	}
	return true;
}

//---------------------------------------------------------------------------
// Specify project property
void __fastcall TMainForm::MenuPrjPropertyClick(TObject *Sender)
{
	PrjForm->LoadData(proj);
	if (PrjForm->ShowModal() == mrOk) {
		PrjForm->UpdateData(proj);
		ChangeBmp(curBmpIdx, true);
		UpdateMenu();
	}

}

//---------------------------------------------------------------------------
// Update menu items
void TMainForm::UpdateMenu(void)
{
	MenuPrjSave->Enabled = false;
	MenuPrjSaveAs->Enabled = false;
	MenuSCGen->Enabled = false;
	MenuPrjProperty->Enabled = false;
	MenuView->Enabled = false;
	MenuCalibration->Enabled = false;

	if (!proj) return;

	MenuPrjProperty->Enabled = true;
	MenuView->Enabled = true;
	MenuViewSummer->Checked   = (curBmpIdx == BM_SUMMER);
	MenuViewSpring->Checked   = (curBmpIdx == BM_SPRING);
	MenuViewFall->Checked     = (curBmpIdx == BM_FALL);
	MenuViewWinter->Checked   = (curBmpIdx == BM_WINTER);
	MenuViewHSWinter->Checked = (curBmpIdx == BM_HSWINTER);
	MenuViewLightmap->Checked = (curBmpIdx == BM_LIGHTMAP);
	MenuViewAlpha->Checked    = (curBmpIdx == BM_ALPHA);

	if (!isCpSpecifing) {
		MenuCalibration->Enabled = true;
		MenuPrjSave->Enabled = proj->Modified;
		MenuPrjSaveAs->Enabled = true;
		MenuSCGen->Enabled = true;
	}
}

//---------------------------------------------------------------------------
// Start specify control points for calibration
void __fastcall TMainForm::SetCPointClick(TObject *Sender)
{
	StartCpSpecify(CP_0);
}

//---------------------------------------------------------------------------
// specify bitmap boundary
void __fastcall TMainForm::MenuTopClick(TObject *Sender)
{
	StartCpSpecify(CP_BOUND_TOP);
}

void __fastcall TMainForm::MenuBottomClick(TObject *Sender)
{
	StartCpSpecify(CP_BOUND_BOTTOM);
}

void __fastcall TMainForm::MenuLeftClick(TObject *Sender)
{
	StartCpSpecify(CP_BOUND_LEFT);
}

void __fastcall TMainForm::MenuRightClick(TObject *Sender)
{
	StartCpSpecify(CP_BOUND_RIGHT);
}

//---------------------------------------------------------------------------
// Start specify control points for calibration
void TMainForm::StartCpSpecify(int cp)
{
	isCpSpecifing = true;
	CpSpecifing = cp;

	AnsiString tmp;
	
	switch (CpSpecifing) {
	case CP_0:
		tmp = _("Specify #1 correction point");
		break;
	case CP_1:
		tmp = _("Specify #2 correction point");
		break;
	case CP_BOUND_TOP:
		tmp = _("Specify bitmap top boundary");
		break;
	case CP_BOUND_BOTTOM:
		tmp = _("Specify bitmap bottom boundary");
		break;
	case CP_BOUND_LEFT:
		tmp = _("Specify bitmap left boundary");
		break;
	case CP_BOUND_RIGHT:
		tmp = _("Specify bitmap right boundary");
		break;
	}

	StatusBar->Panels->Items[0]->Text = tmp;

	PaintBox->Cursor = crCross;
}

//---------------------------------------------------------------------------
// Mouse Event : Down
void __fastcall TMainForm::OnMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	// drag
	if (!isCpSpecifing || Button != mbLeft) {
		// Start dragging
		isDragging = true;
		POINT p;
		GetCursorPos(&p);

		DragX = p.x;
		DragY = p.y;

		MoveX = MoveY = 0;
		
		Timer->Enabled = true;

		// Modify dragging cursor
		// Note: PaintBox->Cursor modification does not work...
		Screen->Cursor = crMove;
		return;
	}

	// Specify control point.
	ControlPoint *c;

	switch (CpSpecifing) {
	case CP_0:
	case CP_1:
		c = &cp[CpSpecifing];
		c->v.x = X;
		c->v.y = Y;

		// Input lat/lon with dialog
		if (LatLonDlg->ShowModal() == mrCancel) {
			StatusBar->Panels->Items[0]->Text = _("Ready");
			isCpSpecifing = false;
			UpdateMenu();
			PaintBox->Cursor = crDefault;
			return;
		}

		c->p.lat.SetStr(LatLonDlg->LatEdit->Text);
		c->p.lon.SetStr(LatLonDlg->LonEdit->Text);

		// check value
		if (c->p.lat.deg <= -90 || c->p.lat.deg >= 90 ||
			c->p.lon.deg <= -180 || c->p.lon.deg >= 360) {
			AnsiString msg = _("Latitude/Longitude value out of range.");
			Application->MessageBox(msg.c_str(), "Error", MB_OK | MB_ICONERROR);

			// try again
			return;
		}

		if (CpSpecifing == CP_0) {
			StartCpSpecify(CP_1);
			return;
		}

		// Calculate calibration parameters
		if (proj->Trans->CalcParameters(cp)) {
			proj->Modified = true;
		} else {
			AnsiString msg = _("Calibration parameters are invalid. Please retry.");
			Application->MessageBox(msg.c_str(), "Error", MB_OK | MB_ICONERROR);
		}
		break;

		// Specify bitmap boundary
	case CP_BOUND_TOP:
		proj->Trans->Boundary.useWhole = false;
		proj->Trans->Boundary.top = Y;
		break;

	case CP_BOUND_BOTTOM:
		proj->Trans->Boundary.useWhole = false;
		proj->Trans->Boundary.bottom = Y;
		break;

	case CP_BOUND_LEFT:
		proj->Trans->Boundary.useWhole = false;
		proj->Trans->Boundary.left = X;
		break;

	case CP_BOUND_RIGHT:
		proj->Trans->Boundary.useWhole = false;
		proj->Trans->Boundary.right = X;
		break;
	}

	StatusBar->Panels->Items[0]->Text = _("Ready");
	proj->Modified = true;

	PaintBox->Invalidate();

	isCpSpecifing = false;
	UpdateMenu();

	PaintBox->Cursor = crDefault;
}
//---------------------------------------------------------------------------
// Mouse Event : Move
void __fastcall TMainForm::OnMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	if (!proj) return;
	
	AnsiString tmp;
        tmp.sprintf("(%d,%d)", X, Y);
	StatusBar->Panels->Items[1]->Text = tmp;

	LatLon ll = proj->Trans->CalcLatLon(X, Y);
	tmp.sprintf("%s %s", ll.lat.GetStr(), ll.lon.GetStr());
	StatusBar->Panels->Items[2]->Text = tmp;

	// drag
	if (isDragging) {
		POINT p;
		GetCursorPos(&p);
		MoveX = p.x - DragX;
		MoveY = p.y - DragY;
	}
}

//---------------------------------------------------------------------------
// Mouse Event : Up
void __fastcall TMainForm::OnMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (isDragging) {
		isDragging = false;
		Timer->Enabled = false;
		Screen->Cursor = crDefault;
	}
}
//---------------------------------------------------------------------------
// Scroll texture
void __fastcall TMainForm::OnTimer(TObject *Sender)
{
	if (!isDragging) return;

	ScrollBox->HorzScrollBar->Position += MoveX * 0.5;
	ScrollBox->VertScrollBar->Position += MoveY * 0.5;
}

//---------------------------------------------------------------------------
// Texture Correction
void __fastcall TMainForm::ExecCorrectionClick(TObject *Sender)
{
	int cx, cy;
	proj->Trans->CalcOptSize(bitmap->Width, bitmap->Height, &cx, &cy);

	AnsiString fmt, mes1, mes2, mes;
	fmt = _("Optimal bitmap size is %d x %d.\n");
	mes1.sprintf(fmt.c_str(), cx, cy);
	mes2 = _("You can resize the bitmap with some image editing tools.");

	mes = mes1 + mes2;
	Application->MessageBox(mes.c_str(), "Info", MB_ICONINFORMATION | MB_OK);
}
//---------------------------------------------------------------------------
// Show option dialog
void __fastcall TMainForm::MenuOptionClick(TObject *Sender)
{
	if (OptionDlg->ShowModal() != mrOk) return;
	TranslateAllForms();
}
//---------------------------------------------------------------------------
// Show scenery generation dialog
void __fastcall TMainForm::MenuSCGenClick(TObject *Sender)
{
	SCGenForm->SetParam(proj);
	SCGenForm->ShowModal();
}
//---------------------------------------------------------------------------
// Show about(version) dialog
void __fastcall TMainForm::MenuAboutClick(TObject *Sender)
{
	AboutDialog->ShowModal();
}
//---------------------------------------------------------------------------
// Show progress on status bar
void TMainForm::SetProgress(int perc)
{
	AnsiString tmp;
	tmp.sprintf("Processing: %d%%", perc);
	StatusBar->Panels->Items[0]->Text = tmp;
}
//---------------------------------------------------------------------------
// Switch seasonal bitmaps
void TMainForm::ChangeBmp(int bmpidx, bool reload)
{
	TCursor saveCursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;

	try {
		curBmpIdx = bmpidx;

		if (bitmap) {
			delete bitmap;
		}
		bitmap = //new Graphics::TBitmap;
		  new TBitmap2;
		try {
			bitmap->LoadFromFile(proj->BmpFile(curBmpIdx));

			proj->Trans->Width = bitmap->Width;
			proj->Trans->Height = bitmap->Height;

			PaintBox->Width = bitmap->Width;
			PaintBox->Height = bitmap->Height;

			PaintBox->Invalidate();
		}
		catch (Exception &e) {
			AnsiString title = _("Can't open bitmap file");
			AnsiString msg = e.Message;
			Application->MessageBox(msg.c_str(),
						title.c_str(), MB_OK | MB_ICONERROR);

			delete bitmap;
			bitmap = NULL;
		}

		// fix boundary (ad hoc...)
		if (proj->Trans->Boundary.right <= 0) {
			proj->Trans->Boundary.right = proj->Trans->Width - 1;
		}
		if (proj->Trans->Boundary.bottom <= 0) {
			proj->Trans->Boundary.bottom = proj->Trans->Height - 1;
		}
	
		UpdateMenu();
	}
	__finally {
		Screen->Cursor = saveCursor;
	}
}
//---------------------------------------------------------------------------
// Display texture
void __fastcall TMainForm::PaintBoxPaint(TObject *Sender)
{
	if (!bitmap) return;
	
	// Draw Bitmap
	PaintBox->Canvas->Draw(0, 0, bitmap);

	// Draw grids
	PaintBox->Canvas->Pen->Color = clWhite;
	PaintBox->Canvas->Pen->Width = 1;
        PaintBox->Canvas->Pen->Style = psDashDot;

	Transform *trans = proj->Trans;
	
	LatLon nw = trans->CalcLatLon(0, 0);
	LatLon se = trans->CalcLatLon(bitmap->Width - 1, bitmap->Height - 1);

	int min, max, i;

	// Latitude line
	const double latbound = 90.0 / 8192.0;	// LOD 13
	min = (int)(se.lat.deg / latbound);
	max = (int)(nw.lat.deg / latbound) + 1;
	for (i = min; i <= max; i++) {
		int y = trans->CalcY(i * latbound);
		PaintBox->Canvas->MoveTo(0, y);
		PaintBox->Canvas->LineTo(bitmap->Width - 1, y);
	}

	// Longitude line
	const double lonbound = 120.0 / 8192.0;	// LOD 13
	min = (int)(nw.lon.deg / lonbound - 0.5);
	max = (int)(se.lon.deg / lonbound - 0.5) + 1;
	for (i = min; i <= max; i++) {
		int x = trans->CalcX(i * lonbound);
		PaintBox->Canvas->MoveTo(x, 0);
		PaintBox->Canvas->LineTo(x, bitmap->Height - 1);
	}

	// Bitmap Boundary
	if (!proj->Trans->Boundary.useWhole) {
		PaintBox->Canvas->Pen->Color = clYellow;
		int x1 = proj->Trans->Boundary.left;
		int x2 = proj->Trans->Boundary.right;
		int y1 = proj->Trans->Boundary.top;
		int y2 = proj->Trans->Boundary.bottom;

		PaintBox->Canvas->MoveTo(x1, y1);
		PaintBox->Canvas->LineTo(x2, y1);
		PaintBox->Canvas->LineTo(x2, y2);
		PaintBox->Canvas->LineTo(x1, y2);
		PaintBox->Canvas->LineTo(x1, y1);
	}
}	

//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuViewSummerClick(TObject *Sender)
{
	ChangeBmp(BM_SUMMER);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuViewSpringClick(TObject *Sender)
{
	ChangeBmp(BM_SPRING);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuViewFallClick(TObject *Sender)
{
	ChangeBmp(BM_FALL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuViewWinterClick(TObject *Sender)
{
	ChangeBmp(BM_WINTER);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuViewHSWinterClick(TObject *Sender)
{
	ChangeBmp(BM_HSWINTER);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuViewLightmapClick(TObject *Sender)
{
	ChangeBmp(BM_LIGHTMAP);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MenuViewAlphaClick(TObject *Sender)
{
	ChangeBmp(BM_ALPHA);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MenuManualClick(TObject *Sender)
{
	ShowHtml("manual");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuTutorialClick(TObject *Sender)
{
	ShowHtml("tutorial");
}

void TMainForm::ShowHtml(AnsiString prefix)
{
	AnsiString html;

	html = ExtractFilePath(Application->ExeName);
	html += "doc\\";
	html += prefix;
	html += ".";
	html += OptionDlg->GetLangCode();
	html += ".html";

	ShellExecute(this->Handle, "open", html.c_str(),
		NULL, NULL, SW_SHOW);
}



//---------------------------------------------------------------------------
