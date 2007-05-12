object PrjForm: TPrjForm
  Left = 327
  Top = 178
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Project Property'
  ClientHeight = 441
  ClientWidth = 492
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 492
    Height = 405
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Bitmaps'
      object Label1: TLabel
        Left = 16
        Top = 36
        Width = 45
        Height = 14
        Caption = 'Summer'
      end
      object Label2: TLabel
        Left = 16
        Top = 68
        Width = 34
        Height = 14
        Caption = 'Spring'
      end
      object Label3: TLabel
        Left = 16
        Top = 100
        Width = 16
        Height = 14
        Caption = 'Fall'
      end
      object Label4: TLabel
        Left = 16
        Top = 132
        Width = 37
        Height = 14
        Caption = 'Winter'
      end
      object Label5: TLabel
        Left = 16
        Top = 164
        Width = 71
        Height = 14
        Caption = 'Harsh Winter'
      end
      object Label6: TLabel
        Left = 16
        Top = 196
        Width = 50
        Height = 14
        Caption = 'Lightmap'
      end
      object Label7: TLabel
        Left = 16
        Top = 228
        Width = 72
        Height = 14
        Caption = 'Water(alpha)'
      end
      object EditBmpSummer: TEdit
        Left = 104
        Top = 32
        Width = 329
        Height = 22
        TabOrder = 1
      end
      object EditBmpSpring: TEdit
        Left = 104
        Top = 64
        Width = 329
        Height = 22
        TabOrder = 3
      end
      object CheckSeason: TCheckBox
        Left = 16
        Top = 8
        Width = 121
        Height = 17
        Caption = 'Support Seasons'
        TabOrder = 0
        OnClick = CheckSeasonClick
      end
      object EditBmpFall: TEdit
        Left = 104
        Top = 96
        Width = 329
        Height = 22
        TabOrder = 5
      end
      object EditBmpWinter: TEdit
        Left = 104
        Top = 128
        Width = 329
        Height = 22
        TabOrder = 7
      end
      object EditBmpHSWinter: TEdit
        Left = 104
        Top = 160
        Width = 329
        Height = 22
        TabOrder = 9
      end
      object EditBmpLightmap: TEdit
        Left = 104
        Top = 192
        Width = 329
        Height = 22
        TabOrder = 11
      end
      object EditBmpAlpha: TEdit
        Left = 104
        Top = 224
        Width = 329
        Height = 22
        TabOrder = 13
      end
      object ButtonRefBmpSummer: TButton
        Left = 440
        Top = 32
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 2
        OnClick = ButtonRefBmpSummerClick
      end
      object ButtonRefBmpSpring: TButton
        Left = 440
        Top = 64
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 4
        OnClick = ButtonRefBmpSpringClick
      end
      object ButtonRefBmpFall: TButton
        Left = 440
        Top = 96
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 6
        OnClick = ButtonRefBmpFallClick
      end
      object ButtonRefBmpWinter: TButton
        Left = 440
        Top = 128
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 8
        OnClick = ButtonRefBmpWinterClick
      end
      object ButtonRefBmpHSWinter: TButton
        Left = 440
        Top = 160
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 10
        OnClick = ButtonRefBmpHSWinterClick
      end
      object ButtonRefBmpLightmap: TButton
        Left = 440
        Top = 192
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 12
        OnClick = ButtonRefBmpLightmapClick
      end
      object ButtonRefBmpAlpha: TButton
        Left = 440
        Top = 224
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 14
        OnClick = ButtonRefBmpAlphaClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Coordinates'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 8
        Top = 8
        Width = 449
        Height = 137
        Caption = 'Bitmap Boundary'
        TabOrder = 0
        object Label10: TLabel
          Left = 152
          Top = 16
          Width = 31
          Height = 14
          Caption = 'North'
        end
        object Label11: TLabel
          Left = 152
          Top = 84
          Width = 33
          Height = 14
          Caption = 'South'
        end
        object Label12: TLabel
          Left = 16
          Top = 52
          Width = 29
          Height = 14
          Caption = 'West'
        end
        object Label13: TLabel
          Left = 280
          Top = 52
          Width = 23
          Height = 14
          Caption = 'East'
        end
        object EditN: TEdit
          Left = 152
          Top = 32
          Width = 121
          Height = 22
          TabOrder = 0
          OnExit = OnCoordEditExit
        end
        object EditS: TEdit
          Left = 152
          Top = 101
          Width = 121
          Height = 22
          TabOrder = 3
          OnExit = OnCoordEditExit
        end
        object EditW: TEdit
          Left = 16
          Top = 69
          Width = 121
          Height = 22
          TabOrder = 1
          OnExit = OnCoordEditExit
        end
        object EditE: TEdit
          Left = 280
          Top = 69
          Width = 121
          Height = 22
          TabOrder = 2
          OnExit = OnCoordEditExit
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 152
        Width = 449
        Height = 73
        Caption = 'Resolution'
        TabOrder = 1
        object Label14: TLabel
          Left = 16
          Top = 20
          Width = 184
          Height = 14
          Caption = 'CellXDimensionDeg (second/pixel)'
        end
        object Label15: TLabel
          Left = 16
          Top = 44
          Width = 185
          Height = 14
          Caption = 'CellYDimensionDeg (second/pixel)'
        end
        object EditXres: TEdit
          Left = 216
          Top = 16
          Width = 209
          Height = 22
          TabOrder = 0
          OnExit = OnResEditExit
        end
        object EditYres: TEdit
          Left = 216
          Top = 40
          Width = 209
          Height = 22
          TabOrder = 1
          OnExit = OnResEditExit
        end
      end
      object GroupBoxInfo: TGroupBox
        Left = 8
        Top = 240
        Width = 449
        Height = 129
        Caption = 'Info'
        TabOrder = 2
        object Label16: TLabel
          Left = 16
          Top = 77
          Width = 74
          Height = 14
          Caption = 'Bitmap Width'
        end
        object Label17: TLabel
          Left = 16
          Top = 101
          Width = 77
          Height = 14
          Caption = 'Bitmap Height'
        end
        object Label18: TLabel
          Left = 16
          Top = 21
          Width = 117
          Height = 14
          Caption = 'X resolution (m/pixel)'
        end
        object Label19: TLabel
          Left = 16
          Top = 45
          Width = 118
          Height = 14
          Caption = 'Y resolution (m/pixel)'
        end
        object EditYres2: TEdit
          Left = 144
          Top = 41
          Width = 121
          Height = 22
          Enabled = False
          TabOrder = 0
        end
        object EditXres2: TEdit
          Left = 144
          Top = 17
          Width = 121
          Height = 22
          Enabled = False
          TabOrder = 1
        end
        object EditWidth: TEdit
          Left = 120
          Top = 73
          Width = 89
          Height = 22
          Enabled = False
          TabOrder = 2
        end
        object EditHeight: TEdit
          Left = 120
          Top = 97
          Width = 89
          Height = 22
          Enabled = False
          TabOrder = 3
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Output'
      ImageIndex = 2
      object GroupFileOutput: TGroupBox
        Left = 8
        Top = 8
        Width = 457
        Height = 105
        Caption = 'File output'
        TabOrder = 0
        object Label9: TLabel
          Left = 16
          Top = 68
          Width = 81
          Height = 14
          Caption = 'Base File Name'
        end
        object Label8: TLabel
          Left = 16
          Top = 30
          Width = 77
          Height = 14
          Caption = 'Output Folder'
        end
        object ButtonRefOutDir: TButton
          Left = 416
          Top = 24
          Width = 25
          Height = 25
          Caption = '...'
          TabOrder = 1
          OnClick = ButtonRefOutDirClick
        end
        object EditBaseFile: TEdit
          Left = 120
          Top = 64
          Width = 121
          Height = 22
          TabOrder = 2
        end
        object EditOutDir: TEdit
          Left = 120
          Top = 26
          Width = 281
          Height = 22
          TabOrder = 0
        end
      end
      object GroupBitmapBoundary: TGroupBox
        Left = 8
        Top = 128
        Width = 321
        Height = 161
        Caption = 'Bitmap boundary'
        TabOrder = 1
        object Label20: TLabel
          Left = 120
          Top = 40
          Width = 22
          Height = 14
          Caption = 'Top'
        end
        object Label21: TLabel
          Left = 24
          Top = 72
          Width = 22
          Height = 14
          Caption = 'Left'
        end
        object Label22: TLabel
          Left = 208
          Top = 72
          Width = 28
          Height = 14
          Caption = 'Right'
        end
        object Label23: TLabel
          Left = 112
          Top = 104
          Width = 41
          Height = 14
          Caption = 'Bottom'
        end
        object CheckUseWhole: TCheckBox
          Left = 16
          Top = 16
          Width = 153
          Height = 17
          Caption = 'Use whole bitmap'
          TabOrder = 0
        end
        object EditBoundTop: TEdit
          Left = 112
          Top = 56
          Width = 81
          Height = 22
          TabOrder = 1
        end
        object EditBoundLeft: TEdit
          Left = 24
          Top = 88
          Width = 81
          Height = 22
          TabOrder = 2
        end
        object EditBoundRight: TEdit
          Left = 200
          Top = 88
          Width = 81
          Height = 22
          TabOrder = 3
        end
        object EditBoundBottom: TEdit
          Left = 112
          Top = 120
          Width = 81
          Height = 22
          TabOrder = 4
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 405
    Width = 492
    Height = 36
    Align = alBottom
    TabOrder = 1
    object Button1: TButton
      Left = 280
      Top = 8
      Width = 75
      Height = 25
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 376
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'bmp'
    Filter = 'Bitmap File (*.bmp)|*.bmp|All Files (*.*)|*.*'
    Left = 8
    Top = 408
  end
end
