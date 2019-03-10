/**************************************************************
*       David F. Signoretti daivd@signoretti.ca
*       C++ ISYS326
*
*       Instructor              John Selmys
*
*       Project Name:Assignment number One
*       File:game.c
*       Date:06 /03 /2000
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>

static int *StartPointer;

void Intro(void){
    printf("\nWelcome to the slide game:\nMove the numbers around by using the");
    printf("\nu for up\nd for down\nl for left\nr for right\n");
    printf("The zero is the blank space\n\n");
}
void ToHeap(int BoardSizeSquared){
    int MakeBoard;
    StartPointer = (int *)malloc(BoardSizeSquared * sizeof(int));
    for ( MakeBoard = 0 ; MakeBoard < BoardSizeSquared ; MakeBoard++ ){
        StartPointer[MakeBoard] = MakeBoard;
    }
}
void Swap(int SwapNumber){
    int ZeroFinder = 0,  SwapTemp;

    while (StartPointer[ZeroFinder] != 0)
        ZeroFinder++;

    SwapNumber += ZeroFinder;

    SwapTemp = StartPointer[ZeroFinder];
    StartPointer[ZeroFinder] = StartPointer[SwapNumber];
    StartPointer[SwapNumber] = SwapTemp;
}
void DisplayBoard(int BoardSize){
    int i, j, val = 0;

    for ( i = 0; i < BoardSize ; i++ ){
        for ( j = 0 ; j < BoardSize ; j++ ){
            printf("\t%i", StartPointer[val]);
            val++;
        }
        printf("\n");
    }
}
void InOrder(int BoardSizeSquared, int ExitMoves){
    int i;
    for ( i = 0 ; i < BoardSizeSquared ; i++ ){
        if (StartPointer[i] != i)
            return;
    }
    printf("You win in %i number of moves:\n\n\n" , ExitMoves);
    free(StartPointer);
    exit (0);
}
void CloseOut(int ExitMoves){
    free(StartPointer);
    printf("The total number of moves was    %i:\n\n\n" , ExitMoves);
    exit(0);
}
int main(void){
    char Board[10], InputChar = '\0';
    int BoardSize, ShuffleTemp, ShuffleLoop, ShuffleNumber, BoardSizeSquared, ShuffleBoard, MovesPlayed = 0;
    Intro();
    do{
        puts("Enter a Board size more than 1 but  less than 10:");
        BoardSize = atoi(gets(Board));
        if (BoardSize < 2 || BoardSize > 9)
            puts("Board size more than 1 but  less than 10:");
    }while (BoardSize < 2 || BoardSize > 9);

    BoardSizeSquared = BoardSize * BoardSize;
    ToHeap(BoardSizeSquared);

    srand((unsigned)time(NULL));
    for ( ShuffleLoop = 0; ShuffleLoop < 100 ; ShuffleLoop++ ){
        ShuffleNumber=rand()% BoardSizeSquared;
        ShuffleBoard=rand()% BoardSizeSquared;

        ShuffleTemp = StartPointer[ShuffleNumber];
        StartPointer[ShuffleNumber] = StartPointer[ShuffleBoard];
        StartPointer[ShuffleBoard] = ShuffleTemp;
    }
    DisplayBoard(BoardSize);

    while(InputChar != 'Q'){
        puts("Next Move  u, d, l, r or q to quit!");
        InputChar = toupper(getch());

        switch(InputChar){
            case'D':
                Swap((-1 * BoardSize));
                break;
            case'U':
                Swap(BoardSize);
                break;
            case'R':
                Swap(-1);
                break;
            case'L':
                Swap(1);
                break;
            case'Q':
                CloseOut(MovesPlayed);
                break;
            default:
                printf("\n\n**** Invalid Entry ****\n\n");
                MovesPlayed--;
                break;
        }
        DisplayBoard(BoardSize);
        InOrder(BoardSizeSquared, MovesPlayed);
        MovesPlayed++;
    }
    return (0);
}

