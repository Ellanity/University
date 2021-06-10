object Form1: TForm1
  Left = 978
  Top = 191
  BorderStyle = bsDialog
  Caption = 'Ping Pong'
  ClientHeight = 432
  ClientWidth = 500
  Color = cl3DLight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 344
    Top = 312
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Label4: TLabel
    Left = 96
    Top = 336
    Width = 111
    Height = 20
    Caption = 'Mode: 2 players'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 96
    Top = 368
    Width = 18
    Height = 20
    Caption = '10'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 500
    Height = 300
    Color = clWindowFrame
    TabOrder = 0
    object Shape4: TShape
      Left = 249
      Top = 0
      Width = 2
      Height = 300
      Brush.Color = cl3DDkShadow
    end
    object Label2: TLabel
      Left = 88
      Top = 80
      Width = 66
      Height = 140
      Caption = '0'
      Color = clWindowFrame
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clGray
      Font.Height = -120
      Font.Name = 'Consolas'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Label3: TLabel
      Left = 304
      Top = 80
      Width = 66
      Height = 140
      Caption = '0'
      Color = clWindowFrame
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clGray
      Font.Height = -120
      Font.Name = 'Consolas'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Shape3: TShape
      Left = 240
      Top = 140
      Width = 20
      Height = 20
      Brush.Color = clCream
      Shape = stCircle
    end
    object Shape5: TShape
      Left = 0
      Top = 0
      Width = 40
      Height = 300
      Brush.Color = clGray
    end
    object Shape1: TShape
      Left = 20
      Top = 100
      Width = 20
      Height = 100
      Brush.Color = clActiveCaption
    end
    object Shape6: TShape
      Left = 460
      Top = 0
      Width = 40
      Height = 300
      Brush.Color = clGray
    end
    object Shape2: TShape
      Left = 460
      Top = 100
      Width = 20
      Height = 100
      Brush.Color = clMoneyGreen
    end
  end
  object Button1: TButton
    Left = 8
    Top = 304
    Width = 105
    Height = 25
    Caption = 'Start'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 120
    Top = 304
    Width = 105
    Height = 25
    Caption = 'Stop'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 232
    Top = 304
    Width = 264
    Height = 121
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'First Player:'
      'UP:   W           DOWN:   S'
      ''
      'Second Player:'
      'UP:   P            DOWN:   L ')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object Button3: TButton
    Left = 8
    Top = 336
    Width = 81
    Height = 25
    Caption = 'Change mode'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 8
    Top = 368
    Width = 81
    Height = 25
    Caption = 'Level of hard'
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 8
    Top = 400
    Width = 217
    Height = 25
    Caption = 'Clear'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = Button5Click
  end
  object BitBtn1: TBitBtn
    Left = 200
    Top = 368
    Width = 25
    Height = 25
    TabOrder = 7
    OnClick = BitBtn1Click
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333FFFFF3333333333F797F3333333333F737373FF333333BFB999BFB
      33333337737773773F3333BFBF797FBFB33333733337333373F33BFBFBFBFBFB
      FB3337F33333F33337F33FBFBFB9BFBFBF3337333337F333373FFBFBFBF97BFB
      FBF37F333337FF33337FBFBFBFB99FBFBFB37F3333377FF3337FFBFBFBFB99FB
      FBF37F33333377FF337FBFBF77BF799FBFB37F333FF3377F337FFBFB99FB799B
      FBF373F377F3377F33733FBF997F799FBF3337F377FFF77337F33BFBF99999FB
      FB33373F37777733373333BFBF999FBFB3333373FF77733F7333333BFBFBFBFB
      3333333773FFFF77333333333FBFBF3333333333377777333333}
    NumGlyphs = 2
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 5
    OnTimer = Timer1Timer
    Left = 464
    Top = 264
  end
end
