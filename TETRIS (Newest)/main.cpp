#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
#include "console.h"

using namespace std;

int main ()
{
//    ifstream Intro;
//    Intro.open("intro.txt", ios::in);
//    while (!Intro.eof())
//    {
//        char c;
//        Intro.get(c);
//        cout << c;
//        Sleep(100);
//        if (kbhit())
//        {
//            return 0;
//        }
//    }
//    Intro.close();

    Tetromino* _tetromino;
    INFO info;
    _tetromino = creatTetromino(typeofTetromino());
    initGame(&info);
    int IDNext = typeofTetromino();
    clock_t Start,End;
    drawboard();
    do
    {
        drawInfo(info);
        drawTetromino(_tetromino);
        deleteNext();
        drawNext(IDNext);
        Start=clock();
        do
        {
            if (kbhit())
            {
                char c = toupper(getch());
                deleteTetromino(_tetromino);
                switch(c)
                {
                case 'W':
                    {
                    rotateTetromino(_tetromino);
                    break;
                    }
                case 'A':
                    turnLeft(_tetromino);
                    break;
                case 'D':
                    turnRight(_tetromino);
                    break;
                case 'S':
                    goDown(_tetromino);
                    break;
                }
                drawTetromino(_tetromino);
            }
            End=clock();
        }while((End-Start)<info.speed);
        deleteTetromino(_tetromino);
        if (goDown(_tetromino)== 0)
        {
            inputtoboard(_tetromino);
            int ketqua = check(_tetromino,&info);
            if (ketqua == -1 || ketqua == 0)
                break;
            emptyTetromino(_tetromino); // giaiphongbonho
            _tetromino = creatTetromino(IDNext);
            IDNext = typeofTetromino();
            displayBoard();
        }
    }while(1);
    gotoxy(40,10);
    cout << "Game Over!!!";
    gotoxy(40,11);
    cout << "Your Score: " << info.score;
    getch();
}
