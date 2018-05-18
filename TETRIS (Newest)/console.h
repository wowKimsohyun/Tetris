#define TOP 4
#define LEFT 4
#define WIDTH 10
#define HEIGHT 22

/* Support */

void textcolor(int x);

void gotoxy(int x,int y);

void clrscr();

/* Diplay Screen */

void drawboard();

void displayBoard ();


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

int typeofTetromino ();

/* Win/Lose */

void updateScore (int nRow);

int check (Tetromino* pTetromino, INFO *pinfogame);

