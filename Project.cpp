/*
 * Photo Scenery Maker X
 *
 * Copyright (C) 2003-2007 Takuya Murakami
 *
 * Project.cpp : Project document class
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

#include "Project.h"

//---------------------------------------------------------------------------
PSMProject::PSMProject()
{
	modified = false;

	for (int i = 0; i < BM_MAX; i++) {
		bmpInfo[i].filename = "";
                bmpInfo[i].variation = -1;
        }

        lod = -1;	// default
}

int PSMProject::numBmp(void)
{
	int nbmp = 0;
        for (int i=0; i <= BM_MAX; i++) {
        	if (bmpInfo[i].isValid()) {
                	nbmp++;
                }
        }
        return nbmp;
}

int PSMProject::lwmaskIdx(void)
{
        for (int i=0; i <= BM_MAX; i++) {
                if (bmpInfo[i].isValid() &&
                     bmpInfo[i].variation & BV_LWMASK) {
                      return i;
                }
        }
        return -1;
}

void PSMProject::LoadFromFile(AnsiString prjfile)
{
	prjpath = prjfile;

	TIniFile *ini = new TIniFile(prjpath);

	for (int i = 0; i < BM_MAX; i++) {
        	AnsiString key;
                key.sprintf("Bitmap%d", i);
                bmpInfo[i].filename = ini->ReadString("Source", key, "");
                key.sprintf("BitmapVariation%d", i);
                bmpInfo[i].variation = ini->ReadInteger("Source", key, BV_ALL);
	}

        // For backward compatibility
        if (bmpInfo[0].filename.IsEmpty()) {
		bmpInfo[0].filename = ini->ReadString("Source", "BMPSummer", "");
	}

	trans.Width  = ini->ReadInteger("Source", "Width",  -1);
	trans.Height = ini->ReadInteger("Source", "Height", -1);

	trans.Boundary.useWhole = ini->ReadBool("Source", "UseWhole", true);
	trans.Boundary.top = ini->ReadInteger("Source", "Top", 0);
	trans.Boundary.left = ini->ReadInteger("Source", "Left", 0);
	trans.Boundary.right = ini->ReadInteger("Source", "Right", trans.Width - 1);
	trans.Boundary.bottom = ini->ReadInteger("Source", "Bottom", trans.Height - 1);

	LatLon base;
	base.lat.deg = ini->ReadFloat("Source", "Latitude", 0);
	base.lon.deg = ini->ReadFloat("Source", "Longitude", 0);
	trans.Base = base;

	XYparam res;
	res.x = ini->ReadFloat("Source", "Xresolution", 0.0001);
	res.y = ini->ReadFloat("Source", "Yresolution", 0.0001);
	trans.Resolution = res;

	outdir   = ini->ReadString("Output", "Directory", "");
	basefile = ini->ReadString("Output", "BaseFile", "");
        lod = ini->ReadInteger("Output", "LOD", -1);

	delete(ini);

	modified = false;
        Packing();
}

bool PSMProject::SaveToFile(AnsiString prjfile)
{
	if (!prjfile.IsEmpty()) {
		prjpath = prjfile;
	}
	if (prjpath.IsEmpty()) {
		return false;	// filename must be specified.
	}

	TIniFile *ini = new TIniFile(prjpath);
	for (int i = 0; i < BM_MAX; i++) {
        	AnsiString key;
                key.sprintf("Bitmap%d", i);
		ini->WriteString("Source", key, bmpInfo[i].filename);
                key.sprintf("BitmapVariation%d", i);
                ini->WriteInteger("Source", key, bmpInfo[i].variation);

	}

	ini->WriteInteger("Source", "Width", trans.Width);
	ini->WriteInteger("Source", "Height", trans.Height);

	ini->WriteBool("Source", "UseWhole", trans.Boundary.useWhole);
	ini->WriteInteger("Source", "Top", trans.Boundary.top);
	ini->WriteInteger("Source", "Left", trans.Boundary.left);
	ini->WriteInteger("Source", "Right", trans.Boundary.right);
	ini->WriteInteger("Source", "Bottom", trans.Boundary.bottom);

	LatLon base = trans.Base;
	ini->WriteFloat("Source", "Latitude", base.lat.deg);
	ini->WriteFloat("Source", "Longitude", base.lon.deg);

	XYparam res = trans.Resolution;
	ini->WriteFloat("Source", "Xresolution", res.x);
	ini->WriteFloat("Source", "Yresolution", res.y);

	ini->WriteString("Output", "Directory", outdir);
	ini->WriteString("Output", "BaseFile",  basefile);
        ini->WriteInteger("Output", "LOD", lod);

	delete(ini);

	modified = false;

	return true;
}

void PSMProject::Packing(void)
{
	for (int i=0; i < BM_MAX - 1; i++) {
		bmpInfo[i].filename = bmpInfo[i].filename.Trim();
        	if (!bmpInfo[i].isValid()) {
                      for (int j = i; j < BM_MAX - 1; j++) {
                      	bmpInfo[j] = bmpInfo[j+1];
                      }
                }
        }
}
#pragma package(smart_init)
