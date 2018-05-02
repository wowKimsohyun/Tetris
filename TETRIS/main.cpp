#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <time.h>

#define TOP 4
#define LEFT 4
#define WIDTH 10
#define HEIGHT 22

using namespace std;

int board[HEIGHT][WIDTH];

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

void drawboard()
{
    int i, j;
    for (i=LEFT;i<=LEFT+WIDTH+1;i++)
    {
        for (j=TOP;j<=TOP+18+1;j++)
        {
            if((j==TOP||j==TOP+18+1)&&i>LEFT&&i<LEFT+WIDTH+1)
            {
                gotoxy(i,j);
                textcolor(7);
                printf("%c",205);
            }
            if((i==LEFT||i==LEFT+WIDTH+1)&&j>TOP&&j<TOP+18+1)
            {
                gotoxy(i,j);
                textcolor(7);
                printf("%c",186);
            }
        }
    }
    gotoxy(TOP,LEFT);textcolor(7);printf("%c" ,219);
    gotoxy(LEFT+WIDTH+1,TOP);textcolor(7);printf("%c" ,219);
    gotoxy(LEFT,TOP+18+1);textcolor(7);printf("%c" ,219);
    gotoxy(LEFT+WIDTH+1,TOP+18+1);textcolor(7);printf("%c" ,219);


}

void displayBoard ()
{
    int i,j;
    for (i=0;i<HEIGHT;i++)
    {
        for (j=0;j<WIDTH;j++)
        {
            if (board[i][j]==1 && i>=4)
            {
                gotoxy(j+LEFT+1,i+TOP+1-4);
                textcolor(15);
                printf ("%c",2);
            }
            if (board[i][j]==0 && i>4)
            {
                gotoxy(j+LEFT+1,i+TOP+1-4);
                textcolor(0);
                cout << " ";
            }

        }
    }
}

// cap nhap toa do khi an diem
void updateScore (int nRow)
{
    int i,j;
    for (i=nRow;i>0;i--)
    {
        for (j=0;j<WIDTH;j++)
        {
            board[i][j]=board[i-1][j];
        }
    }
}

/* Tetromino */

struct Tetromino
{
    int **arr;
    int nRow, nCol;
    int iBoard, jBoard;

};

Tetromino* creatTetromino(int ID);

void inputtoboard (Tetromino* pTetromino);

void drawTetromino (Tetromino* pTetromino);

void deleteTetromino (Tetromino* pTetromino);

void emptyTetromino (Tetromino* pTetromino);

/* Move Tetromino */

bool Inside (int i, int j);

bool Left (int i, int j);

bool Right(int i, int j);

bool Down (int i, int j);

void turnLeft (Tetromino* pTetromino);

void turnRight (Tetromino* pTetromino);

int goDown (Tetromino* pTetromino);

void rotateTetromino (Tetromino* pTetromino);


/* Infomartion */

struct INFO
{
    int score;
    int level;
    float speed;
};
void initGame (INFO* pinfo);

int update (INFO* pinfo, int score);

void drawInfo (INFO pinfo);

 /* Next Tetromino */

void drawNext (int ID);

void deleteNext ();

int check (Tetromino* pTetromino, INFO *pinfogame);

int typeofTetromino ();

/* Win/Lose */

int check (Tetromino* pTetromino, INFO *pinfogame);

/* Dinh Nghia */

/* Tetromino */

Tetromino* creatTetromino(int ID)   // tao khoi gach
{
    Tetromino *pTetromino = new Tetromino[sizeof(Tetromino)];
    switch (ID) //Khoi tao thong so khoi gach
    {
        case 15:
            pTetromino->nRow = 4;
            pTetromino->nCol = 1;
            pTetromino->iBoard = 0;
            pTetromino->jBoard = 5;
            break;
        case 31:
            pTetromino->nRow = 2;
            pTetromino->nCol = 2;
            pTetromino->iBoard = 2;
            pTetromino->jBoard = 5;
            break;
        default:
            pTetromino->nRow = 2;
            pTetromino->nCol = 3;
            pTetromino->iBoard = 2;
            pTetromino->jBoard = 5;
            break;

    }
    pTetromino->arr = new int* [pTetromino->nRow];
    for (int i=0;i<pTetromino->nRow;i++)
    {
        pTetromino->arr[i] = new int [pTetromino->nCol];
    }
    int k=0;
    for (k=0;k<pTetromino->nCol*pTetromino->nRow;k++)
    {
        pTetromino->arr[k/pTetromino->nCol][k%pTetromino->nCol] = (ID >> (pTetromino->nCol*pTetromino->nRow-1-k) & 1);
    }
    return pTetromino;

}

// Cap nhap toa do vao mang board
void inputtoboard (Tetromino* pTetromino) // Gan gia tri tu ma tran khoi gach sang ma tran choi
{
    int i,j;
    for (i=0;i<pTetromino->nRow;i++)
    {
        for (j=0;j<pTetromino->nCol;j++)
        {
            if (pTetromino->arr[i][j]==1)
            {
                board[pTetromino->iBoard+i][pTetromino->jBoard+j]=1;
            }
        }
    }
}
void drawTetromino (Tetromino* pTetromino)
{
    int i,j;
    for (i=0;i<pTetromino->nRow;i++)
    {
        for (j=0;j<pTetromino->nCol;j++)
        {
            if (pTetromino->arr[i][j]==1 && (pTetromino->iBoard+i)>3)
            {
                gotoxy(LEFT+pTetromino->jBoard+j+1,TOP+pTetromino->iBoard+i-3);
                printf ("%c", 2);
            }
        }
    }
}
void deleteTetromino (Tetromino* pTetromino)
{
    int i,j;
    for (i=0;i<pTetromino->nRow;i++)
    {
        for (j=0;j<pTetromino->nCol;j++)
        {
            if (pTetromino->arr[i][j]==1 && (pTetromino->iBoard+i)>3)
            {
                gotoxy(LEFT+pTetromino->jBoard+j+1,TOP+pTetromino->iBoard+i-3);
                printf (" ");
            }
        }
    }
}

// Giai phong con tro
void emptyTetromino (Tetromino* pTetromino)
{
    int i;
    for (i=0;i<pTetromino->nRow;i++)
    {
        delete [] pTetromino->arr[i];
    }
    delete [] pTetromino->arr;
    delete pTetromino;
    pTetromino = NULL;
}

/* Move Tetromino */

//Di chuyen 1 o gach

bool Inside (int i, int j)
{
    if (i>=0 && i<HEIGHT && j>=0 && j<WIDTH)
    {
        return true;
    }
    return false;
}

bool Left (int i, int j)
{
    if (j>0 && Inside(i,j) == true && board[i][j-1]==0)
    {
        return true;
    }
    return false;
}

bool Right(int i, int j)
{
    if (j<WIDTH-1 && Inside(i,j) == true && board[i][j+1]==0)
    {
        return true;
    }
    return false;
}

bool Down (int i, int j)
{
    if (i<HEIGHT-1 && Inside(i,j) == true && board[i+1][j]==0)
    {
        return true;
    }
    return false;
}

// Di chuyen ca khoi gach

void turnLeft (Tetromino* pTetromino)
{
    int i,j;
    for (i=0;i<pTetromino->nRow;i++)
    {
        for (j=0;j<pTetromino->nCol;j++)
        {
            if (pTetromino->arr[i][j]==1)
            {
                if (Left(pTetromino->iBoard+i,pTetromino->jBoard+j)== false || pTetromino->iBoard<=3)
                    return;
            }
        }
        pTetromino->jBoard-=1;
    }
}

void turnRight (Tetromino* pTetromino)
{
    int i,j;
    for (i=0;i<pTetromino->nRow;i++)
    {
        for (j=0;j<pTetromino->nCol;j++)
        {
            if (pTetromino->arr[i][j]==1)
            {
                if (Right(pTetromino->iBoard+i,pTetromino->jBoard+j)== false || pTetromino->iBoard<=3)
                return;
            }
        }
        pTetromino->jBoard+=1;
    }
}

int goDown (Tetromino* pTetromino) // 0 can't down ; 1 go down;
{
    int i,j;
    for (i=0;i<pTetromino->nRow;i++)
    {
        for (j=0;j<pTetromino->nCol;j++)
        {
            if (pTetromino->arr[i][j]==1)
            {
                if (Down(pTetromino->iBoard+i,pTetromino->jBoard+j)== false)
                    return 0;
            }
        }
    }
    pTetromino->iBoard+=1;
    return 1;
}

void rotateTetromino (Tetromino* pTetromino)
{
    int i,j;
    int** tmpArr;
    int tmpCol = pTetromino->nRow;
    int tmpRow = pTetromino->nCol;
    tmpArr = new int* [tmpRow];
    for (i=0;i<tmpRow;i++)
    {
        tmpArr[i] = new int [tmpCol];
    }
    for (i=pTetromino->nRow-1;i>=0;i--)
    {
        for (j=pTetromino->nCol-1;j>=0;j--)
        {
            tmpArr[j][pTetromino->nRow-i-1]=pTetromino->arr[i][j];
        }
    }
    //ktra xoay
    for (i=0;i<tmpRow;i++)
    {
        for (j=0;j<tmpCol;j++)
        {
            if (Inside(pTetromino->iBoard+i,pTetromino->jBoard+j) == false|| board[pTetromino->iBoard+i][pTetromino->jBoard+j]==1)
                return;
        }
    }
    for (i=0;i<pTetromino->nRow;i++)
    {
        delete [] pTetromino->arr[i];
    }
    delete [] pTetromino->arr;
    pTetromino->nCol=tmpCol;
    pTetromino->nRow=tmpRow;
    pTetromino->arr=tmpArr;

}

/* Infomartion */

void initGame (INFO* pinfo)
{
    pinfo->level=1;
    pinfo->score=0;
    pinfo->speed=1000;
}

int update (INFO* pinfo, int score)
{
    pinfo->score+=score;
    if (pinfo->score>=200 && pinfo->level<2)
    {
        pinfo->level++;
        pinfo->speed-=250;
    }
    return 0;
}

void drawInfo (INFO pinfo)
{
    gotoxy(2*LEFT+WIDTH,TOP+5+3);printf("SCORE: %d", pinfo.score);
    gotoxy(2*LEFT+WIDTH,TOP+5+4);printf("LEVEL: %d", pinfo.level);
}

 /* Next Tetromino */

void drawNext (int ID)
{
//    int i,j;
//    for (i=WIDTH+2*LEFT;i<=WIDTH+2*LEFT+5+1;i++)
//    {
//        for (j=TOP;j<=TOP+5+1;j++)
//        {
//            if ((j==TOP || j==TOP+5+1) && i>WIDTH+2*LEFT && i<WIDTH+2*LEFT+5+1)
//            {
//                gotoxy(i,j);
//                textcolor(7);
//                printf("%c",205);
//            }
//            if ((i==WIDTH+2*LEFT || i==WIDTH+2*LEFT+5+1) && j>TOP && j<TOP+5+1)
//            {
//                gotoxy(i,j);
//                textcolor(7);
//                printf("%c",186);
//            }
//        }
//    }
//    gotoxy(2*LEFT+WIDTH,TOP);textcolor(7);printf("%c",219);
//    gotoxy(2*LEFT+WIDTH+5+1,TOP);textcolor(7);printf("%c",219);
//    gotoxy(2*LEFT+WIDTH,TOP+5+1);textcolor(7);printf("%c",219);
//    gotoxy(2*LEFT+WIDTH+5+1,TOP+5+1);textcolor(7);printf("%c",219);
    Tetromino* pnext = creatTetromino(ID);
    int iX=LEFT+WIDTH+5;
    int jY=TOP;
    for (int i=0;i<pnext->nRow;i++)
    {
        for (int j=0;j<pnext->nCol;j++)
        {
            if (pnext->arr[i][j]==1)
            {
                textcolor(7);
                gotoxy(iX+j,jY+i);printf ("%c", 2);
            }
        }
    }
}

void deleteNext ()
{
    int iX=LEFT+WIDTH+5;
    int jY=TOP;
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            textcolor(0);
            gotoxy(iX+j,jY+i);printf (" ");
        }
    }
}

int typeofTetromino ()
{
    int t=rand()%7;
    switch (t)
    {
    case 0:
        return 15;
        break;
    case 1:
        return 31;
        break;
    case 2:
        return 51;
        break;
    case 3:
        return 30;
        break;
    case 4:
        return 58;
        break;
    case 5:
        return 57;
        break;
    case 6:
        return 60;
        break;
    }
}

/* Win/Lose */

int check (Tetromino* pTetromino, INFO *pinfogame)
{
    int i,j,_count;
    i=pTetromino->nRow-1;
    if (pTetromino->iBoard<=3)
    {
        return -1; // End game
    }
    if (pinfogame->score>=1000)
    {
        return 0; // Win game
    }
    do
    {
        _count=0;
        for (j=0;j<WIDTH;j++)
        {
            if (board[pTetromino->iBoard+i][j]==1)
                _count++;
        }
        if (_count==WIDTH)
        {
            update(pinfogame,10);
            updateScore(pTetromino->iBoard+i);
            displayBoard();
        }
        else
        {
            i=i-1;
        }
    }
    while(i>=0);
    return 1;
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

    Tetromino* _tetromino;
    INFO info;
    _tetromino = creatTetromino(typeofTetromino());
    initGame(&info);
    int IDNext = typeofTetromino();
    clock_t Start,End;
//    srand(time(0));
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
    clrscr();
    cout << "Game Over!!!";
    getch();
}
