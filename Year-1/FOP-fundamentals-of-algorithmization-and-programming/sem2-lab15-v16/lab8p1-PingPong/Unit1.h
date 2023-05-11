//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TButton *Button1;
        TButton *Button2;
        TTimer *Timer1;
        TLabel *Label1;
        TMemo *Memo1;
        TShape *Shape4;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button3;
        TButton *Button4;
        TLabel *Label5;
        TButton *Button5;
        TShape *Shape5;
        TShape *Shape6;
        TBitBtn *BitBtn1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
