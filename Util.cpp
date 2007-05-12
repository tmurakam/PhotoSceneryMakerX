/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * Util.cpp : utility functions
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

#define NO_WIN32_LEAN_AND_MEAN

#include <vcl.h>
#pragma hdrstop

#include <shlobj.h>

#include "Util.h"

//---------------------------------------------------------------------------

//#pragma package(smart_init)

static int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
    if(uMsg==BFFM_INITIALIZED){
	SendMessage(hwnd,BFFM_SETSELECTION,(WPARAM)TRUE,lpData);
    }
    return 0;
}


AnsiString SelectFolder(
	AnsiString InitFolder,	// Initial Folder
	HWND owner)              // Owner window handle
{
  AnsiString s;
  IMalloc *m; // Task allocator

  if(SUCCEEDED(SHGetMalloc(&m)))
  {
    BROWSEINFO b;
    char path[MAX_PATH];

    b.hwndOwner= owner; // Owner handle
    b.pidlRoot= NULL;   // Root
    b.pszDisplayName= path; // Display name buffer
    b.lpszTitle= "Select folder"; // Message
    b.ulFlags= BIF_RETURNONLYFSDIRS; // folder only
    b.lpfn= BrowseCallbackProc; // callback func
    b.lParam= (LPARAM)InitFolder.c_str();  // Callback value
    b.iImage= 0;  // image index

    // Show dialog
    LPITEMIDLIST id=SHBrowseForFolder(&b);
    if(id)
    {
      // Get path
      SHGetPathFromIDList(id, path);
      s= path;
      m->Free(id);
    }
    m->Release();
  }
  return s;
}
