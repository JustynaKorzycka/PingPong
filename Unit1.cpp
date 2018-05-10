//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


/*void firsHurdle (x, y)
{
   x = 5;
   y = 6;
   hurdle1->Visible = true;
   if (ball->Top + ball->Height/2 >= hurdle1->Top &&
            ball->Top - ball->Height/2 <= hurdle1->Top + hurde1->Height &&
            ball->Left <= hurdle->Left +hurde1->Width)
            {

                 x = -(x);
                y = -(y+2);
            }
}    */

int x = 4;
int y = 5;
int reflection = 0;
int leftPoint = 0;
int rightPoint = 0;
AnsiString leftName = "";
AnsiString rightName = "";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        sndPlaySound(0, SND_ASYNC);
        ball->Left = 250;
        ball->Top = 100;
        Button1->Visible = false;
        Button2->Visible = false;
        Label2->Visible = false;
        Label1->Visible = false;
        score->Visible = false;
        timerBall->Enabled = true;
        ball->Visible = true;
        paddle1->Visible = true;
        paddle2->Visible = true;
        pause->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timerBallTimer(TObject *Sender)
{



        ball->Left += x;
        ball->Top += y;

        //if (reflection >=12) firsHurdle (x, y);
        if(ball->Top + y <= background->Top) y = -y;
        if (ball->Top+ball->Height + y  >= background->Top+background->Height-8) y = -y;

        if (ball->Top + ball->Height/2 >= paddle1->Top &&
            ball->Top - ball->Height/2 <= paddle1->Top + paddle1->Height &&
            ball->Left <= paddle1->Left +paddle1->Width )
            {
                if (ball->Top + ball->Height/2 == paddle1->Top +
                paddle1->Height/2)
                {
                        x = -0.5*x;
                        y = -0.5*y;
                }
                else
                {
                x = -(x-1);
                y = -y;
                reflection ++;
                }
                if (sound->Visible == true)sndPlaySound("snd/bum.wav", SND_ASYNC);
            }

        else if (ball->Top + ball->Height/2 >= paddle2->Top &&
            ball->Top - ball->Height/2 <= paddle2->Top + paddle2->Height &&
            ball->Left + ball->Width >= paddle2->Left +2 )
            {
              if (ball->Top + ball->Height/2 == paddle2->Top +
               paddle1->Height/2)
                {
                        x = -0.5*x;
                        y = -0.5*y;
                }
                else
                {
                x = -(x);
                y = -(y+2);
                reflection ++;
                }
                if (sound->Visible == true) sndPlaySound("snd/bumRight", SND_ASYNC);

            }
        else if (ball->Left+5 < paddle1->Left + paddle1->Width)
        {
          if(sound->Visible== true)sndPlaySound("snd/master.wav", SND_ASYNC);
          rightPoint ++;
          ball->Visible = false;
          timerBall->Enabled = false;
          pause->Visible = false;

          Label1->Caption = "Punkt dla gracza po prawej";
          Label1->Visible = true;
          Label2->Caption = "Iloœæ odbiæ: " + IntToStr(reflection);
          Label2->Visible = true;
          score->Caption = IntToStr(leftPoint) + ":" + IntToStr(rightPoint);
          score->Visible = true;
          reflection = 0;
          int *vx = &x;
          int *vy = &y;
          *vx = 4;
          *vy = 5;
          Button1->Caption = "Nastêpna runda";
          Button1->Visible = true;
          Button2->Visible = true;


        }
        else if (ball->Left > paddle2->Left)
        {
          if(sound->Visible== true)sndPlaySound("snd/master.wav", SND_ASYNC);
          leftPoint ++;
          ball->Visible = false;
          timerBall->Enabled = false;
          pause->Visible = false;

          Label1->Caption = "Punkt dla gracza po lewej ";
          Label1->Visible = true;
          Label2->Caption = "Iloœæ odbiæ: " + IntToStr(reflection);
          Label2->Visible = true;
          score->Caption = IntToStr(leftPoint) + ":" + IntToStr(rightPoint);
          score->Visible = true;
          reflection = 0;
          int *vx = &x;
          int *vy = &y;
          *vx = 4;
          *vy = 5;
          Button1->Caption = "Nastêpna runda";
          Button1->Visible = true;
          Button2->Visible = true;

        }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 65) timerLeftUp->Enabled = true;
        if(Key == 90) timerLeftDown->Enabled = true;
        if(Key == VK_DOWN) timerRightDown->Enabled = true;
        if(Key == VK_UP) timerRightUp->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timerLeftUpTimer(TObject *Sender)
{
        if(paddle1->Top >= 5) paddle1->Top -=10;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 65) timerLeftUp->Enabled = false;
        if(Key == 90) timerLeftDown->Enabled = false;
        if(Key == VK_DOWN) timerRightDown->Enabled = false;
        if(Key == VK_UP) timerRightUp->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timerLeftDownTimer(TObject *Sender)
{
        if(paddle1->Top + paddle1->Height < background->Height-5) paddle1->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timerRightUpTimer(TObject *Sender)
{
         if(paddle2->Top >= 5) paddle2->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timerRightDownTimer(TObject *Sender)
{
          if(paddle2->Top + paddle2->Height < background->Height-5) paddle2->Top +=10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        users->Visible = false;
        leftGamer->Caption = leftName;
        rightGamer->Caption = rightName;
        sndPlaySound(0, SND_ASYNC);
        ball->Left = 250;
        ball->Top = 100;
        Button1->Visible = false;
        Button2->Visible = false;
        Label2->Visible = false;
        Label1->Visible = false;
        score->Visible = false;
        pause->Visible = true;
        timerBall->Enabled = true;
        ball->Visible = true;
        paddle1->Visible = true;
        paddle2->Visible = true;
        rightPoint = 0;
        leftPoint = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pauseClick(TObject *Sender)
{
        timerBall->Enabled = false;
        pause->Visible = false;
        play->Visible = true;
        Label2->Caption = " PAUZA";
        Label2->Visible = true;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::playClick(TObject *Sender)
{
       Label2->Visible = false;
       play->Visible = false;
       timerBall->Enabled = true;
       pause->Visible = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::soundClick(TObject *Sender)
{
     sndPlaySound(0, SND_ASYNC);

     sound->Visible = false;
     noSound->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::noSoundClick(TObject *Sender)
{
        noSound->Visible = false;
        sound->Visible = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
         Button2->Visible = true;
         sndPlaySound("snd/master.wav", SND_ASYNC);
         users->Visible = true;
         usersName->Visible = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::okNameClick(TObject *Sender)
{
        if (leftName == "")
        {
        leftName = usersName->Text;
        usersName->Clear();
        users->Caption = "WprowadŸ imie gracza po prawej i kliknij OK:";
        }
        else
        {
        rightName = usersName->Text;
        users->Caption = "Witajcie " + leftName + " i " + rightName + "! Zaczynamy grê? :)";
        usersName->Visible = false;
        okName->Visible = false;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
       if (Application->MessageBox (
       "Czy na pewno chcesz zamkn¹æ plik?","PotwierdŸ",
       MB_YESNO | MB_ICONQUESTION) == IDYES)
       {
                Application->Terminate();
       }
       else  Action = caNone;
}
//---------------------------------------------------------------------------

