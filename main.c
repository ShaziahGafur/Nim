//#include <cstdlib>
#include <stdlib.h>
//#include <iostream>
#include <stdio.h>
#include <stdbool.h>

//using namespace std;

/* 
 * Function Declarations:
 */

int MAX_BOARD_SIZE = 6;
int piecesRemaining[6]; //keep track of the number of game pieces that still exist in each row
bool removePieces(int rowNo, int noPieces, int row[6][6]);
bool checkWin();
void print(int row[MAX_BOARD_SIZE][MAX_BOARD_SIZE]);

int main() {
    bool turn = true;
    bool gameOver = false;
    char continueGame = 'y';
    
    piecesRemaining[1] = 1; //initliaze the # of game pieces in each row
    piecesRemaining[2] = 2;
    piecesRemaining[3] = 3;
    piecesRemaining[4] = 4;
    piecesRemaining[5] = 5;
    piecesRemaining[0] = 6;
    
    int row[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    
    for (int i =0; i < MAX_BOARD_SIZE;i++)
    {
        for(int j = 0;j <= i; j++)
        {
            row[i][j] = 1;
        }
    }
    
    for (int i =0; i < MAX_BOARD_SIZE;i++)
    {
        for(int j = 0;j < MAX_BOARD_SIZE; j++)
        {
            if(row[i][j] != 1)
                row[i][j] = 0;
            
        }
    }
   
    print(row);
    
    int rowNo;
    int noPieces;
    
    while(continueGame == 'y' && !gameOver)
    {
    
        // if(turn == true)
        // {
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
        
        
bool removePieces(int rowNo, int noPieces, int row[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
    rowNo--;
    if (rowNo<0 || rowNo > MAX_BOARD_SIZE - 1){
        printf("Invalid row #");
        return true;
    }
    int piecesLeftInRow = piecesRemaining[rowNo-1];
    if (rowNo > piecesLeftInRow || noPieces < 1){
        printf("Invalid # of pieces");
        return true;
    }
    for (int k= piecesLeftInRow; k >= piecesLeftInRow - noPieces; k--) //update board display
    {
        if(row[rowNo][k] != 0)
            row[rowNo][k] = 0;
    }
    piecesRemaining[rowNo-1]-=noPieces; //update the record of # of pieces left in board
    return false;
}

bool checkWin()
{
    for (int i =0; i< MAX_BOARD_SIZE;i++)
    {
        if (piecesRemaining[i] != 0) // if a single piece is left
            return false;
    }
    return true; //empty board (no pieces left)
}

void print(int row[6][6])
{
    for (int i =0; i< 6;i++)
    {   
        printf("Row %d\t", (i+1));
        for(int j = 0;j < 6; j++)
        {
            printf("%d ",row[i][j]);
                    
        }
        
        printf("\n");
    }
}        
        
        
        
        
    
    
    

    


