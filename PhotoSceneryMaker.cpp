/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * PhotoSceneryMaker.cpp : Main
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

#include "gnugettext.hpp"

//---------------------------------------------------------------------------
USEFORM("MForm.cpp", MainForm);
USEFORM("LLDlg.cpp", LatLonDlg);
USEFORM("OptDlg.cpp", OptionDlg);
USEFORM("AboutDlg.cpp", AboutDialog);
USEFORM("SCGenFrm.cpp", SCGenForm);
USEFORM("PJForm.cpp", PrjForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
		 Application->Initialize();
                 Application->Title = "Photo Scenery Maker";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TLatLonDlg), &LatLonDlg);
		Application->CreateForm(__classid(TOptionDlg), &OptionDlg);
		Application->CreateForm(__classid(TAboutDialog), &AboutDialog);
		Application->CreateForm(__classid(TSCGenForm), &SCGenForm);
		Application->CreateForm(__classid(TPrjForm), &PrjForm);
		Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
