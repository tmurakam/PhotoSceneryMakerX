/*
 * Photo Scenery Maker X
 *
 * Copyright (C) 2003-2007 Takuya Murakami
 *
 * SCGenFrm.cpp : Scenery generation thread
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
#include <stdio.h>

#include "gnugettext.hpp"

#include "SCGenThread.h"
#include "SCGenFrm.h"
#include "OptDlg.h"
//#include "targa.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
// Constructor
//
__fastcall SCGenThread::SCGenThread(PSMProject *proj, int sw)
	: TThread(true)
{
	Sw = sw;
	Proj = proj;
}
//---------------------------------------------------------------------------
// Main entry
//
void __fastcall SCGenThread::Execute()
{
	try {
		if (Sw & EX_MAKEINF) MakeInf();
		if (!Terminated && Sw & EX_GENBGL) Resample();

		if (Terminated) {
			ResultMsg = _("Interrupted");
		} else {
			ResultMsg = _("Done");
		}
	}
	catch (Exception &e) {
		//ShowMessage(e.Message);
		ResultMsg = e.Message;
	}

	Synchronize((TThreadMethod)&ShowMsg);
}

// Show Messagebox
void __fastcall SCGenThread::ShowMsg(void)
{
	Application->MessageBox(ResultMsg.c_str(), "Result", MB_OK);
}

//---------------------------------------------------------------------------
// Create INF file for resample.exe
//

// Get INF file name
AnsiString SCGenThread::InfFileName(void)
{
	AnsiString path = Proj->OutDir;
	path.sprintf("%s\\PhotoSceneryMaker.inf", Proj->OutDir);

	return path;
}

// Create one inf file
void SCGenThread::MakeInf(void)
{
	AnsiString msg = _("Creating inf files...");
	SetStatusMsg(msg);

	// Create Output directories
	MkDir(Proj->OutDir);

        AnsiString inf = InfFileName();

	AnsiString BmpFile = Proj->BmpFile();
	if (BmpFile.IsEmpty()) {
		return;
	}

        int nSource = 1;
        int nNight = -1;
        int nAlpha = -1;
        if (Proj->HasNight) {
            nSource++;
            nNight = nSource;
	}
        if (Proj->HasAlpha) {
            nSource++;
            nAlpha = nSource;
        }

	// Open inf file
	FILE *fp;
	fp = fopen(inf.c_str(), "w");
	if (!fp) {
		AnsiString msg, fmt;
		fmt = _("Can't open inf file : %s");
		msg.sprintf(fmt.c_str(), inf.c_str());
		throw Exception(msg);
	}

	Transform *trans = Proj->Trans;

	// Build Source section
        if (nSource >= 2) {
		fprintf(fp, "[Source]\n");
	        fprintf(fp, "Type = MultiSource\n");
	        fprintf(fp, "NumberOfSources = %d\n", nSource);
	        fprintf(fp, "\n");

		MakeInfSub(fp, 1, "Imagery", Proj->BmpFile(BM_DAY), trans);

	        if (Proj->HasAlpha) {
	        	fprintf(fp, "Channel_LandWaterMask = %d.0\n", nAlpha);
	        }
	} else {
		MakeInfSub(fp, 0, "Imagery", Proj->BmpFile(BM_DAY), trans);
        }
	fprintf(fp, "Variation = Day\n");
        fprintf(fp, "\n");

        // set night bitmap section
        if (nNight > 0) {
	        MakeInfSub(fp, nNight, "Imagery", Proj->BmpFile(BM_NIGHT), trans);
	        if (Proj->HasAlpha) {
	        	fprintf(fp, "Channel_LandWaterMask = %d.0\n", nAlpha);
	        }
	        fprintf(fp, "\n");
        }

        // alpha channel (land water mask)
        if (nAlpha > 0) {
	        MakeInfSub(fp, nAlpha, "None", Proj->BmpFile(BM_ALPHA), trans);
		fprintf(fp, "Variation = Night\n");
	        if (Proj->HasAlpha) {
	        	fprintf(fp, "Channel_LandWaterMask = %d.0\n", nAlpha);
	        }
	        fprintf(fp, "\n");
        }

	// Build Destination section
	fprintf(fp, "[Destination]\n");
	fprintf(fp, "DestDir = \"%s\"\n", Proj->OutDir.c_str());
	fprintf(fp, "DestBaseFileName = \"%s\"\n", Proj->BaseFile.c_str());
	if (Proj->Lod < 0) {
        	fprintf(fp, "LOD = Auto\n");
        } else {
	        fprintf(fp, "LOD = 7,%d\n", Proj->Lod);
        }
        
	if (trans->Boundary.useWhole) {
		fprintf(fp, "\tUseSourceDimensions = 1\n");
	} else {
		fprintf(fp, "\tUseSourceDimensions = 0\n");

		LatLon nw = trans->CalcLatLon(trans->Boundary.left, trans->Boundary.top);
		LatLon se = trans->CalcLatLon(trans->Boundary.right, trans->Boundary.bottom);

		fprintf(fp, "\tNorthLat = %.24f\n", nw.lat.deg);
		fprintf(fp, "\tWestLong = %.24f\n", nw.lon.deg);
		fprintf(fp, "\tSouthLat = %.24f\n", se.lat.deg);
		fprintf(fp, "\tEastLong = %.24f\n", se.lon.deg);
	}
	fclose(fp);
}

void SCGenThread::MakeInfSub(FILE *fp, int n, const char *layer, AnsiString bmpfile, Transform *trans)
{
	if (n > 0) {
		fprintf(fp, "[Source%d]\n", n);
        } else {
	        fprintf(fp, "[Source]\n");
        }
	fprintf(fp, "Type = BMP\n");
	fprintf(fp, "Layer = %s\n", layer);
	fprintf(fp, "SourceDir = \"%s\"\n", ExtractFileDir(bmpfile).c_str());
	fprintf(fp, "SourceFile = \"%s\"\n", ExtractFileName(bmpfile).c_str());
	fprintf(fp, "ULXMAP = %.24f\n", trans->Base.lon.deg);
	fprintf(fp, "ULYMAP = %.24f\n", trans->Base.lat.deg);
	fprintf(fp, "XDIM = %.24f\n", trans->Resolution.x);
	fprintf(fp, "YDIM = %.24f\n", trans->Resolution.y);
}

//---------------------------------------------------------------------------
// Execute generic commands
//
int SCGenThread::ExecCmd(AnsiString cmdline, AnsiString desc)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	int ret;

	memset(&si, 0, sizeof(si));
	si.cb=sizeof(si);

	// Create process
	ret = CreateProcess(NULL, cmdline.c_str(),NULL,NULL,FALSE,
		BELOW_NORMAL_PRIORITY_CLASS,
		NULL,NULL,&si,&pi);

	if (ret == 0) {
		// execution failed
		LPTSTR buf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			LANG_USER_DEFAULT,
//			MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
			(LPTSTR)&buf,
			0,
			NULL );

		AnsiString msg; 
		msg.sprintf("%s : %s", desc, buf);
		LocalFree(buf);

		throw Exception(msg);
	}

	// Wait process termination
	for (;;) {
		int st = WaitForSingleObject(pi.hProcess, 200);
		if (st == WAIT_OBJECT_0) break;

		if (Terminated) {
			TerminateProcess(pi.hProcess, 0);
		}
	}
		
	CloseHandle(pi.hProcess);

	return 0;
}

//---------------------------------------------------------------------------
// Execute resample.exe
//
void SCGenThread::Resample(void)
{
	if (Terminated) return;

	SetStatusMsg("Resampling...");

	// Change directory to working directory
	ChDir(Proj->OutDir);

	// Execute resample
	AnsiString inf = InfFileName();

	AnsiString cmdline;
	cmdline.sprintf("\"%s\\resample.exe\" \"%s\"",
			OptionDlg->GetSDKPath(), inf);
	if (ExecCmd(cmdline, "resample.exe") != 0) {
		AnsiString title = _("Error");
		AnsiString mes = _("Some errors occured.");
		Application->MessageBox(mes.c_str(), title.c_str(), MB_OK);
	}
}

//---------------------------------------------------------------------------
// Set status message
//
void SCGenThread::SetStatusMsg(AnsiString msg)
{
	SCGenForm->StatusBar->SimpleText = msg;
}
