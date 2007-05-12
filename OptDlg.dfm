object OptionDlg: TOptionDlg
  Left = 302
  Top = 252
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 189
  ClientWidth = 509
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object Label1: TLabel
    Left = 12
    Top = 16
    Width = 99
    Height = 14
    Caption = 'Terrain SDK folder'
  end
  object Label2: TLabel
    Left = 12
    Top = 96
    Width = 90
    Height = 14
    Caption = 'Imagetool folder'
  end
  object Label3: TLabel
    Left = 12
    Top = 128
    Width = 53
    Height = 14
    Caption = 'Language'
  end
  object Label4: TLabel
    Left = 128
    Top = 40
    Width = 369
    Height = 49
    Caption = 
      'Note: You MUST use FS2000 Terrain SDK. Custom Terrain SDK has so' +
      'me bugs, so it does not work properly!!!'
    WordWrap = True
  end
  object ButtonOK: TButton
    Left = 160
    Top = 152
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
    OnClick = ButtonOKClick
  end
  object Button2: TButton
    Left = 256
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object EditSDKPath: TEdit
    Left = 128
    Top = 12
    Width = 329
    Height = 22
    TabOrder = 2
  end
  object ButtonBrowseSDK: TButton
    Left = 464
    Top = 10
    Width = 25
    Height = 25
    Caption = '...'
    TabOrder = 3
    OnClick = ButtonBrowseSDKClick
  end
  object EditImagetoolPath: TEdit
    Left = 128
    Top = 92
    Width = 329
    Height = 22
    TabOrder = 4
  end
  object ButtonBrowserImagetool: TButton
    Left = 464
    Top = 90
    Width = 25
    Height = 25
    Caption = '...'
    TabOrder = 5
    OnClick = ButtonBrowserImagetoolClick
  end
  object ListLang: TComboBox
    Left = 128
    Top = 124
    Width = 129
    Height = 22
    Style = csDropDownList
    ItemHeight = 14
    TabOrder = 6
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'exe'
    Left = 344
    Top = 128
  end
end
