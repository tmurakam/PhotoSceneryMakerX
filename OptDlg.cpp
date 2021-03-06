/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * OptDlg.cpp : Option Dialog
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
#include "OptDlg.h"
#include "Util.h"

struct _lang {
	char *code;
	char *locale;
	char *desc;
} Lang[] = {
	{ "", "", "System Locale" },
	{ "en", "en", "English" },
	{ "ja", "ja_JP", "Japanese" },
	{ NULL, NULL }
};

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionDlg *OptionDlg;
//---------------------------------------------------------------------------
__fastcall TOptionDlg::TOptionDlg(TComponent* Owner)
	: TForm(Owner)
{
	curLangIdx = 0;
}

AnsiString TOptionDlg::GetSDKPath(void)
{
	return EditSDKPath->Text;
}

//---------------------------------------------------------------------------
// Change Languages
void TOptionDlg::ChangeLang(void)
{
	UseLanguage(Lang[curLangIdx].locale);
}

AnsiString TOptionDlg::GetLangCode(void)
{
	AnsiString lang = Lang[curLangIdx].code;
	if (lang.IsEmpty()) {
		lang = GetCurrentLanguage();
		if (lang == "C") {
			lang = "en";
		} else {
			lang = lang.SubString(1, 2);
		}
	}
	return lang;
}

//---------------------------------------------------------------------------
// Load option values from registry
void TOptionDlg::LoadReg(void)
{
	TRegistry *reg = new TRegistry;
	reg->RootKey = HKEY_CURRENT_USER;
	reg->OpenKey(REG_KEY, true);

	AnsiString sdkpath, lng;
	try {
		EditSDKPath->Text = reg->ReadString("TerrainSDKPath");
		lng = reg->ReadString("Language");
	}
	catch (const Exception &e) {
		// do nothing
	}

	// set language index
	for (int i = 0; ; i++) {
		if (Lang[i].code == NULL) break;
		if (lng == Lang[i].code) {
			curLangIdx = i;
			break;
		}
	}
	ListLang->ItemIndex = curLangIdx;
	ChangeLang();
	
	reg->CloseKey();
	delete reg;
}

//---------------------------------------------------------------------------
void __fastcall TOptionDlg::FormCreate(TObject *Sender)
{
	Font->Handle = GetStockObject(DEFAULT_GUI_FONT);

	// Setup Language Selection
	for (int i = 0; ; i++) {
		if (Lang[i].code == NULL) break;
		ListLang->Items->Add(Lang[i].desc);
	}

	LoadReg();
}

//---------------------------------------------------------------------------
void __fastcall TOptionDlg::FormShow(TObject *Sender)
{
	LoadReg();
}
//---------------------------------------------------------------------------
void __fastcall TOptionDlg::ButtonOKClick(TObject *Sender)
{
	TRegistry *reg = new TRegistry;
	reg->RootKey = HKEY_CURRENT_USER;
	reg->OpenKey(REG_KEY, true);

	reg->WriteString("TerrainSDKPath", EditSDKPath->Text);

	// Change Language
	curLangIdx = ListLang->ItemIndex;
	ChangeLang();

	reg->WriteString("Language", Lang[curLangIdx].code);

	reg->CloseKey();
	delete reg;
}

//---------------------------------------------------------------------------

void __fastcall TOptionDlg::ButtonBrowseSDKClick(TObject *Sender)
{
#if 0
	AnsiString f = SelectFolder("", Handle);
	if (!f.IsEmpty()) {
		EditSDKPath->Text = f;
	}
#endif
	OpenDialog->InitialDir = EditSDKPath->Text;
	OpenDialog->FileName = "resample.exe";
	OpenDialog->Filter = "Terrain SDK Resample tool|resample.exe";
	if (!OpenDialog->Execute()) return;

	//
	// check resample version
	//
	AnsiString save = EditSDKPath->Text;
	EditSDKPath->Text = ExtractFileDir(OpenDialog->FileName);
}

