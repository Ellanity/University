//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
        TCanvas * canv; // �������������� ����������
        int tx, ty;
        int i;
        float x, y, h;
        n = 100;

        canv = Image2->Canvas;

        // 1. ��������� ������ �������� ���������
        xx1 = 0;
        yy1 = 0;
        xx2 = Image2->Width;
        yy2 = Image2->Height;

        x1 = -10;
        x2 =  10;
        y1 = -20;
        y2 =  20;

        // 2. ��������� �������
        canv->Pen->Color = clBlue;
        canv->Brush->Color = clWhite;
        canv->Rectangle(0, 0, Image2->Width, Image2->Height);

        // 2.1. ��������� ���� ���������
        canv->Pen->Color = clBlack;
        // 2.2. ����� �������� ����� ������ ��������� X
        tx = ZoomX(0);
        ty = ZoomY(y1);
        canv->MoveTo(tx,ty);

        // �������� ����� ��� ��������� X
        tx = ZoomX(0);
        ty = ZoomY(y2);
        canv->LineTo(tx,ty);

        // 2.3. ����� ������ ��������� Y
        canv->Pen->Color = clBlack;
        tx = ZoomX(x1);
        ty = ZoomY(0);
        canv->MoveTo(tx,ty);

        // ���������� ��� Y
        tx = ZoomX(x2);
        ty = ZoomY(0);
        canv->LineTo(tx,ty);

        // 3. ��������� ������� �������
        canv->Pen->Color = clRed; // ����
        canv->Pen->Width = 2; // ������� �����

        // ���������� ������ �����
        x = x1;
        y = func(x);
        h = (x2-x1)/n;
        tx = ZoomX(x);
        ty = ZoomY(y);
        canv->MoveTo(tx,ty);

        // ���� �������� ����� � ��������� �������������� �����
        for (i = 0; i < n; i++)
        {
                x = x + h;
                y = func(x);
                tx = ZoomX(x);
                ty = ZoomY(y);
                canv->LineTo(tx,ty);
        }
}
//---------------------------------------------------------------------------

int TForm1::ZoomX(float x)
{
     return (int)(xx1 + (int)((x-x1)*(xx2-xx1)/(x2-x1)));
}

int TForm1::ZoomY(float y)
{
     return (int)(yy2 + (int)((y-y1)*(yy1-yy2)/(y2-y1)));
}

float TForm1::func(float x)
{
     return ( (0.1 * pow(x, 3)) + pow(x, 2) - (10 * sin(x)) - 8 );
}
