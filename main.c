/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kalrameh
 *
 * Created on April 1, 2020, 9:18 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>


using namespace std;

/*
 * 
 */

void remove(int size , int rowNo, int noPieces ,int row[6][6])
{
    for (int k= size; k >= size - noPieces; k--)
    {
        if(row[rowNo-1][k] != 0)
            row[rowNo-1][k] = 0;
    }
}

void checkWin(int row[6][6])
{
    for (int i =0; i< 6;i++)
    {
        for(int j = 0;j < 6; j++)
        {
            if (row[i][j] == 1) //if a single piece is still left
                return false; //no win occurred
                        
        }
    }
    return true; //empty board (no pieces left)
}

void print(int row[6][6])
{
    for (int i =0; i< 6;i++)
    {
        for(int j = 0;j < 6; j++)
        {
            printf("%d ",row[i][j]);
                    
                
        }
        
        printf("\n");
    }
}


int main() {
    
    bool turn = true;
    bool gameOver = false;
    char continueGame = 'y';
    
    int row[6][6];
    
    for (int i =0; i< 6;i++)
    {
        for(int j = 0;j <= i; j++)
        {
            row[i][j] = 1;
        }
    }
    
    for (int i =0; i< 6;i++)
    {
        for(int j = 0;j < 6; j++)
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
    
        if(turn == true)
        {
            printf( "Player 1: Which row would you like to remove pieces from? \n ");
            scanf( "%d", &rowNo);
                
            printf( " Player 1: How many pieces would you like to remove from ",rowNo, "? \n ");
            scanf( "%d", &noPieces);
        
            remove(rowNo, rowNo, noPieces ,row);
            
             print(row);
        
            turn = false;
            
        }
        
        else
        {
            printf( "Player 2: Which row would you like to remove pieces from? \n ");
            scanf( "%d", &rowNo);
                
            printf( " Player 2: How many pieces would you like to remove from ",rowNo, "? \n ");
            scanf( "%d", &noPieces);
        
            remove(rowNo, rowNo, noPieces ,row);
            
            print(row);
        
            turn = true;
            
        }
    
        printf("Continue? Press 'y' and hit ENTER");
        scanf(" %c", &win);
        
        if (checkWin){
            if (turn) //Turn fipped to Player 1, thus Player 2 made the winning move
                printf("Player 2 Wins!");
            else //Winning move by Player 1
                 printf("Player 1 Wins!");
            gameOver = true;
        }
                
                
    }
    //game finished or user exited
    
    if (continueGame != 'y')
        printf("User Exited Game");
    
    return 0;
        
} 
        
        
        
        
        
        
    
    
    

    


