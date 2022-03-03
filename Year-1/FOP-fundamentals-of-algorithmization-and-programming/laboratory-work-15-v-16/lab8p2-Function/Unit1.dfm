object Form1: TForm1
  Left = 1092
  Top = 183
  Width = 371
  Height = 377
  Caption = 'Function'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = -8
    Top = 0
    Width = 361
    Height = 337
    Picture.Data = {}
  end
  object Panel1: TPanel
    Left = 0
    Top = 48
    Width = 353
    Height = 217
    Color = clWhite
    TabOrder = 0
    object Image2: TImage
      Left = 24
      Top = 32
      Width = 305
      Height = 177
    end
    object Label1: TLabel
      Left = 24
      Top = 8
      Width = 315
      Height = 19
      Caption = 'func =(1/10)*(x^3)+x^2-10*sin(x)-8 '
      Color = clWhite
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Consolas'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
  end
  object Button1: TButton
    Left = 200
    Top = 296
    Width = 105
    Height = 25
    Caption = 'Show function'
    TabOrder = 1
    OnClick = Button1Click
  end
end
