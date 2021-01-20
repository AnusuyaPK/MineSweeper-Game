#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <conio.h>
#include<time.h>
#include<windows.h>

void instructions();
int complexity();
void createBoard(int* board,int size,int mines);
void displayBoard(int* board,int* visited,int size,int mines);
void find(int* board,int size,int row,int col,int* visited,int* visitMain);

void instructions()
{
    printf("   WELCOME MINESWEEPER!!\n");
    printf("   INSTRUCTIONS:\n");
    printf("1. CHOOSE YOUR COMPLEXITY\n");
    printf("2. YOUR BOARD WILL APPEAR\n");
    printf("3. ENTER ROW AND COLUMN VALUE TO STEP INTO THE FIELD\n");
    printf("4. FLAG THE FIELDS WITH MIINES\n");
    printf("5. FIND ALL THE MINES AND SAVE THE CITY\n");
    printf("   PRESS 1 TO START THE GAME AND 0 TO QUIT THE GAME!!\n");
}

int complexity()
{
    int complx;
    printf("CHOOSE YOUR COMPLEXITY:\n");
    printf("1.EASY - 5*5 5 MINES\n");
    printf("2.MEDIUM - 7*7 10 MINES\n");
    printf("3.HARD - 10*10 20 MINES\n");
    scanf("%d",&complx);
    return complx;
}

void createBoard(int* board,int size,int mines)
{
    for(int row=0;row<size;row++)
    {
        for(int col=0;col<size;col++)
        {
            *(board+((row*size)+col)) = 0;
        }
    }
    printf("%d %d ",size,mines);
    int row;
    int col;

    while(mines-->0)
    {
        row = rand()%size;
        col = rand()%size;
        
        while(1)
        {
            if(*(board+((row*size)+col))!=-1)
            {
                *(board+((row*size)+col))=-1;
                if(row-1>=0 && *(board+(((row-1)*size)+col))!=-1)
                {
                    *(board+(((row-1)*size)+col))+=1;
                }
                if(row+1<size && *(board+(((row+1)*size)+col))!=-1)
                {
                    *(board+(((row+1)*size)+col))+=1;
                }
                if(col-1>=0 && *(board+(((row)*size)+(col-1)))!=-1)
                {
                    *(board+(((row)*size)+(col-1)))+=1;
                }
                if(col+1<size && *(board+(((row)*size)+(col+1)))!=-1)
                {
                    *(board+(((row)*size)+(col+1)))+=1;
                }
                if(col-1>=0 && row-1>=0 && *(board+(((row-1)*size)+(col-1)))!=-1)
                {
                    *(board+(((row-1)*size)+(col-1)))+=1;
                }
                if(col+1<size && row-1>=0 && *(board+(((row-1)*size)+(col+1)))!=-1)
                {
                    *(board+(((row-1)*size)+(col+1)))+=1;
                }
                if(col-1>=0 && row+1<size && *(board+(((row+1)*size)+(col-1)))!=-1)
                {
                    *(board+(((row+1)*size)+(col-1)))+=1;
                }
                if(col+1<size && row+1<size && *(board+(((row+1)*size)+(col+1)))!=-1)
                {
                    *(board+(((row+1)*size)+(col+1)))+=1;
                }
                break;
            }
            else
            {
                if(row+1<size)
                {
                    row++;
                }
                else
                {
                    if(row-1>=0)

                    {
                        row--;
                    }
                }
            }
        }
    }
}


void displayBoard(int* board,int* visited,int size,int mines)
{
    printf("   ");
    for(int col=0;col<size;col++)
    {
        printf("%2d ",col);
    }
    printf("\n");
    for(int row=0;row<size;row++)
    {
        printf("%2d ",row);
        for(int col=0;col<size;col++)
        {
            if(*(visited+((row*size)+col))==1)
            {
                printf("%2d",*(board+((row*size)+col)));
                printf(" ");
            }
            else if(*(visited+((row*size)+col))==-1)
            {
                printf(" F ");
            }
            else if(*(visited+((row*size)+col))==5)
            {
                printf("   ");
            }
            else
            {
                printf(" - ");
            }
        }
        printf("\n\n");
    }

}

void makeZero(int* arr,int size)
{
    for(int row=0;row<8;row++)
    {
        *(arr+row) = 0;
    }
}

void find(int* board,int size,int row,int col,int* visited,int* visitMain)
{
    //[n-0,s-1,w-2,e-3,se-4,ne-5,nw-6,sw-7]
    int v_pass[8] = {0,0,0,0,0,0,0,0};
    if( (!(*(visited+0))) && (row-1>=0) )// vist north
    {
        if(*(board+(( (row-1) *size)+col))==0)
        {
            *(visited+0)=1;
            *(visited+5)=1;
            *(visited+6)=1;
            v_pass[1]=1;
            v_pass[4]=1;
            v_pass[7]=1;
            find(board,size,row-1,col,v_pass,visitMain);
            *(visitMain+(( (row-1) *size)+col)) = 5;
        }
        else
        {
            *(visitMain+(( (row-1) *size)+col)) = 1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+1))) && (row+1<size) )// visit south
    {
        if(*(board+(( (row+1) *size)+col))==0)
        {
            *(visited+1)=1;
            *(visited+4)=1;
            *(visited+7)=1;
            v_pass[0]=1;
            v_pass[5]=1;
            v_pass[6]=1;
            find(board,size,row+1,col,v_pass,visitMain);
            *(visitMain+(( (row+1) *size)+col))=5;
        }
        else
        {
            *(visitMain+(( (row+1) *size)+col))=1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+2))) && (col-1>=0) )// visit west
    {
        if(*(board+((row*size)+ (col-1) ))==0)
        {
            *(visited+2)=1;
            *(visited+6)=1;
            *(visited+7)=1;
            v_pass[3]=1;
            v_pass[4]=1;
            v_pass[5]=1;
            find(board,size,row,col-1,v_pass,visitMain);
            *(visitMain+((row*size)+ (col-1) ))=5;
        }
        else
        {
            *(visitMain+((row*size)+ (col-1) ))=1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+3))) && (col+1<size))// visit east
    {
        if(*(board+((row*size)+(col+1)))==0)
        {
            *(visited+3)=1;
            *(visited+4)=1;
            *(visited+5)=1;
            v_pass[2]=1;
            v_pass[6]=1;
            v_pass[7]=1;
            find(board,size,row,col+1,v_pass,visitMain);
            *(visitMain+((row*size)+(col+1)))=5;
        }
        else
        {
            *(visitMain+((row*size)+(col+1)))=1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+4))) && (row+1<size) && (col+1<size) )// visit south east
    {
        if(*(board+(( (row+1)*size)+ (col+1) ))==0)
        {
            *(visited+4)=1;
            v_pass[6]=1;
            v_pass[0]=1;
            v_pass[2]=1;
            find(board,size,row+1,col+1,v_pass,visitMain);
            *(visitMain+(( (row+1)*size)+ (col+1) )) = 5;
        }
        else
        {
            *(visitMain+(( (row+1)*size)+ (col+1) )) = 1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+5))) && (row-1>=0) && (col+1<size))//visit north east
    {
        if(*(board+(( (row-1)*size)+ (col+1) ))==0)
        {
            *(visited+5)=1;
            v_pass[7]=1;
            v_pass[2]=1;
            v_pass[1]=1;
            find(board,size,row-1,col+1,v_pass,visitMain);
            *(visitMain+(( (row-1)*size)+ (col+1) )) = 5;
        }
        else
        {
            *(visitMain+(( (row-1)*size)+ (col+1) )) = 1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+6))) && (row-1>=0) && (col-1>=0) )// visit north west
    {
        if(*(board+(( (row-1)*size)+ (col-1) ))==0)
        {
            *(visited+6)=1;
            v_pass[4]=1;
            v_pass[3]=1;
            v_pass[1]=1;
            find(board,size,row-1,col-1,v_pass,visitMain);
            *(visitMain+(( (row-1)*size)+ (col-1) )) = 5;
        }
        else
        {
            *(visitMain+(( (row-1)*size)+ (col-1) )) = 1;
        }
    }
    makeZero(v_pass,8);
    if( (!(*(visited+7))) && (row+1<size) && (col-1>=0) )//visit south west
    {
        if(*(board+(( (row+1)*size)+ (col-1) ))==0)
        {
            *(visited+7)=1;
            v_pass[5]=1;
            v_pass[0]=1;
            v_pass[3]=1;
            find(board,size,row+1,col-1,v_pass,visitMain);
            *(visitMain+(( (row+1)*size)+ (col-1) )) = 5;
        }
        else
        {
            *(visitMain+(( (row+1)*size)+ (col-1) )) = 1;
        }
    }
}

int main()
{
    instructions();

    int startGame;
    scanf("%d",&startGame);

    int complx;
    int mines;
    int size;

    if(startGame == 1)
    {
        complx = complexity();
        if(complx == 1)
        {
            size = 5;
            mines = 5;
        }
        else if(complx == 2)
        {
            size = 7;
            mines = 10;
        }
        else
        {
            size = 10;
            mines = 20;
        }
        int gameBoard[size][size];
        int visited[size][size];
        for(int row=0;row<size;row++)
        {
            for(int col=0;col<size;col++)
            {
                visited[row][col] = 0;
            }
        }
        createBoard(gameBoard,size,mines);

        int flag;
        int row,col;
        int rowd,cold;
        int visit[8];
        makeZero(visit,8);
        while(1)
        {
            system("cls");
            printf("Mines: %d\n",mines);
            displayBoard(gameBoard,visited,size,mines);
            if(mines==0)
            {
                printf("CONGRATS!!!\n");
                printf("YOU SAVED THE CITY!!!\n");
                break;
            }
            else
            {
                while(1)
                {
                    printf("Row: ");
                    scanf("%d",&row);
                    printf("\nCol: ");
                    scanf("%d",&col);
                    printf("\n");
                    if(row>=0 && row<size && col>=0 && col<size)
                    {
                        break;
                    }
                    else
                    {
                        printf("OOPS!\n");
                        printf("INVALID ROW AND COLUMN\n");
                        printf("ENTER VALID INDEX!\n");
                    }
                }
                printf("Flag? 1/0: ");
                scanf("%d",&flag);

                if(flag == 1)
                {
                    printf("%d ",visited[row][col]);

                    if(visited[row][col] == 0)
                    {
                        visited[row][col] = -1;
                        mines--;
                    }
                    else
                    {
                        visited[row][col] = 0;
                        mines++;
                    }
                }
                else
                {
                    if(gameBoard[row][col]==0)
                    {
                        visited[row][col]=5;
                        find(gameBoard,size,row,col,visit,visited);
                    }
                    else if(gameBoard[row][col]==-1)
                    {
                        printf("YOU HAVE STEPPED ON A BOMB!!\n");
                        printf("SORRY, YOU LOST THE GAME!!\n");
                        printf("BETTER LUCK NEXT TIME!!\n");
                        printf("CORRECT MINE POSITIONS:\n");
                        for(int r=0;r<size;r++)
                        {
                            for(int c=0;c<size;c++)
                            {
                                if(gameBoard[r][c]==-1)
                                {
                                    visited[r][c] = -1;
                                }
                                else if(gameBoard[r][c]==0)
                                {
                                    visited[r][c] = 0;
                                }
                                else
                                {
                                    visited[r][c] = 0;
                                }
                            }
                        }
                        displayBoard(gameBoard,visited,size,mines);
                        break;
                    }
                    else
                    {
                        visited[row][col] = 1;
                    }
                }
            }

        }


    }
    else
    {
        printf("QUITING GAME...");
    }
    return 0;
}
