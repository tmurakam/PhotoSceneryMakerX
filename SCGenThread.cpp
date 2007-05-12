/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
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
#include "targa.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
const char *SeasonSuffix[] = SEASON_SUFFIX;
const char *SeasonName[] = SEASON_NAME;

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
		if (!Terminated && Sw & EX_RESAMPLE) Resample();
		if (!Terminated && Sw & EX_MRGALPHA) MergeAlpha();
		if (!Terminated && Sw & EX_CONVTEX) ConvTex();
		if (!Terminated && Sw & EX_GENBGL) GenBgl();

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
void SCGenThread::MakeInf(void)
{
	AnsiString msg = _("Creating inf files...");
	SetStatusMsg(msg);

	// Create Output directories
	MkDir(Proj->OutDir);
	MkDir(Proj->OutDir + "\\TmpBmp");
	MkDir(Proj->OutDir + "\\TmpAlpha");

	if (!Proj->HasSeason) {
		MakeInf(BM_SUMMER);
		MakeInf(BM_ALPHA);
	} else {
		for (int i = 0; i < BM_MAX; i++) {
			MakeInf(i);
		}
	}
}

// Get INF file name
AnsiString SCGenThread::InfFileName(int season)
{
	AnsiString path = Proj->OutDir;
	path.sprintf("%s\\%s.inf", Proj->OutDir, SeasonSuffix[season]);

	return path;
}

// Get BMP path
AnsiString SCGenThread::BmpPath(int season)
{
	AnsiString path;
	if (season == BM_ALPHA) {
		path.sprintf("%s\\TmpAlpha", Proj->OutDir);
	} else {
		path.sprintf("%s\\TmpBmp", Proj->OutDir);
	}
	return path;
}

// Create one inf file
void SCGenThread::MakeInf(int season)
{
	AnsiString inf = InfFileName(season);

	AnsiString BmpFile = Proj->BmpFile(season);
	if (BmpFile.IsEmpty()) {
		return;
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
	fprintf(fp, "[Source]\n");
	fprintf(fp, "\tType = CUSTOM\n");
	fprintf(fp, "\tSourceDir = \"%s\"\n", ExtractFileDir(BmpFile).c_str());
	fprintf(fp, "\tSourceFile = \"%s\"\n", ExtractFileName(BmpFile).c_str());
	fprintf(fp, "\tLat = %.24f\n", trans->Base.lat.deg);
	fprintf(fp, "\tLon = %.24f\n", trans->Base.lon.deg);
	fprintf(fp, "\tNumOfCellsPerLine = %d\n", trans->Width);
	fprintf(fp, "\tNumOfLines = %d\n", trans->Height);
	fprintf(fp, "\tCellXdimensionDeg = %.24f\n", trans->Resolution.x);
	fprintf(fp, "\tCellYdimensionDeg = %.24f\n", trans->Resolution.y);

	// Build Destination section
	fprintf(fp, "\n[Destination]\n");
	fprintf(fp, "\tDestDir = \"%s\"\n", BmpPath(season).c_str());
	fprintf(fp, "\tDestBaseFileName = \"%s\"\n", Proj->BaseFile.c_str());
	if (Proj->HasSeason) {
		fprintf(fp, "\twithseasons = 1\n");
		fprintf(fp, "\tseason = %s\n", SeasonName[season]);
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
	for (int i = 0; i < BM_MAX; i++) {
		if (Terminated) return;

		if (i != BM_SUMMER && i != BM_ALPHA && !Proj->HasSeason) {
			continue;
		}
		if (i == BM_ALPHA && !Proj->HasAlpha) {
			continue;
		}

		AnsiString fmt = _("Resampling : %s...");
		AnsiString msg;
		msg.sprintf(fmt.c_str(), SeasonName[i]);
		SetStatusMsg(msg);

		// Change directory to working directory
		AnsiString bmppath = BmpPath(i);
		ChDir(bmppath);

		// Execute resample
		AnsiString inf = InfFileName(i);
	
		AnsiString cmdline;
		cmdline.sprintf("\"%s\\resample.exe\" \"%s\"",
				OptionDlg->GetSDKPath(), inf);
		if (ExecCmd(cmdline, "resample.exe") != 0) {
			AnsiString title = _("Error");
			AnsiString mes = _("Some errors occured.");
			Application->MessageBox(mes.c_str(), title.c_str(), MB_OK);
		}
	}

	// Move tmf file : Only one tmf file is needed.
	AnsiString tmf;
	tmf.sprintf("%s\\%s.tmf", BmpPath(BM_SUMMER), Proj->BaseFile);
	AnsiString newtmf;
	newtmf.sprintf("%s\\%s.tmf", Proj->OutDir, Proj->BaseFile);

	DeleteFile(newtmf.c_str());
	MoveFile(tmf.c_str(), newtmf.c_str());

	// Delete unused files.
	tmf.sprintf("%s\\%s.tmf", BmpPath(BM_ALPHA), Proj->BaseFile);
	DeleteFile(tmf.c_str());
}

//---------------------------------------------------------------------------
// Merging Alpha textures
//
void SCGenThread::MergeAlpha(void)
{
	AnsiString msg = _("Merging Alpha Textures...");
	SetStatusMsg(msg);

	// Create texture directory
	AnsiString texdir;
	texdir.sprintf("%s\\texture", Proj->OutDir);
	MkDir(texdir);

	// Build Targa file
	AnsiString bmpdir = BmpPath(BM_SUMMER);
	AnsiString alphadir = BmpPath(BM_ALPHA);

	AnsiString searchfile;
	searchfile.sprintf("%s\\*su.bmp", bmpdir);

	AnsiString alphafile, bmpfiles[BM_MAX], tgafiles[BM_MAX], pre;

	alphafile = "";
	
	TSearchRec rec;
	int ret = FindFirst(searchfile, faAnyFile & ~faDirectory, rec);
	int count = 1;
	while (ret == 0) {
		if (Terminated) return;

		// Show current status
		AnsiString st;
		st.sprintf("Merging textures : %d", count++);
		SetStatusMsg(st);

		// Get file name without extension.
		int len = rec.Name.Length();
		pre = rec.Name.SubString(1, len - 6);

		// Get alpha texture filename
		if (Proj->HasAlpha) {
			alphafile.sprintf("%s\\%ssu.bmp", alphadir, pre);
		}

		// Get bmp filenames
		for (int i = 0; i < BM_MAX; i++) {
			if (i == BM_ALPHA) continue;
			bmpfiles[i].sprintf("%s\\%s%s.bmp", bmpdir, pre, SeasonSuffix[i]);
			tgafiles[i].sprintf("%s\\%s%s.tga", texdir, pre, SeasonSuffix[i]);
		}

		// Execute
		MergeAlphaTextures(bmpfiles, alphafile, tgafiles, Proj->HasSeason);

		ret = FindNext(rec);
	}
	FindClose(rec);
}

//---------------------------------------------------------------------------
// Convert textures
//
void SCGenThread::ConvTex(void)
{
	AnsiString msg = _("Converting Textures...");
	SetStatusMsg(msg);

	AnsiString Imagetool;
	Imagetool.sprintf("%s\\imagetool.exe", OptionDlg->GetImagetoolPath());

	AnsiString cmdline;
	cmdline.sprintf("\"%s\" -DXT1 -e bmp -terrainphoto \"%s\\texture\\*.tga\"",
		Imagetool, Proj->OutDir);

	ExecCmd(cmdline, "imagetool.exe");
}
//---------------------------------------------------------------------------
// Generate BGL file
//
void SCGenThread::GenBgl(void)
{
	AnsiString msg = _("Generating BGL files...");
	SetStatusMsg(msg);

	AnsiString outdir = Proj->OutDir;
	AnsiString basefile = Proj->BaseFile;

	// Create scenery directory
	AnsiString scdir;
	scdir.sprintf("%s\\scenery", outdir);
	MkDir(scdir);

	// Get BGL filename
	AnsiString bgl;
	bgl.sprintf("%s\\scenery\\%s.bgl", outdir, basefile);

	// Get working filename
	AnsiString tmf, tmfc;
	tmf.sprintf("%s\\%s.tmf", outdir, basefile);
	tmfc.sprintf("%s\\%s-cmp.tmf", outdir, basefile);

	AnsiString sdkpath;
	sdkpath = OptionDlg->GetSDKPath();

	// Compress tmf file
	AnsiString cmdline;
	cmdline.sprintf("\"%s\\tmfcompress.exe\" \"%s\" \"%s\"", sdkpath, tmf, tmfc);
	ExecCmd(cmdline, "tmfcompress.exe");
	if (Terminated) return;

	// Convert BGL file
	cmdline.sprintf("\"%s\\tmf2bgl.exe\" \"%s\" \"%s\"", sdkpath, tmfc, bgl);
	ExecCmd(cmdline, "tmf2bgl.exe");
}

//---------------------------------------------------------------------------
// Set status message
//
void SCGenThread::SetStatusMsg(AnsiString msg)
{
	SCGenForm->StatusBar->SimpleText = msg;
}
