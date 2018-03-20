#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <fstream>

#define TOP 4
#define LEFT 4
#define WIDTH 10
#define HEIGTH 22

using namespace std;

void resizeConsole(int width, int height);
void textcolor(int x);
void gotoxy(int x,int y);
void clrscr();


void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}


void gotoxy(int x,int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}


void clrscr()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void movebox(int x, int y)
{

}

void DrawBoard()
{
    int i, j;
    for (i=LEFT;i<=LEFT+WIDTH+1;i++)
    {
        for (j=TOP;j<=TOP+HEIGHT+1;j++)
        {
            if (i==LEFT || j==TOP || i==LEFT+WIDTH+1 || j==TOP+HEIGHT+1)
            {
                gotoxy(i,j);
                textcolor(177);
                cout << "|";
                textcolor(7);
            }
        }
        cout << endl;
    }

}

void DecorateBox ()
{
    int i,j;
    for (i=0;i<HEIGTH;i++)
    {
        for (j=0;j<WIDTH;j++)
        {
            if (board[i][j]==1 && i>4)
            {
                gotoxy(j+LEFT+1,i++TOP-4)
                textcolor(15);
                printf ("%c",2);
            }
            if (board[i][j]==0 && i>4)
            {
                gotoxy(j+LEFT+1,i++TOP-4)
                textcolor(0);
                cout << " ";
            }

        }
    }
}
void UpdateScore (int Row)
{
    int i,j;

}
int main ()
{
//    ifstream Intro;
//    Intro.open("intro.txt", ios::in);
//    while (!Intro.eof())
//    {
//        char c;
//        Intro.get(c);
//        cout << c;
//        if (kbhit())
//        {
//            return 0;
//        }
//    }
//
//    Intro.close();
    int board[WIDTH][HEIGTH]
    DrawBoard();
    return 0;
}
