object LatLonDlg: TLatLonDlg
  Left = 586
  Top = 368
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Lat/Lon'
  ClientHeight = 124
  ClientWidth = 228
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
  object Label1: TLabel
    Left = 16
    Top = 20
    Width = 45
    Height = 14
    Caption = 'Latitude'
  end
  object Label2: TLabel
    Left = 16
    Top = 52
    Width = 55
    Height = 14
    Caption = 'Longitude'
  end
  object LatEdit: TEdit
    Left = 80
    Top = 16
    Width = 121
    Height = 22
    TabOrder = 0
  end
  object LonEdit: TEdit
    Left = 80
    Top = 48
    Width = 121
    Height = 22
    TabOrder = 1
  end
  object Button1: TButton
    Left = 32
    Top = 88
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
  end
  object Button2: TButton
    Left = 128
    Top = 88
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
