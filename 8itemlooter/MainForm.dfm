object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'melih_+8looter'
  ClientHeight = 689
  ClientWidth = 207
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object shpbot: TShape
    Left = 126
    Top = 6
    Width = 12
    Height = 12
    Brush.Color = clRed
  end
  object chTop: TCheckBox
    Left = 55
    Top = 5
    Width = 65
    Height = 17
    Caption = 'ustte tut'
    TabOrder = 0
    OnClick = chTopClick
  end
  object btnOff: TButton
    Left = 23
    Top = 1
    Width = 26
    Height = 25
    Caption = 'X'
    TabOrder = 1
    OnClick = btnOffClick
  end
  object btnMin: TButton
    Left = 1
    Top = 1
    Width = 25
    Height = 25
    Caption = '-'
    TabOrder = 2
    OnClick = btnMinClick
  end
  object PageControl1: TPageControl
    Left = 1
    Top = 28
    Width = 209
    Height = 661
    ActivePage = TabSheet1
    Style = tsButtons
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'bot'
      object grpcast: TGroupBox
        Left = -3
        Top = 3
        Width = 97
        Height = 73
        Caption = 'skill'
        TabOrder = 0
        object oparchery: TRadioButton
          Left = 3
          Top = 16
          Width = 62
          Height = 17
          Caption = 'archery'
          TabOrder = 0
          OnClick = oparcheryClick
        end
        object opperfect: TRadioButton
          Left = 3
          Top = 32
          Width = 86
          Height = 17
          Caption = 'perfect shot'
          TabOrder = 1
          OnClick = opperfectClick
        end
        object oparc: TRadioButton
          Left = 3
          Top = 47
          Width = 62
          Height = 17
          Caption = 'arc shot'
          Checked = True
          TabOrder = 2
          TabStop = True
          OnClick = oparcClick
        end
      end
      object grpkill: TGroupBox
        Left = -3
        Top = 82
        Width = 193
        Height = 130
        Caption = 'kes'
        TabOrder = 1
        object opall: TRadioButton
          Left = 8
          Top = 16
          Width = 57
          Height = 17
          Caption = 'hepsi'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = opallClick
        end
        object oplist: TRadioButton
          Left = 8
          Top = 32
          Width = 81
          Height = 17
          Caption = 'listeden se'#231':'
          TabOrder = 1
          OnClick = oplistClick
        end
        object lstmob: TListBox
          Left = 8
          Top = 55
          Width = 113
          Height = 45
          ItemHeight = 13
          Items.Strings = (
            'Werewolf'
            'Lycan')
          TabOrder = 2
        end
        object txtmob: TEdit
          Left = 8
          Top = 100
          Width = 81
          Height = 21
          TabOrder = 3
        end
        object btnadd: TButton
          Left = 144
          Top = 100
          Width = 33
          Height = 21
          Caption = '^ekle'
          TabOrder = 4
          OnClick = btnaddClick
        end
        object btnclear: TButton
          Left = 102
          Top = 57
          Width = 17
          Height = 17
          Caption = 'X'
          TabOrder = 5
          OnClick = btnclearClick
        end
        object btngetmob: TButton
          Left = 95
          Top = 100
          Width = 42
          Height = 21
          Caption = '<AL'
          TabOrder = 6
          OnClick = btngetmobClick
        end
        object chlf: TCheckBox
          Left = 115
          Top = 16
          Width = 65
          Height = 17
          Caption = 'light feet'
          TabOrder = 7
          OnClick = chlfClick
        end
        object chsprint: TCheckBox
          Left = 115
          Top = 32
          Width = 57
          Height = 17
          Caption = 'sprint'
          TabOrder = 8
          OnClick = chsprintClick
        end
        object chwolf: TCheckBox
          Left = 127
          Top = 55
          Width = 49
          Height = 17
          Caption = 'wolf'
          TabOrder = 9
          OnClick = chwolfClick
        end
        object chwh: TCheckBox
          Left = 127
          Top = 77
          Width = 57
          Height = 17
          Caption = 'wallhack'
          Checked = True
          State = cbChecked
          TabOrder = 10
          OnClick = chwhClick
        end
      end
      object grploot: TGroupBox
        Left = 101
        Top = 3
        Width = 89
        Height = 73
        Caption = 'topla'
        TabOrder = 2
        object chloot6: TCheckBox
          Left = 3
          Top = 16
          Width = 54
          Height = 17
          Caption = '+6 item'
          TabOrder = 0
          OnClick = chloot6Click
        end
        object chloot7: TCheckBox
          Left = 3
          Top = 32
          Width = 65
          Height = 17
          Caption = '+7 item'
          TabOrder = 1
          OnClick = chloot7Click
        end
        object chloot8: TCheckBox
          Left = 3
          Top = 47
          Width = 73
          Height = 17
          Caption = '+8 item'
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = chloot8Click
        end
      end
      object grpsupply: TGroupBox
        Left = -3
        Top = 218
        Width = 193
        Height = 282
        Caption = 'tamir-depo'
        TabOrder = 3
        object Label5: TLabel
          Left = 12
          Top = 85
          Width = 33
          Height = 13
          Caption = 'banka:'
        end
        object Label6: TLabel
          Left = 66
          Top = 85
          Width = 44
          Height = 13
          Caption = 'sundries:'
        end
        object Label1: TLabel
          Left = 26
          Top = 252
          Width = 164
          Height = 13
          Caption = '. kutudan itibaren bankaya depola'
        end
        object Label4: TLabel
          Left = 122
          Top = 85
          Width = 20
          Height = 13
          Caption = 'pot:'
        end
        object txtinn: TEdit
          Left = 56
          Top = 18
          Width = 134
          Height = 21
          TabOrder = 0
          Text = '[FolkVillage Captain] Kronil'
        end
        object btngetinn: TButton
          Left = 5
          Top = 18
          Width = 45
          Height = 15
          Caption = 'inn al>'
          TabOrder = 1
          OnClick = btngetinnClick
        end
        object txtsund: TEdit
          Left = 56
          Top = 37
          Width = 134
          Height = 21
          TabOrder = 2
          Text = 'Sundries[Rabino]'
        end
        object btngetsund: TButton
          Left = 5
          Top = 37
          Width = 45
          Height = 15
          Caption = 'sund al>'
          TabOrder = 3
          OnClick = btngetsundClick
        end
        object lstinnroute: TListBox
          Left = 11
          Top = 104
          Width = 55
          Height = 57
          Font.Charset = TURKISH_CHARSET
          Font.Color = clWindowText
          Font.Height = -9
          Font.Name = 'Small Fonts'
          Font.Style = []
          ItemHeight = 11
          ParentFont = False
          TabOrder = 4
        end
        object lstsundroute: TListBox
          Left = 66
          Top = 104
          Width = 55
          Height = 57
          Font.Charset = TURKISH_CHARSET
          Font.Color = clWindowText
          Font.Height = -9
          Font.Name = 'Small Fonts'
          Font.Style = []
          ItemHeight = 11
          ParentFont = False
          TabOrder = 5
        end
        object btnaddinn: TButton
          Left = 11
          Top = 167
          Width = 45
          Height = 17
          Caption = 'x,y ekle'
          TabOrder = 6
          OnClick = btnaddinnClick
        end
        object btnaddsund: TButton
          Left = 66
          Top = 167
          Width = 45
          Height = 17
          Caption = 'x,y ekle'
          TabOrder = 7
          OnClick = btnaddsundClick
        end
        object btnclearsund: TButton
          Left = 104
          Top = 144
          Width = 17
          Height = 17
          Caption = 'X'
          TabOrder = 8
          OnClick = btnclearsundClick
        end
        object btnclearinn: TButton
          Left = 49
          Top = 144
          Width = 17
          Height = 17
          Caption = 'X'
          TabOrder = 9
          OnClick = btnclearinnClick
        end
        object chbuyarrow: TCheckBox
          Left = 3
          Top = 214
          Width = 182
          Height = 17
          Caption = 'rpr -> arrow 5000'#39'e tamamla.'
          Checked = True
          State = cbChecked
          TabOrder = 10
          OnClick = chbuyarrowClick
        end
        object chbuywolf: TCheckBox
          Left = 3
          Top = 229
          Width = 153
          Height = 17
          Caption = 'rpr -> wolf 100'#39'e tamamla.'
          Checked = True
          State = cbChecked
          TabOrder = 11
          OnClick = chbuywolfClick
        end
        object btnsave1: TButton
          Left = 11
          Top = 184
          Width = 45
          Height = 17
          Caption = 'kaydet'
          TabOrder = 12
          OnClick = btnsave1Click
        end
        object btnsave2: TButton
          Left = 66
          Top = 184
          Width = 45
          Height = 17
          Caption = 'kaydet'
          TabOrder = 13
          OnClick = btnsave2Click
        end
        object txtinvslot: TEdit
          Left = 3
          Top = 250
          Width = 22
          Height = 21
          TabOrder = 14
          Text = '4'
        end
        object lstpotroute: TListBox
          Left = 121
          Top = 104
          Width = 55
          Height = 57
          ItemHeight = 13
          TabOrder = 15
        end
        object btnclearpot: TButton
          Left = 159
          Top = 144
          Width = 17
          Height = 17
          Caption = 'X'
          TabOrder = 16
          OnClick = btnclearpotClick
        end
        object btnaddpot: TButton
          Left = 121
          Top = 167
          Width = 45
          Height = 17
          Caption = 'x,y ekle'
          TabOrder = 17
          OnClick = btnaddpotClick
        end
        object btnsave3: TButton
          Left = 121
          Top = 184
          Width = 45
          Height = 17
          Caption = 'kaydet'
          TabOrder = 18
          OnClick = btnsave3Click
        end
        object btngetpot: TButton
          Left = 5
          Top = 56
          Width = 45
          Height = 15
          Caption = 'pot al>'
          TabOrder = 19
          OnClick = btngetpotClick
        end
        object txtpot: TEdit
          Left = 56
          Top = 56
          Width = 134
          Height = 21
          TabOrder = 20
          Text = '[Potion Merchant]Clepio'
        end
      end
      object grpbot: TGroupBox
        Left = -3
        Top = 506
        Width = 193
        Height = 93
        Caption = 'bot'
        TabOrder = 4
        object Label2: TLabel
          Left = 3
          Top = 16
          Width = 38
          Height = 13
          Caption = 'merkez:'
        end
        object lbcenter: TLabel
          Left = 83
          Top = 16
          Width = 16
          Height = 13
          Caption = '0,0'
        end
        object Label3: TLabel
          Left = 3
          Top = 35
          Width = 112
          Height = 13
          Caption = 'max. yayilma mesafesi:'
        end
        object btngetcenter: TButton
          Left = 47
          Top = 16
          Width = 30
          Height = 17
          Caption = 'AL->'
          TabOrder = 0
          OnClick = btngetcenterClick
        end
        object txtmaxgo: TEdit
          Left = 121
          Top = 32
          Width = 25
          Height = 21
          TabOrder = 1
          Text = '10'
        end
        object chminor: TCheckBox
          Left = 8
          Top = 56
          Width = 52
          Height = 17
          Caption = 'minor'
          TabOrder = 2
          OnClick = chminorClick
        end
        object chusepot: TCheckBox
          Left = 56
          Top = 56
          Width = 134
          Height = 17
          Caption = 'mana: canta ilk kutu'
          TabOrder = 3
          OnClick = chusepotClick
        end
        object chgetpot: TCheckBox
          Left = 8
          Top = 72
          Width = 182
          Height = 17
          Caption = 'pot takviye: < 5 ise 100 pot al.'
          TabOrder = 4
          OnClick = chgetpotClick
        end
      end
      object btnstart: TButton
        Left = 2
        Top = 601
        Width = 90
        Height = 25
        Caption = 'Baslat'
        TabOrder = 5
        OnClick = btnstartClick
      end
      object btnstop: TButton
        Left = 98
        Top = 601
        Width = 90
        Height = 25
        Caption = 'Dur'
        TabOrder = 6
        OnClick = btnstopClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'diger'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object btndelos: TButton
        Left = 3
        Top = 3
        Width = 73
        Height = 25
        Caption = 'delos'
        TabOrder = 0
        OnClick = btndelosClick
      end
      object btntrade: TButton
        Left = 3
        Top = 34
        Width = 73
        Height = 25
        Caption = 'hedef trade'
        TabOrder = 1
        OnClick = btntradeClick
      end
    end
  end
  object tminncheck: TTimer
    Enabled = False
    Interval = 5000
    OnTimer = tminncheckTimer
    Left = 168
    Top = 472
  end
  object tmsundcheck: TTimer
    Enabled = False
    Interval = 5000
    OnTimer = tmsundcheckTimer
    Left = 176
    Top = 424
  end
  object tmminor: TTimer
    Enabled = False
    Interval = 300
    OnTimer = tmminorTimer
    Left = 168
    Top = 600
  end
  object tmpot: TTimer
    Enabled = False
    Interval = 2100
    OnTimer = tmpotTimer
    Left = 168
    Top = 552
  end
  object tmlf: TTimer
    Enabled = False
    OnTimer = tmlfTimer
    Left = 176
    Top = 360
  end
  object tmpotcheck: TTimer
    Enabled = False
    Interval = 5000
    OnTimer = tmpotcheckTimer
    Left = 136
    Top = 472
  end
end
