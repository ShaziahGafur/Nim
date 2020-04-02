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
    char win = 'y';
    
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
    
    while(win == 'y')
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
    
        printf("enter win ");
        scanf(" %c", &win);
                
                
    }
    
    return 0;
        
} 
        
        
        
        
        
        
    
    
    

    


