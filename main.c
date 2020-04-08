//#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Function Declarations: */
 
#define BOARD_SIZE 6

int piecesRemaining[BOARD_SIZE]; //keep track of the number of game pieces that still exist in each row
bool removePieces(int rowNo, int noPieces, int row[BOARD_SIZE][BOARD_SIZE]);
bool checkWin();
void print(int row[BOARD_SIZE][BOARD_SIZE]);

int main() {
    bool turn = true;
    bool gameOver = false;
    char continueGame = 'y';

    piecesRemaining[0] = 1; //initliaze the # of game pieces in row 1
    piecesRemaining[1] = 2; //row 2
    piecesRemaining[2] = 3; //row 3
    piecesRemaining[3] = 4;
    piecesRemaining[4] = 5;
    piecesRemaining[5] = 6;

    int row[BOARD_SIZE][BOARD_SIZE];
    
    //for each board's row, set the correct number of pieces 
    for (int i = 0; i < BOARD_SIZE;i++)
    {
        for(int j = 0; j < piecesRemaining[i]; j++)
        {
            row[i][j] = 1;
        }
    }
    
    for (int i = 0; i < BOARD_SIZE;i++)
    {
        for(int j = piecesRemaining[i]; j < BOARD_SIZE; j++)
        {
            row[i][j] = 0;
        }
    }
   
    print(row);
    
    int rowNo;
    int noPieces;
    
    while(continueGame == 'y' && !gameOver)
    {
    
        bool invalidMove = true;
        while(invalidMove){
            printf( "Player %d: Which row would you like to remove pieces from? \n ", ((turn) ? 1 : 2));
            scanf( "%d", &rowNo);
                
            printf( " Player %d: How many pieces would you like to remove from %d? \n ",((turn) ? 1 : 2), rowNo);
            scanf( "%d", &noPieces);
            
            invalidMove = removePieces(rowNo, noPieces ,row);

        }
         print(row);
        
        if (checkWin(row)){
            printf("Player %d Wins!", ((turn) ? 1 : 2));
            gameOver = true;
        }
        turn = turn^1; //toggle turn        
        printf("Continue? Press 'y' and hit ENTER");
        scanf(" %c", &continueGame);        
                
    }
    //game finished or user exited
    
    if (continueGame != 'y')
        printf("User Exited Game");
    
    return 0;
        
} 
        
        
bool removePieces(int rowNo, int noPieces, int row[BOARD_SIZE][BOARD_SIZE])
{
    rowNo--;
    if (rowNo<0 || rowNo >= BOARD_SIZE){
        printf("Invalid row #");
        return true;
    }
    int piecesLeftInRow = piecesRemaining[rowNo];
    if (noPieces > piecesLeftInRow || noPieces < 1){
        printf("Invalid # of pieces");
        return true;
    }
    for (int k = piecesLeftInRow; k >= piecesLeftInRow - noPieces; k--) //update board display
    {
        row[rowNo][k] = 0;
    }
    piecesRemaining[rowNo]-=noPieces; //update the record of # of pieces left in board
    return false;
}

bool checkWin()
{
    for (int i =0; i< BOARD_SIZE;i++)
    {
        if (piecesRemaining[i] != 0) // if a single piece is left
            return false;
    }
    return true; //empty board (no pieces left)
}

void print(int row[BOARD_SIZE][BOARD_SIZE])
{
    for (int i =0; i< BOARD_SIZE;i++)
    {   
        printf("Row %d\t", (i+1));
        for(int j = 0;j < BOARD_SIZE; j++)
        {
            printf("%d ",row[i][j]);
                    
        }
        
        printf("\n");
    }
}        
        
        
        
        
    
    
    

    


