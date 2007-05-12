/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * MForm.h : Main form
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

#ifndef MFormH
#define MFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

#include "Project.h"
#include "Bitmap.h"
#include <ToolWin.hpp>

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE managed components
        TMainMenu *MainMenu;
        TMenuItem *F1;
	TMenuItem *MenuQuit;
        TStatusBar *StatusBar;
	TMenuItem *MenuCalibration;
        TMenuItem *SetCPoint;
	TScrollBox *ScrollBox;
	TMenuItem *ExecCorrection;
	TMenuItem *MenuOption;
	TMenuItem *H1;
	TMenuItem *MenuAbout;
	TMenuItem *MenuSCGen;
	TMenuItem *MenuOpenPrj;
	TMenuItem *MenuPrjSaveAs;
	TMenuItem *MenuPrjSave;
	TMenuItem *N5;
	TOpenDialog *OpenPrjDialog;
	TSaveDialog *SavePrjDialog;
	TMenuItem *MenuPrjProperty;
	TMenuItem *N1;
	TMenuItem *MenuNewPrj;
	TMenuItem *MenuView;
	TMenuItem *MenuViewSummer;
	TMenuItem *MenuViewSpring;
	TMenuItem *MenuViewFall;
	TMenuItem *MenuViewWinter;
	TMenuItem *MenuViewHSWinter;
	TMenuItem *MenuViewLightmap;
	TMenuItem *MenuViewAlpha;
	TPaintBox *PaintBox;
	TTimer *Timer;
	TMenuItem *MenuManual;
	TMenuItem *MenuTutorial;
	TMenuItem *N2;
	TMenuItem *MenuBitmapBoundary;
	TMenuItem *MenuTop;
	TMenuItem *MenuBottom;
	TMenuItem *MenuRight;
	TMenuItem *MenuLeft;

	void __fastcall SetCPointClick(TObject *Sender);
	void __fastcall OnMouseDown(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y);
	void __fastcall OnMouseMove(TObject *Sender, TShiftState Shift, int X,
	  int Y);
	void __fastcall OnMouseUp(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y);
	void __fastcall ExecCorrectionClick(TObject *Sender);
	void __fastcall MenuQuitClick(TObject *Sender);
	void __fastcall MenuOptionClick(TObject *Sender);
	void __fastcall MenuAboutClick(TObject *Sender);
	void __fastcall MenuOpenPrjClick(TObject *Sender);
	void __fastcall MenuPrjSaveClick(TObject *Sender);
	void __fastcall MenuPrjSaveAsClick(TObject *Sender);
	void __fastcall MenuSCGenClick(TObject *Sender);
	void __fastcall MenuPrjPropertyClick(TObject *Sender);
	void __fastcall MenuNewPrjClick(TObject *Sender);
	void __fastcall MenuViewSummerClick(TObject *Sender);
	void __fastcall MenuViewSpringClick(TObject *Sender);
	void __fastcall MenuViewFallClick(TObject *Sender);
	void __fastcall MenuViewWinterClick(TObject *Sender);
	void __fastcall MenuViewHSWinterClick(TObject *Sender);
	void __fastcall MenuViewLightmapClick(TObject *Sender);
	void __fastcall MenuViewAlphaClick(TObject *Sender);
	void __fastcall PaintBoxPaint(TObject *Sender);
	void __fastcall OnTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MenuManualClick(TObject *Sender);
	void __fastcall MenuTutorialClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall MenuTopClick(TObject *Sender);
	void __fastcall MenuBottomClick(TObject *Sender);
	void __fastcall MenuRightClick(TObject *Sender);
	void __fastcall MenuLeftClick(TObject *Sender);

private:	// User decl.
	bool isCpSpecifing;
        int CpSpecifing;
#define	CP_0		0
#define	CP_1		1
#define	CP_BOUND_TOP	2	
#define	CP_BOUND_BOTTOM	3
#define	CP_BOUND_LEFT	4
#define	CP_BOUND_RIGHT	5

        ControlPoint cp[2];

	PSMProject	*proj;

	bool isDragging;
	int DragX, DragY;
	int MoveX, MoveY;

	//Graphics::TBitmap	*bitmap;
	TBitmap2	*bitmap;	
	int curBmpIdx;
        bool isTranslated;

	bool CheckSave(void);
	
	void CalcParameters(void);
//	void Gauss(double k[3][4]);

	void ShowHtml(AnsiString prefix);

public:		// User decl.
        __fastcall TMainForm(TComponent* Owner);
	void UpdateMenu(void);
	void SetProgress(int perc);
	void TranslateAllForms(void);

protected:
	void StartCpSpecify(int cp);
	void ChangeBmp(int bmpidx, bool reload = false);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
