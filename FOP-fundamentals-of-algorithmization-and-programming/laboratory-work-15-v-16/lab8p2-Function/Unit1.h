//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TPanel *Panel1;
        TImage *Image2;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        int xx1, xx2, yy1, yy2;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        float x1, x2, y1, y2;
        int n;
        int ZoomX(float x);
        int ZoomY(float y);
        float func(float x);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
