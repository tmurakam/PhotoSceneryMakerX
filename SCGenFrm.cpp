/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * SCGenFrm.cpp : Scenery generation dialog
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
#include <IniFiles.hpp>
#include <SysUtils.hpp>
#include <stdio.h>

#include "gnugettext.hpp"

#include "Transform.h"

#include "SCGenFrm.h"
#include "SCGenThread.h"

#include "Util.h"
#include "OptDlg.h"
#include "targa.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSCGenForm *SCGenForm;

//---------------------------------------------------------------------------
__fastcall TSCGenForm::TSCGenForm(TComponent* Owner)
	: TForm(Owner)
{
	proj = NULL;
	thr = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSCGenForm::FormCreate(TObject *Sender)
{
	Font->Handle = GetStockObject(DEFAULT_GUI_FONT);
}
//---------------------------------------------------------------------------
void TSCGenForm::SetParam(PSMProject *prj)
{
	proj = prj;
}

//---------------------------------------------------------------------------
// Sanity check
bool TSCGenForm::SanityCheck(void)
{
	Transform *trans = proj->Trans;
	AnsiString msg;

	// Check resample version
	if (!OptionDlg->CheckResampleVersion()) {
		return false;
	}

	//
	// check parameters
	//
	if (trans->Resolution.x < 0 || trans->Resolution.y < 0) {
		msg = _("Some coordinate parameters are invalid. Please re-calibrate.");
		Application->MessageBox(msg.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (trans->Resolution.x < trans->Optres.x / 100 ||
	    trans->Resolution.y < trans->Optres.y / 100) {
		msg = _("Texture resolution is too HIGH. Please check texture resolution and try again.");
		Application->MessageBox(msg.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	if (trans->Resolution.x > trans->Optres.x * 100 ||
	    trans->Resolution.y > trans->Optres.y * 100) {
		msg = _("Texture resolution is too LOW. Please check texture resolution and try again.");
		Application->MessageBox(msg.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	double dx = trans->Width * trans->Resolution.x;
	double dy = trans->Height * trans->Resolution.y;

	if (!trans->Boundary.useWhole) {
		LatLon nw = trans->CalcLatLon(trans->Boundary.left, trans->Boundary.top);
		LatLon se = trans->CalcLatLon(trans->Boundary.right, trans->Boundary.bottom);

		dx = se.lon.deg - nw.lon.deg;
		dy = nw.lat.deg - se.lat.deg;
	}

	int nbitmap = (int)(dx / (90.0 / 8192.0)) * (int)(dy / (120.0 / 8192.0));
	int bmpsize = nbitmap * 43 / 1024;	/* MBytes */

	if (bmpsize > 100) {
		AnsiString fmt = _("Total texture size becomes very big (about %d MBytes).\nProceed?");
		msg.sprintf(fmt.c_str(), bmpsize);

		if (Application->MessageBox(msg.c_str(), "Warning",
			MB_YESNO | MB_ICONQUESTION) != ID_YES) {
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------------------
// Start Thread
void TSCGenForm::StartThread(int sw)
{
	thr = new SCGenThread(proj, sw);
	thr->OnTerminate = OnThreadTerminate;

	ProcessState(true);
	thr->Resume();
}

//---------------------------------------------------------------------------
// Thread Terminate Handler
void __fastcall TSCGenForm::OnThreadTerminate(TObject *Sender)
{
	thr = NULL;

	ProcessState(false);
//	Application->MessageBox("Done", "Done", MB_OK);
	StatusBar->SimpleText = _("Done");
}

//---------------------------------------------------------------------------
// Create inf file
void __fastcall TSCGenForm::ButtonMakeInfClick(TObject *Sender)
{
	if (SanityCheck() == false) return;
	StartThread(EX_MAKEINF);
}

//---------------------------------------------------------------------------
// Execute resample
void __fastcall TSCGenForm::ButtonResampleClick(TObject *Sender)
{
	if (SanityCheck() == false) return;
	StartThread(EX_RESAMPLE);
}

//---------------------------------------------------------------------------
// Merge alpha textures
void __fastcall TSCGenForm::ButtonMergeAlphaClick(TObject *Sender)
{
	StartThread(EX_MRGALPHA);
}

//---------------------------------------------------------------------------
// Convert Texture
void __fastcall TSCGenForm::ButtonConvertTextureClick(TObject *Sender)
{
	StartThread(EX_CONVTEX);
}
//---------------------------------------------------------------------------
// Generate BGL
void __fastcall TSCGenForm::ButtonGenBGLClick(TObject *Sender)
{
	StartThread(EX_GENBGL);
}
//---------------------------------------------------------------------------
// Execute all steps
void __fastcall TSCGenForm::ButtonDoAllClick(TObject *Sender)
{
	if (SanityCheck() == false) return;
	StartThread(EX_MAKEINF | EX_RESAMPLE | EX_MRGALPHA | EX_CONVTEX | EX_GENBGL);
}

//---------------------------------------------------------------------------
// Update all buttons
void TSCGenForm::ProcessState(bool start)
{
	ButtonDoAll->Enabled = !start;
	ButtonMakeInf->Enabled = !start;
	ButtonResample->Enabled = !start;
	ButtonMergeAlpha->Enabled = !start;
	ButtonConvertTexture->Enabled = !start;
	ButtonGenBGL->Enabled = !start;
	ButtonClose->Enabled = !start;

	ButtonStop->Enabled = start;

	if (start == false) {
		StatusBar->SimpleText = "Ready";
	}
}
//---------------------------------------------------------------------------
// Stop process
void __fastcall TSCGenForm::ButtonStopClick(TObject *Sender)
{
	if (thr) {
		thr->Terminate();
	}
}
//---------------------------------------------------------------------------

