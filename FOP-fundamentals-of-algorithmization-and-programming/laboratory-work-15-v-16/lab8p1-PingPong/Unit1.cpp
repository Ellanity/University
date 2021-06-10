//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <time.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int ball_angular = 65;
int ball_radius = 10;
double ball_speed = 5;
double platform_speed = 5.0;

double time_seconds = 0;
bool game_mode_alone = false;
bool game_mode_no_players = false;
int hard_level = 10;

int player1_score = 0, player2_score = 0;
bool ball_kicked = false;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        srand(time(0));
}
//---------------------------------------------------------------------------
// Start game with timer
void __fastcall TForm1::Button1Click(TObject *Sender) {Timer1->Enabled = true;}
//---------------------------------------------------------------------------
// Stop game with timer
void __fastcall TForm1::Button2Click(TObject *Sender) {Timer1->Enabled = false;}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        time_seconds += 0.005;

        // First gamer keys and movements
        if (GetKeyState('W') < 0 && game_mode_no_players == false) {
                if (Shape1->Top > 10)
                        Shape1->Top -= platform_speed;
        }
        if (GetKeyState('S') < 0 && game_mode_no_players == false) {
                if (Shape1->Top < 190)
                        Shape1->Top += platform_speed;
        }

        // First bot
        if (game_mode_no_players)
        {
                if ((Shape1->Top - (Shape3->Top + ball_radius)) > (0 - hard_level + (rand() % 20)))
                        if (Shape1->Top > 10)
                                Shape1->Top -= platform_speed + hard_level / 3;
                if (((Shape3->Top - ball_radius) - (Shape1->Top + 100)) > (0 - hard_level + (rand() % 20)))
                        if (Shape1->Top < 190)
                                Shape1->Top += platform_speed + hard_level / 3;
        }

        // Second gamer keys and movements
        if (GetKeyState('P') < 0 && game_mode_alone == false && game_mode_no_players == false) {
                if (Shape2->Top > 10)
                        Shape2->Top -= platform_speed;
        }
        if (GetKeyState('L') < 0 && game_mode_alone == false && game_mode_no_players == false) {
                if (Shape2->Top < 190)
                        Shape2->Top += platform_speed;
        }

        // Second bot
        if (game_mode_alone || game_mode_no_players)
        {
                if ((Shape2->Top - (Shape3->Top + ball_radius)) > (0 - hard_level + (rand() % 20)))
                        if (Shape2->Top > 10)
                                Shape2->Top -= platform_speed + hard_level / 3;
                if (((Shape3->Top - ball_radius) - (Shape2->Top + 100)) > (0 - hard_level + (rand() % 20)))
                        if (Shape2->Top < 190)
                                Shape2->Top += platform_speed + hard_level / 3;
        }

        /*if (ball_kicked == true)
        {
                Memo1->Lines->Add(IntToStr(int(Shape3->Left)) + " " +
                IntToStr(int(Shape3->Top)));
                ball_kicked = false;
        }*/

        // Ball movements in vertical and horizontal surface
        double ball_radians = (ball_angular * 3.14159265359) / 180.0;
        if (ball_angular >= 0 && ball_angular <= 90) {
                Shape3->Top  += ball_speed * cos(ball_radians);
                Shape3->Left += ball_speed * sin(ball_radians);
        }
        else if (ball_angular >= 90 && ball_angular <= 180) {
                Shape3->Top  -= ball_speed * (-cos(ball_radians));
                Shape3->Left += ball_speed * sin(ball_radians);
        }
        else if (ball_angular >= 180 && ball_angular <= 270) {
                Shape3->Top  -= ball_speed * (-cos(ball_radians));
                Shape3->Left -= ball_speed * (-sin(ball_radians));
        }
        else if (ball_angular >= 270 && ball_angular <= 360) {
                Shape3->Top  += ball_speed * cos(ball_radians);
                Shape3->Left -= ball_speed * (-sin(ball_radians));
        }

        // Check obstackles
        bool vertical_obstacle_top = false, vertical_obstacle_bottom = false;
        bool horizontal_obstacle_left = false, horizontal_obstacle_right = false;
        if (Shape3->Top <= 0) {
                vertical_obstacle_top = true;
                Memo1->Lines->Add("vertical_obstacle_top: " + IntToStr(Shape3->Top) +
                " " + IntToStr(int(time_seconds)) +  " ba: " + IntToStr(int(ball_angular)));
                Shape3->Top = 3;
                if (ball_speed < 12)
                        ball_speed += 0.1;
        }
        if (Shape3->Top >= 290) {
                vertical_obstacle_bottom = true;
                Memo1->Lines->Add("vertical_obstacle_bottom: " + IntToStr(Shape3->Top) +
                " " + IntToStr(int(time_seconds)) +  " ba: " + IntToStr(int(ball_angular)));
                Shape3->Top = 287;
                if (ball_speed < 12)
                        ball_speed += 0.1;
        }
        if (Shape3->Left <= 0) {
                horizontal_obstacle_left = true;
                Memo1->Lines->Add("horizontal_obstacle_left: " + IntToStr(Shape3->Left) +
                " " + IntToStr(int(time_seconds)) +  " ba: " + IntToStr(int(ball_angular)));
                Shape3->Left = 3;
                if (ball_speed < 12)
                        ball_speed += 0.1;
        }
        if (Shape3->Left >= 460) {
                horizontal_obstacle_right = true;
                Memo1->Lines->Add("horizontal_obstacle_right: " + IntToStr(Shape3->Left) +
                " " + IntToStr(int(time_seconds)) +  " ba: " + IntToStr(int(ball_angular)));
                Shape3->Left = 457;
                if (ball_speed < 12)
                        ball_speed += 0.1;
        }

        // Check win cases
        bool player1_win = false, player2_win = false;

        if ((Shape3->Left <= 40) && (
        (Shape1->Top - (Shape3->Top + ball_radius) > 2) ||
        ((Shape3->Top) - Shape1->Top > 100)))
        {
                player2_win = true;
                Memo1->Clear();
                Memo1->Lines->Add("User 2 win!");
        }

        if ((Shape3->Left >= 440) && (
        (Shape2->Top - (Shape3->Top + ball_radius) > 2) ||
        ((Shape3->Top) - Shape2->Top > 100)))
        {
                player1_win = true;
                Memo1->Clear();
                Memo1->Lines->Add("User 1 win!");
        }

        // If nobody wins
        if (player1_win == false && player2_win == false)
        {
                // Direct hit of the ball with the left platform
                if ((Shape3->Left <= 40))// && (
                {
                        horizontal_obstacle_right = true;
                        ball_kicked = true;
                        Shape3->Left = 40;
                }
                // Direct hit of the ball with the right platform
                if ((Shape3->Left >= 439))// && (
                {
                        horizontal_obstacle_left = true;
                        ball_kicked = true;
                        Shape3->Left = 440;
                }

                // Kick the ball sideways on the left platform
                /*if (Shape3->Left > 20 && Shape3->Left < 35 && ball_kicked == false)
                {
                        if (Shape1->Top == Shape3->Top + 2 * ball_radius)
                                vertical_obstacle_bottom = true;
                                ball_kicked = true;
                        if (Shape1->Top + 100 == Shape3->Top)
                                vertical_obstacle_top = true;
                                ball_kicked = true;
                        Shape3->Left = 35 + ball_speed;
                }*/
                // Kick the ball sideways on the right platform
                /*if (Shape3->Left < 460 && Shape3->Left > 450 && ball_kicked == false)
                {
                        if (Shape1->Top == Shape3->Top + 2 * ball_radius)
                                vertical_obstacle_bottom = true;
                                ball_kicked = true;
                        if (Shape1->Top + 100 == Shape3->Top)
                                vertical_obstacle_top = true;
                                ball_kicked = true;
                        Shape3->Left = 445 - ball_speed;
                } */


                // Change ball angular with vertical_obstacle_top
                if (vertical_obstacle_top && ball_angular <= 180 && ball_angular >= 90)
                        ball_angular = 180 - ball_angular;
                if (vertical_obstacle_top && ball_angular <= 270 && ball_angular >= 180)
                        ball_angular = 540 - ball_angular;

                // Change ball angular with vertical_obstacle_bottom
                if (vertical_obstacle_bottom && ball_angular <= 90 && ball_angular >= 0)
                        ball_angular = 180 - ball_angular;
                if (vertical_obstacle_bottom && ball_angular <= 360 && ball_angular >= 270)
                        ball_angular = 540 - ball_angular;

                // Change ball angular with horizontal surface
                if (horizontal_obstacle_right || horizontal_obstacle_left)
                        ball_angular = 360 - ball_angular;

                ball_angular = abs(ball_angular % 360);

                // Show and change angular
                if (vertical_obstacle_bottom  || vertical_obstacle_top ||
                horizontal_obstacle_right || horizontal_obstacle_left) {

                        Memo1->Lines->Add("Kick L: " + IntToStr(int(Shape3->Left)) + " T: " +
                        IntToStr(int(Shape3->Top)));

                        if (ball_angular <= 335 && ball_angular >= 215)
                                ball_angular += (rand() % 3) * 5;
                        else if (ball_angular <= 155 && ball_angular >= 25)
                                ball_angular -= (rand() % 3) * 5;

                        Memo1->Lines->Add("Ball angular: " + IntToStr(int(ball_angular)));
                }
        }

        else if (player1_win == true || player2_win == true)
        {
                Memo1->Lines->Add("Circle1 L: " + IntToStr(int(Shape3->Left)) + " T: " +
                        IntToStr(int(Shape3->Top)));

                if (player1_win)
                        Memo1->Lines->Add("Shape2 L: " + IntToStr(int(Shape2->Left)) + " T: " +
                        IntToStr(int(Shape2->Top)));
                if (player2_win)
                        Memo1->Lines->Add("Shape1 L: " + IntToStr(int(Shape1->Left)) + " T: " +
                        IntToStr(int(Shape1->Top)));


                // Stop game
                if (game_mode_no_players == false)
                        Timer1->Enabled = false;
                // Update score
                if (player1_win)
                        player1_score += 1;
                if (player2_win)
                        player2_score += 1;
                Label2->Caption = IntToStr(player1_score);
                Label3->Caption = IntToStr(player2_score);

                // Give everything its original appearance
                Shape1->Top = 100;
                Shape2->Top = 100;
                Shape3->Top = 140;
                Shape3->Left = 240;

                int h = rand() % 2;
                ball_angular = (rand() % 90) + 45;
                if (h == 1)
                        ball_angular += 180;

                ball_speed = 5;
        }
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
        if (game_mode_alone == false && game_mode_no_players == false) {
                game_mode_alone =  true;
                Label4->Caption = "Mode: 1 player";
        }
        else if (game_mode_alone == true && game_mode_no_players == false) {
                game_mode_no_players =  true;
                Label4->Caption = "Mode: 0 player";
        }
        else {
                game_mode_alone = false;
                game_mode_no_players = false;
                Label4->Caption = "Mode: 2 players";
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        if (hard_level >= 30)
                hard_level = 0;
        else
                hard_level += 1;
        Label5->Caption = IntToStr(hard_level);
        Memo1->Lines->Add("Hard_level: " + IntToStr(hard_level));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        // Stop game
        Timer1->Enabled = false;
        // Update score
        player1_score = 0;
        player2_score = 0;
        Label2->Caption = IntToStr(player1_score);
        Label3->Caption = IntToStr(player2_score);

        // Give everything its original appearance
        Shape1->Top = 100;
        Shape2->Top = 100;
        Shape3->Top = 140;
        Shape3->Left = 240;

        hard_level = 10;
        Label5->Caption = IntToStr(hard_level);
        Memo1->Clear();

}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
        Memo1->Lines->Add(

                String("First Player:\r\n") +
                String("UP:   W           DOWN:   S\r\n") +
                String("Second Player:\r\n") +
                String("UP:   P            DOWN:   L\r\n\r\n") +
                String("Copyright © 2021 Paplauski Eldar\r\n") +
                String("email: <ping.pong.kruapan@gmail.com>")

        );
}
//---------------------------------------------------------------------------

