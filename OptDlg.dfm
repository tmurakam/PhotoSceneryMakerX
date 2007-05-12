object OptionDlg: TOptionDlg
  Left = 302
  Top = 252
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 128
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
    Width = 83
    Height = 14
    Caption = 'FSX SDK Folder'
  end
  object Label3: TLabel
    Left = 12
    Top = 55
    Width = 53
    Height = 14
    Caption = 'Language'
  end
  object ButtonOK: TButton
    Left = 160
    Top = 80
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
    OnClick = ButtonOKClick
  end
  object Button2: TButton
    Left = 256
    Top = 80
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
    Text = 
      'C:\Program Files\Microsoft Games\Microsoft Flight Simulator X SD' +
      'K\SDK\Environment Kit\Terrain SDK'
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
  object ListLang: TComboBox
    Left = 128
    Top = 52
    Width = 129
    Height = 22
    Style = csDropDownList
    ItemHeight = 14
    TabOrder = 4
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'exe'
    Left = 344
    Top = 56
  end
end
