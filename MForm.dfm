object MainForm: TMainForm
  Left = 253
  Top = 122
  Caption = 'Photo Scenery Maker'
  ClientHeight = 461
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnMouseDown = OnMouseDown
  OnMouseMove = OnMouseMove
  OnMouseUp = OnMouseUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object StatusBar: TStatusBar
    Left = 0
    Top = 442
    Width = 628
    Height = 19
    Panels = <
      item
        Text = 'Ready'
        Width = 300
      end
      item
        Width = 120
      end
      item
        Width = 120
      end>
    SimpleText = 'Ready'
  end
  object ScrollBox: TScrollBox
    Left = 0
    Top = 0
    Width = 628
    Height = 442
    HorzScrollBar.Tracking = True
    VertScrollBar.Tracking = True
    Align = alClient
    TabOrder = 1
    object PaintBox: TPaintBox
      Left = 0
      Top = 0
      Width = 57
      Height = 49
      DragCursor = crDefault
      OnMouseDown = OnMouseDown
      OnMouseMove = OnMouseMove
      OnMouseUp = OnMouseUp
      OnPaint = PaintBoxPaint
    end
  end
  object MainMenu: TMainMenu
    Left = 480
    Top = 24
    object F1: TMenuItem
      Caption = 'File(&F)'
      object MenuNewPrj: TMenuItem
        Caption = 'New(&N)...'
        OnClick = MenuNewPrjClick
      end
      object MenuOpenPrj: TMenuItem
        Caption = 'Open(&O)...'
        OnClick = MenuOpenPrjClick
      end
      object MenuPrjSave: TMenuItem
        Caption = 'Save(&S)'
        OnClick = MenuPrjSaveClick
      end
      object MenuPrjSaveAs: TMenuItem
        Caption = 'Save As(&A)...'
        OnClick = MenuPrjSaveAsClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object MenuPrjProperty: TMenuItem
        Caption = 'Project Property(&P)...'
        OnClick = MenuPrjPropertyClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object MenuQuit: TMenuItem
        Caption = 'Quit(&Q)'
        OnClick = MenuQuitClick
      end
    end
    object MenuView: TMenuItem
      Caption = 'Vew(&V)'
      object MenuViewSummer: TMenuItem
        Caption = 'Summer'
        Checked = True
        OnClick = MenuViewSummerClick
      end
      object MenuViewSpring: TMenuItem
        Caption = 'Spring'
        OnClick = MenuViewSpringClick
      end
      object MenuViewFall: TMenuItem
        Caption = 'Fall'
        OnClick = MenuViewFallClick
      end
      object MenuViewWinter: TMenuItem
        Caption = 'Winter'
        OnClick = MenuViewWinterClick
      end
      object MenuViewHSWinter: TMenuItem
        Caption = 'Hard Winter'
        OnClick = MenuViewHSWinterClick
      end
      object MenuViewLightmap: TMenuItem
        Caption = 'Lightmap'
        OnClick = MenuViewLightmapClick
      end
      object MenuViewAlpha: TMenuItem
        Caption = 'Water(Alpha)'
        OnClick = MenuViewAlphaClick
      end
    end
    object MenuCalibration: TMenuItem
      Caption = 'Calibration(&C)'
      object SetCPoint: TMenuItem
        Caption = '2 Point Calibration(&P)...'
        OnClick = SetCPointClick
      end
      object MenuBitmapBoundary: TMenuItem
        Caption = 'Bitmap Boundary'
        object MenuTop: TMenuItem
          Caption = 'Top(&T)'
          OnClick = MenuTopClick
        end
        object MenuBottom: TMenuItem
          Caption = 'Bottom(&B)'
          OnClick = MenuBottomClick
        end
        object MenuLeft: TMenuItem
          Caption = 'Left(&L)'
          OnClick = MenuLeftClick
        end
        object MenuRight: TMenuItem
          Caption = 'Right(&R)'
          OnClick = MenuRightClick
        end
      end
      object ExecCorrection: TMenuItem
        Caption = 'Calculate optimal bitmap size (&O)'
        OnClick = ExecCorrectionClick
      end
    end
    object MenuSCGen: TMenuItem
      Caption = 'Scenery Generation(&S)'
      OnClick = MenuSCGenClick
    end
    object MenuOption: TMenuItem
      Caption = 'Option (&O)'
      OnClick = MenuOptionClick
    end
    object H1: TMenuItem
      Caption = 'Help(&H)'
      object MenuTutorial: TMenuItem
        Caption = 'Tutorial(&T)...'
        OnClick = MenuTutorialClick
      end
      object MenuManual: TMenuItem
        Caption = 'Manual(&M)...'
        OnClick = MenuManualClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object MenuAbout: TMenuItem
        Caption = 'About(&A)...'
        OnClick = MenuAboutClick
      end
    end
  end
  object OpenPrjDialog: TOpenDialog
    DefaultExt = 'psm'
    Filter = 'Project files (*.psm)|*.psm|All files (*.*)|*.*'
    Left = 408
    Top = 16
  end
  object SavePrjDialog: TSaveDialog
    DefaultExt = 'psm'
    Filter = 'Project files (*.psm)|*.psm|All files (*.*)|*.*'
    Left = 440
    Top = 24
  end
  object Timer: TTimer
    Enabled = False
    Interval = 20
    OnTimer = OnTimer
    Left = 520
    Top = 24
  end
end
